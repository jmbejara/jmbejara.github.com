.. _PETSc_parallel_intro:

==========================
PETSc: Let's Get Parallel
==========================
The last example was meant for a single processor only which isn't all that beneficial considering that the whole point of petsc is to do things in parallel. So let's get parallel.

- If you are not already in the vector subfolder, go there now. It is in the PETSc_TutorialStuff folder that should already be in your directory.

- We compile parallel and uniprocessor programs the same way. For this example enter the following and press Enter::

	$ make vec_create_mpi

- However, running them is different. To run this executable type the following command and press Enter::

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

From here on out, we will ignore the code appearing before the main function declaration as it is very repetitive. However, it is important, especially the #define statements, so it should not be ignored by you as the programmer.

The first line of our main function::

  	  Vec x_MPI;

declares a variable of type Vec just the same as last time, just with a different name.
The next line::

  	  PetscErrorCode ierr;

declares a petsc error code variable, also just like last time.
The next line::

  	  PetscInt num_proc, istart, iend, i;

declares several PetscInts which are just like regular ints to the programmer but different for petsc.
The next line::

  	  PetscMPIInt proc_rank;

declares a PetscMPIInt which is just like a regular int to the programmer but different for petsc.
The next line::

	  PetscScalar value;

declares a PetscScalar. A PetscScalar is basically a float or a double and real or complex, depending on the situation.

If you think all of those variable declarations were tedious then just wait.

*TIP* Variables should be declared all at the top like this for every program. But it means that the variable definition section can get quite long. Use comments and whitespace to make it more readable, as with all of your code.

The first line of code that makes a function call is next::

  	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

Get used to this being the first line in the main function with a function call.

The next line::

  	  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);

gets the value that was supplied immediately after the '-n' option given at the command line. The function PetscOptionsGetInt is used to pull integer values out of the command line options. It is most useful when used as the above line demonstrates; to get the number of processors that the current program is running on.

The next line::

  	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);

is where this program begins to demonstrate noticeably different behavior on different processors. With the way MPI works, every processor involved in a single program is given a rank. The root processor is rank 0, the second processor is rank 1, etc. The program MPI_Comm_rank gets the rank for each processor and thus differs for each processor.

The next line::

  	  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,VEC_SIZE,&x_MPI);CHKERRQ(ierr);

is the parallel version of VecCreateSeq. VecCreateMPI creates a parallel vector which means that the vector is distributed over all the processors involved in the program. The first argument to the function is the MPI comm which is PETSC_COMM_WORLD in this case because we want the vector to be distributed over every processor. The second argument is the size of the local vector and the third argument is the size of the total vector. To demonstrate this, imagine we have ten marbles and five students. We wish to divide the marbles up evenly. Thus, each student would receive two marbles (size of the local vector) and the total number of marbles would be ten (size of the total vector). This does not mean, however, that the division has to be even. We could have given one of the students more marbles than another. But to spread the workload as evenly as possible, it is recommended that the second argument be PETSC_DECIDE which lets petsc evenly divide up the vector for you. The third argument is set by us and is 10 in this case. Because we have two processors, each processor will get a local vector of size 5 and petsc will decide this for us. The last argument is a pointer to the vector variable.

*TIP* This function has four arguments and it can be hard if not impossible to remember what they are and the order they should appear. Petsc has a great online manual. Use it so that you don't forget or mix up arguments in your function calls:
  	  http://www.mcs.anl.gov/petsc/petsc-current/docs/index.html

The next line::

	  ierr = VecGetOwnershipRange(x_MPI,&istart,&iend);CHKERRQ(ierr);

allows each processor to figure out the specific range of the vector that belongs to it. For the root processor, istart would be 0 and iend would be 4. For the second processor, istart would be 5 and iend would be 9. However, these indices will change if either the number of processors change or the size of the vector changes. Thus, these should NEVER be hard coded and always determined with a function call to VecGetOwnershipRange.

The next five lines::

	  for(i = istart; i < iend; i++)
  	  {
    	    value = proc_rank;
    	    ierr = VecSetValues(x_MPI,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
 	  }

iterate over the range owned by each processor and assign to each position the MPI rank of the processor that owns that position. VecSetValues inserts a vector of values (the fourth argument, value in this case) of a size given by the second argument (1 in this case) at the position specified by the third argument (i in this case) into a vector given by the first argument (x_MPI in this case). The mode for VecSetValues is given by the last argument and is INSERT_VALUES in this example. INSERT_VALUES replaces existing values with new values. The other option is ADD_VALUES which adds the existing values with the new values and stores that as the new value. Thus, INSERT_VALUES is equivalent to the '=' operator and ADD_VALUES is equivalent to the '+=' operator.

The next two lines::

  	  ierr = VecAssemblyBegin(x_MPI);CHKERRQ(ierr);
  	  ierr = VecAssemblyEnd(x_MPI);CHKERRQ(ierr);

assemble the vector now that is has been changed and MUST be called AFTER VecSetValues is called and BEFORE the vector is used again. One problem with parallel programs is that the processors have to stay synced to one another. If one processor thinks that the value at position 3 is 6 and another thinks the value should be 7, problems will occur. So what VecAssemblyBegin and VecAssemblyEnd do is sync up the processors so such a situation does not develop. Because it could take quite a while to sync up the processors, petsc allows computations NOT INVOLVING THE SPECIFIC VECTOR BEING ASSEMBLED to occur between VecAssemblyBegin and VecAssemblyEnd.

The next two lines::

  	  ierr = PetscPrintf(PETSC_COMM_WORLD,"MPI vector x:\n");CHKERRQ(ierr);
  	  ierr = VecView(x_MPI, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

work the same as with the last example to print out the vector except they use a different MPI comm and petsc viewer. This time we must use PETSC_COMM_WORLD as the MPI comm so that only one processor prints out the message instead of every processor. It is for the same reason that PETSC_VIEWER_STDOUT_WORLD is used instead of PETSC_VIEWER_STDOUT_SELF.

The next line::

  	  ierr = VecDestroy(&x_MPI);CHKERRQ(ierr);

frees up the memory occupied by the x_MPI vector. Remember to always destroy petsc objects as soon as they become useless.

The last line::

  	  ierr = PetscFinalize();CHKERRQ(ierr);

should always end a petsc program.

So now, if we look at the output of our program, can we see why the first half of the vector had the value 0 and the second half the value 1? Remember that the first half of the vector was owned by the processor of rank 0 and the second half was owned by the processor of rank 1. Since all we did was store in each position the rank number of the processor that owned it, the results hopefully make sense.

- To summarize what we have learned

  - Additional function calls are required to get proper behavior with parallel programs because the processors must stay in sync for proper program execution.
  - When thinking about parallel programs, remember that each processor is running the same program but with different data.
  - Other than that, parallel petsc and uniprocessor petsc are surprisingly similar.

Congratulations, you just compiled, ran, and hopefully even understood your first parallel petsc program!