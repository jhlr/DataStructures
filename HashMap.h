#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdlib.h>
#include "LinkedList.h"
#include "PairKV.h"

typedef struct HashMap HashMap;
struct HashMap {
	int size;
	long(*hashfunc)(void*);
	LinkedList* values; // Array<LinkedList<PairKV>>
};

HashMap* HashMap_new(int size, long(*hashfunc)(void*)){
	HashMap* self = (HashMap*)malloc(4+sizeof(HashMap));
	self->size = size;
	self->values = (LinkedList*)malloc(size*sizeof(LinkedList));
	int i;
	for(i=0; i<size; i++){
		self->values[i] = (LinkedList){NULL};
	}
	self->hashfunc = hashfunc;
	return self;
}

void* HashMap_put(HashMap* self, void* key, void* value){
	long hash = self->hashfunc(key);
	int i=0;
	int k = hash % self->size;
	if(k < 0){
		k = 0 - k;
	}
	PairKV* temp;
	void* result;
	NodeN* node = self->values[k].head;
	do{
		if(node == NULL){
			break;
		}
		temp = (PairKV*) node->value;
		if(hash == temp->key){
			if(value == NULL){
				result = LinkedList_remove(&self->values[k], i);
			} else if(value == (void*)-1){
				result = temp->value;
			} else {
				result = temp->value;
				temp->value = value;
			}
			return result;
		}
		i++;
		node = node->next;
	}while(node != self->values[k].head);
	if((long)value != 0 && (long)value != -1){
		PairKV* pair = PairKV_new(hash, value);
		LinkedList_add(&self->values[k], 1, pair);
	}
	return NULL;
}

void* HashMap_remove(HashMap* self, void* key){
	return HashMap_put(self, key, NULL);
}

void* HashMap_get(HashMap* self, void* key){
	return HashMap_put(self, key, (void*)-1);
}

char HashMap_contains(HashMap* self, void* key){
	return HashMap_get(self, key) != NULL;
}

void HashMap_clear(HashMap* self){
	int i;
	for(i=0; i<self->size; i++){
		LinkedList_clear(&self->values[i]);
	}
}

#endif
