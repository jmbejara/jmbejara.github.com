from mpi4py.MPI import COMM_WORLD as comm
from mpi4py.MPI import ANY_SOURCE
import numpy as np
rank = comm.Get_rank()
recv_buffer = np.str()

if comm.rank == 0:
    for i in range(1, comm.size):
        comm.recv(recv_buffer, ANY_SOURCE)
        print(recv_buffer)
    else:
        message = "Hello from Process" + str(rank)
        comm.send(message, dest = 0)


