#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "NodeN.h"

#undef NULL
#define NULL ((void*)0)

typedef struct LinkedList LinkedList;
struct LinkedList {
	NodeN* head;
};

LinkedList* LinkedList_new(){
	LinkedList* self = (LinkedList*)malloc(sizeof(LinkedList));
	self->head = NULL;
	return self;
}

char LinkedList_isEmpty(LinkedList* self){
	return self == NULL || self->head == NULL;
}

int LinkedList_size(LinkedList* self) {
	if(LinkedList_isEmpty(self)){
		return 0;
	}
	NodeN* node = self->head;
	int i=0;
	do{
		i++;
		node = node->next;
	}while(node != self->head);
	return i;
}

void LinkedList_rotate(LinkedList* self, int index) {
	const int size = LinkedList_size(self);
	if(size == 0 || index == 0){
		return;
	}
	NodeN* node = self->head;
	index %= size;
	int i;
	if(index < 0){
		index = size + index;
	}
	for(i=0; i<index; i++){
		node = node->next;
	}
	self->head = node;
}

void LinkedList_add(LinkedList* self, int index, void* value) {
	if (LinkedList_isEmpty(self)) {
		self->head = NodeN_new(value, NULL);
		self->head->next = self->head;
		return;
	}
	LinkedList temp = *self;
	LinkedList* ll = &temp;
	LinkedList_rotate(ll, index-1);
	NodeN* node = NodeN_new(value, ll->head->next);
	ll->head->next = node;
	if(index == 0){
		self->head = ll->head->next;
	}
}

void* LinkedList_set(LinkedList* self, int index, void* value) {
	void* result;
	if (LinkedList_isEmpty(self)) {
		return NULL;
	}
	LinkedList temp = *self;
	LinkedList* ll = &temp;
	LinkedList_rotate(ll, index-1);
	if(value == NULL){
		if (ll->head->next == ll->head) {
			self->head = NULL;
		} else {
			ll->head->next = ll->head->next->next;
			if(index == 0) {
				self->head = ll->head->next;
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

void* LinkedList_get(LinkedList* self, int index) {
	return LinkedList_set(self, index, (void*)-1);
}

void* LinkedList_remove(LinkedList* self, int index) {
	return LinkedList_set(self, index, NULL);
}

void LinkedList_iterate(LinkedList* self, void(*action)(void*)){
	if(LinkedList_isEmpty(self)){
		return;
	}
	NodeN* node = self->head;
	do{
		action(node->value);
		node = node->next;
	}while(node != self->head);
}

void LinkedList_clear(LinkedList* self){
	while(!LinkedList_isEmpty(self)){
		free(LinkedList_remove(self, 0));
	}
}



#endif
