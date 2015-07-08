#ifndef _PAIRKV_H_
#define _PAIRKV_H_

typedef struct PairKV PairKV;
struct PairKV {
	long key;
	void* value;
};

PairKV* PairKV_new(long key, void* value){
	PairKV* self = (PairKV*)malloc(sizeof(PairKV));
	self->key = key;
	self->value = value;
	return self;
}

#endif
