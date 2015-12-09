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


void read_cluster_test()
{
    string filename="latt_file.dat";
    int L=20;
    size_t flag=0;

    ofstream file;
    file.open(filename, ios::out|ios::trunc);
    file<<L<<"\n";
    file.close();

    Cluster cubic; read_lattice(cubic,filename);
    if(cubic.L!=L) flag++;

    remove( filename.c_str() );

    if(flag==0) cout<<"Cluster passed the read lattice test!\n";
    else cout<<"Warning!!!!Cluster failed the read lattice test!\n";

}


#ifdef MPI_HAO
//Do not call this test in test_all.cpp
void MPIBcast_cluster_test()
{
    int L=20;
    int rank=0; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Cluster cubic;
    if(rank==0) cubic=Cluster(L);
    MPIBcast(cubic);
    cout<<cubic.L<<" "<<rank<<endl;
}
#endif


void cluster_test()
{
    cluster_construct_test();
    read_cluster_test();
}
