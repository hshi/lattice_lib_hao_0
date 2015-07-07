#include <iostream>
#include "cluster.h"

using namespace std;

void cluster_construct_test()
{
    size_t flag=0;

    Cluster c_a;
    if(c_a.L!=0) flag++;
    if(c_a.Nhop_up!=0) flag++;
    if(c_a.Nhop_dn!=0) flag++;

    c_a.L=20; c_a.Nhop_up=2; c_a.Nhop_dn=3;
    c_a.hop_up.resize(2);c_a.siti_up.resize(2);c_a.sitj_up.resize(2);
    c_a.hop_dn.resize(3);c_a.siti_dn.resize(3);c_a.sitj_dn.resize(3);
    c_a.hop_up[0]=complex<double>(1.0,2.0);c_a.hop_up[1]=complex<double>(2.0,3.0);
    c_a.hop_dn[0]=complex<double>(1.0,1.0);c_a.hop_dn[1]=complex<double>(2.0,2.0);c_a.hop_dn[2]=complex<double>(3.0,3.0);
    c_a.siti_up[0]=1; c_a.siti_up[1]=2;c_a.sitj_up[0]=3; c_a.sitj_up[1]=4;
    c_a.siti_dn[0]=2; c_a.siti_dn[1]=1;c_a.siti_dn[2]=1;c_a.sitj_dn[0]=6; c_a.sitj_dn[1]=9; c_a.sitj_dn[2]=3;

 
    Cluster c_b(c_a); 
    if(c_b.L!=c_a.L) flag++;
    if(c_b.Nhop_up!=c_a.Nhop_up) flag++;
    if(c_b.Nhop_dn!=c_a.Nhop_dn) flag++;
    for(int i=0; i<2; i++) {if( abs( c_b.hop_up[i]-c_a.hop_up[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<3; i++) {if( abs( c_b.hop_dn[i]-c_a.hop_dn[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<2; i++) {if( c_b.siti_up[i]!=c_a.siti_up[i] ) flag++;}
    for(int i=0; i<2; i++) {if( c_b.sitj_up[i]!=c_a.sitj_up[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_b.siti_dn[i]!=c_a.siti_dn[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_b.sitj_dn[i]!=c_a.sitj_dn[i] ) flag++;}


    Cluster c_c(move(c_b));
    if(c_c.L!=c_a.L) flag++;
    if(c_c.Nhop_up!=c_a.Nhop_up) flag++;
    if(c_c.Nhop_dn!=c_a.Nhop_dn) flag++;
    for(int i=0; i<2; i++) {if( abs( c_c.hop_up[i]-c_a.hop_up[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<3; i++) {if( abs( c_c.hop_dn[i]-c_a.hop_dn[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<2; i++) {if( c_c.siti_up[i]!=c_a.siti_up[i] ) flag++;}
    for(int i=0; i<2; i++) {if( c_c.sitj_up[i]!=c_a.sitj_up[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_c.siti_dn[i]!=c_a.siti_dn[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_c.sitj_dn[i]!=c_a.sitj_dn[i] ) flag++;}

    Cluster c_d; c_d=c_a;
    if(c_d.L!=c_a.L) flag++;
    if(c_d.Nhop_up!=c_a.Nhop_up) flag++;
    if(c_d.Nhop_dn!=c_a.Nhop_dn) flag++;
    for(int i=0; i<2; i++) {if( abs( c_d.hop_up[i]-c_a.hop_up[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<3; i++) {if( abs( c_d.hop_dn[i]-c_a.hop_dn[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<2; i++) {if( c_d.siti_up[i]!=c_a.siti_up[i] ) flag++;}
    for(int i=0; i<2; i++) {if( c_d.sitj_up[i]!=c_a.sitj_up[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_d.siti_dn[i]!=c_a.siti_dn[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_d.sitj_dn[i]!=c_a.sitj_dn[i] ) flag++;}

    Cluster c_e; c_e=move(c_d);
    if(c_e.L!=c_a.L) flag++;
    if(c_e.Nhop_up!=c_a.Nhop_up) flag++;
    if(c_e.Nhop_dn!=c_a.Nhop_dn) flag++;
    for(int i=0; i<2; i++) {if( abs( c_e.hop_up[i]-c_a.hop_up[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<3; i++) {if( abs( c_e.hop_dn[i]-c_a.hop_dn[i] ) > 1e-12 ) flag++;}
    for(int i=0; i<2; i++) {if( c_e.siti_up[i]!=c_a.siti_up[i] ) flag++;}
    for(int i=0; i<2; i++) {if( c_e.sitj_up[i]!=c_a.sitj_up[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_e.siti_dn[i]!=c_a.siti_dn[i] ) flag++;}
    for(int i=0; i<3; i++) {if( c_e.sitj_dn[i]!=c_a.sitj_dn[i] ) flag++;}
 
    if(flag==0) cout<<"Cluster passed the construction test!\n";
    else cout<<"Warning!!!!Cluster failed the construction test!\n";
}

void cluster_test()
{
    cluster_construct_test();
}
