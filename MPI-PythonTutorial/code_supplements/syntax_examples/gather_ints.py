'''
This module is to demonstrate how to pass integers in mpi4py.

Notes:

-Notice that if I set x_local and x to have dtype='int64' and when I specify 
MPI.INT in the gather (with the syntax comm.gather(x_local,[x,MPI.INT]) )
that I receive non-sensical output, but no error.

    The problem here, it turns out, was the pickling gather. I switches to 
    Numpy Gather (upper-case) and it worked fine. You just have to make sure
    that each array has the same dtype. In this case, both are 'int32' or
    'int64'.

-Notice that if we set x_local like below, then x_local is of dtype 'int64'
    
    x_local = numpy.arange(2)


'''

import numpy
from mpi4py import MPI

comm = MPI.COMM_WORLD

rank = comm.rank
size = comm.size

x_local = numpy.arange(2, dtype='int64')
x = numpy.empty(2*size, dtype = 'int64')

comm.Gather(x_local, [x, MPI.INT])

if rank == 0:
    print "dtype of x_local", x_local.dtype
    print "dtype of x", x.dtype
    print x


