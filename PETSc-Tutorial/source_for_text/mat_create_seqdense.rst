.. _PETSc_mat_create_seqdense:

=================
PETSc: Matrices
=================
This is the second PETSc tutorial. This tutorial will explain the basics of matrix creation and operations. This section will demonstrate the most basic PETSc matrix, the sequential dense matrix.

Directions
----------

Run the tutorial code with the following directions:

- Go to the matrix folder. It is in the PETSc_TutorialStuff folder that should already be in your directory.

- To compile the program for this section, enter the following and press <Enter>::

	$ make mat_create_seqdense

- To run the executable type the following command and press <Enter>::

	$ ./mat_create_seqdense

- The output should appear as follows::

	A =
	Matrix Object: 1 MPI processes
	  type: seqdense
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00	
	0.0000000000000000e+00 1.0000000000000000e+00 2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00
	0.0000000000000000e+00 2.0000000000000000e+00 4.0000000000000000e+00 6.0000000000000000e+00 8.0000000000000000e+00 1.0000000000000000e+01
	0.0000000000000000e+00 3.0000000000000000e+00 6.0000000000000000e+00 9.0000000000000000e+00 1.2000000000000000e+01 1.5000000000000000e+01
	0.0000000000000000e+00 4.0000000000000000e+00 8.0000000000000000e+00 1.2000000000000000e+01 1.6000000000000000e+01 2.0000000000000000e+01
	0.0000000000000000e+00 5.0000000000000000e+00 1.0000000000000000e+01 1.5000000000000000e+01 2.0000000000000000e+01 2.5000000000000000e+01 
	
	
Explanation of Code
-------------------

Now lets take a look at the code::

	int main(int argc,char **argv)
	{
	  Mat            A;
	  PetscScalar    value;
	  PetscErrorCode ierr;
	  PetscInt       i,j;
	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
	  ierr = MatCreateSeqDense(PETSC_COMM_SELF,NUM_ROWS,NUM_COLUMNS,PETSC_NULL,&A);CHKERRQ(ierr);
	  for(i = 0; i < NUM_ROWS; i++)
	  {
	    for(j = 0; j < NUM_COLUMNS; j++)
	    {
	      value = i*j;
	      ierr = MatSetValue(A,i,j,value,INSERT_VALUES);CHKERRQ(ierr);
	    }
	  }
	  ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_SELF,"A =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_SELF);CHKERRQ(ierr);
	  ierr = MatDestroy(&A);CHKERRQ(ierr);
	  ierr = PetscFinalize();CHKERRQ(ierr);
	  return 0;
	}

The first four lines of our program::

	  Mat            A;
	  PetscScalar    value;
	  PetscErrorCode ierr;
	  PetscInt       i,j;

declare all the variables that our program will use. The only new one is Mat which declares our matrix variable.

Next we call ``PetscInitialize()`` as usual::

	  ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

The next line::

	  ierr = MatCreateSeqDense(PETSC_COMM_SELF,NUM_ROWS,NUM_COLUMNS,PETSC_NULL,&A);CHKERRQ(ierr);

creates our sequential dense matrix. The matrix is "dense" because it is uncompressed. The PETSc communicator is PETSC_COMM_SELF because it is sequential. The matrix is of size NUM_ROWS by NUM_COLUMNS. The fourth argument is PETSC_NULL because we are choosing to let PETSc allocate space for our matrix. The last argument is a pointer to the variable that will "represent" our matrix.

The next eight lines of code::

	  for(i = 0; i < NUM_ROWS; i++)
	  {
	    for(j = 0; j < NUM_COLUMNS; j++)
	    {
	      value = i*j;
	      ierr = MatSetValue(A,i,j,value,INSERT_VALUES);CHKERRQ(ierr);
	    }
	  }

iterate over all the positions of our matrix and use ``MatSetValue()`` to assign the product of the indices of each position to that position.

Because we called ``MatSetValue()`` we must then assemble the matrix::

	  ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);

The next two lines of code::

	  ierr = PetscPrintf(PETSC_COMM_SELF,"A =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_SELF);CHKERRQ(ierr);

print out the matrix along with the matrix's variable name.

Because we are now done with our matrix, we destroy the matrix::

	  ierr = MatDestroy(&A);CHKERRQ(ierr);

to free up the memory associated with it.

Then we can call::

	  ierr = PetscFinalize();CHKERRQ(ierr);

and return a value::

	  return 0;

to end our program.

Key Functions Learned
---------------------

``MatCreateSeqDense(MPI_Comm comm,PetscInt m,PetscInt n,PetscScalar *data,Mat *A)``
	  * Creates an m by n matrix that is uniprocessor and uncompressed. data is the memory that should be associated with the matrix. Supply PETSC_NULL as the argument is petsc should handle memory allocation ie. you can create your own matrix out of a c matrix and then incorporate into a PETSC matrix or let PETSC allocate the memory for the matrix for you
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatCreateSeqDense.html
``*MatSetValue(Mat mat,PetscInt m,PetscInt n,PetscScalar value,InsertMode mode)*``
	  * Either adds value to (if mode is ADD_VALUES) or sets as value (if mode is INSERT_VALUES) position m by n of matrix mat
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatSetValue.html
``*MatAssemblyBegin(Mat mat,MatAssemblyType type)*``
	  * Similar to ``VecAssemblyBegin()``. Must be called after ``MatSetValue(s)()`` to avoid cache errors. Set type as MAT_FINAL_ASSEMBLY when done with calls to ``MatSetValue(s)()`` and set type as MAT_FLUSH_ASSEMBLY when switching insert mode for ``MatSetValue(s)()``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatAssemblyBegin.html
``*MatAssemblyEnd(Mat mat,MatAssemblyType type)*``
	  * Similar to ``VecAssemblyEnd()``. type argument should match the type argument of the corresponding ``MatAssemblyBegin()``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatAssemblyEnd.html#MatAssemblyEnd
``*MatView(Mat mat,PetscViewer viewer)*``
	  * Displays the matrix. The viewer argument specifies how. If the viewer is  PETSC_VIEWER_STDOUT_SELF then every processor displays the entire matrix. If the viewer is PETSC_VIEWER_STDOUT_WORLD then only the first processor displays the matrix. Finally, if the viewer is PETSC_VIEWER_DRAW_WORLD then a graphical structure is displayed (you must have an X window already open for this to work)
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatView.html
``*MatDestroy(Mat *A)*``
	  * Deallocates the memory associated with matrix A
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatDestroy.html


Summary
-------

Hopefully this demonstrated how easy it is to switch between PETSc objects. The function names for vectors and matrices are very similar and the way you create them, use them, and then destroy them is very similar. Congratulations, you have just compiled, ran, and hopefully even understood a program dealing with the second major PETSc object!