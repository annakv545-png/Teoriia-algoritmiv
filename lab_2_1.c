#include <stdio.h>
#include <stdlib.h>

struct list {
    int data;
    struct list *next;
};

struct list* reverseSegment(struct list* start, struct list* end) {
    struct list *prev = NULL, *curr = start, *next = NULL;
    while (curr != end) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev; 
}
int main() {
    int n, i, E;
    printf("Введіть кількість елементів: ");
    scanf("%d", &n);

    struct list *plist, *head;
    plist = malloc(sizeof(struct list));
    head = plist;

    for (i = 1; i <= n; i++) {
        printf("Елемент %d: ", i);
        scanf("%d", &plist->data);
        if (i < n) {
            plist->next = malloc(sizeof(struct list));
            plist = plist->next;
        } else {
            plist->next = NULL;
        }
    }

    printf("\nПочатковий список:\n");
    plist = head;
    while (plist != NULL) {
        printf("%d ", plist->data);
        plist = plist->next;
    }
    printf("\n");

    printf("\nВведіть елемент E: ");
    scanf("%d", &E);

    struct list *first = NULL, *last = NULL, *prevFirst = NULL, *prev = NULL;
    plist = head;
    while (plist != NULL) {
        if (plist->data == E) {
            if (first == NULL) {
                first = plist;
                prevFirst = prev;
            }
            last = plist;
        }
        prev = plist;
        plist = plist->next;
    }

    if (first == NULL) {
        printf("\nЧисла %d немає у списку.\n", E);
    } else if (first == last) {
        printf("\nЧисло %d зустрічається лише один раз, список без змін.\n", E);
    } else {
        struct list *afterLast = last->next;
        struct list *newStart = reverseSegment(first->next, last);

        struct list *tmp = newStart;
        while (tmp->next != NULL) tmp = tmp->next;
        first->next = newStart;
        tmp->next = last;
        last->next = afterLast;

        if (prevFirst != NULL) {
            prevFirst->next = first;
        } else {
            head = first;
        }
    }
    printf("\nЗмінений список:\n");
    plist = head;
    while (plist != NULL) {
        printf("%d ", plist->data);
        plist = plist->next;
    }
    printf("\n");

    return 0;
}
