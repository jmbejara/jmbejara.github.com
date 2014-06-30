/* This program is similar to vec_create_seq except that the vector is distributed
   over several or many processors. This program creates a parallel vector, assigns
   the processor rank to the local portion of the created vector and then prints it out.
   This code should be compiled with the command 'make vec_create_mpi' and
   run with the command 'mpiexec -n NUM_PROC ./vec_create_mpi [-help]' [] indicates optional
   and NUM_PROC is an int that specifies how many processors this program should be run on.
 */

/* The following message will be printed when the program is run with the '-help' option
   along with an exhaustive list of runtime options */
static char help[] = "Creating a parallel vector.\n\n";

#include <petscvec.h>

#define VEC_SIZE 10

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char **argv)
{
  Vec x_MPI; // Vector Object
  PetscErrorCode ierr; // Petsc Error Code
  PetscInt num_proc, istart, iend, i; // Petsc Int
  PetscMPIInt proc_rank; // MPI Int
  PetscScalar value; // Can represent a variety of atomic numeric data types(ie float, int etc.)
  
  // Configures runtime options and sets up MPI
  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

  /* Gets the number following the '-n' option which is the number of processors
     that this program will be run on */
  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
  
  /* Gets the MPI rank of each processor. It's important to remember when writing programs
     with PETSc that use MPI that the program gets run across multiple processors and thus
     each processor has its own variables. Each processor can be uniquely identified by its
     rank. MPI_Comm_rank gets the rank of each processor. */
  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);
  
  /* Creates a parallel vector. We let PETSC_DECIDE how to divide the vector between processors
     but we specify the total size. (vec_size in this case) */
  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,VEC_SIZE,&x_MPI);CHKERRQ(ierr);
  
  /* VecGetOwnershipRange returns the starting and ending indices that enclose the portion
     of the vector that each process owns. */
  ierr = VecGetOwnershipRange(x_MPI,&istart,&iend);CHKERRQ(ierr);
  
  // This for loop sets each vector element equal to the rank of the processor that owns it
  for(i = istart; i < iend; i++)
  {
    value = proc_rank;

    /* VecSetValues can set 1 or more values. The '1' specifies the number of elements being
     added. The '&i' specifies the index to begin setting values at. '&value' is the value(s)
     to be set. In this example we use INSERT_VALUES which overwrites whatever was previously
     there. The other option is ADD_VALUES which adds to whatever was already there instead of
     just overwriting.*/
    ierr = VecSetValues(x_MPI,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
  }
  /* Any time VecSetValues is called the vector must be assembled so that the vector object
     does not get put into an inconsistent state. Code not related to the vector being assembled
     can be put between calls to VecAssemblyBegin and VecAssemblyEnd. Calls to VecSetValues between
     assembly calls must use either INSERT_VALUES or ADD_VALUES. They CANNOT be mixed.
  */
  ierr = VecAssemblyBegin(x_MPI);CHKERRQ(ierr);
  // Code not related to the vector x_MPI can be placed here, if desired.
  ierr = VecAssemblyEnd(x_MPI);CHKERRQ(ierr);
  
  // Prints out the vector
  ierr = PetscPrintf(PETSC_COMM_WORLD,"MPI vector x:");CHKERRQ(ierr);
  ierr = VecView(x_MPI, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  
  // Frees the memory associated with vector x_MPI and deletes it from the program
  ierr = VecDestroy(&x_MPI);CHKERRQ(ierr);
  
  // Deals with options that apply at the end of program execution and calls MPI_Finalize
  ierr = PetscFinalize();CHKERRQ(ierr);
  return 0;
}
