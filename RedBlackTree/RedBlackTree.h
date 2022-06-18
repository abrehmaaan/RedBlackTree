# include <iostream>
#include<queue>
using namespace std;
enum RBColor { Red = 0, Black = 1 };
struct node {
    int data;
    RBColor Color;
    node* Left;
    node* Right;
    node* Parent;
};
class RBTree {
    node* Leaf;
    node* Root;
    void setNode(node* newNode, node* currNode);
    node* newNode(int val);
    void Insert(node* currNode);
    bool Search(node* currNode, int val);
    queue<int> q_level;
public:
    RBTree() {
        Root = NULL;
        Leaf = new node;
        Leaf->Left = NULL;
        Leaf->Right = NULL;
        Leaf->Parent = NULL;
        Leaf->Color = Black;
    }
    void Insert(int val);
    void RightRotate(node* currNode);
    void LeftRotate(node* currNode);
    bool Search(int val);
    void traverse() {
        queue<node*> q;
        if (Root != NULL)
            q.push(Root);
        while (!q.empty()) {
            node* temp = q.front();
            cout << temp->data << "-";
            cout << (temp->Color == 0 ? "Red" : "Black") << " ";
            q.pop();
            if (temp->Left != Leaf)
                q.push(temp->Left);
            if (temp->Right != Leaf)
                q.push(temp->Right);
        }
        cout << endl;
    }
};
