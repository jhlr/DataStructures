#ifndef _NODEN_H_
#define _NODEN_H_

typedef struct NodeN NodeN;
struct NodeN {
	void* value;
	NodeN* next;
};

NodeN* NodeN_new(void* value, NodeN* next){
	NodeN* self = (NodeN*)malloc(sizeof(NodeN));
	self->value = value;
	self->next = next;
	return self;
}

#endif
