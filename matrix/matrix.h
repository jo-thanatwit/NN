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

void printMatrix(double *m, int x, int y, char deli);
void dmultiple(double * a, double * b, double * result, int s1, int s2, int s3);
void dmultiple_o1(double * a, double * b, double * result, int s1, int s2, int s3);
void drandom(double * result , int size, int seed);
struct timeval get_time(void);
long diff_time(struct timeval s);

#endif /* matrix_h */
