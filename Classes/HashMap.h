
#ifndef HASHMAP
#define HASHMAP

typedef struct {
	int   key;
	void* value;
} HashMapEntry;

typedef struct {
	HashMapEntry* entries;
	int           length;
} HashMap;

HashMap newHashMap(int n);
int   insertEntry(HashMap* hashMap, const int key, void* element);
void* lookupEntry(HashMap* hashMap, const int key);
int   removeEntry(HashMap* hashMap, const int key);

void  deallocHashMap(HashMap* map);

// Debug stuff.
float calculateLoad(HashMap* hashMap);

unsigned int hash1(const unsigned int p, const unsigned int x) __attribute__ ((const));
unsigned int hash2(const unsigned int p, const unsigned int x) __attribute__ ((const));
unsigned int hash3(const unsigned int p, const unsigned int x) __attribute__ ((const));

#endif