#define _GNU_SOURCE /* for tm_gmtoff and tm_zone */

#include <stdio.h>
#include <time.h>

/* Checking errors returned by system calls was omitted for the sake of readability. */
int main()
{
  time_t t = time(NULL);
  printf("%ld\n", t);
  struct tm lt = {0};

  localtime_r(&t, &lt);

  t -= lt.tm_gmtoff;
  printf("%ld\n", t);
  


  return 0;
}