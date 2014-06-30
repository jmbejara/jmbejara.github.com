from mpi4py import MPI 
from array import array 
comm = MPI.COMM_WORLD 
if comm.rank == 0: 
    comm.Send("hello",dest=1) 
elif comm.rank == 1: 
    buf = array('c', '\0') * 256
    r = comm.Irecv(buf,source=0) 
    status = MPI.Status() 
    r.Wait(status) 
    n = status.Get_count(MPI.CHAR) 
    s = buf[:n].tostring() 
    print s 