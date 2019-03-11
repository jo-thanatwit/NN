//
//  matrix.h
//  matrix
//
//  Created by Thanatwit  Angsarawanee on 10/3/2562 BE.
//  Copyright © 2562 Thanatwit  Angsarawanee. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h> 

void printMatrix(double *m, int x, int y, char deli);
void dmultiple(double * a, double * b, double * result, int s1, int s2, int s3);
void dmultiple_o1(double * a, double * b, double * result, int s1, int s2, int s3);
void dmultiple_o2(double * a, double * b, double * result, int s1, int s2, int s3);
void dmultiple_o2_min_max_s2(double * a, double * b, double * result, int s1, int min_s2, int max_s2,int s2, int s3);
void dmultiple_o3(double * a, double * b, double * result, int s1, int s2, int s3, int worker);
void dmultiple_o4(double * a, double * b, double * result, int s1, int s2, int s3, int worker);
void drandom(double * result , int size, int seed);
char dcheck_matrix(double * a, double * b, int s1, int s2, double threshold);
struct timeval get_time(void);
long diff_time(struct timeval s);


struct _MULTIPLE_MATRIX_{
    double * a;
    double * b;
    double * result;
    int s1;
    int s2;
    int s3;
    int worker;
    int index;
    pthread_t tid;
};

typedef struct _MULTIPLE_MATRIX_ multiple_matrix;

#endif /* matrix_h */
