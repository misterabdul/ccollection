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

unsigned int SinglyLinkedList__count(SinglyLinkedList this)
{
  if (!this)
    return 0;
  unsigned int count = 0;
  while (this) {
    count++;
    this = this->next;
  }
  return count;
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
SinglyLinkedList__swap(SinglyLinkedList* beforeThis,
                       SinglyLinkedList* this,
                       SinglyLinkedList* beforeThat,
                       SinglyLinkedList* that)
{
  SinglyLinkedList temp;
  if (*beforeThis) {
    temp = (*beforeThis)->next;
    (*beforeThis)->next = (*beforeThat)->next;
    (*beforeThat)->next = temp;

    *this = (*beforeThis)->next;
    *that = (*beforeThat)->next;
  } else {
    (*beforeThat)->next = *this;
    *this = *that;
    *that = (*beforeThat)->next;
  }

  temp = (*this)->next;
  (*this)->next = (*that)->next;
  (*that)->next = temp;
}

void
SinglyLinkedList__naiveSort(SinglyLinkedList* this,
                            int (*comparator)(void*, void*))
{
  SinglyLinkedList curr = *this;
  SinglyLinkedList preCurr = NULL;

  if (!curr->next)
    return;
  SinglyLinkedList walker = curr->next;
  SinglyLinkedList preWalker = curr;

  while (curr && curr->next) {
    while (walker) {
      if (comparator(curr->data, walker->data) > 0) {
        SinglyLinkedList__swap(&preCurr, &curr, &preWalker, &walker);
      }
      preWalker = walker;
      walker = walker->next;
    }
    if (preCurr == NULL) {
      *this = curr;
    }
    preCurr = curr;
    curr = curr->next;
    preWalker = curr;
    walker = curr->next;
  }
}

void
splitMiddle(SinglyLinkedList this, SinglyLinkedList* middle)
{
  SinglyLinkedList _middle = this;
  while (this) {
    this = this->next;
    if (this) {
      this = this->next;
      if (this)
        _middle = _middle->next;
    }
  }
  *middle = _middle->next;
  _middle->next = NULL;
}

void
SinglyLinkedList__mergeSort(SinglyLinkedList* this,
                            int (*comparator)(void*, void*))
{
  if (!*this || !(*this)->next)
    return;

  SinglyLinkedList start = *this;
  SinglyLinkedList middle = start;
  splitMiddle(start, &middle);

  SinglyLinkedList__mergeSort(&start, comparator);
  SinglyLinkedList__mergeSort(&middle, comparator);

  SinglyLinkedList result = NULL;
  SinglyLinkedList walkerResult = NULL;
  while (start && middle) {
    SinglyLinkedList temp = NULL;

    if (comparator(start->data, middle->data) > 0) {
      temp = middle;
      middle = middle->next;
    } else {
      temp = start;
      start = start->next;
    }

    if (result) {
      walkerResult->next = temp;
      walkerResult = walkerResult->next;
    } else {
      result = temp;
      walkerResult = result;
    }

    if (!start && middle) {
      walkerResult->next = middle;
      middle = NULL;
    }
    if (!middle && start) {
      walkerResult->next = start;
      start = NULL;
    }
  }

  *this = result;
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
