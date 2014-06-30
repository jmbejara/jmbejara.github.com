.. _overview:

=================================
An Overview of Parallel Computing
=================================
.. include:: <isonum.txt>

Single Processor Limits
-----------------------
Over the past few dacades we have seen vast increases in computational power available. These increases in computational power have come through increased single processor performance, which have almost wholly been driven by increases in the density of trasnsistors on integrated circuits. The smaller sizes allow the speed of these trasistors to be increased and the overall speed of the integrated circuit can be increased. However, as the speed of these transistors increase, their power consumption increases. Because most of the power consumed is dissapated as heat, the circuit become hotter. If the circuit becomes too hot, it becomes unreliable. In most laptops and desktops, you'll notice that the processor is cooled by a fan and heat sink (in larger systems, other cooling systems are often used). The so-called "heat wall" refers to the physical limits of single processors to become faster because of the growing inability to sufficiently dissapate heat.

Flynn's Taxonomy
----------------
The original classification of parallel computers is popularly known as Flynn's taxonomy. In 1966, Michael Flynn classified systems according to the number of instruction streams and the number of data streams. The classical von Neumann machine has a single instruction stream and a single data stream, and hence is identified as a single-instruction single-data (SISD) machine. This basically translates into modern terms as one processor and one set of RAM. At the opposite extreme is the multiple-instruction multiple-data (MIMD) system, in which a collection of autonomous processors operate on their own data streams. In Flynn's taxonomy, this is the most general architecture.  Lying between these two extremes, are single-instruction multiple-data (SIMD) and multiple-instruction single-data (MISD) systems.

The classical von Neumann machine is divided into a CPU and main memory. The CPU is further divided into a control unit and an arithmetic logic unit (ALU). Both data and program memory are stored in a separate memory area, and have to be moved to the CPU in order to do any computation. The wires used to transport the data and program are collectively referred to as the bus. The larger the bus, the more data can be transported simultaneously. Unfortunately, no matter how wide the bus, the CPU can only process one calculation at a time. The von Neumann Bottleneck is the limitation of transfer of data and instructions between memory and the CPU: no matter how fast we make our CPUs, the speed of execution is limited by the rate at which we can transfer information between main memory and the CPU.

Piplining
---------
The first solution to the von Neumann bottleneck was the idea of pipelining. Pipelining is the architecting of a computer and its program into functional units, such that calculations which do not depend on each other can be done concurrently. If the circuits of the CPU are split up, then in theory, the CPU can act like more than one CPU.

SIMD Systems
------------
A pure SIMD system has only one processor, or CPU, to control, and has many subordinate ALUs. With each instruction cycle, the CPU broadcasts a single instruction to all the subordinate processors, which either executed the instruction or is idle. For example, if we have two vectors of length 1000, we could theoretically add them by distributing their data among the ALUs, and concurrently processing the data. If 1000 is not evenly divisible by the number of ALU's, then some are going to have to process more data than the others. Thus, as the few ALUs with extra information to process are working, the other ALU's must sit idle, since they are receiving the same instructions from the master CPU.

General MIMD
------------
The main difference between MIMD and SIMD systems are that the MIMD systems consist of processors which are autonomous, or self-governing. Each process is a fully implemented CPU with its own program memory. Each processor is capable of executing its own program in its own space. It is like having completely separate computers, but which work together. Unlike SIMD systems, MIMD systems are asynchronous, meaning that there is no global clock issuing instructions at regular intervals across all processors anymore. This gives rise to greater flexibility in programming, and greater complexity to manage.

Message Passing
---------------
The most commonly used method of programming distributed-memory MIMD systems is message passing, or some variant of message passing. In basic message passing, the processes coordinate their activities by explicitly sending and receiving messages, For example, at its most basic, the Message Passing Interface (MPI) provides a function for sending a message, ``MPI_Send``, and a function for receiving a message, ``MPI_Receive``.

There are several issues to address here. First, note that the commands being executed by process *a* are going to be different from process *b*. Thus we could actually write two separate computer programs in different files to accomplish this. However, the most common method today has become to write both processes into one program and to control which lines of execution get assigned to which process. This means that there is only one file of code and that the code is written to assign certain lines to certain processors. This approach to MIMD systems is called single-program multiple-data (SPMD). In SPMD programs, the effect of running different programs is obtained by the use of conditional branches within the source code.

MPI: the Message Passing Interface
----------------------------------
MPI was developed out of the need for standardization of programming parallel systems. MPI is different than other approaches in that it does not specify a ne language. Rather, MPI specifies a *library* of functions--the syntax and sematics of message passing routines--that can be called from the main scientific programming languages: C, Fortran, C++, and (as we will demonstrate in this tutorial) Python. MPI provides a very powerful and very general way of expressing parallelism. It is however, to use an analogy "the assemply language of parallel computing," because of this generality and the detail that it forces the programmer to deal with. [#f1]_ In spite of this apparent drawback, MPI is important because it is the *first* portable and universally available standard for programming parallel systems and the *de facto* standard. That is, MPI makes it possible for programmers to develop portable, parallel software libraries. It is worth reemphasizing, one of the most important contributions of MPI is its support for parallel libraries. [#f2]_ Until recently, one of the biggest problems in parallel computing was the lack of software. However, parallel software is growing faster thanks in large part to this standardization. At the end of this manual we will discuss how this is accomplished (through MPI *communicators*) and then we will breifly discuss some of the more well-known parallel software libraries.

Exercises
---------
1. Provide a concise definition of MPI.
2. Most modern personal computers now have multicore processors. In order to take advantage of the extra available computational power, a single program must be specially designed. Programs that are designed for these multicore processors are also "parallel" programs, typically written using POSIX |reg| threads or openMP. MPI, on the other hand, is designed with a different kind of architecture in mind. How does the architecture of a system for which MPI is designed differ what POSIX |reg| threads or openMP is designed for? What is the difference between MPI and openMP or Pthreads?
3. List two different implementations of MPI.
4. Determine what implementation of MPI is running on the machine you are using. (Note that mpi4py must be built on top an MPI distrubtion like MPICH or openMPI. What implementation is mpi4py built on top of on you machine?)


.. [#f1] Parallel Programming with MPI, by Peter S. Pacheco, p. 7
.. [#f2] ibid. p. 340

