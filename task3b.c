#include <stdio.h>

int main(){
    //
    // File name detection, prevent using existing file
    FILE *file;
    char filename[] = "Schelde_SJF_00.txt";
    int indexD1 = 0;
    int indexD2 = 0;
    int index = 1;
    for (int i = 0; i < 100; i++)
    {
        indexD2 = index/10;
        indexD1 = index-indexD2*10;
        char temp[] = "0";
        sprintf(temp,"%d",indexD2);
        filename[12]=temp[0];
        sprintf(temp,"%d",indexD1);
        filename[13]=temp[0];
        if (file=fopen(filename,"r")){
            fclose(file);
            index++;
        }
        else{
            break;
        }
    }
    // Output: filename
    printf("A: %s",filename);
    
    
    return 0;
}
