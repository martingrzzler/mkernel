#include "string.h"

int strlen(const char *ptr)
{
  int len = 0;
  while (*ptr != 0)
  {
    len++;
    ptr += 1;
  }
  return len;
}

char *strcpy(char *dest, const char *src)
{
  char *res = dest;
  while (*src != 0)
  {
    *dest = *src;
    src += 1;
    dest += 1;
  }
  *dest = 0x00;

  return res;
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