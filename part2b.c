#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include<ctype.h>


struct Meeting{
        char team[40];
        char date[40];
        char time[40];
        char duration[40];
        
    };

    void batch_input(struct Meeting marr[100]);



    int main(int argc, char *argv[]){ //for testing only
 
 
  
          struct Meeting marr[100];
  

         batch_input(marr);

  
    
 for(int i =0; i<10; i++){
            printf("showmain2b: %s %s  %s  %s\n",marr[i].team,marr[i].date,marr[i].time,marr[i].duration);
        }

}



void batch_input(struct Meeting marr[100]){//define a team array of 100 records

 #define LSIZE 130 
 #define RSIZE 10

  char line[RSIZE][LSIZE];
	char fname[20];
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;//count the number of line
    int crow =0; //count for which row is empty 
    int count=0;
    

/**
 for(int row=0; row<100; row++){ // find the marr row until the row is empty

     if(strlen(marr[row].team) !=0){
       crow++;
     }else{
  
         break;  
  
    }
 }
 count =crow;
**/
 
	printf("Input the filename to be opened : ");
	scanf("%s",fname);	

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZE, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0'; //count each line of the file and write it to line array
        i++;
    }
      fclose(fptr);

    tot = i;//The number of row from import file 


  
    for(i = 0; i < tot; ++i)
    {
      sscanf( line[i], "%s %s %s %s ",marr[count].team,marr[count].date,marr[count].time,marr[count].duration); //put the line string array into struct  
        count++;


    }
    for(int j=tot;j<100;j++){// set the rest of the array to empty 
    
      strcpy(marr[j].team , "\0");
      strcpy(marr[j].date , "\0");
      strcpy(marr[j].time , "\0");
      strcpy(marr[j].duration ,"\0");


    }
   printf("\nMeeting request has been imported!\n\n");
   
/**for testing only **/
 for(int i =0; i<7; i++){
            printf("show: %s %s  %s  %s\n",marr[i].team,marr[i].date,marr[i].time,marr[i].duration);
        }




}