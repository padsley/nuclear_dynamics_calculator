#include "function_library.h"

//Written by padsley@gmail.com E-mail if you have questions/comments/corrections. You should check the numbers coming out of here. No guarantee is provided that they're right.



int main()
{
  //Ask the user to provide the relevant values
  
  cout << "Penetrability calculator. Keep an eye out for any warning messages and remember to check the results for sanity." << endl;

  int Z1=0, Z2=0, A1=1, A2=1;

  cout << "Enter target charge: " << endl;
  cin >> Z1;

  cout << "Enter projectile charge: "<< endl;
  cin >> Z2;

  cout << "Enter target mass number: " << endl;
  cin >> A1;

  cout << "Enter projectile mass number: " << endl;
  cin >> A2; 

  double L = 0;

  cout << "Enter the orbital angular momentum value: " << endl;
  cin >> L;

  double E = 0;
  double SeparationEnergy = 0;
  double EnergyStep = 0;

  cout << "Enter maximum energy in MeV - easiest to set this to be the max energy that you want and separation energy (next step) to 0: ";
  cin >> E;

  cout << "Enter separation energy in MeV: ";
  cin >> SeparationEnergy;

  cout << "Enter energy step in MeV: ";
  cin >> EnergyStep;

  double r = 5;
  cout << "Enter the channel radius in fm: ";
  cin >> r;

  TGraph *g = new TGraph();
  g->SetName("NeutronPenetrability");
  int counter = 0;

  
  double Energy = SeparationEnergy+EnergyStep;
  while(Energy<E)
    {
      double Gamma = Wigner_width(Z1, Z2, A1, A2, L, Energy-SeparationEnergy, r);
      cout << "Energy: " << Energy - SeparationEnergy << "\t Wigner limit: " << Gamma*1000 << " keV" << endl;

      g->SetPoint(counter,Energy,Gamma);
      counter++;
      Energy += EnergyStep;
    }

  TFile *fout = new TFile("WignerLimitGraph.root","RECREATE");
  g->Write();
  fout->Close();
}
