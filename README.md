# qinv
Matrix inversion in kdb+ using lapack instead of the native inv function.

##Compiling qinv.c
Requires [lapack](http://www.netlib.org/lapack/) and [k.h](http://code.kx.com/wsvn/code/kx/kdb+/c/c/k.h) from Kx systems to compile.

Assuming a os is 64 bit linux.

lapack 64 bit libraries can be obtained for linux through the following command:

    sudo apt-get install liblapack-dev liblapack3 libopenblas-base libopenblas-dev

For 32 bit libraries:

    sudo apt-get install liblapack-dev:i386 liblapack3:i386 libopenblas-base:i386 libopenblas-dev:i386

To use the inv function from qinv.c the source must be compiled into a shared object.

For use with 64 bit kdb+ version 3.x (assuming lapack is installed in the standard location):
    
    gcc -DKXVER=3 -shared -fPIC qinv.c -llapack -L/usr/lib -o qinv.so
    
For 32 bit kdb+ (requires the 32 bit libraries):

    gcc -DKXVER=3 -m32 -shared -fPIC qinv.c -llapack -L/usr/lib -o qinv.so
    
##Installation
Once compiled put the .so file in the default directory or the current working directory. More details here http://code.kx.com/wiki/Cookbook/ExtendingWithC#Introduction 

Place the q script qinv.q in the same directory as q.k or in the current working directory. Loading qinv.q from the command line or with \l will automatically define qinv to use the inv function from qinv.c.

##Examples
Will not operate on an input that is not a square matrix of floats

    q)qinv[1 2 3f]
    "Not a square matrix"
    q)qinv[(1 2 3f;1 2 3f)]
    "Not a square matrix"
    q)qinv[(1 2 3f;1 3f)]
    "Not a square matrix"
    q)qinv[(1 2;1 3f)]
    "Invalid type. Requires all floats"

If the function encounters a singular matrix which has no inverse it will return 0 and display the following (standard q inv function included for comparison):
    
    q)inv[(1 2f;1 2f)]
     
     
    q)qinv[(1 2f;1 2f)]
    "Error: Matrix is singular"

Function returns accurate results even when the standard q function fails to:

    q)qinv[(1 2f;1 3f)]
    3  -2
    -1 1 
    q)inv[(1 2f;1 3f)]
    3  -2
    -1 1 
    q)inv[(5 10010f;10010 20040030f)]
     
     
    q)qinv[(5 10010f;10010 20040030f)]
    400800.6 -200.2
    -200.2   0.1   
