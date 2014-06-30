#collective3.py
from mpi4py import MPI
import numpy
import sys

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

#read from command line
if rank == 0:
	n = int(sys.argv[1])
else:
	n = 0
#arbitrary example vectors, generated to be evenly divided by the number of
#processes for convenience

x = numpy.linspace(0,100,n) if comm.rank == 0 else None
y = numpy.linspace(20,300,n) if comm.rank == 0 else None

#initialize as numpy arrays
dot = numpy.array([0.])



#communicate vector size (we assumed only process 0 had its info
sendbuf = numpy.array([n])
comm.Bcast(sendbuf)
n = sendbuf[0]

#calculate sendcounts
leftOvers = n % size

#compute each process' local sendcount value
local_sendcount = numpy.array([n//size])
if rank < leftOvers:
    local_sendcount += 1

#compute the 'sendcount' argumant to pass into Scatterv
#we do this locally so that we don't have to do any communication
sendcount = (n//size)*numpy.ones(size) + numpy.hstack((numpy.ones(leftOvers),numpy.zeros(size - leftOvers)))

#calculate displacements
displacements = numpy.zeros(size)
for i in range(0,size):
	displacements[i] = numpy.sum(sendcount[0:i])



sendcount = tuple(sendcount)
displacements = tuple(displacements)

local_x = numpy.zeros(local_sendcount)
local_y = numpy.zeros(local_sendcount)


comm.Scatterv([x, sendcount, displacements, MPI.DOUBLE],
    local_x, root=0)
comm.Scatterv([y, sendcount, displacements, MPI.DOUBLE],
    local_y, root=0)

