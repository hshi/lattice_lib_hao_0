#include <iostream>
#include <stdexcept>
#include <math.h>
#include "rashba2d.h"

#define PI 3.14159265358979324

using namespace std;

Rashba2d::Rashba2d():Supercubic() {}

Rashba2d::Rashba2d(int Dc, const int* Nc):Supercubic(Dc, Nc) 
{
    if(dimen!=2) {cout<<"Rashba2d only support two dimension!!!"<<endl; exit(1); }
}

Rashba2d::Rashba2d(const Rashba2d& x):Supercubic(x) 
{
    if(dimen!=2) {cout<<"Rashba2d only support two dimension!!!"<<endl; exit(1); }
    uk=x.uk; 
    vk=x.vk;
}

Rashba2d::Rashba2d(Rashba2d&& x):Supercubic(std::move(x))  
{
    if(dimen!=2) {cout<<"Rashba2d only support two dimension!!!"<<endl; exit(1); }
    uk=std::move(x.uk);
    vk=std::move(x.vk);
}


Rashba2d::~Rashba2d() {}

Rashba2d& Rashba2d::operator  = (const Rashba2d& x) 
{
    Supercubic::operator=(x);
    if(dimen!=2) {cout<<"Rashba2d only support two dimension!!!"<<endl; exit(1); }
    uk=x.uk;
    vk=x.vk; 
    return *this;
}

Rashba2d& Rashba2d::operator  = (Rashba2d&& x) 
{
    Supercubic::operator=(std::move(x));
    if(dimen!=2) {cout<<"Rashba2d only support two dimension!!!"<<endl; exit(1); } 
    uk=std::move(x.uk);
    vk=std::move(x.vk);
    return *this;
}

void Rashba2d::set_dispersion(double t_nn_sc, double lambda)
{
    complex<double> Xi(0.0,1.0); 
    vector<int> k_tmp; double kx,ky;
    double ek, esoc;

    dispersion.resize(2*L); uk.resize(L); vk.resize(L); 
    for(int i=0; i<L; i++)
    {
        k_tmp=this->coor(i);
        kx=k_tmp[0]*2.0*PI/n[0]; 
        ky=k_tmp[1]*2.0*PI/n[1];

        ek   = 2.0*t_nn_sc*( cos(kx)+cos(ky) );

        esoc = lambda*sqrt( sin(kx)*sin(kx)+sin(ky)*sin(ky) ) ; //Remove 2.0 here so that it is consistent with continuous.

        if( k_tmp[0]==0 && k_tmp[1]==0) uk[i]=-1.0/sqrt(2.0);
        else uk[i]= -1.0*( sin(ky)+Xi*sin(kx) ) / ( sqrt(2.0)*abs((sin(ky)-Xi*sin(kx))) );
        vk[i]=1.0/sqrt(2.0); 

        dispersion[i]  = ek-esoc;
        dispersion[i+L]= ek+esoc;
    }
}


void Rashba2d::set_dispersion(double lambda)
{
    complex<double> Xi(0.0,1.0);
    vector<int> k_tmp; double kx,ky;
    double ek, esoc;

    dispersion.resize(2*L); uk.resize(L); vk.resize(L);
    for(int i=0; i<L; i++)
    {
        k_tmp=this->coor(i);
        kx=k_tmp[0]*2.0*PI/n[0]; if(kx>PI)  kx-=2.0*PI;
        ky=k_tmp[1]*2.0*PI/n[1]; if(ky>PI)  ky-=2.0*PI;

        ek   = kx*kx+ky*ky ;

        esoc = lambda*sqrt( kx*kx + ky*ky ) ;

        if( k_tmp[0]==0 && k_tmp[1]==0) uk[i]=-1.0/sqrt(2.0);
        else uk[i]=-1.0*(ky+Xi*kx) / ( sqrt(2.0)*abs(ky-Xi*kx) );
        vk[i]=1.0/sqrt(2.0);

        dispersion[i]  = ek-esoc;
        dispersion[i+L]= ek+esoc;
    }
}

