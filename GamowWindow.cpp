#include "function_library.h"
#include <TF1.h>
#include <TCanvas.h>

double GWFunction(double *x, double *pars)
{
    double result = 0;
    
    //double penetrability(int Z1, int Z2, double A1, double A2, int L, double E, double r)//See equation 2.162 in Iliadis, for example
    
    result = penetrability(6.,6.,12.,12.,0.,x[0],7.2) * x[0] * exp(-x[0]*1.e6/(TMath::K()/TMath::Qe()*pars[0]*1.e9));
    
    return result;
}

double MBFunction(double *x, double *pars)
{
  return pars[1] * x[0] * exp(-x[0]*1.e6/(TMath::K()/TMath::Qe()*pars[0]*1.e9));
}

double CrossSectionFunction(double *x, double *pars)
{
  return pars[0]*penetrability(6.,6.,12.,12.,0.,x[0],7.2);
}

void GamowWindow(double T9 = 0.5)
{
    TF1 *fGW = new TF1("fGW",&GWFunction,0.01,10,1);
    fGW->SetNpx(1.e6);
    
    fGW->SetParameter(0,T9);

    TF1 *fMB = new TF1("fMB",&MBFunction,0.01,10,2);
    fMB->SetNpx(1.e6);
    fMB->SetParameter(0,T9);
    fMB->SetParameter(1,1.e-28);

    TF1 *fP = new TF1("fP",&CrossSectionFunction,0.01,10,1);
    fP->SetNpx(1.e6);
    fP->SetParameter(0,1.e-28);

    TCanvas *c1 = new TCanvas("c1","c1",800,800);
    c1->SetLogy();
//     cout << TMath::K()/TMath::Qe()*1.e9/1.e3 << endl;
    
    fGW->Draw();
    fMB->SetLineColor(1);
    fMB->Draw("same");
    fP->SetLineColor(3);
    fP->Draw("same");
    
    double xmax = fGW->GetMaximumX();
    double ymax = fGW->Eval(xmax);
    cout << "xmax = " << xmax << endl;
    cout << "ymax = " << ymax << endl;
    cout << "ymax check = " << fGW->GetMaximum() << endl;
    
    cout << "lower GW edge: " << fGW->GetX(0.5*ymax,0.1,xmax) << endl;
    cout << "upper GW edge: " << fGW->GetX(0.5*ymax,xmax,10.) << endl;

    fGW->GetYaxis()->SetRangeUser(1.e-60,1.e-25);
}
