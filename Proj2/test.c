#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **get_me_some_strings() {
  char *ary[] = { "ABC", "BCD", NULL };
  char **strings = ary; // a pointer to a pointer, for easy iteration
  char **to_be_returned = malloc(sizeof(char*) * 3);
  int i = 0;
  while(*strings) {
    to_be_returned[i] = malloc( sizeof(char) * strlen( *strings ) );
    strcpy( to_be_returned[i++], *strings);
    strings++;
  }
  return to_be_returned;
}

void main() {
  /*char **strings = get_me_some_strings();
  while(*strings) {
    printf("a fine string that says: %s\n", *strings);
    strings++;
  }*/

   /* strcat example */

  char str[80];
  strcpy (str,"these ");
  strcat (str,"strings ");
  strcat (str,"are ");
  strcat (str,"concatenated.");
  puts (str);
  
}
