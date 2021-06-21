#include "function_library.h"

int main()
{
    int Z1 = 68;
    int Z2 = 2;
    int A1 = 156;
    int A2 = 4;
    
    double L = 1;
    
    double Q = 3.4826;
    
    double T9 = 3;
    
    double r = 1.4*(pow(4.,1./3.) + pow(156.,1./3.));
    
    TGraph *g = new TGraph();
    g->SetName("EffLifetime");
    
    double kT = TMath::K()/TMath::Qe()*T9*1e9/1e6;//Boltzman constant in eV/K * T9 - gives result in eV so divide by 1e6
    cout << "kT: " << kT << " MeV" << endl;
    
    int counter=0;
    
    for(double E=1;E<10.0727;E+=0.1)
    {
        double Gamma =  Wigner_width(Z1, Z2, A1, A2, L, E+Q, r)*1e6*1e-2; //Result in eV - 1% SF
        
        double tauState = TMath::Hbar()/TMath::Qe()/Gamma;
        
        g->SetPoint(counter,E,tauState*(exp(E/kT)-1));
        counter++;
//         cout << "Point: " << counter << endl;
    }
    TFile *output = new TFile("output.root","RECREATE");
    g->Write();
    output->Close();
    
    
    return 0;
}