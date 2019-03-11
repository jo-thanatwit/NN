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
            printf("%.16e%c",m[i*y+j],deli);
            j++;
        }
        j=0;
        printf("\n");
        i++;
    }
}

// multiple of matrix a*b (size of a is s1*s2, b is s2*s3)
void dmultiple(double * a, double * b, double * result, int s1, int s2, int s3){
    int i1,i2,i3;
    (void)memset(result,0,(unsigned long)s1*s3*sizeof(double));
    for ( i1=0 ; i1<s1 ; i1++) {
        for ( i3=0 ; i3<s3 ; i3++) {
            for ( i2=0 ; i2<s2 ; i2++) {
                result[i1*s3+i3] += a[i1*s2 + i2] * b[i2*s3+i3];
            }
        }
    }
}

void dmultiple_o1(double * a, double * b, double * result, int s1, int s2, int s3){
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

void dmultiple_o1_min_max_s1(double * a, double * b, double * result, int min_s1, int max_s1, int s1,int s2, int s3){
    int i1,i2,i3,buf1,buf2,buf3;
    for ( i1=min_s1 ; i1<max_s1 ; i1++) {
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

void dmultiple_o2(double * a, double * b, double * result, int s1, int s2, int s3){
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

void dmultiple_o2_min_max_s2(double * a, double * b, double * result, int s1, int min_s2, int max_s2,int s2, int s3){
    int i1,i2,i3,buf1,buf2,buf3,buf4;
    (void)memset(result,0,(unsigned long)s1*s3*sizeof(double));
    for ( i1=0 ; i1<s1 ; i1++) {
        buf1 = i1*s2;
        buf4 = i1*s3;
        for ( i2=min_s2 ; i2<max_s2 ; i2++) {
            buf2 = i2*s3;
            buf3 = buf1 +i2;
            for ( i3=0 ; i3<s3 ; i3++) {
                result[buf4+i3] += a[buf3] * b[buf2 + i3];
            }
        }
    }
}

void * workerCPU1(void * mm){
    multiple_matrix *m = (multiple_matrix *)mm;
    int min_s2 = (m->s2 / m->worker)* m->index;
    int max_s2 = (m->s2 / m->worker)* (m->index+1);
    dmultiple_o2_min_max_s2(m->a,m->b,m->result,m->s1,min_s2,max_s2,m->s2,m->s3);
    
    return NULL;
}

void dplus(double * a, double * b, double * result,int s1, int s2){
    int i;
    int s = s1*s2;
    for (i=0; i<s; i++) {
        result[i] = a[i] + b[i];
    }
}

void dmultiple_o3(double * a, double * b, double * result, int s1, int s2, int s3, int worker){
    int i;
    multiple_matrix mm[worker];
    for (i=0; i<worker; i++) {
        mm[i].a         = a;
        mm[i].b         = b;
        mm[i].result    = malloc(sizeof(double)*s1*s3);
        mm[i].s1        = s1;
        mm[i].s2        = s2;
        mm[i].s3        = s3;
        mm[i].worker    = worker;
        mm[i].index     = i;
        pthread_create(&(mm[i].tid),NULL,workerCPU1,(void*)&(mm[i]));
    }
    if(s2%worker != 0){
        dmultiple_o2_min_max_s2(a,b,result,s1,(s2/worker)*worker,s2,s2,s3);
    }
    else{
        (void)memset(result,0,(unsigned long)s1*s3*sizeof(double));
    }
    i=0;
    while (i < worker) {
        pthread_join(mm[i].tid,NULL);
        dplus(result,mm[i].result,result,s1,s3);
        free(mm[i].result);
        i++;
    }
}

void * workerCPU2(void * mm){
    multiple_matrix *m = (multiple_matrix *)mm;
    int min_s1 = (m->s1 / m->worker)* m->index;
    int max_s1 = (m->s1 / m->worker)* (m->index+1);
    dmultiple_o1_min_max_s1(m->a,m->b,m->result,min_s1,max_s1,m->s1,m->s2,m->s3);
    
    return NULL;
}

void dmultiple_o4(double * a, double * b, double * result, int s1, int s2, int s3, int worker){
    int i;
    multiple_matrix mm[worker];
    for (i=0; i<worker; i++) {
        mm[i].a         = a;
        mm[i].b         = b;
        mm[i].result    = result;
        mm[i].s1        = s1;
        mm[i].s2        = s2;
        mm[i].s3        = s3;
        mm[i].worker    = worker;
        mm[i].index     = i;
        pthread_create(&(mm[i].tid),NULL,workerCPU2,(void*)&(mm[i]));
    }
    if(s1%worker != 0){
        dmultiple_o1_min_max_s1(a,b,result,(s1/worker)*worker,s1,s1,s2,s3);
    }
    i=0;
    while (i < worker) {
        pthread_join(mm[i].tid,NULL);
        i++;
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

char dcheck_matrix(double * a, double * b, int s1, int s2,double threshold){
    int same = 0,i,s=s1*s2 , round_s = 0;
    for (i=0; i<s; i++) {
        double diff = ((a[i]-b[i]) / ((a[i]+b[i]) / 2))*100; //diff from avg in percent
        if(diff > threshold || diff < threshold*(-1)){
            same = 1;
            printf("index[%d]\ta[%.16e]\tb[%.16e]\tdiff[%.16e]%%\r\n",i,a[i],b[i],diff);
            round_s++;
            if(round_s == 10){
                break;
            }
        }
    }
    
    return same;
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
