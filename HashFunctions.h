#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

#include <stdlib.h>

long djb2(void* key){
	int i;
	long result = 5381;
	char* str = (char*) key;
	for(i=0; str[i]; i++){
		result += (result << 5) + str[i];
	}
	return result;
}

long fnv1a(void* key){
	static const long PRIME = 1099511628211l;
	static const long OFFSET = 14695981039346656037ul;
	int i;
	long result = OFFSET;
	char* str = (char*) key;
	for(i=0; str[i]; i++){
		result ^= str[i];
		result *= PRIME;
	}
	return result;
}

#endif
