#include <iostream>
#include "rashba2d.h"
using namespace std;

void rashba2d_construct_test()
{
    int dimen=2;
    int n[2]={3,5};
    size_t flag=0;

    //Construct
    Rashba2d latt(dimen, n);
    if(latt.dimen!=dimen)    flag++;
    for(int i=0; i<dimen;i++) {if(latt.n[i]!=n[i]) flag++;}
    if(latt.L!=15) flag++;
    if(latt.Nhop!=0) flag++;

    latt.uk.push_back({1.0,2.0});
    latt.vk.push_back({2.0,3.0});
    latt.vk.push_back({3.0,4.0});

    //Copy
    Rashba2d latt_c(latt);
    if(latt_c.dimen!=dimen)    flag++;
    for(int i=0; i<dimen;i++) {if(latt_c.n[i]!=n[i]) flag++;}
    if(latt_c.L!=15) flag++;
    if(latt_c.Nhop!=0) flag++;
    if(abs(latt_c.uk[0]-complex<double>(1.0,2.0))>1e-12) flag++;
    if(abs(latt_c.vk[0]-complex<double>(2.0,3.0))>1e-12) flag++;
    if(abs(latt_c.vk[1]-complex<double>(3.0,4.0))>1e-12) flag++;


    //Move Copy
    Rashba2d latt_v(move(latt));
    if(latt_v.dimen!=dimen)    flag++;
    for(int i=0; i<dimen;i++) {if(latt_v.n[i]!=n[i]) flag++;}
    if(latt_v.L!=15) flag++;
    if(latt_v.Nhop!=0) flag++;
    if(abs(latt_v.uk[0]-complex<double>(1.0,2.0))>1e-12) flag++;
    if(abs(latt_v.vk[0]-complex<double>(2.0,3.0))>1e-12) flag++;
    if(abs(latt_v.vk[1]-complex<double>(3.0,4.0))>1e-12) flag++;


    //Equal
    Rashba2d latt_ec; latt_ec=latt_c;
    if(latt_ec.dimen!=dimen)    flag++;
    for(int i=0; i<dimen;i++) {if(latt_ec.n[i]!=n[i]) flag++;}
    if(latt_ec.L!=15) flag++;
    if(latt_ec.Nhop!=0) flag++;
    if(abs(latt_ec.uk[0]-complex<double>(1.0,2.0))>1e-12) flag++;
    if(abs(latt_ec.vk[0]-complex<double>(2.0,3.0))>1e-12) flag++;
    if(abs(latt_ec.vk[1]-complex<double>(3.0,4.0))>1e-12) flag++;


    //Move Equal
    Rashba2d latt_ev; latt_ev=move(latt_c);
    if(latt_ev.dimen!=dimen)    flag++;
    for(int i=0; i<dimen;i++) {if(latt_ev.n[i]!=n[i]) flag++;}
    if(latt_ev.L!=15) flag++;
    if(latt_ev.Nhop!=0) flag++;
    if(abs(latt_ev.uk[0]-complex<double>(1.0,2.0))>1e-12) flag++;
    if(abs(latt_ev.vk[0]-complex<double>(2.0,3.0))>1e-12) flag++;
    if(abs(latt_ev.vk[1]-complex<double>(3.0,4.0))>1e-12) flag++;


    if(flag==0) cout<<"Rashba2d passed the construction and equal test!\n";
    else cout<<"Warning!!!!Rashba2d failed the construction and equal test!\n"; 
}


void rashba2d_disp_lattice_test()
{
    int dimen=2;
    int n[2]={2,3};
    double t1=-1.0; double lambda=1.30904;
    size_t flag=0;
    Rashba2d latt(dimen, n);
    latt.set_dispersion(t1, lambda);

    vector<double> disp_exact={-4.00000000000001, 0.000000000000000E+000, -2.13366189456998, 1.86633810543002, -2.13366189456998,
                               1.86633810543002,  -4.00000000000001, 0.000000000000000E+000, 0.133661894569983, 4.13366189456999,
                               0.133661894569983,  4.13366189456999};
    vector<complex<double>> uk_exact={ {-0.707106781186547,0.000000000000000E+000}, {0.000000000000000E+000,-0.707106781186548},
                                 {-0.707106781186547,0.000000000000000E+000}, {-0.707106781186547,-9.999199243478975E-017},
                                 {0.707106781186547,0.000000000000000E+000},  {0.707106781186547,-9.999199243478976E-017}};

    for(int i=0; i<latt.L*2; i++)
    {
        if( (disp_exact[i]-latt.dispersion[i] )>1e-12 ) flag++;
    }
    for(int i=0; i<latt.L; i++)
    {
        if( abs(uk_exact[i]-latt.uk[i] )>1e-12 ) flag++;
    }

    if(flag==0) cout<<"Rashba2d passed the lattice dispersion test!\n";
    else cout<<"Warning!!!!Rashba2d failed the lattice dispersion test!\n";
}


void rashba2d_disp_continuous_test()
{
    int dimen=2;
    int n[2]={2,3};
    double lambda=1.30904;
    size_t flag=0;
    Rashba2d latt(dimen, n);
    latt.set_dispersion(lambda);

    vector<double> disp_exact={0.000000000000000E+000, 5.75713395383418, 1.64484388009182,
                                        9.31352089054833,1.64484388009182,9.31352089054833,0.000000000000000E+000,
                                        13.9820748483445,7.12813780976539,19.1986696014876,7.12813780976539,
                                        19.1986696014876};
    vector<complex<double>> uk_exact={ {-0.707106781186547,0.000000000000000E+000}, {0.000000000000000E+000,-0.707106781186548},
                                 {-0.707106781186547,0.000000000000000E+000}, {-0.392232270276368,-0.588348405414552},
                                 {0.707106781186547,0.000000000000000E+000},  {0.392232270276368,-0.588348405414552}};

    for(int i=0; i<latt.L*2; i++) 
    {
        if( (disp_exact[i]-latt.dispersion[i] )>1e-12 ) flag++;
    }
    for(int i=0; i<latt.L; i++)
    {
        if( abs(uk_exact[i]-latt.uk[i] )>1e-12 ) flag++;
    }

    if(flag==0) cout<<"Rashba2d passed the continuous dispersion test!\n";
    else cout<<"Warning!!!!Rashba2d failed the continuous dispersion test!\n";
}

void rashba2d_test()
{
    rashba2d_construct_test();
    rashba2d_disp_lattice_test();
    rashba2d_disp_continuous_test();
}
