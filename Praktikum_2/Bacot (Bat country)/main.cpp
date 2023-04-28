#include <cstdlib>
#include <queue>
#include "stdio.h"

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


bool is_possible(BST *bst, int target) {
    std::queue<BSTNode*> q;
    if (bst->_root == NULL) {
        return false;
    }

    q.push(bst->_root);

    while (!q.empty()) {
        BSTNode *node = q.front();
        q.pop();

        // 1 node
        // -------
        // current node itself
        if (node->key == target) {
            return true;
        }

        // 2 nodes
        // -------
        // current + left
        if (node->left != NULL && (node->key + node->left->key == target)) {
            return true;
        }
            // current + right
        else if (node->right != NULL && (node->key + node->right->key == target)) {
            return true;
        }

        // 3 nodes
        // -------
        // current + left + left_left
        if (node->left != NULL && node->left->left != NULL &&
            (node-> key + node->left->key + node->left->left->key == target)) {
            return true;
        }
            // current + left + left_right
        else if (node->left != NULL && node->left->right != NULL &&
                 (node-> key + node->left->key + node->left->right->key == target)) {
            return true;
        }
            // current + left + right
        else if (node->left != NULL && node->right != NULL &&
                 (node-> key + node->left->key + node->right->key == target)) {
            return true;
        }
            // current + right + right_right
        else if (node->right != NULL && node->right->right != NULL &&
                 (node-> key + node->right->key + node->right->right->key == target)) {
            return true;
        }
            // current + right + right_left
        else if (node->right != NULL && node->right->left != NULL &&
                 (node-> key + node->right->key + node->right->left->key == target)) {
            return true;
        }

        if (node->left != NULL) {
            q.push(node->left);
        }
        if (node->right != NULL) {
            q.push(node->right);
        }
    }

    return false;
}

int main() {
    int b, c, t;

    BST* bst = (BST*) malloc(sizeof(BST));
    bst->_root = NULL;

    scanf("%d", &b);

    for (int i = 0; i < b; ++i) {
        scanf("%d", &c);
        bst_insert(bst, c);
    }

    scanf("%d", &t);

    bool possible = is_possible(bst, t);

    if (possible) {
        printf("Monggo Lewat...\n");
    } else {
        printf("Wani Piro?\n");
    }

    return 0;
}

