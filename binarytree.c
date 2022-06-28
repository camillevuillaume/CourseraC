#include <stdlib.h>
#include <stdio.h>

typedef struct binary_tree {
    int value;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree *create_binary_tree(int size, int *values) {
    return NULL;
}

void free_binary_tree(binary_tree *t) {
    if(t != NULL) {
        free_binary_tree(t->left);
        free_binary_tree(t->right);
        free(t);
    }
}

int main(int argc, char *argv[]) {
    int i;
    int *array = (int *)malloc(argc * sizeof(int));
    for(i=1; i<argc; i++) {
        array[i-1] = atoi(argv[i]);
        printf(" %d ", array[i-1]);
    }
    printf("\n");

}