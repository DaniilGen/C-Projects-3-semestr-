//
// Created by Даниил on 18.01.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int pr1(int *p, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("[%d]@[%p]\n", *(p + i), (p + i));
    }
}

void arr(int *p, int n) {
    int i;
    printf("%p\n", p);
    for (i = 0; i < n; i++, *p++ = rand() % 100);
}

void sort_f(int *p, int n) {
    int i, j;
    int temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (*(p + j) > *(p + j + 1)) {
                temp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = temp;
            }
        }
    }
}
void sort_s(int c[], int n) {
    int i, j;
    int temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (c[j] > c[j+1]) {
                temp = c[j];
                c[j] = c[j+1];
                c[j+1] = temp;
            }
        }
    }
}

void qs_s(int *a, int f, int l) {
    if (f < l) {
        int left = f, right = l, middle = a[(left + right) / 2];
        do {
            while (a[left] < middle) left++;
            while (a[right] > middle) right--;
            if (left <= right) {
                int temp = a[left];
                a[left] = a[right];
                a[right] = temp;
                left++;
                right--;
            }
        } while (left <= right);
        qs_s(a, f, right);
        qs_s(a, left, l);
    }
}
void qs_f(int* f, int* l) {
    if (l - f <= 1) return;
    int middle = *(f + (l - f) / 2);
    int *left = f, *right = l - 1;
    int temp;
    while (left <= right) {
        while (*left < middle) left++;
        while (*right > middle) right--;
        if (left <= right) {
            temp=*left;
            *left=*right;
            *right=temp;
            left++;
            right--;
        }
    }
    if (f < right) qs_f(f, right + 1);
    if (left < l) qs_f(left, l);
}

int main(void) {
    register double time;
    int *a, *b;
    if ((a= malloc(1000000*sizeof (int)))==NULL){
        printf("malloc: NULL\n");
        exit(1);
    }
    if ((b= malloc(1000000*sizeof (int)))==NULL){
        printf("malloc: NULL\n");
        exit(1);
    }
    arr(a, 1000000);
    arr(b, 1000000);


    clock_t begin = clock();
//    sort_s(a,100000);
    qs_s(a,0,1000000);
    clock_t end = clock();
    time= (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Time slow: %f \n", time);
    printf("\n");

    begin = clock();
//    sort_f(b,100000);
    qs_f(a,a+1000000-1);
    end = clock();
    time= (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Time fast: %f \n", time);
    printf("\n");

    return 0;
}
