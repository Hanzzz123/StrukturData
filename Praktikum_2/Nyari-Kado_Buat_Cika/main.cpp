#include <vector>
#include <unordered_map>
#include <string>
#include "stdio.h"
#include <climits>

//kenapa menggunakan unordered map, karena jika menggunakan array, harus menginisialisasi
//aray dengan ukuran 100.000,TLE. dan kalo menggunakan array, harus traverse seluruh elemen
//yg ada di array

typedef struct bstnode_t {
    int key;
    struct bstnode_t *left, *right, *parent;
    bool visited;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __insert(BSTNode *root, BSTNode *parent, int value, int level, int distance, std::unordered_map<std::string, int> *distances) {
    if (root == NULL) {
        BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
        node->key = value;
        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
        node->visited = false;

        //store the distance between child to parent and parent to child
        if (parent != NULL) {
            //child to parent, type cast to string because key is of type int. and then we concat (combine) the two
            //strings.
            std::string childToParentKey = std::to_string(node->key) + "," + std::to_string(parent->key);
            //make pair to insert a value in a map.
            distances->insert(std::make_pair(childToParentKey, distance));

            //parent to child.
            std::string parentToChildKey = std::to_string(parent->key) + "," + std::to_string(node->key);
            distances->insert(std::make_pair(parentToChildKey, distance));
        }

        return node;
    }

    level += 1;

    if (value < root->key) {
        root->left = __insert(root->left, root, value, level, distance, distances);
    } else if (value > root->key) {
        root->right = __insert(root->right, root, value, level, distance, distances);
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

void bst_insert(BST *bst, int value, int distance, std::unordered_map<std::string, int> *distances) {
    int level = 0;
    if (!bst_find(bst, value)) {
        bst->_root = __insert(bst->_root, bst->_root, value, level, distance, distances);
        bst->_size++;
    }
}

int find_shortest_path(BSTNode* node, int current_distance, int shortest_distance, std::unordered_map<std::string, int> distances) {
    if (node == NULL) {
        return shortest_distance;
    }

    if (node->left == NULL && node->right == NULL) {
        if (current_distance < shortest_distance) {
            shortest_distance = current_distance;
        }

        return shortest_distance;
    }

    int shortestDistanceToParent = INT_MAX;
    int shortestDistanceToLeft = INT_MAX;
    int shortestDistanceToRight = INT_MAX;

    //it doesn't go to the same node again when travelling
    node->visited = true;

    //visits the parent from child
    if (node->parent != NULL && !node->parent->visited) {
        std::string sourceToParentKey = std::to_string(node->key) + "," + std::to_string(node->parent->key);
        //at recieves value for that key (distances)
        int distanceToParent = distances.at(sourceToParentKey);
        shortestDistanceToParent = find_shortest_path(node->parent, current_distance + distanceToParent, shortest_distance, distances);
        //we set it to false, so we can visit the node again. but, with a different route
        node->parent->visited = false;
    }

    //visits left from parent
    if (node->left != NULL && !node->left->visited) {
        std::string sourceToLeftKey = std::to_string(node->key) + "," + std::to_string(node->left->key);
        int distanceToLeft = distances.at(sourceToLeftKey);
        shortestDistanceToLeft = find_shortest_path(node->left, current_distance + distanceToLeft, shortest_distance, distances);
        //we set it to false, so we can visit the node again. but, with a different route
        node->left->visited = false;
    }

    //visits right from parent
    if (node->right != NULL && !node->right->visited) {
        std::string sourceToRightKey = std::to_string(node->key) + "," + std::to_string(node->right->key);
        int distanceToRight = distances.at(sourceToRightKey);
        shortestDistanceToRight = find_shortest_path(node->right, current_distance + distanceToRight, shortest_distance, distances);
        //we set it to false, so we can visit the node again. but, with a different route
        node->right->visited = false;
    }

    //we set it to false, so we can visit the node again. but, with a different route
    node->visited = false;

    //find the smallest distance out of the 3
    return std::min(std::min(shortestDistanceToParent, shortestDistanceToLeft), shortestDistanceToRight);
}

int main() {
    std::unordered_map<std::string, int> distances;

    BST* bst = (BST*) malloc(sizeof(BST));
    bst->_root = NULL;

    int n, r;

    scanf("%d %d", &n, &r);

    // this is the root and the only node
    // it does not have a parent hence distance is 0
    bst_insert(bst, r, 0, &distances);

    for (int i = 0; i < n-1; ++i) {
        int node, distance;
        scanf("%d %d", &node, &distance);
        //insert each node and their distance
        bst_insert(bst, node, distance, &distances);
    }

    int t;

    scanf("%d", &t);

    //store the answers in a vector
    std::vector<int> answers;

    for (int i = 0; i < t; ++i) {
        int miko_location;
        std::unordered_map<std::string, int> visited;

        scanf("%d", &miko_location);

        //find mikos location in the node.
        BSTNode *miko_node = __search(bst->_root, miko_location);

        //finds the shortest path and add it to the vector
        int shortest = find_shortest_path(miko_node, 0, INT_MAX, distances);
        answers.push_back(shortest);
    }

    //print the answers here
    for (int i = 0; i < (int)answers.size(); ++i) {
        printf("%d", answers[i]);
        if (i < (int)answers.size() - 1) {
            printf(" ");
        }
    }


    return 0;
}

