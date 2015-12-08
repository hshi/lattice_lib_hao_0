#include <iostream>
#include "cluster.h"

using namespace std;

void cluster_construct_test()
{
    size_t flag=0;

    Cluster c_a;
    if(c_a.L!=0) flag++;

    c_a.L=20;
 
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

void cluster_test()
{
    cluster_construct_test();
}
