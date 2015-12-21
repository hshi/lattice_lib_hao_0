#include <iostream>
#include <fstream>
#include "cluster.h"

using namespace std;

void cluster_construct_test()
{
    size_t flag=0;

    Cluster c_p;
    if(c_p.L!=0) flag++;

    Cluster c_a(20);
    if(c_a.L!=20) flag++;
 
    Cluster c_b(c_a); 
    if(c_b.L!=c_a.L) flag++;

    Cluster c_c(move(c_b));
    if(c_c.L!=c_a.L) flag++;

    Cluster c_d; c_d=c_a;
    if(c_d.L!=c_a.L) flag++;

    Cluster c_e; c_e=move(c_d);
    if(c_e.L!=c_a.L) flag++;
 
    if(flag==0) cout<<"Cluster passed the construction test!\n";
    else cout<<"Warning!!!!Cluster failed the construction test!\n";
}


void cluster_read_construct_test()
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    string filename="latt_file.dat";
    int L=20;
    size_t flag=0;

    if(rank==0)
    {
        ofstream file;
        file.open(filename, ios::out|ios::trunc);
        file<<L<<"\n";
        file.close();
    }

    Cluster latt(filename);

    if(rank==0) remove( filename.c_str() );

    if(latt.L!=L) flag++;

    if(flag!=0) cout<<"Warning!!!!Cluster failed the read lattice test!\n";
    if(rank==0) cout<<"If there is no waring, Cluster passed the read lattice test!\n";
}


void cluster_test()
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    //Serial test
    if(rank==0)
    {
        cluster_construct_test();
    }

    //Might involve mpi test
    cluster_read_construct_test();

    if(rank==0) cout<<"\n";
}
