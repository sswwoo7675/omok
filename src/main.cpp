#include <stdio.h> 
#include <Windows.h> //gotoxy()함수 구현위해 선언함
#void gotoxy(int x, int y); //커서이동함수include <conio.h> //getch()함수를 사용하기 위해 선언함

void draw_pan(void); //바둑판을 그리는 함수
void move_xy(char key);//방향키에 따른 좌표이동함수.
int push_stone(int stone[][16]); //돌을 놓는 함수. 
int start(); //게임시작함수
int win(int stone[][16]);//승리판독함수
int x = 15, y = 8; //처음 시작 출력좌표
int wb = 1;//1이면 흑돌차례 2이면 백돌차례

int main(void)
{
	printf("\t\t\t오목게임 (made by Seo ji Woo)\n\n");

	printf("조작방법 : →(오른쪽으로이동)\t←(왼쪽으로이동)\n\t   ↑(위로이동)\t\t↓(아래로이동)\n\t   스페이스(바둑돌놓기)\n\n");
	printf("Enter키를 입력하시면 게임이 시작됩니다\n");


	char ch = getch();

	if (ch == 13) {
		system("cls");
		for (;;)
		{
			if (start()) {
				x = 15;  //게임 다시 시작위해 좌표를 처음 시작 좌표로 초기화.
				y = 8;
				wb = 1;  //흑 시작으로 초기화
			}
			else {
				break;
			}
		}
	}
	system("pause");
	return 0;
}

int start()
{
	int stone[16][16] = { 0 };//원래 15*15 공간이나 코딩의 편리를 위해 16*16의 배열공간을 생성
	char key = 0;
	draw_pan(); //바둑판 생성
	gotoxy(1, 20); //상태출력하는 좌표로 이동
	printf("이제 흑돌 차례입니다.");
	gotoxy(x, y); //중앙으로 커서이동
	for (;;) {
		gotoxy(x, y);   //지금 위치로 이동.
		key = getch();  //키를 입력받음(입력받을때까지 프로그램 대기)
		if (key == 75 || key == 77 || key == 72 || key == 80) { //방향키를 입력하면
			move_xy(key); //키 입력에 따른 xy좌표변경
			gotoxy(x, y); //커서위치이동
		}
		else if (key == 32) { //스페이스바 입력시
			if (push_stone(stone)) { //돌을 정상적으로 놓았을 경우.
				if (win(stone)) { //승리가 결정나면?
					gotoxy(1, 20);
					if (wb == 1) {
						printf("                                                         "); //해당 위치 출력 부분 clear
						gotoxy(1, 20);,
						printf("흑의 승리입니다.\n");
					}
					else {
						printf("                                                         "); //해당 위치 출력 부분 clear
						gotoxy(1, 20);
						printf("백의 승리입니다.\n");
					}
					printf("게임을 다시 하시겠습니까? 아니면 종료 하시겠습니까?\n다시 하려면 y 종료 하려면 아무키나 누르십시오.");
					key = getch();  //키를 입력받음(입력받을때까지 프로그램 대기)
					if (key == 121) {
						system("cls"); //다시 게임 시작을 위해 화면을 지움
						return 1; //1을 반환후 함수 종료
					}
					else
					{
						return 0; //0을 반환후 함수 종료
					}
				}
				else {		//승리가 결정나지 않으면
					if (wb == 1) {
						wb = 2;
						gotoxy(1, 20);
						printf("이제 백돌 차례입니다.");
					}
					else {
						wb = 1;
						gotoxy(1, 20);
						printf("이제 흑돌 차례입니다.");
					}
				}
			}
		}
	}
}

void gotoxy(int x, int y) { //커서이동함수 (책참고)
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_pan(void)
{
	printf("┌");
	for (int i = 0; i < 13; i++) {
		printf("┬");
	}
	printf("┐\n");
	for (int i = 0; i < 13; i++) {
		printf("├");
		for (int j = 0; j < 13; j++) {
			printf("┼");
		}
		printf("┤\n");
	}
	printf("└");
	for (int i = 0; i < 13; i++) {
		printf("┴");
	}
	printf("┘\n");
}


void move_xy(char key)
{
	if (key == 75) {    //←키 입력
		if (x != 1) {
			x -= 2;
		}
	}
	else if (key == 77) { //→키 입력
		if (x != 29) {
			x += 2;
		}
	}
	else if (key == 72) { //↑키 입력
		if (y != 1) {
			y--;
		}
	}
	else if (key == 80) { //↓키 입력
		if (y != 15) {
			y++;
		}
	}
}

int push_stone(int stone[][16])
{
	if (stone[(x + 1) / 2][y] == 0) {  //해당 위치에 돌이 놓여있지 않으면
		if (wb == 1) {
			stone[(x + 1) / 2][y] = 1;
			printf("○");
			return  1;
		}
		else if (wb == 2) {
			stone[(x + 1) / 2][y] = 2;
			printf("●");
			return  1;
		}
	}
	return 0;
}

int win(int stone[][16])
{
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, start1, start2, start3, start4;
	for (start1 = (x + 1) / 2, start2 = y; start1 < 15 && start2 > 1; start1++, start2--) {  //대각선 방향 탐색을 위한 초기위치 설정과정
	}
	for (start3 = (x + 1) / 2, start4 = y; start3 > 1 && start4 > 1; start3--, start4--) {	//대각선 방향 탐색을 위한 초기위치 설정과정
	}
	if (wb == 1) { //흑 차례일경우
		for (int i = 1; i < 16; i++) {     //현재 돌이 놓인 기점으로 가로와, 세로 탐색
			if (stone[i][y] == 0 || stone[i][y] == 2) {  //(가로방향)탐색도중 돌이 놓여져 있지 않거나 백돌이 놓여져 있을경우
				cnt1 = 0; //카운트를 초기화함.
			}
			else {
				cnt1++;
			}
			if (stone[(x + 1) / 2][i] == 0 || stone[(x + 1) / 2][i] == 2) { //(세로방향)탐색도중 돌이 놓여져 있지 않거나 백돌이 놓여져 있을경우
				cnt2 = 0; //카운트를 초기화함
			}
			else {
				cnt2++;
			}
			if (cnt1 == 5 || cnt2 == 5) {      //가로, 세로방향 탐색중 돌 5개가 연속으로 있을 때
				return 1;  //1을 반환하고 함수를 종료
			}
		}
		for (int i = start1, j = start2; i > 0 && j < 16; i--, j++) {//대각선 방향 탐색 1
			if (stone[i][j] == 0 || stone[i][j] == 2) { //(대각선방향1)탐색도중 돌이 놓여져 있지 않거나 백돌이 놓여져 있을경우
				cnt3 = 0; //카운트를 초기화함.
			}
			else {
				cnt3++;
			}
			if (cnt3 == 5) {    //돌 5개가 연속으로 있을경우
				return 1;   //1반환후 종료
			}
		}
		for (int i = start3, j = start4; i < 16 && j < 16; i++, j++) {//대각선 방향 탐색 2
			if (stone[i][j] == 0 || stone[i][j] == 2) { //(대각선방향2)탐색도중 돌이 놓여져 있지 않거나 백돌이 놓여져 있을경우
				cnt4 = 0; //카운트를 초기화함.
			}
			else {
				cnt4++;
			}
			if (cnt4 == 5) {    //돌 5개가 연속으로 있을경우
				return 1;   //1반환후 종료
			}
		}
	}
	else if (wb == 2) {  //백 순서일경우
		for (int i = 1; i < 16; i++) {     //현재 돌이 놓인 기점으로 가로와, 세로 탐색
			if (stone[i][y] == 0 || stone[i][y] == 1) {       //(가로방향)탐색도중 돌이 놓여져 있지 않거나 흑돌이 놓여져 있을경우
				cnt1 = 0;	//카운트를 초기화함.
			}
			else {
				cnt1++;
			}
			if (stone[(x + 1) / 2][i] == 0 || stone[(x + 1) / 2][i] == 1) { //(세로방향)탐색도중 돌이 놓여져 있지 않거나 흑돌이 놓여져 있을경우
				cnt2 = 0; //카운트를 초기화함
			}
			else {
				cnt2++;
			}
			if (cnt1 == 5 || cnt2 == 5) {       //가로, 세로방향 탐색중 돌 5개가 연속으로 있을 때
				return 1;						//1을 반환하고 함수를 종료
			}
		}
		for (int i = start1, j = start2; i > 0 && j < 16; i--, j++) {//대각선 방향 탐색 1
			if (stone[i][j] == 0 || stone[i][j] == 1) { //(대각선방향1)탐색도중 돌이 놓여져 있지 않거나 흑돌이 놓여져 있을경우
				cnt3 = 0; //카운트를 초기화함.
			}
			else {
				cnt3++;
			}
			if (cnt3 == 5) {    //돌 5개가 연속으로 있을경우
				return 1;   //1반환후 종료
			}
		}
		for (int i = start3, j = start4; i < 16 && j < 16; i++, j++) {//대각선 방향 탐색 2
			if (stone[i][j] == 0 || stone[i][j] == 1) { //(대각선방향2)탐색도중 돌이 놓여져 있지 않거나 흑돌이 놓여져 있을경우
				cnt4 = 0; //카운트를 초기화함.
			}
			else {
				cnt4++;
			}
			if (cnt4 == 5) {    //돌 5개가 연속으로 있을경우
				return 1;   //1반환후 종료
			}
		}
	}
	return 0;
}