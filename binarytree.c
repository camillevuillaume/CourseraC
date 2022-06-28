#include <stdlib.h>
#include <stdio.h>

//structure for binary tree
typedef struct binary_tree {
    int value;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

//create root node from value
binary_tree * create_binary_tree(int value) {
    binary_tree *t = (binary_tree *)malloc(sizeof(binary_tree));
    t->value = value;
    t->left = NULL;
    t->right = NULL;
    return t;
}

//add value to left of element of binary tree
binary_tree * add_left(binary_tree * t, int value) {
    if(t->left == NULL) {
        t->left = (binary_tree *)malloc(sizeof(binary_tree));
    }
    t->left->value = value;
    t->left->left = NULL;
    t->left->right = NULL;
    return t->left;
}

//add value to right of element of binary tree
binary_tree * add_right(binary_tree * t, int value) {
    if(t->right == NULL) {
        t->right = (binary_tree *)malloc(sizeof(binary_tree));
    }
    t->right->value = value;
    t->right->left = NULL;
    t->right->right = NULL;
    return t->right;
}

//traverse and free binary tree, recursive
void free_binary_tree(binary_tree *t) {
    if(t != NULL) {
        free_binary_tree(t->left);
        free_binary_tree(t->right);
        free(t);
    }
}

//create tree based on array
binary_tree * populate_tree(int size, int *array) {
    int i;
    binary_tree *t, *pt;
    if(size == 0 || array == NULL) return NULL;
    //initialize tree
    t = create_binary_tree(array[0]);
    for(i = 1; i< size; i++) {
        pt = t;
        while(1) {
            //if array value is smaller or equal than current value in tree go left
            if(array[i] <= pt->value) {
                //if leaf reached, generated it and go to next array value
                if(pt->left == NULL) {
                    add_left(pt, array[i]);
                    break;
                }
                //otherwise continue tree parsing
                pt = pt->left;
            }
            else {
                //if array value is greater than current value in tree go right
                if(pt->right == NULL) {
                    add_right(pt, array[i]);
                    break;
                }
                pt = pt->right;
            }
        }
    }
    return t;

}

//print binary tree in order, recursive
void print_inorder(binary_tree *t) {
    if(t != NULL) {
        if(t->left != NULL) {
            print_inorder(t->left);
        }
        printf(" %d ", t->value);
        if(t->right != NULL) {
            print_inorder(t->right);
        }
    }
}

//load array from file
int * load_array_from_file(char *path) {
    int size, i;
    int *array;
    FILE *fp;
    fp = fopen(path, "r");
    if(fscanf(fp, "%d ", &size) == 0) return NULL;
    array = (int *)malloc(sizeof(int)*(size+1));
    array[0] = size;
    for(i=1; i<size+1; i++) {
        fscanf(fp, "%d", &array[i]);
    }
    fclose(fp);
    return array;
}

int main(int argc, char *argv[]) {
    int i;
    binary_tree *t;
    char *path;
    if(argc != 2) {
        printf("Please supply path\n");

    }
    else {
        path = argv[1];
    }
    int *array = load_array_from_file(path);

    //print array read from argv
    printf("Data in file %s, excluding first int which is number of elements in file \n", path);
    for(i=1; i<array[0]+1; i++) {
        printf(" %d ", array[i]);
    }
    printf("\n");
    //print binary tree generated from array, in order - should be values sorted from smallest to largest
    printf("Put data in binary tree, read in order\n");
    t = populate_tree(array[0], &array[1]);
    print_inorder(t);
    printf("\n");
    free_binary_tree(t);
    free(array);

}