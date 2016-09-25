CSC 4103 Project 1
==================

Chosen assignments

1. Forking processes to calculate series and products

     (``series.c``)


2. Utilizing pipes to calculate combinations.

     (``choose.c``)


3. Using shared memory to exchange secret messages among users
     
     (``secret.c``)


4. System calls used to create a self-reprecating program.
   
   (``kitties.c``) The implementation by default requires a number as a command line argument to limit the scope of the program. There is a trigger word that will make it run indefinitely to be compliant with the assignment. Don't use it. Also the program was modified at the last minute to conform with the default GCC options (``-std=gnu90``), which amounted to changing ``for(int i=0; ...)`` to ``int i; for(i=0; ..)``. If you want to preserve my bonus points, that'd be awfully swell. I understand if you can't do that. If you need proof, examine the git logs.
   
   Also it should be known that to seed the RNG (which I'm told the standard is to use the system clock (a combination of ``time(NULL)`` and ``clock()``), I need permission to /dev/rtc. See output of ``clock`` (at the bash prompt).

   A makefile is supplied to conveniently compile all programs. ``make all``


Total Point submitted **[64]**
