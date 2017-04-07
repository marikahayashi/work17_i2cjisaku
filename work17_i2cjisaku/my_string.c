#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "my_string.h"


char *my_strcat(char *pStr1, char *pStr2) {
  while(*pStr1!='\0') {
    pStr1++;
  }
  while(*pStr2 != '\0') {
    *pStr1++ = *pStr2++;
  }
  *pStr1 = *pStr2; //'\0'
  return pStr1;
}

/*
int my_sprintf(char *psStr, const char *psFormat, ...) {
  va_list tagArgs;
  int anArgs[MY_STRING_MAX];
  int i, j, k = 0;
  int nValistlen = 0;
  char sTempbuf[MY_STRING_MAX];
  int nTemplen = 0;
  for(i=1;psFormat[i]!='\0';i++) {
    if(psFormat[i-1] == '%' && psFormat[i] == 'd') {
      nValistlen++;
    }
  }
  va_start(tagArgs, psFormat);
  for(i=0; i<nValistlen; i++) {
    anArgs[i] = va_arg(tagArgs, int);
  }
  va_end(tagArgs);
  j=0;
  k=0;
  *psStr++ = psFormat[0];
  *psStr = '\0';
  for(i=1;psFormat[i]!='\0';i++) {
    if(psFormat[i-1] == '%' && psFormat[i] == 'd') {
      my_itoa(anArgs[j], sTempbuf, 10);
      nTemplen=0;
      while(sTempbuf[nTemplen++]!='\0');
      for(k=0;k<nTemplen;k++){
	*(psStr-1) = sTempbuf[k];
	psStr++;
      }
      psStr--;
      psStr--;
      j++;
    } else if(psFormat[i-1] == '%' && psFormat[i] != 'd') {
      *psStr++ = psFormat[i-1];
      *psStr++ = psFormat[i];
    } else {
      *psStr = psFormat[i];
      psStr++;
    }
  }
  *psStr ='\0';
}
*/

void my_itoa(int val, char *a, int radix) {
  char *p = a;
  unsigned int v = val;
  int n = 1;
  while(v >= radix) {
    v /= radix;
    n++;
  }
  p = a + n;
  v = val;
  *p = '\0';
  do {
    --p;
    *p = v % radix + '0';
    if (*p > '9') {
      *p = v % radix -10 + 'A';
    }
    v /= radix;
  } while ( p != a);	
}
