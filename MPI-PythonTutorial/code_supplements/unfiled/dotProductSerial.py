import numpy
def dotSerial(x, y):
    return sum((map( lambda(x, y): x*y, zip(x, y))))
def example():
	x = numpy.array([1., 2., 3., 4., 5.])
	y = numpy.array([2., 2., 2., 2., 2.])
	print dotSerial(x, y)	
if __name__ == "__main__":
	example()
