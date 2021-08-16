#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#include<bits/stdc++.h>
using namespace std;
vector<int>a;
int mini,maxi;
struct Node
{
    int data;
    struct Node *left, *right;
    
};


struct Node* node(int val)
{
    struct Node* temp = new Node();
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

void tr(struct Node*head)
{
    if(head==NULL)
    return ;
    tr(head->left);
    a.push_back(head->data);
    tr(head->right);
}
void* it(void* args)
{
    struct Node* temp=(struct Node*)args;
    tr(temp);
    return NULL;
}


void porder(struct Node*h)
{ struct Node*head=h;
   if(head==NULL)
   return;
  
   porder(head->left);
    cout<<head->data<<" ";
   porder(head->right);
   
}
struct Node* sortedArrayToBST(vector<int>&arr,int start, int end)
{
    /* Base Case */
    if (start > end)
    return NULL;
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct Node*root = node(arr[mid]);
 
    /* Recursively construct the left subtree
    and make it left child of root */
    root->left = sortedArrayToBST(arr, start,
                                    mid - 1);
 
    /* Recursively construct the right subtree
    and make it right child of root */
    root->right = sortedArrayToBST(arr, mid + 1, end);
 
    return root;
}
void*left(void*arg)
{
    struct Node*root=(struct Node*)arg;
    root->left=sortedArrayToBST(a, 0, ((a.size()-1)/2)-1);
}
void*right(void*arg)
{
     struct Node*root=(struct Node*)arg;
     root->right=sortedArrayToBST(a, ((a.size()-1)/2)+1,a.size()-1);
}
void* _min(void* arg)
{

    struct Node *root=(struct Node*)arg;
    while(root->left!=NULL){
        root=root->left;
    }
    cout<<"min in tree: "<<root->data<<endl;
    mini = root->data;
    
    return NULL;
}
void* _max(void* arg)
{
    struct Node*root=(struct Node*)arg;
    while(root->right!=NULL){
        root=root->right;
    }
    cout<<"max in tree: "<<root->data<<endl;
    maxi = root->data;
    return NULL;
}

int main()
{
    struct Node *root = node(100);
    root->left = node(1120);
    root->right = node(130);
    //root->left->left = node(10);
    root->left->right = node(2);
    root->right->left = node(120);
    root->right->right = node(370);
    printf("Given tree is\n");
    porder(root);
    //cout<<endl;
  a.push_back(root->data);
    
  
  //printf(root->data);
    

    pthread_t t1, t2,t3,t4;
    pthread_create(&t1, NULL, it, (void *)root->left);
    pthread_create(&t2, NULL, it, (void *)root->right);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
  sort(a.begin(),a.end());
  cout<<"\nafter sorting\n";
    for(int i=0;i<a.size();i++)
    cout<<a[i]<<" ";
    cout<<endl;
    struct Node* root2 = node(a[(a.size()-1)/2]);
    pthread_create(&t1, NULL, left, (void *)root2);
    pthread_create(&t2, NULL, right, (void *)root2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    cout << "inorder Traversal of constructed BST \n";
  
    
    porder(root2);
    cout<<endl;
    
    pthread_create(&t3, NULL, _max, (void *)root2);
    pthread_create(&t4, NULL, _min, (void *)root2);

    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    cout<<"DIFFERANCE = "<<maxi - mini<<endl;
    
    return 0;
}
