#include <stdlib.h>
#include <stdio.h>
#include "k.h"

// dgetrf is double precision LU decomp
extern void dgetrf_(int* M, int *N, double* A, int* lda, int* IPIV, int* INFO);
// dgetri is double precision inverse using the result from dgetrf
extern void dgetri_(int* N, double* A, int* lda, int* IPIV, double* WORK, int* lwork, int* INFO);

K inv(K mlst,K dim){
        K res = ktn(KF,0);
        int len=(int)(mlst->n);
        //A is in column major format due to lapack being written in fortran
        F* A=kF(mlst);
        int i,j,n=dim->i,info;
        int ipiv[len];
        // Set the dimension of the workspace array
        int lwork=n*n;
        double work[lwork];
        // LU decomposition of A (stored in same memory as A)
        dgetrf_ (&n,&n,A,&n,ipiv,&info);
        if(info>0)return ki(0); // If info is greater than 0 then matrix is singular
        // Calculate inverse of A using LU decomp (also stored in same memory as A)
        dgetri_ (&n,A,&n,ipiv,work,&lwork,&info);
        // Assign inverse to res as k 'float' objects.
        // Res is in row major format instead of column
        // This makes it easier to convert back to a matrix in q
        // e.q. A after inversion = 1 3 2 4 (1 3 are column 1; 2 4 are column 2)
        //      res returned to q = 1 2 3 4 (1 2 are row 1;3 4 are row 2)
        //      Convert to matrix in q = 2 2#1 2 3 4
        for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                        res=ja(&res,&A[n*j+i]);
        return res;
}
