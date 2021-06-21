#include "function_library.h"
#include <TGraph.h>
#include <TCanvas.h>

int main()
{
//     double shift_factor(int Z1, int Z2, int A1, int A2, int L, double E, double r)
    
    TCanvas *c1 = new TCanvas("c1","c1",800,800);
    
    TGraph *gShift = new TGraph();
    
    for(double E=0.001;E<=2.000;E+=0.001)
    {
        gShift->SetPoint(gShift->GetN(),E,shift_factor(6,1,12,1,0,E,4.1));
    }
    
    gShift->Draw("AL");
    
    c1->SetLogx();
    c1->SaveAs("ShiftFunctionTest.png");
}
