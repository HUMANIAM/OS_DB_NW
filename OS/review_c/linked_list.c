/**
Author :    Ibrahim Saad
Date :      20/2/2019
Program :   Doubly linkedlist
Note :      this program can be easily extended to circular linkedlist


Functionality :
*************
1- create doubly linkedlist
2- push back of the linkedlist
3- push forward of the linkedlist
4- erese elements has specific value
5- searching for an element
6- reverse the linkedlist
7- you can easily add many features to this linkedlist
*/

// this code about coding one of the basic data structure in c (Linked list).
//It is a dynamic data structure whose length can be extended or shrinked with time (so it is memory is reserved in the heap)
/**
* Arrays are static data structure so you can't change their length in the run time and its elements are stored in  consuctive locations
* Linked Lists elements are scattered in the heap but they are connected in someway. It is like the graph be more specific like a path
* when you don't know the required memory that you need to store your data in the run time linked list is the best choice for you
* Vectors in c++ are similar to linked lists (I don't remember they based on linked lists or arrays with reallocation but i think the second)
*
*/
# include <stdio.h>
# include <stdlib.h>
#include  <stdbool.h>

// struct for node
struct Node{
    int val;
    struct Node* pre_node;
    struct Node* next_node;
};

typedef struct Node Node;

// struct for linked list
typedef struct Linkedlist{
    Node* head;
    Node* tail;
    int Size;
} Linkedlist;



//create new node
Node* create_new_node(int v){
    // create new node
    Node* n_node = (struct Node*) malloc(sizeof (struct Node));

    //failed in creation a new nod
    if (n_node == NULL){
        printf("failed in creating a new nod\n");
        exit(1);
    }

    //set attrs of the node
    n_node->pre_node = n_node->next_node = NULL;
    n_node->val = v;
}


// add new node at the beginning of the linked list
void push_front(Linkedlist* linklst, int val){
    //create new node
    Node* n_node = create_new_node(val);

    // update next of the new node
    n_node->next_node = linklst->head;

    // if linked list is empty then create node and make tail and head points to it
    if(linklst->head == NULL){
        linklst->head = linklst->tail = n_node;

    }else{
        linklst->head->pre_node = n_node;
        linklst->head = n_node;
    }

    //increase the size of the linkedlist
    linklst->Size += 1;
}


//add new node at the end of the linked list
Node* push_back(Linkedlist* linklst, int val){
    //create new node
    Node* n_node = create_new_node(val);

    // update next of the new node
    n_node->pre_node = linklst->tail;

    // if linked list is empty then make tail and head points to the new node
    if(linklst->tail == NULL){
        linklst->tail = linklst->head = n_node;

    }else{
        linklst->tail->next_node = n_node;
        linklst->tail = n_node;
    }

    //increase the size of the linkedlist
    linklst->Size += 1;
}


// find element node
bool find_node(Linkedlist linked_list, int val){
    // linear search in the linked list
    while(linked_list.head != NULL){
        if (linked_list.head->val == val) return true;

        //update the indicator to point the previous node
        linked_list.head = linked_list.head->next_node;
    }

    //this element not exist in the linked list
    return false;

}


//delete element
void delete_from_linkedlist(Linkedlist* linkedlist, int val){
    //search for nodes has value val
    Node* ptr_head = linkedlist->head;

    while(ptr_head != NULL){
        // next node in the linked list keep it before free the current node which the ptr_head points to
        Node* next_head = ptr_head->next_node;

        //current node has value = val
        if(ptr_head->val == val){

            // if my previous node isn't NULL then make it points to my next node
            if (ptr_head->pre_node != NULL)
                ptr_head->pre_node->next_node = ptr_head->next_node;

            else{  // it is the head node
                linkedlist->head = ptr_head->next_node;
            }

            //if my next node isn't NULL then make it points to my previous node
            if (ptr_head->next_node != NULL)
                ptr_head->next_node->pre_node = ptr_head->pre_node;

            else {  // it is the tail node
                linkedlist->tail = ptr_head->pre_node;
            }

            //delete this node
            free(ptr_head);

            //decrease the size of the linkedlist
            linkedlist->Size -= 1;
        }

        //update head pointer to the next node
        ptr_head = next_head;
    }
}

//reverse the linkedlist
void reverse_linkedlist(Linkedlist* linkedlist){
    Node* head_ptr = linkedlist->head;

    //swap pointers of every node in the linkedlist
    while(head_ptr != NULL){
        //swap nextpointer and prepointer
        Node* tmp_ptr = head_ptr->next_node;
        head_ptr->next_node = head_ptr->pre_node;
        head_ptr->pre_node = tmp_ptr;

        //update head_ptr to the next node
        head_ptr = tmp_ptr;
    }

    //swap head and tail
    head_ptr = linkedlist->head;
    linkedlist->head = linkedlist->tail;
    linkedlist->tail = head_ptr;
}

// print backward
void print_backward_linkedlist(Linkedlist lklst){
    while(lklst.tail != NULL){
        printf("%d ", lklst.tail->val);
        lklst.tail = lklst.tail->pre_node;
    }
    printf("\n");
}

// print forward
void print_forward_linkedlist(Linkedlist lklst){
    while(lklst.head != NULL){
        printf("%d ", lklst.head->val);
        lklst.head = lklst.head->next_node;
    }
    printf("\n");
}


//main function
int main(){

    //create new linked list
    Linkedlist linkedlist = {.head = NULL, .tail = NULL, .Size = 0};

    //add some elements
    int i = 1;
    while(i<11) push_back(&linkedlist, i++);


    printf("\n**** Size of the linked list = %d  *** \n", linkedlist.Size);
    printf("\n***   Linked list elements in forward walking    ***\n");
    //print forward
    print_forward_linkedlist(linkedlist);

    printf("\n***   Linked list elements in backward walking ***\n");
    //print backward
    print_backward_linkedlist(linkedlist);

    printf("\n***   Search for element 10 in the linked list if exist delete it ***\n");
    //find element in the linked list
    if(find_node(linkedlist, 10)){
        //delete value from the linked list
        delete_from_linkedlist(&linkedlist, 10);
    }

    printf("\n**** Size of the linked list = %d  *** \n", linkedlist.Size);
    printf("\n***   Linked list elements in forward walking  after deleting 55  ***\n");
    //print forward
    print_forward_linkedlist(linkedlist);

    //reverse the linked list
    printf("\n******* before reverse the linkedlist    *******\n");
    print_forward_linkedlist(linkedlist);
    reverse_linkedlist(&linkedlist);
    printf("\n******* after reverse the linkedlist    *******\n");
    print_forward_linkedlist(linkedlist);

   return 0;
}
