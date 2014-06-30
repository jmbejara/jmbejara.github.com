.. _PETSc_vec_operations:

=================
PETSc: Operations
=================
In the last two sections we learned the most basic functions in PETSc--how to assemble vectors in serial and in parallel.  In additiona, we learned how to size them, how to change the values stored in the vector--either over the whole vector or at an individual position--and we even learned how to duplicate vectors. However, in this section we will begin learning how to make use of this, starting with the various operations that we can perform on our vectors. 

Directions
----------

Run the tutorial code with the follwoing directions:

- If you are not already in the vector subfolder, go there now. It is in the PETSc_TutorialStuff folder that should already be in your directory.

- To compile the program for this section, enter the following and press <Enter>::

	$ make vec_operations

- To run the executable type the following command and press <Enter>::

	$ mpiexec -n 2 ./vec_operations

- The output should appear as follows::

	Vector x:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	0
	1
	2
	3
	4
	Process [1]
	5
	6
	7
	8
	9
	Vector y:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	3	
	3	
	3
	3
	3
	Process [1]
	3
	3
	3
	3
	3
	Vector z:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	2
	2
	2
	2
	2
	Process [1]
	2
	2
	2
	2
	2
	x dot y: 135.000000
	sum x(i) for each i: 45.000000
	NORM_1 of x: 45.000000
	Reciprocal of x:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	0
	1
	0.5
	0.333333
	0.25
	Process [1]
	0.2
	0.166667
	0.142857
	0.125
	0.111111
	VecScale(z=a*z) z*3:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	6
	6
	6
	6
	6
	Process [1]
	6
	6
	6
	6
	6
	
	
Explanation of Code
-------------------

Now lets take a look at the code::
	
	#include <petscvec.h>
	#undef __FUNCT__
	#define __FUNCT__ "main"
	int main(int argc, char **argv)
	{
	  Vec x,y,z;
	  PetscErrorCode ierr;
	  PetscInt vec_size=10, num_proc, istart, iend, i;
	  PetscMPIInt proc_rank;
	  PetscScalar value,one=1,two=2,three=3,r;
	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);
	  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,vec_size,&x);CHKERRQ(ierr);
	  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);
	  ierr = VecDuplicate(x,&z);CHKERRQ(ierr);
	  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
	  for(i = 0; i < vec_size; i++)
	  {
	    value = i;
	    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);
	  ierr = VecSet(y,three);CHKERRQ(ierr);
	  ierr = VecSet(z,two);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CHKERRQ(ierr);
	  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z:\n");CHKERRQ(ierr);
	  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = VecTDot(x,y,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"x dot y: %f\n",r);CHKERRQ(ierr);
	  ierr = VecSum(x,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"sum x(i) for each i: %f\n",r);CHKERRQ(ierr);

	  ierr = VecNorm(x,NORM_1,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"NORM_1 of x: %f\n",r);CHKERRQ(ierr);
	  ierr = VecReciprocal(x);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Reciprocal of x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
 	  ierr = VecScale(z,three);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"VecScale(z=a*z) z*3:\n");CHKERRQ(ierr);
	  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = VecDestroy(&x);CHKERRQ(ierr);
	  ierr = VecDestroy(&y);CHKERRQ(ierr);
	  ierr = VecDestroy(&z);CHKERRQ(ierr);
	  ierr = PetscFinalize();
 	 return 0;
	}

The first five lines of our main function::

	  Vec x,y,z; // Vector Objects
	  PetscErrorCode ierr; // PETSc Error Code
	  PetscInt vec_size=10, num_proc, istart, iend, i; // PETSc Int
	  PetscMPIInt proc_rank; // MPI Int
	  PetscScalar value,one=1,two=2,three=3,r;

declares the variables that our program will use. We have seen all of these variables before.

The next line::

	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

is always the first function call we make.

The next fifteen lines of our program::

	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);
	  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,vec_size,&x);CHKERRQ(ierr);
	  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);
	  ierr = VecDuplicate(x,&z);CHKERRQ(ierr);
	  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
	  for(i = 0; i < vec_size; i++)
	  {
	    value = i;
	    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);
	  ierr = VecSet(y,three);CHKERRQ(ierr);
	  ierr = VecSet(z,two);CHKERRQ(ierr);

are a nice combination of the various things we have learned in previous sections. Try to understand this code snippet yourself. If any of these functions look unfamiliar, consult with the previous sections of this tutorial. In essence, this snippet creates a parallel vector of size 10 and then duplicates it twice for a total of three vectors. It then takes the first vector and sets each position equal to its positional index (i.e. position 4 is set to a value of 4). It then assembles the first vector and finally uses ``VecSet`` to set all of y's values to be three and all of z's values to be two.

The next six lines of code::

	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CHKERRQ(ierr);
	  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z:\n");CHKERRQ(ierr);
	  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

print out the original contents of the vectors.

Now we get to start doing operations on our vectors. The next two lines of code::

	  ierr = VecTDot(x,y,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"x dot y: %f\n",r);CHKERRQ(ierr);

first calculates the dot product of x and y and then prints out the result.


The next two lines of code::

	  ierr = VecSum(x,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"sum x(i) for each i: %f\n",r);CHKERRQ(ierr);

first sums all the values contained in vector x and then prints out the result.

The next two lines of code::

	  ierr = VecNorm(x,NORM_1,&r);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"NORM_1 of x: %f\n",r);CHKERRQ(ierr);

first calculates the 1-Norm of vector x and then prints out the result.

The next three lines of code::

	  ierr = VecReciprocal(x);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Reciprocal of x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

takes the multiplicative inverse of each position of vector x and stores it back to the vector x and then prints out the new x vector.

The next three lines of code::

 	  ierr = VecScale(z,three);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"VecScale(z=a*z) z*3:\n");CHKERRQ(ierr);
	  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

Multiplies each position in vector z by a scalar (3 in this case) and stores the result back to z. It then prints out the new z vector.

The final lines of code::

	  ierr = VecDestroy(&x);CHKERRQ(ierr);
	  ierr = VecDestroy(&y);CHKERRQ(ierr);
	  ierr = VecDestroy(&z);CHKERRQ(ierr);
	  ierr = PetscFinalize();CHKERRQ(ierr);

free up the memory that was occupied by the three and vectors and then ``PetscFinalize`` is called so that the program can end execution properly.

Key Functions Learned
---------------------

``VecTDot(Vec x,Vec y,PetscScalar *val)``
	  * Calculates x dot y and stores the result in val
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecTDot.html

``VecSum(Vec v,PetscScalar *sum)``
	  * Sums every value contained in vector v and stores the result in sum
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecSum.html

``VecNorm(Vec x,NormType type,PetscReal *val)``
	  * Calculates the norm (type specified by type) of vector x and stores the result in val
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecNorm.html

``VecReciprocal(Vec vec)``
	  * Takes the multiplicative inverse of every vector position of vec and stores it back to the same position
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecReciprocal.html

``VecScale (Vec x, PetscScalar alpha)``
	  * Multiplies every position of x by alpha and stores the result back to the same position in x
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecScale.html

Summary
-------

This is only a small sample of the many vector operations that PETSc provides. An exhaustive list can be found at: http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/index.html

Hopefully this section of the tutorial has demonstrated the ease with which operations can be done on vectors. You could write your own functions to do these sorts of calculations but PETSc provides many already and they are very efficient so try to use PETSc functions for everything, when possible.

This completes a short section on vector operations in PETSc. You now know how to create vectors, both parallel and sequential, given them properties, duplicate them, give them values, print out their contents, and do operations on them.