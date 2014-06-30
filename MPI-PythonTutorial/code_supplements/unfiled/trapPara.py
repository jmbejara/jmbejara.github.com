from mpi4py.MPI import COMM_WORLD as comm
from mpi4py.MPI import ANY_SOURCE
import numpy
def example( a = 0., b = 1., n = 10000):
   h = (b-a)/n
   local_n = float(n)/comm.size
   local_a = a + comm.rank*local_n*h
   local_b = local_a + local_n*h   
   integral = numpy.zeros(1)
   recv_buffer = numpy.zeros(1)
   integral[0] = integrateRange(local_a, local_b, h)
   if comm.rank == 0:
      total = integral[0]
      for i in range(1, comm.size):
         comm.Recv(recv_buffer, ANY_SOURCE)
         total += recv_buffer[0]
   else:
      comm.Send(integral)
   if comm.rank == 0:
	print "With n =", n, "trapezoids, our estimate of the integral from", a, "to", b, "is", total
def f(x):
	return x*x
def integrateRange(a, b, dx):
	integral = (f(a) + f(b))/2.0
	for x in numpy.arange(a+dx, b, dx):
		integral = integral + f(x)
	integral = integral*dx
	return integral
if __name__ == "__main__" :
   example()
