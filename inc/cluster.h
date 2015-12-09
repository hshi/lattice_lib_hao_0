#ifndef CLUSTER_H
#define CLUSTER_H

#include<complex>
#include<vector>
#include<string>

//We do not have any member function for a general cluster.
//Only the lattice size L is used in this class.
class Cluster
{
 public:
    int     L; 

    Cluster(); 
    Cluster(int Lc); 
    Cluster(const Cluster& x);
    Cluster(Cluster&& x);
    ~Cluster();
   
    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);
};


void read_lattice(Cluster& latt, std::string filename);

#ifdef MPI_HAO
#include <mpi.h>
void MPIBcast(Cluster& latt, int root=0,  const MPI_Comm& comm=MPI_COMM_WORLD);
#endif


#endif
