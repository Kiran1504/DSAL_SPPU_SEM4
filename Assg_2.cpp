#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;
	node(int val){
		this->data = val;
		this->left = this->right = nullptr;
	}

    node* operator= (node* oldRoot){
		node* newRoot = oldRoot;
		return newRoot;
	}
};

class BST{
    public:
    node* root;
    BST(){
        root = nullptr;
    }
    node* constructTree(node* tempRoot, int val){
        if(tempRoot == nullptr){
            node* nn = new node(val);
            return nn;
        }
        if(val > tempRoot->data){
            tempRoot->right = constructTree(tempRoot->right, val);
        }
        else{
            tempRoot->left = constructTree(tempRoot->left, val);
        }
        return tempRoot;
    }
    void inputSequence(){
        cout<<"\nEnter the elements: ";
        int val;
        while(true){
            cin>>val;
            if(val == -1){
                break;
            }
            root = constructTree(root, val);
        }
    }

    void recursiveInorderTraversal(node* root){
		if(root == nullptr){
			return;
		}
		recursiveInorderTraversal(root->left);
		cout<<root->data<<"  ";
		recursiveInorderTraversal(root->right);
	}


    void breadthFirstTraversal(node* root){
		if(root == nullptr){
			return;
		}
		queue<node*> q;
		q.push(root);
		cout<<endl;
		q.push(nullptr);
		while(!q.empty()){
			node* temp = q.front();
			q.pop();
			cout<<temp->data<<"  ";
			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
			if(q.front() == nullptr){
				cout<<endl;
				q.pop();
				if(!q.empty())
					q.push(nullptr);
				continue;
			}
		}
	}

    void insertInBST(){
        cout<<"\nEnter the element to insert: ";
        int val;
        cin>>val;
        root = constructTree(root, val);
    }

    node* minimumInBST(node* root){
        if(root->left == nullptr){
            return root;
        }
        return minimumInBST(root->left);
        
    }
    node* maximumInBST(node* root){
        if(root->right == nullptr){
            return root;
        }
        return maximumInBST(root->right);
    }
    void swapTree(node* root){
        if(root == nullptr){
            return;
        }
        node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        swapTree(root->left);
        swapTree(root->right);
	
    }
    node* successor(node* ptr){
        node* temp = ptr->right;
        while(temp->left){
            temp = temp->left;
        }
        return temp;
    }
    int longestPathFromRoot(node* root){
            if(root == nullptr){
            return 0;
        }
        int left = longestPathFromRoot(root->left);
        int right = longestPathFromRoot(root->right);
        return max(left, right) + 1;
    }

    bool searchInBST(node* root, int key){
        if(root == nullptr){
            return false;
        }
        if(root->data == key){
            return true;
        }
        if(root->data < key){
            return searchInBST(root->right, key);
        }
        else{
            return searchInBST(root->left, key);
        }
    }

    node* deleteFromBST(node* root, int key){
        if(root == nullptr){
            return root;
        }
        if(root->data == key){
            if(!root->left && !root->right){
                delete root;
                return nullptr;
            }

            //1 child
            if(root->left && !root->right){
                node* temp = root->left;
                delete root;
                return temp;
            }
            if(!root->left && root->right){
                node* temp = root->right;
                delete root;
                return temp;
            }

            // 2 child
            if(root->left && root->right){
                int succ = successor(root)->data;
                root->data = succ;
                root->right = deleteFromBST(root->right, succ);
                return root;
            }
        }
        if(root->data < key){
            return deleteFromBST(root->right, key);
        }
        else{
            return deleteFromBST(root->left, key);
        }
    }
};


int main(){
    BST obj;
    // obj.inputSequence();
    // obj.breadthFirstTraversal(obj.root);
    node* minnode;
    node* maxnode;
    node* copytree;

    // cout<<"\n\nmini: "<<minnode->data<<" maxi: "<<maxnode->data;
    int k;
    while(k != -1){
        cout<<"\n1. Construct a BST.\n2. Insert a node.\n3. Count of nodes in Longest path.\n4. Minimum in BST.\n";
        cout<<"5. Maximum in BST.\n6. Swap the BST.\n7. Search in BST:  ";
        cin>>k;
        switch (k)
        {
        case 1:
			obj.inputSequence();
			break;
		case 2:
			obj.insertInBST();
            obj.breadthFirstTraversal(obj.root);
			break;
		case 3:
			cout<<"\nCount of nodes in Longest path: "<<obj.longestPathFromRoot(obj.root);
			break;
		case 4:
			minnode = obj.minimumInBST(obj.root);
			cout<<"\nMinimum node in BST: "<<minnode->data;
			break;
		case 5:
			maxnode = obj.maximumInBST(obj.root);
			cout<<"\nMaximum node in BST: "<<maxnode->data;
			break;
		case 6:
            copytree = obj.root;
			cout<<"\nAfter Swapping the tree: ";
            obj.swapTree(copytree);
			obj.breadthFirstTraversal(copytree);
			break;
		case 7:
            cout<<"\nEnter element to search: ";
            int key;
            bool result;
            cin>>key;
			result = obj.searchInBST(obj.root, key);
			cout<<"\nSearch Result: "<<result;
			break;
        
        default:
            break;
        }
    }

}