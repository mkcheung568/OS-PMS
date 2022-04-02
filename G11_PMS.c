#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>



void menu();



int main(int argc, char *argv[]){


   menu();

  return 0;
  }





//print menu
  void menu(){

  printf("\n ~~  WELCOME TO PolyStar ~~  \n\n");

  printf("1. Create Project Team \n\n");
  printf("2. Project Meeting Request\n");
  printf("   2a.  Single input\n");
  printf("   2b.  Batch input\n\n");
 // printf("   2c. Meeting Attendance\n\n");
  printf("3. Print Meeting Schedule\n");
  printf("   3a.  FCFS (First Come First Served)\n");
  printf("   3b.  SJF (Shortest Jobs First)\n\n");
//  printf("   3c.   YYYY(Attendance Report)\n\n");
  printf("4. Exit\n\n");
  printf("  Enter an option: \n\n");


  }