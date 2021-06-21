#include "function_library.h"
#include <TGraph.h>
#include <TMultiGraph.h>

void MgAlphaWignerLimits()
{
  double Emin = 1;
  double Emax = 6;

  int counter = 0;

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogy();
  
  TGraph *gWL = new TGraph();
  gWL->SetName("gWL");

  
  for(double Ecm = Emin;Ecm<=Emax;Ecm+=(Emax-Emin)/100)
    {
      gWL->SetPoint(counter,Ecm,1000*1000*Wigner_width(2,12,4,24,0,Ecm,1.25*(pow(24.,1./3.)+pow(4.,1./3.))));
		    //penetrability(1,24,1,50,0,Ecm,1.25*(pow(50.,1./3.))));
      counter++;
    }

  gWL->Draw("AL");
  gWL->GetXaxis()->SetTitle("E_{cm} [MeV]");
  gWL->GetXaxis()->CenterTitle();
  gWL->GetYaxis()->SetTitle("#Gamma_{WL} [eV]");
  gWL->GetYaxis()->CenterTitle();
  
  c1->Update();
  c1->SaveAs("MgAlphaWignerLimit.png");
}
