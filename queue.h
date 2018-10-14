/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdbool.h>

#include <stddef.h>

/* "typeof" is a GNU extension.
 * Reference: https://gcc.gnu.org/onlinedocs/gcc/Typeof.html
 */
#if defined(__GNUC__)
#define __LIST_HAVE_TYPEOF 1
#endif

#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })

#define list_for_each_safe(node, safe, head)                     \
    for (node = (head)->next, safe = node->next; node != (head); \
         node = safe, safe = node->next)

/************** Data structure declarations ****************/

/**
 * struct list_head - node of a doubly linked list
 * @prev: previous pointer
 * @next: next pointer
 */
struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

/* Linked list element (You shouldn't need to change this) */
typedef struct ELE {
    /* Pointer to array holding string.
       This array needs to be explicitly allocated and freed */
    char *value;
    struct list_head list;
} list_ele_t;

/* Queue structure */
typedef struct {
    size_t size;           // size of the linked list
    struct list_head head; /* Doubly Linked list of elements */
} queue_t;

/************** Operations on doubly linked list *********************/

/**
 * list_add() - add a list_head node in the beginning of the list.
 * @node: pointer to the new node
 * @entry: pointer to the entry of the list
 *
 * In the doubly linked list, there is no head or tail.
 * So I prefer using the "entry" term to not mislead myself.
 */
static inline void list_add(struct list_head *node, struct list_head *entry)
{
    struct list_head *next = entry->next;

    next->prev = node;
    node->next = next;
    node->prev = entry;
    entry->next = node;
}

/**
 * list_add_tail() - Add a list node to the end of the list
 * @node: pointer to the new node
 * @head: pointer to the head of the list
 */
static inline void list_add_tail(struct list_head *node, struct list_head *head)
{
    struct list_head *prev = head->prev;

    prev->next = node;
    node->next = head;
    node->prev = prev;
    head->prev = node;
}

/**
 * list_del() - delete the current node.
 * @node: the node which we want to remove
 */
static inline void list_del(struct list_head *node)
{
    struct list_head *next = node->next;
    struct list_head *prev = node->prev;

    next->prev = prev;
    prev->next = next;
}

static inline void INIT_LIST_HEAD(struct list_head *head)
{
    head->next = head;
    head->prev = head;
}

/************** Operations on queue ************************/

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new();

/*
  Free ALL storage used by queue.
  No effect if q is NULL
*/
void q_free(queue_t *q);

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s);

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s);

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize);

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q);

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q);

/**
 * q_print_addr() - a function used to print the next and prev pointer address
 * @head: the list_head struct want to print address
 */
void q_print_addr(struct list_head *head);