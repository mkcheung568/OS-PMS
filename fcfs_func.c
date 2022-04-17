
////function about FCFS not include print out report


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


    for(int row=0; row<100; row++){ // find the marr row until the row is empty

        if(strlen(marr[row].team) !=0){
        crow++;
        }else{
  
            break;  
  
      } 
    }

          //sorting by month
      for(int i=0;i<crow;++i){ //put the month to the mon array
       
        sscanf(marr[i].date, "%d-%d-%d",&year[i],&mon[i],&day[i]);
  
      }

       //bubble sorting , sort by month
       for (int i = 0; i < crow-1; i++){  
        for (int j = 0; j < crow -1- i; j++){
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
      for(int i=0;i<crow;++i){ //put the day value from date array to the day array
        sscanf(marr[i].date, "%d-%d-%d",&year[i],&mon[i],&day[i]);
  
      }

    
       //bubble sorting , sort by day
       for (int i = 0; i < crow-1; i++){  
        for (int j = 0; j < crow -1- i; j++){
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
      for(int i=0;i<crow;++i){   //put the month to the mon array
        sscanf(marr[i].time, "%d:%d",&hour[i],&minutes[i]);
  
      }

    
       //bubble sorting , sort by time
       for (int i = 0; i < crow-1; i++){  
        for (int j = 0; j < crow -1- i; j++){
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
