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

element aasel(atom a);
element atomCompare(list originalList, atom a);
element lasel(list l);
element listCompare(list l1, list l2);
list cons(element e, list l);
list append(l1, l2);
element car(element e);
list cdr(element e);
list cddr(element e);
void print(element e);
void lfree(list l);
void printList(list originalList);
void printListRecur(list originalList);
void printCarOfCar(list originalList);


int main()
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

    element ele_abcde;
    ele_abcde.type = LIST;
    ele_abcde.l = originalList;

    /* Uncomment to create and test on a new list based on custom input */

    //printf("\nCreating a New List from User Input....");
    //list tryList= (struct _listnode*) malloc(sizeof(struct _listnode));
    //tryList->next=NULL;
    //createList(tryList); //function does not return anything, but the created list remains stored in the pointer.
    //printList(tryList);

    if(originalList != NULL) {

        /* Print Given List in Format */
        printList(originalList);
        printf("\n");

        /*Print Car of Given List */
        print(car(ele_abcde));
        printf("\n");

        /* Print Cdr of Given List */
        printList(cdr(ele_abcde));
        printf("\n");

        /* Print Car of Car of Given List */
        printCarOfCar(originalList);

        /* Testing Function assel */
        element matchedElement =  aasel('a');
        printf("\n\nFunction 1 : Matched element : %c", matchedElement.a);

        /* Testing Function lasel */
        element matchListElement=lasel(ele_bc.l);
        printf("\nFunction 2 : First Element of List Referenced:  %c ", matchListElement.l->el.a);

        /* Testing Function cons */
        list newList = cons(ele_bc, point_e);
        printf("\nFunction 3 : Cons of Element ");
        print(ele_bc);
        printf(" and List ");
        printList(point_e);
        printf(" is ");
        printList(newList);

        /* Testing Function append */

        // Creating a new List

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

        list l3 = append(originalList, ele_vwxyz.l);
        printf("\nFunction 4 : Appended List Output : ");
        printList(l3);

        /* Testing Function car */
        element carElement = car(ele_bc);
        printf("\nFunction 5 : For List ");
        print(ele_bc);
        printf(" Car of element is %c", carElement.a);

        /* Testing Function cdr */
        list cdrList = cdr(ele_vwxyz);
        printf("\nFunction 6 : CDR of List ");
        print(ele_vwxyz);
        printf(" is ");
        printList(cdrList);

        /* Testing Function cddr */
        list cddrList = cddr(ele_vwxyz);
        printf("\nFunction 7 : Cddr of List ");
        print(ele_vwxyz);
        printf(" is ");
        printList(cddrList);

        /* Testing Function print */
        printf("\nFunction 8 : Print function, ");
        printf("for List Element: ");
        print(ele_vwxyz);
        printf(", for Atom Element: ");
        print(ele_z);
        printf(", for NIL Element: ");
        print(NIL);

        /*Testing Function lfree */
        lfree(originalList);
        printf("\nFunction 9 : Freed all the memory allocated");
    }
    free(originalList);
	originalList = NULL;
	return 0;
}

/* Function 1: Aasel Function: AKA atom as element, returns an element whose content is set to atom a. */

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

/* Util Function of atomCompare */

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

/* Function 2: element lasel(list l); AKA list as element, returns an element whose content is set to the list, pointed by l */

element lasel(list l){
    element matchedElement;
     if(originalList != NULL) {

        if(originalList->el.type == LIST && originalList->el.l == l) {
            return originalList->el;
        }
        else if(originalList->el.type == LIST) {
            matchedElement = listCompare(originalList->el.l, l);
        }
    }
    if(matchedElement.type == LIST && matchedElement.l!=NULL)
        return matchedElement;


    return listCompare(originalList->next, l);
}

/* Util Function of Lasel */

element listCompare(list originalList, list l) {
    element matchedElement;
    if(originalList != NULL) {
        if(originalList->el.type == LIST && originalList->el.l == l) {
                return originalList->el;
        }
        else if(originalList->el.type == LIST) {
            matchedElement = listCompare(originalList->el.l, l);
            if(matchedElement.type == LIST && matchedElement.l!=NULL)
                return matchedElement;
        }
    }
    if(originalList->next != NULL) {
          matchedElement = listCompare(originalList->next, l);
            if(matchedElement.type == LIST && matchedElement.l!=NULL)
                return matchedElement;
    }
    return NIL;
}

/* Function 3: list cons(element e, list l); that creates a new list whose car and cdr are the element e and the list l. While the memory for the newly created list is to be allocated dynamically */

list cons(element e, list l) {
    list newList = malloc(sizeof *newList);
    newList->el = e;
    newList->next = l;
    return newList;
}

/* Function 4: list append(LIST l1, list l2); that creates a new list whose elements are shallow copies of elements in l2 and l2, appended. */

list append(list l1, list l2){
    list result = NULL;
    if(l1 == NULL ){
        return (l2);
    }
    else if (l2 == NULL){
        return (l1);
    }
    else{
        result = l1;
        result->next = append(l1->next, l2);
    }
}

/* Function 5: element car(element e); that returns head of the list, represented by e; returns NIL, if e is not a list. */

element car(element e) {
    if(e.type == ATOM) {
        return NIL;
    }
    else if(e.type == LIST) {
        return e.l->el;
    }
}

/* Function 6: list cdr(element e); that returns tail of the list, represented by e */

list cdr(element e){
    if(e.type == ATOM){
        return NULL;
    }else{
        return(e.l->next);
    }
}

/* Function 7: list cddr(element e); that similarly returns the cddr of the list, represented by e */

list cddr(element e) {
    if(e.type == LIST) {
        list firstNodePointer = e.l->next; //ele w, ref to x
        list secondNodePointer = firstNodePointer->next; //ele x, ref to y
        return secondNodePointer;
    }
}

/* Function 8: void print(e); that prints the content of the element e. If e is an atom, it prints the
symbol enclosed in spaces, and if e it is a list, if prints recursively prints the elements
of the list enclosed in parentheses. If e is NIL, the word “NIL” must be printed. */

void print(element e){
    if(e.type == LIST && e.l == NULL){
        printf(" NIL ");
    }else if(e.type == LIST && e.l!=NULL){
        printList(e.l);
    }else{
        printf(" %c ", e.a);
    }
}
/* Utils for Print Function */

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

/* Function 9: void free(LIST l); that frees all the memory previously allocated by the whole list (including all its elements and its inner lists) */

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

/* Function to print Car of Car */

void printCarOfCar(list originalList) {
    if(originalList != NULL) {
        if(originalList->el.type == ATOM) {
            printf("NIL");
        }
        else if(originalList->el.type == LIST) {
            print(car(originalList->el));
        }
    }
}
/* Define and Create Custom List Functions */

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
    printf("\nEnter number of sublist nodes : ");
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
    printf("\nEnter number of nodes : ");
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
