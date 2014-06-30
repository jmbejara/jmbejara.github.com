.. _PETSc_intro:

==================
PETSc Introduction
==================
This short tutorial is designed to introduce the basics of PETSc. PETSc , pronounced PET-see (the S is silent), ia a "Portable, Extensible Toolkit for
Scientific Computation." It consists of a "suite of data structures and routines for the scalable (parallel) solution of scientific applications modeled by partial differential equations. It supports MPI, shared memory pthreads, and NVIDIA GPUs, as well as hybrid MPI-shared memory pthreads or MPI-GPU parallelism." http://www.mcs.anl.gov/petsc/

Directions
----------
To begin this tutorial, follow these directions:

- Download the compressed folder ``PETSc_TutorialStuff.zip`` onto your Fulton supercomputing directory. Uncompress this file and change your current directory to it.

- Now to begin, we will compile and run our first program. Change your current directory to the ``vector`` folder. Then type the following command and press <Enter>::

	$ make vec_create_seq

All this does is it compiles ``vec_create_seq.c`` with a bunch of command line options automatically so that you don't have to type them or even worry about them. Notice that this command created an executable called ``vec_create_seq``.

- Run this executable type the following command and press Enter::

	$ ./vec_create_seq

The output should appear as follows::

	Seq vector x:
	Vector Object: 1 MPI processes
	  type: seq
	3
	3
	3
	3
	3
	3
	3
	3
	3
	3 

Explanation of Code
-------------------

Now lets take a look at the code::

	#include <petscvec.h>
	#define VEC_SIZE 10
	#define VEC_DEFAULT_VALUE 3
	#undef __FUNCT__
	#define __FUNCT__ "main"
	int main(int argc, char **argv)
	{
  	  Vec x_Seq;
  	  PetscErrorCode ierr;
  	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
  	  ierr = VecCreateSeq(PETSC_COMM_SELF,VEC_SIZE,&x_Seq);CHKERRQ(ierr);
  	  ierr = VecSet(x_Seq,Vec_DEFAULT_VALUE);
  	  ierr = PetscPrintf(PETSC_COMM_SELF,"Seq vector x:\n");CHKERRQ(ierr);
  	  ierr = VecView(x_Seq, PETSC_VIEWER_STDOUT_SELF);CHKERRQ(ierr);
  	  ierr = VecDestroy(&x_Seq);CHKERRQ(ierr);
  	  ierr = PetscFinalize();CHKERRQ(ierr);
	  return 0;
	}

In the first line::

	#include <petscvec.h>

we tell the compiler to include the header for vectors which is called ``petscvec.h``. You will generally only need to include one header for any given PETSc program but be aware that the header will include A LOT of code so PETSc executables are generally very large. The next two lines::

	#define VEC_SIZE 10
	#define VEC_DEFAULT_VALUE 3

are macro statements that define the size of the vector that we will be creating and the default value that it will be set to. The next two lines::

	#undef __FUNCT__
	#define __FUNCT__ "main"

are meant to protect against multiple definitions of the main function::

	int main(int argc, char **argv)

.. note:: 
	
	Code that appears before the main function is usually just extra stuff and can be ignored, with the important exception of ``#define`` statements.

The first line of our main function::

  	  Vec x_Seq;

declares a variable of type ``Vec``. Basically, Vec is a pre-defined data structure that holds all the data that a vector needs to know about itself, including the data it holds. The next line::

  	  PetscErrorCode ierr;

declares a PETSc error code variable which should be checked constantly so that in the event of your program crashing, you know exactly where the error occurred.

The first line of code that makes a function call is next::

  	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

This should always be done first. ``PetscInitialize`` is the function that gets everything ready for your program to run properly including interpreting command line options given to the program and makes calls to functions such as ``MPI_Init``. Notice how the return value of ``PetscInitialize`` is assigned to ``ierr`` as is the case for every function call in this program. On the same line the function ``CHKERRQ`` is supplied with the value that was just returned. Because this is done for every function call, you as the programmer will know every time your program crashes exactly where the error occurred. It may seem redundant and tedious but it is well worth the effort.

The next line::

  	  ierr = VecCreateSeq(PETSC_COMM_SELF,VEC_SIZE,&x_Seq);CHKERRQ(ierr);

makes a function call to ``VecCreateSeq`` which brings a vector object into existence. The first argument to the function is an ``MPI_Comm`` value. In this example we use ``PETSC_COMM_SELF`` because this is a uniprocessor example. The next value is the size of the vector we wish to create. Note the use of a predefined constant rather than just using a number. Always use a predefined constant. It may seem unnecessary in this small example but it reduces the chances of mistakes greatly for larger programs. It is a good habit to develop. The final argument is a pointer to the variable that will represent the vector we are creating. Hopefully you are familiar enough with *C* pointers to understand why it is done this way. If not, just understand that for some tasks it is better for the program to pass around a reference to a variable rather than the whole memory contents that a variable represents.

So, now we have initialized our program and created a vector. At this point, we have a vector with ten positions. The default value happens to be zero in this case. YOu cannot, however, assume that a PETSc object will be zeroed out initialy. It is recommended that you always set your PETSc objects to some default value, even if it is zero.

Luckily, this is very straightforward with PETSc. When dealing with vectors, use the function ``VecSet``, as the code above does::

  	  ierr = VecSet(x_Seq,Vec_DEFAULT_VALUE);

All you have to do is supply two arguments: the vector you would like to have reset to a single value and the value. Now our vector has the value *3* at every position.

The next line::

  	  ierr = PetscPrintf(PETSC_COMM_SELF,"Seq vector x:\n");CHKERRQ(ierr);

demonstrates how to use the PETSc equivalent of ``printf`` in *C*. It is called, conveniently enough, ``PetscPrintf``. The only difference between ``printf`` from the *C* standard library and ``PetscPrintf`` is that the ``MPI_Comm`` must be given as the first argument to ``PetscPrintf`. We use the same one here as before because the program is still uniprocessor and the ``MPI_Comm`` you use for a specific program will usually (but not always) stay the same throughout the program. I chose to print out the message ``Seq vector x:`` so that the output can be understood more clearly. This is certainly not necessary but can be useful for debugging.

PETSc objects are generally very easy to view. For vectors, the next line of code demonstrates this::

  	  ierr = VecView(x_Seq, PETSC_VIEWER_STDOUT_SELF);CHKERRQ(ierr);

The function ``VecView`` prints out the vector that is given as the first argument using the PETSc viewer value given as the second argument. The PETSc viewer value tells the viewer function if the vector is to be printed out by each processor or whether the processors should sync their output to one processor only. In this case, there is only one processor so we use the standard value, PETSC_VIEWER_STDOUT_SELF.

At this point we are done with our vector. First, we created it. Then, we set every position simultaneously to the same value. Finally, we viewed the contents of the vector to ensure that this actually occurred. So now we need to "destroy" it. Memory management in a large parallel program is vital to good performance, so destroy PETSc objects the moment they become useless. To destroy a vector, we simply call ``VecDestroy`` and supply a pointer to the vector as the argument as demonstrated in this line of code::

  	  ierr = VecDestroy(&x_Seq);CHKERRQ(ierr);

So now we come to the last function call::

  	  ierr = PetscFinalize();CHKERRQ(ierr);

This function is equally as important as ``PetscInitialize``. It basically just cleans everything up. So now we can return *0* and our first program is done. 

Key Functions Learned
---------------------

``PetscInitialize(int *argc,char ***args,const char file[],const char help[])``
	* Analogous to MPI_Init. It is the beginning of every PETSc program
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Sys/PetscInitialize.html
``VecCreateSeq(MPI_Comm comm,PetscInt n,Vec *v)``
	* Creates a sequential vector object which involves allocating memory, setting up the appropriate MPI communicator, applying any command line options and sizing it
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecCreateSeq.html
``VecSet(Vec x,PetscScalar alpha)``
	* Sets every position in the supplied Vec object to the supplied value
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecSet.html
``PetscPrintf(MPI_Comm comm,const char format[],...)``
	* The petsc version of printf. Works exactly like c std lib printf except that the first argument specifies if the message should be printed by every processor or just the root processor.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Sys/PetscPrintf.html
``VecView(Vec vec,PetscViewer viewer)``
	* Dumps the contents of the supplied Vec object using the specified viewer
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecView.html
``VecDestroy(Vec *v)``
	* Destroys the Vec object associated with the supplied Vec pointer which frees up the memory associated with the Vec object.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecDestroy.html
``PetscFinalize(void)``
	* Cleans up everything and allows for a graceful program termination. It is the ending of every PETSc program.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Sys/PetscFinalize.html
``CHKERRQ(PetscErrorCode errorcode)``
	* Checks the petsc error code. If the value indicates that an error occurred then it will dump information that will help in tracing the error to STDOUT. If not then it will do nothing.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Sys/CHKERRQ.html

Summary
-------

Let's reflect on what we've learned and the pattern for most PETSc programs.

- Create pre-defined constants for all values such as the vector size to limit magic number type errors. 
- Place a PETSc error code check on EVERY line of code that makes a PETSc function call. 
- Clean up memory as soon as possible.

The pattern for PETSc programs is straightforward:

	1. Declare all the variables that your program will make use of. 
	2. Call ``PetscInitialize``. 
	3. Make all the function calls that constitute the body of your program. 
	4. Call ``PetscFinalize``. 

As you can probably guess, its the body of your program that will be the hardest part. But follow the pattern so that the other parts don't cause unnecessary headaches.

Congratulations, you just compiled, ran, and hopefully even understood your first PETSc program!