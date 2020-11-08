#ifndef STRING_H
#define STRING_H

#include <coop_object.h>

/**
 * @brief String data type.
 *
 */
typedef struct _string
{
  struct _object object;

  void* privateData;
} * String;

/**
 * @brief Create new instance of string.
 *
 * @param value The string value.
 * @param length The length of the value.
 * @return String
 */
String
String__new(char* value, int length);

/**
 * @brief Returns the length of the string.
 *
 * @param string The string.
 * @return int
 */
int
String__length(String string);

/**
 * @brief Returns char at selected index from string.
 *
 * @param string The string.
 * @param index Selected index.
 * @return char
 */
char
String__charAt(String string, int index);

/**
 * @brief Concatenate string with new value.
 *
 * @param string The string.
 * @param value The new value.
 * @param length The length of new value.
 */
void
String__concat(String string, char* value, int length);

/**
 * @brief Free the memory containing instance of string.
 *
 * @param string The string.
 */
void
String__delete(void* string);

#endif
