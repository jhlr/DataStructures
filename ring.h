#ifndef _RING_H_
#define _RING_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct ring_t ring_t;
struct ring_t {
	void* value;
	ring_t* next;
};

ring_t* ring_new(void* value) {
	ring_t* temp = (ring_t*) malloc(sizeof(ring_t));
	temp->value = value;
	temp->next = temp;
	return temp;
}

int ring_len(ring_t* self) {
	if (self == NULL) {
		return 0;
	}
	ring_t* nd = self;
	int i=0;
	do {
		i++;
		nd = nd->next;
	} while(nd != self);
	return i;
}

ring_t* ring_rotate(ring_t* self, int i) {
	if (self == NULL) {
		return NULL;
	} else if (i < 0) {
		int len = ring_len(self);
		i = i%len + len;
	}
	for (; i>0; i--) {
		self = self->next;
	}
	return self;
}

ring_t* ring_link(ring_t* self, int i, ring_t* nd) {
	if (nd == NULL) {
		return self;
	} else if (self == NULL) {
		nd->next = nd;
		return nd;
	}

	// consider nd as a full ring
	ring_t* last = ring_rotate(nd, -1);

	int j;
	int len = ring_len(self);
	if (i < 0) {
		j = i%(len+1) + len;
	} else {
		j = (i-1)%(len+1);
	}

	ring_t* prev = ring_rotate(self, j);

	// link both rings
	ring_t* temp = prev->next;
	prev->next = nd;
	last->next = temp;

	if (i==0) {
		return nd;
	}
	return self;
}

ring_t* ring_unlink(ring_t* self, int n) {
	int len = ring_len(self);
	if (len <= 1 && n != 0) {
		return self;
	} else if (n == 0) {
		return NULL;
	} else if ((n%len) == 0) {
		return self;
	}
	n = n % len;
	if (n < 0) {
		ring_t* before = ring_rotate(self, n+len-1);
		return ring_unlink(before, -n);
	}
	ring_t* last = ring_rotate(self, n);
	ring_t* first = self->next;
	self->next = last->next;
	last->next = first;
	return first;
}

void ring_free(ring_t* self, bool v) {
	if (self == NULL) {
		return;
	}
	ring_t* nd = self;
	ring_t* nxt = self->next;
	do {
		if (v && nd->value != NULL) {
			free(nd->value);
		}
		free(nd);
		nd = nxt;
		nxt = nxt->next;
	} while (nd != self);
}

#endif
