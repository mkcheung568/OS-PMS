#include <stdio.h>
#include <string.h>

// Example of using structures to get the data and compare

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
    struct Team team[5];
    strcpy(team[0].teamName,"Team_A");
    strcpy(team[0].projectTitle,"Project_A");
    strcpy(team[0].Member[0],"Alan");
    strcpy(team[0].Member[1],"Cathy");
    strcpy(team[0].Member[2],"Fanny");
    strcpy(team[0].Member[3],"Helen");
    strcpy(team[1].teamName,"TB");
    strcpy(team[1].projectTitle,"Prototype GameOver");
    strcpy(team[1].Member[0],"Cathy");
    strcpy(team[1].Member[1],"Helen");

    struct Meeting meeting[10];
    strcpy(meeting[0].teamName,"Team_A");
    strcpy(meeting[0].startDate,"2022-04-25");
    strcpy(meeting[0].startTime,"09:00");
    meeting[0].length=2;

    strcpy(meeting[1].teamName,"TB");
    strcpy(meeting[1].startDate,"2022-04-28");
    strcpy(meeting[1].startTime,"10:00");
    meeting[1].length=3;

    strcpy(meeting[2].teamName,"Team_A");
    strcpy(meeting[2].startDate,"2022-04-29");
    strcpy(meeting[2].startTime,"14:00");
    meeting[2].length=4;

    strcpy(meeting[3].teamName,"TB");
    strcpy(meeting[3].startDate,"2022-05-01");
    strcpy(meeting[3].startTime,"9:00");
    meeting[3].length=1;

    strcpy(meeting[4].teamName,"TB");
    strcpy(meeting[4].startDate,"2022-04-30");
    strcpy(meeting[4].startTime,"15:00");
    meeting[4].length=3;

    int i,j;
    for (i=0;i<2;i++){
        printf("Team Name: %s below\n\n",team[i].teamName);
        for (j=0;j<5;j++){
            if (strcmp(team[i].teamName,meeting[j].teamName)==0){
                printf("Team Name: %s, Project Name: %s, Team Leader: %s, Meeting Start Time: %s, Meeting Date: %s, Length: %d\n",team[i].teamName,team[i].projectTitle,team[i].Member[0],meeting[j].startTime,meeting[j].startDate,meeting[j].length);
            }
        }
        printf("\n");
    }
}
