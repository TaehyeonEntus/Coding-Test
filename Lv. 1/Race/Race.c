#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 10

//i등과 i-1등을 변경하는 함수
void call(char** array, int i){
    char buf[MAX_NAME_LEN];
    strcpy(buf,array[i-1]);
    strcpy(array[i-1],array[i]);
    strcpy(array[i],buf);
}

char** solution(const char* players[], size_t players_len, const char* callings[], size_t callings_len) { 
    
    //동적할당
    char** answer = (char**)malloc(players_len * sizeof(char*));
    for (int i = 0; i < players_len; i++){  
        answer[i] = (char*)malloc(MAX_NAME_LEN * sizeof(char)); 
        strcpy(answer[i],players[i]);
    }
    
    for (int i = 0; i<callings_len; i++){
        for (int j = 1; j<players_len; j++){
            if (!strcmp(answer[j],callings[i])){
                call(answer,j);
                break;
            }
        }
    }

    return answer;
}