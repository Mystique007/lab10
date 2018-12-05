#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 128
void tempread(char *device, int verbose);
void usage();

int main(int argc, char **argv){
    char *device =  "28-0118424232ff";
    int verbose = 0;

    argc--;
    argv++;

    while(argc > 0){
        printf("%d %s\n", argc, argv[0]);
        if(!strcmp("-v", argv[0])){
            verbose = 1;
        }
        else if(!strcmp("-d", argv[0])){
            argc--;
            argv++;
            if(argc == 0){
                usage();
            }
            device = argv[0];
        }
        else{
            usage();
        }
        argc--;
        argv++;
    }
    tempread(device, verbose);
    return 0;
}

void tempread(char *device, int verbose){
    int fd;
    char ch;
    char buff[BUFFSIZE] = {'\0'};
    char directory[] = "/sys/bus/w1/devices/";
    char temparature[6] = {'\0'};
    char *file_name = malloc(strlen(directory) + strlen(device)+ 11);
    strcat(file_name, directory);
    strcat(file_name, device);
    strcat(file_name, "/w1_slave");
//    printf("%s\n\n", file_name);

    char *fname = "/sys/bus/w1/devices/28-0118424232ff/w1_slave";

    fd = open(file_name, O_RDONLY);

    if(fd == -1){
        printf("Can't open the file %s\n", file_name);
        exit(1);
    }
    else{
        
        int ret = read(fd, buff, BUFFSIZE);
        if(ret == -1){
            printf("Can't read file\n");
            exit(1);
        }

        char *ptr = buff;
        int i, j;
        for(i = 0; i < strlen(buff); ++i){
            if(buff[i] == 't'){
                for(j = 0; j < sizeof(temparature) - 1; ++j){
                    temparature[j] = buff[i+2+j];
                }
                break;
            }
        }
       /* while(ptr){
            if(*ptr == 't'){
                int i = 0;
                ++ptr;
                while(++ptr){
                    temparature[i++] = *ptr;
                    printf("%c", *ptr);
                }
                break;
            }
            ++ptr;
        }*/
    }
    printf("%s\n", temparature);
    if(verbose){
        printf("%s\n", buff);
    }

    close(fd);
    
}

void usage(){
    printf("Wrong commad line arguments are passed\n");
    printf("[Usage]: ./tempread [-v] [-d device_name]\n");
}
