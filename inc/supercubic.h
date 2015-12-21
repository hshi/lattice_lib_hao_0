#ifndef SUPERCUBIC_H
#define SUPERCUBIC_H

#include<complex>
#include<vector>
#include<string>

#ifdef MPI_HAO
#include <mpi.h>
#endif

class Supercubic
{
 public:
    int     dimen;
    int     *n;
    int     L;
   
    Supercubic();                       //Void Construction.
    Supercubic(int Dc, const int* Nc);  //Construct lattice from parameters.
    Supercubic(std::string filename);   //Construct lattice from reading file.
    Supercubic(const Supercubic& x);
    Supercubic(Supercubic&& x);
    ~Supercubic();
   
    Supercubic& operator  = (const Supercubic& x);
    Supercubic& operator  = (Supercubic&& x);
   
    std::vector<int> coor(int lattice_index) const;
    int index(const std::vector<int>& lattice_coor) const;
    int bound(const int i, const int i_max) const; 
    std::vector<int> coor_relat(const std::vector<int>& coor_i, const std::vector<int>& coor_j) const; // return coor_j-coor_i
    int inverse(int lattice_index) const; //return the inverse point of lattice_index with zero point

    void read_param(std::string filename); // read dimen and *n, allocate n 
};

#endif
