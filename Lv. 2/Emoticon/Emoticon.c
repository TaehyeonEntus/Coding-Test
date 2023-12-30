#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int sale;
} Emoticon;

// ���ε� ������ ����ϴ� �Լ�
int calc_sale(int price, int sale) {
    return (price * (100 - sale)) * 0.01;
}

// �����, �� üũ �Լ�
int* check(int** users, size_t users_len, Emoticon emoticons[], size_t emoticons_len) {
    int membership = 0;
    int money = 0;

    // ���� �Ҵ�
    int* wallet = (int*)malloc(users_len * sizeof(int));

    // �迭 �ʱ�ȭ
    for (size_t i = 0; i < users_len; i++) {
        wallet[i] = 0;
    }

    // �̸�Ƽ�� ���Ͽ� ���� ����� ���� �ݾ� ���
    for (size_t i = 0; i < emoticons_len; i++) {
        for (size_t j = 0; j < users_len; j++) {
            if (users[j][0] <= emoticons[i].sale)
                wallet[j] += calc_sale(emoticons[i].price, emoticons[i].sale);
        }
    }

    // ����� ���ο� ��ü ���� �ݾ� Ȯ��
    for (size_t i = 0; i < users_len; i++) {
        if (users[i][1] <= wallet[i])
            membership++;
        else
            money += wallet[i];
    }

    // �迭 �޸� ����
    free(wallet);

    // ����� ������ �迭 ���� �Ҵ�
    int* answer = (int*)malloc(sizeof(int) * 2);
    answer[0] = membership;
    answer[1] = money;

    return answer;
}

void exploreCombinations(Emoticon e[], size_t e_len, int** users, size_t u_len, size_t index, int* result, int* bestResult) {
    int* tempResult = check(users, u_len, e, e_len);

    // 1���� : �����, 2���� : �ݾ�
    if (tempResult[0] > bestResult[0] || (tempResult[0] == bestResult[0] && tempResult[1] > bestResult[1])) {
        bestResult[0] = tempResult[0];
        bestResult[1] = tempResult[1];
    }

    free(tempResult);

    if (index == e_len) {
        // ���ȣ�� ��
        return;
    }

    // �̸�Ƽ�� ������
    for (int sale = 1; sale <= 4; sale++) {
        e[index].sale = sale * 10;
        exploreCombinations(e, e_len, users, u_len, index + 1, result, bestResult);
    }
}

// users_rows�� 2���� �迭 users�� �� ����, users_cols�� 2���� �迭 users�� �� �����Դϴ�.
// emoticons_len�� �迭 emoticons�� �����Դϴ�.
int* solution(int** users, size_t users_rows, size_t users_cols, int emoticons[], size_t emoticons_len) {
    Emoticon* emo = (Emoticon*)malloc(emoticons_len * sizeof(Emoticon));
    for (size_t i = 0; i < emoticons_len; i++) {
        emo[i].price = emoticons[i];
        emo[i].sale = 0;
    }

    // ����� ������ �迭 �ʱ�ȭ
    int* result = (int*)malloc(sizeof(int) * 2);
    result[0] = 0;
    result[1] = 0;

    // ���� ���� ����ʰ� ��ü �ݾ��� ������ �迭 �ʱ�ȭ
    int* bestResult = (int*)malloc(sizeof(int) * 2);
    bestResult[0] = 0;
    bestResult[1] = 0;

    // ��ø �ݺ��� ��� ��� �Լ��� ȣ���Ͽ� ������ ��� ���� Ž��
    exploreCombinations(emo, emoticons_len, users, users_rows, 0, result, bestResult);

    free(emo);
    free(result);

    return bestResult;
}
