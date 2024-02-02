#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;
	node(int val){
		data = val;
		left = right = nullptr;
	}

	node* operator= (node* oldRoot){
		node* newRoot = oldRoot;
		return newRoot;
	}
};

class BinaryTree{
	node* root;
	public:
	BinaryTree(){
		root = nullptr;
	}
	node* createBinaryTree(node* root){
		int data;
		cout<<"Enter the data: ";
		cin>>data;
		root = new node(data);
		if(data == -1){
			return nullptr;
		}
		cout<<"Enter the data left of "<<data<<endl;
		root->left = createBinaryTree(root->left);
		cout<<"Enter the data right of "<<data<<endl;
		root->right = createBinaryTree(root->right);
		return root;
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
	void recursiveInorderTraversal(node* root){
		if(root == nullptr){
			return;
		}
		recursiveInorderTraversal(root->left);
		cout<<root->data<<"  ";
		recursiveInorderTraversal(root->right);
	}

	void recursivePreorderTraversal(node* root){
		if(root == nullptr){
			return;
		}
		cout<<root->data<<"  ";
		recursivePreorderTraversal(root->left);
		recursivePreorderTraversal(root->right);
	}

	void recursivePostorderTraversal(node* root){
		if(root == nullptr){
			return;
		}
		recursivePostorderTraversal(root->left);
		recursivePostorderTraversal(root->right);
		cout<<root->data<<"  ";
	}

	void inorderTraversal(node*);
	void preorderTraversal(node*);
	void postorderTraversal(node*);
	void swapTree(node*);
	int heightOfTree(node*);
	void leafNodeCount(node*, int&);
	void internalNodesCount(node*, int&);
	node* deleteTree(node*);
};

node* BinaryTree::deleteTree(node* root){
	if(root == nullptr){
		return nullptr;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	node* temp = root;
	delete temp;
	return nullptr;
}

void BinaryTree::leafNodeCount(node* root, int& count){
	if(root == nullptr){
		return;
	}
	if(root->left == nullptr && root->right == nullptr){
		count++;
	}
	leafNodeCount(root->left, count);
	leafNodeCount(root->right, count);
}

void BinaryTree::internalNodesCount(node* root, int& count){
	if(root == nullptr){
		return;
	}
	if(root->left || root->right){
		count++;
	}
	internalNodesCount(root->left, count);
	internalNodesCount(root->right, count);
}

void BinaryTree::inorderTraversal(node* root){
	stack<node*> s;
	// s.push(root);
	node* curr = root;
	while(true){
		while(curr){
			s.push(curr);
			curr = curr->left;
		}
		if (s.empty()) return;
		curr = s.top();
		s.pop();
		cout<<curr->data<<"  ";
		curr = curr->right;
		
	}
}

void BinaryTree::preorderTraversal(node* root){
	stack<node*> s;
	s.push(root);
	while(!s.empty()){
		node* temp = s.top();
		s.pop();
		cout<<temp->data<<"  ";

		if(temp->right){
			s.push(temp->right);
		}
		if(temp->left){
			s.push(temp->left);
		}
	}
}

void BinaryTree::postorderTraversal(node* root){
	stack<node*> s1;
	s1.push(root);
	stack<node*> s2;
	while(!s1.empty()){
		node* temp = s1.top();
		s1.pop();
		s2.push(temp);
		if(temp->left)
			s1.push(temp->left);
		if(temp->right)
			s1.push(temp->right);
	}
	while(!s2.empty()){
		node* temp = s2.top();
		s2.pop();
		cout<<temp->data<<"  ";
	}
}

void BinaryTree::swapTree(node* root){
	if(root == nullptr){
		return;
	}
	node* temp = root->left;
	root->left = root->right;
	root->right = temp;
	swapTree(root->left);
	swapTree(root->right);
	
}

int BinaryTree::heightOfTree(node* root){
	if(root == nullptr){
		return 0;
	}
	int left = heightOfTree(root->left);
	int right = heightOfTree(root->right);
	return max(left, right) + 1;
}

int main() {

	//1 2 4 -1 -1 5 7 -1 -1 -1 3 6 -1 8 -1 -1 -1

	//  1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
	node* root = nullptr;

	int internalcount = 0;
	int leafcount = 0; 
	BinaryTree obj;
	int k;
	bool isTreeDeleted = 0;
	while(k != -1){
	cout<<"\n";
		cout<<"1. to create a tree\n2. recursive inorder\n3. recursive preorder\n4. recursive postorder\n";
		cout<<"5. iterative inorder\n6. iterative preorder\n7. iterative postorder\n";
		cout<<"8. height of tree\n9. no of leaf node\n10. no of internal nodes\n11. copy tree to another tree\n";
		cout<<"12. erase the binary tree: \n13. Swap all left and Right nodes: \n";
		cin>>k;
		switch (k)
		{
		case 1:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			root = obj.createBinaryTree(root);
			break;
		case 2:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nRecuesive inorder: ";
			obj.recursiveInorderTraversal(root);
			break;
		case 3:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nRecuesive preorder: ";
			obj.recursivePreorderTraversal(root);
			break;
		case 4:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nRecuesive postorder: ";
			obj.recursivePostorderTraversal(root);
			break;
		case 5:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nIterative inorder: ";
			obj.inorderTraversal(root);
			break;
		case 6:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nIterative preorder: ";
			obj.preorderTraversal(root);
			break;
		case 7:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nIterative postorder: ";
			obj.postorderTraversal(root);
			break;
		case 8:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nHeight of tree: "<<obj.heightOfTree(root);
			break;
		case 9:                                                                                          
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			obj.leafNodeCount(root,leafcount);
			cout<<"\nNo of leaf nodes: "<<leafcount;
			break;
		case 10:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			obj.internalNodesCount(root, internalcount);
			cout<<"\nNo of internal nodes: "<<internalcount;
			break;
		case 11:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			node* root2;
			root2 = root;
			cout<<"\nInorder Traversal of new/second tree: ";
			obj.inorderTraversal(root2);
			break;
		case 12:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			cout<<"\nThe Tree is deleted completely: ";
			obj.deleteTree(root);
			isTreeDeleted = 1;
			break;
		case 13:
			if(isTreeDeleted) {
				cout<<"Tree is not present!!!!"<<endl;
				break;
			}
			obj.swapTree(root);
			cout<<"After swapping the node: ";
			obj.breadthFirstTraversal(root);
			break;

		
		default:
			exit(0);
		}
	}
	return 0;
}
