from mpi4py.MPI import COMM_WORLD as comm
import numpy
def example( a = 0., b = 10., n = 10000):
   h = (b-a)/n
   local_n = n/comm.size
   local_a = a + comm.rank*local_n*h
   local_b = local_a + local_n*h
   integral = numpy.zeros(1)
   total = numpy.zeros(1)
   integral[0] = integrateRange(local_a, local_b, h);    
   comm.Reduce(integral, total)
   if comm.rank == 0:
       print "Our estimate is", total
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
