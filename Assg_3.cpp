#include<iostream>
using namespace std;

class ThreadedBST;
class Node{
    public:
    int data;
    bool lthread, rthread;
    Node* left;
    Node* right;
    public:
    Node(int data){
        this->data = data;
        lthread = rthread = 1;
        left = right = nullptr;
    }
    friend class ThreadedBST;
};

class ThreadedBST{
    public:
    Node* root;
    ThreadedBST(){
        root = nullptr;
    }
    void insertInTBST(){
        int val;
        while(true){
            cout<<"\nEnter the elements: ";
            cin>>val;
            if(val == -1){
                break;
            }
            Node* par = nullptr;
            Node* temp = root;
            while(temp){
                par = temp;
                if(val > temp->data){
                    if(!temp->rthread){
                        temp = temp->right;
                    }else break;
                }else{
                    if(!temp->lthread){
                        temp = temp->left;
                    }else break;
                }
            }
            Node* nn = new Node(val);
            if(par == nullptr){
                root = nn;
            }
            else{
                if(val > par->data){    // right child
                    par->rthread = 0;
                    nn->right = par->right;
                    nn->left = par;
                    par->right = nn;
                }
                else{
                    par->lthread = 0;
                    nn->left = par->left;
                    nn->right = par;
                    par->left = nn;
                }
            }
        }
    }

    void inorder(){
        if(!root) return;
        cout<<"\nInorder Traversal is:  ";
        Node* temp = root;
        while (temp->right)
        {   
            while(!temp->lthread){
                temp = temp->left;
            }
            cout<<temp->data<<"  ";
            while(temp->rthread){
                temp = temp->right;
                cout<<temp->data<<"  ";
            }
            temp = temp->right;
        }
        cout<<temp->data<<endl;   
    }

    Node* successor(Node* ptr){
        Node* temp = ptr->right;
        while(!temp->lthread){
            temp = temp->left;
        }
        return temp;
    }

    Node* predecessor(Node* ptr){
        Node* temp = ptr->left;
        while(!temp->rthread){
            temp = temp->right;
        }
        return temp;
    }

    void preorder(){
        if(!root){
            return;
        }
        cout<<"\nPreorder Traversal is:  ";
        Node* temp = root;
        while (temp->right)
        {   
            while(temp){
                cout<<temp->data<<"  ";
                if(temp->lthread) break;
                temp = temp->left;
            }
            while(temp->rthread){
                temp = temp->right;
            }
            temp = temp->right;
        }
        cout<<temp->data<<endl; 
    }
};

int main(){
    ThreadedBST obj;
    obj.insertInTBST();
    cout<<"tree input success"<<endl;
    obj.inorder();
    cout<<endl;
    obj.preorder();
    cout<<endl;
    // cout<<(obj.successor(obj.root))->data<<endl;
    // cout<<obj.predecessor(obj.root)->data;
}