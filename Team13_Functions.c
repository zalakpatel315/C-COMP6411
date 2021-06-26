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
struct _listnode* originalList; 


void printList(struct _listnode *originalList);
void printListRecur(struct _listnode *originalList);
void printCar(struct _listnode *originalList);
void printCdr(struct _listnode *originalList);
void printCarOfCar(struct _listnode *originalList);

element aasel(atom a);
element atomCompare(struct _listnode *originalList, atom a);

list cons(element e, list l);

void main()
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
    
    originalList = malloc(sizeof *originalList);
    originalList->el = ele_a;
    originalList->next = point_bc;
    
    if(originalList != NULL) {
        printList(originalList);
        printf("\n");
        printCar(originalList);
        printf("\n");
        printCdr(originalList);
        printf("\n");
        printCarOfCar(originalList);
        
        element matchedElement =  aasel('a');
        printf("\nMatched element : %c", matchedElement.a);
        
        struct _listnode *newList = cons(ele_a, point_bc);
        printf("\n");
        printList(newList);
    }
    free(originalList);
	originalList = NULL;
}


void printList(struct _listnode *originalList) {
    printf("(");
    printListRecur(originalList);
    printf(")");
}

void printListRecur(struct _listnode *originalList) {
    if(originalList != NULL) {
        if(originalList->el.type == ATOM) {
            printf(" %c ",(originalList->el.a));
        }
        else if(originalList->el.type == LIST) {
            printf("(");
            printListRecur(originalList->el.l);
            printf(")");
        }
    }
    if(originalList->next != NULL) {
        printListRecur(originalList->next);
    }
}

void printCar(struct _listnode *originalList) {
    if(originalList != NULL) {
        if(originalList->el.type == ATOM) {
            printf(" %c ",(originalList->el.a));
        }
        else if(originalList->el.type == LIST) {
            printf("(");
            printListRecur(originalList->el.l);
            printf(")");
        }
    }
}

void printCdr(struct _listnode *originalList) {
    if(originalList->next != NULL) {
        printf("(");
        printListRecur(originalList->next);
        printf(")");
    }
}

void printCarOfCar(struct _listnode *originalList) {
    if(originalList != NULL) {
        if(originalList->el.type == ATOM) {
            printf("NIL");
        }
        else if(originalList->el.type == LIST) {
            printCar(originalList->el.l);
        }
    }
}

element aasel(atom a) {
    element matchedElement;
     if(originalList != NULL) {
        
        if(originalList->el.type == ATOM && originalList->el.a == a) {
            return originalList->el;
        }
        else if(originalList->el.type == LIST) {
            matchedElement = atomCompare(originalList->el.l, a);
        }
    }
    if(matchedElement.type == ATOM) 
        return matchedElement;
    

    return atomCompare(originalList->next, a);
}

element atomCompare(struct _listnode *originalList, atom a) {
    element matchedElement;
    if(originalList != NULL) {
        if(originalList->el.type == ATOM) {
            if(originalList->el.a == a)
                return originalList->el;
        }
        else if(originalList->el.type == LIST) {
            matchedElement = atomCompare(originalList->el.l, a);
            if(matchedElement.type == ATOM)
                return matchedElement;
        }
    }
    if(originalList->next != NULL) {
          matchedElement = atomCompare(originalList->next, a);
            if(matchedElement.type == ATOM)
                return matchedElement;
    }
    return NIL;
}

list cons(element e, list l) {
    struct _listnode *newList = malloc(sizeof *newList);
    newList->el = e;
    newList->next = l;
    return newList;
}


