#ifndef _TREEMAP_H_
#define _TREEMAP_H_

#undef NULL
#define NULL ((void*)0)

#include "TreeNode.h"

typedef struct TreeMap TreeMap;
struct TreeMap {
	long(*hashfunc)(void*);
	TreeNode* root;
};

TreeMap* TreeMap_new(long(*hashfunc)(void*)){
	TreeMap* self = (TreeMap*)malloc(sizeof(TreeMap));
	self->root = NULL;
	self->hashfunc = hashfunc;
	return self;
}

char TreeMap_isEmpty(TreeMap* self){
	return self->root == NULL;
}

void TreeMap_remove(TreeMap* self, void* key){
	self->root = TreeNode_remove(self->root, self->hashfunc(key));
}

void* TreeMap_get(TreeMap* self, void* key){
	return TreeNode_get(self->root, self->hashfunc(key));
}

char TreeMap_contains(TreeMap* self, void* key){
	return TreeMap_get(self, key) != NULL;
}

void TreeMap_put(TreeMap* self, void* key, void* value){
	if(value == NULL){
		TreeMap_remove(self, key);
	} else if(TreeNode_set(self->root, self->hashfunc(key), value) == NULL){
		self->root = TreeNode_add(self->root, self->hashfunc(key), value);
	}
}

int TreeMap_height(TreeMap* self){
	return self->root->height;
}

#endif
