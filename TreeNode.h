#ifndef _TREENODE_H_
#define _TREENODE_H_

#define MAX(a, b) ((a > b)? a : b)
#undef NULL
#define NULL ((void*)0)

#include <stdlib.h>
#include "PairKV.h"

typedef struct TreeNode TreeNode;
struct TreeNode {
	int height;
	PairKV content;
	TreeNode* left;
	TreeNode* right;
};

int TreeNode_balance(TreeNode*);

TreeNode* TreeNode_new(long key, void* value, TreeNode* left, TreeNode* right){
	TreeNode* self = (TreeNode*)malloc(sizeof(TreeNode));
	self->content.key = key;
	self->content.value = value;
	self->left = left;
	self->right = right;
	TreeNode_balance(self);
	return self;
}

int TreeNode_height(TreeNode* self){
	if(self == NULL){
		return 0;
	}
	return self->height;
}

int TreeNode_balance(TreeNode* self){
	if(self == NULL) return 0;
	self->height = MAX(TreeNode_height(self->left), TreeNode_height(self->right))+1;
	return TreeNode_height(self->left) - TreeNode_height(self->right);
}

TreeNode* _TreeNode_rotate_left(TreeNode* self){
	TreeNode *y = self->right;
	TreeNode *temp = y->left;
	y->left = self;
	self->right = temp;
	TreeNode_balance(self);
	TreeNode_balance(y);
	return y;
}

TreeNode* _TreeNode_rotate_right(TreeNode* self){
	TreeNode *x = self->left;
	TreeNode *temp = x->right;
	x->right = self;
	self->left = temp;
	TreeNode_balance(self);
	TreeNode_balance(x);
	return x;

}

TreeNode* TreeNode_remove(TreeNode* self, long key){
	if(TreeNode_height(self) == 0){
		return self;
	}
	if(key < self->content.key){
		self->left = TreeNode_remove(self->left, key);
	} else if(key > self->content.key){
		self->right = TreeNode_remove(self->right, key);
	} else if(self->left == NULL || self->right == NULL){
		TreeNode *temp = (self->left != NULL)? self->left : self->right;
		if(temp == NULL){
			temp = self;
			self = NULL;
		} else {
			*self = *temp;
		}
		free(temp);
	} else {
		TreeNode* temp = self->right;
		while(temp->left != NULL){
			temp = temp->left;
		}
		self->content = temp->content;
		self->right = TreeNode_remove(self->right, self->content.key);
	}
	if(self == NULL){
		return NULL;
	}
	int balance = TreeNode_balance(self);
	if(balance > 1){
		if(TreeNode_balance(self->left) < 0){
			self->left = _TreeNode_rotate_left(self->left);
		}
		return _TreeNode_rotate_right(self);
	} else if(balance < -1){
		if(TreeNode_balance(self->right) > 0){
			self->right = _TreeNode_rotate_right(self->right);
		}
		return _TreeNode_rotate_left(self);
	}
	return self;
}

void* TreeNode_set(TreeNode* self, long key, void* value){
	if(value == NULL){
		return TreeNode_remove(self, key);
	}
	TreeNode* node = self;
	void* result = NULL;
	char isLeft;
	while(node != NULL){
		if(node->content.key < key){
			isLeft = 0;
			node = node->right;
		} else if(node->content.key > key){
			isLeft = 1;
			node = node->left;
		} else {
			result = node->content.value;
			if(value != (void*)-1) {
				node->content.value = value;
			}
			return result;
		}
	}
	return result;
}

TreeNode* TreeNode_add(TreeNode* self, long key, void* value){
	if(value == NULL){
		return self;
	}
	if(self == NULL){
		return TreeNode_new(key, value, NULL, NULL);
	}
	if(key < self->content.key){
		self->left = TreeNode_add(self->left, key, value);
	} else {
		self->right = TreeNode_add(self->right, key, value);
	}
	int balance = TreeNode_balance(self);
	if(balance > 1){
		if(key > self->left->content.key){
			self->left = _TreeNode_rotate_left(self->left);
		}
		return _TreeNode_rotate_right(self);
	} else if(balance < -1){
		if(key < self->right->content.key){
			self->right = _TreeNode_rotate_right(self->right);
		}
		return _TreeNode_rotate_left(self);
	}
	return self;
}

void* TreeNode_get(TreeNode* self, long key){
	return TreeNode_set(self, key, (void*)-1);
}

char TreeNode_contains(TreeNode* self, long key){
	return TreeNode_get(self, key) != NULL;
}

void TreeNode_clear(TreeNode* self){
	if(self == NULL){
		return;
	}
	TreeNode_clear(self->left);
	TreeNode_clear(self->right);
	free(self->content.value);
	free(self);
}

#undef MAX
#endif
