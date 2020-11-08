#ifndef OBJECT_H
#define OBJECT_H

/**
 * @brief Object data type.
 *
 */
typedef struct _object
{
  void* privateData;

  char* (*toString)(void*);
} * Object;

/**
 * @brief Create new instance of object.
 *
 * @return Object
 */
Object
Object__new();

/**
 * @brief Get the name of the object.
 *
 * @param object The object.
 * @return char*
 */
char*
Object__getName(Object object);

/**
 * @brief Returns the string value of the object.
 *
 * @param object The object.
 * @return char*
 */
char*
Object__toString(void* object);

/**
 * @brief Free the memory containing instance of object.
 *
 * @param object
 */
void
Object__delete(void* object);

#endif
