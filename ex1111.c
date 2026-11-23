#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//..

#define SIZE 10
#define MAX_TURN 10

// .: 빈칸, #: 장애물, V: 바이러스, W: 방화벽
// A/B/C: 병원, X: 감염된 병원
char board[SIZE][SIZE + 1] = {
    "..........",
    "...#...A..",
    "...#.#....",
    "...#......",
    "....V.....",
    "......#...",
    "......#...",
    ".B....#...",
    "......C...",
    ".........."
};

typedef struct VirusNode {
    int row;
    int col;
    struct VirusNode* next;
} VirusNode;

VirusNode* head = NULL;
VirusNode* tail = NULL;
int wallsLeft = 8;
int infectedHospitals = 0;

// 바이러스가 생긴 위치를 연결 리스트 끝에 추가
void addVirus(int row, int col)
{
    VirusNode* p = (VirusNode*)malloc(sizeof(VirusNode));
    if (p == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    p->row = row;
    p->col = col;
    p->next = NULL;

    if (head == NULL)
        head = p;
    else
        tail->next = p;
    tail = p;
}

// 게임 종료 시 연결 리스트 메모리 해제
void freeViruses(void)
{
    VirusNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

void printMap(void)
{
    int r, c;
    printf("\n     0 1 2 3 4 5 6 7 8 9\n");
    for (r = 0; r < SIZE; r++) {
        printf(" %d | ", r);
        for (c = 0; c < SIZE; c++)
            printf("%c ", board[r][c]);
        printf("\n");
    }
    printf(". 빈칸  # 장애물  V 바이러스  W 방화벽  A/B/C 병원  X 감염된 병원\n");
}

// 숫자가 아닌 입력이 남았을 때 버리기
void clearInput(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// 설치 성공 1, 실패 0
int putWall(void)
{
    int r, c;
    if (wallsLeft == 0) {
        printf("남은 방화벽이 없습니다.\n");
        return 0;
    }
    printf("방화벽 좌표 입력 (행 열): ");
    if (scanf("%d %d", &r, &c) != 2) {
        clearInput();
        printf("좌표는 숫자 2개로 입력하세요.\n");
        return 0;
    }
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
        printf("지도 밖의 좌표입니다.\n");
        return 0;
    }
    if (board[r][c] != '.') {
        printf("빈칸에만 설치할 수 있습니다.\n");
        return 0;
    }
    board[r][c] = 'W';
    wallsLeft--;
    printf("(%d, %d)에 방화벽을 설치했습니다.\n", r, c);
    return 1;
}

// 한 칸 감염 처리
void infect(int r, int c)
{
    char tile;
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE)
        return;
    tile = board[r][c];
    if (tile != '.' && tile != 'A' && tile != 'B' && tile != 'C')
        return;

    addVirus(r, c);
    if (tile == '.')
        board[r][c] = 'V';
    else {
        board[r][c] = 'X';
        infectedHospitals++;
        printf("[경고] %c병원이 감염되었습니다!\n", tile);
    }
}

// 현재 턴 시작 전 존재하던 바이러스에서만 확산
void spreadVirus(void)
{
    VirusNode* p = head;
    VirusNode* last = tail;
    while (p != NULL) {
        infect(p->row - 1, p->col);
        infect(p->row + 1, p->col);
        infect(p->row, p->col - 1);
        infect(p->row, p->col + 1);
        if (p == last)
            break;
        p = p->next;
    }
}

int main(void)
{
    int turn = 1;
    int choice;
    int usedWall;

    addVirus(4, 4);
    printf("=== 바이러스 디펜스: 2주 차 ===\n");

    while (turn <= MAX_TURN && infectedHospitals < 3) {
        usedWall = 0;
        while (1) {
            printf("\n===== %d / %d 턴 =====\n", turn, MAX_TURN);
            printMap();
            printf("남은 방화벽: %d | 생존 병원: %d/3\n", wallsLeft, 3 - infectedHospitals);
            printf("1. 방화벽 설치  2. 다음 턴  0. 종료\n선택: ");
            if (scanf("%d", &choice) != 1) {
                if (feof(stdin)) {
                    freeViruses();
                    return 0;
                }
                clearInput();
                printf("메뉴 번호를 입력하세요.\n");
                continue;
            }
            if (choice == 0) {
                freeViruses();
                return 0;
            }
            if (choice == 1) {
                if (usedWall)
                    printf("한 턴에 1개만 설치할 수 있습니다.\n");
                else if (putWall())
                    usedWall = 1;
            }
            else if (choice == 2) {
                spreadVirus();
                break;
            }
            else
                printf("0, 1, 2 중에서 선택하세요.\n");
        }
        turn++;
    }

    printMap();
    printf("\n게임 종료! 생존 병원: %d / 3\n", 3 - infectedHospitals);
    printf("병원별 점수 계산은 3주 차에 추가합니다.\n");
    freeViruses();
    return 0;
}
