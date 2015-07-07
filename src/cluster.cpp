#include <iostream>
#include <stdexcept>
#include <math.h>
#include "cluster.h"

using namespace std;

Cluster::Cluster():L(0),Nhop_up(0),Nhop_dn(0){}

Cluster::Cluster(const Cluster& x) 
{
    L=x.L; Nhop_up=x.Nhop_up; Nhop_dn=x.Nhop_dn;
    hop_up=x.hop_up; siti_up=x.siti_up; sitj_up=x.sitj_up; 
    hop_dn=x.hop_dn; siti_dn=x.siti_dn; sitj_dn=x.sitj_dn; 
}

Cluster::Cluster(Cluster&& x) 
{
    L=x.L; Nhop_up=x.Nhop_up; Nhop_dn=x.Nhop_dn;
    hop_up=move(x.hop_up); siti_up=move(x.siti_up); sitj_up=move(x.sitj_up);
    hop_dn=move(x.hop_dn); siti_dn=move(x.siti_dn); sitj_dn=move(x.sitj_dn);
}

Cluster::~Cluster() {}

Cluster& Cluster::operator  = (const Cluster& x) 
{
    L=x.L; Nhop_up=x.Nhop_up; Nhop_dn=x.Nhop_dn;
    hop_up=x.hop_up; siti_up=x.siti_up; sitj_up=x.sitj_up;
    hop_dn=x.hop_dn; siti_dn=x.siti_dn; sitj_dn=x.sitj_dn;
    return *this;
}

Cluster& Cluster::operator  = (Cluster&& x)
{
    L=x.L; Nhop_up=x.Nhop_up; Nhop_dn=x.Nhop_dn;
    hop_up=move(x.hop_up); siti_up=move(x.siti_up); sitj_up=move(x.sitj_up);
    hop_dn=move(x.hop_dn); siti_dn=move(x.siti_dn); sitj_dn=move(x.sitj_dn);
    return *this;
}
