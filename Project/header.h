#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>

#define eps 1.0e-7
#define step 1.0e-3

#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define itemNumber 5

using namespace std;

/* khai bao nguyen mau ham*/
// ham dau vao
void input(double poly[], double der[], double der2[], int& n);
void out_poly(double poly[], int n, int xtt, int ytt);

// cac ham phu tro menu
void draw_menu(int choice, int xtt, int ytt, int xdp, int ydp, int bg_color, int sl_color, int count);
void recta(int xtt, int ytt, int xdp, int ydp, int index, int count);
void Menu_ForInterval(int count, int sl_color, int bg_color, int mucchon);
int sub_menu(int count);		// menu lua chon khoang nghiem
void color(int color);			// mau
void gotoxy(int x, int y);		// di den toa do (x, y) tren console
	
// cac ham tinh toan gia tri bieu thuc
double f(double x0, double poly[], int n);		// tinh f(x0)
double f1(double x0, double der[], int n);		// tinh f'(x0)
double f2(double x0, double der2[], int n);		// tinh f''(x0)

// thuat toan tim can tren, can duoi
double B(double poly[], int n);		// tim B
double upper(double& upper_bound, double poly[], int n);	// tim can tren
double lower(double& lower_bound, double poly[], int n);	// tim can duoi

// tim cuc tri voi gradient descent
int check(double x0, double der[], int n);
double gradient_descent(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta);	// tim cuc tri dia phuong
void all_critical_points(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta);	// dua cuc tri vao trong vector local
void root_interval(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta, int& count);	// tim khoang phan ly nghiem va dua vao vector intervals
void show_intervals(int count);		// in cac khoang nghiem
void show_weird_roots(int count);

// thu hep khoang cach ly
void bisection(double poly[], int n, int count);	// thu nho tat ca khoang nghiem trong vector intervals

void regula(double& x0, double d, double poly[], double der[], int n);		// cong thuc lap
void m1_M1(double& m1, double& M1, double poly[], double der[], double der2[], int n, int number);			// tim m1 va M1 tren khoang ma ta chon
void fourier_point(double& x0, double& d, double poly[], double der2[], int n, double a, double b);			// tim diem fourier
void iteration_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count);		// tim nghiem voi so lan lap cho truoc
void epsilon_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count);		// tim nghiem voi epsilon
void last_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count);			// tim nghiem theo ct hau nghiem