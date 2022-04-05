#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include<ctype.h>



//  The Struct save the  data of meeting request,can access by define a array tag like arr[5]
struct Meeting{
        char team[40];
        char date[40];
        char time[40];
        char duration[40];
        
    };



    void single_input(struct Meeting marr[100]);

//for testing the function
int main(int argc, char *argv[]){
 
  struct Meeting marr[100];
 
   single_input(marr);

}




void single_input(struct Meeting marr[100]){

        char str[100];
        int op =21; // op is a option from user input 1-4
        int count=0;
  
       
  
     while (1){ // "op == 21 || op != 21" is same as true, as it cannot be false, i.e. op = 10 then right is true, op = 21 then left is false
            
          if (op == 21 ){
        
            do{ //this while loop for range checking to make sure user input duration should between 1-9
            printf("Enter>  ");
            scanf("%[^\n]s",str); //%[^\n]s can input string including space 
            getchar(); 
            sscanf( str, "%s %s %s %s ",marr[count].team,marr[count].date,marr[count].time,marr[count].duration); //conver user input string to words and store in struct variable separately

            if(atoi(marr[count].duration) <=0 || atoi(marr[count].duration) >=10 ){ //atoi is convert string to integer

              printf("The duration should from 1 to 9,Please enter again\n");
              continue; //back to the beginning of the looping
            }else{
              break;
            }
            
            }while(1);
     
             printf("Meeting is being added for %s in %s at %s for %s hours.  \n\n",replaceWordInText(marr[count].team,"_", " "),marr[count].date,marr[count].time,marr[count].duration);
            
              count++; //count for time of looping if user wants to continues

         
            }else if(op == 0){
               menu(); //calling menu function
                break;
            }else{  
               
                  printf("Wrong input, please enter again!\n");
                 
                }

              printf ("Do you want to add again ? Enter 21 to continue or 0 back to main menu: " );  
            
              scanf("%d",&op);
              getchar(); //due to the newline character is still in the input buffer on fgets,add getchar() can solve the problem in looping
      }  
 
/**  check the input whether save in struct correctly 
        for(int i =0; i<5; i++){
            printf("show: %s %s  %s  %s\n",marr[i].team,marr[i].date,marr[i].time,marr[i].duration);
        }
        
        **/
}
