/*
  PLOVER: BUFF.OVER, RACE
*/

/*
  Unprotected string copy, unlocked shared resource
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 5

void *foo(void* targ)
{

  char *buffer = ((char **)targ)[0];
  char *str =  ((char **)targ)[1];
  char *str2 =  ((char **)targ)[2];

  if(strlen(str) < BUFSIZE)
    strcpy(buffer, str);
  else
    pthread_exit(NULL);
  strncat(buffer, str2, BUFSIZE);
  printf("results: %s\n", buffer);
  
  pthread_exit(NULL);
}

void *bar(void* targ)
{
  char **buffer = (char **)targ;
  
  *buffer = NULL;

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  char buf[BUFSIZE];
  pthread_t tids[3];
  char *tin[3];
  tin[0] = buf;
  if(argc > 2){
    tin[1] = argv[1];
    tin[2] = argv[2];
  }
  else
    return 0;

  int rc = pthread_create(&tids[0], NULL, foo, (void *)tin);
  rc = pthread_create(&tids[1], NULL, bar, (void *)&buf);
  rc = pthread_create(&tids[2], NULL, bar, (void *)&buf);
  pthread_join(tids[0],NULL);
  pthread_join(tids[1],NULL);
  pthread_join(tids[2],NULL);

  printf("final string: %s \n", buf);

  return 0;
}
