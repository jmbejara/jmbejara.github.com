.. A Python Introduction to Parallel Programming with MPI documentation master file, created by
   sphinx-quickstart on Wed Apr 25 15:38:55 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

A Python Introduction to Parallel Programming with MPI
==================================================================================

A short introduction and tutorial to distributed memory computing with Python. Although HPC projects should usually be written in faster, compiled languages, like C or Fortran, Python is an excellent tool for algorithm development and proof of concept. This is especially true in parallel programming, where code becomes especially complex.

Parallel computing is overviewed, and MPI is introduced. Python is used to demonstrate applications and introduce the methods of the interface. 


There are TODO's in this document:
	* Allreduce and Reduce theoretically take the same amount of time. Include a picture of the butterfly communication structure.
TODO not listed:
	* note how you can use mpi4py on you own computer (serially, for testing purposes)
	* stuff about I/O
	* how to properly time a parallel function
	* Section of chapter on parallel libraries (how this is accomplished by communicators. See end of preface.)
	* show how you can run unbuffered. Then, if you would like to print, you must use the format of print where you concatenate string, not seperate them with commas  
	
	

.. toctree::
   :maxdepth: 2
   
   preface
   overview
   introMPI
   pointToPoint
   collectiveCom
   IOandDebugging
   appendix


Indices and tables
==================

* :ref:`genindex`
* :ref:`search`

