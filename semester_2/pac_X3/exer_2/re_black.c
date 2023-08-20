#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int color; // 0 - черный, 1 - красный
} Node;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // новый узел всегда красный
    return newNode;
}

Node *rotateLeft(Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

Node *rotateRight(Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

void flipColors(Node *node) {
    node->color = 1;
    node->left->color = 0;
    node->right->color = 0;
}

Node *insert(Node *node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    // проверяем свойства красно-черного дерева
    if (node->right != NULL && node->right->color == 1 && node->left != NULL && node->left->color == 0) {
        node = rotateLeft(node);
        flipColors(node);
    }

    if (node->left != NULL && node->left->color == 1 && node->left->left != NULL && node->left->left->color == 1) {
        node = rotateRight(node);
        flipColors(node);
    }

    if (node->left != NULL && node->left->color == 1 && node->right != NULL && node->right->color == 1) {
        flipColors(node);
    }

    return node;
}

void printTree(Node *node) {
    if (node == NULL) {
        return;
    }

    printf("%d ", node->data);
    if (node->color == 0) {
        printf("(B) ");
    } else {
        printf("(R) ");
    }

    if (node->left != NULL) {
        printf("L: %d ", node->left->data);
    } else {
        printf("L: NULL ");
    }

    if (node->right != NULL) {
        printf("R: %d ", node->right->data);
    } else {
        printf("R: NULL ");
    }

    printf("\n");

    printTree(node->left);
    printTree(node->right);
}

int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    printTree(root);

    return 0;
}