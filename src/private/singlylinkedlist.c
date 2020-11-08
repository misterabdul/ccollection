#include <stdlib.h>

#include <private/singlylinkedlist.h>

SinglyLinkedList
SinglyLinkedList__new(void* object)
{
  SinglyLinkedList newList = malloc(sizeof(struct _singlyLinkedList));
  newList->data = object;
  newList->next = NULL;
  return newList;
}

void
SinglyLinkedList__push(SinglyLinkedList* this, void* object)
{
  if (!*this) {
    SinglyLinkedList newLinkedList = SinglyLinkedList__new(object);
    *this = newLinkedList;
    return;
  }

  SinglyLinkedList next = (*this)->next;
  SinglyLinkedList__push(&next, object);
  (*this)->next = next;
}

void*
SinglyLinkedList__pop(SinglyLinkedList* this)
{
  if (!*this)
    return NULL;

  if (!(*this)->next) {
    void* poppedObject = (*this)->data;
    SinglyLinkedList__delete(this, NULL);
    return poppedObject;
  }

  SinglyLinkedList next = (*this)->next;
  void* poppedObject = SinglyLinkedList__pop(&next);
  (*this)->next = next;
  return poppedObject;
}

SinglyLinkedList
SinglyLinkedList__get(SinglyLinkedList this, unsigned int pos)
{
  for (int i = 0; i < pos; i++)
    if (this->next)
      this = this->next;
    else
      return NULL;
  return this;
}

void
SinglyLinkedList__delete(SinglyLinkedList* this, void (*itemDeleteFunc)(void*))
{
  if (!*this)
    return;
  SinglyLinkedList next = (*this)->next;
  if (next)
    SinglyLinkedList__delete(&next, itemDeleteFunc);
  (*this)->next = NULL;

  void* item = (*this)->data;
  if (itemDeleteFunc && item)
    itemDeleteFunc(&item);
  (*this)->data = NULL;

  if (*this)
    free(*this);
  *this = NULL;
}
