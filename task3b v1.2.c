#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TSIZE 10000

// SJT of task 3
// Require task 1 typeof struct team and task 2a typeof struct meeting
// Require total number of team and meeting

// The code below are NOT tested, function can be used, but I am not sure if the array can put into the argument.

// Modify from task3b(sjt).c
// meeting array and team array change into "meetingArr" and "teamArr" to prevent using same variable the struct in task 1 and 2a
// create function to easily combine
// 4 argument are required.
// total number of meeting records, total number of teams, the meeting record's array and array of team list.

int main()
{
    task3_sjt(5,3,marr,arr);
}

void task3_sjt(int meetingTotal, int teamTotal, meeting meetingArr, team teamArr){
    int i,j; //looping integer       
    //  |loop for member                     |Check if member have meeting record or not
    //  |       |loop for team     |Loop for meeting
    //  |       |      |Loop for 4 member position
    int memberID,teamID,memberPos=0,meetingID,haveMeetingRecord=0;// calculation for the loop
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
                if(strcmp(teamArr[teamID].Member[memberPos],MemberName[memberID])==0){// Member Find in team
                    for(meetingID=0;meetingID<meetingTotal;meetingID++){ // Search All meeting record
                        if(strcmp(meetingArr[meetingID].teamName,teamArr[teamID].teamName)==0){// Meeting belong to that team
                            int hour,minute;
                            char *temp;
                            temp = strtok(meetingArr[meetingID].startTime,":");// Get the hour of start time
                            hour = atoi(temp);
                            temp = strtok(NULL,":");
                            minute = atoi(temp); // Get the minute of start time
                            // \/ Record to be printed
                            sprintf(sjt[nextPos],"Date: %s, Start: %02d:%02d, End: %02d:%02d, Team: %s, Project: %s\n",meetingArr[meetingID].startDate,hour,minute,hour+meetingArr[meetingID].length,minute,meetingArr[meetingID].teamName,teamArr[teamID].projectTitle);
                            sjtPlaced=0;
                            for(i=0;i<nextPos;i++){// Loop for checking the minimum hour, and place into two array
                                if(sjtMeetingLength[i]>meetingArr[meetingID].length){
                                    for(j=nextPos;j>=i;j--){// Find a smaller length in the array
                                        sjtMeetingLength[j]=sjtMeetingLength[j-1];// Move all result in array backward
                                        sjtID[j]=sjtID[j-1];
                                    }
                                    sjtID[i]=nextPos;// Store the record into array
                                    sjtMeetingLength[i]=meetingArr[meetingID].length;
                                    sjtPlaced=1;
                                    break;// stop search
                                }
                            }
                            if(!sjtPlaced){// Cannot find a smaller length with other;
                                sjtID[nextPos]=nextPos;
                                sjtMeetingLength[nextPos]=meetingArr[meetingID].length;
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