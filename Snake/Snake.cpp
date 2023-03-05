#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int width = 49;
const int height = 25;
const int clsWidth = 120;
const int clsHeight = 30;
bool lose1;
int snakePosx, snakePosy;
int fruitPosx, fruitPosy;
int snakeLenght;
int prevPosx, prevPosy;
int tailPosx[100];
int tailPosy[100];
int score;
int record;
int countMessage = 0;


string dir = "";

void fruitRand();

void prev() {
	prevPosx = snakePosx;
	prevPosy = snakePosy;
}

void tailPos() {
	int prevPos2x, prevPos2y;
	int prevPosx = tailPosx[0];
	int prevPosy = tailPosy[0]; 
	tailPosx[0] = snakePosx;
	tailPosy[0] = snakePosy;
	
	for (int i = 1; i < snakeLenght; i++) {
		prevPos2x = tailPosx[i];
		prevPos2y = tailPosy[i];
		tailPosx[i] = prevPosx;
		tailPosy[i] = prevPosy;
		prevPosx = prevPos2x;
		prevPosy = prevPos2y;

	}
}

void backspace(int count)
{
	for (int i = 0; i < count; i++)
		printf_s("\b \b");
}

void setup() {
	lose1 = false;
	snakePosx = width / 2;
	snakePosy = height / 2;
	fruitRand();
	snakeLenght = 0;
}

void input() {

		if (GetAsyncKeyState('W') && (dir == "left" || dir == "right" || dir == ""))
			dir = "up";
		else if(GetAsyncKeyState('S') && (dir == "left" || dir == "right" || dir == ""))
			dir = "down";
		else if (GetAsyncKeyState('A') && (dir == "up" || dir == "down" || dir == ""))
			dir = "left";
		else if(GetAsyncKeyState('D') && (dir == "up" || dir == "down" || dir == ""))
			dir = "right";
}

void lose() {
	if (snakePosx == width - 2 || snakePosx == width + 1 || snakePosx == width - 1 || snakePosx == 0 || snakePosy == -1 || snakePosy == height)
		lose1 = true;
	for (int i = 0; i < snakeLenght; ++i) {
		if (snakePosx == tailPosx[i] && snakePosy == tailPosy[i]) {
			lose1 = true;
		}
	}
}

int random(int a, int b) { //число от и до
	srand(time(NULL));
	int randNum = rand() % (b - a) + a ;
	return randNum;
}

int randomEven(int a, int b) { //число от и до
	int randNum = 1;
	srand(time(NULL));
	while (randNum % 2 != 0)
		randNum = rand() % (b - a) + a;
	return randNum;
}

void fruitRand() {
	fruitPosx = randomEven(2, width - 2);   
	fruitPosy = random(2, height - 2);
	while (fruitPosx == snakePosx && fruitPosy == snakePosy) { 
		fruitPosx = randomEven(2, width - 2);
		fruitPosy = random(2, height - 2);
	}
	for (int i = 0; i < snakeLenght; i++) {
		while (fruitPosx == tailPosx[i] && fruitPosy == tailPosy[i]) {
			fruitPosx = randomEven(2, width - 2);
			fruitPosy = random(2, height - 2);
		}
	}
}

bool checkFruit() {
	bool check = false;
	if (snakePosx == fruitPosx && snakePosy == fruitPosy) {
		check = true;
		snakeLenght++;
		score += 10;
	}
	
	return check;
}

void loseMessage() {
	system("cls");
	cout << "You lose!";
	cout << endl;
	cout << "Your score: " << score;
}

void funMessage() {

	if (score == 30) {
		cout << " Nice!";
		
	}
	if (score == 40) {
		cout << " Fuck Belolipeckiy!";
		
	}
	if (score == 50) {
		cout << " Wow!";
		
	}
	if (score == 80) {
		cout << " Amazing!";
		
	}
	if (score == 150) {
		cout << " Roma Somow!?";
		
	}
	if (score == 170) {
		cout << " Esports player?";
		
	}
	if (score == 230) {
		cout << " 228..";
		
	}
	if (score == 250) {
		cout << "                           ";
		cout << " Closing the game...";
	}
	if (score == 900) {
		cout << "                           ";
		cout << " God of the game!";
	}
	else {
		cout << "                           ";
	}
}

void draw() {
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd;
	cd.X = 0;
	cd.Y = 0;
	SetConsoleCursorPosition(hd, cd);
	bool a = false;
	char space = ' ';

		for (int i = 0; i < width; ++i) {    //верхняя граница
			cout << (char)219;
			
		}
		cout << " Your score: " << score;
		cout << endl;

		for (int i = 0; i < height; ++i) {    //центр
			for (int j = 0; j < width; ++j) {
					if (j == 0 || j == 1 || j == width - 2 || j == width - 1) {
						cout << (char)219;
					}
					else if (snakePosx == j && snakePosy == i) {
						cout << 'O';
					}
					else if (fruitPosx == j && fruitPosy == i) {
						cout << 'F';
					}
					else {
						bool a = false;
						for (int k = 0; k < snakeLenght; ++k) {
							if (tailPosx[k] == j && tailPosy[k] == i) {
								cout << '*';
								a = true;
							}
						}
						if(!a)
							cout << space;
					}
			}
			if (i == 0)
				funMessage();
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
	while (!lose1) {
		draw();
		input();
		tailPos();
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
		Sleep(180);
	}
	loseMessage();
}
