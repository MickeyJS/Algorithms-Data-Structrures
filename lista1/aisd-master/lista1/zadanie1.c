#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;                                                      /* wartość elementu */
  struct node *next;                                              /* wskaźnik na kolejny element w kolejce */
};

struct node *first = NULL, *view;
int length = 0;

void enqueue(int n) {
  struct node *new = (struct node*) malloc(sizeof(struct node));
  new->value = n;
  if (first == NULL) {
    first = new;                                                  /* kolejka jest pusta, dodany zostaje nowy element */
  } else {
    for (view = first; view->next != NULL; view = view->next);    /* przejście na koniec kolejki */
    view->next = new;
  }
  new = NULL;
  free(new);
  length++;
}

int dequeue() {
  if (first == NULL) {
    fprintf(stderr, "\nThere is nothing to be deleted from the queue.\n\n");
    return -1;
  }
  struct node *tmp = (struct node*) malloc(sizeof(struct node));
  tmp = first;
  int tmpVal = first->value;
  first = first->next;                                            /* drugi element staje się początkiem kolejki */
  free(tmp);                                                      /* zwalnianie pamięci */
  length--;
  return tmpVal;
}

void print() {
  if (first == NULL) {
    fprintf(stderr, "\nThe queue is empty.\n\n");
  } else {
    int i = 0;
    printf("\n");
    for (view = first; view != NULL; view = view->next) {
      printf("index: %d \t value: %d\n", i, view->value);
      i++;
    }
    printf("\n");
  }
}

int getFirst() {
  if (first == NULL) {
    fprintf(stderr, "\nThe queue is empty.\n\n");
    return -1;
  }
  return first->value;
}

int getLast() {
  if (first == NULL) {
    fprintf(stderr, "\nThe queue is empty.\n\n");
    return -1;
  }
  for (view = first; view->next != NULL; view = view->next);
  return view->value;
}

int getAt(int n) {
  if (n >= length) {
    fprintf(stderr, "\nThe queue has less than %d elements.\n\n", n+1);
    return -1;
  }
  int i = 0;
  for (view = first; view != NULL; view = view->next) {
    if (i == n) {
      return view->value;
    }
    i++;
  }
}

int main(void) {
  view = (struct node*) malloc(sizeof(struct node));

  printf("\nNumber of elements: %d\n", length);
  
  enqueue(2509);
  enqueue(809);
  enqueue(666);
  enqueue(1024);
  enqueue(7070);
  print();

  printf("The 1st element: %d\n", getFirst());
  printf("The element at index %d: %d\n", 2, getAt(2));
  printf("The last element: %d\n", getLast());

  printf("\nNumber of elements: %d\n", length);

  dequeue();
  printf("\nThe queue after removing the 1st element:\n");
  print();

  free(view);
  return 0;
}