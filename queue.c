/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;
    q->entry = NULL;  // initialization
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        list_ele_t *enptr = q->entry;

        if (enptr != NULL) {
            /* one for iterator, one for safe */
            struct list_head *li = NULL, *lis = NULL;
            list_ele_t *rm_node;

            list_for_each_safe(li, lis, &enptr->list)
            {
                list_del(li);
                rm_node = container_of(li, list_ele_t, list);
                free(rm_node);
            }
            rm_node = container_of(li, list_ele_t, list);
            free(rm_node);
        }

        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q != NULL) {
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        newh = malloc(sizeof(list_ele_t));
        if (newh != NULL) {
            newh->value = strdup(s);
            INIT_LIST_HEAD(&newh->list);

            if (q->entry != NULL)
                list_add_tail(&newh->list, &q->entry->list);

            q->entry = newh;  // entry is new node
            q->size++;
            return true;
        }
    }
    return false;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q != NULL) {
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        newh = malloc(sizeof(list_ele_t));
        if (newh != NULL) {
            newh->value = strdup(s);
            INIT_LIST_HEAD(&newh->list);

            if (q->entry != NULL)
                list_add_tail(&newh->list, &q->entry->list);
            else
                q->entry = newh;  // entry is new node

            q->size++;
            return true;
        }
    }
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q != NULL) {
        list_ele_t *rm_ptr = q->entry;
        if (rm_ptr != NULL) {  // if the removed node is not NULL
            if (sp != NULL) {
                memcpy(sp, rm_ptr->value,
                       bufsize);         // copy the removed string to sp
                sp[bufsize - 1] = '\0';  // add terminator at the end
            }

            /*
             * move the entry ptr to the next node.
             * if it's the last node, then make entry to NULL
             */
            if (q->size > 1)
                q->entry = container_of(rm_ptr->list.next, list_ele_t, list);
            else
                q->entry = NULL;

            q->size--;

            list_del(&rm_ptr->list);
            free(rm_ptr);   // free the removed node
            rm_ptr = NULL;  // tmp ptr to NULL

            return true;
        }
    }

    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q != NULL ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{ /*
     if (q != NULL && q->size != 0) {
         list_ele_t *pre = NULL;       // previous
         list_ele_t *cur = q->head;    // current
         list_ele_t *nxt = cur->next;  // next

         q->tail = q->head;
         while (nxt != NULL) {
             cur->next = pre;
             pre = cur;
             cur = nxt;
             nxt = cur->next;
         }

         cur->next = pre;
         q->head = cur;
     }
   */
}
