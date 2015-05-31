#ifndef RASHBA2D_H
#define RASHBA2D_H

#include "supercubic.h"

//Rashba2d inherited from supercubic
//redefine the set_dispersion function, dispersion_inv is disabled.
//coor, index, bound, distance, inverse can still be used.
//set_nn_hop is not changed.

class Rashba2d:public Supercubic
{
 public:

    std::vector<std::complex<double>> uk,vk; //store the information about diagonal 2x2 matrix

    Rashba2d(); 
    Rashba2d(int Dc, const int* Nc);
    Rashba2d(const Rashba2d& x);
    Rashba2d(Rashba2d&& x);
    ~Rashba2d();
   
    Rashba2d& operator  = (const Rashba2d& x);
    Rashba2d& operator  = (Rashba2d&& x);

    void set_dispersion(double t_nn_sc, double lambda); //correspond to lattice
    void set_dispersion(double lambda); //correspond to continuous
};

#endif
