#include <cstdlib>
#include <queue>
#include "stdio.h"

using namespace std;

typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __insert(BSTNode *root, int value) {
    if (root == NULL) {
        BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
        node->key = value;
        node->left = NULL;
        node->right = NULL;

        return node;
    }

    if (value < root->key) {
        root->left = __insert(root->left, value);
    } else if (value > root->key) {
        root->right = __insert(root->right, value);
    }

    return root;
}

BSTNode* __search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key) {
            root = root->left;
        }
        else if (value > root->key) {
            root = root->right;
        }
        else {
            return root;
        }
    }

    return root;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __search(bst->_root, value);
    if (temp == NULL) {
        return false;
    }

    if (temp->key == value) {
        return true;
    }
    else {
        return false;
    }
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __insert(bst->_root, value);
        bst->_size++;
    }
}

int getBalanceOfTree(BSTNode* currentNode)
{
    if (currentNode == NULL)
    {
        return 0;
    }

    int leftSubtreeHeight = getBalanceOfTree(currentNode->left);
    if (leftSubtreeHeight == -1) return -1;

    int rightSubtreeHeight = getBalanceOfTree(currentNode->right);
    if (rightSubtreeHeight == -1) return -1;

    if (abs(leftSubtreeHeight - rightSubtreeHeight) > 1)
    {
        return -1;
    }

    return (max(leftSubtreeHeight, rightSubtreeHeight) + 1);
}

int main()
{
    BST bst;
    bst._root = NULL;
    int jumlahNode;
    scanf("%d", &jumlahNode);
    for (int i = 0; i < jumlahNode; i++) {
        int value;
        scanf("%d", &value);
        bst_insert(&bst, value);
    }
    int ifBalanceNode;
    scanf("%d", &ifBalanceNode);
    bst_insert(&bst, ifBalanceNode);

    if(getBalanceOfTree(bst._root) ==-1){
        printf("Tree tidak balance\n");
    }
    else {
        printf("Tree tetap balance\n");
    }
}
