   
    void fcfs_report(struct Meeting marr[100],struct Team arr[5]){

    int hour[8];
    int minutes[8];
    int duration[8];
    int endtime[8];
    char end[8][10];//end of the meeting
    int crow=0;
    char project[8][10];//for project name and team matching
    char namelist[8][10]={"Alan","Billy","Cathy","David","Eva","Fanny","Gary","Helen"};


    for(int row=0; row<100; row++){ // find the marr row until the row is empty

        if(strlen(marr[row].team) !=0){
        crow++;
        }else{
  
            break;  
  
      } 
    } 

     ///////////////////////////////print data to txt file /////////////////////////

    FILE *file; // set file variable
    char filename[] = "Schelde_FCFS_01.txt"; // temp file name
    int indexD1 = 0;// get 10 digit
    int indexD2 = 0;// get 1 digit
    int index = 0;
    for (int i = 0; i < 100; i++) // loop from 00 to 99
    {
        indexD2 = index/10; // get 10 digit
        indexD1 = index-indexD2*10; // get 1 digit
        char temp[] = "0"; // create empty string
        sprintf(temp,"%d",indexD2); // combine the string 
        filename[12]=temp[0]; // replace the temp file name
        sprintf(temp,"%d",indexD1); //combine the string 
        filename[13]=temp[0]; // replace the temp file name
        if (file==fopen(filename,"r")){ // open to test if the file exist
            fclose(file);
            index++;  // exist add one digit
        }
        else{ // no exist the file name is found
            break;
        }        
    }
    file = fopen(filename,"w");
    fprintf(file,"\n*** Project Meeting ***\n\n");
    fprintf(file,"Algorithm used: FCFS\n");
    fprintf(file,"Algorithm used: FCFS\n");
    fprintf(file,"Period: 2022-04-25 to 2022-04-27\n");
     fprintf(file,"Date                 Start            End             Team             Project        \n");
     fprintf(file,"================================================================================\n");






  
    ////// this part is for formating the the whole meeting from 2022-04-25 to 2022-04-27 //////////////////////

  for(int i=0;i<crow;++i){   //extract the hour value on time array
        sscanf(marr[i].time, "%d:%d",&hour[i],&minutes[i]);
        
      }

      for(int i=0;i<crow;++i){   //change the duration value to integer save in duration[] array 
        sscanf(marr[i].duration, "%d",&duration[i]);
      }
      

   
          for(int j=0;j<crow;j++){// add start hour and duration 

            endtime[j]=hour[j]+duration[j];
        

          }

       for(int j=0;j<crow;j++){ // resulting the end time in time format and save in end array,for fcfs report printing

            snprintf(end[j],sizeof(end),"%d:00",endtime[j]);
          
            
          }


     //for report printing team and project name matching
       for(int k=0;k<crow;k++){ 

           for(int n=0;n<5;n++){
                
  
                if( strcmp(marr[k].team,arr[n].tem) == 0){

                strcpy(project[k],arr[n].proj);
               
               
                }

           }

       }



            for(int i=0;i<crow; i++){

                  fprintf(file,"%s           %s           %s           %s           %s           \n",marr[i].date,marr[i].time,end[i],marr[i].team,project[i]);



              }

//fprintf(file,"===============================================================================\n");

//////////////////////     Each staff meeting output printing      ///////////////////////////////////////////////





//loop for separate each staff meeting 
for(int m=0; m<8;m++ ){ //loop for namelist
     fprintf(file,"================================================================================\n");
      fprintf(file,"Staff: %s\n\n",namelist[m]);
      fprintf(file,"Date                 Start            End             Team             Project        \n");
     fprintf(file,"================================================================================\n");
     for(int n=0;n<5;n++){ //loop for team struct,mathching the namelist with team struct member name
             
         if(strcmp(namelist[m],arr[n].leader) == 0 || strcmp(namelist[m],arr[n].mem1) == 0 || strcmp(namelist[m],arr[n].mem2) == 0 || strcmp(namelist[m],arr[n].mem3) == 0 ){
        
               for(int p=0;p<crow;p++){//loop for meeting struct find match with teams name
                    if(strcmp(arr[n].tem,marr[p].team) == 0){

                        fprintf(file,"%s           %s           %s           %s           %s           \n",marr[p].date,marr[p].time,end[p],arr[n].tem,arr[n].proj);
                       
                    }
               
              }
               

         }

     }
      
}


fprintf(file,"                               -End-                                        \n");

fclose(file);
printf("Printed. File name: %s.\n",filename);

       
}