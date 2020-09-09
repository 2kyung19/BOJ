#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

void selection(int* array, int n);
void insertion(int* array, int n);
void reverse(int* array, int n);

int main(void) {
    int *A , *B;
    int n, num;
    int i, j;

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    srand(time(NULL));
    QueryPerformanceFrequency(&ticksPerSec);

    scanf("%d", &n);

    A = (int*)malloc(sizeof(int) * n);
    B = (int*)malloc(sizeof(int) * n);
    
    /*���� ����*/
    for (i = 0; i < n; i++) {
        num = rand();
        A[i] = num;
        B[i] = num;
    }

/* A : ���� ������ ���� */
    printf("\n** A\n");
    QueryPerformanceCounter(&start);
    /*����*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);
    
    QueryPerformanceCounter(&start);
    /*����*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart)*1000);
    
/* B : �̹� ���ĵ� �����͸� ����*/
    printf("\n** B\n");
    QueryPerformanceCounter(&start);
    /*����*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceCounter(&start);
    /*����*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


/* C : �������� ���ĵ� �����͸� ���� */
    reverse(A, n);
    reverse(B, n);

    printf("\n** C\n");
    QueryPerformanceCounter(&start);
    /*����*/ selection(A, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceCounter(&start);
    /*����*/ insertion(B, n);
    QueryPerformanceCounter(&end);
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("%.5f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    return 0;
}

void selection(int* array, int n) {
    int min,temp;
    int i,j;

    /*���� ����*/
    for (i = 0; i < n - 1; i++) {

        min = n - 1;
        for (j = n - 1; j >= i; j--) {
            if (array[min] > array[j]) {
                min = j;
            }
        }

        //��ȯ
        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void insertion(int* array, int n) {
    int exchange, temp;
    int i, j;

    /*���� ����*/
    for (i = 1; i < n; i++) {

        exchange = i;
        for (j = i - 1; j >= 0; j--) {
            if (array[exchange] > array[j]) {
                break;
            }

            //��ȯ
            temp = array[exchange];
            array[exchange] = array[j];
            array[j] = temp;

            exchange = j;
        }
    }
}

void reverse(int* array, int n) {
    int exchange, temp;
    int i, j;

    /*���� ����*/
    for (i = 1; i < n; i++) {

        exchange = i;
        for (j = i - 1; j >= 0; j--) {
            if (array[exchange] < array[j]) {
                break;
            }

            //��ȯ
            temp = array[exchange];
            array[exchange] = array[j];
            array[j] = temp;

            exchange = j;
        }
    }
}