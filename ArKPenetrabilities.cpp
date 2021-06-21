#include "function_library.h"
#include <TGraph.h>
#include <TMultiGraph.h>

void ArKPenetrabilities()
{
  double Emin = 0.1;
  double Emax = 1;

  int counter = 0;

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetLogy();
  
  TGraph *gAr = new TGraph();
  gAr->SetName("gAr");

  TGraph *gAr1 = new TGraph();
  gAr1->SetName("gAr1");

  TGraph *gAr2 = new TGraph();
  gAr2->SetName("gAr2");

  TGraph *gK = new TGraph();
  gK->SetName("gK");
  
  TGraph *gK1 = new TGraph();
  gK1->SetName("gK1");
  
  TGraph *gK2 = new TGraph();
  gK2->SetName("gK2");
  
  for(double Ecm = Emin;Ecm<=Emax;Ecm+=(Emax-Emin)/100)
    {
      gAr->SetPoint(counter,Ecm,penetrability(1,18,1,37,0,Ecm,1.25*(pow(50.,1./3.))));
      gAr1->SetPoint(counter,Ecm,penetrability(1,18,1,37,1,Ecm,1.25*(pow(50.,1./3.))));
      gAr2->SetPoint(counter,Ecm,penetrability(1,18,1,37,2,Ecm,1.25*(pow(50.,1./3.))));
      gK->SetPoint(counter,Ecm,penetrability(1,19,1,39,0,Ecm,1.25*(pow(180.,1./3.))));
      gK1->SetPoint(counter,Ecm,penetrability(1,19,1,39,1,Ecm,1.25*(pow(180.,1./3.))));
      gK2->SetPoint(counter,Ecm,penetrability(1,19,1,39,2,Ecm,1.25*(pow(180.,1./3.))));
      counter++;
    }

  TMultiGraph *mg = new TMultiGraph();
  gAr->Draw("AL");
  gK->SetLineColor(2);
  gK1->SetLineColor(5);
  gK2->SetLineColor(6);
  gAr1->SetLineColor(3);
  gAr2->SetLineColor(4);
  mg->Add(gAr);
  mg->Add(gAr1);
  mg->Add(gAr2);
  mg->Add(gK);
  mg->Add(gK1);
  mg->Add(gK2);
  mg->Draw("AL");
  
  TGraph *gLValueDependence = new TGraph();
  gLValueDependence->SetName("gLValueDependence");
  
  gLValueDependence->SetPoint(0,0,penetrability(1,18,1,37,0,0.3,1.25*(pow(50.,1./3.))));
  gLValueDependence->SetPoint(1,1,penetrability(1,18,1,37,1,0.3,1.25*(pow(50.,1./3.))));
  gLValueDependence->SetPoint(2,2,penetrability(1,18,1,37,2,0.3,1.25*(pow(50.,1./3.))));
  gLValueDependence->SetPoint(3,3,penetrability(1,18,1,37,3,0.3,1.25*(pow(50.,1./3.))));
  gLValueDependence->SetPoint(4,4,penetrability(1,18,1,37,4,0.3,1.25*(pow(50.,1./3.))));
  gLValueDependence->SetPoint(5,5,penetrability(1,18,1,37,5,0.3,1.25*(pow(50.,1./3.))));
  
//   gLValueDependence->Draw("AL");
}
