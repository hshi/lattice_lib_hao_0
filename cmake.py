#!/usr/bin/python
import sys
import os
import subprocess
typ  = sys.argv[1]
dirc = sys.argv[2]
if(typ=="mpi"):
  com="cmake -DCMAKE_CXX_COMPILER=mpic++ -DMPI_HAO=1 -DCMAKE_INSTALL_PREFIX:PATH=~/lib_hao/mpi "+dirc
elif(typ=="serial"):
  com="cmake -DCMAKE_INSTALL_PREFIX:PATH=~/lib_hao/serial "+dirc

subprocess.call(com, shell=True )
