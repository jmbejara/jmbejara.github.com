.. _appendix:

========
Appendix
========

Here is an abbreviated reference of the features of mpi4py. For a full documentation of the API, see http://mpi4py.scipy.org/docs/apiref/.

.. Note::

	One of the main differences between this presentation of mpi4py and MPI in C or Fortan, besides being array-based, is that mpi4py is largely object oriented. The MPI Communicator in mpi4py is a Python class and MPI functions like *Send* or *Broadcast* are instance methods of the communicator class. The object-oriented nature of mpi4py is seen mostly in dealing with MPI topologies. I will not discuss these in detail, but rather focus on an introduction to the basics of distributed memory programming with MPI. Throughout the tutorial you will see functions like ``Send(...)`` presented as ``Comm.Send(...)`` where it is implied that ``Comm`` is an instance of the *Comm* class. I will document ``Comm`` as in input paramter to the function.

.. _commMethods:
	
Instance Methods of *Comm* Class
--------------------------------

For full documentation of the *Comm* class, see http://mpi4py.scipy.org/docs/apiref/mpi4py.MPI.Comm-class.html.

"Uppercase" Communication
^^^^^^^^^^^^^^^^^^^^^^^^^
.. glossary::

	Abort( errorcode=0) 
		Terminate MPI execution environment
		
	Allgather(sendbuf, recvbuf) 
		Gather to All, gather data from all processes and distribute it to all other processes in a group
		
	Allgatherv(sendbuf, recvbuf) 
		Gather to All Vector, gather data from all processes and distribute it to all other processes in a group providing different amount of data and displacements
		
	Allreduce(sendbuf, recvbuf, Op op=SUM)
		All Reduce
				
	Alltoall(sendbuf, recvbuf)
		All to All Scatter/Gather, send data from all to all processes in a group

	Alltoallv(sendbuf, recvbuf)
		All to All Scatter/Gather Vector, send data from all to all processes in a group providing different amount of data and displacements	

	Alltoallw(sendbuf, recvbuf)
		Generalized All-to-All communication allowing different counts, displacements and datatypes for each partner	

	Barrier() 	
		Barrier synchronization	

	Bcast(buf, root=0) 	
		Broadcast a message from one process to all other processes in a group	

	Bsend(buf, dest=0, tag=0) 	
		Blocking send in buffered mode	

	Bsend_init(buf, dest=0, tag=0) 	
		Persistent request for a send in buffered mode	

	Call_errhandler(errorcode) 	
		Call the error handler installed on a communicator	

	Clone() 	
		Clone an existing communicator	

	Compare(type cls, Comm comm1, Comm comm2) 	
		Compare two communicators	

	Disconnect() 	
		Disconnect from a communicator	

	Free() 	
		Free a communicator	

	Gather(sendbuf, recvbuf, root=0) 	
		Gather together values from a group of processes	

	Gatherv(sendbuf, recvbuf, root=0) 	
		Gather Vector, gather data to one process from all other processes in a group providing different amount of data and displacements at the receiving sides	

	Get_attr(keyval) 	
		Retrieve attribute value by key	

	Get_errhandler() 	
		Get the error handler for a communicator	

	Get_group() 	
		Access the group associated with a communicator	

	Get_name() 	
		Get the print name for this communicator	

	Get_parent(type cls) 	
		Return the parent intercommunicator for this process	

	Get_rank()
		Return the rank of this process in a communicator	

	Get_size() 	
		Return the number of processes in a communicator	

	Get_topology() 	
		Determine the type of topology (if any) associated with a communicator	

	Ibsend(buf, dest=0, tag=0) 	
		Nonblocking send in buffered mode	

	Iprobe(source=0, tag=0, Status status=None) 	
		Nonblocking test for a message	

	Irecv(buf, source=0, tag=0) 	
		Nonblocking receive	

	Irsend(buf, dest=0, tag=0) 	
		Nonblocking send in ready mode	

	Is_inter() 	
		Test to see if a comm is an intercommunicator	

	Is_intra() 	
		Test to see if a comm is an intracommunicator	

	Isend(buf, dest=0, tag=0) 	
		Nonblocking send	

	Issend(buf, dest=0, tag=0) 	
		Nonblocking send in synchronous mode	

	Join(type cls, fd) 	
		Create a intercommunicator by joining two processes connected by a socket	

	Probe(source=0, tag=0, Status status=None) 
		Blocking test for a message	

	Recv(buf, source=0, tag=0, Status status=None) 
		Blocking receive	

	Recv_init(buf, source=0, tag=0) 	
		Create a persistent request for a receive	

	Reduce(sendbuf, recvbuf, Op op=SUM, root=0) 	
		Reduce	

	Reduce_scatter(sendbuf, recvbuf, recvcounts=None, Op op=SUM) 	
		Reduce-Scatter (vector version)	

	Reduce_scatter_block(sendbuf, recvbuf, Op op=SUM) 	
		Reduce-Scatter Block (regular, non-vector version)	

	Rsend(buf, dest=0, tag=0) 	
		Blocking send in ready mode	

	Rsend_init(buf, dest=0, tag=0) 	
		Persistent request for a send in ready mode	

	Scatter(sendbuf, recvbuf, root=0) 	
		Scatter Vector, scatter data from one process to all other processes in a group	

	Scatterv([choice sendbuf, tuple_int sendcounts, tuple_int displacements, MPI_Datatype sendtype], choice recvbuf, root=0) 	
		Scatter data from one process to all other processes in a group providing different amount of data and displacements at the sending side	

	Send(buf, dest=0, tag=0) 
		Blocking send	

	Send_init(buf, dest=0, tag=0) 	
		Create a persistent request for a standard send	

	Sendrecv(sendbuf, dest=0, sendtag=0, recvbuf=None, source=0, recvtag=0, Status status=None) 	
		Send and receive a message	

	Sendrecv_replace(buf, dest=0, sendtag=0, source=0, recvtag=0, Status status=None) 	
		Send and receive a message	

	Set_errhandler(Errhandler errhandler) 	
		Set the error handler for a communicator	

	Set_name(name) 	
		Set the print name for this communicator	

	Ssend(buf, dest=0, tag=0) 	
		Blocking send in synchronous mode	

	Ssend_init(buf, dest=0, tag=0) 	
		Persistent request for a send in synchronous mode	
		

"Lowercase" Communication
^^^^^^^^^^^^^^^^^^^^^^^^^

.. glossary::

	allgather(sendobj=None, recvobj=None) 
		Gather to All
		
	allreduce(sendobj=None, recvobj=None, op=SUM) 	
		Reduce to All	

	alltoall(sendobj=None, recvobj=None) 	
		All to All Scatter/Gather	

	barrier() 	
		Barrier	

	bcast(obj=None, root=0) 	
		Broadcast	

	bsend(obj=None, dest=0, tag=0) 	
		Send in buffered mode	

	gather(sendobj=None, recvobj=None, root=0) 	
		Gather	

	ibsend(obj=None, dest=0, tag=0) 	
		Nonblocking send in buffered mode	

	isend(obj=None, dest=0, tag=0) 	
		Nonblocking send	

	issend(obj=None, dest=0, tag=0) 	
		Nonblocking send in synchronous mode	

	recv(obj=None, source=0, tag=0, Status status=None) 	
		Receive	

	reduce(sendobj=None, recvobj=None, op=SUM, root=0) 	
		Reduce	

	scatter(sendobj=None, recvobj=None, root=0) 	
		Scatter	

	send(obj=None, dest=0, tag=0) 	
		Send	

	sendrecv(sendobj=None, dest=0, sendtag=0, recvobj=None, source=0, recvtag=0, Status status=None) 	
		Send and Receive	

	ssend(obj=None, dest=0, tag=0) 	
		Send in synchronous mode

.. _OpClass:

The *Op* Class (Reduction Operations)
-------------------------------------

Within the *Op* class are values that represent predefine operations to be used with the "reduce" functions. There are also methods that allow the creation of user-defined operations. I present here a table of the predefined operations. Full documentation is found here: http://mpi4py.scipy.org/docs/apiref/mpi4py.MPI.Op-class.html

=============    =======================
Name             Meaning    
=============    =======================
MPI.MAX          maximum 
MPI.MIN          minimum 
MPI.SUM          sum 
MPI.PROD         product 
MPI.LAND         logical and 
MPI.BAND         bit-wise and 
MPI.LOR          logical or 
MPI.BOR          bit-wise or 
MPI.LXOR         logical xor 
MPI.BXOR         bit-wise xor 
MPI.MAXLOC       max value and location 
MPI.MINLOC       min value and location 
=============    =======================


