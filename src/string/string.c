#include "string.h"

char tolower(char s1)
{
  if (s1 >= 65 && s1 <= 90)
  {
    s1 += 32;
  }

  return s1;
}

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

int strncmp(const char *str1, const char *str2, int n)
{
  unsigned char u1, u2;

  while (n-- > 0)
  {
    u1 = (unsigned char)*str1++;
    u2 = (unsigned char)*str2++;
    if (u1 != u2)
    {
      return u1 - u2;
    }
    if (u1 == '\0')
      return 0;
  }
  return 0;
}

int istrncmp(const char *s1, const char *s2, int n)
{
  unsigned char u1, u2;
  while (n-- > 0)
  {
    u1 = (unsigned char)*s1++;
    u2 = (unsigned char)*s2++;
    if (u1 != u2 && tolower(u1) != tolower(u2))
      return u1 - u2;
    if (u1 == '\0')
      return 0;
  }
  return 0;
}

int strnlen_terminator(const char *str, int max, char terminator)
{
  int i = 0;
  for (i = 0; i < max; i++)
  {
    if (str[i] == '\0' || str[i] == terminator)
      break;
  }
  return i;
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