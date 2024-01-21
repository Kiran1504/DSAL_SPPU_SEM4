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
};

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

void inorderTraversal(node* root){
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

void preorderTraversal(node* root){
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

void postorderTraversal(node* root){
	stack<node*> s;
	s.push(root);
	node* curr = root;
	while(true){
		while(curr->right){
			s.push(curr->right);
			curr = curr->right;
		}
		while(curr->left){
			s.push(curr->left);
			curr = curr->left;
		}
		if (s.empty()) return;
		curr = s.top();
		s.pop();
		cout<<curr->data<<"  ";
		if(curr->left) {
			curr = curr->left;
			s.push(curr);
		}
		
	}
}

int main() {

	//1 2 4 -1 -1 5 7 -1 -1 -1 3 6 -1 8 -1 -1 -1

	//  1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
	node* root = nullptr;
	root = createBinaryTree(root);
	cout<<"Breadth First Traversal(Level Order) result:  ";
	breadthFirstTraversal(root);
	cout<<"\nRecursive InOrder Traversal result:  "<<endl;
	recursiveInorderTraversal(root);
	cout<<"\nRecursive PreOrder Traversal result:  "<<endl;
	recursivePreorderTraversal(root);
	cout<<"\nRecursive PostOrder Traversal result:  "<<endl;
	recursivePostorderTraversal(root);
	cout<<"\nIterative InOrder Traversal result:  "<<endl;
	inorderTraversal(root);
	cout<<"\nIterative PreOrder Traversal result:  "<<endl;
	preorderTraversal(root);
	cout<<"\nIterative PostOrder Traversal result:  "<<endl;
	postorderTraversal(root);
	cout<<"\n";


	return 0;
}
