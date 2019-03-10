//
//  main.c
//  matrix
//
//  Created by Thanatwit  Angsarawanee on 10/3/2562 BE.
//  Copyright © 2562 Thanatwit  Angsarawanee. All rights reserved.
//

//  This lib build for operate to matrix with highest performance

/*
    CPU 2GHz 2 core compute MxM size n*n
        - number of operate is 2*n^3
        - if n = 1,000 , time to wait is 2*1000^3 / 2*2*10^9 = 0.5 second
*/

#include <stdio.h>
#include "matrix.h"

#define _S1 1000
#define _S2 1000
#define _S3 1000
#define SEED_NUMBER 19
#define FLAG_PRINT  0

int main(int argc, const char * argv[]) {
    double * a;
    double * b;
    double * c;
    int round ;
    
    a = malloc(sizeof(double)*_S1*_S2);
    b = malloc(sizeof(double)*_S2*_S3);
    c = malloc(sizeof(double)*_S1*_S3);
    
    drandom((double *)a,_S1*_S2,SEED_NUMBER);
    drandom((double *)b,_S1*_S2,SEED_NUMBER);
    if(FLAG_PRINT){
        printf("A:\r\n");
        printMatrix((double *)a, _S1, _S2, '\t');
        printf("B:\r\n");
        printMatrix((double *)b, _S2, _S3, '\t');
    }
    
    struct timeval s;
    long process_time;
    
    for (round = 0; round < 3; round++) {
        printf("\r\nround %d\r\n",round+1);
        printf("Result:\r\n");
        s = get_time();
        dmultiple(a,b,c,_S1,_S2,_S3);
        process_time = diff_time(s);
        if(FLAG_PRINT){
            printMatrix((double *)c, _S1, _S3, '\t');
        }
        printf("Processing time: %ld.%ld\r\n",process_time/1000000,process_time%1000000);
        
        printf("Result_o1:\r\n");
        s = get_time();
        dmultiple_o1(a,b,c,_S1,_S2,_S3);
        process_time = diff_time(s);
        if(FLAG_PRINT){
            printMatrix((double *)c, _S1, _S3, '\t');
        }
        printf("Processing time: %ld.%ld\r\n",process_time/1000000,process_time%1000000);
    
    }
    
    return 0;
}
