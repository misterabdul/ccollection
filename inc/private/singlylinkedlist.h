#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

/**
 * @brief Single linked-list data type.
 *
 */
typedef struct _singlyLinkedList
{
  struct _singlyLinkedList* next;
  void* data;
} * SinglyLinkedList;

/**
 * @brief Create new instance of single linked-list containing object.
 *
 * @param object The object.
 * @return SinglyLinkedList
 */
SinglyLinkedList
SinglyLinkedList__new(void* object);

/**
 * @brief Push new linked-list item containing object at the end of the current
 * list.
 *
 * @param list The current list.
 * @param object The object.
 */
void
SinglyLinkedList__push(SinglyLinkedList* list, void* object);

/**
 * @brief Pop the last item in the linked-list and returns the popped item
 * instance.
 *
 * @param list The current list.
 * @return void*.
 */
void*
SinglyLinkedList__pop(SinglyLinkedList* list);

/**
 * @brief Count total element in the list.
 *
 * @param list The list.
 * @return unsigned int
 */
unsigned int
SinglyLinkedList__count(SinglyLinkedList list);

/**
 * @brief Get the linked list at selected position.
 *
 * @param list The linked list.
 * @param position The selected position.
 * @return SinglyLinkedList
 */
SinglyLinkedList
SinglyLinkedList__get(SinglyLinkedList list, unsigned position);

/**
 * @brief Swap the linked list.
 *
 * @param beforeFirst The linked list before the first.
 * @param first The first linked list.
 * @param beforeSecond The linked list before the second.
 * @param second The second linked list.
 */
void
SinglyLinkedList__swap(SinglyLinkedList* beforeFirst,
                       SinglyLinkedList* first,
                       SinglyLinkedList* beforeSecond,
                       SinglyLinkedList* second);

/**
 * @brief Sort the linked list naively.
 *
 * @param list The linked list.
 */
void
SinglyLinkedList__naiveSort(SinglyLinkedList* list,
                            int (*comparator)(void*, void*));

void
SinglyLinkedList__mergeSort(SinglyLinkedList* list,
                            int (*comparator)(void*, void*));

/**
 * @brief Free all the memory containing the linked-list instance recursively.
 *
 * @param list The linked-list.
 * @param itemDeleteFunc The function to free the memory for each object in
 * the list.
 */
void
SinglyLinkedList__delete(SinglyLinkedList* list, void (*itemDeleteFunc)(void*));

#endif
