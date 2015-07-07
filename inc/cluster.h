#ifndef CLUSTER_H
#define CLUSTER_H

#include<complex>
#include<vector>

class Cluster
{
 public:
    int     L;                              // total lattice number 
    int     Nhop_up, Nhop_dn;               //Number of hopping
    std::vector<std::complex<double>> hop_up, hop_dn;  //Hopping element
    std::vector<int>  siti_up,sitj_up,siti_dn,sitj_dn; //Hopping site i and j

    Cluster(); 
    Cluster(const Cluster& x);
    Cluster(Cluster&& x);
    ~Cluster();
   
    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);
};

#endif
