#include "stdio.h"
#include "stdlib.h"
#include "queue"

//avl node definition
typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right, *parent = NULL;
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

void findParentSibling(AVL* avl, int target)
{
    std::queue<AVLNode*>q;
    if(avl->_root == NULL){
        return;
    }
    avl->_root->parent = NULL;
    q.push(avl->_root);
    while (!q.empty()){
        AVLNode* node = q.front();
        q.pop();

        if(node->data == target){

            if(node->parent == NULL){
                printf("%d\n",node->data);
                break;
            }

            AVLNode* parent = node->parent;
            if(parent->parent == NULL){
                printf("%d\n",parent->data);
                break;
            }

            AVLNode* grandParent = parent->parent;
            AVLNode* sibling = NULL;
            int selisih;

            if(grandParent->left!=NULL && grandParent->left != parent){
                sibling = grandParent->left;
                selisih = abs(sibling->data - grandParent->right->data);
            }
            else if(grandParent->right != NULL && grandParent -> right != parent){
                sibling = grandParent->right;
                selisih = abs(sibling->data - grandParent->left->data);
            }
            if(sibling != NULL){

                printf("%d\n",selisih);
            }
            else if(sibling == NULL){
                printf("%d\n", parent->data);
            }

            break;

        }

        if(node->left != NULL){
            node->left->parent = node;
            q.push(node->left);
        }
        if(node->right != NULL){
            node->right->parent = node;
            q.push(node->right);
        }

    }

}


int main() {
    AVL avl;
    avl_init(&avl);

    int posKeamanan, jumlahTestcase, Testcase;

    scanf("%d %d", &posKeamanan, &jumlahTestcase);
    for(int i = 1; i <= posKeamanan; i++)
    {
        int value;
        scanf("%d", &value);
        avl_insert(&avl,value);
    }
    for (int i = 1; i <=jumlahTestcase ; ++i) {
        scanf("%d", &Testcase);
        findParentSibling(&avl, Testcase);
    }
}