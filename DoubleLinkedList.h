#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <stdlib.h>
#include "NodeLR.h"

typedef struct DoubleLinkedList DoubleLinkedList;
struct DoubleLinkedList {
	NodeLR *head;
};

DoubleLinkedList* DoubleLinkedList_new() {
	DoubleLinkedList* self = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	self->head = NULL;
	return self;
}

char DoubleLinkedList_isEmpty(DoubleLinkedList* self) {
	return self == NULL || self->head == NULL;
}

void DoubleLinkedList_rotate(DoubleLinkedList* self, int index) {
	if (DoubleLinkedList_isEmpty(self)) {
		return;
	}
	int i;
	NodeLR* node = self->head;
	if(index >= 0) {
		for(i=0; i<index; i++){
			node = node->right;
		}
	} else {
		for(i=index; i<0; i++){
			node = node->left;
		}
	}
	self->head = node;
}

void DoubleLinkedList_add(DoubleLinkedList* self, int index, void* value) {
	if (DoubleLinkedList_isEmpty(self)) {
		self->head = NodeLR_new(value, NULL, NULL);
		self->head->left = self->head->right = self->head;
		return;
	}
	DoubleLinkedList temp = *self;
	DoubleLinkedList* ll = &temp;
	DoubleLinkedList_rotate(ll, index);
	NodeLR* node = NodeLR_new(value, ll->head->left, ll->head);
	ll->head->left->right = node;
	ll->head->left = node;
	if(index == 0){
		self->head = ll->head->left;
	}
}


void* DoubleLinkedList_set(DoubleLinkedList* self, int index, void* value) {
	void* result;
	if (DoubleLinkedList_isEmpty(self)) {
		return NULL;
	}
	DoubleLinkedList temp = *self;
	DoubleLinkedList* ll = &temp;
	DoubleLinkedList_rotate(ll, index);
	if(value == NULL){
		if (ll->head->left == ll->head) {
			self->head = NULL;
		} else {
			ll->head->right->left = ll->head->left;
			ll->head->left->right = ll->head->right;
			if(index == 0) {
				self->head = ll->head->right;
			}
		}
		result = ll->head->value;
		free(ll->head);
	} else if(value == (void*)-1){
		result = ll->head->value;
	} else {
		result = ll->head->value;
		ll->head->value = value;
	}
	return result;
}

void* DoubleLinkedList_get(DoubleLinkedList* self, int index) {
	return DoubleLinkedList_set(self, index, (void*)-1);
}

void* DoubleLinkedList_remove(DoubleLinkedList* self, int index) {
	return DoubleLinkedList_set(self, index, NULL);
}


int DoubleLinkedList_size(DoubleLinkedList* self) {
	if (DoubleLinkedList_isEmpty(self)) {
		return 0;
	}
	int i = 0;
	NodeLR* node = self->head;
	do {
		i++;
		node = node->right;
	} while (node != self->head);
	return i;
}

void DoubleLinkedList_iterate(DoubleLinkedList* self, void(*action)(void*)){
	NodeLR* node = self->head;
	do{
		action(node->value);
		node = node->right;
	}while(node != self->head);
}

void DoubleLinkedList_clear(DoubleLinkedList* self){
	while(!DoubleLinkedList_isEmpty(self)){
		DoubleLinkedList_remove(self, 0);
	}
}

#endif
