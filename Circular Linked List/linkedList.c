#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
* Allocates the list's sentinel and sets the size to 0.
* The sentinels' next and prev should point to eachother or NULL
* as appropriate.
*/
static void init(struct LinkedList* list) {
	//create memory for the front and back link
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);

	list->frontSentinel->next = list->backSentinel; //set FS next to BS
	list->frontSentinel->prev = 0;					//set FS prev to 0
	list->backSentinel->prev = list->frontSentinel;	//set BS prev to FS
	list->backSentinel->next = 0;					//set BS next to 0
	list->size = 0;					
}

/**
* Adds a new link with the given value before the given link and
* increments the list's size.
*/
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	struct Link* newLink = malloc(sizeof(struct Link)); //allocate memory for new link
	assert(newLink != 0);

	link->prev->next = newLink; //set the link before the value passed in to the newLink
	newLink->prev = link->prev; //adjust newLinks prev pointer 
	newLink->next = link;		
	newLink->prev->next = newLink;
	link->prev = newLink;

	newLink->value = value; //set value to that passed in

	list->size++; //increment the size of the structure
}

/**
* Removes the given link from the list and
* decrements the list's size.
*/
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(! linkedListIsEmpty(list)); //make sure list is not empty

	//adjust pointers so the go around the link and we can free it
	link->prev->next = link->next; 
	link->next->prev = link->prev;

	list->size--;
	free(link);
}

/**
* Allocates and initializes a list.
*/
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
* Deallocates every link in the list including the sentinels,
* and frees the list itself.
*/
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
* Adds a new link with the given value to the front of the deque.
*/
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	//add the link using the addLinkBefore function and using the
	//front sentinel to place it in the front
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
* Adds a new link with the given value to the back of the deque.
*/
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	//add the link in the back using the back sentinel to find 
	//the back of the list
	addLinkBefore(list, list->backSentinel->prev, value);

}

/**
* Returns the value of the link at the front of the deque.
*/
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list->size != 0); //make sure list is not empty
	return (list->frontSentinel->next->value);
}

/**
* Returns the value of the link at the back of the deque.
*/
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list->size != 0); //make sure list is not empty
	return (list->backSentinel->prev->value);
}

/**
* Removes the link at the front of the deque.
*/
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list->size != 0);
	linkedListRemove(list, list->frontSentinel->next->value);
}

/**
* Removes the link at the back of the deque.
*/
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list->size != 0);
	linkedListRemove(list, list->backSentinel->prev->value);
}

/**
* Returns 1 if the deque is empty and 0 otherwise.
*/
int linkedListIsEmpty(struct LinkedList* list)
{
	if (list->size > 0)
		return 0; //0 for false that list is NOT empty
	else
		return 1; //1 for True that list is empty
}

/**
* Prints the values of the links in the deque from front to back.
*/
void linkedListPrint(struct LinkedList* list)
{
	//create a temp variable to traverse list. State at the
	//first element
	struct Link *temp = list->frontSentinel->next;

	while (temp != list->backSentinel) {
		printf("%p  %d", temp, temp->value);
		temp = temp->next;
	}
	printf("\n"); //for spacing
}

/**
* Adds a link with the given value to the bag.
*/
void linkedListAdd(struct LinkedList* list, TYPE value)
{

	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
* Returns 1 if a link with the value is in the bag and 0 otherwise.
*/
int linkedListContains(struct LinkedList* list, TYPE value)
{
	struct Link *temp = list->frontSentinel->next;

	while (temp != list->backSentinel) {
		if (temp->value == value)
			return 1;//item found
		
		temp = temp->next; //move down the bag
	}
	return 0;//item not found
}

/**
* Removes the first occurrence of a link with the given value.
*/
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list->size != 0);

	struct Link *temp = list->frontSentinel->next;

	while (temp != list->backSentinel) {
		if (temp->value == value) {
			removeLink(list, temp); //value found so remove it
		}
		temp = temp->next;// move down the list
	}
}
