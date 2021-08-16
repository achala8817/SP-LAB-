#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#include <limits.h>

struct Node
{
	int data;
	struct Node *left, *right;
	int min, max;
};


struct Node* cn(int val)
{
	struct Node* temp = (struct Node *)malloc(sizeof(struct Node));
	temp->data = val;
	temp->left = temp->right = NULL;
}

bool cb(struct Node* head, int min, int max)
{
	if(head == NULL)
		return true;
	if(head->data < min || head->data > max)
		return false;
	return cb(head->left, min, head->data) && cb(head->right, head->data, max);
}

bool nbst = false;

void* isBST(void* args)
{
	struct Node* temp = (struct Node *)args;
	if(cb(temp, temp->min, temp->max) == false)
		nbst = true;
	return NULL;
}

int main()
{
	struct Node *root = cn(10);
	root->left = cn(20);
	root->right = cn(130);
	root->left->left = cn(101);
	root->left->right = cn(50);
	root->right->left = cn(120);
	root->right->right = cn(370);

	if(root->data < root->left->data || root->data > root->right->data)
	{
		printf("Tree is not BST\n");
		return 0;
	}

	root->left->min = INT_MIN;
	root->left->max = root->data;

	root->right->min = root->data;
	root->right->max = INT_MAX;

	pthread_t t1, t2;
	pthread_create(&t1, NULL, isBST, (void *)root->left);
	pthread_create(&t2, NULL, isBST, (void *)root->right);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	if(nbst == true)
	{
		printf("Given Tree in Not BST\n");
	}
	else
		printf("Given Tree is a BST\n");
	
	return 0;
}
