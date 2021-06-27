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


void printList(list originalList);
void printListRecur(list originalList);
void printCar(list originalList);
void printCdr(list originalList);
void printCarOfCar(list originalList);

element aasel(atom a);
element atomCompare(list originalList, atom a);

list cons(element e, list l);

element car(element e);

list cddr(element e);

void lfree(list l);

void main()
{
    element ele_a = {ATOM, 'a'};
    
    list point_c = malloc(sizeof *point_c);
    element ele_c = {ATOM, 'c'};
    point_c->el = ele_c;
    point_c->next = NULL;
    
    list point_b = malloc(sizeof *point_b);
    element ele_b = {ATOM, 'b'};
    point_b->el = ele_b;
    point_b->next = point_c;
    
    element ele_bc; 
    ele_bc.type = LIST;
    ele_bc.l = point_b;

    element ele_d = {ATOM, 'd'};
    element ele_e = {ATOM, 'e'};
    
    list point_e = malloc(sizeof *point_e);
    point_e->el = ele_e;
    point_e->next = NULL;
    
    list point_d = malloc(sizeof *point_d);
    point_d->el = ele_d;
    point_d->next = point_e;
    
    list point_bc = malloc(sizeof *point_bc);
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
        printf("\n\nFunction 1 : Matched element : %c", matchedElement.a);
        
        list newList = cons(ele_bc, point_e);
        printf("\nFunction 3 : ");
        printList(newList);
        
        element carElement = car(ele_bc);
        printf("\nFunction 5 : Car of element : %c", carElement.a);
        
        
        list point_z = malloc(sizeof *point_z);
        element ele_z = {ATOM, 'z'};
        point_z->el = ele_z;
        point_z->next = NULL;
        
        list point_y = malloc(sizeof *point_y);
        element ele_y = {ATOM, 'y'};
        point_y->el = ele_y;
        point_y->next = point_z;
        
        list point_x = malloc(sizeof *point_x);
        element ele_x = {ATOM, 'x'};
        point_x->el = ele_x;
        point_x->next = point_y;
        
        list point_w = malloc(sizeof *point_w);
        element ele_w = {ATOM, 'w'};
        point_w->el = ele_w;
        point_w->next = point_x;
        
        list point_v = malloc(sizeof *point_v);
        element ele_v = {ATOM, 'v'};
        point_v->el = ele_v;
        point_v->next = point_w;
        
        element ele_vwxyz; 
        ele_vwxyz.type = LIST;
        ele_vwxyz.l = point_v;
        
        list cddrList = cddr(ele_vwxyz);
        printf("\nFunction 7 : cddr of vwxyz : %c %c %c", cddrList->el.a, cddrList->next->el.a, cddrList->next->next->el.a);
        
        lfree(originalList);
        printf("\nFunction 9 : freed all the memory allocated");
    }
    free(originalList);
	originalList = NULL;
}

element createAtomElement(atom r){
    element e;
    e.type = ATOM;
    e.a = r;
    return e;
}

void addElement(struct _listnode* head ,element ele){
    printf("entered add element\n");
    struct _listnode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (struct _listnode*) malloc(sizeof(struct _listnode));
    current->next->el = ele;
    current->next->next = NULL;
}
element createListElement(struct _listnode* startOfList){
    element e;
    e.type = LIST;
    e.l = startOfList;
    return e;
}
struct _listnode* createSubList(){
    struct _listnode* newList = (struct _listnode*) malloc(sizeof(struct _listnode));
    newList->next=NULL;
    int numberNodes, i, choice;
    char tempC;
    printf("enter number of nodes : ");
    scanf("%d", &numberNodes);
    printf("Press 1 for atom, 2 for List : ");
    scanf("%d", &choice);
    if(choice == 1){
        printf("Enter character : ");
        scanf(" %c", &tempC);
        newList->el = createAtomElement(tempC);
    }else{
        newList->el = createListElement(createSubList());
    }
    for(i=1; i<numberNodes; i++){
        printf("Press 1 for atom, 2 for List : ");
        scanf("%d", &choice);
        if(choice == 1){
            printf("Enter character : ");
            scanf(" %c", &tempC);
            addElement(newList, createAtomElement(tempC));
        }else{
            addElement(newList, createListElement(createSubList()));
        }
    }
    return newList;
}
void createList(struct _listnode* mainList){
    int numberNodes, i, choice;
    char tempC;
    printf("enter number of nodes : ");
    scanf("%d", &numberNodes);
    printf("Press 1 for atom, 2 for List : ");
    scanf("%d", &choice);
    if(choice == 1){
        printf("Enter character : ");
        scanf(" %c", &tempC);
        mainList->el = createAtomElement(tempC);
    }else{
        mainList->el = createListElement(createSubList());
    }
    for(i=1; i<numberNodes; i++){
        printf("Press 1 for atom, 2 for List : ");
        scanf("%d", &choice);
        if(choice == 1){
            printf("Enter character : ");
            scanf(" %c", &tempC);
            addElement(mainList, createAtomElement(tempC));
        }else{
            addElement(mainList, createListElement(createSubList()));
        }
    }
}

void printList(list originalList) {
    printf("(");
    printListRecur(originalList);
    printf(")");
}

void printListRecur(list originalList) {
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

void printCar(list originalList) {
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

void printCdr(list originalList) {
    if(originalList->next != NULL) {
        printf("(");
        printListRecur(originalList->next);
        printf(")");
    }
}

void printCarOfCar(list originalList) {
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

element atomCompare(list originalList, atom a) {
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
    list newList = malloc(sizeof *newList);
    newList->el = e;
    newList->next = l;
    return newList;
}


element car(element e) {
    if(e.type == ATOM) {
        return NIL;
    }
    else if(e.type == LIST) {
        return e.l->el;
    }
}

list cddr(element e) {
    if(e.type == LIST) {
        list firstNodePointer = e.l->next; //ele w, ref to x
        list secondNodePointer = firstNodePointer->next; //ele x, ref to y
        return secondNodePointer;
    }
}

void lfree(list l){
    list temp;
   while (l != NULL)
    {
        if(l->el.type == LIST){
            lfree(l->el.l);
        }
        if(l->next == NULL) {
            free(l);
            break;
        } else {
            temp = l;
            l = l->next;
            free(temp);
        }
    }
}
