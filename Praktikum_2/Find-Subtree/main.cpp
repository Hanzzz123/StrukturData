#include <stdlib.h>
#include <stdio.h>

// information in the nodes
typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right;
    int level;
} BSTNode;

//definition of the bst
typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

// Function for inserting the  nodes
BSTNode* __insert(BSTNode *root, int value, int level) {
    //1. check if tree is empty to insert node

    //2. if tree is not empty, we go to the other if
    //and else if statement to see where to insert the
    //other nodes, if its lesser or bigger than the
    //root's key. it recurses until it returns the node
    if (root == NULL) {
        BSTNode *node = (BSTNode*)malloc(sizeof (BSTNode));
        node->key = value;
        node->level = level;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    level = level + 1;

    if (value < root->key) {
        root->left = __insert(root->left, value, level);
    } else if (value > root->key) {
        root->right = __insert(root->right, value, level);
    }

    return root;
}

//traverses the whole bst
BSTNode* __search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key) {
            root = root->left;
        } else if (value > root->key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return root;
}

//checks to see if value being search is there in
//the bst
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

//insert node into the actuall bst
void bst_insert(BST *bst, int value) {
    int level = 0;
    if (!bst_find(bst, value)) {
        bst->_root = __insert(bst->_root, value, level);
        bst->_size++;
    }
}

//find the lca of two nodes,
int lca(BSTNode* node, int a, int b){
    if (node == NULL) {
        return 0;
    }

    //logic of lca
    if(node->key > a && node->key > b){
        return lca(node->left,a, b);
    } else if (node->key < a && node->key < b) {
        return lca(node->right, a, b);
    }
    return node->key;
}

int main() {
    //n = amount of nodes
    //q = jumlah list yang akan diberikan
    //x = jumlah bilangan pada list
    int n, q, x;

    //create the bst structure
   BST* bst = (BST*) malloc(sizeof(BST));
   bst->_root = NULL;

   //insert n
    scanf("%d", &n);

    //insert the nodes in the bst
    for (int i = 0; i < n; ++i) {
        int value;
        //insert all n's value
        scanf("%d", &value);
        bst_insert(bst, value);
    }
    //inser q
    scanf("%d", &q);

    for (int i = 0; i < q; ++i) {
        //insert x
        scanf("%d", &x);
        int values[x];
        for (int j = 0; j < x; ++j) {
            //store values variable in an array
            scanf("%d", &values[j]);
        }

        //compare node a(values[0]) with node values[j] (1,2,3...) to find lca.
        //a will change to the new root (lca) it returns to after the comparison. then compares it to value[j].
        //because the function only receives two integers as arguments, the result of the comparison
        //between values[0] and values [1] will be compared to values [2]. then the result of that will be
        //compared to value [3]. this continues until the last element in the array. the result of that comparison
        //will be the lca of all the elements in the array

        int a = values[0];
        for (int j = 1; j < x; j++) {
            a = lca(bst->_root, a, values[j]);
        }

        //searches for the node of the lca which includes the key and the level of the lca
        BSTNode* root_subtree = __search(bst->_root, a);

        //prints the node that it found from the __search
        printf("%d %d\n", root_subtree->key, root_subtree->level);

    }
    return 0;

}
