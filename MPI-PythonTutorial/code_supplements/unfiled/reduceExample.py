from mpi4py.MPI import COMM_WORLD as comm
import numpy
rank = numpy.zeros(1)
total = numpy.zeros(1)
rank[0] = comm.Get_rank()
comm.Reduce(rank,total)
if rank == 0:
    print "total of ranks is" + str(total)