#ifndef SUPERCUBIC
#define SUPERCUBIC

#include<complex>
#include<vector>

class Supercubic
{
 public:
 int     dimen;
 int     *n;
 int     L;

 int     Nhop;
 std::vector<std::complex<double>> hop;
 std::vector<int>  siti,sitj;
 std::vector<double> dispersion,dispersion_inv; //dispersion_inv is the inverse k point

 Supercubic(); 
 Supercubic(int Dc, const int* Nc);
 Supercubic(const Supercubic& x);
 Supercubic(Supercubic&& x);
 ~Supercubic();

 Supercubic& operator  = (const Supercubic& x);
 Supercubic& operator  = (Supercubic&& x);

 //Real space function
 std::vector<int> coor(int lattice_index) const;
 int index(const std::vector<int>& lattice_coor) const;
 int bound(const int i, const int i_max) const; 
 std::vector<int> distance(const std::vector<int>& coor_i, const std::vector<int>& coor_j) const; // return coor_j-coor_i
 int inverse(int lattice_index) const; //return the inverse point of lattice_index with zero point


 void set_nn_hop(double t_nn_sc, const double* ktwist);
 void set_dispersion(double t_nn_sc, const double* ktwist); //correspond to nn_hop
 void set_dispersion(const double* ktwist); //correspond to k^2_hop
};

#endif
