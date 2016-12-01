#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

/* Private node ADT. */

typedef struct _node node;

struct _node {
  node * next;
  void * e;
};

static node * newNode(void * e) {
  node * n  = malloc(sizeof(node));
  if (!n) return NULL;
  n->next = NULL;
  n->e = e;
  return n;
}

static void deleteNode(node * n) {
  free(n);
}

/* Linked list library. */

struct _llist {
  node * head;
};

llist * newLList(void) {
  llist * ll = malloc(sizeof(llist));
  if (!ll) return NULL;
  ll->head = NULL;
  return ll;
}

void deleteLList(llist * ll) {
  if (!ll) return;
  node * n = ll->head;
  while (n) {
    node * next = n->next;
    deleteNode(n);
    n = next;
  }
  free(ll);
}

int isEmptyLList(llist const * ll) {
  if (!ll) return 0;
  return (ll->head == NULL);
}

int putLList(llist * ll, void * e) {
  node * n;
  if (!ll) return -1;
  n = newNode(e);
  if (!n) return -1;
  n->next = ll->head;
  ll->head = n;
  return 0;
}

int getLList(llist * ll, void ** e) {
  node * n;
  if (!ll || !e) return -1;
  if (ll->head == NULL) { /* nothing to get */
    *e = NULL;
    return -2;
  }
  n = ll->head;
  *e = n->e; /* write element */
  ll->head = n->next;
  deleteNode(n);
  return 0;
}

int peekLList(llist const * ll, void ** e) {
  if (!ll || !e) return -1;
  if (ll->head == NULL) {
    /* Nothing to get. */
    *e = NULL;
    return -2;
  }
  *e = ll->head->e; /* write element */
  return 0;
}

int printLList(llist const * ll, printFn f) {
  node * n;
  int cnt;
  if (!ll || !f) return -1;

  cnt = 0;
  for (n = ll->head; n != NULL; n = n->next) {
    /* Print the index of the element. */
    cnt++;
    printf(" %d:", cnt);
    /* Call user-provided f to print the element. */
    f(n->e);
  }
  printf("\n");
  return 0;
}


//this function should combine ll1 and ll2 into ll3 where the values in ll1 and ll2 are alternating
int zip(llist * ll1, llist * ll2, llist * ll3) {
  if (!ll1 || !ll2) return -1;
  if (ll1 == ll3) return -1;
  if (ll2 == ll3) return -1;
  //ll3 should be an empty list, the code below checks for that
  if (!isEmptyLList(ll3)) return -1;
  //this code below should prevent the input list being the same as the output list
  node * tail3 = NULL;
 
  while(ll1->head != NULL && ll2->head != NULL){
    
    if(!tail3){
    ll3->head = tail3 = ll1->head;
    } else {
    tail3->next = ll1->head;
    tail3 = tail3->next;
    }
    ll1->head = ll1->head->next;
    tail3->next = ll2->head;
    tail3 = tail3->next;
    ll2->head = ll2->head->next;
    }

    //This code below was what performed the function lmost exactly correct except it was mirrored.
    // node * n = ll1->head;
    // node * next = n->next;
    // n->next = ll3->head;
    // ll3->head = n;
    // ll1->head = next;

    // node * x = ll2->head;
    // next = x->next;
    // x->next = ll3->head;
    // ll3->head = x;
    // ll2->head = next;
    //once at least one of the llists are emoty it will autmatically exit from the while loop.
  //if ll1 is not yet empty use while(n) to finish transferring it over
  while (ll1->head != NULL){
    
      node * next = ll1->head->next;
      ll1->head->next = ll3->head;
      ll3->head = ll1->head;
      ll1->head = next;
    
  }
  //if ll2 is not yet empty use while(x) to finish transferring it over
  while (ll2->head != NULL){
      node * next = ll2->head->next;
      ll2->head->next = ll3->head;
      ll3->head = ll2->head;
      ll2->head = next;
  }
  //possibly use exercise 8.2 to determine if it's been properly sorted?
  ll1->head = NULL;
  //make sure the llists are finished and empty and NULL
  ll2->head = NULL;
  //make sure ll1 is not equal to ll3
 
  //the program is almost finished except that the lists are being added in reverse order. I need to start from the tail and work up.
  
  /* Your code goes here. */
  return 0;
}
