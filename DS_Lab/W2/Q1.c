#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n) {
    *p = (int **)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; ++i)
        (*p)[i] = (int *)malloc(sizeof(int) * n);
}

int main() {
    int **array, *a;
    allocArray(&array, 5, 10);
    for (int j = 0; j < 5; j++)
        for (int k = 0; k < 10; k++)
            array[j][k] = j * 10 + k;
    for (int j = 0; j < 5; j++)
        for (int k = 0; k < 10; k++)
            printf("%p ", &(array[j][k]));
    for (int i = 0; i < 5; ++i)
        free(array[i]);
    free(array);
}

/*another solution
#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n) {
    int *data = (int *)malloc(sizeof(int) * m * n);
    *p = (int **)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; ++i)
        (*p)[i] = data + i * n;
}

int main() {
    int **array;
    allocArray(&array, 5, 10);
    for (int j = 0; j < 5; j++)
        for (int k = 0; k < 10; k++)
            array[j][k] = j * 10 + k;
    for (int j = 0; j < 5; j++)
        for (int k = 0; k < 10; k++)
            printf("%p ", &(array[j][k]));
    free(array[0]);
    free(array);
}
*/
