/*
 * Filename   : io.c
 *
 * Created    : 09.05.2016
 *
 * Modified   : jue 23 jun 2016 16:56:03 CEST
 *
 * Author     : jatorre
 *
 * Purpose    : IO functions for correlation.c 
 *
 */
#include "correlation.h"

void PrintMsg(char *msg)
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  char * timestamp = asctime(timeinfo);
  timestamp[strlen(timestamp)-1] = '\0';
  printf("[%s]\t%s\n", timestamp, msg);
}
    
void PrintInitInfo(void) 
{
  printf("##############################################################################\n");
  printf("#                                                                            #\n");
  printf("# CORRELATION                                                                #\n");
  printf("#                                                                            #\n");
  printf("# This program computes (cross)correlation of a given input matrix           #\n");
  printf("#                                                                            #\n");
  printf("##############################################################################\n");
  printf("#                                                                            #\n");
  printf("# The input matrix should be at $1 in matrixform                             #\n");
  printf("#                                                                            #\n");
  printf("##############################################################################\n");
  printf("#                                                                            #\n");
  printf("# Cross correlation will be stored at ./output/                              #\n");
  printf("#                                                                            #\n");
  printf("# Log files (if any) will be stored in ./log/                                #\n");
  printf("#                                                                            #\n");
  printf("##############################################################################\n\n");
}

int CheckInput(int argc)
{
  if (argc != 2)
  {
    PrintMsg("\e[1m\e[31m[ERROR]\e[0m Correlation needs an input basename. Exiting now...");
    return 1; 
  }

  return 0;
}
