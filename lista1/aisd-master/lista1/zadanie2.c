#include <stdio.h>
#include <stdlib.h>

struct singlyLinkedList {
  int value;                        /* wartość elementu */
  struct singlyLinkedList *next;    /* następnik */
};

struct singlyLinkedList *newNode(int value) {
  /* tworzenie struktury nowego elementu listy */
  struct singlyLinkedList *list = malloc(sizeof(struct singlyLinkedList));
  list->value = value;
  list->next = NULL;
  return list;
}

struct singlyLinkedList *last(struct singlyLinkedList *node) {
  /* przejście do ostatniego elementu na liście */
  if (node == NULL) {
    fprintf(stderr, "\nThe list is empty!\n\n");
    return NULL;
  } else {
    for (node; node->next != NULL; node = node->next);
    return node;
  }
}

int size(struct singlyLinkedList *node) {
  /* rozmiar listy */
  int s = 0;
  for (node; node != NULL; node = node->next) {
    s++;
  }
  return s;
}

void push(struct singlyLinkedList **list, struct singlyLinkedList *node, int index) {
  /* jeśli lista jest pusta */
  if (*list == NULL) {
    *list = node;
  } else {
    int total = size(*list);
    if (index < 0 || index > total) {
      fprintf(stderr, "There is not such an index in this list.\n");
    } else {
      /* jeśli element jest na końcu listy */
      if (index == total) {
        last(*list)->next = node;
      } 
      /* jeśli element jest na początku listy */
      else if (index == 0) {
        node->next = (*list);
        (*list) = node;
      }
      /* jeśli element jest w środku listy */
      else {
        struct singlyLinkedList *current;
        int k = 0;
        for (current = *list; k < index; current = current->next) {
          if (k == index-1) {
            node->next = current->next;
            current->next = node;
            break;
          }
          k++;
        }
      }
    }
  }
}

int pop(struct singlyLinkedList **list, int index) {
  /* usuwanie elementu z listy */
  if (*list == NULL) {
    fprintf(stderr, "The linked list is empty\n");
    return -1;
  } else {
    int total = size(*list);
    if (index < 0 || index >= total) {
      fprintf(stderr, "There is not such an index in this list\n");
      return -1;
    } else {
      int value;
      if (total == 1) {
        value = (*list)->value;
        *list = NULL;
        free(*list);
      } else {
        struct singlyLinkedList *del;
        if (index == 0) {
          del = (*list);
          value = del->value;
          (*list) = (*list)->next;
          del = NULL;
          free(del);
        } else {
          int i = 0;
          struct singlyLinkedList *tmp;
          for (tmp = *list; i < index-1; tmp = tmp->next) {
            i++;
          }
          del = tmp->next;
          tmp->next = (tmp->next)->next;
          value = del->value;
          free(del);
        }
      }
      return value;
    }
  }
}

void printList(struct singlyLinkedList *first) {
  /* wyświetlanie elementów listy */
  if (first == NULL) {
    printf("The list is empty.\n");
    return;
  }
  for (first; first != NULL; first = first->next) {
    printf("%d ", first->value);
  }
  printf("\n");
}

int getByIndex(struct singlyLinkedList *node, int n) {
  /* n-ty element listy */
  if (n < 0 || n >= size(node)) {
    fprintf(stderr, "The supplied index is not valid\n");
    return -1;
  } else {
    int i = 0;
    for (node; node->next != NULL; node = node->next) {
      if (i == n) {
        return node->value;
      }
      i++;
    }
  }
}

int getByValue(struct singlyLinkedList *node, int value) {
  /* element listy o zadanej wartości */
  int i = 0;
  for (node; node->next != NULL; node = node->next) {
    if (node->value == value) {
      return i;
    }
    i++;
  }
  fprintf(stderr, "There is no such a value in this linked list\n");
  return -1;
}

struct singlyLinkedList *merge(struct singlyLinkedList **list1, struct singlyLinkedList **list2) {
  if (*list1 == NULL || *list2 == NULL) {
    fprintf(stderr, "At least one of two lists is empty\n");
    return NULL;
  } else {
    struct singlyLinkedList *merged = NULL, *current, *it;
    merged = newNode((*list1)->value);
    current = merged;
    for (it = (*list1)->next; it != NULL; it = it->next) {
      current->next = newNode(it->value);
      current = current->next;
    }
    for (it = *list2; it != NULL; it = it->next) {
      current->next = newNode(it->value);
      current = current->next;
    }
    current = NULL;
    return merged;
  }
}

void destroy(struct singlyLinkedList **list) {
  struct singlyLinkedList *current;
  while (*list != NULL) {
    current = *list;
    free(current);
    *list = (*list)->next;
  }
  *list = NULL;
}

long measureTime (struct singlyLinkedList *list, int index) {
  /* struktury niezbędne do funkcji gettimeofday */
  struct timeval bef, aft;       
  gettimeofday(&bef, 0);
  getByIndex (list, index);
  gettimeofday(&aft, 0);
  /* czas, jaki upłynął (w mikrosekundach) */
  long elapsed = (aft.tv_sec-bef.tv_sec)*1000000 + aft.tv_usec-bef.tv_usec;
  return elapsed;
}

int main(int argc, char *argv[]) {
  int n = 0;

  if (argc == 2) {
    n = atoi(argv[1]);
  }

  if (n > 0) {
    printf("\n######\n");
    int i;

    struct singlyLinkedList *bigList = NULL;
    for (i = 0; i < n; i++) {
      push(&bigList, newNode(rand() % 100), i);
    }
    printf("\nA singly linked list:\n");
    printList(bigList);

    int sum = 0;
    for (i = 0; i < n; i++) {
      sum += measureTime(bigList, rand() % n);
    }
    printf("\nAverage time of accessing a randomly chosen element: %d.%d μs.\n", sum/n, sum%n); 
  } else {
    struct singlyLinkedList *list1 = NULL, *list2 = NULL;
    printf("\n");
    push(&list1, newNode(60), 0);
    push(&list1, newNode(809), 1);
    push(&list1, newNode(2509), 2);
    push(&list1, newNode(1260), 0);
    push(&list1, newNode(3322), size(list1));
    push(&list1, newNode(170715), 2);
    printf("Singly linked list number 1:\n");
    printList(list1);
    printf("Size of this list: %d\n", size(list1));

    printf("\n");
    printf("The index of number 2509: %d\n", getByValue(list1, 2509));
    printf("The value at index 2: %d\n", getByIndex(list1, 2));  

    printf("\n");
    push(&list2, newNode(6), 0);
    push(&list2, newNode(36), 1);
    push(&list2, newNode(216), 2);
    push(&list2, newNode(125), 3);
    push(&list2, newNode(25), 4);
    push(&list2, newNode(5), 5);
    printf("Singly linked list number 2:\n");
    printList(list2);

    printf("\n");
    printf("Merged lists:\n");
    printList(merge(&list1, &list2));

    printf("\n");
    printList(list1);
    printList(list2);

    printf("\n");
    printf("The first singly linked list after removing elements number 0, 2, 5:\n");
    pop(&list1, 0);
    pop(&list1, 1);
    pop(&list1, 3);
    printList(list1);
  }

  printf("\n");
  return 0;
}