/* list.c */

#include "list.h"

/* Internal Function Prototypes */

static struct node*	reverse(struct node *curr, struct node *next);
static struct node *	msort(struct node *head, node_compare f);
static void		split(struct node *head, struct node **left, struct node **right);
static struct node *	merge(struct node *left, struct node *right, node_compare f);

/**
 * Create list.
 *
 * This allocates a list that the user must later deallocate.
 * @return  Allocated list structure.
 */
struct list *	list_create() {
    struct list* newList = malloc(sizeof(struct list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/**
 * Delete list.
 *
 * This deallocates the given list along with the nodes inside the list.
 * @param   l	    List to deallocate.
 * @return  NULL pointer.
 */
struct list *	list_delete(struct list *l) {
    /*struct node* current = l->head;
    struct node* next = NULL;

    while(current != NULL)
    {
        next = current->next;
        node_delete(current);
        current = next;
    }
    */
    if(l->head != NULL)
        node_delete(l->head,true);

    free(l);
    return NULL;
}

/**
 * Push front.
 *
 * This adds a new node containing the given string to the front of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_front(struct list *l, char *s) {
        struct node* newNode = node_create(s,l->head);
        l->head = newNode;
        l->size++;
        if(l->size == 1)
            l->tail = newNode;
}

/**
 * Push back.
 *
 * This adds a new node containing the given string to the back of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_back(struct list *l, char *s) {
        struct node* newNode = node_create(s,NULL);
        l->size++;
        if(l->size == 1)
            l->head = newNode;
        else
            l->tail->next = newNode;
        l->tail = newNode;
}

/**
 * Dump list to stream.
 *
 * This dumps out all the nodes in the list to the given stream.
 * @param   l	    List structure.
 * @param   stream  File stream.
 */
void		list_dump(struct list *l, FILE *stream) {
        struct node* current = l->head;

        while(current != NULL)
        {
            node_dump(current,stdout);
            current = current->next;
        }
}

/**
 * Convert list to array.
 *
 * This copies the pointers to nodes in the list to a newly allocate array that
 * the user must later deallocate.
 * @param   l	    List structure.
 * @return  Allocate array of pointers to nodes.
 */
struct node **	list_to_array(struct list *l) {
    struct node ** list = malloc(sizeof(struct node*) * l->size);
    struct node* curNode = l->head;
    for(int i = 0; i < l->size; i++)
    {
        list[i] = curNode;
        curNode = curNode->next;
    }
    return list;
}

/**
 * Sort list using qsort.
 *
 * This sorts the list using the qsort function from the standard C library.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_qsort(struct list *l, node_compare f) {
    struct node** array = list_to_array(l);
    qsort(array,l->size,sizeof(struct node *),f);

    for(int i = 0; i < l->size-1; i++)
        array[i]->next = array[i+1];

    l->head = array[0];
    l->tail = array[l->size-1];
    array[l->size-1]->next = NULL;

    free(array);
}

/**
 * Reverse list.
 *
 * This reverses the list.
 * @param   l	    List structure.
 */
void		list_reverse(struct list *l) {
    struct node** array = list_to_array(l);

    l->head = array[l->size-1];
    l->tail = array[0];
    array[0]->next = NULL;

    for(int i = 1; i < l->size; i++)
        reverse(array[i],array[i-1]);

    free(array);
}

/**
 * Reverse node.
 *
 * This internal function recursively reverses the node.
 * @param   curr    The current node.
 * @param   prev    The previous node.
 * @return  The new head of the singly-linked list.
 */
struct node*	reverse(struct node *curr, struct node *prev) {
    curr->next = prev;
    return curr;
}

/**
 * Sort list using merge sort.
 *
 * This sorts the list using a custom implementation of merge sort.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_msort(struct list *l, node_compare f) {
    l->head = msort(l->head,f);
    l->tail = l->head;
    while(l->tail->next != NULL)
        l->tail = l->tail->next;

}

/**
 * Performs recursive merge sort.
 *
 * This internal function performs a recursive merge sort on the singly-linked
 * list starting with head.
 * @param   head    The first node in a singly-linked list.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	msort(struct node *head, node_compare f) {

    if(head == NULL || head->next == NULL)
        return head;

    struct node* left = NULL;
    struct node* right = NULL;
    split(head,&left,&right);

    left = msort(left,f);
    right = msort(right,f);

    head = merge(left,right,f);
    
    return head;
}

/**
 * Splits the list.
 *
 * This internal function splits the singly-linked list starting with head into
 * left and right sublists.
 * @param   head    The first node in a singly-linked list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 */
void		split(struct node *head, struct node **left, struct node **right) {

    if(head == NULL || head->next == NULL)
        return;

    struct node *fast = head;
    struct node *slow = head;
    struct node *prevSlow = head;

    while(slow != NULL && fast != NULL && fast->next != NULL)
    {
        prevSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head;
    *right = slow;
    prevSlow->next = NULL;
}

/**
 * Merge sublists.
 *
 * This internal function merges the left and right sublists into one ordered
 * list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	merge(struct node *left, struct node *right, node_compare f) {
    if(left == NULL && right == NULL)
        return NULL;
    else if(left == NULL)
        return right;
    else if(right == NULL)
        return left;

    struct node *head;
    struct node *tail;

    if(f(&left,&right) < 0)
    {
        head = left;
        tail = left;
        left = left->next;
    }
    else
    {
        head = right;
        tail = right;
        right = right->next;
    }

    while(left != NULL || right != NULL)
    {
        if(left != NULL && (right == NULL || f(&left,&right) < 0))
        {
            tail->next = left;
            tail = left;
            left = left->next;
        }
        else if(right != NULL)
        {
            tail->next = right;
            tail = right;
            right = right->next;
        }
    }

    tail->next = NULL;

        
    return head;
}
