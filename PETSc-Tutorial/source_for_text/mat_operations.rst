.. _PETSc_mat_operations:

===============================
PETSc: Operations with Matrices
===============================
Now that we understand vectors and matrices, we will demonstrate how they can be used together to do more complex operations.

Directions
----------

Run the tutorial code with the following directions:

- Go to the matrix folder, if you are not already there. It is in the PETSc_TutorialStuff folder that should already be in your directory.

- To compile the program for this section, enter the following and press <Enter>::

	$ make mat_operations

- To run the executable type the following command and press <Enter>::

	$ mpiexec -n 2 ./mat_operations

- The output should appear as follows::

	**ORIGINAL** A =
	Matrix Object: 1 MPI processes
	  type: mpidense
	0.0000000000000000e+00 1.0000000000000000e+00 2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00
	1.0000000000000000e+00 2.0000000000000000e+00 3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00
	4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00
	9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01
	1.6000000000000000e+01 1.7000000000000000e+01 1.8000000000000000e+01 1.9000000000000000e+01 2.0000000000000000e+01 2.1000000000000000e+01
	2.5000000000000000e+01 2.6000000000000000e+01 2.7000000000000000e+01 2.8000000000000000e+01 2.9000000000000000e+01 3.0000000000000000e+01

	**ORIGINAL** B =
	Matrix Object: 1 MPI processes
	  type: mpidense
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00
	1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00 1.0000000000000000e+00

	**ORIGINAL** X and V =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	0
	1
	16
	Process [1]
	81
	256
	625
	
	(result stored in A) A + 3B =
	Matrix Object: 1 MPI processes
	  type: mpidense
	3.0000000000000000e+00 4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00
	4.0000000000000000e+00 5.0000000000000000e+00 6.0000000000000000e+00 7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00
	7.0000000000000000e+00 8.0000000000000000e+00 9.0000000000000000e+00 1.0000000000000000e+01 1.1000000000000000e+01 1.2000000000000000e+01
	1.2000000000000000e+01 1.3000000000000000e+01 1.4000000000000000e+01 1.5000000000000000e+01 1.6000000000000000e+01 1.7000000000000000e+01
	1.9000000000000000e+01 2.0000000000000000e+01 2.1000000000000000e+01 2.2000000000000000e+01 2.3000000000000000e+01 2.4000000000000000e+01
	2.8000000000000000e+01 2.9000000000000000e+01 3.0000000000000000e+01 3.1000000000000000e+01 3.2000000000000000e+01 3.3000000000000000e+01

	A*X =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	7362
	8341
	11278
	Process [1]
	16173
	23026
	31837
	
	V + A*X =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	7362
	8342
	11294
	Process [1]
	16254
	23282
	32462
	
	A(t)*X =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	23452
	24431
	25410
	Process [1]
	26389
	27368
	28347
	
	V + A(t)*X =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	23452
	24432
	25426
	Process [1]
	26470
	27624
	28972
	
	Norm 1 of A  = 103.000000
	Norm Frobenius of A = 103.431137
	Norm Infinity of A = 183.000000
	
	(result stored in A) 100 * A =
	Matrix Object: 1 MPI processes
	  type: mpidense
	3.0000000000000000e+02 4.0000000000000000e+02 5.0000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02
	4.0000000000000000e+02 5.0000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02 9.0000000000000000e+02
	7.0000000000000000e+02 8.0000000000000000e+02 9.0000000000000000e+02 1.0000000000000000e+03 1.1000000000000000e+03 1.2000000000000000e+03
	1.2000000000000000e+03 1.3000000000000000e+03 1.4000000000000000e+03 1.5000000000000000e+03 1.6000000000000000e+03 1.7000000000000000e+03
	1.9000000000000000e+03 2.0000000000000000e+03 2.1000000000000000e+03 2.2000000000000000e+03 2.3000000000000000e+03 2.4000000000000000e+03
	2.8000000000000000e+03 2.9000000000000000e+03 3.0000000000000000e+03 3.1000000000000000e+03 3.2000000000000000e+03 3.3000000000000000e+03
	
	Diagonals of A =
	Vector Object: 2 MPI processes
	  type: mpi
	Process [0]
	300
	500
	900
	Process [1]
	1500
	2300
	3300
	
	(result stored in B) A(t) =
	Matrix Object: 1 MPI processes
	  type: mpidense
	3.0000000000000000e+02 4.0000000000000000e+02 7.0000000000000000e+02 1.2000000000000000e+03 1.9000000000000000e+03 2.8000000000000000e+03
	4.0000000000000000e+02 5.0000000000000000e+02 8.0000000000000000e+02 1.3000000000000000e+03 2.0000000000000000e+03 2.9000000000000000e+03
	5.0000000000000000e+02 6.0000000000000000e+02 9.0000000000000000e+02 1.4000000000000000e+03 2.1000000000000000e+03 3.0000000000000000e+03
	6.0000000000000000e+02 7.0000000000000000e+02 1.0000000000000000e+03 1.5000000000000000e+03 2.2000000000000000e+03 3.1000000000000000e+03
	7.0000000000000000e+02 8.0000000000000000e+02 1.1000000000000000e+03 1.6000000000000000e+03 2.3000000000000000e+03 3.2000000000000000e+03
	8.0000000000000000e+02 9.0000000000000000e+02 1.2000000000000000e+03 1.7000000000000000e+03 2.4000000000000000e+03 3.3000000000000000e+03

	(result stored in B) B(hermitian transpose) =
	Matrix Object: 1 MPI processes
	  type: mpidense
	3.0000000000000000e+02 4.0000000000000000e+02 5.0000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02
	4.0000000000000000e+02 5.0000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02 9.0000000000000000e+02
	7.0000000000000000e+02 8.0000000000000000e+02 9.0000000000000000e+02 1.0000000000000000e+03 1.1000000000000000e+03 1.2000000000000000e+03
	1.2000000000000000e+03 1.3000000000000000e+03 1.4000000000000000e+03 1.5000000000000000e+03 1.6000000000000000e+03 1.7000000000000000e+03
	1.9000000000000000e+03 2.0000000000000000e+03 2.1000000000000000e+03 2.2000000000000000e+03 2.3000000000000000e+03 2.4000000000000000e+03
	2.8000000000000000e+03 2.9000000000000000e+03 3.0000000000000000e+03 3.1000000000000000e+03 3.2000000000000000e+03 3.3000000000000000e+03

	A + 50*I =
	Matrix Object: 1 MPI processes
	  type: mpidense
	3.5000000000000000e+02 4.0000000000000000e+02 5.0000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02
	4.0000000000000000e+02 5.5000000000000000e+02 6.0000000000000000e+02 7.0000000000000000e+02 8.0000000000000000e+02 9.0000000000000000e+02
	7.0000000000000000e+02 8.0000000000000000e+02 9.5000000000000000e+02 1.0000000000000000e+03 1.1000000000000000e+03 1.2000000000000000e+03
	1.2000000000000000e+03 1.3000000000000000e+03 1.4000000000000000e+03 1.5500000000000000e+03 1.6000000000000000e+03 1.7000000000000000e+03
	1.9000000000000000e+03 2.0000000000000000e+03 2.1000000000000000e+03 2.2000000000000000e+03 2.3500000000000000e+03 2.4000000000000000e+03
	2.8000000000000000e+03 2.9000000000000000e+03 3.0000000000000000e+03 3.1000000000000000e+03 3.2000000000000000e+03 3.3500000000000000e+03

	diag(V)*A*diag(W) =
	Matrix Object: 1 MPI processes
	  type: mpidense
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	1.2000000000000000e+05 2.7500000000000000e+05 5.4000000000000000e+05 1.0500000000000000e+06 1.8400000000000000e+06 2.9700000000000000e+06
	3.3600000000000000e+06 6.4000000000000000e+06 1.3680000000000000e+07 2.4000000000000000e+07 4.0480000000000000e+07 6.3360000000000000e+07
	2.9160000000000000e+07 5.2650000000000000e+07 1.0206000000000000e+08 1.8832500000000000e+08 2.9808000000000000e+08 4.5441000000000000e+08
	1.4592000000000000e+08 2.5600000000000000e+08 4.8384000000000000e+08 8.4480000000000000e+08 1.3836800000000000e+09 2.0275200000000000e+09
	5.2500000000000000e+08 9.0625000000000000e+08 1.6875000000000000e+09 2.9062500000000000e+09 4.6000000000000000e+09 6.9093750000000000e+09

	A(zeroed) =
	Matrix Object: 1 MPI processes
	  type: mpidense
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00
	0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 0.0000000000000000e+00 
	
	
Code
-------------------

Now lets take a look at the code::

	  Mat            A,B;
	  Vec            V,W,X;
	  PetscScalar    values[1],value,one=1,three=3;
	  PetscReal      norm_one,norm_frob,norm_infin;
	  PetscErrorCode ierr;
	  PetscInt       i,j,istart,iend;
	  PetscMPIInt    rank;
	  PetscInitialize(&argc,&argv,0,0);CHKERRQ(ierr);
	  ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&rank);
	  ierr = MatCreateMPIDense(MPI_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,ARRAY_SIZE,ARRAY_SIZE,PETSC_NULL,&A);CHKERRQ(ierr);
	  ierr = MatCreateMPIDense(MPI_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE,ARRAY_SIZE,ARRAY_SIZE,PETSC_NULL,&B);CHKERRQ(ierr);
	  ierr = VecCreate(PETSC_COMM_WORLD,&V);CHKERRQ(ierr);
	  ierr = VecSetSizes(V,PETSC_DECIDE,ARRAY_SIZE);CHKERRQ(ierr);
	  ierr = VecSetFromOptions(V);CHKERRQ(ierr);
	  ierr = VecDuplicate(V,&W);CHKERRQ(ierr);
	  ierr = VecDuplicate(V,&X);CHKERRQ(ierr);
	  ierr = MatGetOwnershipRange(A,&istart,&iend);CHKERRQ(ierr);
	  for(i = istart; i < iend; i++)
	  {
	    for(j = 0; j < ARRAY_SIZE; j++)
	    {
	      *values = i*i+j;
	      ierr = MatSetValues(A,1,&i,1,&j,values,INSERT_VALUES);CHKERRQ(ierr);
	      ierr = MatSetValue(B,i,j,one,INSERT_VALUES);CHKERRQ(ierr);
	    }
	    value = i*i*i*i;
	    ierr = VecSetValues(X,1,&i,&value,INSERT_VALUES);CHKERRQ(ierr);
	  }
	  ierr = MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = MatAssemblyBegin(B,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = MatAssemblyEnd(B,MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	  ierr = VecAssemblyBegin(X);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(X);CHKERRQ(ierr);
	  ierr = VecCopy(X,V);CHKERRQ(ierr);
	  ierr = VecAssemblyBegin(V);CHKERRQ(ierr);
	  ierr = VecAssemblyEnd(V);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n**ORIGINAL** A =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n**ORIGINAL** B =\n");CHKERRQ(ierr);
	  ierr = MatView(B, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n**ORIGINAL** X and V =\n");CHKERRQ(ierr);
	  ierr = VecView(X, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatAXPY(A,three,B,SAME_NONZERO_PATTERN);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n(result stored in A) A + 3B =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatMult(A,X,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nA*X =\n");CHKERRQ(ierr);
	  ierr = VecView(W, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatMultAdd(A,X,V,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nV + A*X =\n");CHKERRQ(ierr);
	  ierr = VecView(W, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatMultTranspose(A,X,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nA(t)*X =\n");CHKERRQ(ierr);
	  ierr = VecView(W, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatMultTransposeAdd(A,X,V,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nV + A(t)*X =\n");CHKERRQ(ierr);
	  ierr = VecView(W, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatNorm(A,NORM_1,&norm_one);CHKERRQ(ierr);
	  ierr = MatNorm(A,NORM_FROBENIUS,&norm_frob);CHKERRQ(ierr);
	  ierr = MatNorm(A,NORM_INFINITY,&norm_infin);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nNorm 1 of A  = %f\n",norm_one);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Norm Frobenius of A = %f\n",norm_frob);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"Norm Infinity of A = %f\n",norm_infin);CHKERRQ(ierr);
	  ierr = MatScale(A, 100);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n(result stored in A) 100 * A =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatGetDiagonal(A,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nDiagonals of A =\n");CHKERRQ(ierr);
	  ierr = VecView(W, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatTranspose(A,MAT_INITIAL_MATRIX,&B);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n(result stored in B) A(t) =\n");CHKERRQ(ierr);
	  ierr = MatView(B,PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatHermitianTranspose(B,MAT_REUSE_MATRIX,&B);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\n(result stored in B) B(hermitian transpose) =\n");CHKERRQ(ierr);
	  ierr = MatView(B,PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatShift(A,50);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nA + 50*I =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatDiagonalScale(A,V,W);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\ndiag(V)*A*diag(W) =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatZeroEntries(A);CHKERRQ(ierr);
	  ierr = PetscPrintf(PETSC_COMM_WORLD,"\nA(zeroed) =\n");CHKERRQ(ierr);
	  ierr = MatView(A, PETSC_VIEWER_STDOUT_WORLD);CHKERRQ(ierr);
	  ierr = MatDestroy(&A);CHKERRQ(ierr);
	  ierr = MatDestroy(&B);CHKERRQ(ierr);
	  ierr = VecDestroy(&V);CHKERRQ(ierr);
	  ierr = VecDestroy(&W);CHKERRQ(ierr);
	  ierr = PetscFinalize();CHKERRQ(ierr);
	  return 0;

	This program sets up two matrices and three vectors and does various operations with them.

Key Functions Learned
---------------------

``MatAXPY(Mat Y,PetscScalar a,Mat X,MatStructure str)``
	  * Computes ``Y = a*X + Y``. ``str`` is ``SAME_NONZERO_PATTERN`` if matrices ``X`` and ``Y`` have the same compression configuration. If not, ``str`` is ``DIFFERENT_NONZERO_PATTERN``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatAXPY.html
``MatMult(Mat mat,Vec x,Vec y)``
	  * Computes the matrix-vector product, ``y = Ax``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatMult.html
``MatMultAdd(Mat mat,Vec v1,Vec v2,Vec v3)``
	  * Computes ``v3 = v2 + A * v1``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatMultAdd.html
``MatMultTranspose(Mat mat,Vec x,Vec y)``
	  * Computes ``y = mat^T * x``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatMultTranspose.html
``MatMultTransposeAdd(Mat mat,Vec v1,Vec v2,Vec v3)``
	  * Computes ``v3 = v2 + A' * v1``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatMultTransposeAdd.html
``MatNorm(Mat mat,NormType type,PetscReal *nrm)``
	  * Calculates the norm of type ``type`` of matrix ``mat`` and stores the result to ``nrm``. The possible values for ``type`` are: ``NORM_1``, ``NORM_FROBENIUS``, ``NORM_INFINITY``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatNorm.html
``MatScale(Mat mat,PetscScalar a)``
	  * Computes ``mat = mat * a`` where ``a`` is a scalar
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatScale.html
``MatGetDiagonal(Mat mat,Vec v)``
	  * Stores the diagonal entries of ``mat`` into ``v``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatGetDiagonal.html
``MatTranspose(Mat mat,MatReuse reuse,Mat *B)``
	  * Calculates the transpose of ``mat`` and stores it to ``B``. If ``reuse`` is ``MAT_INITIAL_MATRIX`` then ``B`` and ``mat`` are different matrices. If you want the transpose done in place, pass ``MAT_REUSE_MATRIX`` in for ``reuse``
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatTranspose.html
``MatHermitianTranspose(Mat mat,MatReuse reuse,Mat *B)``
	  * Same exact usage as ``MatTranspose()`` except it does the Hermitian transpose
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatHermitianTranspose.html
``MatShift(Mat Y,PetscScalar a)``
	  * Computes ``Y = Y + a * I``, where ``a`` is a PetscScalar and ``I`` is the identity matrix. 
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatShift.html
``MatDiagonalScale(Mat mat,Vec l,Vec r)``
	  * Computes ``mat = l * mat * r``, where ``l`` is a diagonal matrix (stored as a vector), ``r`` is a diagonal matrix (stored as a vector) The ``l`` scales the rows of the matrix, the ``r`` scales the columns of the matrix
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatDiagonalScale.html
``MatZeroEntries(Mat mat)``
	  * Zeros out ``mat``. In equation form: ``mat = 0 * mat`` where ``0`` is a scalar
	  * http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/MatZeroEntries.html

For an exhaustive list of matrix operations, visit http://www.mcs.anl.gov/petsc/petsc-current/docs/manualpages/Mat/index.html (Note that this lists all matrix function calls, not just operation type function calls)

Summary
-------

	This program ties a lot of what we have learned together. Make sure you can go through each line of code and understand the purpose before moving on.