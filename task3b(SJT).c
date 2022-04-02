#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TSIZE 10000

// SJT of task 3 with changeable record
// Job Done: 
// Find all members with corresponding team information and meeting record
// Sorting all the meeting record according to meeting length
// Calculate all the End time by adding start time and length
// Print all result with member name
// Testing had been done with the data below, **still need to test for more case**
// --------------------------------------------------------------------------------
// To be done:
// create a file
// print all record into file
// print  all the result in format

struct Team{
    char teamName[50];
    char projectTitle[50];
    char Member[4][100];
};
struct Meeting{
    char teamName[50];
    char startDate[50];
    char startTime[50];
    int length;
};

int main(){
    const char MemberName[8][11] = {"Cathy\0", "Billy\0", "Alan\0", "David\0", "Eva\0", "Fanny\0", "Gary\0","Helen\0"};
    struct Team team[5];
    //team record below
    // Team 0
    strcpy(team[0].teamName,"Team_A");
    strcpy(team[0].projectTitle,"Project_A");
    strcpy(team[0].Member[0],"Alan");
    strcpy(team[0].Member[1],"Cathy");
    strcpy(team[0].Member[2],"Fanny");
    strcpy(team[0].Member[3],"Helen");
    // Team 1
    strcpy(team[1].teamName,"TB");
    strcpy(team[1].projectTitle,"Prototype GameOver");
    strcpy(team[1].Member[0],"Cathy");
    strcpy(team[1].Member[1],"David");
    // ------------------------------------------------------
    struct Meeting meeting[10];
    // Meeting record below
    // Meeting 0
    strcpy(meeting[0].teamName,"Team_A");
    strcpy(meeting[0].startDate,"2022-04-25");
    strcpy(meeting[0].startTime,"09:00");
    meeting[0].length=2;
    // Meeting 1
    strcpy(meeting[1].teamName,"TB");
    strcpy(meeting[1].startDate,"2022-04-28");
    strcpy(meeting[1].startTime,"10:00");
    meeting[1].length=3;
    // Meeting 2
    strcpy(meeting[2].teamName,"Team_A");
    strcpy(meeting[2].startDate,"2022-04-29");
    strcpy(meeting[2].startTime,"14:00");
    meeting[2].length=4;
    // Meeting 3
    strcpy(meeting[3].teamName,"TB");
    strcpy(meeting[3].startDate,"2022-05-01");
    strcpy(meeting[3].startTime,"9:00");
    meeting[3].length=1;
    // Meeting 4
    strcpy(meeting[4].teamName,"TB");
    strcpy(meeting[4].startDate,"2022-04-30");
    strcpy(meeting[4].startTime,"15:00");
    meeting[4].length=3;

    int i,j; //looping integer       
        
    //  |loop for member                     |Check if member have meeting record or not
    //  |       |loop for team     |Loop for meeting
    //  |       |      |Loop for 4 member position
    int memberID,teamID,memberPos=0,meetingID,haveMeetingRecord=0;// calculation for the loop
    int meetingTotal=5,teamTotal=2; // Change when input data change
    int nextPos,sjtID[meetingTotal],sjtMeetingLength[meetingTotal],sjtPlaced=0;// array for sjt use
    // SJT \/ use to store the string to be printed
    // nextPos store the next position of SJT to be used
    // sjtID store the id order of nextPos to be printed
    // sjtMeetingLength store the sjtID represent meetingID's lenght, use for compare the length for other meeting
    // sjtPlace use to check if current meetingID is placed into the array of SJT or not
    char sjt[meetingTotal][TSIZE];
    for (memberID=0;memberID<8;memberID++){// Find all member
        printf("Member: %s\n\n",MemberName[memberID]);
        nextPos = 0;
        for(teamID=0;teamID<teamTotal;teamID++){// Search all team
            for(memberPos=0;memberPos<4;memberPos++){ // Find all 4 position in member of team
                if(strcmp(team[teamID].Member[memberPos],MemberName[memberID])==0){// Member Find in team
                    for(meetingID=0;meetingID<meetingTotal;meetingID++){ // Search All meeting record
                        if(strcmp(meeting[meetingID].teamName,team[teamID].teamName)==0){// Meeting belong to that team
                            int hour,minute;
                            char *temp;
                            temp = strtok(meeting[meetingID].startTime,":");// Get the hour of start time
                            hour = atoi(temp);
                            temp = strtok(NULL,":");
                            minute = atoi(temp); // Get the minute of start time
                            // \/ Record to be printed
                            sprintf(sjt[nextPos],"Date: %s, Start: %02d:%02d, End: %02d:%02d, Team: %s, Project: %s\n",meeting[meetingID].startDate,hour,minute,hour+meeting[meetingID].length,minute,meeting[meetingID].teamName,team[teamID].projectTitle);
                            sjtPlaced=0;
                            for(i=0;i<nextPos;i++){// Loop for checking the minimum hour, and place into two array
                                if(sjtMeetingLength[i]>meeting[meetingID].length){
                                    for(j=nextPos;j>=i;j--){// Find a smaller length in the array
                                        sjtMeetingLength[j]=sjtMeetingLength[j-1];// Move all result in array backward
                                        sjtID[j]=sjtID[j-1];
                                    }
                                    sjtID[i]=nextPos;// Store the record into array
                                    sjtMeetingLength[i]=meeting[meetingID].length;
                                    sjtPlaced=1;
                                    break;// stop search
                                }
                            }
                            if(!sjtPlaced){// Cannot find a smaller length with other;
                                sjtID[nextPos]=nextPos;
                                sjtMeetingLength[nextPos]=meeting[meetingID].length;
                            }
                            nextPos++;// check to index of sjt
                            haveMeetingRecord=1;// boolean set
                        }
                    }
                }
            }
        }
        for(i=0;i<nextPos;i++){// print the result in specical order
            printf("%s\n",sjt[sjtID[i]]);
        }
        if (!haveMeetingRecord){// no data to be printed
            printf("No Meeting Record.\n");
        }
        haveMeetingRecord=0; // boolean reset
        printf("\n");
    }
}
