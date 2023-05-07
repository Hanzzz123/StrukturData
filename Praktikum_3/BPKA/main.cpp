#include "stdio.h"
#include "stdlib.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "string.h"
#include "stdbool.h"
#include "iostream"

using namespace std;

//avl node definition
typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

//avl tree definition
typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

//initialize the avl tree
void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

//see each height of every node
int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0;
    return node->height;
}

//check the balance factor of a node
int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

int _max(int a,int b){
    return (a > b)? a : b;
}

//--------------------------------------------------------------------------------------------------------
//ROTASI

//Rotasi Kanan (Case left-skewed), tusuk sate dari kiri bawah
AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                           _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                            _getHeight(newParrent->right))+1;

    return newParrent;
}
//Rotasi kanan ini bisa menyelesaikan permasalahan untuk Case Left Skewed.
AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

//Rotasi Kiri (Case right-skewed), tusuk sate dari kanan bawah
AVLNode* _leftRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                           _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                            _getHeight(newParrent->right))+1;

    return newParrent;
}

//Rotasi kanan ini bisa menyelesaikan permasalahan untuk Case Left Skewed.
AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}
//case left-right zig - zag
AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

//case right-left zig - zag
AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

//---------------------------------------------------------------------------
//SEARCH

//Fungsi utilitas search
AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

//Fungsi utama search
bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;

    if (temp->data == value)
        return true;
    else
        return false;
}

//---------------------------------------------------------------------------
//INSERTION

// Creating a new node for the avl tree
AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//fungsi utilitas insert
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value){

    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);

    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));

    int balanceFactor=_getBalanceFactor(node);

    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);

    return node;
}

//Fungsi Utama insert
void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root = _insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

void constructRows(AVLNode* root, int hd, unordered_map<int, vector<int> >& m)
{
    if (root == NULL) {
        return;
    }

    m[hd].push_back(root->data);

    constructRows(root->left, hd - 1, m);

    constructRows(root->right, hd + 1, m);
}

int calculateVerticalRows(AVLNode* root)
{
    unordered_map<int, vector<int> > m;
    int hd = 0;
    constructRows(root, hd, m);

    unordered_map<int, vector<int> >::iterator it;
    int result = 0;
    for (it = m.begin(); it != m.end(); it++) {
        int sumOfSameRow = 0;
        for (int i = 0; i < it->second.size(); ++i) {
            sumOfSameRow += it->second[i];
        }
        result += sumOfSameRow * sumOfSameRow;
    }
    return result;
}

int main()
{
    AVL avl;
    avl_init(&avl);

    while(true){
        string input;
        cin >> input;

        if (input == "MASUKKAN"){
            int number;
            cin >> number;
            avl_insert(&avl, number);
        }
        else if(input == "HITUNG"){
            printf("%d", calculateVerticalRows(avl._root));
            break;
        }
    }
}


