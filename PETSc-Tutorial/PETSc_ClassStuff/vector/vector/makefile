include ${PETSC_DIR}/conf/variables
include ${PETSC_DIR}/conf/rules

vec_create_seq: vec_create_seq.o  chkopts 
	-${CLINKER} -o vec_create_seq vec_create_seq.o ${PETSC_VEC_LIB}
	${RM} -f vec_create_seq.o

vec_create_mpi: vec_create_mpi.o  chkopts 
	-${CLINKER} -o vec_create_mpi vec_create_mpi.o ${PETSC_VEC_LIB}
	${RM} -f vec_create_mpi.o

vec_create_duplicate: vec_create_duplicate.o  chkopts 
	-${CLINKER} -o vec_create_duplicate vec_create_duplicate.o ${PETSC_VEC_LIB}
	${RM} -f vec_create_duplicate.o

vec_operations: vec_operations.o  chkopts 
	-${CLINKER} -o vec_operations vec_operations.o ${PETSC_VEC_LIB}
	${RM} -f vec_operations.o