.. _PETSc_parallel_intro:

==========================
PETSc: Let's Get Parallel
==========================
The last example was meant for a single processor only which isn't all that beneficial considering that the whole point of PETSc is to do things in parallel. So let's get parallel. 

Directions
----------

Follow these directions to compile and run a short code that will create a vector that parallel:

- If you are not already in the vector subfolder, go there now. It is in the PETSc_TutorialStuff folder that should already be in your directory.
- We compile parallel and uniprocessor programs the same way. For this example enter the following and press Enter::

	$ make vec_create_mpi

- However, running them is different. They must be called using MPI. To run this executable type the following command and press Enter::

	$ mpiexec -n 2 ./vec_create_mpi

- The output should appear as follows::

	MPI vector x:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	0
	0
	0
	0
	0
	Process [1]
	1
	1
	1
	1
	1

This has created a *10 x 1* array that exists on two seperate processes, with the value of each element equal to the process on which it is stored.

Explanation of Code
-------------------

Now lets take a look at the code::

	#include <petscvec.h>
	#define VEC_SIZE 10
	#undef __FUNCT__
	#define __FUNCT__ "main"
	int main(int argc, char **argv)
	{
	  Vec x_MPI;
	  PetscErrorCode ierr;
	  PetscInt num_proc, istart, iend, i;
	  PetscMPIInt proc_rank;
	  PetscScalar value;
	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);
	  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,VEC_SIZE,&x_MPI);CHKERRQ(ierr);
	  ierr = VecGetOwnershipRange(x_MPI,&istart,&iend);CHKERRQ(ierr);
	  for(i = istart; i < iend; i++)
  	  {
    	    value = proc_rank;
    	    ierr = VecSetValues(x_MPI,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
 	  }
  	  ierr = VecAssemblyBegin(x_MPI);CHKERRQ(ierr);
  	  ierr = VecAssemblyEnd(x_MPI);CHKERRQ(ierr);
  	  ierr = PetscPrintf(PETSC_COMM_WORLD,"MPI vector x:\n");CHKERRQ(ierr);
  	  ierr = VecView(x_MPI, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  	  ierr = VecDestroy(&x_MPI);CHKERRQ(ierr);
  	  ierr = PetscFinalize();CHKERRQ(ierr);
  	  return 0;
	}	

From here on out we will ignore the code appearing before the main function declaration as it is very repetitive. However, it is important, especially the #define statements, so it should not be ignored by you as the programmer.

The first line of our main function::

  	  Vec x_MPI;

declares a variable of type ``Vec`` just the same as in the previous section.
The next line::

  	  PetscErrorCode ierr;

declares a PETSc error code variable, also as in the last section.
The next line::

  	  PetscInt num_proc, istart, iend, i;

declares several ``PetscInt`` variables, which behave like regular ``int`` variables to the programmer, but different for PETSc.
The next line::

  	  PetscMPIInt proc_rank;

declares a ``PetscMPIInt`` which is just like a regular int to the programmer but different for PETSc.
The next line::

	  PetscScalar value;

declares a ``PetscScalar``. A ``PetscScalar`` is basically a float or a double, which can be real or complex.

.. note::

	In every program, variables should all be declared at the top of the code as we have done here. This means that the variable definition section can get quite long. Use comments and whitespace to make it more readable, as with all of your code.

The first line of code that makes a function call is next::

  	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

Get used to this being the first line in the main function with a function call.

The next line::

  	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);

gets the value that was supplied immediately after the ``-n`` option given at the command line. The function PetscOptionsGetInt is used to pull integer values out of the command line options. It is most useful when used as the above line demonstrates; to get the number of processors that the current program is running on.

The next line::

  	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);

is where this program begins to demonstrate noticeably different behavior on different processors. With the way MPI works, every processor involved in a single program is given a rank. The root processor is rank 0, the second processor is rank 1, etc. The program ``MPI_Comm_rank`` gets the rank for each processor and thus differs for each processor.

The next line::

  	  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,VEC_SIZE,&x_MPI);CHKERRQ(ierr);

is the parallel version of ``VecCreateSeq``. ``VecCreateMPI`` creates a parallel vector which means that the vector is distributed over all the processors involved in the program. The first argument to the function is the MPI comm which is ``PETSC_COMM_WORLD`` in this case because we want the vector to be distributed over every processor. The second argument is the size of the local vector and the third argument is the size of the total vector. To demonstrate this, imagine we have ten marbles and five students. We wish to divide the marbles up evenly. Thus, each student would receive two marbles (size of the local vector) and the total number of marbles would be ten (size of the total vector). This does not mean, however, that the division has to be even. We could have given one of the students more marbles than another. But to spread the workload as evenly as possible, it is recommended that the second argument be ``PETSC_DECIDE`` which lets PETSc evenly divide up the vector for you. The third argument is set by us and is 10 in this case. Because we have two processors, each processor will get a local vector of size 5 and PETSc will decide this for us. The last argument is a pointer to the vector variable.

.. note::

	This function has four arguments and it can be hard if not impossible to remember what they are and the order they should appear. PETSc has a great online manual. Use it so that you don't forget or mix up arguments in your function calls:
  	  http://www.mcs.anl.gov/petsc/petsc-current/docs/index.html

.. warning::

	In order to achieve speedups with PETSc, it is important to create vectors and matrices in parallel in addition to solving them in parallel. The PETSc user manual in the beginning warns, "PETSc should not be used to attempt to provide a **'parallel linear solver'** in an otherwise sequential code. Certainly all parts of a previously sequential code need not be parallelized but the matrix generation portion must be paralleized to expect any kind of reasonable performance. Do not expect to generate your matrix sequentially and then 'use PETSc' to solve the linear system in parallel" (p. 3).

	


The next line::

	  ierr = VecGetOwnershipRange(x_MPI,&istart,&iend);CHKERRQ(ierr);

allows each processor to figure out the specific range of the vector that belongs to it. For the root processor, ``istart`` would be 0 and ``iend`` would be 4. For the second processor, ``istart`` would be 5 and ``iend`` would be 9. However, these indices will change if either the number of processors change or the size of the vector changes. Thus, these should never be hard coded and always determined with a function call to ``VecGetOwnershipRange``.

The next five lines::

	  for(i = istart; i < iend; i++)
  	  {
    	    value = proc_rank;
    	    ierr = VecSetValues(x_MPI,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
 	  }

iterate over the range owned by each processor and assign to each position the MPI rank of the processor that owns that position. ``VecSetValues`` inserts a vector of values (the fourth argument, value in this case) of a size given by the second argument (1 in this case) at the position specified by the third argument (i in this case) into a vector given by the first argument (x_MPI in this case). The mode for ``VecSetValues`` is given by the last argument and is ``INSERT_VALUES`` in this example. ``INSERT_VALUES`` replaces existing values with new values. The other option is ``ADD_VALUES`` which adds the existing values with the new values and stores that as the new value. Thus, ``INSERT_VALUES`` is equivalent to the ``=`` operator and ``ADD_VALUES`` is equivalent to the ``+=`` operator.

The next two lines::

  	  ierr = VecAssemblyBegin(x_MPI);CHKERRQ(ierr);
  	  ierr = VecAssemblyEnd(x_MPI);CHKERRQ(ierr);

assemble the vector now that is has been changed and must be called AFTER ``VecSetValues`` is called and BEFORE the vector is used again. This call is especially important to ensure that the processors are in sync adn coordinating correctly. If one processor thinks that the value at position 3 is 6 and another thinks the value should be 7, problems will occur. Therefore, ``VecAssemblyBegin`` and ``VecAssemblyEnd`` serve to ensure that such a situation does not develop. Because the assembly process could potentially be very slow, PETSc allows computations *not involving the specific vector being assembled* to occur between ``VecAssemblyBegin`` and ``VecAssemblyEnd``.

The next two lines::

  	  ierr = PetscPrintf(PETSC_COMM_WORLD,"MPI vector x:\n");CHKERRQ(ierr);
  	  ierr = VecView(x_MPI, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

work the same to print out the vector as in the previous section. Howver, they use a different MPI *comm* and PETSc *viewer*. This time we must use ``PETSC_COMM_WORLD`` as the MPI *comm*. This will ensure that only one processor prints out the message instead of every processor. We use PETSC_VIEWER_STDOUT_WORLD in place of ``PETSC_VIEWER_STDOUT_SELF`` for the same reason.

The next line::

  	  ierr = VecDestroy(&x_MPI);CHKERRQ(ierr);

frees up the memory occupied by the vector ``x_MPI``. Remember to always destroy PETSc objects as soon as they become useless.

The last line::

  	  ierr = PetscFinalize();CHKERRQ(ierr);

should always end a PETSc program.

So now, if we look at the output of our program, can we see why the first half of the vector had the value 0 and the second half the value 1? Remember that the first half of the vector was owned by the processor of rank 0 and the second half was owned by the processor of rank 1. Since all we did was store in each position the rank number of the processor that owned it, the results hopefully make sense.

Key Functions Learned
---------------------

``PetscOptionsGetInt(const char pre[],const char name[],PetscInt *ivalue,PetscBool  *set)``
	* Gets the integer value for a particular option (option ex. "-n")
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Sys/PetscOptionsGetInt.html
``MPI_Comm_rank(MPI_Comm comm, int *rank)``
	* Determines the rank of the calling processor
	* http://www.mcs.anl.gov/research/projects/mpi/www/www3/MPI_Comm_rank.html
``VecCreateMPI(MPI_Comm comm,PetscInt n,PetscInt N,Vec *v)``
	* Creates a parallel vector; second argument is total size and second argument is local size
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecCreateMPI.html
``VecGetOwnershipRange(Vec x,PetscInt *low,PetscInt *high)``
	* Gets the starting and ending index of the vector positions owned by the processor that calls this function. Second argument is the starting index and the third argument is the ending index.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecGetOwnershipRange.html
``VecSetValues(Vec x,PetscInt ni,const PetscInt ix[],const PetscScalar y[],InsertMode iora)``
	* Adds to (ADD_VALUES) or overwrites (INSERT_VALUES) sections of a vector. The second argument specifies the number of values to be added. The third argument specifies the index of the vector where the values should be added. The fourth argument is the array of values.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecSetValues.html
``VecAssemblyBegin(Vec vec) / VecAssemblyEnd(Vec vec)``
	* These two functions must be called WHENEVER VecSetValues is called or when the INSERT_MODE is changed. If not, caching errors may occur. *TIP* If both modes need to be used for the same vector, do all of the one mode changes first, assemble the vector, then do the changes with the other mode, and then assemble the vector again.
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecAssemblyBegin.html#VecAssemblyBegin
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecAssemblyEnd.html#VecAssemblyEnd

Summary
-------

To summarize what we have learned

  - Additional function calls are required to get proper behavior with parallel programs because the processors must stay in sync for proper program execution.
  - When thinking about parallel programs, remember that each processor is running the same program but with different data.
  - Other than that, parallel PETSc and uniprocessor PETSc are surprisingly similar.
