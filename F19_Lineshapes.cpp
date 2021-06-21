#include "function_library.h"
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>

double Ex = 10.137;//MeV
double Sp = 7.994;//MeV
double Sa = 4.014;//MeV

double gamma2proton = 0;//keV - reduced width for the p0 channel;
double gamma2alpha  = 0;//keV - reduced width for the a0 channel;

double AlphaWidth(double *x, double *pars)
{
    return 2. * gamma2alpha * penetrability(7, 2, 15, 4, 2, x[0] - Sa, 5.07);
}

double ProtonWidth(double *x, double *pars)
{
    return 2. * gamma2proton * penetrability(8, 1, 18, 1, 1, x[0] - Sp, 4.53);
}

double AlphaDelta(double *x, double *pars)
{
    return -gamma2alpha * (shift_factor(7, 2, 15, 4, 2, x[0] - Sa, 5.07) - shift_factor(7, 2, 15, 4, 2, Ex - Sa, 5.07));
}

double ProtonDelta(double *x, double *pars)
{
    return -gamma2proton * (shift_factor(8, 1, 18, 1, 1, x[0] - Sp, 4.53) - shift_factor(8, 1, 18, 1, 1, Ex - Sp, 4.53));
}

double AlphaLineShape(double *x, double *pars)
{
    return AlphaWidth(x,pars) / ( pow(x[0] - Ex - AlphaDelta(x, pars),2.) + 0.25 * pow(AlphaWidth(x, pars) + ProtonWidth(x, pars),2.));
}

double ProtonLineShape(double *x, double *pars)
{
    return ProtonWidth(x,pars) / ( pow(x[0] - Ex - ProtonDelta(x, pars),2.) + 0.25 * pow(AlphaWidth(x, pars) + ProtonWidth(x, pars),2.));
}

int main()
{
    gamma2alpha  = 0.25 * 4.3e-3 / penetrability(7, 2, 15, 4, 2, Ex - Sa, 5.07);
    cout << 2 * gamma2alpha * penetrability(7, 2, 15, 4, 2, Ex - Sa, 5.07) *1e3 << endl;
    gamma2proton = 0.25 * 4.33e-3 / penetrability(8, 1, 18, 1, 1, Ex - Sp, 4.53);
    
    
    TF1 *f_AlphaWidth = new TF1("f_AlphaWidth",AlphaWidth,Sa+0.1,11);
    cout << f_AlphaWidth->Eval(Ex)*1000 << endl;
    
    TF1 *f_ProtonWidth = new TF1("f_ProtonWidth",ProtonWidth,Sp+0.1,11);
    f_ProtonWidth->SetLineColor(3);
    
    TF1 *f_AlphaLineShape = new TF1("f_AlphaLineShape",AlphaLineShape,9.5,11);
    f_AlphaLineShape->SetNpx(1e4);
    
    TF1 *f_ProtonLineShape = new TF1("f_ProtonLineShape",ProtonLineShape,9.5,11);
    f_ProtonLineShape->SetNpx(1e4);
    f_ProtonLineShape->SetLineColor(3);
    
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    
    f_AlphaLineShape->Draw();
    c1->SetLogy();
    
    
    c1->SaveAs("F19_AlphaLineshape.C");
    c1->SaveAs("F19_AlphaLineshape.png");
    
    TFile *fout = new TFile("F19_Lineshape_Functions.root","RECREATE");
    f_AlphaWidth->Write();
    f_ProtonWidth->Write();
    f_AlphaLineShape->Write();
    f_ProtonLineShape->Write();
    fout->Close();
}