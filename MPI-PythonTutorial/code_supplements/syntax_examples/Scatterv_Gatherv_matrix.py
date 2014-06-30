# Note: The sendcounts and displaments are hardcoded on purpose. They are
# coded so as to demonstrate the use of "Gatherv" and "Scatterv."
#This code snipeet is to be run only with 3 processes
# mpiexec -n 3 python26 scratch.py -u
import numpy
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if not size == 3:
    raise ValueError('Only runs with communicator of size 3')

M = 11
N = 4

#Notice that the matrix is created only on process 0.
if rank == 0:
    x = numpy.linspace(0,100,N*M).reshape((M,N))
else:
    x = None

#Initialize local vectors to receive pieces of x    
if rank == 2:
    xlocal = numpy.zeros((9,N))
else:
    xlocal = numpy.zeros((1,N))

if rank == 0:
    print "Gather"
    
comm.Scatterv([x,(1*N,1*N,9*N),(0*N,1*N,2*N),MPI.DOUBLE],xlocal)
#This demonstrates who has what stored locally after the scatter
print ("process " + str(rank) + " has " +str(xlocal))

comm.Barrier()
if rank == 0:
        print "Gather"
        xGathered = numpy.zeros((M,N))
else:
        xGathered = None

#This demonstrates who has what locally after the gather.
comm.Gatherv(xlocal,[xGathered,(1*N,1*N,9*N),(0*N,1*N,2*N),MPI.DOUBLE])
print ("process " + str(rank) + " has " +str(xGathered)) 