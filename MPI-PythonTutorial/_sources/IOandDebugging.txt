.. _IOandDebugging:

===============================
I/O, Debugging, and Performance
===============================


I/O
---



Debugging
---------



.. function:: Comm.Barrier()

	Blocks until all processes in the communicator have reached this routine
	
	:param Comm: communicator on which we are to block processes
	:type Comm: MPI comm

Example:

.. code-block:: python


Performance: Speedup and Efficiency
-----------------------------------

Wtime() and Wtick()
-------------------

Example::

	#timeExample.py
	from mpi4py import MPI
	import numpy
	comm = MPI.COMM_WORLD	
	rank = comm.Get_rank()
	
	comm.Barrier()
	start = MPI.Wtime()
	
	A = numpy.array([[1.,2.,3.],[4.,5.,6.],[7.,8.,9.]])
	local_a = numpy.zeros(3)
	comm.Scatter(A,local_a)
	print "process", rank, "has", local_a
	
	comm.Barrier()
	end = MPI.Wtime()
	
	print end - start


Amdahl's Law
------------


Exercises
---------

1. Some examples may display super-linear speedup, at least at some point
2. Do a speedup analysis of the trap rule...

