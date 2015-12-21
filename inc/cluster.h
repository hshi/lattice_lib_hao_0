#ifndef CLUSTER_H
#define CLUSTER_H

#include<complex>
#include<vector>
#include<string>

#ifdef MPI_HAO
#include <mpi.h>
#endif


//We do not have any member function for a general cluster.
//Only the lattice size L is used in this class.
class Cluster
{
 public:
    int     L; 

    Cluster();                     //Void Construction.
    Cluster(int Lc);               //Construct lattice from parameters.
    Cluster(std::string filename); //Construct lattice from reading file.
    Cluster(const Cluster& x);
    Cluster(Cluster&& x);
    ~Cluster();
   
    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);

    void read_param(std::string filename); // read L
};

#endif
