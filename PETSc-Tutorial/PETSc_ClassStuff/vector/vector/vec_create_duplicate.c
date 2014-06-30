/* This program uses a different vector creation function that does the same thing but allows
   the user to specify the type (MPI or sequential). It then duplicates that vector as another vector
   as well as an array of vectors. This method should be used when creating multiple vectors; that is,
   creating a single vector and then duplicating it as needed rather than creating a new one from scratch
   every time another is needed.
   This code should be compiled with the command 'make vec_create_duplicate' and
   run with the command 'mpiexec -n NUM_PROC ./vec_create_duplicate [-vec_type VEC_TYPE] [-help]' [] indicates optional
   and NUM_PROC is an int that specifies how many processors this program should be run on.
   VEC_TYPE can either be 'mpi' for parallel vectors or 'seq' for sequential vectors. (defaults to mpi)
   If one wishes to use sequential vectors then NUM_PROC MUST BE 1; otherwise, the program will terminate early.
 */

/* The following message will be printed when the program is run with the '-help' option
   along with an exhaustive list of runtime options */
static char help[] = "Duplicating vectors.\n\n";

#include <petscvec.h>

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char **argv)
{
  Vec x,y; // Vector Object
  Vec *z; // Array of Vector Objects
  PetscErrorCode ierr; // Petsc Error Code
  PetscInt vec_size=10, num_proc, istart, iend, i, num_vecs_z=3; // Petsc Int
  PetscMPIInt proc_rank; // MPI Int
  PetscScalar value,one=1,two=2,three=3; // Can represent a variety of atomic numeric data types(ie float, int etc.)

  // Deals with runtime options and makes a call to MPI_Initialize
  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

  // Gets the number of processors to be used as entered on the command line
  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);

  // Gets the unique rank for each processor
  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);

  /* The following three functions allow a vector to be created and sized and then the VecSetFromOptions
   allows the command line argument '-vec_type seq' to change the vector to a uniprocessor vector. Without
   that command line argument, it defaults to an MPI vector because of the COMM used in VecCreate but that
   can easily be changed to PETSC_COMM_SELF, if desired. However, if one attempts to create a sequential
   vector with multiple processors, the program will prematurely end execution.*/
  ierr = VecCreate(PETSC_COMM_WORLD,&x);CHKERRQ(ierr);
  ierr = VecSetSizes(x,PETSC_DECIDE,vec_size);CHKERRQ(ierr);
  ierr = VecSetFromOptions(x);CHKERRQ(ierr);
  
  /* VecDuplicate only duplicates the structure of the vector (x) to another vector (y). Values are NOT copied.
     Use VecCopy to copy the contents */
  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);
  /* VecDuplicateVecs only duplicates the structure of the vector (x) to each vector in the array of vectors (z).
     Values are NOT copied. Use VecCopy to copy the contents */
  ierr = VecDuplicateVecs(x,num_vecs_z,&z);CHKERRQ(ierr);

  // This for loop sets each vector element equal to the rank of the processor that owns it
  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
  for(i = istart; i < iend; i++)
  {
    value = proc_rank;
    // Sets 1 value (value) at a time at index i. INSERT_VALUES overwrites previous value
    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
  }
  // We used VecSetValues on x so we must assemble the vector
  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);

  // Use VecSet to easily and quickly set all the values of these vectors
  ierr = VecSet(y,one);CHKERRQ(ierr);
  ierr = VecSet(z[0],one);CHKERRQ(ierr);
  ierr = VecSet(z[1],two);CHKERRQ(ierr);
  ierr = VecSet(z[2],three);CHKERRQ(ierr);

  // Print vector x
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  
  // Print vector y
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CHKERRQ(ierr);
  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Prints out the vectors of array z.  Use standard c array notation (brackets and zero based)
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[0]:\n");CHKERRQ(ierr);
  ierr = VecView(z[0], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[1]:\n");CHKERRQ(ierr);
  ierr = VecView(z[1], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z[2]:\n");CHKERRQ(ierr);
  ierr = VecView(z[2], PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Free the memory and destroy the vectors x and y
  ierr = VecDestroy(&x);CHKERRQ(ierr);
  ierr = VecDestroy(&y);CHKERRQ(ierr);
  // Free the memory and destroy each vector that is in the array z
  ierr = VecDestroyVecs(num_vecs_z,&z);CHKERRQ(ierr);
  
  // Deals with options that apply at the end of program execution and calls MPI_Finalize
  ierr = PetscFinalize();CHKERRQ(ierr);
  return 0;
}
