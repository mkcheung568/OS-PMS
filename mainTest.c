#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <ctype.h>

#define TSIZE 256

struct Team{
    char tem[40];
    char proj[40];
    char member[4][40];
};

struct Meeting{
    char team[40];
    char date[40];
    char time[40];
    char duration[40];       
};
// Declare function
int DateCompare(int SmallerYear,int SmallerMonth, int SmallerDate, int LargerYear, int LargerMonth, int LargerDate);
char* replaceWordInText(const char *text, const char *oldWord, const char *newWord);
void batch_input(struct Meeting marr[100]);

// Global Variable
int team_count=0;//Original in project_team, Problem occur if users input once and exit function, then go to function again and input.
int meeting_count=0;// same as above
int i,j;

//print menu
void menu(){
    int option;
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
    printf("  Enter an option: ");
}
void batch_input(struct Meeting marr[100]){//define a team array of 100 records

    #define LSIZE 130 
    #define RSIZE 10

    char line[RSIZE][LSIZE];
    char fname[20];
    FILE *fptr = NULL; 
    i = 0;
    int tot = 0;//count the number of line
    int crow =0; //count for which row is empty 
    int count=meeting_count;

    
    printf("Input the filename to be opened : ");
    scanf("%s",fname);	

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZE, fptr)) {
        line[i][strlen(line[i]) - 1] = '\0'; //count each line of the file and write it to line array
        i++;
    }
    fclose(fptr);
    tot = i;//The number of row from import file 
    getchar();

    
    for(i = 0; i < tot; ++i){
        if (line[i]=="") crow++;
        sscanf( line[i], "%s %s %s %s ",marr[count].team,marr[count].date,marr[count].time,marr[count].duration); //put the line string array into struct  
        count++;
    }
    for(j=tot;j<100;j++){// set the rest of the array to empty 
        strcpy(marr[j].team , "\0");
        strcpy(marr[j].date , "\0");
        strcpy(marr[j].time , "\0");
        strcpy(marr[j].duration ,"\0");
    }
    printf("\nMeeting request has been imported!\n\n");
    meeting_count += tot-crow;
}

void project_team(struct Team arr[5]){
    char str[100];

    do{
        printf("Enter>  ");
        scanf("%99[^\n]",&str); //%[^\n]s can input string including space 
        getchar();
        if(strcmp(str,"0")==0) break;// exit function if users input 0
        sscanf( str, "%s %s %s %s %s %s",arr[team_count].tem,arr[team_count].proj,arr[team_count].member[0],arr[team_count].member[1],arr[team_count].member[2],arr[team_count].member[3]); //conver user input string to words and store in struct variable separately
        printf(">>>>>> Project %s is created.\n",replaceWordInText(arr[team_count].tem,"_"," "));

        team_count++; //count for time of looping if user wants to continues
    }while(1);
}


/*************************************separate****************************************/

//this function is for change [team_A] without underline  become [team A]when print out on function project_team()
char* replaceWordInText(const char *text, const char *oldWord, const char *newWord) {
    i = 0;
    int cnt = 0;
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
    do{    
        printf("Enter>  ");
        scanf("%[^\n]s",&str); //%[^\n]s can input string including space 
        getchar();
        if(strcmp(str,"0")==0) break; // exit the function
        sscanf( str, "%s %s %s %s ",marr[meeting_count].team,marr[meeting_count].date,marr[meeting_count].time,marr[meeting_count].duration); //conver user input string to words and store in struct variable separately

        if(atoi(marr[meeting_count].duration) <=0 || atoi(marr[meeting_count].duration) >=10 ){ //atoi is convert string to integer
            printf("The duration should from 1 to 9,Please enter again\n");
            continue; //back to the beginning of the looping
        }
        printf("Meeting is being added for %s in %s at %s for %s hours.  \n\n",replaceWordInText(marr[meeting_count].team,"_"," "),marr[meeting_count].date,marr[meeting_count].time,marr[meeting_count].duration);
        meeting_count++; //count for time of looping if user wants to continues
    }while(1);

}

void task3_sjf(int meetingTotal, int teamTotal, struct Meeting meetingArr[], struct Team teamArr[], char startDateArg[], char endDateArg[]){
    int start_year, start_month, start_date, end_year, end_month, end_date;
    char *temp;
    char startDate[TSIZE], endDate[TSIZE];
    strcpy(startDate,startDateArg); // backup data
    strcpy(endDate,endDateArg);     // backup data
    temp = strtok(startDate,"-");   // remove year (Start date)
    start_year = atoi(temp);        // save the year
    temp = strtok(NULL,"-");        // remove month
    start_month = atoi(temp);       // save the month
    temp = strtok(NULL,"-");        // remove date
    start_date = atoi(temp);        // save the date
    temp = strtok(endDate,"-");     // remove year (end date)
    end_year = atoi(temp);          // save the start    
    temp = strtok(NULL,"-");        // remove month
    end_month = atoi(temp);         // save the month
    temp = strtok(NULL,"-");        // remove date
    end_date = atoi(temp);          // save the date
    
    FILE *file; // set file variable
    char filename[] = "Schelde_SJF_00.txt"; // temp file name
    int indexD1 = 0;// get 10 digit
    int indexD2 = 0;// get 1 digit
    int index = 0;
    for (i = 0; i < 100; i++) // loop from 00 to 99
    {
        indexD2 = index/10; // get 10 digit
        indexD1 = index-indexD2*10; // get 1 digit
        char temp[] = "0"; // create empty string
        sprintf(temp,"%d",indexD2); // combine the string 
        filename[12]=temp[0]; // replace the temp file name
        sprintf(temp,"%d",indexD1); //combine the string 
        filename[13]=temp[0]; // replace the temp file name
        if (file=fopen(filename,"r")){ // open to test if the file exist
            fclose(file);
            index++;  // exist add one digit
        }
        else{ // no exist the file name is found
            break;
        }        
    }
    // open the file
    file = fopen(filename,"w");
    // title
    fprintf(file,"\n*** Project Meeting ***\n\n");
    // method
    fprintf(file,"Algorithm used: SJF (Shortest Job First)\n");
    // period
    fprintf(file,"Period: %04d-%02d-%02d to %04d-%02d-%02d\n\n",start_year,start_month,start_date,end_year,end_month,end_date);

    // All member number here
    const char MemberName[8][11] = {"Alan\0", "Billy\0", "Cathy\0", "David\0", "Eva\0", "Fanny\0", "Gary\0","Helen\0"};     
    //  |loop for member                      |Check if member have meeting record or not
    //  |        |loop for team     |Loop for meeting
    //  |        |      |Loop for 4 member position               |Boolean for any record printed
    //  |        |      |           |         |                   |
    int memberID,teamID,memberPos=0,meetingID,haveMeetingRecord=0,anyRecord=0;// calculation for the loop
    int meeting_year, meeting_date, meeting_month; // save the meeting year, date and month
    char temp_date[11];// temp for saving the date
    int hour,minute;// meeting hour and minutes
    char temp_time[6];// temp for saving the time

    // sjf \/ use to store the string to be printed
    char sjf[TSIZE][TSIZE];
    // nextPos store the next position of sjf to be used

    int nextPos,sjfID[TSIZE],sjfMeetingLength[TSIZE],sjfPlaced=0;// array for sjf use
    // sjfID store the id order of nextPos to be printed
    // sjfMeetingLength store the sjfID represent meetingID's lenght, use for compare the length for other meeting
    // sjfPlace use to check if current meetingID is placed into the array of sjf or not

    // Get all meeting record
    for (teamID = 0; teamID < teamTotal; teamID++){
        for(meetingID=0;meetingID<meetingTotal;meetingID++){
            if(strcmp(meetingArr[meetingID].team,teamArr[teamID].tem)==0){
                strcpy(temp_date,meetingArr[meetingID].date); // backup the data
                temp = strtok(temp_date,"-");   // remove year
                meeting_year = atoi(temp);
                temp = strtok(NULL,"-");        // remove month
                meeting_month = atoi(temp);
                temp = strtok(NULL,"-");        // remove date
                meeting_date = atoi(temp);

                // Check if meeting date is within the date
                if(DateCompare(start_year,start_month,start_date,meeting_year,meeting_month,meeting_date) && DateCompare(meeting_year,meeting_month,meeting_date,end_year,end_month,end_date)){ 
                    anyRecord=1;// it is at least one record
                    strcpy(temp_time,meetingArr[meetingID].time); // backup the data
                    temp = strtok(temp_time,":");// Get the hour of start time
                    hour = atoi(temp);
                    temp = strtok(NULL,":");// Get the minute of start time
                    minute = atoi(temp); 
                    // Record to be printed
                    //                    Date Start              End                Team Project
                    sprintf(sjf[nextPos],"%-15s%02d:%02d          %02d:%02d          %-15s%-15s\n",meetingArr[meetingID].date,hour,minute,hour+atoi(meetingArr[meetingID].duration),minute,meetingArr[meetingID].team,teamArr[teamID].proj);
                    sjfPlaced=0;// boolean for if the data has changed pos
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
    if (haveMeetingRecord){// have data to printed.
        fprintf(file,"Date           Start          End            Team           Project        \n");
        fprintf(file,"===========================================================================\n");
        for(i=0;i<nextPos;i++){// print the result in specical order
            fprintf(file,"%s",sjf[sjfID[i]]);
        }
        fprintf(file,"===========================================================================\n");
    }
    haveMeetingRecord=0;

    // same as above for loop for each member
    for (memberID=0;memberID<8;memberID++){// Find all member
        // printf("Member: %s\n\n",MemberName[memberID]); # current
        nextPos = 0;
        for(teamID=0;teamID<teamTotal;teamID++){// Search all team
            for(memberPos=0;memberPos<4;memberPos++){ // Find all 4 position in member of team
                if(strcmp(teamArr[teamID].member[memberPos],MemberName[memberID])==0){// Member Find in team
                    for(meetingID=0;meetingID<meetingTotal;meetingID++){ // Search All meeting record
                        if(strcmp(meetingArr[meetingID].team,teamArr[teamID].tem)==0){// Meeting belong to that team
                            strcpy(temp_date,meetingArr[meetingID].date);
                            temp = strtok(temp_date,"-");// remove year
                            meeting_year = atoi(temp);
                            temp = strtok(NULL,"-");    // remove month
                            meeting_month = atoi(temp);
                            temp = strtok(NULL,"-");    // remove date
                            meeting_date = atoi(temp);
                            if(DateCompare(start_year,start_month,start_date,meeting_year,meeting_month,meeting_date) && DateCompare(meeting_year,meeting_month,meeting_date,end_year,end_month,end_date)){ 
                                strcpy(temp_time,meetingArr[meetingID].time);
                                temp = strtok(temp_time,":");// Get the hour of start time
                                hour = atoi(temp);
                                temp = strtok(NULL,":");    // Get the minute of start time
                                minute = atoi(temp); 
                                // Record to be printed
                                //                    Date Start              End                Team Project       
                                sprintf(sjf[nextPos],"%-15s%02d:%02d          %02d:%02d          %-15s%-15s\n",meetingArr[meetingID].date,hour,minute,hour+atoi(meetingArr[meetingID].duration),minute,meetingArr[meetingID].team,teamArr[teamID].proj);
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
        }
        if (haveMeetingRecord){// have data to printed.
            // start line
            fprintf(file,"Staff: %s\n\n",MemberName[memberID]);
            // list
            fprintf(file,"Date           Start          End            Team           Project        \n");
            fprintf(file,"===========================================================================\n");
            // record
            for(i=0;i<nextPos;i++){// print the result in specical order
                //printf("%s\n",sjf[sjfID[i]]);
                fprintf(file,"%s",sjf[sjfID[i]]);
            }
            // end line
            fprintf(file,"\n===========================================================================\n");
        }
        haveMeetingRecord=0; // boolean reset
    }
    if (!anyRecord){ // if not meeting record in the periods
        fprintf(file,"===========================================================================\n");
        fprintf(file,"No meeting record within this period.\n");
        fprintf(file,"===========================================================================\n");
    }
    // end file line.
    fprintf(file,"                                    -End-                                    \n");
    fclose(file); // close file very important
    printf(">>>> Printed. Export file name: %s.\n",filename);// show user which file name has generate
}

int DateCompare(int SmallerYear,int SmallerMonth, int SmallerDate, int LargerYear, int LargerMonth, int LargerDate){
    if (LargerYear > SmallerYear) return 1;
    if (LargerYear == SmallerYear && LargerMonth > SmallerMonth) return 1;
    if (LargerYear == SmallerYear && LargerMonth == SmallerMonth && LargerDate >= SmallerDate) return 1;
    return 0;
}

void fcfs(struct Meeting marr[100]) {

    int year[8];
    int mon[8];
    int day[8];
    int hour[8];
    int minutes[8];
    int temp=0;
    int crow=0;
         

    //save the meeting schedule data in temp
    char teamtem[20];
    char datetem[20];
    char timetem[20];
    char durationtem[20];

    int row;
    for(row=0; row<100; row++){ // find the marr row until the row is empty

        if(strlen(marr[row].team) !=0){
            crow++;
        }else{  
            break;  
        }
    }

    //sorting by month
    for(i=0;i<crow;++i){ //put the month to the mon array
       
        sscanf(marr[i].date, "%d-%d-%d",&year[i],&mon[i],&day[i]);
  
    }

       //bubble sorting , sort by month
    for (i = 0; i < crow-1; i++){  
        for (j = 0; j < crow -1- i; j++){
            if (mon[j] > mon[j + 1]) {
              
                temp = mon[j];
                strcpy(teamtem, marr[j].team);
                strcpy(datetem, marr[j].date);
                strcpy(timetem, marr[j].time);
                strcpy(durationtem, marr[j].duration);

                mon[j] = mon[j + 1];
                strcpy(marr[j].team, marr[j+1].team);
                strcpy(marr[j].date, marr[j+1].date);
                strcpy(marr[j].time, marr[j+1].time);
                strcpy(marr[j].duration, marr[j+1].duration);


                mon[j + 1] = temp;
                strcpy(marr[j+1].team, teamtem);
                strcpy(marr[j+1].date, datetem);
                strcpy(marr[j+1].time, timetem);
                strcpy(marr[j+1].duration, durationtem);

            }
        }

    }

///////////////////////////////////////////////////////////////////////////////////

    //sorting by day
    for(i=0;i<crow;++i){ //put the day value from date array to the day array
        sscanf(marr[i].date, "%d-%d-%d",&year[i],&mon[i],&day[i]);
  
    }

    
       //bubble sorting , sort by day
    for (i = 0; i < crow-1; i++){  
        for (j = 0; j < crow -1- i; j++){
            if (mon[j] == mon[j + 1] && day[j] > day[j + 1] ) {
                

                temp = day[j];
                strcpy(teamtem, marr[j].team);
                strcpy(datetem, marr[j].date);
                strcpy(timetem, marr[j].time);
                strcpy(durationtem, marr[j].duration);

                day[j] = day[j + 1];
                strcpy(marr[j].team, marr[j+1].team);
                strcpy(marr[j].date, marr[j+1].date);
                strcpy(marr[j].time, marr[j+1].time);
                strcpy(marr[j].duration, marr[j+1].duration);


                day[j + 1] = temp;
                strcpy(marr[j+1].team, teamtem);
                strcpy(marr[j+1].date, datetem);
                strcpy(marr[j+1].time, timetem);
                strcpy(marr[j+1].duration, durationtem);

            }
        }

    }
/////////////////////////////////////////////////////////////////////////////

    //sorting by time(hour)
    for(i=0;i<crow;++i){   //put the month to the mon array
        sscanf(marr[i].time, "%d:%d",&hour[i],&minutes[i]);
  
    }

    
       //bubble sorting , sort by time
    for ( i = 0; i < crow-1; i++){  
        for ( j = 0; j < crow -1- i; j++){
            if (day[j] == day[j + 1] && hour[j] > hour[j + 1] ) {
               
                temp = hour[j];
                strcpy(teamtem, marr[j].team);
                strcpy(datetem, marr[j].date);
                strcpy(timetem, marr[j].time);
                strcpy(durationtem, marr[j].duration);

                hour[j] = hour[j + 1];
                strcpy(marr[j].team, marr[j+1].team);
                strcpy(marr[j].date, marr[j+1].date);
                strcpy(marr[j].time, marr[j+1].time);
                strcpy(marr[j].duration, marr[j+1].duration);


                hour[j + 1] = temp;
                strcpy(marr[j+1].team, teamtem);
                strcpy(marr[j+1].date, datetem);
                strcpy(marr[j+1].time, timetem);
                strcpy(marr[j+1].duration, durationtem);

            }
        }

    }

}



int main(int argc, char *argv[]){
    int meetingTotal = 100, teamTotal = 5, loop = 1;
    struct Team arr[teamTotal];
    struct Meeting marr[meetingTotal];
    do
    {
        char inputString[50], *temp,option[10], Start_Date[12],End_Date[12];
        menu();
        fgets(inputString,50,stdin);
        if ((strlen(inputString) > 0) && (inputString[strlen (inputString) - 1] == '\n'))
            inputString[strlen (inputString) - 1] = '\0';

        temp = strtok(inputString," ");
        strcpy(option,temp);
        if (strcmp(option,"3a")==0 || strcmp(option,"3b")==0){
            temp = strtok(NULL," ");
            sprintf(Start_Date,"%s",temp);
            temp = strtok(NULL," ");
            sprintf(End_Date,"%s",temp);
        }
        if(strcmp(option,"1")==0) project_team(arr);
        else if(strcmp(option,"2a")==0) single_input(marr);
        else if(strcmp(option,"2b")==0) batch_input(marr);
        else if(strcmp(option,"3a")==0) fcfs(marr);
        else if(strcmp(option,"3b")==0) task3_sjf(meeting_count,team_count,marr,arr,Start_Date,End_Date);
        else if(strcmp(option,"4")==0) loop=0;
        else  printf(" \n **  Input ERROR! Please input again! ** \n");

    } while (loop);
    exit(0);
}
