#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
    int* array;
    int n, temp;
    int max;
    int i,j;

    scanf("%d", &n);

    array = (int*)malloc(sizeof(int) * n);

    /*�迭 �� ����*/
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    /*���� ����*/
    for (i = n - 1; i > 0; i--) {
        
        max = 0;
        for (j = 1; j <= i; j++) {
            if (array[max] < array[j]) {
                max = j;
            }
        }
       
        //��ȯ
        temp = array[i];
        array[i] = array[max];
        array[max] = temp;
    }

    for (i = 0; i < n; i++) {
        printf(" %d", array[i]);
    }

    return 0;
}
 