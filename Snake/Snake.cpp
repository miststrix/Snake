#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int width = 48;
const int height = 25;
bool lose1;
int snakePosx, snakePosy;
int fruitPosx, fruitPosy;


string dir;

void fruitRand();

void setup() {
	lose1 = false;
	snakePosx = width / 2;
	snakePosy = height / 2;
	fruitRand();
}

void input() {

		if (GetAsyncKeyState('W'))
			dir = "up";
		else if(GetAsyncKeyState('S'))
			dir = "down";
		else if (GetAsyncKeyState('A'))
			dir = "left";
		else if(GetAsyncKeyState('D'))
			dir = "right";
}

void lose() {
	if (snakePosx == width - 2 || snakePosx == width - 1 || snakePosx == 0 || snakePosy == -1 || snakePosy == height)
		lose1 = true;
}

int random(int a, int b) { //число от и до
	int randNum = rand() % (b - a) + a ;
	return randNum;
}

int randomEven(int a, int b) { //число от и до
	int randNum = 1;
	while (randNum % 2 != 0)
		randNum = rand() % (b - a) + a;
	return randNum;
}

void fruitRand() {
	fruitPosx = randomEven(2, width - 2);   
	fruitPosy = random(2, height - 2);
}

bool checkFruit() { //позиция фрукта x, позиция фрукта y, позиция головы x, позиция головы y
	bool check = false;
	if (snakePosx == fruitPosx && snakePosy == fruitPosy) {
		check = true;
	}
	return check;
}

void draw() {
	system("cls");
	char space = ' ';

	




		for (int i = 0; i < width; ++i) {    //верхняя граница
			cout << (char)219;
			if (i == width - 1)
				cout << endl;
		}

		for (int i = 0; i < height; ++i) {    //центр
			for (int j = 0; j < width; ++j) {
				if (j == 0 || j == width - 3) {
					cout << (char)219;
					cout << (char)219;
				}
				else if (snakePosx == j && snakePosy == i) {
					cout << 'O';
				}
				else if (fruitPosx == j && fruitPosy == i) {
					cout << 'F';
				}

				else{
					cout << space;
				}
				
				}
			cout << endl;
			}
			
		

		for (int i = 0; i < width; ++i) {    //нижняя граница
			cout << (char)219;
			if (i == width - 1)
				cout << endl;
		}

		
	
}


int main(){	
	setup();
	while (lose1 == false) {
		draw();
		input();
		if (dir == "up")
			snakePosy--;
		if (dir == "down")
			snakePosy++;
		if (dir == "left")
			snakePosx -= 2;
		if (dir == "right")
			snakePosx += 2;

		if (checkFruit()) {
			fruitRand();
		}
		lose();
		Sleep(500);
	}
}
