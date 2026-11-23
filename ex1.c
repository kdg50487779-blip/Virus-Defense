//
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <wchar.h>
//#include <locale.h>
//
//#ifdef _WIN32
//#include <io.h>
//#include <fcntl.h>
//#endif
//
//#define SIZE 10
//#define MAX_TURN 10
//
//char map[SIZE][SIZE + 1] = {
//    "..........",
//    "...#...A..",
//    "...#.#....",
//    "...#......",
//    "....V.....",
//    "......#...",
//    "......#...",
//    ".B....#...",
//    "......C...",
//    ".........."
//};
//
//typedef struct VirusNode {
//    int row;
//    int col;
//    struct VirusNode* next;
//} VirusNode;
//
//VirusNode* head = NULL;
//VirusNode* tail = NULL;
//
//int score = 1000;
//int walls = 8;
//int lostHospitals = 0;
//
//// 연결 리스트에 바이러스 추가
//void addVirus(int row, int col)
//{
//    VirusNode* p = (VirusNode*)malloc(sizeof(VirusNode));
//
//    if (p == NULL) {
//        wprintf(L"\uBA54\uBAA8\uB9AC\uAC00 \uBD80\uC871\uD569\uB2C8\uB2E4.\n");
//        exit(1);
//    }
//
//    p->row = row;
//    p->col = col;
//    p->next = NULL;
//
//    if (tail == NULL)
//        head = p;
//    else
//        tail->next = p;
//
//    tail = p;
//}
//
//// 연결 리스트 메모리 해제
//void freeViruses(void)
//{
//    while (head != NULL) {
//        VirusNode* temp = head;
//        head = head->next;
//        free(temp);
//    }
//
//    tail = NULL;
//}
//
//// 게임 지도 출력
//void printMap(void)
//{
//    int r, c;
//
//    wprintf(L"\n     0 1 2 3 4 5 6 7 8 9\n");
//
//    for (r = 0; r < SIZE; r++) {
//        wprintf(L"%2d | ", r);
//
//        for (c = 0; c < SIZE; c++) {
//            wprintf(L"%lc ", (wchar_t)map[r][c]);
//        }
//
//        wprintf(L"\n");
//    }
//
//    wprintf(L". \uBE48\uCE78  # \uC7A5\uC560\uBB3C  V \uBC14\uC774\uB7EC\uC2A4  W \uBC29\uD654\uBCBD  A/B/C \uBCD1\uC6D0  X \uAC10\uC5FC\uB41C \uBCD1\uC6D0\n");
//}
//
//// 방화벽 설치
//void putWall(void)
//{
//    int r, c;
//
//    if (walls == 0) {
//        wprintf(L"\uB0A8\uC740 \uBC29\uD654\uBCBD\uC774 \uC5C6\uC2B5\uB2C8\uB2E4.\n");
//        return;
//    }
//
//    wprintf(L"\uBC29\uD654\uBCBD \uC124\uCE58 \uC88C\uD45C (\uD589 \uC5F4): ");
//    fflush(stdout);
//
//    if (scanf("%d %d", &r, &c) != 2) {
//        wprintf(L"\uC22B\uC790\uB97C \uC785\uB825\uD574\uC57C \uD569\uB2C8\uB2E4. \uAC8C\uC784\uC744 \uC885\uB8CC\uD569\uB2C8\uB2E4.\n");
//        freeViruses();
//        exit(1);
//    }
//
//    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
//        wprintf(L"\uC9C0\uB3C4 \uBC94\uC704\uB97C \uBC97\uC5B4\uB0AC\uC2B5\uB2C8\uB2E4.\n");
//        return;
//    }
//
//    if (map[r][c] != '.') {
//        wprintf(L"\uBE48 \uCE78\uC5D0\uB9CC \uC124\uCE58\uD560 \uC218 \uC788\uC2B5\uB2C8\uB2E4.\n");
//        return;
//    }
//
//    map[r][c] = 'W';
//    walls--;
//
//    wprintf(L"(%d,%d)\uC5D0 \uBC29\uD654\uBCBD\uC744 \uC124\uCE58\uD588\uC2B5\uB2C8\uB2E4.\n", r, c);
//}
//
//// 바이러스 감염 처리
//void infect(int r, int c)
//{
//    char tile;
//
//    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE)
//        return;
//
//    tile = map[r][c];
//
//    if (tile != '.' && tile != 'A' &&
//        tile != 'B' && tile != 'C')
//        return;
//
//    addVirus(r, c);
//
//    if (tile == '.') {
//        map[r][c] = 'V';
//    }
//    else {
//        map[r][c] = 'X';
//        lostHospitals++;
//
//        if (tile == 'A')
//            score -= 300;
//
//        if (tile == 'B')
//            score -= 200;
//
//        if (tile == 'C')
//            score -= 500;
//
//        wprintf(L"\n[\uACBD\uACE0] %lc\uBCD1\uC6D0\uC774 \uAC10\uC5FC\uB418\uC5C8\uC2B5\uB2C8\uB2E4! \uD604\uC7AC \uC810\uC218: %d\uC810\n",
//            (wchar_t)tile, score);
//    }
//}
//
//// 바이러스 확산
//void spreadVirus(void)
//{
//    int dr[4] = { -1, 1, 0, 0 };
//    int dc[4] = { 0, 0, -1, 1 };
//
//    VirusNode* p = head;
//    VirusNode* last = tail;
//
//    int i;
//
//    while (p != NULL) {
//        for (i = 0; i < 4; i++) {
//            infect(p->row + dr[i],
//                p->col + dc[i]);
//        }
//
//        if (p == last)
//            break;
//
//        p = p->next;
//    }
//}
//
//// 메인 함수
//int main(void)
//{
//    int turn = 1;
//    int choice;
//    int usedWall;
//
//    // Windows 콘솔 한글 출력
//#ifdef _WIN32
//    _setmode(_fileno(stdout), _O_U16TEXT);
//#else
//    setlocale(LC_ALL, "");
//#endif
//
//    addVirus(4, 4);
//
//    wprintf(L"===== \uBC14\uC774\uB7EC\uC2A4 \uB514\uD39C\uC2A4: \uCD5C\uD6C4\uC758 10\uD134 =====\n");
//    wprintf(L"\uBCD1\uC6D0 \uAC10\uC5FC \uC2DC A:-300, B:-200, C:-500\uC810\n");
//    wprintf(L"\uB9E4 \uD134 \uBC29\uD654\uBCBD\uC744 \uCD5C\uB300 1\uAC1C \uC124\uCE58\uD558\uACE0 \uB2E4\uC74C \uD134\uC744 \uC9C4\uD589\uD558\uC138\uC694.\n");
//
//    while (turn <= MAX_TURN && lostHospitals < 3) {
//
//        usedWall = 0;
//
//        while (1) {
//
//            wprintf(L"\n===== %d / %d \uD134 =====\n",
//                turn, MAX_TURN);
//
//            printMap();
//
//            wprintf(L"\uD604\uC7AC \uC810\uC218: %d | \uB0A8\uC740 \uBC29\uD654\uBCBD: %d\n",
//                score, walls);
//
//            wprintf(L"1. \uBC29\uD654\uBCBD \uC124\uCE58  2. \uB2E4\uC74C \uD134  0. \uC885\uB8CC\n\uC120\uD0DD: ");
//
//            fflush(stdout);
//
//            if (scanf("%d", &choice) != 1) {
//                wprintf(L"\uC22B\uC790 \uC785\uB825 \uC624\uB958\uB85C \uC885\uB8CC\uD569\uB2C8\uB2E4.\n");
//                freeViruses();
//                return 1;
//            }
//
//            if (choice == 0) {
//                freeViruses();
//                wprintf(L"\uAC8C\uC784\uC744 \uC885\uB8CC\uD588\uC2B5\uB2C8\uB2E4.\n");
//                return 0;
//            }
//
//            if (choice == 1) {
//
//                if (usedWall) {
//                    wprintf(L"\uD55C \uD134\uC5D0 \uBC29\uD654\uBCBD\uC740 1\uAC1C\uB9CC \uC124\uCE58\uD560 \uC218 \uC788\uC2B5\uB2C8\uB2E4.\n");
//                }
//                else {
//                    int before = walls;
//
//                    putWall();
//
//                    if (walls < before)
//                        usedWall = 1;
//                }
//            }
//            else if (choice == 2) {
//                spreadVirus();
//                break;
//            }
//            else {
//                wprintf(L"0, 1, 2 \uC911\uC5D0\uC11C \uC120\uD0DD\uD558\uC138\uC694.\n");
//            }
//        }
//
//        turn++;
//    }
//
//    printMap();
//
//    wprintf(L"\n===== \uAC8C\uC784 \uC885\uB8CC =====\n");
//
//    wprintf(L"\uCD5C\uC885 \uC810\uC218: %d / 1000\uC810\n",
//        score);
//
//    wprintf(L"\uC0DD\uC874 \uBCD1\uC6D0: %d / 3\uAC1C\n",
//        3 - lostHospitals);
//
//    if (score == 1000)
//        wprintf(L"\uB4F1\uAE09: S\n");
//
//    else if (score >= 800)
//        wprintf(L"\uB4F1\uAE09: A\n");
//
//    else if (score >= 500)
//        wprintf(L"\uB4F1\uAE09: B\n");
//
//    else if (score > 0)
//        wprintf(L"\uB4F1\uAE09: C\n");
//
//    else
//        wprintf(L"\uB4F1\uAE09: F\n");
//
//    freeViruses();
//
//    return 0;
//}
