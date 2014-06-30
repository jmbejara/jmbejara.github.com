.. _PETSc_mat_create_mpi:

========================================
PETSc: Parallel Matrices - Dense and AIJ
========================================
Next we will introduce the parallel dense matrix and the AIJ dense matrix. Just as the parallel vector is divided among two or more processors, so too is the parallel matrix. 

Directions
----------

Run the tutorial code with the following directions:

- Go to the matrix folder, if you are not already there. It is in the PETSc_TutorialStuff folder that should already be in your directory.

- To compile the program for this section, enter the following and press <Enter>::

	$ make mat_create_mpi

- To run the executable type the following command and press <Enter>::

	$ mpiexec -n 3 ./mat_create_mpi

- The output should appear as follows::

	Dense =
	Matrix Object: 1 MPI processes
  	type: mpidense
	0.0000000000000000e+00 1.0000000000000000e+00 2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00
	1.0000000000000000e+00 2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00
	2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01
	4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01
	5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01
	6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01
	8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01 1.5000000000000000e+01 1.6000000000000000e+01
	9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01 1.5000000000000000e+01 1.6000000000000000e+01 1.7000000000000000e+01
	1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01 1.5000000000000000e+01 	1.6000000000000000e+01 1.7000000000000000e+01 1.8000000000000000e+01
	AIJ =
	Matrix Object: 1 MPI processes
	  type: mpiaij
	row 0: (0, 0)  (1, 0)  (2, 0)  (3, 0)  (4, 0)  (5, 0)  (6, 0)  (7, 0)  (8, 0)
	row 1: (0, 0)  (1, 0)  (2, 0)  (3, 0)  (4, 0)  (5, 0)  (6, 0)  (7, 0)  (8, 0)
	row 2: (0, 0)  (1, 0)  (2, 0)  (3, 0)  (4, 0)  (5, 0)  (6, 0)  (7, 0)  (8, 0)
	row 3: (0, 3)  (1, 4)  (2, 5)  (3, 6)  (4, 7)  (5, 8)  (6, 9)  (7, 10)  (8, 11)
	row 4: (0, 4)  (1, 5)  (2, 6)  (3, 7)  (4, 8)  (5, 9)  (6, 10)  (7, 11)  (8, 12)
	row 5: (0, 5)  (1, 6)  (2, 7)  (3, 8)  (4, 9)  (5, 10)  (6, 11)  (7, 12)  (8, 13)
	row 6: (0, 12)  (1, 14)  (2, 16)  (3, 18)  (4, 20)  (5, 22)  (6, 24)  (7, 26)  (8, 28)
	row 7: (0, 14)  (1, 16)  (2, 18)  (3, 20)  (4, 22)  (5, 24)  (6, 26)  (7, 28)  (8, 30)
	row 8: (0, 16)  (1, 18)  (2, 20)  (3, 22)  (4, 24)  (5, 26)  (6, 28)  (7, 30)  (8, 32)

	
Explanation of Code
-------------------

Now lets take a look at the code::

  	Mat            Dense,AIJ;
  	PetscScalar    value;
  	PetscErrorCode ierr;
  	PetscInt       i,j,istart,iend;
  	PetscMPIInt    rank;
  	ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);
  	ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&rank);
  	ierr = MatCreateMPIDense(MPI_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,NUM_ROW	S,NUM_COLUMNS,PETSC_NULL,&Dense);CHKERRQ(ierr);
	ierr = MatGetOwnershipRange(Dense,&istart,&iend);CHKERRQ(ierr);
	for(i = istart; i < iend; i++)
	{
	  for(j = 0; j < NUM_COLUMNS; j++)
	  {
	    value = rank+i+j; // calculate an arbitrary value
	    ierr = MatSetValue(Dense,i,j,value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	}
	ierr = MatAssemblyBegin(Dense,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	ierr = MatAssemblyEnd(Dense,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	ierr = PetscPrintf(PETSC_COMM_WORLD,"Dense =\n");CHKERRQ(ierr);
	ierr = MatView(Dense, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	ierr = MatDestroy(&Dense);CHKERRQ(ierr);
 	if(rank == 0) num_nonzeros = 0;
  	else if(rank == 1) num_nonzeros = (NUM_ROWS/2)*(NUM_ROWS/2);
  	else if(rank == 2) num_nonzeros = 2*(NUM_ROWS/2)*(NUM_ROWS/2);
	ierr = MatCreateMPIAIJ(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,NUM_ROWS,NUM_COLUMNS,NUM_ROWS,PETSC_NULL,num_nonzeros,PETSC_NULL,&AIJ);CHKERRQ(ierr);
  	ierr = MatGetOwnershipRange(AIJ,&istart,&iend);CHKERRQ(ierr);
  	for(i = istart; i < iend; i++)
  	{
    	  for(j = 0; j <= i; j++)
    	  {
      	    value = i*j;
      	    ierr = MatSetValue(AIJ,i,j,value,INSERT_VALUES);CHKERRQ(ierr);
    	  }
  	}
  	ierr = MatAssemblyBegin(AIJ,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  	ierr = MatAssemblyEnd(AIJ,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
  	ierr = PetscPrintf(PETSC_COMM_WORLD,"AIJ =\n");CHKERRQ(ierr);
  	ierr = MatView(AIJ, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
  	ierr = MatDestroy(&AIJ);CHKERRQ(ierr);
	ierr = PetscFinalize();CHKERRQ(ierr);
	return 0;

The variable declarations and definitions::

  	Mat            Dense,AIJ;
  	PetscScalar    value;
  	PetscErrorCode ierr;
  	PetscInt       i,j,istart,iend;
  	PetscMPIInt    rank;

should look very similar to the declarations and definitions from the parallel vector section. The only difference is, of course, that we declared a matrix rather than a vector.
Next we call ``PetscInitialize()`` as usual::

  	ierr = PetscInitialize(&argc,&argv,(char*)0,help);CHKERRQ(ierr);

The next line::

  	ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

gets the rank of the calling processor. *NOTE* This tutorial makes frequent use of this function for demonstration purposes only. It is not generally used so frequently.

Next we create our matrix::

  	ierr = MatCreateMPIDense(MPI_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,NUM_ROWS,NUM_COLUMNS,PETSC_NULL,&Dense);CHKERRQ(ierr);

The first argument is MPI_COMM_WORLD because this is a multiprocessor program. The next two arguments specify the rows that the current processor will own. You can specify the row numbers yourself or you can supply ``PETSC_DECIDE`` which tells PETSc to divide the total rows as evenly as possible over all the available processors. The next two arguments specify the number of rows and number of columns the matrix is to have. The second to last argument is optional. If you preallocated memory for the matrix, then you would supply a pointer. If you wish for PETSc to allocate the memory for you, supply ``PETSC_NULL``. The final argument is the variable name of your matrix.

The next function call::

	ierr = MatGetOwnershipRange(Dense,&istart,&iend);CHKERRQ(ierr);

is the matrix version of ``VecGetOwnershipRange()``. The indices that the matrix version returns reference the rows owned by the current processor.

Next we use those indices and the ``MatSetValue()`` function to give all of our matrix positions values::

	for(i = istart; i < iend; i++)
	{
	  for(j = 0; j < NUM_COLUMNS; j++)
	  {
	    value = rank+i+j; // calculate an arbitrary value
	    ierr = MatSetValue(Dense,i,j,value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	}

The value at each matrix position is the sum of the rank of the processor that set the value and the coordinates that refer to the position.

Now that we have called ``MatSetValue()`` we must assemble our matrix::

	ierr = MatAssemblyBegin(Dense,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	ierr = MatAssemblyEnd(Dense,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);

The next two lines of code::

	ierr = PetscPrintf(PETSC_COMM_WORLD,"Dense =\n");CHKERRQ(ierr);
	ierr = MatView(Dense, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);

print out the matrix. Notice the PETSc communicator is ``PETSC_COMM_WORLD`` because we only want the ``PetscPrintf()`` function to print on one processor. Also notice that the PETSc Viewer is ``PETSC_VIEWER_STDOUT_WORLD`` because we only want the matrix to be printed by one processor.

Because we are now done with our matrix, we destroy the matrix::

	  ierr = MatDestroy(&Dense);CHKERRQ(ierr);

to free up the memory associated with it.

The next three lines::

 	if(rank == 0) num_nonzeros = 0;
  	else if(rank == 1) num_nonzeros = NUM_ROWS;
  	else if(rank == 2) num_nonzeros = NUM_ROWS;

are the only thing that we will do in addition to what we did with the dense matrix. With the dense matrix, we assumed that every position in the matrix (or at least the vast majority) would contain a non-zero value. But if we are working with a very large matrix, it is usually the case that many positions simply have the value of zero. So the whole point of the AIJ matrix is that we decide how many non-zero positions our matrix will have so that we only have to allocate enough memory to hold those values rather than allocating a space for every single position.

When we create our AIJ matrix::

	MatCreateMPIAIJ(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,NUM_ROWS,NUM_COLUMNS,num_nonzeros,PETSC_NULL,num_nonzeros,PETSC_NULL,&AIJ);CHKERRQ(ierr);

We must specify quite a bit of information. First, we specify the communicator to use which will be the parallel one in this case. Next we provide the local dimensions (row ,2nd arg by col, 3rd arg). We have chosen PETSC_DECIDE for both of these so that way PETSC splits up the matrix as evenly as possible among the processors. Then we provide the global dimensions (NUM_ROWS by NUM_COLUMS). The next four arguments are the most important for an AIJ matrix. It is recommended that you read pages 60(starting at the subheader `Parallel Sparse AIJ Matrices`)-62 of the PETSc manual (http://www.mcs.anl.gov/petsc/petsc-current/docs/manual.pdf). The four arguments are (shown in order)::

	  d_nz - number of nonzeros per row in diagonal portion of local submatrix; value is applied to ALL the rows; if d_nzz is specified, then d_nz must be set to PETSC_NULL

	  d_nzz - number of nonzeros per row in diagonal portion of local submatrix; (potentially) DIFFERENT value for each row; if d_nz is specified, then d_nzz must be set to PETSC_NULL

	  o_nz - number of nonzeros per row in off-diagonal portion of local submatrix; value is applied to ALL the rows; if o_nzz is specified, then o_nz must be set to PETSC_NULL

	  o_nzz - number of nonzeros per row in off-diagonal portion of local submatrix; (potentially) DIFFERENT value for each row; if o_nz is specified, then o_nzz must be set to PETSC_NULL

The last argument is a pointer to the matrix variable.

*NOTE* The next fourteen lines of code correspond virtually exactly to the fourteen lines of code used after the function `MatCreateMPIDense()` and therefore will not be reexplained.

Then we can call::

	  ierr = PetscFinalize();CHKERRQ(ierr);

and return a value::

	  return 0;

to end our program.

Key Functions Learned
---------------------

``MatCreateMPIDense(MPI_Comm comm,PetscInt m,PetscInt n,PetscInt M,PetscInt N,PetscScalar *data,Mat *A)``
	  * Creates a dense (uncompressed) parallel matrix. The matrix has global size of M rows by N columns. Each processor owns the rows m through n-1. It is recommended that the values for m and n be ``PETSC_DECIDE`` in most circumstances. ``data`` is the location of preallocated memory. If you wish to let PETSC allocate the memory for you, supply ``PETSC_NULL`` as the value for ``data``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatCreateMPIDense.html

``MatGetOwnershipRange(Mat mat,PetscInt *m,PetscInt* n)``
	  * Returns the first row of mat owned by the current processor as variable m and one more than the last row owned by the current processor as variable n
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatGetOwnershipRange.html

``MatCreateMPIAIJ(MPI_Comm comm,int m,int n,int M,int N,int d_nz,int *d_nnz,int o_nz,int *o_nnz,Mat *A)``
	  * Creates a parallel AIJ matrix. First, we specify the communicator to use which will be the parallel one in this case. Next we provide the local dimensions (row ,2nd arg by col, 3rd arg). We have chosen PETSC_DECIDE for both of these so that way PETSC splits up the matrix as evenly as possible among the processors. Then we provide the global dimensions (NUM_ROWS by NUM_COLUMS). The next four arguments are the most important for an AIJ matrix. It is recommended that you read pages 60(starting at the subheader `Parallel Sparse AIJ Matrices`)-62 of the PETSc manual (http://www.mcs.anl.gov/petsc/petsc-current/docs/manual.pdf). The four arguments are (shown in order)::

	  	  d_nz - number of nonzeros per row in diagonal portion of local submatrix; value is applied to ALL the rows; if d_nzz is specified, then d_nz must be set to PETSC_NULL

		  d_nzz - number of nonzeros per row in diagonal portion of local submatrix; (potentially) DIFFERENT value for each row; if d_nz is specified, then d_nzz must be set to PETSC_NULL

	  	  o_nz - number of nonzeros per row in off-diagonal portion of local submatrix; value is applied to ALL the rows; if o_nzz is specified, then o_nz must be set to PETSC_NULL

	 	  o_nzz - number of nonzeros per row in off-diagonal portion of local submatrix; (potentially) DIFFERENT value for each row; if o_nz is specified, then o_nzz must be set to PETSC_NULL

	  	  The last argument is a pointer to the matrix variable.

	  * http://www.itservices.hku.hk/sp2/software/petsc/www/man2/MatCreateMPIAIJ.html

Summary
-------

	Moving from one processor to multiple processors with dense matrices is similar to the same change with vectors. The only difference is that individual processors own a run of matrix rows rather than a run of vector entries. AIJ matrices can get incredible performance increase over dense matrices but you must be very careful as to how you allocate memory for that is how the speed increases occur. Congratulations, you have just compiled, ran, and hopefully even understood your first PETSc program involving parallel matrices!