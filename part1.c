#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

// Menu Part 1 is finished


//  The Struct save the  data of project team,can access by define a array tag like arr[4]
struct Team{
        char tem[40];
        char proj[40];
        char leader[40];
        char mem1[40];
        char mem2[40];
        char mem3[40];
    };



//char* replaceWordInText(const char *text, const char *oldWord, const char *newWord);



   void project_team(struct Team arr[4]){

        char str[100];
        int op =1; // op is a option from user input 1-4
        int count=0;

  
        while (1 ){
            
            if (op == 1){
        
            
            printf("Enter>  ");
            scanf("%99[^\n]",str); //%[^\n]s can input string including space 

            sscanf( str, "%s %s %s %s %s %s",arr[count].tem,arr[count].proj,arr[count].leader,arr[count].mem1,arr[count].mem2,arr[count].mem3); //conver user input string to words and store in struct variable separately

             printf(">>>>>> Project %s  is created.\n",replaceWordInText(arr[count].tem,"_", " "));


               count++; //count for time of looping if user wants to continues
              
            }else if(op == 0){
             menu(); //calling menu function
        
                break;
            }else {
                  printf("Wrong input, please enter again ");
                  scanf("%d",&op);
                  getchar(); //due to the newline character is still in the input buffer on fgets,add getchar() can solve the problem in looping
              
            }

             printf ("Enter 1/0 > " );  
              scanf("%d",&op);
              getchar(); //due to the newline character is still in the input buffer on fgets,add getchar() can solve the problem in looping 
 }


/**  check the input whether save in struct correctly
        for(int i =0; i<5; i++){
            printf("show: %s %s  %s  %s %s %s\n",arr[i].tem,arr[i].proj,arr[i].leader,arr[i].mem1,arr[i].mem2,arr[i].mem3);
        }
**/

  }


/*************************************separate****************************************/

//this function is for change [team_A] without underline  become [team A]when print out on function project_team()
  char* replaceWordInText(const char *text, const char *oldWord, const char *newWord) {
   int i = 0, cnt = 0;
   int len1 = strlen(newWord);
   int len2 = strlen(oldWord);
   for (i = 0; text[i] != '\0'; i++) {
      if (strstr(&text[i], oldWord) == &text[i]) {
         cnt++;
         i += len2 - 1;
      }
   }
   char *newString = (char *)malloc(i + cnt * (len1 - len2) + 1);
   i = 0;
   while (*text) {
      if (strstr(text, oldWord) == text) {
         strcpy(&newString[i], newWord);
         i += len1;
         text += len2;
      }
      else
      newString[i++] = *text++;
   }
   return newString;
}



//for testing only
int main(int argc, char *argv[]){
 
 struct Team arr[4]; //must add to access the data in struct
  project_team(arr); 

}