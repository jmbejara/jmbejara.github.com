from mpi4py import MPI
from mpi4py.MPI import ANY_SOURCE

import numpy as np

comm = MPI.COMM_WORLD
rank = np.zeros(1)
rbuf = np.zeros(1)
total = np.zeros(1)
rank[0] = comm.Get_rank()


if rank[0] == 0:
    for i in range(1,comm.size):
        comm.Recv(rbuf, ANY_SOURCE)
        total[0] += rbuf[0]
    print "the toal of ranks is" + str(total)
else:
    comm.Send(rank)
