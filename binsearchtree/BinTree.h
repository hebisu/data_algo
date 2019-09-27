////////////////////////////////////////////////////////
// Binary search tree algorithm (Header)
////////////////////////////////////////////////////////

#ifndef ___BinTree
#define ___BinTree

#include "Member.h"

// Node
typedef struct __bnode {
	Member         data; // Data
	struct __bnode *left; // Pointer to left child node
	struct __bnode *right; // Pointer to right child node
} BinNode;

BinNode *Search(BinNode *p, const Member *x);
BinNode *Add(BinNode *p, const Member *x);
BinNode *GetMinNode(const BinNode *p);
BinNode *GetMaxNode(const BinNode *p);
BinNode *DeleteMinNode(BinNode **p);
BinNode *DeleteMaxNode(BinNode **p);
int Remove(BinNode **root, const Member *target);
void PrintTree(const BinNode *p);
void PrintTreeReverse(const BinNode *p);
void FreeTree(BinNode *p);

#endif
