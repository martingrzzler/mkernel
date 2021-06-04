#include "string.h"

int strlen(const char *ptr)
{
  int len = 0;
  while (*ptr != 0)
  {
    len++;
  }
  return len;
}

int tonumericdigit(char c)
{
  return c - 48;
}

bool isdigit(char c)
{
  return c >= 48 && c <= 57;
}

int strnlen(const char *ptr, int max)
{
  int len = 0;
  for (len = 0; len < max; len++)
  {
    if (ptr[len] == 0)
      break;
  }

  return len;
}