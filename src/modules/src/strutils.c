#include "strutils.h"

#define LOG_TAG "StrUtils"
#include "logger.h"

/***********************************
* Internal variables declaration   *
************************************/


/**********************************
*  Function definitions           *
***********************************/
void to_upcase(char* str)
{
  while (*str)
  {
    if (*str >='a' && *str <= 'z') *str += 'A'-'a';
    str++;
  }
}
