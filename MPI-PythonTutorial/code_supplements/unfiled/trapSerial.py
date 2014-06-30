import numpy
def f(x):
	return x*x
def integrateRange(a, b, dx):
	integral = (f(a) + f(b))/2.0
	for x in numpy.arange(a+dx, b, dx):
		integral = integral + f(x)
	integral = integral*dx
	return integral
def example( a = 0., b = 1., n = 10000):
	h = (b-a)/n;
	integral = integrateRange(a, b, h)
	print "With n =", n, "trapezoids, our estimate of the integral from", a, "to", b, "is", integral
if __name__ == "__main__" :
	example()
