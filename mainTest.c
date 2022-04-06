#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <ctype.h>

#define TSIZE 10000

struct Team{
    char tem[40];
    char proj[40];
    char member[4][40]; // !! leader, mem1,mem2,mem3 have changed into 2D array, make the looping easiler
};

struct Meeting{
    char team[40];
    char date[40];
    char time[40];
    char duration[40];       
};
// Declare function
char* replaceWordInText(const char *text, const char *oldWord, const char *newWord);
//print menu
int menu(){
    int option;
    printf("\n ~~  WELCOME TO PolyStar ~~  \n\n");

    printf("1. Create Project Team \n\n");
    printf("2. Project Meeting Request\n");
    printf("   21.  Single input\n");
    printf("   22.  Batch input\n\n");
    // printf("   2c. Meeting Attendance\n\n");
    printf("3. Print Meeting Schedule\n");
    printf("   31.  FCFS (First Come First Served)\n");
    printf("   32.  SJF (Shortest Jobs First)\n\n");
    //  printf("   3c.   YYYY(Attendance Report)\n\n");
    printf("4. Exit\n\n");
    printf("  Enter an option: ");
    scanf("%d",&option);
    return option;
}

void project_team(struct Team arr[5]){

    char str[100];
    int op =1; // op is a option from user input 1-4
    int count=0;


    while (1){

        if (op == 1){

            printf("Enter>  ");
            scanf("%99[^\n]",&str); //%[^\n]s can input string including space 

            sscanf( str, "%s %s %s %s %s %s",arr[count].tem,arr[count].proj,arr[count].member[0],arr[count].member[1],arr[count].member[2],arr[count].member[3]); //conver user input string to words and store in struct variable separately
            printf(">>>>>> Project %s  is created.\n",replaceWordInText(arr[count].tem,"_"," "));


            count++; //count for time of looping if user wants to continues
     
        }else if(op == 0){
            //menu(); //calling menu function
            break;
        }else {
            printf("Wrong input, please enter again ");
            scanf("%d",&op);
            getchar(); //due to the newline character is still in the input buffer on fgets,add getchar() can solve the problem in looping 
        }
        printf("Enter 1/0 > " );  
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

void single_input(struct Meeting marr[100]){

    char str[100];
    int op =21; // op is a option from user input 1-4
    int count=0;
    printf("A\n");
       
  
    while (1){
            
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
            printf("Meeting is being added for %s in %s at %s for %s hours.  \n\n",replaceWordInText(marr[count].team,"_"," "),marr[count].date,marr[count].time,marr[count].duration);
            
            count++; //count for time of looping if user wants to continues

            
        }else if(op == 0){
            //menu(); //calling menu function
            break;
        }else{  
            
            printf("Wrong input, please enter again!\n");
                
        }

        printf ("Do you want to add again ? Enter 21 to continue or 0 back to main menu: " );  
        
        scanf("%d",&op);
        getchar(); //due to the newline character is still in the input buffer on fgets,add getchar() can solve the problem in looping
    }
}

void task3_sjf(int meetingTotal, int teamTotal, struct Meeting meetingArr[], struct Team teamArr[]){
    const char MemberName[8][11] = {"Alan\0", "Billy\0", "Cathy\0", "David\0", "Eva\0", "Fanny\0", "Gary\0","Helen\0"};
    int i,j; //looping integer       
    //  |loop for member                     |Check if member have meeting record or not
    //  |       |loop for team     |Loop for meeting
    //  |       |      |Loop for 4 member position
    int memberID,teamID,memberPos=0,meetingID,haveMeetingRecord=0;// calculation for the loop
    int nextPos,sjfID[meetingTotal],sjfMeetingLength[meetingTotal],sjfPlaced=0;// array for sjf use
    // sjf \/ use to store the string to be printed
    // nextPos store the next position of sjf to be used
    // sjfID store the id order of nextPos to be printed
    // sjfMeetingLength store the sjfID represent meetingID's lenght, use for compare the length for other meeting
    // sjfPlace use to check if current meetingID is placed into the array of sjf or not
    char sjf[meetingTotal][TSIZE];
    for (memberID=0;memberID<8;memberID++){// Find all member
        printf("Member: %s\n\n",MemberName[memberID]);
        nextPos = 0;
        for(teamID=0;teamID<teamTotal;teamID++){// Search all team
            for(memberPos=0;memberPos<4;memberPos++){ // Find all 4 position in member of team
                if(strcmp(teamArr[teamID].member[memberPos],MemberName[memberID])==0){// Member Find in team
                    for(meetingID=0;meetingID<meetingTotal;meetingID++){ // Search All meeting record
                        if(strcmp(meetingArr[meetingID].team,teamArr[teamID].tem)==0){// Meeting belong to that team
                            int hour,minute;
                            char *temp;
                            temp = strtok(meetingArr[meetingID].date,":");// Get the hour of start time
                            hour = atoi(temp);
                            temp = strtok(NULL,":");
                            minute = atoi(temp); // Get the minute of start time
                            // \/ Record to be printed
                            sprintf(sjf[nextPos],"Date: %s, Start: %02d:%02d, End: %02d:%02d, Team: %s, Project: %s\n",meetingArr[meetingID].date,hour,minute,hour+atoi(meetingArr[meetingID].duration),minute,meetingArr[meetingID].team,teamArr[teamID].proj);
                            sjfPlaced=0;
                            for(i=0;i<nextPos;i++){// Loop for checking the minimum hour, and place into two array
                                if(sjfMeetingLength[i]>atoi(meetingArr[meetingID].duration)){
                                    for(j=nextPos;j>=i;j--){// Find a smaller length in the array
                                        sjfMeetingLength[j]=sjfMeetingLength[j-1];// Move all result in array backward
                                        sjfID[j]=sjfID[j-1];
                                    }
                                    sjfID[i]=nextPos;// Store the record into array
                                    sjfMeetingLength[i]=atoi(meetingArr[meetingID].duration);
                                    sjfPlaced=1;
                                    break;// stop search
                                }
                            }
                            if(!sjfPlaced){// Cannot find a smaller length with other;
                                sjfID[nextPos]=nextPos;
                                sjfMeetingLength[nextPos]=atoi(meetingArr[meetingID].duration);
                            }
                            nextPos++;// check to index of sjf
                            haveMeetingRecord=1;// boolean set
                        }
                    }
                }
            }
        }
        for(i=0;i<nextPos;i++){// print the result in specical order
            printf("%s\n",sjf[sjfID[i]]);
        }
        if (!haveMeetingRecord){// no data to be printed
            printf("No Meeting Record.\n");
        }
        haveMeetingRecord=0; // boolean reset
        printf("\n");
    }
}


int main(int argc, char *argv[]){
    int meetingTotal = 100, teamTotal = 5;
    struct Team arr[teamTotal];
    struct Meeting marr[meetingTotal];
    int option;
    do
    {
        option = menu();
        switch(option){
            case 1: project_team(arr);printf("AA\n");break;
            case 21: single_input(marr);break;
            case 32: task3_sjf(meetingTotal,teamTotal,marr,arr);break;
            case 4: break;
            default: printf("Input ERROR!\n Please input again! \n");
        }
    } while (option!=4);
    exit(0);
}
