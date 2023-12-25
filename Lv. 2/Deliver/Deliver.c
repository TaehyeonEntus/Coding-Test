#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// deliveries_len�� �迭 deliveries�� �����Դϴ�.
// pickups_len�� �迭 pickups�� �����Դϴ�.

int array_sum(int* array, int n) {   //�迭 ���ϱ� (start to end)
    int arraySum = 0;
    for (int i = 0; i < n; i++) {
        arraySum += array[i];
    }
    return arraySum;
}

long long last_home_distance(int* deliver, int* pickup, int n) {   //Ʈ���� �ٳ�� ���� �� �� �Ÿ�
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
    typedef struct { //Ʈ�� ����ü
        int full_box;
        int empty_box;
    } truck_struct;

    typedef struct { //�� ����ü
        int* deliver;
        int* pickup;
    } home_struct;

    truck_struct truck = { 0,0 };                      //�� �� ����, �� ����
    home_struct home = { deliveries, pickups };      //���, �Ⱦ�
    int total_deliver = array_sum(home.deliver, n);  //����ؾ� �� ���ڵ�
    int total_pickup = array_sum(home.pickup, n);    //�Ⱦ��ؾ� �� ���ڵ�
    distance = last_home_distance(home.deliver, home.pickup, n);
    while (!((total_deliver == 0) && (total_pickup == 0))) {
        truck.full_box = 0;     //Ʈ�� û���ϰ�
        truck.empty_box = 0;

        distance = last_home_distance(home.deliver, home.pickup, distance); //�׺���̼� ���
        answer += 2 * distance; //�Ÿ� ���

        //����� �ڽ� ���
        if (total_deliver >= cap) {
            truck.full_box = cap;
            total_deliver -= cap;
        }
        else {
            truck.full_box = total_deliver;
            total_deliver = 0;
        }

        //�Ⱦ��� �ڽ� ���
        if (total_pickup >= cap)
            total_pickup -= cap;
        else
            total_pickup = 0;

        // ���������� ���ʴ�� ���
        for (int i = distance - 1; i >= 0; i--) {
            if ((truck.full_box > 0) && (home.deliver[i] > 0)) {    // �ڽ� ����, ��� ���� Ȯ��
                if (truck.full_box >= home.deliver[i]) {            // �ڽ� >= ���
                    truck.full_box -= home.deliver[i];
                    home.deliver[i] = 0;
                }
                else {                                            // �ڽ� < ���
                    home.deliver[i] -= truck.full_box;
                    truck.full_box = 0;
                }
                if (truck.full_box == 0)
                    break;
            }
        }

        // ���������� ���ʴ�� �Ⱦ�
        for (int i = distance - 1; i >= 0; i--) {
            if ((truck.empty_box < cap) && (home.pickup[i] > 0)) {  // ���� ����, �Ⱦ� ���� Ȯ��
                if ((truck.empty_box + home.pickup[i]) <= cap) {    // �� ���� >= �Ⱦ�
                    truck.empty_box += home.pickup[i];
                    home.pickup[i] = 0;
                }
                else {                                            // �� ���� < �Ⱦ�
                    home.pickup[i] -= (cap - truck.empty_box);
                    truck.empty_box = cap;
                }
                if (truck.empty_box == cap)
                    break;
            }
        }
    }
    return answer;
}
