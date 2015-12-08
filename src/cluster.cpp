#include <iostream>
#include <stdexcept>
#include <math.h>
#include "cluster.h"

using namespace std;

Cluster::Cluster():L(0){}

Cluster::Cluster(const Cluster& x) 
{
    L=x.L;
}

Cluster::Cluster(Cluster&& x) 
{
    L=x.L; 
}

Cluster::~Cluster() {}

Cluster& Cluster::operator  = (const Cluster& x) 
{
    L=x.L;
    return *this;
}

Cluster& Cluster::operator  = (Cluster&& x)
{
    L=x.L;
    return *this;
}
