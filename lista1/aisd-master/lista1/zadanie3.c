#include <stdio.h>
#include <stdlib.h>

struct doublyLinkedList {
  int value;
  struct doublyLinkedList *prev;
  struct doublyLinkedList *next;
};

struct doublyLinkedList *newNode(int value) {
  /* tworzenie struktury nowego elementu listy */
  struct doublyLinkedList *node = malloc(sizeof(struct doublyLinkedList));
  node->value = value;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

int size(struct doublyLinkedList *node) {
  /* rozmiar listy */
  if (node == NULL) {
    return 0;
  }
  int s = 1;
  struct doublyLinkedList *current;
  for (current = node->next; current != node; current = current->next) {
    s++;
  }
  return s;
}

int getByIndex(struct doublyLinkedList *node, int n, char way) {
  /* n-ty element listy */
  int total = size(node);
  if (n < 0 || n >= total) {
    fprintf(stderr, "The supplied index is not valid\n");
    return -1;
  } else {
    int h = total/2, i = 0;
    if (way == 'l') {
      h = -1;
    } else if (way == 'r') {
      h = 999999999;
    }

    if (n > h) {
      i = total;
    }
    while (1) {
      if (i == n) {
        return node->value;
      } else {
        if (n > h) {
          i--;
          node = node->prev;
        } else if (n <= h) {
          i++;
          node = node->next;
        }
      }
    }
  }
}

int getByValue(struct doublyLinkedList *node, int value) {
  /* element listy o zadanej wartości */
  int i = 0;
  if (node->value == value) {
    return 0;
  } else {
    i++;
    struct doublyLinkedList *current;
    for (current = node->next; current->next != node; current = current->next) {
      if (current->value == value) {
        return i;
      }
      i++;
    }
  }
  fprintf(stderr, "There is no such a value in this linked list\n");
  return -1;
}

void push(struct doublyLinkedList **list, struct doublyLinkedList *node, int index) {
  /* dodawanie nowego elementu do listy */
  int total = size(*list);
  if (index < 0 || index > total) {
    fprintf(stderr, "There is not such an index in this list\n");
  } else {
    /* jeśli lista jest pusta */
    if (*list == NULL) {
      *list = node;
      (*list)->next = node;
      (*list)->prev = node;
    } else {
      /* jeśli element ma być na początku lub na końcu listy  */ 
      if (index == total || index == 0) {
        (*list)->prev->next = node;
        node->prev = (*list)->prev;
        node->next = *list;
        (*list)->prev = node;
        if (index == 0) {
          *list = node;
        }
      }
      /* element ma być w środku listy */
      else {
        int h = total/2, k;
        struct doublyLinkedList *current = *list;
        if (index > h) {
          k = total;
          for (current; k > index; current = current->prev) {
            k--;
          }
        } else {
          k = 0;
          for (current; k < index; current = current->next) {
            k++;
          }
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
      }
    }
  }
}

int pop(struct doublyLinkedList **list, int index) {
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
        struct doublyLinkedList *del;
        if (index == 0 || index == total-1) {
          if (index == 0) {
            del = *list;
            *list = (*list)->next;
          } else {
            del = (*list)->prev;
          }
          (*list)->prev = del->prev;
          (*list)->prev->next = *list;
        } else {
          int h = total/2, k;
          struct doublyLinkedList *current = *list;
          if (index > h) {
            k = total;
            for (current; k > index; current = current->prev) {
              k--;
            }
          } else {
            k = 0;
            for (current; k < index; current = current->next) {
              k++;
            }
          }
          del = current;
          current->next->prev = del->prev;
          current->prev->next = del->next;
        }
        value = del->value;
        del = NULL;
        free(del);
      }
      return value;
    }
  }
}

long measureTime (struct doublyLinkedList *list, int index, char way) {
  /* struktury niezbędne do funkcji gettimeofday */
  struct timeval bef, aft;       
  gettimeofday(&bef, 0);
  getByIndex (list, index, way);
  gettimeofday(&aft, 0);
  /* czas, jaki upłynął (w mikrosekundach) */
  long elapsed = (aft.tv_sec-bef.tv_sec)*1000000 + aft.tv_usec-bef.tv_usec;
  return elapsed;
}

struct doublyLinkedList *merge(struct doublyLinkedList **list1, struct doublyLinkedList **list2) {
  if (*list1 == NULL || *list2 == NULL) {
    fprintf(stderr, "At least one of two lists is empty\n");
    return NULL;
  } else {
    struct doublyLinkedList *merged = NULL, *current, *it;
    int size1 = size(*list1), size2 = size(*list2), i = 0;

    merged = newNode((*list1)->value);
    current = merged;
    i = 0;

    for (it = (*list1)->next; i < size1-1; it = it->next) {
      current->next = newNode(it->value);
      current->next->prev = current;
      current = current->next;
      i++;
    }

    i = 0;
    current->next = newNode((*list2)->value);
    current->next->prev = current;
    current = current->next;

    for (it = (*list2)->next; i < size2-1; it = it->next) {
      current->next = newNode(it->value);
      current->next->prev = current;
      current = current->next;
      i++;
    }
    current->next = merged;
    merged->prev = current;
    current = NULL;

    return merged;
  }
}

void destroy(struct doublyLinkedList **list) {
  int total = size(*list), i = 1;
  struct doublyLinkedList *current;
  while (i != total) {
    current = *list;
    free(current);
    *list = (*list)->next;
    i++;
  }
  *list = NULL;
}


void printList(struct doublyLinkedList *head) {
  /* wyświetlanie elementów listy */
  if (head == NULL) {
    printf("The list is empty.\n");
    return;
  }
  struct doublyLinkedList *current;
  printf("%d ", head->value);
  for (current = head->next; current != head; current = current->next) {
    printf("%d ", current->value);
  }
  printf("\n");
}

void printListReversely(struct doublyLinkedList *head) {
  /* wyświetlanie elementów listy w odwrotnym porządku */
  if (head == NULL) {
    printf("The list is empty.\n");
    return;
  }
  struct doublyLinkedList *current;
  for (current = head->prev; current != head; current = current->prev) {
    printf("%d ", current->value);
  }
  printf("%d ", current->value);
  printf("\n");
}

int main(int argc, char* argv[]) {
  int n = 0;

  if (argc == 2) {
    n = atoi(argv[1]);
  }

  if (n > 0) {
    printf("\n######\n");
    int i;

    struct doublyLinkedList *bigList = NULL;
    for (i = 0; i < n; i++) {
      push(&bigList, newNode(rand() % 100), i);
    }
    printf("\nA doubly linked list:\n");
    printList(bigList);

    int sum = 0;
    for (i = 0; i < n; i++) {
      sum += measureTime(bigList, rand() % n, '0');
    }
    printf("\n");
    printf("Average time of accessing a randomly chosen element: %d.%d μs\n", sum/n, sum%n);

    if (n == 1000) {
      sum = 0;
      for (i = 0; i < n; i++) {
        sum += measureTime(bigList, 332, 'r');
      }
      printf("\n");
      printf("Average time of accessing a 333th element: %d.%d", sum/n, sum%n);
      sum = 0;
      for (i = 0; i < n; i++) {
        sum += measureTime(bigList, 332, 'l');
      }
      printf(" / %d.%d μs\n", sum/n, sum%n);
    }
  } else {
    struct doublyLinkedList *list1 = NULL, *list2 = NULL;
    printf("\n");
    push(&list1, newNode(60), 0);
    push(&list1, newNode(809), 1);
    push(&list1, newNode(2509), 2);
    push(&list1, newNode(1260), 0);
    push(&list1, newNode(3322), size(list1));
    push(&list1, newNode(170715), 2);
    push(&list1, newNode(1500100900), 5);

    printf("Doubly linked list number 1:\n");
    printList(list1);

    printf("\n");
    printf("...reversely:\n");
    printListReversely(list1);

    printf("\n");
    printf("Size of this list: %d\n", size(list1));

    printf("\n");
    printf("Element number 2 of this list: %d\n", getByIndex(list1, 2, '0'));
    printf("Element number 5 of this list: %d\n", getByIndex(list1, 5, '0'));

    printf("\n");
    printf("The index of number 170715: %d\n", getByValue(list1, 170715));

    printf("\n");
    push(&list2, newNode(6), 0);
    push(&list2, newNode(36), 1);
    push(&list2, newNode(216), 2);
    push(&list2, newNode(125), 3);
    push(&list2, newNode(25), 4);
    push(&list2, newNode(5), 5);
    printf("Doubly linked list number 2:\n");
    printList(list2);

    printf("\n");
    printf("Merged lists:\n");
    printList(merge(&list1, &list2));
    
    printf("\n");
    printf("...reversely:\n");
    printListReversely(merge(&list1, &list2));

    printf("\n");
    printList(list1);
    printList(list2);

    printf("\n");
    printf("The first doubly linked list after removing elements number 0, 2, 5, 6:\n");
    pop(&list1, 0);
    pop(&list1, 1);
    pop(&list1, 4);
    pop(&list1, size(list1)-1);
    printList(list1);

    printf("\n");
    printf("...reversely:\n");
    printListReversely(list1);

  }
  printf("\n");
  return 0;
}