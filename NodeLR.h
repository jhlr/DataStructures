#ifndef _NODELR_H_
#define _NODELR_H_
#include <stdlib.h>

typedef struct NodeLR NodeLR;
struct NodeLR {
	void* value;
	NodeLR *left, *right;
};

NodeLR* NodeLR_new(void* value, NodeLR* left, NodeLR* right) {
	NodeLR* self = (NodeLR*)malloc(sizeof(NodeLR));
	self->value = value;
	self->left = left;
	self->right = right;
	return self;
};

#endif
