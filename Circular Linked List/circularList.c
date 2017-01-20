#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinel's next and prev should point to the sentinel itself.
*/
static void init(struct CircularList* list)
{
	assert(list != 0);
	list->sentinel = (struct Link*)malloc(sizeof(struct Link));

	assert(list->sentinel != 0); 

	//make sentinel's next and prev point to itself
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0; //set size to 0
}

/**
* Creates a link with the given value and NULL next and prev pointers.
*/
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = (struct Link*)malloc(sizeof(struct Link));
	assert(newLink != 0);

	newLink->value = value;
	newLink->next = NULL;

	newLink->prev = NULL;

	return(newLink);
}

/**
* Adds a new link with the given value after the given link and
* increments the list's size.
*/
void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link *newLink = createLink(value);

	newLink->next = link->next;
	link->next->prev = newLink;
	newLink->prev = link;
	link->next = newLink;
	list->size++;
}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != 0);

	//change pointers appropriately
	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);	
	//clear memory and decrement
	list->size--;
}

/**
* Allocates and initializes a list.
*/
struct CircularList* circularListCreate()
{
	struct CircularList* list = (struct CircularList*)malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
* Deallocates every link in the list and frees the list pointer.
*/
void circularListDestroy(struct CircularList* list)
{
	assert(list != 0);
	int i;
	
	//loop through the list and use the removeLink function
	//to remove each link in the list
	for (i = 0; i < list->size; i++) {
		removeLink(list, list->sentinel->next);
	}
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void circularListAddFront(struct CircularList* list, TYPE value)
{
	//creates new link with given value
	struct Link *newLink = createLink(value);

	//adjust pointers
	newLink->prev = list->sentinel;
	newLink->next = list->sentinel->next;

	list->sentinel->next = newLink;
	newLink->next->prev = newLink;

	list->size++;
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void circularListAddBack(struct CircularList* list, TYPE value)
{
	//create new link with given value
	struct Link *newLink = createLink(value);

	//change pointers appropriately
	newLink->next = list->sentinel;
	newLink->prev = list->sentinel->prev;


	list->sentinel->prev = newLink;
	newLink->prev->next = newLink;

	list->size++;
}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE circularListFront(struct CircularList* list)
{
	assert(list != 0);
	return (list->sentinel->next->value);
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE circularListBack(struct CircularList* list)
{
	assert(list != 0);
	return (list->sentinel->prev->value);
}

/**
* Removes the link at the front of the deque.
*/
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != 0);
	assert(list->size > 0);

	removeLink(list, list->sentinel->next);
}

/**
* Removes the link at the back of the deque.
*/
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != 0);
	assert(list->size > 0);

	removeLink(list, list->sentinel->prev);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != 0);

	if (list->size > 0)
		return 0;    //list is NOT empty, return 0 to indicate
	else 
		return 1;    //list empty, return 1 
}

/**
* Prints the values of the links in the deque from front to back.
*/
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	assert(list->size > 0);

	struct Link *current = list->sentinel->next;
	
	while(current != list->sentinel){
		printf("%g | ", current->value);
		current = current->next;
	}
	printf("\n");
}

/**
* Reverses the deque.
*/
void circularListReverse(struct CircularList* list)
{
	/* FIXME: you must write this */
	struct Link *current;
	struct Link *temp;

	assert(list != NULL);
	assert(list->size != 0);

	current = list->sentinel;

	do {
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;
		current = temp;
	} while (current != list->sentinel);
	
}
