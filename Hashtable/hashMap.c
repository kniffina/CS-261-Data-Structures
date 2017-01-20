/*
* CS 261 Data Structures
* Assignment 6
* Name: Adam Kniffin		
* Date: 78/6/2016
* Description: The code below contains the implementation for the hashmap 
* ADT. The functions will be described in more detail as you see them.
*/

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
	int r = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{
		r += key[i];
	}
	return r;
}

int hashFunction2(const char* key)
{
	int r = 0;
	for (int i = 0; key[i] != '\0'; i++)
	{
		r += (i + 1) * key[i];
	}
	return r;
}

/**
* Creates a new hash table link with a copy of the key string.
* @param key Key string to copy in the link.
* @param value Value to set in the link.
* @param next Pointer to set as the link's next.
* @return Hash table link allocated on the heap.
*/
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
	HashLink* link = malloc(sizeof(HashLink));
	link->key = malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(link->key, key);
	link->value = value;
	link->next = next;
	return link;
}

/**
* Free the allocated memory for a hash table link created with hashLinkNew.
* @param link
*/
static void hashLinkDelete(HashLink* link)
{
	free(link->key);
	free(link);
}

/**
* Initializes a hash table map, allocating memory for a link pointer table with
* the given number of buckets.
* @param map
* @param capacity The number of table buckets.
*/
void hashMapInit(HashMap* map, int capacity)
{
	map->capacity = capacity;
	map->size = 0;
	map->table = malloc(sizeof(HashLink*) * capacity);
	for (int i = 0; i < capacity; i++)
	{
		map->table[i] = NULL;
	}
}

/**
* Removes all links in the map and frees all allocated memory. You can use
* hashLinkDelete to free the links.
* @param map
*/
void hashMapCleanUp(HashMap* map)
{
	// FIXME: implement
	struct HashLink *current;
	struct HashLink *previous;

	assert(map != 0);

	int i;

	for (i = 0; i < map->capacity; i++) {
		//loop and get each value
		current = map->table[i];

		//while loop to free each link from memory
		while (current != NULL) {
			//set previous equal to current and then move down the links
			previous = current;
			current = current->next;
			hashLinkDelete(previous);
		}
	}
}

/**
* Creates a hash table map, allocating memory for a link pointer table with
* the given number of buckets.
* @param capacity The number of buckets.
* @return The allocated map.
*/
HashMap* hashMapNew(int capacity)
{
	HashMap* map = malloc(sizeof(HashMap));
	hashMapInit(map, capacity);
	return map;
}

/**
* Removes all links in the map and frees all allocated memory, including the
* map itself.
* @param map
*/
void hashMapDelete(HashMap* map)
{
	hashMapCleanUp(map);
	free(map);
}

/**
* Returns a pointer to the value of the link with the given key. Returns NULL
* if no link with that key is in the table.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @return Link value or NULL if no matching link.
*/
int* hashMapGet(HashMap* map, const char* key)
{
	// FIXME: implement
	int hashIndex;
	struct HashLink *current;
	assert(map != 0);

	//use hash function to get the index
	hashIndex = HASH_FUNCTION(key) % map->capacity;

	if (hashIndex < 0) {
		hashIndex += map->size;
	}
	//set current equal to the value at hashIndex table
	current = map->table[hashIndex];
	while (current) {
		if (strcmp(current->key, key) == 0)
			return &(current->value);
		
		//if not equal move down the line
		current = current->next;
	}
	//return NULL if not found
	return NULL;
}

/**
* Resizes the hash table to have a number of buckets equal to the given
* capacity. After allocating the new table, all of the links need to be
* rehashed into it because the capacity has changed.
*
* Remember to free the old table and any old links if you use hashMapPut to
* rehash them.
*
* @param map
* @param capacity The new number of buckets.
*/
void resizeTable(HashMap* map, int capacity)
{
	// FIXME: implement
	assert(map != 0);
	
	struct HashMap *newCap;
	struct HashLink *current;

	int i;

	assert(capacity > map->capacity);
	newCap = hashMapNew(capacity);
	assert(newCap != 0);

	for (i = 0; i < map->capacity; i++) {
		current = map->table[i];
		
		while (current != NULL) {
			//copy the contents to the new Hash Map
			hashMapPut(newCap, current->key, current->value);
			current = current->next;
		}
	}

	hashMapCleanUp(map->table);
	map->table = newCap->table;
	map->capacity == newCap->capacity;
}



/**
* Updates the given key-value pair in the hash table. If a link with the given
* key already exists, this will just update the value. Otherwise, it will
* create a new link with the given key and value and add it to the table
* bucket's linked list. You can use hashLinkNew to create the link.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @param value
*/
void hashMapPut(HashMap* map, const char* key, int value)
{
	// FIXME: implement
	assert(map != 0);
	int hashIndex;
	struct HashLink *newLink;

	//if else to see if the key value is in the map already
	if (hashMapContainsKey(map, key))
		*hashMapGet(map, key) = value; //change the value
	else {
		//get the hashIndex variable using HASH_FUNCTION
		hashIndex = HASH_FUNCTION(key) % map->capacity;

		//determine the hashIndex / if it needs to increase
		if (hashIndex < 0)
			hashIndex += map->capacity;

		//create space in memory for the HashLink
		newLink = malloc(sizeof(struct HashLink));
		assert(newLink != 0);

		//insert values into the newLink
		newLink->key = key;
		newLink->value = value;
		newLink->next = map->table[hashIndex];
		map->table[hashIndex] = newLink;
		map->size++;

		//check to see if size needs to be doubled
		if (map->size / (double)map->capacity > 8.0)
			resizeTable(map, map->capacity * 2);
	}
}

/**
* Removes and frees the link with the given key from the table. If no such link
* exists, this does nothing. Remember to search the entire linked list at the
* bucket. You can use hashLinkDelete to free the link.
* @param map
* @param key
*/
void hashMapRemove(HashMap* map, const char* key)
{
	// FIXME: implement
	assert(map != 0);
	
	int hashIndex;
	struct HashLink *current = NULL;
	struct HashLink *previous = NULL;

	hashIndex = HASH_FUNCTION(key) % map->capacity;
	if (hashIndex < 0)
		hashIndex += map->capacity;

	current = map->table[hashIndex];

	while (current != NULL && (strcmp(current->key, key) == 0)) {
		previous = current;
		current = current->next;
	}

	if (previous != NULL)
		previous->next = current->next;
	else
		map->table[hashIndex] = current->next;

	//free memory 
	free(current);

}

/**
* Returns 1 if a link with the given key is in the table and 0 otherwise.
*
* Use HASH_FUNCTION(key) and the map's capacity to find the index of the
* correct linked list bucket. Also make sure to search the entire list.
*
* @param map
* @param key
* @return 1 if the key is found, 0 otherwise.
*/
int hashMapContainsKey(HashMap* map, const char* key)
{
	// FIXME: implement
	assert(map != 0);

	if (hashMapGet(map, key) != NULL)
		return 1; //key found
	else
		return 0; //NULL so key not found
}

/**
* Returns the number of links in the table.
* @param map
* @return Number of links in the table.
*/
int hashMapSize(HashMap* map)
{
	// FIXME: implement
	return map->size;
}

/**
* Returns the number of buckets in the table.
* @param map
* @return Number of buckets in the table.
*/
int hashMapCapacity(HashMap* map)
{
	// FIXME: implement
	return map->capacity;
}

/**
* Returns the number of table buckets without any links.
* @param map
* @return Number of empty buckets.
*/
int hashMapEmptyBuckets(HashMap* map)
{
	// FIXME: implement
	assert(map != 0);
	int amountEmpty = 0;
	int i;
	
	//loop through the size of the
	for (i = 0; i < map->capacity; i++)
		if (map->table[i] == NULL)
			amountEmpty++;

	//return the amount of NULL or empty buckets
	return amountEmpty;

}

/**
* Returns the ratio of (number of links) / (number of buckets) in the table.
* Remember that the buckets are linked lists, so this ratio tells you nothing
* about the number of empty buckets. Remember also that the load is a floating
* point number, so don't do integer division.
* @param map
* @return Table load.
*/
float hashMapTableLoad(HashMap* map)
{
	// FIXME: implement
	assert(map != 0);

	return (float)map->size / map->capacity;
}

/**
* Prints all the links in each of the buckets in the table.
* @param map
*/
void hashMapPrint(HashMap* map)
{
	for (int i = 0; i < map->capacity; i++)
	{
		HashLink* link = map->table[i];
		if (link != NULL)
		{
			printf("\nBucket %i ->", i);
			while (link != NULL)
			{
				printf(" (%s, %d) ->", link->key, link->value);
				link = link->next;
			}
		}
	}
	printf("\n");
}