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
        while(!temp->lthread){
            temp = temp->left;
        }
        while (temp)
        {   
            cout<<temp->data<<"  ";
            if(temp->rthread)
                temp = temp->right;
            else{
                temp = temp->right;
                while(!temp->lthread){
                    temp = temp->left;
                }
            }
        }
        // cout<<temp->data<<endl;   
    }

    Node* successor(Node* ptr){
        if(ptr->rthread){
            return ptr->right;
        }
        Node* temp = ptr->right;
        while(!temp->lthread){
            temp = temp->left;
        }
        return temp;
    }

    Node* predecessor(Node* ptr){
        if(ptr->lthread) return ptr->left;
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

    Node* caseA(Node* root, Node* par, Node* ptr){
        if(par == nullptr){
            root = nullptr;
        }
        else if(par->left == ptr){
            par->lthread = 1;
            par->left = ptr->left;
        }
        else{
            par->right = ptr->right;
            par->rthread = 1;
        }
        delete ptr;
        return root;
    }

    Node* caseB(Node* root, Node* par, Node* ptr){
        Node* child;
        if(!ptr->lthread){
            child = ptr->left;
        }
        else{
            child = ptr->right;
        }
        if(par == nullptr){
            root = child;
        }
        if(par->left == ptr){
            par->left = child;
        }
        else if(par->right == ptr){
            par->right = child;
        }


        Node* succ = successor(ptr);
        Node* pred = predecessor(ptr);
        cout<<succ->data<<"  "<<pred->data<<endl;
        if(!ptr->lthread){
            pred->right = succ;
        }
        else if(!ptr->rthread){
            succ->left = pred;
        }

        delete ptr;
        return root;
    }

    Node* caseC(Node* root, Node* par, Node* ptr){
        Node* succ = ptr->right;
        Node* parSucc = ptr;
        while(!succ->lthread){
            parSucc = succ;
            succ = succ->left;
        }
        ptr->data = succ->data;
        if(succ->lthread && succ->rthread){
            root = caseA(root, parSucc, succ);
        }
        else{
            root = caseB(root, parSucc, succ);
        }

        return root;
    }

    Node* deleteNodeInBST(Node* root, int key){
        bool flag = 0;
        Node* par = nullptr;
        Node* ptr = root;
        while(ptr){
            if(ptr->data == key){
                flag = 1;
                break;
            }
            par = ptr;
            if(ptr->data > key){
                if(!ptr->lthread){
                    ptr = ptr->left;
                }
                else break;
            }
            else{
                if(!ptr->rthread){
                    ptr = ptr->right;
                }
                else break;
            }
        }
        if(!flag){
            cout<<"Key not found!!!\n";
            return root;
        }
        else if(ptr->lthread && ptr->rthread){
            root = caseA(root, par, ptr);
        }
        else if((ptr->lthread && !ptr->rthread) || (ptr->rthread && !ptr->lthread)){
            root = caseB(root, par, ptr);
        }
        else{
            root = caseC(root, par, ptr);
        }
        return root;
    }
};

int main(){
    // 20 10 30 5 16 14 13 15 -1
    ThreadedBST obj;
    // obj.insertInTBST();
    // cout<<"tree input success"<<endl;
    // obj.inorder();
    // cout<<endl;
    // obj.deleteNodeInBST(obj.root, 15);
    // obj.inorder();
    // obj.deleteNodeInBST(obj.root, 16);
    // obj.inorder();
    // obj.deleteNodeInBST(obj.root, 10);
    // obj.inorder();
    // obj.deleteNodeInBST(obj.root, 99);
    // obj.inorder();
    // cout<<endl;
    // cout<<(obj.successor(obj.root))->data<<endl;
    // cout<<obj.predecessor(obj.root)->data;



    int k;
    while(k != -1){
        cout<<"\n1. Construct a BST.\n2. Inorder\n";
        cout<<"3. Preorder.\n4. Delete a node:  ";
        cin>>k;
        switch (k)
        {
        case 1:
			obj.insertInTBST();
			break;
		case 2:
            obj.inorder();
			break;
		case 3:
            obj.preorder();
			break;
		
		case 4:
            cout<<"\nEnter element to delete: ";
            int key;
            cin>>key;
            obj.deleteNodeInBST(obj.root, key);
            cout<<"After deletion: ";
            obj.inorder();
			break;
        
        default:
            break;
        }
    }
}