#include <stdio.h> 
#include <Windows.h> //gotoxy()�Լ� �������� ������
#void gotoxy(int x, int y); //Ŀ���̵��Լ�include <conio.h> //getch()�Լ��� ����ϱ� ���� ������

void draw_pan(void); //�ٵ����� �׸��� �Լ�
void move_xy(char key);//����Ű�� ���� ��ǥ�̵��Լ�.
int push_stone(int stone[][16]); //���� ���� �Լ�. 
int start(); //���ӽ����Լ�
int win(int stone[][16]);//�¸��ǵ��Լ�
int x = 15, y = 8; //ó�� ���� �����ǥ
int wb = 1;//1�̸� �浹���� 2�̸� �鵹����

int main(void)
{
	printf("\t\t\t������� (made by Seo ji Woo)\n\n");

	printf("���۹�� : ��(�����������̵�)\t��(���������̵�)\n\t   ��(�����̵�)\t\t��(�Ʒ����̵�)\n\t   �����̽�(�ٵϵ�����)\n\n");
	printf("EnterŰ�� �Է��Ͻø� ������ ���۵˴ϴ�\n");


	char ch = getch();

	if (ch == 13) {
		system("cls");
		for (;;)
		{
			if (start()) {
				x = 15;  //���� �ٽ� �������� ��ǥ�� ó�� ���� ��ǥ�� �ʱ�ȭ.
				y = 8;
				wb = 1;  //�� �������� �ʱ�ȭ
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
	int stone[16][16] = { 0 };//���� 15*15 �����̳� �ڵ��� ������ ���� 16*16�� �迭������ ����
	char key = 0;
	draw_pan(); //�ٵ��� ����
	gotoxy(1, 20); //��������ϴ� ��ǥ�� �̵�
	printf("���� �浹 �����Դϴ�.");
	gotoxy(x, y); //�߾����� Ŀ���̵�
	for (;;) {
		gotoxy(x, y);   //���� ��ġ�� �̵�.
		key = getch();  //Ű�� �Է¹���(�Է¹��������� ���α׷� ���)
		if (key == 75 || key == 77 || key == 72 || key == 80) { //����Ű�� �Է��ϸ�
			move_xy(key); //Ű �Է¿� ���� xy��ǥ����
			gotoxy(x, y); //Ŀ����ġ�̵�
		}
		else if (key == 32) { //�����̽��� �Է½�
			if (push_stone(stone)) { //���� ���������� ������ ���.
				if (win(stone)) { //�¸��� ��������?
					gotoxy(1, 20);
					if (wb == 1) {
						printf("                                                         "); //�ش� ��ġ ��� �κ� clear
						gotoxy(1, 20);,
						printf("���� �¸��Դϴ�.\n");
					}
					else {
						printf("                                                         "); //�ش� ��ġ ��� �κ� clear
						gotoxy(1, 20);
						printf("���� �¸��Դϴ�.\n");
					}
					printf("������ �ٽ� �Ͻðڽ��ϱ�? �ƴϸ� ���� �Ͻðڽ��ϱ�?\n�ٽ� �Ϸ��� y ���� �Ϸ��� �ƹ�Ű�� �����ʽÿ�.");
					key = getch();  //Ű�� �Է¹���(�Է¹��������� ���α׷� ���)
					if (key == 121) {
						system("cls"); //�ٽ� ���� ������ ���� ȭ���� ����
						return 1; //1�� ��ȯ�� �Լ� ����
					}
					else
					{
						return 0; //0�� ��ȯ�� �Լ� ����
					}
				}
				else {		//�¸��� �������� ������
					if (wb == 1) {
						wb = 2;
						gotoxy(1, 20);
						printf("���� �鵹 �����Դϴ�.");
					}
					else {
						wb = 1;
						gotoxy(1, 20);
						printf("���� �浹 �����Դϴ�.");
					}
				}
			}
		}
	}
}

void gotoxy(int x, int y) { //Ŀ���̵��Լ� (å����)
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_pan(void)
{
	printf("��");
	for (int i = 0; i < 13; i++) {
		printf("��");
	}
	printf("��\n");
	for (int i = 0; i < 13; i++) {
		printf("��");
		for (int j = 0; j < 13; j++) {
			printf("��");
		}
		printf("��\n");
	}
	printf("��");
	for (int i = 0; i < 13; i++) {
		printf("��");
	}
	printf("��\n");
}


void move_xy(char key)
{
	if (key == 75) {    //��Ű �Է�
		if (x != 1) {
			x -= 2;
		}
	}
	else if (key == 77) { //��Ű �Է�
		if (x != 29) {
			x += 2;
		}
	}
	else if (key == 72) { //��Ű �Է�
		if (y != 1) {
			y--;
		}
	}
	else if (key == 80) { //��Ű �Է�
		if (y != 15) {
			y++;
		}
	}
}

int push_stone(int stone[][16])
{
	if (stone[(x + 1) / 2][y] == 0) {  //�ش� ��ġ�� ���� �������� ������
		if (wb == 1) {
			stone[(x + 1) / 2][y] = 1;
			printf("��");
			return  1;
		}
		else if (wb == 2) {
			stone[(x + 1) / 2][y] = 2;
			printf("��");
			return  1;
		}
	}
	return 0;
}

int win(int stone[][16])
{
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, start1, start2, start3, start4;
	for (start1 = (x + 1) / 2, start2 = y; start1 < 15 && start2 > 1; start1++, start2--) {  //�밢�� ���� Ž���� ���� �ʱ���ġ ��������
	}
	for (start3 = (x + 1) / 2, start4 = y; start3 > 1 && start4 > 1; start3--, start4--) {	//�밢�� ���� Ž���� ���� �ʱ���ġ ��������
	}
	if (wb == 1) { //�� �����ϰ��
		for (int i = 1; i < 16; i++) {     //���� ���� ���� �������� ���ο�, ���� Ž��
			if (stone[i][y] == 0 || stone[i][y] == 2) {  //(���ι���)Ž������ ���� ������ ���� �ʰų� �鵹�� ������ �������
				cnt1 = 0; //ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt1++;
			}
			if (stone[(x + 1) / 2][i] == 0 || stone[(x + 1) / 2][i] == 2) { //(���ι���)Ž������ ���� ������ ���� �ʰų� �鵹�� ������ �������
				cnt2 = 0; //ī��Ʈ�� �ʱ�ȭ��
			}
			else {
				cnt2++;
			}
			if (cnt1 == 5 || cnt2 == 5) {      //����, ���ι��� Ž���� �� 5���� �������� ���� ��
				return 1;  //1�� ��ȯ�ϰ� �Լ��� ����
			}
		}
		for (int i = start1, j = start2; i > 0 && j < 16; i--, j++) {//�밢�� ���� Ž�� 1
			if (stone[i][j] == 0 || stone[i][j] == 2) { //(�밢������1)Ž������ ���� ������ ���� �ʰų� �鵹�� ������ �������
				cnt3 = 0; //ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt3++;
			}
			if (cnt3 == 5) {    //�� 5���� �������� �������
				return 1;   //1��ȯ�� ����
			}
		}
		for (int i = start3, j = start4; i < 16 && j < 16; i++, j++) {//�밢�� ���� Ž�� 2
			if (stone[i][j] == 0 || stone[i][j] == 2) { //(�밢������2)Ž������ ���� ������ ���� �ʰų� �鵹�� ������ �������
				cnt4 = 0; //ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt4++;
			}
			if (cnt4 == 5) {    //�� 5���� �������� �������
				return 1;   //1��ȯ�� ����
			}
		}
	}
	else if (wb == 2) {  //�� �����ϰ��
		for (int i = 1; i < 16; i++) {     //���� ���� ���� �������� ���ο�, ���� Ž��
			if (stone[i][y] == 0 || stone[i][y] == 1) {       //(���ι���)Ž������ ���� ������ ���� �ʰų� �浹�� ������ �������
				cnt1 = 0;	//ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt1++;
			}
			if (stone[(x + 1) / 2][i] == 0 || stone[(x + 1) / 2][i] == 1) { //(���ι���)Ž������ ���� ������ ���� �ʰų� �浹�� ������ �������
				cnt2 = 0; //ī��Ʈ�� �ʱ�ȭ��
			}
			else {
				cnt2++;
			}
			if (cnt1 == 5 || cnt2 == 5) {       //����, ���ι��� Ž���� �� 5���� �������� ���� ��
				return 1;						//1�� ��ȯ�ϰ� �Լ��� ����
			}
		}
		for (int i = start1, j = start2; i > 0 && j < 16; i--, j++) {//�밢�� ���� Ž�� 1
			if (stone[i][j] == 0 || stone[i][j] == 1) { //(�밢������1)Ž������ ���� ������ ���� �ʰų� �浹�� ������ �������
				cnt3 = 0; //ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt3++;
			}
			if (cnt3 == 5) {    //�� 5���� �������� �������
				return 1;   //1��ȯ�� ����
			}
		}
		for (int i = start3, j = start4; i < 16 && j < 16; i++, j++) {//�밢�� ���� Ž�� 2
			if (stone[i][j] == 0 || stone[i][j] == 1) { //(�밢������2)Ž������ ���� ������ ���� �ʰų� �浹�� ������ �������
				cnt4 = 0; //ī��Ʈ�� �ʱ�ȭ��.
			}
			else {
				cnt4++;
			}
			if (cnt4 == 5) {    //�� 5���� �������� �������
				return 1;   //1��ȯ�� ����
			}
		}
	}
	return 0;
}