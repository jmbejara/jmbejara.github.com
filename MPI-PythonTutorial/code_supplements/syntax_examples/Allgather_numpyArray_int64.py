'''
Syntax example for Allgather with numpy integer arrays (dtype= 'int64').
'''

import numpy
from mpi4py import MPI

comm = MPI.COMM_WORLD

rank = comm.rank
size = comm.size

x_local = numpy.arange(2, dtype='int64')
x = numpy.empty(2 * size, dtype='int64')

comm.Allgather(x_local, [x, MPI.INT])

if rank == 0:
    print "dtype of x_local", x_local.dtype
    print "dtype of x", x.dtype
print x


