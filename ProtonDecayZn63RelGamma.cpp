#include "function_library.h"
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>

void ProtonDecayZn63RelGamma()
{
  double Emin = 0.1;//MeV
  double Emax = 6;

  int counter = 0;

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogy();
  
  TGraph *gProtonWidthRatio = new TGraph();
  gProtonWidthRatio->SetName("gCr");
  
  for(double Ecm = Emin;Ecm<=Emax;Ecm+=(Emax-Emin)/100)
    {
      gProtonWidthRatio->SetPoint(counter,Ecm,0.01*1.e6*Wigner_width(1,30,1,63,0,Ecm,1.25*(pow(63.,1./3.)+1))/3.);//assume that the normal gamma-ray width 3 eV
      counter++;
    }

  //TMultiGraph *mg = new TMultiGraph();
  gProtonWidthRatio->Draw("AL");
 
  //mg->Add(gProtonWidthRatio);
  //mg->Draw("AL");
}
