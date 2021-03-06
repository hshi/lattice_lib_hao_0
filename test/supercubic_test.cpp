#include <iostream>
#include <fstream>
#include "supercubic.h"

using namespace std;

void supercubic_construct_test()
{
    int dimen=3;
    int n[3]={3,5,6};
    size_t flag=0;

    //Void constructor 
    Supercubic point;
    if(point.dimen!=0) flag++;
    if(point.L!=0) flag++;
   
    //Parameter constructor
    Supercubic cubic(dimen, n);
    if(cubic.dimen!=dimen)  flag++;
    for(int i=0; i<dimen;i++) {if(cubic.n[i]!=n[i]) flag++;}
    if(cubic.L!=90) flag++;

    //Copy constructor
    Supercubic cubic_a(cubic);
    if(cubic_a.dimen!=cubic.dimen) flag++;
    if(cubic_a.L!=cubic.L) flag++;
    for(int i=0; i<dimen;i++) {if(cubic_a.n[i]!=cubic.n[i]) flag++;}

    //Move constructor
    Supercubic cubic_b( move(cubic) );
    if(cubic_a.dimen!=cubic_b.dimen) flag++;
    if(cubic_a.L!=cubic_b.L) flag++;
    for(int i=0; i<dimen;i++) {if(cubic_a.n[i]!=cubic_b.n[i]) flag++;}


    if(flag==0) cout<<"PASSED! Supercubic passed the construction test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the construction test!"<<endl;
}

void supercubic_equal_test()
{
    int dimen=3;
    int n[3]={3,5,6};
    size_t flag=0;
    Supercubic cubic_a,cubic_b; 
    Supercubic cubic(dimen, n);
   
    //Supercubic cubic_a=cubic; 
    cubic_a=cubic; 
    if(cubic_a.dimen!=cubic.dimen) flag++;
    if(cubic_a.L!=cubic.L) flag++;
    for(int i=0; i<dimen;i++) {if(cubic_a.n[i]!=cubic.n[i]) flag++;}
   
    //Supercubic cubic_b=std::move(cubic); 
    cubic_b=std::move(cubic); 
    if(cubic_a.dimen!=cubic_b.dimen) flag++;
    if(cubic_a.L!=cubic_b.L) flag++;
    for(int i=0; i<dimen;i++) {if(cubic_a.n[i]!=cubic_b.n[i]) flag++;}
 
    if(flag==0) cout<<"PASSED! Supercubic passed the equal test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the equal test!"<<endl;
}

void supercubic_coor_test()
{
    int dimen=3;
    int n[3]={3,5,6};
    Supercubic cubic(dimen, n); 
    int ix,iy,iz;
   
    ix=0;iy=0;iz=0; 
    vector<int> coor;
    size_t flag=0;
    for(int latt=0; latt<cubic.L; latt++)
    {
        coor=cubic.coor(latt);
        if(coor[0]!=ix) flag++;
        if(coor[1]!=iy) flag++;
        if(coor[2]!=iz) flag++;
        ix++;
        if(ix==3) {ix=0;iy++;}
        if(iy==5) {iy=0;iz++;}
        //cout<<coor[0]<<" "<<coor[1]<<" "<<coor[2]<<"\n";
    }
    if(flag==0) cout<<"PASSED! Supercubic passed the coor test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the coor test!"<<endl;
}

void supercubic_index_test()
{
    int dimen=3;
    int n[3]={3,5,6};
    Supercubic cubic(dimen,n);
    vector<int> coor;
    size_t flag=0;
    for(int latt=0; latt<cubic.L; latt++)
    {
        coor=cubic.coor(latt);
        if(cubic.index(coor)!=latt) flag++;
    }
    if(flag==0) cout<<"PASSED! Supercubic passed the index test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the index test!"<<endl;
}

void supercubic_bound_test()
{
    int dimen=3;
    int n[3]={3,5,6};
    Supercubic cubic(dimen,n);
    size_t flag=0;
    if(cubic.bound(-5,7)!=2) flag++;
    if(cubic.bound(-7,7)!=0) flag++;
    if(cubic.bound(-10,7)!=4) flag++;
    if(cubic.bound(-14,7)!=0) flag++;
    if(cubic.bound(-22,7)!=6) flag++;
    if(cubic.bound(5,7)!=5) flag++;
    if(cubic.bound(7,7)!=0) flag++;
    if(cubic.bound(10,7)!=3) flag++;
    if(cubic.bound(14,7)!=0) flag++;
    if(cubic.bound(22,7)!=1) flag++;
    if(flag==0) cout<<"PASSED! Supercubic passed the bound test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the bound test!"<<endl;
    //cout<<flag<<endl;
}

void supercubic_coor_relat_test()
{
    int dimen=2;
    int n[2]={3,4};
    Supercubic square(dimen,n);
    vector<int> coor_i(2),coor_j(2),dist(2),dist_exact(2);
    size_t flag=0;
   
    coor_i={1,2};coor_j={2,3};dist_exact={1,1};
    dist=square.coor_relat(coor_i,coor_j);
    for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}
   
    coor_i={2,3};coor_j={1,2};dist_exact={2,3};
    dist=square.coor_relat(coor_i,coor_j);
    for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}
   
    coor_i={1,2};coor_j={2,0};dist_exact={1,2};
    dist=square.coor_relat(coor_i,coor_j);
    for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}
   
    if(flag==0) cout<<"PASSED! Supercubic passed the coor_relat test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the coor_relat test!"<<endl;
   
    //cout<<flag<<endl;
}


void supercubic_inverse_test()
{
    int dimen=2;
    int n[2]={3,4};
    Supercubic square(dimen,n);
    size_t flag=0;
    if(square.inverse(0)!=0)  flag++;
    if(square.inverse(1)!=2)  flag++;
    if(square.inverse(2)!=1)  flag++;
    if(square.inverse(3)!=9)  flag++;
    if(square.inverse(4)!=11) flag++;
    if(square.inverse(5)!=10) flag++;
    if(square.inverse(6)!=6)  flag++;
    if(square.inverse(7)!=8)  flag++;
    if(square.inverse(8)!=7)  flag++;
    if(square.inverse(9)!=3)  flag++;
    if(square.inverse(10)!=5)  flag++;
    if(square.inverse(11)!=4)  flag++;
   
    if(flag==0) cout<<"PASSED! Supercubic passed the inverse test!"<<endl;
    else cout<<"Warning!!!!Supercubic failed the inverse test!"<<endl;
}

void supercubic_read_construct_test()
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    string filename="latt_file.dat";
    int dimen=3;
    int n[3]={3,5,6};
    size_t flag=0;

    if(rank==0)
    {
        ofstream file;
        file.open(filename, ios::out|ios::trunc);
        file<<dimen<<"\n";
        for(int i=0; i<dimen;i++) {file<<n[i]<<" ";} file<<"\n";
        file.close();
    }

    Supercubic cubic(filename);

    if(rank==0) remove( filename.c_str() );

    if(cubic.dimen!=dimen) flag++;
    if(cubic.L!=90) flag++;
    for(int i=0; i<dimen;i++) {if(cubic.n[i]!=n[i]) flag++;}

    if(flag!=0) cout<<"Warning!!!!Supercubic failed the read lattice test!"<<endl;
    if(rank==0) cout<<"PASSED! If there is no waring, Supercubic passed the read lattice test!"<<endl;
}


void supercubic_test()
{
    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    //Serial test
    if(rank==0)
    {
        supercubic_construct_test();
        supercubic_equal_test();
        supercubic_coor_test();
        supercubic_index_test();
        supercubic_bound_test();
        supercubic_coor_relat_test();
        supercubic_inverse_test();
    }

    //Might involve mpi test
    supercubic_read_construct_test();

    if(rank==0) cout<<" "<<endl;
}
