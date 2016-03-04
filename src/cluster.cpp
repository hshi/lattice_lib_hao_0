#include <iostream>
#include <fstream>
#include <stdexcept>
#include <math.h>
#include "cluster.h"

using namespace std;

Cluster::Cluster():L(0){}

Cluster::Cluster(int Lc):L(Lc){}

Cluster::Cluster(string filename) 
{
    read_param(filename);
}

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
//Read L
void Cluster::read_param(string filename)
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    if(rank==0)
    {
       ifstream latt_file;
       latt_file.open(filename,ios::in);
       if ( ! latt_file.is_open() ) {cout << "Error opening file!!!"; exit(1);}
       latt_file>>L;
       latt_file.close();
    }

#ifdef MPI_HAO
    MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
#endif
}

