#include <stdio.h>
#include <stdlib.h>

 
typedef enum { ATOM, LIST } eltype;
typedef char atom;
struct _listnode;

typedef struct {
eltype type;
union {
atom a;
struct _listnode* l;
};
} element;

typedef struct _listnode {
element el;
struct _listnode* next;
} * list;
const element NIL = { .type=LIST, .l=NULL };

void printList(struct _listnode *point_a);

int main()
{
    element ele_a = {ATOM, 'a'};
    
    struct _listnode *point_c = malloc(sizeof *point_c);
    element ele_c = {ATOM, 'c'};
    point_c->el = ele_c;
    point_c->next = NULL;
    
    struct _listnode *point_b = malloc(sizeof *point_b);
    element ele_b = {ATOM, 'b'};
    point_b->el = ele_b;
    point_b->next = point_c;
    
    element ele_bc; 
    ele_bc.type = LIST;
    ele_bc.l = point_b;

    element ele_d = {ATOM, 'd'};
    element ele_e = {ATOM, 'e'};
    
    struct _listnode *point_e = malloc(sizeof *point_e);
    point_e->el = ele_e;
    point_e->next = NULL;
    
    struct _listnode *point_d = malloc(sizeof *point_d);
    point_d->el = ele_d;
    point_d->next = point_e;
    
    struct _listnode *point_bc = malloc(sizeof *point_bc);
    point_bc->el = ele_bc;
    point_bc->next = point_d;
    
    struct _listnode *point_a = malloc(sizeof *point_a);
    point_a->el = ele_a;
    point_a->next = point_bc;
    
    if(point_a != NULL) {
        printf("(");
        printList(point_a);
        printf(")");
    }
    return 0;
}


void printList(struct _listnode *point_a) {
    if(point_a != NULL) {
        if(point_a->el.type == ATOM) {
            printf(" %c ",(point_a->el.a));
        }
        else if(point_a->el.type == LIST) {
            printf("(");
            printList(point_a->el.l);
            printf(")");
        }
    }
    if(point_a->next != NULL) {
        printList(point_a->next);
    }
}

