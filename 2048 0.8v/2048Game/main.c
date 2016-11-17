#include <stdio.h>
#include <stdlib.h>  //cls
#include <time.h>    //rand
#include <Windows.h> //cursor
#include <conio.h>   //_getch

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void gotoxy(int x, int y); //Ŀ��
void gameover(int score);  //���ӿ���
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
	int map[4][4] = { 0, };  //2048 ��
	int input = 0;  //�Է¹޴� ����
	int i = 0, j = 0, k = 0;
	int rand1 = 0;  //x�� ����
	int rand2 = 0;  //y�� ����
	int rand3 = 0;  //������ ���� ���� 1Ȥ�� 2
	int score = 0;  //���ھ�
	srand((unsigned)time(NULL));  //unsigned �� �ð����� �����õ� ����
	while (1)
	{
		while (1) {               //���ǿ� �ְ���� ������ ���� �ִٸ� �ٽõ�
			rand1 = rand() % 4;  //x��ǥ
			rand2 = rand() % 4;  //y��ǥ
			rand3 = rand() % 4;  //4���� ������
			if (rand3 > 0) {
				rand3 = 2;       //1~3 ������ 2
			}
			else if (rand3 == 0) {
				rand3 = 4;       //0 �ϰ�� 4 (4�п�1Ȯ��) 
			}
			if (map[rand1][rand2] == 0) {  //������ ������ break
				map[rand1][rand2] = rand3;
				if (rand3 == 1)      //1�̻���� 2�� �߰�
					score += 2;
				else if (rand3 == 2)  //2������� 4�� �߰�
					score += 4;
				break;
			}
		}

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				setcolor(map[j][i]);
				gotoxy(j * 10, i * 4);       printf("��������");
				gotoxy(j * 10, (i * 4) + 1); printf("��%5d", map[j][i]);
				gotoxy(j * 10, (i * 4) + 2); printf("��������");
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy(0, 16); printf("��������������������������������������");
		gotoxy(0, 17); printf("��2048 GAME �� score           %5d ", score);
		gotoxy(0, 18); printf("��������������������������������������");
		input = _getch(); //ù��° Ư��Ű �Է�Ȯ��
		if (input == 0xe0 || input == 0) { // Ư��Ű �Է� Ȯ��
			input = _getch(); //�ι�° Ư��Ű ����Ű �Է� 
			switch (input) {
			case UP:
				for (i = 0; i < 4; i++) {
					for (k = 0; k < 4; k++) {
						for (j = 1; j < 4; j++) { //ù��° �б� /  ���̿� 0�� �����ʰ�(����ȭ �ȵ�)
							if (map[i][j - 1] == 0) {
								map[i][j - 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
					for (j = 1; j < 4; j++) { //������ ���� ��ġ�� �Է� ���� ������� �ؾ��� �ι� �������� ����
						if (map[i][j - 1] == map[i][j]) {
							map[i][j - 1] += map[i][j];
							map[i][j] = 0;
						}
					}
					for (k = 0; k < 4; k++) { //�ι�° �б� / ���ļ� ���� 0���� �� �ſ�� ���Ͽ� �б� (����ȭ �ȵ�)
						for (j = 1; j < 4; j++) {
							if (map[i][j - 1] == 0) {
								map[i][j - 1] = map[i][j];
								map[i][j] = 0;
							}
						}
					}
				}
				break; //left�� x y �� �ٲ㼭  down �� 3��° for ���� ���� right �� down ���� x y �� �ٲ۴�

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
				printf("����׿�");
			}
		}
		for (i = 0, k = 0; i < 4; i++) {  //i��k �����ʱ�ȭ
			for (j = 0; j < 4; j++) {     //4*4 ������
				if (map[i][j] != 0)k++;   //0�̾ƴ϶�� k++
			}
		}
		if (k == 16) gameover(score);
		system("cls");
	}
}

void gameover(int score)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy(0, 16); printf("���ӿ����Դϴ�.                         \n");
	gotoxy(0, 17); printf("��������������������������������������");
	gotoxy(0, 18); printf("��Game Over �� your score      %5d ", score);
	gotoxy(0, 19); printf("��������������������������������������");
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

void gotoxy(int x, int y)  //Ŀ�� �̵�
{
	COORD pos = { x ,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
