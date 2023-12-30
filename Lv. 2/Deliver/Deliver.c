#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int price;
    int sale;
} emoticon;

int calc_sale(int price, int sale) {
    return (price * (100 - sale)) / 100;
}

int* check(int** u, size_t u_len, emoticon e[], size_t e_len) {
    int membership = 0;
    int money = 0;

    int wallet[u_len];
    for (int i = 0; i < u_len; i++) {
        wallet[i] = 0;
    }

    for (int i = 0; i < e_len; i++) {
        for (int j = 0; j < u_len; j++) {
            if (u[j][0] <= e[i].sale)
                wallet[j] += calc_sale(e[i].price, e[i].sale);
        }
    }

    for (int i = 0; i < u_len; i++) {
        if (u[i][1] <= wallet[i])
            membership++;
        else
            money += wallet[i];
    }

    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = membership;
    answer[1] = money;

    return answer;
}

// 정수로 할인율 계산
int calculateSale(int sale) {
    return sale * 10; // 10, 20, 30, 40으로 변환
}

void printEmoticons(emoticon e[], size_t e_len) {
    printf("Emoticons: ");
    for (size_t i = 0; i < e_len; i++) {
        printf("(%d, %d) ", e[i].price, e[i].sale);
    }
    printf("\n");
}

void exploreCombinations(emoticon e[], size_t e_len, int** users, size_t u_len, size_t index, int* result) {
    int* tempResult = check(users, u_len, e, e_len);

    // 현재 결과가 더 나쁜 경우는 무시
    if (tempResult[0] < result[0] || (tempResult[0] == result[0] && tempResult[1] < result[1])) {
        free(tempResult);
        return;
    }

    // 현재 결과가 더 좋은 경우 갱신
    result[0] = tempResult[0];
    result[1] = tempResult[1];
    free(tempResult);

    if (index == e_len) {
        // Base case: 마지막 이모티콘까지 조합을 정했을 때
        return;
    }

    // 디버깅을 위한 출력 코드
    printEmoticons(e, e_len);

    // 현재 이모티콘의 세일을 10, 20, 30, 40 중 하나로 정함
    for (int sale = 1; sale <= 4; sale++) {
        e[index].sale = calculateSale(sale);
        exploreCombinations(e, e_len, users, u_len, index + 1, result);
    }
}


// users_rows는 2차원 배열 users의 행 길이, users_cols는 2차원 배열 users의 열 길이입니다.
// emoticons_len은 배열 emoticons의 길이입니다.
int* solution(int** users, size_t users_rows, size_t users_cols, int emoticons[], size_t emoticons_len) {
    emoticon emo[emoticons_len];
    for (size_t i = 0; i < emoticons_len; i++) {
        emo[i].price = emoticons[i];
        emo[i].sale = 0;
    }

    // 결과를 저장할 배열 초기화
    int* result = (int*)malloc(sizeof(int) * 2);

    result[0] = 0;
    result[1] = 0;

    // 중첩 반복문 대신 재귀 함수를 호출하여 가능한 모든 조합을 탐색
    exploreCombinations(emo, emoticons_len, users, users_rows, 0, result);

    return result;
}

int main() {
    int emoticon_prices[] = { 1300, 1500, 1600, 4900 };
    int users_data[][2] = { {40, 2900}, {23, 10000}, {11, 5200}, {5, 5900}, {40, 3100}, {27, 9200}, {32, 6900} };

    // 2차원 배열을 동적으로 할당
    size_t users_rows = sizeof(users_data) / sizeof(users_data[0]);
    size_t users_cols = sizeof(users_data[0]) / sizeof(users_data[0][0]);
    int** users = (int**)malloc(users_rows * sizeof(int*));
    for (size_t i = 0; i < users_rows; i++) {
        users[i] = (int*)malloc(users_cols * sizeof(int));
        for (size_t j = 0; j < users_cols; j++) {
            users[i][j] = users_data[i][j];
        }
    }

    size_t emoticons_len = sizeof(emoticon_prices) / sizeof(emoticon_prices[0]);

    int* result = solution(users, users_rows, users_cols, emoticon_prices, emoticons_len);

    // 결과값 출력
    printf("[%d, %d]\n", result[0], result[1]);

    // 메모리 해제
    for (size_t i = 0; i < users_rows; i++) {
        free(users[i]);
    }
    free(users);
    free(result);

    return 0;
}
