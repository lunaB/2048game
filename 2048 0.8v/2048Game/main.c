#include <stdio.h>
#include <stdlib.h>  //cls
#include <time.h>    //rand
#include <Windows.h> //cursor
#include <conio.h>   //_getch

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void gotoxy(int x, int y); //커서
void gameover(int score);  //게임오버
void setcolor(int num);

enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY_BLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKY_BLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE
};

int main(void)
{
	system("cls");
	int map[4][4] = { 0, };  //2048 맵
	int input = 0;  //입력받는 변수
	int i = 0, j = 0, k = 0;
	int rand1 = 0;  //x축 랜덤
	int rand2 = 0;  //y축 랜덤
	int rand3 = 0;  //생성될 숫자 결정 1혹은 2
	int score = 0;  //스코어
	srand((unsigned)time(NULL));  //unsigned 형 시간으로 랜덤시드 생성
	while (1)
	{
		while (1) {               //조건에 넣고싶은 공간에 값이 있다면 다시돔
			rand1 = rand() % 4;  //x좌표
			rand2 = rand() % 4;  //y좌표
			rand3 = rand() % 4;  //4가지 경우생성
			if (rand3 > 0) {
				rand3 = 2;       //1~3 까지는 2
			}
			else if (rand3 == 0) {
				rand3 = 4;       //0 일경우 4 (4분에1확률) 
			}
			if (map[rand1][rand2] == 0) {  //조건이 맞으면 break
				map[rand1][rand2] = rand3;
				if (rand3 == 1)      //1이생기면 2점 추가
					score += 2;
				else if (rand3 == 2)  //2가생기면 4점 추가
					score += 4;
				break;
			}
		}

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				setcolor(map[j][i]);
				gotoxy(j * 10, i * 4);       printf("┌──┐");
				gotoxy(j * 10, (i * 4) + 1); printf("│%5d", map[j][i]);
				gotoxy(j * 10, (i * 4) + 2); printf("└──┘");
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(0, 16); printf("┌─────┬───────────┐");
		gotoxy(0, 17); printf("│2048 GAME │ score           %5d ", score);
		gotoxy(0, 18); printf("└─────┴───────────┘");
		input = _getch(); //첫번째 특수키 입력확인
		if (input == 0xe0 || input == 0) { // 특수키 입력 확인
			input = _getch(); //두번째 특수키 방향키 입력 
			switch (input) {
			case UP:
				for (i = 0; i < 4; i++) {
					for (k = 0; k < 4; k++) {
						for (j = 1; j < 4; j++) { //첫번째 밀기 /  사이에 0이 들어가지않게(최적화 안됨)
							if (map[i][j - 1] == 0) {
								map[i][j - 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
					for (j = 1; j < 4; j++) { //인접한 수와 합치기 입력 받은 방향부터 해야지 두번 합쳐지지 않음
						if (map[i][j - 1] == map[i][j]) {
							map[i][j - 1] += map[i][j];
							map[i][j] = 0;
						}
					}
					for (k = 0; k < 4; k++) { //두번째 밀기 / 합쳐서 생긴 0공간 을 매우기 위하여 밀기 (최적화 안됨)
						for (j = 1; j < 4; j++) {
							if (map[i][j - 1] == 0) {
								map[i][j - 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
				}
				break; //left는 x y 만 바꿔서  down 은 3번째 for 문을 반전 right 는 down 에서 x y 를 바꾼다

					   //---------------------------------------------------

			case DOWN:
				for (i = 0; i < 4; i++) {
					for (k = 0; k < 4; k++) {
						for (j = 2; j >= 0; j--) {
							if (map[i][j + 1] == 0) {
								map[i][j + 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
					for (j = 2; j >= 0; j--) {
						if (map[i][j + 1] == map[i][j]) {
							map[i][j + 1] += map[i][j];
							map[i][j] = 0;
						}
					}
					for (k = 0; k < 4; k++) {
						for (j = 2; j >= 0; j--) {
							if (map[i][j + 1] == 0) {
								map[i][j + 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
				}
				break;

				//---------------------------------------------------------

			case LEFT:
				for (i = 0; i < 4; i++) {
					for (k = 0; k < 4; k++) {
						for (j = 1; j < 4; j++) {
							if (map[j - 1][i] == 0) {
								map[j - 1][i] = map[j][i];
								map[j][i] = 0;
							}
						}
					}
					for (j = 1; j < 4; j++) {
						if (map[j - 1][i] == map[j][i]) {
							map[j - 1][i] += map[j][i];
							map[j][i] = 0;
						}
					}
					for (k = 0; k < 4; k++) {
						for (j = 1; j < 4; j++) {
							if (map[j - 1][i] == 0) {
								map[j - 1][i] = map[j][i];
								map[j][i] = 0;
							}
						}
					}
				}
				break;

				//----------------------------------------------------------

			case RIGHT:
				for (i = 0; i < 4; i++) {
					for (k = 0; k < 4; k++) {
						for (j = 2; j >= 0; j--) {
							if (map[j + 1][i] == 0) {
								map[j + 1][i] = map[j][i];
								map[j][i] = 0;
							}
						}
					}
					for (j = 2; j >= 0; j--) {
						if (map[j + 1][i] == map[j][i]) {
							map[j + 1][i] += map[j][i];
							map[j][i] = 0;
						}
					}
					for (k = 0; k < 4; k++) {
						for (j = 2; j >= 0; j--) {
							if (map[j + 1][i] == 0) {
								map[j + 1][i] = map[j][i];
								map[j][i] = 0;
							}
						}
					}
				}
				break;
			default:
				printf("디버그용");
			}
		}
		for (i = 0, k = 0; i < 4; i++) {  //i와k 동시초기화
			for (j = 0; j < 4; j++) {     //4*4 돌리기
				if (map[i][j] != 0)k++;   //0이아니라면 k++
			}
		}
		if (k == 16) gameover(score);
		system("cls");
	}
}

void gameover(int score)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(0, 16); printf("게임오버입니다.                         \n");
	gotoxy(0, 17); printf("┌─────┬───────────┐");
	gotoxy(0, 18); printf("│Game Over │ your score      %5d ", score);
	gotoxy(0, 19); printf("└─────┴───────────┘");
	system("pause");
	main();
}

void setcolor(int num) 
{
	switch (num) {
	case 0: 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK); break;
	case 2:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN); break;
	case 4:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW); break;
	case 8:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE); break;
	case 16:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED); break;
	case 32:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), VIOLET); break;
	case 64:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GREEN); break;
	case 128:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_SKY_BLUE); break;
	case 256:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_YELLOW); break;
	case 512:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_GREEN); break;
	case 1024:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_VIOLET); break;
	case 2048:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SKY_BLUE); break;

	}
}

void gotoxy(int x, int y)  //커서 이동
{
	COORD pos = { x ,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
