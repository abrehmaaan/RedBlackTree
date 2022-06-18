#include"RedBlackTree.h"
//this function creates a node having the value passed to it as a parameter
node* RBTree::newNode(int val) {
    node* currNode = new node;
    currNode->Parent = NULL;
    currNode->Color = Red;
    //left and right should be null but storing leaf node into them so that we can store their color as black
    //leaf is initialized in the constructor of the tree with black color
    currNode->Left = this->Leaf;
    currNode->Right = this->Leaf;
    currNode->data = val;
    return currNode;
}
void RBTree::setNode(node* newNode, node* currNode) {
    //initially takes new node and root node of the tree
    //if root is null it stores the new inserted node in the root and sets its color to black
    if (this->Root == NULL) {
        this->Root = newNode;
        newNode->Color = Black;
        return;
    }
    //if newly inserted node has value greater than the root node than it checks its appropiate position by recursively calling this function for subtrees
    if (newNode->data > currNode->data) {
        //since this if block will only executed if the value of newly inserted node is greater than the root of the subtree
        //it checks whether the right node is a leaf node i.e. NULL
        if (currNode->Right == this->Leaf) {
            //if right node is leaf than it place it here
            currNode->Right = newNode;
            newNode->Parent = currNode;
            return;
        }
        setNode(newNode, currNode->Right);
    }
    //vice versa of above if block
    else {
        if (currNode->Left == this->Leaf) {
            currNode->Left = newNode;
            newNode->Parent = currNode;
            return;
        }
        setNode(newNode, currNode->Left);
    }
    return;
}
void RBTree::Insert(node* currNode) {
    setNode(currNode, this->Root);
    //once the new node is placed at its position than we can further check for rotations or color fixing if needed
    
    if (currNode == this->Root) {
        currNode->Color = Black;
        return;
    }
    if (!currNode->Parent->Parent)
        return;
    //uncle node will be the sibling of parent node
    node* Uncle;
    int flag;
    //while loop will run until the two consecutive nodes have same color i.e. RED
    while (currNode->Parent->Color == Red) {
        //if the parent of current node is the right child of its parent then uncle should be left child of its parent
        currNode->Parent == currNode->Parent->Parent->Right ? flag = 0 : flag = 1;
        !flag ? Uncle = currNode->Parent->Parent->Left : Uncle = currNode->Parent->Parent->Right;
        //if uncle's color is also red then we have to do color fixing
        if (Uncle->Color == Red)
        {
            Uncle->Color = Black;
            currNode->Parent->Color = Black;
            currNode->Parent->Parent->Color = Red;
            //after fixing colors now we have to check for any violation from the grandparent node
            currNode = currNode->Parent->Parent;
        }
        //if uncle's color is black we have to do rotations
        else
        {
            //if parent is right child than right rotation else left rotation
            if (!flag ? currNode == currNode->Parent->Left : currNode == currNode->Parent->Right) {
                
                currNode = currNode->Parent;
                !flag ? RightRotate(currNode) : LeftRotate(currNode);
            }
            //first swapping the color than doing rotation
            currNode->Parent->Color = Black;
            currNode->Parent->Parent->Color = Red;
            !flag ? LeftRotate(currNode->Parent->Parent) : RightRotate(currNode->Parent->Parent);
        }
        if (currNode == this->Root)
            break;
    }
    //at the end root should be black
    this->Root->Color = Black;
}
//when a value is inserted it is passed to this oveloaded insert function
void RBTree::Insert(int val) {
    //this function creates a new node having inserted value using new node function and passes that node to overloaded insert function to insert it into tree
    Insert(newNode(val));
}
void RBTree::RightRotate(node* currNode) {
    if (currNode->Left == Leaf)
        return;
    node* swap = currNode->Left;
    currNode->Left = swap->Right;
    if (currNode->Right != this->Leaf)
        swap->Right->Parent = currNode;
    swap->Parent = currNode->Parent;
    if (currNode == this->Root)
        this->Root = swap;
    else if (currNode == currNode->Parent->Right)
        currNode->Parent->Right = swap;
    else
        currNode->Parent->Left = swap;
    swap->Right = currNode;
    currNode->Parent = swap;
}
void RBTree::LeftRotate(node* currNode) {
    if (currNode->Right == Leaf)
        return;
    node* swap = currNode->Right;
    currNode->Right = swap->Left;
    if (currNode->Left != this->Leaf)
        swap->Left->Parent = currNode;
    swap->Parent = currNode->Parent;
    if (currNode == this->Root)
        this->Root = swap;
    else if (currNode == currNode->Parent->Left)
        currNode->Parent->Left = swap;
    else
        currNode->Parent->Right = swap;
    swap->Left = currNode;
    currNode->Parent = swap;
}
bool RBTree::Search(node* currNode, int val) {
    if (currNode == NULL) {
        return false;
    }
    else if (currNode->data == val) {
        return true;
    }
    if (currNode->data > val)
        return (Search(currNode->Left, val));
    return Search(currNode->Right, val);
}
bool RBTree::Search(int val) {
    return Search(this->Root, val);
}