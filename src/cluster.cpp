#include <iostream>
#include <fstream>
#include <stdexcept>
#include <math.h>
#include "cluster.h"

using namespace std;

Cluster::Cluster():L(0){}

Cluster::Cluster(int Lc):L(Lc){}

Cluster::Cluster(const Cluster& x) 
{
    L=x.L;
}

Cluster::Cluster(Cluster&& x) 
{
    L=x.L; 
}

Cluster::~Cluster() {}

Cluster& Cluster::operator  = (const Cluster& x) 
{
    L=x.L;
    return *this;
}

Cluster& Cluster::operator  = (Cluster&& x)
{
    L=x.L;
    return *this;
}

//Read the parameters from "filename"
//Create cluster class and return it.
Cluster read_cluster(string filename)
{
    int     L;
    ifstream latt_file;

    latt_file.open(filename);
    latt_file>>L;
    latt_file.close();

    Cluster latt(L);

    return latt;
}

#ifdef MPI_HAO
//Bcast a cluster latt
void MPIBcast(Cluster& latt, int root,  const MPI_Comm& comm)
{
    MPI_Bcast(&latt.L, 1, MPI_INT, root, comm);
}
#endif

