.. _preface:

=======
Preface
=======

This tutorial was written for use in teaching courses in an undergradtuate research training program in applied and computational mathematics at BYU (for both the IMPACT group in the Department of Mathematics [#f1]_ and for the Macro Group in the Department of Economics [#f2]_).

Why *MPI for Python* (mpi4py)?
------------------------------

The purpose of this tutorial is to teach parallel programming on ditributed memory machines using MPI (Message Pasing Interface). I have written the entire tutorial in Python using the MPI implementation mpi4py. 

Though the most appropriate languages for parallel computing are C or Fortran, many researchers favor array-based languages (such as Python or Matlab) over C and Fortran for their ease of use. In particular, Python has become increasingly popular. Unfortunately, Python is not well suited for High Performance Computing and its the parallel capabilities are still somewhat underdeveloped. However, for the same reason that Python is an excellent language for algorithm design and for solving problems that don't require maximum performance, Python is an excellent tool in developing parallel code. In general, parallel programming is much more difficult and complex than in serial. This makes parallel programming in Python great for prototyping and for small to medium codes. It can even be considered appropriate for production if the communication is not very frequent and performance is not the primary concern [#f3]_.

Most importantly, I use Python coupled with mpi4py for pedagogical purposes. mpi4py seems to retain the most functionality of C implementations of MPI of the several parallel Python packages. This allows me to present MPI in a way that can be easily translated into C or Fortran. Throughout this tutorial I restrict myself to using mpi4py in a way that best resembles MPI in C or Fortran.

Note that one of the main differences between this presentation of mpi4py and MPI in C or Fortan, besides being array-based, is that mpi4py is largely object oriented. The MPI Communicator in mpi4py is a Python class and MPI functions like *Send* or *Broadcast* are instance methods of the communicator class. The object-oriented nature of mpi4py is seen mostly in dealing with MPI topologies. I will not discuss these in detail, but rather focus on an introduction to the basics of distributed memory programming with MPI. Throughout the tutorial you will see functions like ``Send(...)`` are presented as ``Comm.Send(...)`` where it is implied that ``Comm`` is an instance of the *Comm* class. I will document ``Comm`` as in input parameter to the function.
	
Also, note that mpi4py supports two methods of communication to implement each of the basic MPI commands. They are the upper and lower case commands (e.g. ``Bcast(...)`` and ``bcast(...)``). The uppercase implementations use traditional MPI datatypes while the lower case use Python's pickling method. Pickling offers extra convenience to using mpi4py, but the traditional method is faster. In this tutorial, we use only the uppercase functions, though we include a section about using the other.

Why this tutorial?
------------------
Although other tutorials exist that teach mpi4py, none are complete and none of them teach MPI from scratch. This tutorial dills that gap and is designed to teach MPI from a beginner's point of view, enabling the student the convenience of learning it with Python.

.. [#f1] BYU IMPACT Group http://impact.byu.edu
.. [#f2] BYU Macro Group, Computational Economics Boot Camp http://economics.byu.edu/Pages/MacroLab/MacroLab-Boot-Camp.aspx
.. [#f3] http://www.tacc.utexas.edu/c/document_library/get_file?uuid=be16db01-57d9-4422-b5d5-17625445f351&groupId=13601
