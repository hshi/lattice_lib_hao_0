#ifndef CLUSTER_H
#define CLUSTER_H

#include<complex>
#include<vector>

//We do not have any member function for a general cluster.
//Only the lattice size L is used in this class.
class Cluster
{
 public:
    int     L; 

    Cluster(); 
    Cluster(const Cluster& x);
    Cluster(Cluster&& x);
    ~Cluster();
   
    Cluster& operator  = (const Cluster& x);
    Cluster& operator  = (Cluster&& x);
};

#endif
