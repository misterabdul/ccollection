#include <stdlib.h>
#include <string.h>

#include <coop_string.h>

typedef struct _stringPrivateData
{
  char* data;
  int length;
} * StringPrivateData;

char*
String__innerToString(void* this)
{
  return ((StringPrivateData)((String)this)->privateData)->data;
}

String
String__new(char* value, int length)
{
  Object object = Object__new();
  object->toString = &String__innerToString;

  String string = realloc(object, sizeof(struct _string));

  StringPrivateData privateData = malloc(sizeof(struct _stringPrivateData));
  privateData->data = malloc(length * sizeof(char) + 1);
  strncpy(privateData->data, value, length);
  privateData->length = length;
  string->privateData = privateData;

  return string;
}

int String__length(String this)
{
  if (!this)
    return 0;
  return ((StringPrivateData)(this->privateData))->length;
}

char
String__charAt(String this, int index)
{
  if (!this)
    return 0;
  int length = ((StringPrivateData)(this->privateData))->length;
  if (index < 0 || index >= length)
    return 0;
  return ((StringPrivateData)(this->privateData))->data[index];
}

void
String__concat(String this, char* value, int length)
{
  if (!this)
    return;
  StringPrivateData privateData = this->privateData;
  char* newData = realloc(privateData->data,
                          (privateData->length + length) * sizeof(char) + 1);
  strncat(newData, value, length);
  privateData->data = newData;
  privateData->length += length - 1;
}

int
String__compare(String this, String other)
{
  StringPrivateData privateData = this->privateData;
  StringPrivateData otherPrivateData = other->privateData;
  return strcmp(privateData->data, otherPrivateData->data);
}

void
String__delete(void* _this)
{
  String* this = _this;
  StringPrivateData privateData = (*this)->privateData;
  if (privateData->data)
    free(privateData->data);
  privateData->data = NULL;
  if (privateData)
    free(privateData);
  (*this)->privateData = NULL;

  Object__delete(this);
}
