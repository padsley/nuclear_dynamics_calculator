#include "function_library.h"

//Written by padsley@gmail.com E-mail if you have questions/comments/corrections. You should check the numbers coming out of here. No guarantee is provided that they're right.

//to compile - this works on my Ubuntu system: g++ penetrability.cpp -o penetrability `root-config --cflags --libs` -lgsl -lgslcblas

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

  cout << "Enter projectile energy in MeV - I'm almost positive that this is the centre-of-mass value...: ";
  cin >> E;

  double r = 5;
  cout << "Enter the channel radius in fm: ";
  cin >> r;
  
  double P = penetrability(Z1, Z2, A1, A2, L, E, r);
  cout << "Penetrability: " << P << endl;

  double Gamma = Wigner_width(Z1, Z2, A1, A2, L, E, r);
  cout << "Wigner limit: " << Gamma*1000*1000 << " eV" << endl;

  double shift = shift_factor(Z1, Z2, A1, A2, L, E, r);
  cout << "Phase shift: " << shift << endl;
}
