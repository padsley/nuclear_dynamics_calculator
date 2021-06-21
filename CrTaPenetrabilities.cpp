#include "function_library.h"
#include <TGraph.h>
#include <TMultiGraph.h>

void CrTaPenetrabilities()
{
  double Emin = 1;
  double Emax = 6;

  int counter = 0;

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogy();
  
  TGraph *gCr = new TGraph();
  gCr->SetName("gCr");

  TGraph *gCr1 = new TGraph();
  gCr1->SetName("gCr1");

  TGraph *gCr2 = new TGraph();
  gCr2->SetName("gCr2");

  TGraph *gTa = new TGraph();
  gTa->SetName("gTa");
  
  for(double Ecm = Emin;Ecm<=Emax;Ecm+=(Emax-Emin)/100)
    {
      gCr->SetPoint(counter,Ecm,penetrability(1,24,1,50,0,Ecm,1.25*(pow(50.,1./3.))));
      gCr1->SetPoint(counter,Ecm,penetrability(1,24,1,50,1,Ecm,1.25*(pow(50.,1./3.))));
      gCr2->SetPoint(counter,Ecm,penetrability(1,24,1,50,2,Ecm,1.25*(pow(50.,1./3.))));
      gTa->SetPoint(counter,Ecm,penetrability(1,73,1,180,0,Ecm,1.25*(pow(180.,1./3.))));
      counter++;
    }

  TMultiGraph *mg = new TMultiGraph();
  gCr->Draw("AL");
  gTa->SetLineColor(2);
  gCr1->SetLineColor(3);
  gCr2->SetLineColor(4);
  mg->Add(gCr);
  mg->Add(gCr1);
  mg->Add(gCr2);
  mg->Add(gTa);
  mg->Draw("AL");
}
