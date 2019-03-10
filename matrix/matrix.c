//
//  matrix.c
//  matrix
//
//  Created by Thanatwit  Angsarawanee on 10/3/2562 BE.
//  Copyright © 2562 Thanatwit  Angsarawanee. All rights reserved.
//

#include "matrix.h"

void printMatrix(double *m, int x, int y, char deli){
    int i=0,j=0;
    while (i<x) {
        while (j<y) {
            printf("%.6e%c",m[i*y+j],deli);
            j++;
        }
        j=0;
        printf("\n");
        i++;
    }
}

// multiple of matrix a*b (size of a is s1*s2, b is s2*s3)
void dmultiple(double * a, double * b, double * result, int s1, int s2, int s3){
    int i1,i2,i3,buf1,buf2,buf3;
    for ( i1=0 ; i1<s1 ; i1++) {
        buf1=i1*s3;
        buf3=i1*s2;
        for ( i3=0 ; i3<s3 ; i3++) {
            buf2=buf1+i3;
            result[buf2] = 0;
            for ( i2=0 ; i2<s2 ; i2++) {
                result[buf2] += a[buf3 + i2] * b[i2*s3+i3];
            }
        }
    }
}

void dmultiple_o1(double * a, double * b, double * result, int s1, int s2, int s3){
    int i1,i2,i3,buf1,buf2,buf3,buf4;
    (void)memset(result,0,(unsigned long)s1*s3*sizeof(double));
    for ( i1=0 ; i1<s1 ; i1++) {
        buf1 = i1*s2;
        buf4 = i1*s3;
        for ( i2=0 ; i2<s2 ; i2++) {
            buf2 = i2*s3;
            buf3 = buf1 +i2;
            for ( i3=0 ; i3<s3 ; i3++) {
                result[buf4+i3] += a[buf3] * b[buf2 + i3];
            }
        }
    }
}

void drandom(double * result , int size, int seed){
    int i;
    static char flag = 0;
    if(flag == 0){
        srand(seed);
        flag = 1;
    }
    for ( i=0 ; i<size ; i++) {
        result[i] = (double)rand()/RAND_MAX*2.0-1.0;//float in range -1 to 1
    }
}

struct timeval get_time(){
    struct timeval s;
    gettimeofday(&s, NULL);
    return s;
}

long diff_time(struct timeval s){
    struct timeval e;
    gettimeofday(&e, NULL);
    return (e.tv_sec - s.tv_sec)*1000000 +(e.tv_usec - s.tv_usec);
}
