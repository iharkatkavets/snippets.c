#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

const char ACCESS_ERROR = 1;

typedef struct HashTable HashTable;
typedef struct Bucket Bucket;

struct Bucket {
	char key;
	int value;
	Bucket *next;
};

struct HashTable {
	size_t size;	
	size_t count;
	Bucket **buckets;
};

HashTable *makeHashTable(size_t size) {
	HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
	hashTable->size = size;
	hashTable->count = 0;
	hashTable->buckets = (Bucket **)calloc(128, sizeof(Bucket *));
	return hashTable;
}

size_t indexForKey(char key, size_t hashTableSize) {
	size_t index = key % hashTableSize;
	return index;
}

void putValue(HashTable *hashTable, int value, char key) {
	size_t index = indexForKey(key, hashTable->size);
	Bucket *bucket = hashTable->buckets[index];
	if (bucket == NULL) {
		bucket = (Bucket *)malloc(sizeof(Bucket));
		bucket->key = key;
		bucket->value = value;
		bucket->next = NULL;
	}
	else if (bucket->key != key) {
		Bucket *nextBucket = (Bucket *)malloc(sizeof(Bucket *));
		nextBucket->key = key;
		nextBucket->value = value;
		nextBucket->next = NULL;
		bucket->next = nextBucket;
	}
	else {
		bucket->value = value;
	}
	hashTable->buckets[index] = bucket;
}

bool hasValue(HashTable *hashTable, char key) {
	size_t index = indexForKey(key, hashTable->size);
	Bucket *bucket = hashTable->buckets[index];
	return bucket != NULL;
}

int getValue(HashTable *hashTable, char key) {
	size_t index = indexForKey(key, hashTable->size);
	Bucket *bucket = hashTable->buckets[index];
	while(bucket) {
		if (bucket->key == key) {
			return bucket->value;
		}
		bucket = bucket->next;
	}
	exit(ACCESS_ERROR);
}

int getValueOrDefault(HashTable *hashTable, char key, int defaultValue) {
	size_t index = indexForKey(key, hashTable->size);
	Bucket *bucket = hashTable->buckets[index];
	while(bucket) {
		if (bucket->key == key) {
			return bucket->value;
		}
		bucket = bucket->next;
	}
	return defaultValue;
}
