////////////////////////////////////////////////////////
// Binary search tree algorithm
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "BinTree.h"

// Allocate memory for a node
static BinNode *AllocBinNode(void)
{
	BinNode *node = calloc(1, sizeof(BinNode));

	if(!node){
		fprintf(stderr, "Failed to calloc in AllocBinNode\n");
		return NULL;
	}
	return node;
}

// Set values for each node
static void SetBinNode(BinNode *n, const Member *x, const BinNode *left,
	const BinNode *right)
{
	n->data = *x; // Data
	n->left = (BinNode *)left; // Pointer to left child node
	n->right = (BinNode *)right; // Pointer to right child node
}

// Search node
BinNode *Search(BinNode *p, const Member *x)
{
	int compare_result;

	if (!p) // Failed to search
		return NULL;
	else if ((compare_result = MemberNoCmp(x, &p->data)) == 0) // Succeed to search
		return p;
	else if (compare_result < 0)
		Search(p->left, x); // Search from left tree
	else
		Search(p->right, x); // Search from right tree
}

// Insert node
BinNode *Add(BinNode *p, const Member *x)
{
	int compare_result;

	if (!p) {
		p = AllocBinNode();
		if(!p){
			fprintf(stderr, "Failed to calloc in Add\n");
			return NULL;
		}
		SetBinNode(p, x, NULL, NULL);
	}
	else if ((compare_result = MemberNoCmp(x, &p->data)) == 0)
		fprintf(stderr, "Error: %d is already in the tree\n", x->no);
	else if (compare_result < 0)
		p->left = Add(p->left, x);
	else
		p->right = Add(p->right, x);
	return p;
}

// Remove a node
int Remove(BinNode **root, const Member *target){
	BinNode **p = root;

	while(*p){
		BinNode *x = *p;
		int compare_result = MemberNoCmp(target, &x->data);
		if (compare_result == 0){ // Succeed to search
            if( !(x->left) && !(x->right) ){ // x has no child
                *p = NULL;
            }
            else if( !(x->left) ){ // x has right child
                *p = x->right;
            }
            else if( !(x->right) ){ // x has left child
                *p = x->left;
            }
			else{ // x has both childs
                *p = DeleteMinNode( &x->right );
                (*p)->left = x->left;
                (*p)->right = x->right;
			}
			free(x);
            return 0;
		}
		else if(compare_result < 0){ //Target value is smaller than current node
			p = &x->left;
		}
		else{ //Target value is bigger than current node
			p = &x->right;
		}
	}
	fprintf(stderr, "Error: %d is not registered in the tree\n", target->no);
	return -1;
}

// Search min node from the tree
BinNode *GetMinNode(const BinNode *p){
	if(!p)
		return NULL;

	BinNode *node = (BinNode *)p;

	while(node->left)
		node = node->left;

	return node;
}

// Search max node from the tree
BinNode *GetMaxNode(const BinNode *p){
	if(!p)
		return NULL;

	BinNode *node = (BinNode *)p;

	while(node->right)
		node = node->right;

	return node;
}

BinNode *DeleteMinNode(BinNode **p){
	BinNode *min = GetMinNode(*p);
	*p = (*p)->right;
	return min;
}

BinNode *DeleteMaxNode(BinNode **p){
	BinNode *max = GetMaxNode(*p);
	*p = (*p)->left;
	return max;
}

// Print all nodes (ascending)
void PrintTree(const BinNode *p)
{
	if (p) {
		PrintTree(p->left);
		PrintLnMember(&p->data);
		PrintTree(p->right);
	}
}

// Print all nodes (descending)
void PrintTreeReverse(const BinNode *p)
{
	if (p) {
		PrintTreeReverse(p->right);
		PrintLnMember(&p->data);
		PrintTreeReverse(p->left);
	}
}

// Free all nodes
void FreeTree(BinNode *p)
{
	if (p) {
		FreeTree(p->left);
		FreeTree(p->right);
		free(p);
	}
}
