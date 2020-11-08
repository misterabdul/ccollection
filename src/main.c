#include <stdio.h>

#include <coop_list.h>
#include <coop_object.h>
#include <coop_string.h>

int
main(int argc, char* argv[])
{
  List list = List__new();
  printf("LinkedList<String> list = new LinkedList<>();\n\n");

  char* str[] = { "Lorem", "Ipsum", "Dolor", "Sit", "Amet" };
  for (int i = 0; i < 5; i++) {
    String s = String__new(str[i], sizeof(str[i]));
    List__push(list, s);

    printf("list.push(\"%s\");\n", Object__toString(s));
  }
  printf("\n");

  printf("list.count(); // %u\n", List__count(list));
  for (unsigned int i = 0; i < List__count(list); i++) {
    String s = List__get(list, i);
    printf("list.get(%u); // \"%s\"\n", i, Object__toString(s));
  }
  printf("\n");

  String s = List__pop(list);
  printf("String s = list.pop(); // \"%s\"\n\n", Object__toString(s));
  String__delete(&s);

  printf("list.count(); // %u\n", List__count(list));
  for (unsigned int i = 0; i < List__count(list); i++) {
    String s = List__get(list, i);
    printf("list.get(%u); // \"%s\"\n", i, Object__toString(s));
  }
  printf("\n");

  unsigned int listCount = List__count(list);
  String arr_s[listCount];
  printf("String[] arr_s = new String[list.count()];\n");

  List__toArray(list, &arr_s);
  printf("list.toArray(arr_s);\n");

  for (unsigned int i = 0; i < listCount; i++) {
    printf("arr_s[%u]; // %s\n", i, Object__toString(arr_s[i]));
  }
  printf("\n");

  List__delete(&list, NULL);

  for (unsigned int i = 0; i < listCount; i++) {
    printf("arr_s[%u]; // %s\n", i, Object__toString(arr_s[i]));
  }
  printf("\n");

  for (unsigned int i = 0; i < listCount; i++) {
    String s = arr_s[i];
    String__delete(&s);
    arr_s[i] = NULL;
  }

  return 0;
}
