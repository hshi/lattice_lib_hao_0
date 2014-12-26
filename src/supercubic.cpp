#include <iostream>
#include <stdexcept>
#include <math.h>
#include "supercubic.h"

using std::vector;
using std::complex;
#define PI 3.14159265358979324

Supercubic::Supercubic():dimen(0),n(nullptr),L(0),Nhop(0){}

Supercubic::Supercubic(int Dc, const int* Nc)
{
 dimen=Dc;
 n=new int[dimen]; std::copy(Nc,Nc+dimen,n);
 L=1; for(int i=0; i<dimen; i++) L*=n[i];
 Nhop=0;
}

Supercubic::Supercubic(const Supercubic& x) 
{
 dimen=x.dimen;L=x.L;Nhop=x.Nhop;
 n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
 hop=x.hop; siti=x.siti; sitj=x.sitj; dispersion=x.dispersion;
}

Supercubic::Supercubic(Supercubic&& x) 
{
 dimen=x.dimen;L=x.L;Nhop=x.Nhop;
 n=x.n; x.n=nullptr;
 hop=std::move(x.hop); siti=std::move(x.siti); sitj=std::move(x.sitj); dispersion=std::move(x.dispersion);
}

Supercubic::~Supercubic() {if(n) delete[] n;}

Supercubic& Supercubic::operator  = (const Supercubic& x) 
{
 dimen=x.dimen;L=x.L;Nhop=x.Nhop;
 if(n) delete[] n; n=new int[dimen]; std::copy(x.n,x.n+dimen,n);
 hop=x.hop; siti=x.siti; sitj=x.sitj; dispersion=x.dispersion;
 return *this;
}

Supercubic& Supercubic::operator  = (Supercubic&& x)
{
 dimen=x.dimen;L=x.L;Nhop=x.Nhop;
 n=x.n; x.n=nullptr;
 hop=std::move(x.hop); siti=std::move(x.siti); sitj=std::move(x.sitj); dispersion=std::move(x.dispersion);
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
  throw std::runtime_error(" ");
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
vector<int> Supercubic::distance(const vector<int>& coor_i, const vector<int>& coor_j) const
{
 int size_i=coor_i.size(); int size_j=coor_j.size();
 if(size_i!=dimen||size_j!=dimen)
 {
  std::cout<<"Input for distance in Supercubic error! Size of coor_i or coor_j !=dimen \n";
  throw std::runtime_error(" ");
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


void Supercubic::set_nn_hop(double t_nn_sc, const double* ktwist)
{
 Nhop=2*L*dimen;

 vector<int> coor_i,coor_j; complex<double> xi(0.0,1.0);

 for(int latt_index=0; latt_index<L; latt_index++)
 {
  coor_i=this->coor(latt_index);
  for(int dim_index=0; dim_index<dimen; dim_index++)
  {
   for(int direct=-1; direct<=1; direct+=2)
   {
    coor_j=coor_i; 
    coor_j[dim_index]=this->bound(coor_j[dim_index]+direct,n[dim_index]);
    siti.push_back(latt_index);sitj.push_back(this->index(coor_j));
    hop.push_back( t_nn_sc*exp(ktwist[dim_index]*direct*xi*2.0*PI/(n[dim_index]*1.0)) );
   } 
  } 
 }
 
}


void Supercubic::set_dispersion(double t_nn_sc, const double* ktwist)
{
 vector<int> k_tmp;
 double ek;
 dispersion.resize(L);
 for(int i=0; i<L; i++)
 {
  k_tmp=this->coor(i);
  ek=0.0;
  for(int j=0; j<dimen; j++) ek+=cos((k_tmp[j]+ktwist[j])*2.0*PI/n[j]);
  dispersion[i]=2.0*t_nn_sc*ek;
 }
}


void Supercubic::set_dispersion(const double* ktwist)
{
 vector<int> k_tmp; double km;
 double ek;
 dispersion.resize(L);
 for(int i=0; i<L; i++)
 {
  k_tmp=this->coor(i);
  ek=0.0;
  for(int j=0; j<dimen; j++) 
  {
   km=(k_tmp[j]+ktwist[j])*2.0*PI/n[j];
   if(km>=PI)  km-=2.0*PI;
   ek+=km*km;
  }
  dispersion[i]=ek;
 }
}
