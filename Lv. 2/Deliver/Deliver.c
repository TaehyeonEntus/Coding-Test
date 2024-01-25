#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// deliveries_len은 배열 deliveries의 길이입니다.
// pickups_len은 배열 pickups의 길이입니다.

int array_sum(int* array, int n) {   //배열 더하기 (start to end)
    int arraySum = 0;
    for (int i = 0; i < n; i++) {
        arraySum += array[i];
    }
    return arraySum;
}

long long last_home_distance(int* deliver, int* pickup, int n) {   //트럭이 다녀올 가장 먼 집 거리
    int distance = 0;
    for (int i = n - 1; i >= 0; i--) {
        if ((deliver[i] != 0) || (pickup[i]) != 0) {
            distance = i;
            break;
        }
    }
    return distance + 1;
}

long long solution(int cap, int n, int deliveries[], size_t deliveries_len, int pickups[], size_t pickups_len) {
    long long answer = 0;
    long long distance = 0;
    typedef struct { //트럭 구조체
        int full_box;
        int empty_box;
    } truck_struct;

    typedef struct { //집 구조체
        int* deliver;
        int* pickup;
    } home_struct;

    truck_struct truck = {0,0};                      //꽉 찬 상자, 빈 상자
    home_struct home = { deliveries, pickups };      //배달, 픽업
    int total_deliver = array_sum(home.deliver, n);  //배달해야 할 상자들
    int total_pickup = array_sum(home.pickup, n);    //픽업해야 할 상자들
    distance = last_home_distance(home.deliver, home.pickup, n); 
    while (!((total_deliver == 0) && (total_pickup == 0))) {
        truck.full_box = 0;     //트럭 청소하고
        truck.empty_box = 0;
        
        distance = last_home_distance(home.deliver, home.pickup, distance); //네비게이션 찍고
        answer += 2 * distance; //거리 계산
        
        //배송할 박스 계산
        if (total_deliver >= cap) {
            truck.full_box = cap;
            total_deliver -= cap;
        } else {
            truck.full_box = total_deliver;
            total_deliver = 0;
        }

        //픽업할 박스 계산
        if (total_pickup >= cap)
            total_pickup -= cap;
        else
            total_pickup = 0;

        // 마지막부터 차례대로 배달
        for (int i = distance-1; i >= 0; i--) {
            if ((truck.full_box > 0) && (home.deliver[i] > 0)) {    // 박스 여부, 배달 여부 확인
                if (truck.full_box >= home.deliver[i]) {            // 박스 >= 배달
                    truck.full_box -= home.deliver[i];
                    home.deliver[i] = 0;
                } else {                                            // 박스 < 배달
                    home.deliver[i] -= truck.full_box;
                    truck.full_box = 0;
                }
                if(truck.full_box == 0) 
                    break;
            }
        }

        // 마지막부터 차례대로 픽업
        for (int i = distance-1; i >= 0; i--) {
            if ((truck.empty_box < cap) && (home.pickup[i] > 0)) {  // 공간 여부, 픽업 여부 확인
                if ((truck.empty_box + home.pickup[i]) <= cap) {    // 빈 공간 >= 픽업
                    truck.empty_box += home.pickup[i];
                    home.pickup[i] = 0;
                } else {                                            // 빈 공간 < 픽업
                    home.pickup[i] -= (cap - truck.empty_box);
                    truck.empty_box = cap;
                }
                if(truck.empty_box == cap) 
                    break;
            }
        }
    }
    return answer;
}
