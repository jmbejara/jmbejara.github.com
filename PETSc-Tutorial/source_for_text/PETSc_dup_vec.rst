.. _PETSc_dup_vec:

=================================
PETSc: Creating Duplicate Objects
=================================
Petsc programs will often consist of many different PETSc objects as well as a large number of each type of object. Depending on the object, it can take a lot of work to create it. Therefore, it will be useful for us to learn how to quickly create duplicates of PETSc objects. 

Directions
----------

We will learn how to duplicate vectors in this section:

- If you are not already in the vector subfolder, go there now. It is in the ``PETSc_TutorialStuff`` folder that should already be in your directory.

- To compile the program for this section, type the following command and press Enter::

	$ make vec_create_duplicate

- To run this executable type the following command and press Enter::

	$ mpiexec -n 2 ./vec_create_duplicate

- The output should appear as follows::

	Vector x:
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
	Vector y:
	Vector Object: 2 MPI processes
	  type: mpi	
	Process [0]	
	1	
	1
	1
	1
	1
	Process [1]
	1
	1
	1
	1
	1
	Vector z[0]:
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	1
	1
	1
	1
	1
	Process [1]
	1
	1
	1
	1
	1
	Vector z[1]:
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
	Vector z[2]:
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

Explanation of Code
-------------------
	
Now lets take a look at the code::

	#include <petscvec.h>
	#undef __FUNCT__
	#define __FUNCT__ "main"
	int main(int argc, char **argv)
	{
	  Vec x,y;
	  Vec *z;
	  PetscErrorCode ierr;
	  PetscInt vec_size=10, num_proc, istart, iend, i, num_vecs_z=3;
	  PetscMPIInt proc_rank;
	  PetscScalar value,one=1,two=2,three=3;
	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);
	  ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
	  ierr = VecSetSizes(x,PETSC_DECIDE,vec_size);CHKERRQ(ierr);
	  ierr = VecSetFromOptions(x);CHKERRQ(ierr);
	  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);
	  ierr = VecDuplicateVecs(x,num_vecs_z,&z);CHKERRQ(ierr);
	  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
	  for(i = istart; i < iend; i++)
	  {
	    value = proc_rank;
	    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);
	  ierr = VecSet(y,one);CHKERRQ(ierr);
	  ierr = VecSet(z[0],one);CHKERRQ(ierr);
	  ierr = VecSet(z[1],two);CHKERRQ(ierr);
	  ierr = VecSet(z[2],three);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CH	KERRQ(ierr);
	  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[0]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[0], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[1]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[1], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[2]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[2], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = VecDestroy(&x);CHKERRQ(ierr);
	  ierr = VecDestroy(&y);CHKERRQ(ierr);
	  ierr = VecDestroyVecs(num_vecs_z,&z);CHKERRQ(ierr);
	  ierr = PetscFinalize();CHKERRQ(ierr);
	  return 0;
	}

The first six lines of the main function::

	  Vec x,y;
	  Vec *z;
	  PetscErrorCode ierr;
	  PetscInt vec_size=10, num_proc, istart, iend, i, num_vecs_z=3;
	  PetscMPIInt proc_rank;
	  PetscScalar value,one=1,two=2,three=3;

declare the variables that this program will make use of. Two things are of interest. Notice how this program does not have pre-defined constants. Instead, it just uses regular variables. This is an alternative to pre-defined constants but pre-defined constants are usually better. Also, we declared not only two ``Vec`` objects, but also a pointer to a ``Vec`` object. If you are familiar with C, then you hopefully will recognize that as the way to declare an array of something. So in this case, z is a pointer to an array of ``Vec`` objects.

The next three lines::

	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);

were in our last program. The first line is the function that sets everything up for our program. The second line gets the number of processors that our program is running on. The third line gets the rank of each processor (remember that this differs for each processor whereas the total number of processors is the same on each processor).

The next three lines::

	  ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
	  ierr = VecSetSizes(x,PETSC_DECIDE,vec_size);CHKERRQ(ierr);
	  ierr = VecSetFromOptions(x);CHKERRQ(ierr);

do basically the same thing as ``VecCreateSeq`` or ``VecCreateMPI`` except the type (sequential or parallel) is decided at run-time rather than compile-time. These three functions should usually be used rather than ``VecCreateSeq`` or ``VecCreateMPI`` because they are more general functions. The first line creates the vector but doesn't specify anything about the vector. The second function sizes the vector. Remember that ``PETSC_DECIDE`` tells PETSc to decide how to split up the vector between the available processors and that ``vec_size`` is the total size of the vector. The third and final line tells PETSc to use the command line options to specify characteristics of the vector. The function ``VecSetFromOptions`` becomes more useful as the program becomes more advanced and details regarding specifying options at run-time will be covered later.

The next line::

	  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);

is how we duplicate a single vector. Notice how the first argument is the vector that acts as the template and the second argument is a pointer to the vector that will assume the same characteristics as the first vector. Notice that I said characteristics, not contents. There is a vector copy operation. *This is not a vector copy operation*. Rather, this function formats another vector to have similar properties (memory allocation, type, size) as a vector that has already been formatted. We could have just as easily done the three function calls for the y vector as we already did for the x vector and if the y vector was going to be different in properties then we would have to. But since x and y will differ only in contents, it is much easier to just use VecDuplicate to specify the properties of y. Hopefully you can imagine why vectors would have similar properties. If not, imagine that we were solving a linear system Ax = b where the only thing that changed was the b vector. We could easily use ``VecDuplicate`` to create a bunch of different b vectors all with the same properties.

Another way to create a bunch of similarly propertied vectors is shown by the next line of code::

	  ierr = VecDuplicateVecs(x,num_vecs_z,&z);CHKERRQ(ierr);

Rather than have separate vector variables for all of our b vectors, we can just have an array of vectors. Once again, the first argument is the vector that will serve as the template. The second argument specifies the number of vectors that we wish to have in our array. The final argument is the vector pointer that represents our array of vectors. So now we have an array of vectors. It is natural to ask if this is what constitutes a matrix in PETSc. *An array of vectors is NOT a matrix in PETSc*. PETSc matrices will be covered later and have several important differences. Think of an array of vectors as a logical grouping of distinct vectors.

The next eight lines of code::

	  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
	  for(i = istart; i < iend; i++)
	  {
	    value = proc_rank;
	    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);

are taken directly from the last program. Hopefully you still understand what they do. If not, they are fully explained in the last tutorial section.

The next four lines of code give values to every position in y and in the three vectors of z.

	  ierr = VecSet(y,one);CHKERRQ(ierr);
	  ierr = VecSet(z[0],one);CHKERRQ(ierr);
	  ierr = VecSet(z[1],two);CHKERRQ(ierr);
	  ierr = VecSet(z[2],three);CHKERRQ(ierr);

The first line we have seen before. Notice for the last three lines how the function call is made identically even though the vector is part of an array. This is C so to access a single member of an array, just use array notation. 'z' is just a pointer so the second line could have been written as::

	  ierr = VecSet(*z,one);CHKERRQ(ierr);

The next ten lines::

	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
	  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CH	KERRQ(ierr);
	  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[0]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[0], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[1]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[1], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[2]:\n");CHKERRQ(ierr);
	  ierr = VecView(z[2], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

print out the five vectors we have created. Again, notice the C array notation.

Now that we are done with our vectors we need to delete them. The next two lines::

	  ierr = VecDestroy(&x);CHKERRQ(ierr);
	  ierr = VecDestroy(&y);CHKERRQ(ierr);

should be familiar. But how do we delete our array of vectors? Might it be::

	  ierr = VecDestroy(&z[0]);CHKERRQ(ierr);
	  ierr = VecDestroy(&z[1]);CHKERRQ(ierr);
	  ierr = VecDestroy(&z[2]);CHKERRQ(ierr);

The designers of PETSc could have chosen this syntax. But what if you have 100 vectors in your array? So instead they chose to make it a single function call regardless of the size of your array::

	  ierr = VecDestroyVecs(num_vecs_z,&z);CHKERRQ(ierr);

Notice that for an array of vectors we must specify first the number of vectors in array that is being deleted. Luckily, we are not using magic numbers so if we change the size of z, we don't have to search through our code and replace every occurrence of the size of z.

Our last line of code::

	  ierr = PetscFinalize();CHKERRQ(ierr);

finishes up our program.

Key Functions Learned
---------------------

``VecCreate(MPI_Comm comm, Vec *vec)``
	* Creates an empty vector object. The type *MUST* be set with ``VecSetType()`` or ``VecSetFromOptions()`` before the vector can be used 
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecCreate.html
``VecSetSizes(Vec v, PetscInt n, PetscInt N)``
	* Sets the local size (n) and global size (N) of vector v
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecSetSizes.html
``VecSetFromOptions(Vec vec)``
	* Uses the command line options to set the type of the vector vec
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecSetFromOptions.html
``VecDuplicate(Vec v,Vec *newv)``
	* Creates a new vector, newy, with an identical format (size, type, memory allocation) as vector v. *NOTE* This function does not copy the contents. Use ``VecCopy()`` to copy contents of vectors
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecDuplicate.html
``VecDuplicateVecs(Vec v,PetscInt m,Vec *V[])``
	* Similar to ``VecDuplicate()`` except that it creates an array of new vectors. The number of new vectors to create is specified by m
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecDuplicateVecs.html#VecDuplicateVecs
``VecDestroyVecs(PetscInt m,Vec *vv[])``
	* Similar to ``VecDestroy()`` except that an array of vectors is destroyed. The number of vectors is specified by m
	* http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Vec/VecDestroyVecs.html#VecDestroyVecs

Summary
-------

So, to summarize:

  - It can be a lot of work to set up a PETSc object so if we need several PETSc objects of the same properties, we can use VecDuplicate or VecDuplicateVecs to quickly format additional vectors as needed.

  - Arrays of PETSc objects behave much like any kind of c array but function calls that use arrays of PETSc objects are sometimes different than function calls that use a single PETSc object.

Congratulations, you just compiled, ran, and hopefully even understood your first PETSc program that duplicates PETSc objects!