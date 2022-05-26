#pragma once
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Tree.h"

using namespace std;

const int X_COORD = 1000;
const int Y_COORD = int(log10(250000)) * 4;
const float coeff = X_COORD / Y_COORD;
const float ITERATIONS = 1;
float x_off = 2 * coeff;
float y_off = 2;

//исходная функция
#define expr x

void load();
void load_screen(string, int);
void sleep(double);
void drawgrid(float, float);
void drawfunc(double*, float, float, float);
void display();
void init();

string main_menu() {
	system("cls");
	cout << "====================== Выберите действие ======================";
	cout << "\n\n\t1. Работа с деревьями\n\t2. Работа с множеством\n\t3. Таймирование множества\n\t4. Выход\n\n";
	string x;
	cin >> x;
	return x;
}

void timing() {
	int n1, n2;
	cin >> n1 >> n2;
	double* paste = new double[X_COORD * 2];
	double* erase = new double[X_COORD * 2];
	double* find = new double[X_COORD * 2];
	set<int> st;
	for (int i = 0; i < n1; i++) {
		st.push(rand() % 100000);
	}
	for (int i = n1, j = 0; i <= n2; i += (n2 - n1) / (X_COORD * 2), j++) {
		clock_t start = clock();
		for (int k = 0; k < 10; k++) {
			st.push(rand() % 100000);
		}
		clock_t finish = clock();
		paste[j] = ((double)(finish - start) / CLOCKS_PER_SEC) / 10;
		start = clock();
		for (int k = 0; k < 10; k++) {
			st.erase(rand() % 1000);
		}
		finish = clock();
		erase[j] = ((double)(finish - start) / CLOCKS_PER_SEC) / 10;
		start = clock();
		for (int k = 0; k < 10; k++) {
			st.find(rand() % 1000);
		}
		finish = clock();
		find[j] = ((double)(finish - start) / CLOCKS_PER_SEC) / 10;
	}
	drawfunc(paste, 0, 0, 0);
	glutDisplayFunc(display);
	glutMainLoop();
}

void menu() {
	load();
	std::string s = "";
	while (s != "4") {
		s = main_menu();
		switch (stoi(s))
		{
		case 1:

		case 2:

		case 3:
			timing();
		case 4:
			system("cls");
			cout << "\tВсего хорошего!";
			return;
		default:
			break;
		}
	}
}

void load() {
	load_screen("Загрузка файлов", 20);
	load_screen("Загрузка библиотек", 28);
	load_screen("Подключение математического модуля", 16);
	load_screen("Сборка программы", 22);
	load_screen("Запуск main.cpp", 19);
	cout << "\n\nзагрузка завершена.\n";
	sleep(2);
}

void load_screen(string text, int delta) {
	int d = 0;
	srand(time(0));
	system("cls");
	int f = 2;
	while (d <= 100 && f) {
		sleep(0.25);
		system("cls");
		cout << "\n" << text << "\t";
		cout << "[ " << d << "% ]\n\n< ";
		for (int i = 0; i < d / 4; i++) {
			cout << (char)(4);
		}
		cout << " >";
		d += rand() % 8 - 4 + delta;
		if (d > 100) d = 100, f -= 1;
	}
	sleep(0.5);
}

void sleep(double _duration) {
	clock_t t1 = clock();
	clock_t t2 = clock();
	while ((double)(t2 - t1) / (double)(CLOCKS_PER_SEC) < _duration) {
		t2 = clock();
	}
}




void drawgrid(float SERIF_OFFSET, float SERIF_DISTANCE) {
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);

	glVertex2f(x_off / 2, y_off);
	glVertex2f(X_COORD, y_off);
	
	glVertex2f(x_off, Y_COORD);
	glVertex2f(x_off, y_off - 1);

	//}
	glEnd();
}

void drawfunc(double* a, float r, float g, float b) {
	glBegin(GL_POINTS);
	float j = 0;
	glColor3f(r, g, b);
	for (int x = 0; x < X_COORD * 2; x += ITERATIONS) {
		j = a[x];
		glVertex2f(x_off + x, y_off + j);
	}
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawgrid(0.25, 40);
	glutSwapBuffers();
	glFlush();
}

void init() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("GLUT_TESTING_APP");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//пространство координат
	glOrtho(0.0, X_COORD, 0.0, Y_COORD, -1.0, 1.0);

	//glutDisplayFunc(display);
	//glutMainLoop();
}
