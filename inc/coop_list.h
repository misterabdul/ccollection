#ifndef LIST_H
#define LIST_H

#include <coop_object.h>

/**
 * @brief List data type.
 *
 */
typedef struct _list
{
  struct _object object;

  void* privateData;
} * List;

/**
 * @brief Create new instance of list.
 *
 * @return List
 */
List
List__new();

/**
 * @brief Returns the total item count in the list.
 *
 * @param list The list.
 * @return unsigned int
 */
unsigned int
List__count(List list);

/**
 * @brief Push new object at the end of the list.
 *
 * @param list The list.
 * @param object The object.
 */
void
List__push(List list, void* object);

/**
 * @brief Pop the last object from the end of the list and returns the popped
 * object instance.
 *
 * @param list The list.
 * @return void*
 */
void*
List__pop(List list);

/**
 * @brief Returns the item at selected position from the list;
 *
 * @param list The list.
 * @param position Selected position.
 * @return void*
 */
void*
List__get(List list, unsigned int position);

/**
 * @brief Fill array with initialized size with each list item in order.
 * 
 * @param list The list.
 * @param array The array.
 */
void
List__toArray(List list, void* array);

/**
 * @brief Free the memory containing instance of list.
 *
 * @param list The list.
 * @param itemDeleteFunc The function to free the memory for each item in the
 * list.
 */
void
List__delete(List* list, void (*itemDeleteFunc)(void*));

#endif
