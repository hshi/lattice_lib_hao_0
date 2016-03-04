#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <math.h>
#include "supercubic.h"

using namespace std;

Supercubic::Supercubic():dimen(0),n(nullptr),L(0) {}

Supercubic::Supercubic(int Dc, const int* Nc)
{
    dimen=Dc;
    n=new int[dimen]; std::copy(Nc,Nc+dimen,n);
    L=1; for(int i=0; i<dimen; i++) L*=n[i];
}

Supercubic::Supercubic(string filename)
{
    n=nullptr;  //We first initial n, since read_param function assume n is either nullptr or allocated.
    read_param(filename); //read dimen and *n, allocate n
    L=1; for(int i=0; i<dimen; i++) L*=n[i];
}



Supercubic::Supercubic(const Supercubic& x) 
{
    dimen=x.dimen;L=x.L;
    n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
}

Supercubic::Supercubic(Supercubic&& x) 
{
    dimen=x.dimen;L=x.L;
    n=x.n; x.n=nullptr;
}

Supercubic::~Supercubic() {if(n) delete[] n;}

Supercubic& Supercubic::operator  = (const Supercubic& x) 
{
    dimen=x.dimen;L=x.L;
    if(n) delete[] n; n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
    return *this;
}

Supercubic& Supercubic::operator  = (Supercubic&& x)
{
    dimen=x.dimen;L=x.L;
    int* ntmp=n; n=x.n; x.n=ntmp; //swap
    return *this;
}

vector<int> Supercubic::coor(int lattice_index) const
{
    vector<int> coordinate(dimen); int den=L;
    for(int i=dimen-1; i>=0; i--)
    {
        den/=n[i];
        coordinate[i]=lattice_index/den;
        lattice_index%=den;
    }
    return coordinate;
}

int Supercubic::index(const vector<int>& lattice_coor) const
{
    int size=lattice_coor.size();
    if(size!=dimen) 
    {
        std::cout<<"Input for index in Supercubic error! Size of lattice_coor !=dimen \n"; 
        exit(1);
    }
   
    int lattice_index=0; int den=1;
    for(int i=0; i<dimen; i++)
    {
        lattice_index+=(lattice_coor[i]*den);
        den*=n[i];
    }
    return lattice_index;
}


int Supercubic::bound(const int i, const int i_max) const
{
    int i_bound = (i>=0) ? i%i_max : i%i_max+i_max;
    if(i_bound==i_max) i_bound=0;
    return i_bound;
}


//return coor_j-coor_i
vector<int> Supercubic::coor_relat(const vector<int>& coor_i, const vector<int>& coor_j) const
{
    int size_i=coor_i.size(); int size_j=coor_j.size();
    if(size_i!=dimen||size_j!=dimen)
    {
        std::cout<<"Input for coor_relat in Supercubic error! Size of coor_i or coor_j !=dimen \n";
        exit(1);
    }
   
    vector<int> dist(dimen);
    for(int i=0; i<dimen; i++) dist[i]=this->bound(coor_j[i]-coor_i[i], n[i]);
    return dist;
}


//return the inverse point of lattice_index with zero point
int Supercubic::inverse(int lattice_index) const
{
    vector<int> coordinate=this->coor(lattice_index);
    for(int i=0; i<dimen; i++) coordinate[i]=this->bound(-coordinate[i],n[i]);
    return this->index(coordinate); 
}


//Read the parameters from "filename"
//Read dimen and *n, allocate n
void Supercubic::read_param(string filename)
{
    int rank=0; 
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    if(rank==0)
    {
       ifstream latt_file;
       latt_file.open(filename, ios::in);
       if ( ! latt_file.is_open() ) {cout << "Error opening file!!!"; exit(1);}
       latt_file>>dimen; latt_file.ignore(numeric_limits<streamsize>::max(),'\n');
       if(n) delete[] n; n=new int[dimen];
       for(int i=0; i<dimen; i++) {latt_file>>n[i];} latt_file.ignore(numeric_limits<streamsize>::max(),'\n');
       latt_file.close();
    }

#ifdef MPI_HAO
    MPI_Bcast(&dimen, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank!=0) { if(n) delete[] n; n=new int[dimen]; }
    MPI_Bcast(n, dimen, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
#endif
}
