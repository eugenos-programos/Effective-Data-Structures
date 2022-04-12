#include <stdio.h>
#include <stdlib.h>

struct SplayTree
{
    struct SplayNode
    {
        struct SplayNode *leftChild;
        struct SplayNode *rightChild;
        struct SplayNode *parent;
        void *data;
    } * root;
}

struct SplayNode *
newNode(void *data)
{
    struct SplayNode *node = (struct SplayNode *)malloc(sizeof(struct SplayNode));
    node->data = data;
    node->leftChild = node->rightChild = NULL;
}

void deleteNode(struct SplayNode *node)
{
    free(node->leftChild);
    free(node->rightChild);
}

struct SplayNode *_Minimum(struct SplayNode *localRoot)
{
    struct SplayNode *minimum = localRoot;

    while (minimum->leftChild != NULL)
        minimum = minimum->leftChild;

    return minimum;
}

struct SplayNode *_Maximum(struct SplayNode *localRoot)
{
    struct SplayNode *maximum = localRoot;

    while (maximum->rightChild != NULL)
        maximum = maximum->rightChild;

    return maximum;
}

struct SplayNode *_Predecessor(struct SplayNode *localRoot)
{
    struct SplayNode *predecessor = localRoot;
    if (predecessor->leftChild != NULL)
    {
        predecessor = _Maximum(predecessor->leftChild);
    }
    else
    {
        while (predecessor != root || predecessor != predecessor->parent->rightChild)
        {
            predecessor = predecessor->parent;
        }
    }
    return predecessor;
}

struct SplayNode *Successor(struct SplayNode *localRoot)
{
    struct SplayNode *successor = localRoot;
    if (successor->rightChild != NULL)
    {
        successor = _Minimum(successor->rightChild);
    }
    else
    {
        while (successor != root || successor != successor->parent->leftChild)
        {
            successor = successor->parent;
        }
    }
    return successor;
}

void _LeftRotate(struct SplayNode *localRoot)
{
    struct SplayNode *rightChild = localRoot->rightChild;

    localRoot->rightChild = rightChild->leftChild;
    if (rightChild->leftChild != NULL)
        rightChild->leftChild->parent = localRoot;

    _Transplant(localRoot, rightChild);

    rightChild->leftChild = localRoot;
    rightChild->leftChild->parent = rightChild;
}

void _RightRotate(struct SplayNode *localRoot)
{
    struct SplayNode *leftChild = localRoot->leftChild;

    localRoot->leftChild = leftChild->rightChild;
    if (leftChild->rightChild != NULL)
        leftChild->rightChild->parent = localRoot;

    _Transplant(localRoot, leftChild);

    leftChild->rightChild = localRoot;
    leftChild->rightChild->parent = leftChild;
}

void _Splay(struct SplayNode *pivotElement)
{
    while (pivotElement != root)
    {
        if (pivotElement->parent == root)
        {

            if (pivotElement == pivotElement->parent->leftChild)
            {
                _RightRotate(pivotElement->parent);
            }
            else if (pivotElement == pivotElement->parent->rightChild)
            {
                _LeftRotate(pivotElement->parent);
            }
        }
        else
        {
            // Zig-Zig step.
            if (pivotElement == pivotElement->parent->leftChild &&
                pivotElement->parent == pivotElement->parent->parent->leftChild)
            {

                _RightRotate(pivotElement->parent->parent);
                _RightRotate(pivotElement->parent);
            }
            else if (pivotElement == pivotElement->parent->rightChild &&
                     pivotElement->parent == pivotElement->parent->parent->rightChild)
            {

                _LeftRotate(pivotElement->parent->parent);
                _LeftRotate(pivotElement->parent);
            }
            // Zig-Zag step.
            else if (pivotElement == pivotElement->parent->rightChild &&
                     pivotElement->parent == pivotElement->parent->parent->leftChild)
            {

                _LeftRotate(pivotElement->parent);
                _RightRotate(pivotElement->parent);
            }
            else if (pivotElement == pivotElement->parent->leftChild &&
                     pivotElement->parent == pivotElement->parent->parent->rightChild)
            {

                _RightRotate(pivotElement->parent);
                _LeftRotate(pivotElement->parent);
            }
        }
    }
}

struct SplayTree *newTree()
{
    struct SplayTree *tree;
    tree->root = NULL;
    return tree;
}

void deleteTree(struct SplayTree *tree)
{
    free(tree);
}

void Insert(struct SplayTree* tree, const T &key)
{
    struct SplayNode *preInsertPlace = NULL;
    struct SplayNode *insertPlace = root;

    while (insertPlace != NULL)
    {
        preInsertPlace = insertPlace;

        if (insertPlace->data() < key)
            insertPlace = insertPlace->rightChild;
        else if (key <= insertPlace->data)
            insertPlace = insertPlace->leftChild;
    }

    struct SplayNode *insertElement = newNode(key);
    insertElement->parent = preInsertPlace;

    if (preInsertPlace == NULL)
        tree->root = insertElement;
    else if (preInsertPlace->data < insertElement->data)
        preInsertPlace->rightChild = insertElement;
    else if (insertElement->data < preInsertPlace->data)
        preInsertPlace->leftChild = insertElement;

    _Splay(insertElement);
}

void Remove(struct SplayTree* tree, const T &key)
{
    struct SplayNode *removeElement = _Search(key);

    if (removeElement != NULL)
    {
        if (removeElement->rightChild == NULL)
            _Transplant(removeElement, removeElement->leftChild);
        else if (removeElement->leftChild == NULL)
            _Transplant(removeElement, removeElement->rightChild);
        else
        {
            struct SplayNode *newLocalRoot = _Minimum(removeElement->rightChild);

            if (newLocalRoot->parent != removeElement)
            {

                _Transplant(newLocalRoot, newLocalRoot->rightChild);

                newLocalRoot->rightChild = removeElement->rightChild;
                newLocalRoot->rightChild->parent = newLocalRoot;
            }

            _Transplant(removeElement, newLocalRoot);

            newLocalRoot->leftChild = removeElement->leftChild;
            newLocalRoot->leftChild->parent = newLocalRoot;

            _Splay(newLocalRoot);
        }

        free(removeElement);
    }
}

bool Search(const T &key)
{ 
    return _Search(key) != NULL; 
}

bool isEmpty(struct SplayTree* tree) const {
    return tree->root == NULL;
}

T Successor(const T &key)
{
    if (_Successor(_Search(key)) != NULL)
    {
        return _Successor(_Search(key))->getValue();
    }
    else
    {
        return -1;
    }
}

T Predecessor(const T &key)
{
    if (_Predecessor(_Search(key)) != NULL)
    {
        return _Predecessor(_Search(key))->getValue();
    }
    else
    {
        return -1;
    }
}

int main(int argc, char const *argv[])
{

    return 0;
}
