#include<iostream>
#include<stdio.h>

using namespace std;

struct node{
	long int lo,hi,max;
	struct node* right,left,parent;
}

void maxassign(struct node* parent, struct node* left, struct node* right){
	if(left==NULL && right==NULL)
		parent->max=parent->hi;

	else if(left!=NULL && right==NULL)
		parent->max=((left->hi) >= (parent->hi)) ? (left->hi) : (parent->hi);
	
	else if(left==NULL && right!=NULL)
		parent->max=((right->hi) >= (parent->hi)) ? (right->hi) : (parent->hi);

	else if(left!=NULL && right!=NULL){
		long int temp=((long int dummy=((left->hi)>=(right->hi) ? (left->hi) : (right->hi) )) >= (parent->hi)) ? dummy : (parent->hi);
		parent->max=temp;
	}
}


void insert(long int low, long int high, struct node* root){
	struct node* x=root;

	if(root==NULL){
		root=(struct node*)malloc(sizeof(struct node));
		root->lo=low;
		root->hi=high;
		root->left=NULL;
		root->right=NULL;
		root->max=high;
	}

	else{
		struct node* y;

		if(high<=(root->hi))
			y=root->left;
		else
			y=root->right;

		
		while(y!=NULL){
			x=y;
			if(high<=(x->hi))
				y=x->left;
			else
				y=x->right;
		}

		struct node* temp;
		if(high<=(x->hi)){
			x->left=(struct node*)malloc(sizeof(struct node));
			temp=x->left;
		}
		else{
			x-right=(struct node*)malloc(sizeof(struct node));
			temp=x->right;
		}

		temp->lo=low;
		temp->hi=high;
		temp->max=high;
		maxassign(x,x->left,x->right);
		
		}
}

int main(){
	long int t;
	cin>>t;
}