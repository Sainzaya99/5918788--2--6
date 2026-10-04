#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[100];
int arraySize = 0;
int arrayComparisons = 0;

void arrayInsert(int value) {
    int i;

    for (i = 0; i < arraySize; i++) {
        arrayComparisons++;

        if (array[i] == value) {
            return;
        }
    }

    array[arraySize] = value;
    arraySize++;
}

int arraySearch(int value, int* comparisons) {
    int i;

    *comparisons = 0;

    for (i = 0; i < arraySize; i++) {
        (*comparisons)++;

        if (array[i] == value) {
            return 1;
        }
    }

    return 0;
}

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

int bstComparisons = 0;

Node* createNode(int value) {
    Node* newNode;

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* bstInsert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    bstComparisons++;

    if (value == root->data) {
        return root;
    }

    if (value < root->data) {
        root->left = bstInsert(root->left, value);
    }
    else {
        root->right = bstInsert(root->right, value);
    }

    return root;
}

int bstHeight(Node* root) {
    int leftHeight;
    int rightHeight;

    if (root == NULL) {
        return 0;
    }

    leftHeight = bstHeight(root->left);
    rightHeight = bstHeight(root->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    else {
        return rightHeight + 1;
    }
}

int bstSearch(Node* root, int value, int* comparisons) {
    *comparisons = 0;

    while (root != NULL) {
        (*comparisons)++;

        if (value == root->data) {
            return 1;
        }

        if (value < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }

    return 0;
}

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

int avlComparisons = 0;

int maxOf(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int avlHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }

    return node->height;
}

AVLNode* createAVLNode(int value) {
    AVLNode* newNode;

    newNode = (AVLNode*)malloc(sizeof(AVLNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int getBalance(AVLNode* node) {
    if (node == NULL)
    {
        return 0;
    }

    return avlHeight(node->left) - avlHeight(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x;
    AVLNode* temp;

    x = y->left;
    temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxOf(avlHeight(y->left),
        avlHeight(y->right));

    x->height = 1 + maxOf(avlHeight(x->left),
        avlHeight(x->right));

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y;
    AVLNode* temp;

    y = x->right;
    temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxOf(avlHeight(x->left),
        avlHeight(x->right));

    y->height = 1 + maxOf(avlHeight(y->left),
        avlHeight(y->right));

    return y;
}

AVLNode* avlInsert(AVLNode* root, int value) {
    int balance;

    if (root == NULL) {
        return createAVLNode(value);
    }

    avlComparisons++;

    if (value == root->data) {
        return root;
    }

    if (value < root->data) {
        root->left = avlInsert(root->left, value);
    }
    else {
        root->right = avlInsert(root->right, value);
    }

    root->height = 1 + maxOf(avlHeight(root->left),
        avlHeight(root->right));

    balance = getBalance(root);

    if (balance > 1 && value < root->left->data) {
        return rightRotate(root);
    }

    if (balance < -1 && value > root->right->data) {
        return leftRotate(root);
    }

    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int avlSearch(AVLNode* root, int value, int* comparisons) {
    *comparisons = 0;

    while (root != NULL) {
        (*comparisons)++;

        if (value == root->data) {
            return 1;
        }

        if (value < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }

    return 0;
}

void freeBST(Node* root) {
    if (root == NULL) {
        return;
    }

    freeBST(root->left);
    freeBST(root->right);

    free(root);
}

void freeAVL(AVLNode* root) {
    if (root == NULL) {
        return;
    }

    freeAVL(root->left);
    freeAVL(root->right);

    free(root);
}

int main(void) {
    Node* bstRoot = NULL;
    AVLNode* avlRoot = NULL;

    int i;

    int numbers[100];
    int keys[50];

    int seqTotal = 0;
    int bstTotal = 0;
    int avlTotal = 0;

    srand((unsigned int)time(NULL));

    for (i = 0; i < 100; i++) {
        numbers[i] = rand() % 1001;

        arrayInsert(numbers[i]);
        bstRoot = bstInsert(bstRoot, numbers[i]);
        avlRoot = avlInsert(avlRoot, numbers[i]);
    }

    printf("Generated 100 integers:\n");

    for (i = 0; i < 100; i++) {
        printf("%4d", numbers[i]);

        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    printf("\n");

    printf("Stored values    : %d\n", arraySize);
    printf("Duplicate values : %d\n", 100 - arraySize);

    printf("\nConstruction\n");
    printf("Array comparisons : %d\n", arrayComparisons);
    printf("BST comparisons   : %d\n", bstComparisons);
    printf("AVL comparisons   : %d\n", avlComparisons);

    printf("\nStructure\n");
    printf("Array length : %d\n", arraySize);
    printf("BST height   : %d\n", bstHeight(bstRoot));
    printf("AVL height   : %d\n", avlHeight(avlRoot));

    for (i = 0; i < 50; i++) {
        keys[i] = rand() % 1001;
    }

    printf("\nGenerated 50 search keys:\n");

    for (i = 0; i < 50; i++) {
        printf("%4d", keys[i]);

        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    printf("\n========================================\n");
    printf("50 SEARCHES\n");
    printf("========================================\n");

    for (i = 0; i < 50; i++) {
        int seqComparisons;
        int bstSearchComparisons;
        int avlSearchComparisons;

        int seqResult;
        int bstResult;
        int avlResult;

        seqResult = arraySearch(keys[i], &seqComparisons);
        bstResult = bstSearch(bstRoot, keys[i], &bstSearchComparisons);
        avlResult = avlSearch(avlRoot, keys[i], &avlSearchComparisons);

        seqTotal += seqComparisons;
        bstTotal += bstSearchComparisons;
        avlTotal += avlSearchComparisons;

        printf("\nSearch Key : %d\n", keys[i]);

        printf("\nSequential Search\n");
        printf("Result      : %s\n", seqResult ? "Found" : "Not Found");
        printf("Comparisons : %d\n", seqComparisons);

        printf("\nBST Search\n");
        printf("Result      : %s\n", bstResult ? "Found" : "Not Found");
        printf("Comparisons : %d\n", bstSearchComparisons);

        printf("\nAVL Search\n");
        printf("Result      : %s\n", avlResult ? "Found" : "Not Found");
        printf("Comparisons : %d\n", avlSearchComparisons);
    }

    printf("\n========================================\n");
    printf("SEARCH SUMMARY\n");
    printf("========================================\n");

    printf("Searches : 50\n");

    printf("\nSequential Search\n");
    printf("Total comparisons   : %d\n", seqTotal);
    printf("Average comparisons : %.2f\n", (double)seqTotal / 50);

    printf("\nBST Search\n");
    printf("Total comparisons   : %d\n", bstTotal);
    printf("Average comparisons : %.2f\n", (double)bstTotal / 50);

    printf("\nAVL Search\n");
    printf("Total comparisons   : %d\n", avlTotal);
    printf("Average comparisons : %.2f\n", (double)avlTotal / 50);

    freeBST(bstRoot);
    freeAVL(avlRoot);

    return 0;
}