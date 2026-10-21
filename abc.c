#include <stdio.h>
#include <stdlib.h>

/* ========== LIST (mảng động) ========== */
typedef struct {
    int *a;
    int n, cap;
    int front;          // chỉ dùng cho Queue
} List;

void list_add(List *l, int x) {
    if (l->n == l->cap) {
        l->cap = l->cap ? l->cap * 2 : 4;
        l->a = realloc(l->a, l->cap * sizeof(int));
    }
    l->a[l->n++] = x;
}

/* Stack bằng List */
void push(List *l, int x) { list_add(l, x); }
int  pop(List *l)         { return l->a[--l->n]; }

/* Queue bằng List */
void enqueue(List *l, int x) { list_add(l, x); }
int  dequeue(List *l)        { return l->a[l->front++]; }

/* ========== LINKED LIST ========== */
typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *head, *tail;
} LinkedList;

Node *new_node(int x) {
    Node *p = malloc(sizeof(Node));
    p->val = x;
    p->next = NULL;
    return p;
}

int remove_head(LinkedList *l) {
    Node *p = l->head;
    int x = p->val;
    l->head = p->next;
    if (!l->head) l->tail = NULL;
    free(p);
    return x;
}

/* Stack bằng Linked list: thêm/lấy ở head */
void push_ll(LinkedList *l, int x) {
    Node *p = new_node(x);
    p->next = l->head;
    l->head = p;
    if (!l->tail) l->tail = p;
}
int pop_ll(LinkedList *l) { return remove_head(l); }

/* Queue bằng Linked list: thêm ở tail, lấy ở head */
void enqueue_ll(LinkedList *l, int x) {
    Node *p = new_node(x);
    if (l->tail) l->tail->next = p;
    else l->head = p;
    l->tail = p;
}
int dequeue_ll(LinkedList *l) { return remove_head(l); }

/* ========== MAIN ========== */
int main(void) {
    List stackL = {0}, queueL = {0};
    LinkedList stackN = {0}, queueN = {0};
    int n, x;

    printf("Nhap so phan tu: ");
    scanf("%d", &n);
    printf("Nhap %d so: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        push(&stackL, x);
        enqueue(&queueL, x);
        push_ll(&stackN, x);
        enqueue_ll(&queueN, x);
    }

    printf("\nStack (List):        ");
    while (stackL.n > 0) printf("%d ", pop(&stackL));

    printf("\nQueue (List):        ");
    while (queueL.front < queueL.n) printf("%d ", dequeue(&queueL));

    printf("\nStack (Linked list): ");
    while (stackN.head) printf("%d ", pop_ll(&stackN));

    printf("\nQueue (Linked list): ");
    while (queueN.head) printf("%d ", dequeue_ll(&queueN));
    printf("\n");

    free(stackL.a);
    free(queueL.a);
    return 0;
}