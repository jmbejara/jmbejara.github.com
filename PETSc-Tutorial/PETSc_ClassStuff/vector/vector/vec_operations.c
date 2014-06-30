/* This program creates three vectors and then performs a few basic operations on them.
   An exhaustive list of the various vector options can be found on page 44 of the PETSc
   Users Manual (at least, for the 3.2 Revision).
   This code should be compiled with the command 'make vec_operations' and
   run with the command 'mpiexec -n NUM_PROC ./vec_operations [-help]' [] indicates optional
   and NUM_PROC is an int that specifies how many processors this program should be run on.
 */

/* The following message will be printed when the program is run with the '-help' option
   along with an exhaustive list of runtime options */
static char help[] = "Some of the many vector operations.\n\n";

#include <petscvec.h>

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char **argv)
{
  Vec x,y,z; // Vector Objects
  PetscErrorCode ierr; // Petsc Error Code
  PetscInt vec_size=10, num_proc, istart, iend, i; // Petsc Int
  PetscMPIInt proc_rank; // MPI Int
  PetscScalar value,one=1,two=2,three=3,r; // Can represent a variety of atomic numeric data types(ie float, int etc.)


  // Configures runtime options and sets up MPI
  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

  /* Gets the number following the '-n' option which is the number of processors
     that this program will be run on */
  ierr = PetscOptionsGetInt(PETSC_NULL,"-n",&num_proc,PETSC_NULL);CHKERRQ(ierr);
  
  /* Gets the MPI rank of each processor. It's important to remember when writing programs
     with PETSc that use MPI that the program gets run across multiple processors and thus
     each processor has its own variables. Each processor can be uniquely identified by its
     rank. MPI_Comm_rank gets the rank of each processor. */
  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&proc_rank);CHKERRQ(ierr);
  
  /* Creates a parallel vector. We let PETSC_DECIDE how to divide the vector between processors
     but we specify the total size. (vec_size in this case) */
  ierr = VecCreateMPI(PETSC_COMM_WORLD,PETSC_DECIDE,vec_size,&x);CHKERRQ(ierr);
  
  // Copies the structure of x to y and z, not the contents.  Use VecCopy for that.
  ierr = VecDuplicate(x,&y);CHKERRQ(ierr);
  ierr = VecDuplicate(x,&z);CHKERRQ(ierr);

  // This loop sets each value of the vector x equal to its index
  ierr = VecGetOwnershipRange(x,&istart,&iend);CHKERRQ(ierr);
  for(i = 0; i < vec_size; i++)
  {
    value = i;
    ierr = VecSetValues(x,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
  }
  // We called VecSetValues on x so we must assemble x.
  ierr = VecAssemblyBegin(x);CHKERRQ(ierr);
  ierr = VecAssemblyEnd(x);CHKERRQ(ierr);

  // Set all the values of a vector with VecSet
  ierr = VecSet(y,three);CHKERRQ(ierr);
  ierr = VecSet(z,two);CHKERRQ(ierr);

  // Print the vector x
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector x:\n");CHKERRQ(ierr);
  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  
  // Print the vector y
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector y:\n");CHKERRQ(ierr);
  ierr = VecView(y, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Print the vector z
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Vector z:\n");CHKERRQ(ierr);
  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Take the regular(noncomplex) dot product of x and y
  ierr = VecTDot(x,y,&r);CHKERRQ(ierr);
  // Print the result of x dot y
  ierr = PetscPrintf(PETSC_COMM_WORLD,"x dot y: %f\n",r);CHKERRQ(ierr);

  // Sum all the elements of x
  ierr = VecSum(x,&r);CHKERRQ(ierr);
  // Print the sum of all the elements of x
  ierr = PetscPrintf(PETSC_COMM_WORLD,"sum x(i) for each i: %f\n",r);CHKERRQ(ierr);

  // Calculate the NORM_1 of the vector x
  ierr = VecNorm(x,NORM_1,&r);CHKERRQ(ierr);
  // Print the result of the NORM_1 of the vector x
  ierr = PetscPrintf(PETSC_COMM_WORLD,"NORM_1 of x: %f\n",r);CHKERRQ(ierr);

  // Take the multiplicative inverse of every element of x and store it back to x
  ierr = VecReciprocal(x);CHKERRQ(ierr);
  // Print the new vector x, with every element the multiplicative inverse of its previous value
  ierr = PetscPrintf(PETSC_COMM_WORLD,"Reciprocal of x:\n");CHKERRQ(ierr);
  ierr = VecView(x, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Multiply every element in z by a scalar (3 in this case)
  ierr = VecScale(z,three);CHKERRQ(ierr);
  // Print the vector z where every element has been multiplied by a scalar (3 in this case)
  ierr = PetscPrintf(PETSC_COMM_WORLD,"VecScale(z=a*z) z*3:\n");CHKERRQ(ierr);
  ierr = VecView(z, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

  // Free memory and destroy x, y, and z
  ierr = VecDestroy(&x);CHKERRQ(ierr);
  ierr = VecDestroy(&y);CHKERRQ(ierr);
  ierr = VecDestroy(&z);CHKERRQ(ierr);
  
  // Deals with options that apply at the end of program execution and calls MPI_Finalize
  ierr = PetscFinalize();
  return 0;
}
