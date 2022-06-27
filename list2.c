#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define RND_SCALE 50
#define LIST_SIZE 200

//list structure
typedef struct list {
    int value;
    struct list *next;
    struct list *previous;
} list;

//create a list initialized with random integers
list * create_list(int size) {
    int i;
    list *pl, *head;

    //if size zero or negative, return empty list
    if(size <= 0) {
        return NULL;
    } 

    //create first element
    head = (list *)malloc(sizeof(list));
    head->value = rand() % RND_SCALE;
    head->previous = NULL;
    head->next = NULL;
    pl = head;
    //create remaining size-1 elements
    for(i=1; i<size; i++) {
        pl->next = (list *)malloc(sizeof(list));
        pl->next->value = rand() % RND_SCALE;
        pl->next->previous = pl;
        pl->next->next = NULL;
        pl = pl->next;
    }
    //return first element
    return head;
}

//free allocated memory for list (recursive)
void free_list(list *l) {
    //if list empty do nothing
    if(l == NULL) {
        return;
    }
    //if next element exists, recursive call
    if(l->next) {
        free_list(l->next);
    }
    //free current element
    free(l);
}

//display list (recursive function)
void print_list(list *l, int row) {
    if(l == NULL) {
        printf("\n");
    }
    else {
        printf("%-6d ", l->value);
        //if last row print new line
        if(row == 4) {
            printf("\n");
        }
        row = (row+1) % 5;
        print_list(l->next, row);
    }    
}

//merge two sorted lists
list *merge_list(list *l1, list *l2) {
    list *res, *pl1, *pl2, *pres;
    pl1 = l1;
    pl2 = l2;

    //if one of the list is empty return the other (also works if both are empty)
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    //select list with smaller value
    if(l1->value <= l2->value) {
        res = l1;
        pl1 = pl1->next;
    }
    else {
        res = l2;
        pl2 = pl2->next;
    }
    pres = res;
    while(pl1 != NULL && pl2 != NULL) {
        if(pl1->value <= pl2->value) {
            pres->next = pl1;
            pl1 = pl1->next;
        }
        else {
            pres->next = pl2;
            pl2 = pl2->next;
        }
        pres->next->previous = pres;
        pres = pres->next;
    }
    if(pl1 != NULL) {
        pres->next = pl1;
    }
    else if(pl2 != NULL) {
        pres->next = pl2;
    }
    pres->next->previous = pres;
    return res;
}

//check list length
int list_len(list *l) {
    list *pl = l;
    int len;
    if(l == NULL) {
        return 0;
    }
    len = 1;
    while(pl->next != NULL) {
        len++;
        pl = pl->next;
    }
    return len;
}

//merge sort, for recursive call
list *merge_sort_recursive(list *l, int len) {
    int i, temp;
    list *pl = l;

    //terminal cases if len is 1 or 2
    if(len == 1) {
        return l;

    }
    else if(len == 2) {
        if(l->next->value < l->value) {
            temp = l->value;
            l->value = l->next->value;
            l->next->value = temp;
        }

        return l;
    }
    //otherwise split into two lists, recursive call and merge
    for(i=0; i<len/2; i++) {
        pl = pl->next;
    }
    //separate lists
    pl->previous->next = NULL;
    pl->previous = NULL;
    l = merge_sort_recursive(l, len/2);
    pl = merge_sort_recursive(pl, len - len/2);
    return merge_list(l, pl);
}

//sort list with merge sort
list *merge_sort(list *l) {
    int len;

    //if list is empty or of len 1, just return it
    if(l == NULL || l->next == NULL) {
        return l;
    }

    len = list_len(l);
    return merge_sort_recursive(l, len);
}

//check if ascending order
int is_ascending(list *l) {
    list *pl = l;
    while(pl->next != NULL) {
        if(pl->value > pl->next->value) {
            return 0;
        }
        pl = pl->next;
    }
    return 1;
}

//remove duplicates
void remove_duplicates(list *l) {
    list *pl =l, *pl2;
    int val_ref;
    if(pl == NULL) return;

    val_ref = pl->value;
    while(pl->next != NULL) {
        if(pl->next->value == val_ref) {
            pl2 = pl->next;
            pl->next = pl->next->next;
            if(pl->next != NULL) {
                pl->next->previous = pl;
            }
            free(pl2);
        } else {
            pl = pl->next;
            val_ref = pl->value;
        }
    }  
}

int main(void) {
    list *l, *l2;

    srand(time(0));
    //create list with random data
    l = create_list(LIST_SIZE);
    printf("Random list of %d elements\n", LIST_SIZE);
    print_list(l, 0);
    
    //sort list with merge sort
    l2 = merge_sort(l);
    //printf("Sorted list of length %d\n", list_len(l2));
    //print_list(l2, 0);
    //printf("Is list in ascending order (1 for yes, 0 for no): %d\n", is_ascending(l2));
    
    //remove duplicates and print list
    remove_duplicates(l2);
    printf("Sorted list without duplicates of length %d\n", list_len(l2));
    print_list(l2, 0);
    free_list(l2);

    return 0;
}