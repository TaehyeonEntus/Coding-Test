#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int sale;
} Emoticon;

// 할인된 가격을 계산하는 함수
int calc_sale(int price, int sale) {
    return (price * (100 - sale)) * 0.01;
}

// 멤버쉽, 돈 체크 함수
int* check(int** users, size_t users_len, Emoticon emoticons[], size_t emoticons_len) {
    int membership = 0;
    int money = 0;

    // 동적 할당
    int* wallet = (int*)malloc(users_len * sizeof(int));

    // 배열 초기화
    for (size_t i = 0; i < users_len; i++) {
        wallet[i] = 0;
    }

    // 이모티콘 세일에 따라 사용자 지불 금액 계산
    for (size_t i = 0; i < emoticons_len; i++) {
        for (size_t j = 0; j < users_len; j++) {
            if (users[j][0] <= emoticons[i].sale)
                wallet[j] += calc_sale(emoticons[i].price, emoticons[i].sale);
        }
    }

    // 멤버십 여부와 전체 지불 금액 확인
    for (size_t i = 0; i < users_len; i++) {
        if (users[i][1] <= wallet[i])
            membership++;
        else
            money += wallet[i];
    }

    // 배열 메모리 해제
    free(wallet);

    // 결과를 저장할 배열 동적 할당
    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = membership;
    answer[1] = money;

    return answer;
}

void exploreCombinations(Emoticon e[], size_t e_len, int** users, size_t u_len, size_t index, int* result, int* bestResult) {
    int* tempResult = check(users, u_len, e, e_len);

    // 1순위 : 멤버십, 2순위 : 금액
    if (tempResult[0] > bestResult[0] || (tempResult[0] == bestResult[0] && tempResult[1] > bestResult[1])) {
        bestResult[0] = tempResult[0];
        bestResult[1] = tempResult[1];
    }

    free(tempResult);

    if (index == e_len) {
        // 재귀호출 끝
        return;
    }

    // 이모티콘 할인율
    for (int sale = 1; sale <= 4; sale++) {
        e[index].sale = sale * 10;
        exploreCombinations(e, e_len, users, u_len, index + 1, result, bestResult);
    }
}

// users_rows는 2차원 배열 users의 행 길이, users_cols는 2차원 배열 users의 열 길이입니다.
// emoticons_len은 배열 emoticons의 길이입니다.
int* solution(int** users, size_t users_rows, size_t users_cols, int emoticons[], size_t emoticons_len) {
    Emoticon* emo = (Emoticon*)malloc(emoticons_len * sizeof(Emoticon));
    for (size_t i = 0; i < emoticons_len; i++) {
        emo[i].price = emoticons[i];
        emo[i].sale = 0;
    }

    // 결과를 저장할 배열 초기화
    int* result = (int*)malloc(sizeof(int) * 2);
    result[0] = 0;
    result[1] = 0;

    // 가장 높은 멤버십과 전체 금액을 저장할 배열 초기화
    int* bestResult = (int*)malloc(sizeof(int) * 2);
    bestResult[0] = 0;
    bestResult[1] = 0;

    // 중첩 반복문 대신 재귀 함수를 호출하여 가능한 모든 조합 탐색
    exploreCombinations(emo, emoticons_len, users, users_rows, 0, result, bestResult);

    free(emo);
    free(result);

    return bestResult;
}
