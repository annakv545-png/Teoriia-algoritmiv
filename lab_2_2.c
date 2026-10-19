#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* buildBalancedTree(int* arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    Node* root = newNode(arr[mid]);
    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);
    return root;
}


Node* insertBST(Node* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->data)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}


void inorderCollect(Node* root, int* seq, int* idx) {
    if (root == NULL) return;
    inorderCollect(root->left, seq, idx);
    seq[*idx] = root->data;
    (*idx)++;
    inorderCollect(root->right, seq, idx);
}

void printTree(Node* root, int space, int count) {
    if (root == NULL) return;
    space += count;
    printTree(root->right, space, count);
    printf("\n");
    for (int i = count; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    printTree(root->left, space, count);
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    srand((unsigned)time(NULL));

    int n;
    printf("Введіть кількість елементів n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некоректне n.\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Згенеровані випадкові числа: ");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 101 - 50; 
        printf("%d ", arr[i]);
    }
    printf("\n");

    qsort(arr, n, sizeof(int), cmpfunc);

    Node* balancedRoot = buildBalancedTree(arr, 0, n - 1);
    printf("\nЗБАЛАНСОВАНЕ БІНАРНЕ ДЕРЕВО:\n");
    printTree(balancedRoot, 0, 5);

    int* seq = (int*)malloc(n * sizeof(int));
    int idx = 0;
    inorderCollect(balancedRoot, seq, &idx);
    Node* bstRoot = NULL;
    for (int i = 0; i < n; i++) {
        bstRoot = insertBST(bstRoot, seq[i]);
    }

    printf("\nБІНАРНЕ ДЕРЕВО ПОШУКУ:\n");
    printTree(bstRoot, 0, 5);

    freeTree(balancedRoot);
    freeTree(bstRoot);
    free(arr);
    free(seq);

    return 0;