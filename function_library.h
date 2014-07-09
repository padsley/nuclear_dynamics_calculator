#include <gsl/gsl_sf_coulomb.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_sf_result.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_coupling.h>
#include <gsl/gsl_sf_legendre.h>
#include <TRandom3.h>
#include <TH1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TVector3.h>
#include <cmath>
#include <iostream>
#include <complex>

//Code written by Philip Adsley (@padsley, padsley(at)gmail.com). Please feel free to use or modify. I cannot guarantee that this code is always correct and working. Use at your own risk. I assume no liability for your results. Please check that they make sense. This code is freely available under 2 conditions: that you make any modified version available to others and that you inform me if you find any errors in it. Thanks.



//References to 'Iliadis' are to 'Nuclear Physics of Stars'. This is a rather good book and I commend it to you.
//References to 'Thompson and Nunes' are to 'Nuclear Reactions for Astrophysics'. Again, it's very good and you should consider getting a copy.


using namespace std;

double mu_calc(double A1, double A2)//Calculate the reduced mass in amu
{
  double result = (double)A1*(double)A2/((double)A1+(double)A2);
  return result;
}

double penetrability(int Z1, int Z2, double A1, double A2, int L, double E, double r)//See equation 2.162 in Iliadis, for example
{
//   cout << Z1 << "\t" << Z2 << "\t" << A1 << "\t" << A2 << "\t" << L << "\t" << E << "\t" << r << endl;
  double mu = mu_calc(A1, A2);
//   cout << "mu: " << mu << endl;

  double eta = 0.157489*(double)Z1*(double)Z2*sqrt(mu/E);
//   cout << "eta: " << eta << endl;

  double x = 0.218735*r*sqrt(mu*E);
//   cout << "kr: " << x << endl;

  gsl_sf_result F_result, Fp_result, G_result, Gp_result;
  int K=0;
  double exp_F, exp_G;

  int status = gsl_sf_coulomb_wave_FG_e(eta, x, L, K, &F_result, &Fp_result, &G_result, &Gp_result, &exp_F, &exp_G);

  if(status!=0)printf("status = %s\n", gsl_strerror(status));
  if(exp_F==0 && exp_G==0)
    {
    }
  else
    {
      cout << "Exponentials of F and G are non-zero... take care... this might mean that the code is reaching a fruity area" << endl;
    }

  double P = x/(pow(F_result.val,2)*exp(2*exp_F)+pow(G_result.val,2)*exp(2*exp_G));//P is defined as given in Iliadis Nuclear Physics of Stars, Equation 2.162
  /*if(P<1e-12)*/
//   cout << F_result.val << "\t" << exp_F << "\t" << G_result.val << "\t" << exp_G << "\t" << P << endl;
  return P;
}

double Wigner_width(int Z1, int Z2, double A1, double A2, int L, double E, double r)
{
//   double result = 83.135/mu_calc(A1, A2) * penetrability(Z1, Z2, A1, A2, L, E, r);
  double result = 83.135/mu_calc(A1, A2) / pow(r,2.) * penetrability(Z1, Z2, A1, A2, L, E, r);
  return result;
}

double shift_factor(int Z1, int Z2, int A1, int A2, int L, double E, double r)//See equation 2.162 in Iliadis, for example
{
  double mu = mu_calc(A1, A2);
  double eta = 0.157489*(double)Z1*(double)Z2*sqrt(mu/E);
  double x = 0.218735*r*sqrt(mu*E);
  
  double *fc_array, *fcp_array, *gc_array, *gcp_array;
  double F_exp, G_exp;
  fc_array = new double[1];
  fcp_array = new double[1];
  gc_array = new double[1];
  gcp_array = new double[1];

  int status = gsl_sf_coulomb_wave_FGp_array(L, 0, eta, x,  fc_array, fcp_array, gc_array, gcp_array, &F_exp, &G_exp);

  if(status!=0)printf("status = %s\n", gsl_strerror(status));

  double result = x * (fc_array[0]*fcp_array[0]*exp(2*F_exp)+gc_array[0]*gcp_array[0]*exp(2*F_exp))/(pow(fc_array[0],2)*exp(2*F_exp)+pow(gc_array[0],2)*exp(2*G_exp));
  return result;
}

double hard_sphere_phase_shift(int Z1, int Z2, double A1, double A2, int L, double E, double r)//See equation 10.2.7 in Thompson and Nunes
{
  double mu = mu_calc(A1, A2);
  double eta = 0.157489*(double)Z1*(double)Z2*sqrt(mu/E);
  double x = 0.218735*r*sqrt(mu*E);

  gsl_sf_result F_result, Fp_result, G_result, Gp_result;
  int K=0;
  double exp_F, exp_G;

  int status = gsl_sf_coulomb_wave_FG_e(eta, x, L, K, &F_result, &Fp_result, &G_result, &Gp_result, &exp_F, &exp_G);
  
  if(status!=0)printf("status = %s\n", gsl_strerror(status));
 
  double result = -atan((F_result.val/G_result.val)*exp(exp_F-exp_G));
  //cout << "Hard sphere phase shift: \t" << result*180.0/M_PI << endl;
  return result;
}

double gamma_function(double z[2])
{
  //  int gsl_sf_lngamma_complex_e (double zr, double zi, gsl_sf_result * lnr, gsl_sf_result * arg)
  gsl_sf_result lnr, arg;
  int status = gsl_sf_lngamma_complex_e(z[0], z[1], &lnr, &arg);
  if(status!=0)printf("status = %s\n", gsl_strerror(status));
  double result = 0;
  return result;
}

double Coulomb_phase_shift(int L, int Z1, int Z2, double A1, double A2, double E)//Equation 3.1.64 in Thompson and Nunes
{
  double result = 0;
  double mu = mu_calc(A1, A2);
  double eta = 0.157489*(double)Z1*(double)Z2*sqrt(mu/E);
  gsl_sf_result lnr, arg;
  complex<double> input(1+L,eta);
  
  int status = gsl_sf_lngamma_complex_e(input.real(),input.imag(), &lnr, &arg);
  if(status!=0)printf("status = %s\n", gsl_strerror(status));
  result = arg.val;
  //cout << "Coulomb phase shift:     \t" << result*180.0/M_PI << endl;
  return result;
}

double Clebsch_Gordon_coefficient(int ja, int ma, int jb, int mb, int L)
{
    double result = 0;
    result = pow(-1,-L+jb-ma)*sqrt(2*ja+1)*gsl_sf_coupling_3j(2*L, 2*jb, 2*ja, 2*(ma-mb), 2*mb, -2*ma);
    return result;
}

double factorial(int n)
{
  double result = gsl_sf_fact(n);
  return result;
}

complex<double> spherical_harmonic(double theta, double phi, int L, int m)
{
  //cout << "Spherical harmonic: \t" << theta << "\t" << phi << "\t" << L << "\t" << m << endl;
  complex<double> result;
  complex<double> i(0,1);
  if(m>=0)
  {
    complex<double> dummy (
      pow(-1,m) * sqrt((2*L+1)/4/M_PI * factorial(L - m)/factorial(L + m)) * gsl_sf_legendre_sphPlm(L, m, cos(theta)) * cos(phi),
			   pow(-1,m) * sqrt((2*L+1)/4/M_PI * factorial(L - m)/factorial(L + m)) * gsl_sf_legendre_sphPlm(L, m, cos(theta)) * sin(phi));
    result = dummy;
  }
  else if(m<0)
  {
    complex<double> dummy (
      pow(-1,m) * pow(-1,-m) * sqrt((2*L+1)/4/M_PI * factorial(L + m)/factorial(L - m)) * gsl_sf_legendre_sphPlm(L, -m, cos(theta)) * cos(phi),
			   pow(-1,m) * pow(-1,-m) * sqrt((2*L+1)/4/M_PI * factorial(L + m)/factorial(L - m)) * gsl_sf_legendre_sphPlm(L, -m, cos(theta)) * sin(phi));
  result = dummy;
  }
  //cout << "result : " << result << endl;
  return result;
}
