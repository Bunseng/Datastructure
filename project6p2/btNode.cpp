#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

// write definition for bst_insert here
bool bst_insert(btNode*& bst_root, int insInt)
{
   btNode* current;
   btNode* parent;
   if(bst_root == 0){
   	btNode* temp = new btNode;
	temp->data = insInt;
	temp->left = temp->right = 0;

	bst_root = temp;
 	current = bst_root;
   
    }else{
  	current = bst_root;
 
	while(current != 0){
	if(current->data == insInt){
		return false;
        }
	if(insInt < current->data){
		parent = current;
		current = current->left;
	}
	else{
		parent = current;
		current = current->right;
	}
        }
	btNode* temp = new btNode;
	temp->data = insInt;
	temp->left = temp->right = 0;

	if(insInt < parent->data)
		parent->left = temp;
	else
		parent->right = temp;
    }
	return true;
}
// write definition for bst_remove here
bool bst_remove(btNode*& bst_root, int remInt)
{
   if(bst_root == 0) return false;
   if(remInt < bst_root->data)
	return bst_remove(bst_root->left, remInt);
   if(remInt > bst_root->data)
	return bst_remove(bst_root->right, remInt);
   if(remInt == bst_root->data){
	if(bst_root->left == 0){
		btNode* prev = bst_root;
		bst_root = bst_root->right;
		delete prev;
		return true;
	}
	else
		bst_remove_max(bst_root->left, bst_root->data);
		return true;
   }
	return false;
}
// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& data)
{
   btNode* current = new btNode;
   current = bst_root;
   btNode* deletePtr = new btNode;
   deletePtr = 0;
   
   if(current->right == 0){
	data = current->data;
   	bst_root = bst_root->left;
   	delete deletePtr;
   }else
	bst_remove_max(current->right, data);
}

