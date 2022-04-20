#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <ctype.h>
#include <signal.h>

#define TSIZE 1000

struct Team{
    char tem[40]; // team name
    char proj[40]; // project name
    char member[4][40]; // team member
};

struct Meeting{
    char team[40]; // team belong to the meeting
    char date[40]; // meeting start date
    char time[40]; // meeting start time
    char duration[40]; // meeting duration
};
// Declare function
int DateCompare(int SmallerYear,int SmallerMonth, int SmallerDate, int LargerYear, int LargerMonth, int LargerDate);
char* replaceWordInText(const char *text, const char *oldWord, const char *newWord);
void batch_input(struct Meeting marr[100]);

// Global Variable
int team_count=0;//Original in project_team, Problem occur if users input once and exit function, then go to function again and input.
int meeting_count=0;// same as above
int i,j; // loop use

//print menu
void menu(){

    printf("\n ~~  WELCOME TO PolyStar ~~  \n\n");

    printf("1. Create Project Team \n\n");

    printf("2. Project Meeting Request\n");
    printf("   2a.  Single input\n");
    printf("   2b.  Batch input\n\n");

    printf("3. Print Meeting Schedule\n");
    printf("   3a.  FCFS (First Come First Served)\n");
    printf("   3b.  SJF (Shortest Jobs First)\n\n");

    printf("4. Exit\n\n");
    printf("  Enter an option: ");
}

void batch_input(struct Meeting marr[100]){//define a team array of 100 records

    #define RSIZE 100

    char line[TSIZE][RSIZE];
    char fname[20];
    FILE *fptr = NULL; 
    i = 0;
    int tot = 0;//count the number of line
    int crow =0; //count for which row is empty 
    int count=meeting_count; // count exist meeting record

    // ask user to input file
    printf("Input the filename to be opened : ");
    scanf("%s",fname);	
    getchar();
    // if 0 is input, return the main menu
    if(strcmp(fname,"0")==0){
        return;
    }
    // open the user input file
    fptr = fopen(fname, "r");
    while(fgets(line[i], RSIZE, fptr)) {
        line[i][strlen(line[i])] = '\0'; //count each line of the file and write it to line array
        i++;
    }
    fclose(fptr);
    tot = i;//The number of row from import file 

    char meeting_DATE[TSIZE],meeting_Time[TSIZE],*temp;
    int meeting_year, meeting_month, meeting_date,time,minute;
    for(i = 0; i < tot; ++i){
        if (line[i]=="")
            continue;
        sscanf(line[i], "%s %s %s %s ",marr[count].team,marr[count].date,marr[count].time,marr[count].duration); //put the line string array into struct  
        strcpy(meeting_DATE,marr[count].date);      // backup data
        temp = strtok(meeting_DATE,"-");            // remove year (Start date)
        meeting_year = atoi(temp);                  // save the year
        temp = strtok(NULL,"-");                    // remove month
        meeting_month = atoi(temp);                 // save the month
        temp = strtok(NULL,"-");                    // remove date
        meeting_date = atoi(temp);                  // save the date
        strcpy(meeting_Time,marr[count].time);
        temp = strtok(meeting_Time,":");            // hour
        time = atoi(temp);
        temp = strtok(NULL,":");            // minute
        minute = atoi(temp);
        // sunday
        if ((meeting_month == 5 && meeting_date == 1)||(meeting_month == 5 && meeting_date == 8)){
            printf("Meeting cannot added to the system. Problem detected: Meeting on Sunday.\n Detail: Team: %s, Meeting Date: %s, Meeting Time: %s, Meeting Duration: %s",marr[count].team,marr[count].date,marr[count].time,marr[count].duration);
        }// 0900 > time > 1800 
        else if (time + atoi(marr[count].duration) > 18 || (time + atoi(marr[count].duration) == 18 && minute != 0) || time < 9){
            printf("Meeting cannot added to the system. Problem detected: Meeting time should be within 09:00 to 18:00.\n Detail: Team: %s, Meeting Date: %s, Meeting Time: %s, Meeting Duration: %s",marr[count].team,marr[count].date,marr[count].time,marr[count].duration);
        }// correct period date
        else if (DateCompare(2022,04,25,meeting_year,meeting_month,meeting_date) && DateCompare(meeting_year,meeting_month,meeting_date,2022,05,14)){
            count++;
        }else { // other error
            printf("Meeting cannot added to the system. Problem detected: Meeting is not within 2022-04-25 to 2022-05-14.\n Detail: Team: %s, Meeting Date: %s, Meeting Time: %s, Meeting Duration: %s\n",marr[count].team,marr[count].date,marr[count].time,marr[count].duration);
        }
    }
    // inform user
    printf("\nMeeting request has been imported!\n\n");
    // count all the meeting number
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
        // Duration 1-9
        if(atoi(marr[meeting_count].duration) <=0 || atoi(marr[meeting_count].duration) >=10 ){ //atoi is convert string to integer
            printf("The duration should from 1 to 9. Please enter again.\n");
            continue; //back to the beginning of the looping
        }
        char meeting_DATE[TSIZE],meeting_Time[TSIZE],*temp;
        int meeting_year, meeting_month, meeting_date,time,minute;
        strcpy(meeting_DATE,marr[meeting_count].date);      // backup data
        temp = strtok(meeting_DATE,"-");                    // remove year (Start date)
        meeting_year = atoi(temp);                          // save the year
        temp = strtok(NULL,"-");                            // remove month
        meeting_month = atoi(temp);                         // save the month
        temp = strtok(NULL,"-");                            // remove date
        meeting_date = atoi(temp);                          // save the date
        strcpy(meeting_Time,marr[meeting_count].time);      // backup the time
        temp = strtok(meeting_Time,":");                    // get the hour
        time = atoi(temp);
        temp = strtok(NULL,":");                    // get the minute
        minute = atoi(temp);
        // not within 2022-04-25 and 2022-05-14
        if (! DateCompare(2022,04,25,meeting_year,meeting_month,meeting_date) || !DateCompare(meeting_year,meeting_month,meeting_date,2022,05,14)){
            printf("Meeting date should be within 2022-04-25 to 2022-05-14.Please enter again.\n");
            continue; //back to the beginning of the looping
        }
        // 0900 >= time >= 1800
        if (time + atoi(marr[meeting_count].duration) > 18 || (time + atoi(marr[meeting_count].duration) == 18 && minute != 0) || time < 9){
            printf("Meeting time should be within 09:00 to 18:00.Please enter again.\n");
            continue; //back to the beginning of the looping
        }// sunday 2022-5-1 and 2022-5-8
        if ((meeting_month == 5 && meeting_date == 1)||(meeting_month == 5 && meeting_date == 8)){
            printf("Meeting date should be between Monday to Saturday. Please enter again.\n");
            continue; //back to the beginning of the looping
        }
        // correct
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

    int nextPos,sjfID[TSIZE],sjfMeetingLength[TSIZE],sjfPlaced=0,sjfMeetingID[TSIZE];// array for sjf use
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

    fclose(file);
    int parentID;
    char buffer[21];
    int fd[8][2];
    for (i=0;i<8;i++){ // pipe for exchange the member name
        if(pipe(fd[i])<0){
            printf("Pipe Error");exit(1);
        }
    };
    //loop for separate each staff meeting 
    parentID = getpid();
    pid_t pid[8];
    for (memberID=0;memberID<8;memberID++){ // create 8 children for write each member
        if((pid[memberID] = fork()) < 0){
            printf("Fork Error!"); exit(1);// fork error occur
        }else if(pid[memberID]==0){// child here
            // close all not necessary pipe
            for (i=0;i<8;i++){
                if (i != memberID){
                    close(fd[i][0]);
                    close(fd[i][1]);
                }
            }
            read(fd[memberID][0],buffer,20);
            // printf("Member: %s\n\n",MemberName[memberID]); # current
            nextPos = 0;
            for(teamID=0;teamID<teamTotal;teamID++){// Search all team
                for(memberPos=0;memberPos<4;memberPos++){ // Find all 4 position in member of team
                    if(strcmp(teamArr[teamID].member[memberPos],buffer)==0){// Member Find in team
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
                                                sjfMeetingID[j]=sjfMeetingID[j-1];
                                            }
                                            sjfID[i]=nextPos;// Store the record into array
                                            sjfMeetingLength[i]=atoi(meetingArr[meetingID].duration);
                                            sjfMeetingID[i]=meetingID;
                                            sjfPlaced=1;
                                            break;// stop search
                                        }
                                    }
                                    if(!sjfPlaced){// Cannot find a smaller length with other;
                                        sjfID[nextPos]=nextPos;
                                        sjfMeetingLength[nextPos]=atoi(meetingArr[meetingID].duration);
                                        sjfMeetingID[nextPos]=meetingID;
                                    }
                                    nextPos++;// check to index of sjf
                                    haveMeetingRecord=1;// boolean set
                                }                            
                            }
                        }
                    }
                }
            }
            raise(SIGSTOP);
            //                  dateID Data
            char dateHaveMeeting[TSIZE][TSIZE];
            //                  dataID
            int totalMeetingTime[TSIZE];
            // Date, hour
            int timeSlot[TSIZE][19]; // 0 empty // 1 = used // 2 = cannot use
            int meetingTimeOnDate[TSIZE]; // < 9
            int sjtOrder,dateID=0,total_Date=0;
            file=fopen(filename,"a");
            if (haveMeetingRecord){// have data to printed.
                // start line
                fprintf(file,"Staff: %s\n\n",buffer);
                // list
                fprintf(file,"Date           Start          End            Team           Project        \n");
                fprintf(file,"===========================================================================\n");
                // record
                int k,hour,minute,can_Print,date_exist;
                struct Meeting currentMeetingData;
                for(sjtOrder=0;sjtOrder<nextPos;sjtOrder++){// print the result in specical order
                    can_Print =1;
                    date_exist=total_Date;
                    currentMeetingData = meetingArr[sjfMeetingID[sjtOrder]];// get the meeting data
                    sscanf(currentMeetingData.time,"%d:%d",&hour,&minute);
                    for (dateID=0;dateID<total_Date;dateID++){
                        if(strcmp(currentMeetingData.date,dateHaveMeeting[dateID])==0){ // check if the date has meeting before
                            for (k=hour;k<=hour+atoi(currentMeetingData.duration);k++){
                                if(timeSlot[dateID][k] == 1){
                                    can_Print = 0;
                                    break;
                                }
                                if (totalMeetingTime[dateID]+atoi(currentMeetingData.duration)>9){
                                    can_Print = 0;
                                    break;
                                }
                            }
                            date_exist=dateID;
                        }
                    }
                    if (can_Print){
                        fprintf(file,"%s",sjf[sjfID[sjtOrder]]);
                        for (k=hour;k<=hour+atoi(currentMeetingData.duration);k++){ // set the time slot used
                            timeSlot[date_exist][k]=1;
                        }
                        if (date_exist == total_Date){
                            strcpy(dateHaveMeeting[total_Date],currentMeetingData.date);
                            totalMeetingTime[total_Date] += atoi(currentMeetingData.duration);
                            total_Date++;
                        }else
                            totalMeetingTime[total_Date] += atoi(currentMeetingData.duration);
                        
                    }
                }
                // end line
                fprintf(file,"\n===========================================================================\n");
            }
            fclose(file);
            close(fd[memberID][0]);
            close(fd[memberID][1]);
            raise(SIGSTOP);
            exit(0);
        }else{// give the child member name
            write(fd[memberID][1],MemberName[memberID],20);
        }
    }
    for (memberID = 0; memberID<8;memberID++){
        waitpid(pid[memberID], NULL, WUNTRACED);
        kill(pid[memberID], SIGCONT);
        waitpid(pid[memberID], NULL, WUNTRACED);
        kill(pid[memberID], SIGCONT);
    }
    file=fopen(filename,"a");   
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

// Check the date of second one is larger than the first one
int DateCompare(int SmallerYear,int SmallerMonth, int SmallerDate, int LargerYear, int LargerMonth, int LargerDate){
    if (LargerYear > SmallerYear) return 1;//year check
    if (LargerYear == SmallerYear && LargerMonth > SmallerMonth) return 1;// month check
    if (LargerYear == SmallerYear && LargerMonth == SmallerMonth && LargerDate >= SmallerDate) return 1;// date check
    return 0;
}

// Save the result of FCFS into .txt variable
void fcfs_report(struct Meeting marr[],struct Team arr[], char StartDate[], char EndDate[]){
    int hour[TSIZE];
    int minutes[TSIZE];
    int duration[TSIZE];
    int endtime[TSIZE];
    char end[TSIZE][10];//end of the meeting
    int crow=meeting_count;
    char project[TSIZE][10];//for project name and team matching
    char namelist[8][10]={"Alan","Billy","Cathy","David","Eva","Fanny","Gary","Helen"};
    int row;


    ///////////////////////////////print data to txt file /////////////////////////

    FILE *file; // set file variable
    char filename[] = "Schelde_FCFS_00.txt"; // temp file name
    int indexD1 = 0;// get 10 digit
    int indexD2 = 0;// get 1 digit
    int index = 0;
    for (i = 0; i < 100; i++) // loop from 00 to 99
    {
        indexD2 = index/10; // get 10 digit
        indexD1 = index-indexD2*10; // get 1 digit
        char temp[] = "0"; // create empty string
        sprintf(temp,"%d",indexD2); // combine the string 
        filename[13]=temp[0]; // replace the temp file name
        sprintf(temp,"%d",indexD1); //combine the string 
        filename[14]=temp[0]; // replace the temp file name
        if (file=fopen(filename,"r")){ // open to test if the file exist
            fclose(file);
            index++;  // exist add one digit
        }
        else{ // no exist the file name is found
            break;
        }        
    }
    // Open the file
    file = fopen(filename,"w");
    // Heading of text file
    fprintf(file,"\n*** Project Meeting ***\n\n");
    // Algorithm
    fprintf(file,"Algorithm used: FCFS\n");
    // period
    fprintf(file,"Period: %s to %s\n",StartDate,EndDate);

    fprintf(file,"Date                 Start            End             Team             Project        \n");
    fprintf(file,"================================================================================\n");
    //fclose(file);


  
    ////// this part is for formating the the whole meeting from 2022-04-25 to 2022-04-27 //////////////////////
    for(i=0;i<crow;++i){   //extract the hour value on time array
        sscanf(marr[i].time, "%d:%d",&hour[i],&minutes[i]);
    }
    
    for(i=0;i<crow;++i){   //change the duration value to integer save in duration[] array 
        sscanf(marr[i].duration, "%d",&duration[i]);
    }
    for(j=0;j<crow;j++){// add start hour and duration 
        endtime[j]=hour[j]+duration[j];
    }

    for(j=0;j<crow;j++){ // resulting the end time in time format and save in end array,for fcfs report printing
        snprintf(end[j],sizeof(end),"%d:00",endtime[j]);     
    }

    int k, n, m, p;
    //for report printing team and project name matching
    for(k=0;k<crow;k++){ 
        for(n=0;n<5;n++){
            if( strcmp(marr[k].team,arr[n].tem) == 0){
                strcpy(project[k],arr[n].proj);
            }
        }
    }



    char startDate[TSIZE], endDate[TSIZE], temp_date[11], *temp;
    int start_year, start_month, start_date, end_year, end_month, end_date, meeting_year, meeting_month, meeting_date;
    strcpy(startDate,StartDate); // backup data
    strcpy(endDate,EndDate);     // backup data
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

   
    for(i=0;i<meeting_count; i++){
        for (n=0;n<5;n++){ // loop for team then
            // If team is response for the meeting
            if(strcmp(arr[n].tem,marr[i].team) == 0){

                strcpy(temp_date,marr[i].date);
                /*printf("Temp: %s\n",temp_date);
                sscanf(temp_date,"%d-%d-%d",&meeting_year,&meeting_month,&meeting_date);
                printf("%d, %d ,%d\n",meeting_year,meeting_month,meeting_date);
                continue;*/
                temp = strtok(temp_date,"-");// remove year
                meeting_year = atoi(temp);
                temp = strtok(NULL,"-");    // remove month
                meeting_month = atoi(temp);
                temp = strtok(NULL,"-");    // remove date
                meeting_date = atoi(temp);
                // check if the meeting record within the period
                if(DateCompare(start_year,start_month,start_date,meeting_year,meeting_month,meeting_date) && DateCompare(meeting_year,meeting_month,meeting_date,end_year,end_month,end_date)) {
                    fprintf(file,"%s           %s           %s           %s           %s           \n",marr[i].date,marr[i].time,end[i],arr[n].tem,arr[n].proj);
                }
            }
        }
    }

    //fprintf(file,"===============================================================================\n");

    //////////////////////     Each staff meeting output printing      ///////////////////////////////////////////////




    fclose(file);
    //loop for separate each staff meeting 
    int childID, parentID,aid=0,temp_hour,temp_mint,print,date_Exist=0,dateID;
    char reject_date[TSIZE][TSIZE];
    int reject_Time[TSIZE][19];
    int reject_TotalTime[TSIZE];

    parentID = getpid();
    pid_t pid[8];
    for (childID=0;childID<8;childID++){ // create 8 children for write each member
        if((pid[childID] = fork()) < 0){
            printf("Fork Error!"); exit(1);// fork error occur
        }else if(pid[childID]==0){// child here
            raise(SIGSTOP);
            file = fopen(filename,"a");
            // file heading
            fprintf(file,"================================================================================\n");
            fprintf(file,"Staff: %s\n\n",namelist[childID]);
            fprintf(file,"Date                 Start            End             Team             Project        \n");
            fprintf(file,"================================================================================\n");
            for(p=0;p<meeting_count;p++){ //loop for meeting recording first
                for (n=0;n<5;n++){ // loop for team then
                    // If team is response for the meeting
                    if(strcmp(arr[n].tem,marr[p].team) == 0){
                    // If member is belong to the team
                        if(strcmp(namelist[childID],arr[n].member[0]) == 0 || strcmp(namelist[childID],arr[n].member[1]) == 0 || strcmp(namelist[childID],arr[n].member[2]) == 0 || strcmp(namelist[childID],arr[n].member[3]) == 0 ){
                            
                            // int checkreject(int date, int time, int duration){

                            // }
                            print = 1;
                            sscanf(marr[p].time,"%d:%d",&temp_hour,&temp_mint);
                            date_Exist=0;
                            for(i=0;i<aid;i++){
                                if(strcmp(reject_date[i],marr[p].date) == 0){
                                    date_Exist=1;
                                    dateID = i;
                                    for(k=temp_hour;k<=temp_hour+atoi(marr[p].duration);k++){
                                        if(reject_Time[i][k]==1){
                                            print=0;
                                            break;
                                        }
                                        if(reject_TotalTime[i]+atoi(marr[p].duration)>9){
                                            print=0;
                                            break;
                                        }
                                    }
                                }
                            }
                            if(print) {
                                strcpy(temp_date,marr[p].date);
                                temp = strtok(temp_date,"-");// remove year
                                meeting_year = atoi(temp);
                                temp = strtok(NULL,"-");    // remove month
                                meeting_month = atoi(temp);
                                temp = strtok(NULL,"-");    // remove date
                                meeting_date = atoi(temp);
                                // Check the date
                                if(DateCompare(start_year,start_month,start_date,meeting_year,meeting_month,meeting_date) && DateCompare(meeting_year,meeting_month,meeting_date,end_year,end_month,end_date)){
                                    if (!date_Exist){
                                        dateID = aid;
                                    }
                                    for(k=temp_hour;k<=temp_hour+atoi(marr[p].duration);k++){
                                        strcpy(reject_date[aid],marr[p].date);
                                        reject_Time[dateID][k]=1;
                                        reject_TotalTime[dateID]+=1;
                                    }
                                    if (!date_Exist){
                                        aid++;
                                    }
                                    fprintf(file,"%s           %s           %s           %s           %s           \n",marr[p].date,marr[p].time,end[p],arr[n].tem,arr[n].proj);
                                }
                            }
                        }
                    }
                }
            }
            fclose(file);
            raise(SIGSTOP);
            exit(0);
        }
    }
    for (childID = 0; childID<8;childID++){
        // Wait for children ready
        waitpid(pid[childID], NULL, WUNTRACED);
        // Let one children write the file
        kill(pid[childID], SIGCONT);
        // Wait for the children finish
        waitpid(pid[childID], NULL, WUNTRACED);
        // let the children continue and start next children
        kill(pid[childID], SIGCONT);
    }
    file=fopen(filename,"a");
    // End line
    fprintf(file,"                               -End-                                        \n");
    // Close the file is important
    fclose(file);
    // END
    printf("Printed. Export file name: %s.\n",filename);

       
}

void fcfs(struct Meeting marr[], int meeting_Count) {

    int year[TSIZE];
    int mon[TSIZE];
    int day[TSIZE];
    int hour[TSIZE];
    int minutes[TSIZE];
    int temp=0;
    int crow=0;
         

    //save the meeting schedule data in temp
    char teamtem[TSIZE];
    char datetem[TSIZE];
    char timetem[TSIZE];
    char durationtem[TSIZE];

    int row;
    for(row=0; row<meeting_Count; row++){ // find the marr row until the row is empty

        if(strlen(marr[row].team) !=0){
            crow++;
        }else{  
            break;  
        }
    }
    crow = meeting_Count;
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
    int meetingTotal = TSIZE, teamTotal = 5, loop = 1, pid;
    // set the struct
    struct Team arr[teamTotal];
    struct Meeting marr[meetingTotal];
    do // loop the main page until 4 is input
    {
        char inputString[50], *temp, option[10], Start_Date[12], End_Date[12]; 
        menu(); // show menu
        fgets(inputString,50,stdin); // get the user input
        if ((strlen(inputString) > 0) && (inputString[strlen (inputString) - 1] == '\n')) //remove the newline
            inputString[strlen (inputString) - 1] = '\0';

        // save the input
        sscanf(inputString,"%s %s %s",option,Start_Date,End_Date);
        // check if 3a 3b include time period
        if ((strcmp(option,"3a")==0 || strcmp(option,"3b")==0) && (strcmp(Start_Date,"") == 0 || strcmp(End_Date,"") == 0)){
            printf("Please input the meeting period\n");
            continue;
        }
        // 1, 2a, 2b, 3a, 3b, 4
        
        if(strcmp(option,"1")==0) project_team(arr); // option 1
        else if(strcmp(option,"2a")==0) single_input(marr); // option 2a
        else if(strcmp(option,"2b")==0) batch_input(marr); // option 2b
        else if(strcmp(option,"3a")==0) {fcfs(marr,meeting_count);fcfs_report(marr,arr,Start_Date,End_Date);} // option 3a
        else if(strcmp(option,"3b")==0) task3_sjf(meeting_count,team_count,marr,arr,Start_Date,End_Date); // option 3b
        else if(strcmp(option,"4")==0) loop=0;// exit
        else  printf(" \n **  Input ERROR! Please input again! ** \n");
    } while (loop);
    exit(0);
}
