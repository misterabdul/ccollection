#include <stdlib.h>

#include <coop_list.h>
#include <private/singlylinkedlist.h>

typedef struct _listPrivateData
{
  unsigned int itemCount;
  SinglyLinkedList linkedList;
} * ListPrivateData;

char*
List__innerToString(void* object)
{
  return "List";
}

List
List__new()
{
  Object object = Object__new();
  object->toString = &List__innerToString;

  List newList = realloc(object, sizeof(struct _list));

  ListPrivateData privateData = malloc(sizeof(struct _listPrivateData));
  privateData->itemCount = 0;
  privateData->linkedList = NULL;
  newList->privateData = privateData;

  return newList;
}

unsigned int List__count(List this)
{
  if (!this)
    return 0;
  return ((ListPrivateData)(this->privateData))->itemCount;
}

void
List__push(List this, void* object)
{
  if (!this)
    return;
  ListPrivateData privateData = this->privateData;
  SinglyLinkedList linkedList = privateData->linkedList;
  SinglyLinkedList__push(&linkedList, object);

  privateData->linkedList = linkedList;
  privateData->itemCount++;
}

void* List__pop(List this)
{
  if (!this)
    return NULL;
  ListPrivateData privateData = this->privateData;
  SinglyLinkedList linkedList = privateData->linkedList;
  void* poppedObject = SinglyLinkedList__pop(&linkedList);

  privateData->linkedList = linkedList;
  privateData->itemCount--;

  return poppedObject;
}

void*
List__get(List this, unsigned int pos)
{
  if (!this)
    return NULL;
  ListPrivateData privateData = this->privateData;
  if (pos > privateData->itemCount)
    return NULL;
  SinglyLinkedList linkedList = privateData->linkedList;

  return SinglyLinkedList__get(linkedList, pos)->data;
}

void
List__toArray(List this, void* _array)
{
  if (!this)
    return;
  void** array = _array;
  for (unsigned int i = 0; i < List__count(this); i++)
    *(array + i) = List__get(this, i);
}

void
List__delete(List* this, void (*itemDeleteFunc)(void*))
{
  if (!*this)
    return;
  ListPrivateData privateData = (*this)->privateData;
  SinglyLinkedList linkedList = privateData->linkedList;
  SinglyLinkedList__delete(&linkedList, itemDeleteFunc);
  privateData->linkedList = NULL;
  privateData->itemCount = 0;

  if (privateData)
    free(privateData);
  (*this)->privateData = NULL;

  Object__delete(this);
}
