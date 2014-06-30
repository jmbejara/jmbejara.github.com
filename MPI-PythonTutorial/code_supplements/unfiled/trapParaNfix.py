from mpi4py.MPI import COMM_WORLD as comm
from mpi4py.MPI import ANY_SOURCE
import numpy
def example( a = 0., b = 1., n = 10000):
   h = (b-a)/n
   local_n = n/comm.size
   extras = n%comm.size
   if comm.rank < extras:
    local_n += 1
   
   local_a = a + comm.rank*local_n*h 
   local_b = local_a + local_n*h   
   if comm.rank >= extras:
    local_a += extras*h
    local_b += extras*h
   print "proc num", comm.rank,"local_n",local_n,"local_a",local_a,"local_b",local_b
   
   integral = numpy.zeros(1)
   recv_buffer = numpy.zeros(1)
   integral[0] = integrateRange(local_a, local_b, local_n)
   total = numpy.zeros(1)
   comm.Reduce(integral,total)
   print "With n =", n, "trapezoids, our estimate of the integral from", a, "to", b, "is", total[0]
def f(x):
	return x*x
def integrateRange(a, b, n):
	integral = (f(a) + f(b))/2.0
	for x in numpy.linspace(a,b,n+1)[1:-1]:
		integral = integral + f(x)
	integral = integral*(b-a)/n
	return integral
if __name__ == "__main__" :
   example()
