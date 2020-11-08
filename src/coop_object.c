#include <stdlib.h>
#include <string.h>

#include <coop_object.h>

typedef struct _objectPrivateData
{
  char name[32];
} * ObjectPrivateData;

char*
Object__innerToString(void* this)
{
  return ((ObjectPrivateData)((Object)this)->privateData)->name;
}

Object
Object__new()
{
  Object newObject = malloc(sizeof(struct _object));
  ObjectPrivateData privateData = malloc(sizeof(struct _objectPrivateData));
  strcpy(privateData->name, "Object");
  newObject->privateData = privateData;
  newObject->toString = &Object__innerToString;

  return newObject;
}

char* Object__getName(Object this)
{
  return ((ObjectPrivateData)(this->privateData))->name;
}

char*
Object__toString(void* this)
{
  return ((Object)this)->toString(this);
}

void
Object__delete(void* _this)
{
  Object* this = _this;
  free((*this)->privateData);
  (*this)->privateData = NULL;
  free(*this);
  *this = NULL;
}
