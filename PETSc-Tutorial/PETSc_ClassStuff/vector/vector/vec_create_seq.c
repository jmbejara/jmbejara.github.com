/* This is a simple uniprocessor example that demonstrates creating a vector,
   assigning the same value to every element and finally printing it out.
   This code should be compiled with the command 'make vec_create_seq' and
   run with the command 'mpiexec -n 1 ./vec_create_seq [-help]' [] indicates optional
 */

/* The following message will be printed when the program is run with the '-help' option
   along with an exhaustive list of runtime options */
static char help[] = "Creating a sequential vector.\n\n";

#include <petscvec.h>

#define VEC_SIZE 10 // Can be changed
#define VEC_DEFAULT_VALUE 3 // Can be changed

#undef __FUNCT__
#define __FUNCT__ "main"
int main(int argc, char **argv)
{
  Vec x_Seq; // Vector Object
  PetscErrorCode ierr; // Petsc Error Code (for tracking when something goes wrong)
  
  /* PetscInitialize is a VITAL function call. It performs a number of
     important options handling as well as calling MPI_Init(), if needed */
  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
 
  // Creates a sequential (uniprocessor) vector called x_Seq of size VEC_SIZE
  ierr = VecCreateSeq(PETSC_COMM_SELF,VEC_SIZE,&x_Seq);CHKERRQ(ierr);
  
  // VecSet sets every value in a given vector to the value specified (3 in this case)
  ierr = VecSet(x_Seq,VEC_DEFAULT_VALUE);
  
  /* PetscPrintf works much like the c std lib's printf. The main difference
   is that you must specify the MPI_COMM. In this case, we call it with
   PETSC_COMM_SELF because this is a uniprocess example. */
  ierr = PetscPrintf(PETSC_COMM_SELF,"Seq vector x:\n");CHKERRQ(ierr);
  
  /* VecView prints out a vector. The VIEWER must be specified. This is a
     uniprocessor example so we call it with PETSC_VIEWERD_STDOUT_SELF. */
  ierr = VecView(x_Seq, PETSC_VIEWER_STDOUT_SELF);CHKERRQ(ierr);
  
  // VecDestroy destroys a vector obect.
  ierr = VecDestroy(&x_Seq);CHKERRQ(ierr);
  
  // This function complements the functionality of PetscInitialize and is equally important
  ierr = PetscFinalize();CHKERRQ(ierr);
  return 0;
}
	
