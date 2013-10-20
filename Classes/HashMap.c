
#include "HashMap.h"

#include <stdlib.h>
#include <stdio.h>

int nextHash(const int n, const int key, const int h) __attribute__ ((const));
int insertHelp(HashMap* map, int pos, const int key, void* value);

HashMap newHashMap(int n) 
{	
	return (HashMap){calloc(n, sizeof(HashMapEntry)), n};
}

void deallocHashMap(HashMap* map) {
	free(map->entries);
	map->entries = NULL;
}

int resizeMap(HashMap* map) 
{
	if (map->length > 32000)
		return -1;
	else
		printf("Resized HashMap of size %i to %i", map->length, map->length * 2);
	
	HashMapEntry* entries = map->entries;
	unsigned int  length  = map->length;
	map->entries          = calloc(length * 2, sizeof(HashMapEntry));
	map->length           = length * 2;
	
	for (int i = 0; i < length; i++) {
		if (entries[i].key != 0)
			insertEntry(map, entries[i].key, entries[i].value);
	}
	return 1;
}

int insertEntry(HashMap* map, const int key, void* value)
{
	const int n = map->length; 
	
	int a = hash1(n, key);
	if (map->entries[a].key == key) {
		map->entries[a].value = value;
		return 0;
	}
	int b = hash2(n, key);
	if (map->entries[b].key == key) {
		map->entries[b].value = value;
		return 0;
	}
	b = hash3(n, key);
	if (map->entries[b].key == key) {
		map->entries[b].value = value;
		return 0;
	}
	
	HashMapEntry  entry = {key, value};
	HashMapEntry  temp;
	unsigned int (*hashFunc)(const unsigned int, const unsigned int) = &hash1;
	
	for (int j = 0; j < 3; j++) {
		if (j % 3 == 0)
			hashFunc = &hash1;
		else if (j % 3 == 1)
			hashFunc = &hash2;
		else if (j % 3 == 2)
			hashFunc = &hash3;
		
		for (int i = 0; i < 17; i++) {
			if (map->entries[a].key == 0) {
				map->entries[a] = entry;
				return 1;
			} else {
				temp            = map->entries[a];
				map->entries[a] = entry;
				entry           = temp;
				a               = (*hashFunc)(n, entry.key);
			}
		}
	}
	if (resizeMap(map) == 1)
		return insertEntry(map, entry.key, entry.value);
	else
		return -1;
}

int removeEntry(HashMap* map, const int key) {
	int a = hash1(map->length, key);
	if (map->entries[a].key == key) {
		map->entries[a].key = 0;
		return 1;
	}
	a = hash2(map->length, key);
	if (map->entries[a].key == key) {
		map->entries[a].key = 0;
		return 1;
	}
	
	a = hash3(map->length, key);
	if (map->entries[a].key == key) {
		map->entries[a].key = 0;
		return 1;
	}
	return -1;
}

void* lookupEntry(HashMap* map, const int key) 
{
	int a = hash1(map->length, key);
	if (map->entries[a].key == key)
		return map->entries[a].value;
	
	a = hash2(map->length, key);
	if (map->entries[a].key == key)
		return map->entries[a].value;
	
	a = hash3(map->length, key);
	if (map->entries[a].key == key)
		return map->entries[a].value;
	
	return NULL;
}

float calculateLoad(HashMap* map)
{
	float n = 0;
	
	for (int i = 0; i < map->length; i++) {
		if (map->entries[i].key != 0)
			n++;
	}
	
	return (n / map->length);
}

unsigned int hash1(const unsigned int p, const unsigned int x)
{
	const unsigned int y = abs(x);
	return (1 + ((58193 + 1258207*y + 2808193*y*y) % 308383) % p);
}

unsigned int hash2(const unsigned int p, const unsigned int x)
{
	const unsigned int y = abs(x);
	return (1 + ((711929 + 1810057*y + 9767*y*y) % 608459) % p);
}

unsigned int hash3(const unsigned int p, const unsigned int x)
{
	const unsigned int y = abs(x);
	return (1 + ((459257 + 808481*y + 2958259*y*y) % 1358333) % p);
}


