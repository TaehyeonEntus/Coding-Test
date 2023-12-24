#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
int H, W;           //세로, 가로
int location[2];    //현재 위치

void find_start(char* park[]) {  //시작위치 찾기
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (park[i][j] == 'S') {
                H = i;
                W = j;
            }
        }
    }
}
void move(char* park[], char* routes[], int i) {     //시작위치 찾기
    char* direction_str = strtok(routes[i], " ");   //방향
    char direction = routes[i][0];                  //문자열을 문자형으로
    char* distance_str = strtok(NULL, " ");         //거리
    int distance = atoi(distance_str);              //문자열을 정수형으로
    switch (direction) {
    case 'E':
        for (int i = 1; i <= distance; i++) {
            if ((park[H][W + i] != 'O') && (park[H][W + i] != 'S')) {
                distance = 0;
                break;
            }
        }
        W += distance;
        break;
    case 'W':
        for (int i = 1; i <= distance; i++) {
            if ((park[H][W - i] != 'O') && (park[H][W - i] != 'S')) {
                distance = 0;
                break;
            }
        }
        W -= distance;
        break;
    case 'S':
        for (int i = 1; i <= distance; i++) {
            if ((park[H + i][W] != 'O') && (park[H + i][W] != 'S')) {
                distance = 0;
                break;
            }
        }
        H += distance;
        break;
    case 'N':
        for (int i = 1; i <= distance; i++) {
            if ((park[H - i][W] != 'O') && (park[H - i][W] != 'S')) {
                distance = 0;
                break;
            }
        }
        H -= distance;
        break;
    default:
        break;
    }
}
int* solution(const char* Const_park[], size_t park_len, const char* Const_routes[], size_t routes_len) {
    // park_len은 배열 park의 길이입니다.
    // routes_len은 배열 routes의 길이입니다.
    // 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* park[MAX_SIZE];
    char* routes[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        park[i] = (char*)malloc(MAX_SIZE * sizeof(char));
        routes[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    }
    for (int i = 0; i < park_len; i++) {
        strcpy(park[i], Const_park[i]);
    }
    for (int i = 0; i < routes_len; i++) {
        strcpy(routes[i], Const_routes[i]);
    }

    find_start(park);                  //시작위치 계산
    for (int i = 0; i < routes_len; i++) { //routes에 따라 실행
        move(park, routes, i);
    }

    int* answer = (int*)malloc(2 * sizeof(int));
    answer[0] = H; answer[1] = W;
    return answer;
}