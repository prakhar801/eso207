#include<iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

struct node{
	long int lo,hi;
	struct node* right;
	struct node* left;
	struct node* parent;
};

void insert(long int low, long int high, struct node** root1,struct node** root2){
	struct node* x;

	if((*root1)==NULL){
		(*root1)=(struct node*)malloc(sizeof(struct node));
		(*root1)->lo=low;
		(*root1)->hi=high;
		(*root1)->left=NULL;
		(*root1)->right=NULL;
		(*root1)->parent=NULL;
	}

	else{
		x=(*root1);
		struct node* y;

		if(low<(x->lo))
			y=x->left;
		else
			y=x->right;

		
		while(y!=NULL){
			x=y;
			if(low<(x->lo))
				y=x->left;
			else
				y=x->right;
		}

		struct node* temp;
		if(low<(x->lo)){
			x->left=(struct node*)malloc(sizeof(struct node));
			temp=x->left;
		}
		else{
			x->right=(struct node*)malloc(sizeof(struct node));
			temp=x->right;
		}

		temp->lo=low;
		temp->hi=high;
		temp->left=NULL;
		temp->right=NULL;
		temp->parent=x;
		
		}

		if((*root2)==NULL){
			*root2=(struct node*)malloc(sizeof(struct node));
			(*root2)->lo=low;
			(*root2)->hi=high;
			(*root2)->left=NULL;
			(*root2)->right=NULL;
			(*root2)->parent=NULL;
		}


		else{
			x=(*root2);
			struct node* y;

			if(high<=(x->hi))
				y=x->left;
			else
				y=x->right;

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
				x->right=(struct node*)malloc(sizeof(struct node));
				temp=x->right;
			}

			temp->lo=low;
			temp->hi=high;
			temp->left=NULL;
			temp->right=NULL;
			temp->parent=x;
		}
}

void traversal(struct node* root){

	if(root==NULL){
		return;
	}

	traversal(root->left);
	cout<<" ["<<root->lo<<","<<root->hi<<"] ";
	traversal(root->right);

}

struct node* min(struct node* root){   //x points at the node with min lo. call with tree 1
	struct node* x,y;
	x=root;
	while((root->left)!=NULL){
		x=(root->left);
		(root->left)=(x->left);
	}

	return x;

}

struct node* max(struct node* root){ //x points at the node with max hi call with tree 2
	struct node* x,y;
	x=root;
	while((root->right)!=NULL){
		x=(root->right);
		(root->right)=(x->right);
	}

	return x;
}

struct node* successor(struct node* x){

	if(x==NULL)
		return NULL;

	else if((x->right)!=NULL){
		return min(x->right);
	}

	else{
		struct node* y=x->parent;
		while(y!=NULL && x==(y->right)){
			x=y;
			y=x->parent;
		}
		return y;
	}

}

void transplant(struct node** root,struct node* u,struct node* v){
	if(u==(*root))
		*root=v;

	else if(u==((u->parent)->left))
		((u->parent)->left)=v;
	
	else
		((u->parent)->right)=v;

	if(v!=NULL)
		(v->parent)=(u->parent);

}

struct node* search1(long int low,long int high,struct node** root){ //returns pointer to interval low,high
	struct node* x=*root;

	while(x!=NULL){
		if(low==(x->lo) && high==(x->hi))
			return x;

		else if(low<(x->lo))
			x=x->left;

		else
			x=x->right;
	}

		return x;

}

struct node* search2(long int low,long int high,struct node** root){
	struct node* x=(*root);

	while(x!=NULL){
		if(low==(x->lo)  &&  high==(x->hi))
			return x;

		else if(high<=(x->hi))
			x=(x->left);

		else
			x=(x->right);
	}

	return x;
}

void nodedelete(long int low,long int high,struct node** root1,struct node** root2){

	struct node* temp1=search1(low,high,root1);
	struct node* temp2=search2(low,high,root2);

	if(temp1!=NULL){
		if((temp1->left)==NULL)
			transplant(root1,temp1,temp1->right);
		else if((temp1->right)==NULL)
			transplant(root1,temp1,temp1->right);

		else{
			struct node* y=min(temp1->right);

			if((y->parent)!=temp1){
				transplant(root1,temp1,temp1->right);
				(y->right)=(temp1->right);
				((y->right)->parent)=y;
			}

			transplant(root1,temp1,y);
			(y->left)=(temp1->left);
			((y->left)->parent)=y;
		}
	}


	if(temp2!=NULL){
		if((temp2->left)==NULL)
			transplant(root2,temp1,temp2->right);
		else if((temp2->right)==NULL)
			transplant(root2,temp2,temp2->right);

		else{
			struct node* y=min(temp2->right);

			if((y->parent)!=temp2){
				transplant(root2,temp2,temp2->right);
				(y->right)=(temp2->right);
				((y->right)->parent)=y;
			}

			transplant(root2,temp2,y);
			(y->left)=(temp2->left);
			((y->left)->parent)=y;
		}
	}

}

// int overlap(long int low,long int high,struct node* root){
	
// }

int main(){
	long int t;
	cin>>t;

	for(long int i=0;i<t;i++){
		struct node* tree1=NULL;
		struct node* tree2=NULL;

		long int n;
		cin>>n;
		int one=1;
		for(long int j=0;j<n;j++){
			char str[80];
			if(one){getchar(); one=0;}
			cin.getline(str,80);
			
			if(str[0]=='+'){
				int k=2;
				long int temp1=0,temp2=0;
				while(str[k]!=' '){
					temp1=temp1*10+int(str[k])-48;
					k++;
				}
				k++;
				while(str[k]!='\0'){
					temp2=temp2*10+int(str[k])-48;
					k++;
				}
				insert(temp1,temp2,&tree1,&tree2);   // check for min of temp1,temp2 assumed temp1 is min
			}

			else if(str[0]=='-'){
				int k=2;
				long int temp1=0,temp2=0;
				while(str[k]!=' '){
					temp1=temp1*10+int(str[k])-48;
					k++;
				}
				k++;
				while(str[k]!='\0'){
					temp2=temp2*10+int(str[k])-48;
					k++;
				}
				nodedelete(temp1,temp2,&tree1,&tree2);
			}

			else if(!strcmp(str,"min")){
				struct node* temp=min(tree1);
				cout<<"["<<temp->lo<<" "<<temp->hi<<"]\n";
			}

			else if(!strcmp(str,"max")){
				struct node* temp=max(tree2);
				cout<<"["<<temp->lo<<" "<<temp->hi<<"]\n";
			}

			else if(str[0]=='l'){
				int k=6;
				long int temp1=0,temp2=0;
				while(str[k]!=' '){
					temp1=temp1*10+int(str[k])-48;
					k++;
				}
				k++;
				while(str[k]!='\0'){
					temp2=temp2*10+int(str[k])-48;
					k++;
				}

				struct node* temp=search1(temp1,temp2,&tree1);
				struct node* succ=successor(temp);
				cout<<"["<<succ->lo<<" "<<succ->hi<<"]\n";
			}

			else if(str[0]=='h'){
				int k=6;
				long int temp1=0,temp2=0;
				while(str[k]!=' '){
					temp1=temp1*10+int(str[k])-48;
					k++;
				}
				k++;
				while(str[k]!='\0'){
					temp2=temp2*10+int(str[k])-48;
					k++;
				}
				struct node* temp=search2(temp1,temp2,&tree2);
				struct node* succ=successor(temp);
				cout<<"["<<succ->lo<<" "<<succ->hi<<"]\n";
			}


		}
	}

	return 0;
}