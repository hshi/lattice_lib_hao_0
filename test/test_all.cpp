#ifdef MPI_HAO
#include <mpi.h>
#endif
#include <iostream>
using namespace std;

void supercubic_test();
void cluster_test();

int main(int argc, char** argv)
{
    int rank=0;

#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    if(rank==0) cout<<"\n\n\n=======Testing======="<<endl;
    supercubic_test();
    //cluster_test();

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return 0;
}
