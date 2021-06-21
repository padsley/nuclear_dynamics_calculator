#include "function_library.h"
#include <TCanvas.h>

int main()
{
  
  TGraph *g = new TGraph();

  int counter = 0;
  
  for(double Ex=8.6;Ex<12;Ex+=0.1)
    {
      double alpha_WL = Wigner_width(16.,2.,32.,4.,2,Ex - 6.641,5.95);

      double proton_WL = Wigner_width(17.,1.,35.,1.,0,Ex-8.507,5.34);

      g->SetPoint(counter,Ex,proton_WL/alpha_WL);
      
      counter++;
    }

  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->Draw();
  c1->SetLogy();

  g->Draw("ALP");
  g->SetName("WLRatio");
  g->SaveAs("outputGraph.root");
}
