#include "header.h"

/* khai bao bien toan cuc*/
vector<double> intervals[100];		// vector chua cac khoang phan ly nghiem
vector<double> varX;		// vector chua gia tri cac lan lap o buoc gradient descent
vector<double> local;	// vector chua cac diem cuc tri
vector<double> weird;	// vector chua cac nghiem ky di (nghiem boi)
string menu[] = { "1. Print root domain", "2. Print root intervals"
					, "3. Find root with the given n iteration"
					, "4. Find root with the given error"
					, "5. Find root (posterior formula)" };

int main() {
	int xtt = 0, ytt = 0, xdp = xtt + 60, ydp = ytt + 19;
	int bg_color = 12, sl_color = 15;
	int choice = 0;
	int key;
	int n = 0;		// bac da thuc
	int count = 0;		// so cac vector interval
	double m1 = 0, M1 = 0;
	double eta = 0.0001;	// learning rate
	double lower_bound = 0, upper_bound = 0;
	double poly[100] = { 0 };
	double der[100] = { 0 };
	double der2[100] = { 0 };

	while (count == 0 && weird.empty()) {
		input(poly, der, der2, n);

		system("cls");

		upper_bound = upper(upper_bound, poly, n);
		lower_bound = lower(lower_bound, poly, n);
		root_interval(lower_bound, upper_bound, poly, der, n, eta, count);
		bisection(poly, n, count);

		if (count == 0 && weird.empty()) {
			std::cout << "The polynomial has no roots! Try another one!" << endl;
		}
	}

	while (1) {
		out_poly(poly, n, xtt, ytt);

		draw_menu(choice, xtt, ytt, xdp, ydp, bg_color, sl_color, count);

		key = _getch();	// trong Visual Studio 2019 ko su dung dc getch()

		switch (key) {
		case UP:
			if (choice == 0) choice = itemNumber - 1;
			else choice--;

			draw_menu(choice, xtt, ytt, xdp, ydp, bg_color, sl_color, count);
			break;
		case DOWN:
			if (choice == itemNumber - 1) choice = 0;
			else choice++;

			draw_menu(choice, xtt, ytt, xdp, ydp, bg_color, sl_color, count);
			break;
		case ENTER:
			system("cls");

			switch (choice) {
			case 0:
				std::cout << " Roots are in range: " << endl;
				std::cout << " Lower bound: " << lower_bound << endl;
				std::cout << " Upper bound: " << upper_bound << endl;
				break;
			case 1:
				show_intervals(count);
				break;
			case 2:
				iteration_one(m1, M1, poly, der, der2, n, count);
				break;
			case 3:
				epsilon_one(m1, M1, poly, der, der2, n, count);
				break;
			case 4:
				color(12);
				last_one(m1, M1, poly, der, der2, n, count);
				break;
			}
			std::cout << endl;
			system("pause");
			system("cls");
			break;
		case ESC:
			system("cls");
			color(12);
			recta(0, 0, 51, 8, itemNumber + 3, count);
			gotoxy(0, 9);
			return -1;
		}
	}

	system("cls");
	return 0;
}

void draw_menu(int choice, int xtt, int ytt, int xdp, int ydp, int bg_color, int sl_color, int count) {
	color(bg_color);

	gotoxy(xtt, ytt);
	std::cout << char(218);
	for (int i = ytt + 1; i < ydp; i++) {
		gotoxy(xtt, i);
		if (i == ytt + 3) {
			std::cout << char(195);
		}
		else {
			std::cout << char(179);
		}
	}
	gotoxy(xtt, ydp);
	std::cout << char(192);
	for (int i = xtt + 1; i < xdp; i++) {
		gotoxy(i, ytt);
		std::cout << char(196);
	}
	for (int i = xtt + 1; i < xdp; i++) {
		gotoxy(i, ydp);
		if (i == 3 * ((xdp + xtt) / 4) - 1) {
			std::cout << char(193);
		}
		else {
			std::cout << char(196);
		}
	}
	gotoxy(xdp, ytt);
	std::cout << char(191);
	for (int i = ytt + 1; i < ydp; i++) {
		gotoxy(xdp, i);
		if (i == ytt + 3) {
			std::cout << char(180);
		}
		else {
			std::cout << char(179);
		}
	}
	gotoxy(xdp, ydp);
	std::cout << char(217);
	for (int i = xtt + 1; i < xdp; i++) {
		gotoxy(i, ytt + 3);
		if (i == 3 * ((xdp + xtt) / 4) - 1) {
			std::cout << char(194);
		}
		else {
			std::cout << char(196);
		}
	}
	for (int i = ytt + 4; i < ydp; i++) {
		gotoxy(3 * ((xdp + xtt) / 4) - 1, i);
		std::cout << char(179);
	}
	gotoxy(5 * ((xtt + xdp) / 6) - 1, 1 * ((ytt + ydp) / 2) + 1);
	std::cout << "To Exit";
	gotoxy(5 * ((xtt + xdp) / 6) - 2, 1 * ((ytt + ydp) / 2) + 2);
	std::cout << "Press ESC";

	for (int i = 0; i < itemNumber; i++) {
		if (i == choice) {
			color(sl_color);
		}
		else {
			color(bg_color);
		}
		recta(xtt + 1, ytt + 3 * i + 4, 43, ytt + 3 * i + 6, i, count);
	}
}
void recta(int xtt, int ytt, int xdp, int ydp, int index, int count) {
	static int j = count - 1;

	gotoxy(xtt, ytt);
	std::cout << char(218);
	for (int i = ytt + 1; i < ydp; i++) {
		gotoxy(xtt, i);
		std::cout << char(179);
		gotoxy(xdp, i);
		std::cout << char(179);
	}
	gotoxy(xtt, ydp);
	std::cout << char(192);
	for (int i = xtt + 1; i < xdp; i++) {
		gotoxy(i, ytt);
		std::cout << char(196);
		gotoxy(i, ydp);
		std::cout << char(196);
	}
	gotoxy(xdp, ytt);
	std::cout << char(191);
	gotoxy(xdp, ydp);
	std::cout << char(217);

	gotoxy(xtt + 1, (ytt + ydp) / 2);
	if (index >= 0 && index <= itemNumber) {
		std::cout << menu[index];
	}
	if (index == itemNumber + 1) {
		std::cout << setw(25) << "Choose your interval!";
	}
	if (index == itemNumber + 2) {
		if (j < 0) {
			j = count - 1;
		}
		std::cout << j + 1 << ". (" << intervals[j][0] << "; " << intervals[j][1] << ")";
		j--;
	}
	if (index == itemNumber + 3) {
		std::cout << setw(40) << "THE PROGRAM IS GOING TO END!";
	}
}
void Menu_ForInterval(int count, int sl_color, int bg_color, int mucchon) {
	for (int i = 0; i < count; i++) {
		if (i == mucchon) {
			color(sl_color);
		}
		else {
			color(bg_color);
		}
		recta(0, 2 * (count - i), 30, 2 * (count - i + 1), itemNumber + 2, count);
	}
	color(bg_color);
	recta(0, 0, 30, 2, itemNumber + 1, count);
}
int sub_menu(int count) {
	int choice = count - 1;
	int sl_color = 15, bg_color = 12;
	int phim;

	if (count != 0) {
		while (1) {
			Menu_ForInterval(count, sl_color, bg_color, choice);
			show_weird_roots(count);
			phim = _getch();
			switch (phim) {
			case DOWN:
				if (choice == 0) choice = count - 1;
				else choice--;
				Menu_ForInterval(count, sl_color, bg_color, choice);
				break;
			case UP:
				if (choice == count - 1) choice = 0;
				else choice++;
				Menu_ForInterval(count, sl_color, bg_color, choice);
				break;
			case ENTER:
				system("cls");
				return count - choice - 1;
			}
		}
	}
	else {
		std::cout << "The polynomial has only weird roots: ";
		for (size_t i = 0; i < weird.size(); i++) {
			std::cout << weird[i] << " ";
		}
		return -1;
	}
}
void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void input(double poly[], double der[], double der2[], int& n) {
	fstream file;

	file.open("test.txt", ios::out);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		return;
	}

	std::cout << "Degree of the polynomial: ";
	do {
		std::cin >> n;
	} while (n < 0 || n > 50);				// chi cho phep bac da thuc nam trong khoang [0, 50]

	for (int i = n; i >= 0; i--) {
		std::cout << "Coefficient of x^" << i << ": ";
		std::cin >> poly[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		der[i] = poly[i + 1] * (i + 1.0);	// he so f'(x)
	}
	for (int i = n - 2; i >= 0; i--) {
		der2[i] = der[i + 1] * (i + 1.0);	// he so f''(x)
	}

	file << "Bac cua da thuc: " << n << endl;
	file << "Da thuc f(x) = ";
	for (int i = n; i >= 0; i--) {
		if (i != 0) {
			file << poly[i] << "x^" << i << " + ";
		}
		else {
			file << poly[i];
		}
	}
	file << endl << "Da thuc f'(x) = ";
	for (int i = n - 1; i >= 0; i--) {
		if (i != 0) {
			file << der[i] << "x^" << i << " + ";
		}
		else {
			file << der[i];
		}
	}
	file << endl << "Da thuc f''(x) = ";
	for (int i = n - 2; i >= 0; i--) {
		if (i != 0) {
			file << der2[i] << "x^" << i << " + ";
		}
		else {
			file << der2[i];
		}
	}
	file << endl << "--------------------------------------" << endl;

	file.close();
}
void out_poly(double poly[], int n, int xtt, int ytt) {
	color(9);
	gotoxy(xtt + 1, ytt + 1);
	std::cout << setw(35);
	std::cout << "THE POLYNOMIAL" << endl;
	gotoxy(xtt + 1, ytt + 2);
	std::cout << "f(x): ";
	std::cout << poly[n] << "x^" << n;
	for (int i = n - 1; i >= 0; i--) {
		if (i != 0) {
			if (poly[i] >= 0) {
				std::cout << " + " << poly[i] << "x^" << i;
			}
			else {
				std::cout << " - " << fabs(poly[i]) << "x^" << i;
			}
		}
		else {
			if (poly[i] >= 0) {
				std::cout << " + " << poly[i];
			}
			else {
				std::cout << " - " << fabs(poly[i]);
			}
		}
	}
	std::cout << endl;
}

double f(double x0, double poly[], int n) {
	double res = poly[n];
	for (int i = n - 1; i >= 0; i--) {
		res = res * x0 + poly[i];
	}
	return res;
}
double f1(double x0, double der[], int n) {
	return f(x0, der, n - 1);
}
double f2(double x0, double der2[], int n) {
	return f1(x0, der2, n - 1);
}

double B(double poly[], int n) {
	static int j = 0;
	int k = 0;	// di tim chi so cua he so am dau tien
	double B = 0;
	bool flag = false;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	if (poly[n] > 0) {
		for (int i = 0; i <= n - 1; i++) {
			if (poly[i] < 0) {
				flag = true;
				k = i;
			}
		}
		if (flag == true) {
			B = poly[k];
			for (int i = n - 2; i >= 0; i--) {
				if ((poly[i] < 0) && (fabs(B) < fabs(poly[i]))) {
					B = poly[i];
				}
			}
		}
	}
	else if (poly[n] < 0) {
		for (int i = 0; i <= n; i++) {
			poly[i] = (-1) * poly[i];
		}
		for (int i = 0; i <= n - 1; i++) {
			if (poly[i] < 0) {
				flag = true;
				k = i;
			}
		}
		if (flag == true) {
			B = poly[k];
			for (int i = n - 2; i >= 0; i--) {
				if ((poly[i] < 0) && (fabs(B) < fabs(poly[i]))) {
					B = poly[i];
				}
			}
		}
	}
	else {
		std::cout << endl << "The coeficient of the polynomial must not equal to 0";
		exit(0);
	}

	if (j == 0) {
		file << "+ Doi voi can tren:" << endl;
		file << "He so am dau tien: k = " << 5 - k << endl;
		file << "Max cua cac tri tuyet doi cua cac he so am la: B = " << fabs(B) << endl;
		j++;
	}
	else {
		file << endl << "+ Doi voi can duoi: " << endl;;
		file << "He so am dau tien: k = " << 5 - k << endl;
		file << "Max cua cac tri tuyet doi cua cac he so am la: B = " << fabs(B);
	}

	file.close();
	return fabs(B);
}
double upper(double& upper_bound, double poly[], int n) {
	double temp[100];
	static int j = 0;
	int k = 0;		
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	if (poly[n] > 0) {
		for (int i = 0; i <= n - 1; i++) {
			if (poly[i] < 0) {
				k = n - i;
			}
		}
		upper_bound = 1 + pow(B(poly, n) / poly[n], (double)1 / k);
	}
	else if (poly[n] < 0) {
		for (int i = 0; i <= n; i++) {
			temp[i] = (-1) * poly[i];
		}
		for (int i = 0; i <= n - 1; i++) {
			if (temp[i] < 0) {
				k = n - i;
			}
		}
		upper_bound = 1 + pow(B(temp, n) / ((-1) * poly[n]), (double)1 / k);
	}
	else {
		std::cout << "Invalid input!";
		exit(0);
	}

	if (j == 0) {
		file << "Can tren cua mien chua nghiem: " << upper_bound;
		j++;
	}

	file.close();
	return upper_bound;
}
double lower(double& lower_bound, double poly[], int n) {
	double temp[100] = { 0 };
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	for (int i = 0; i <= n; i++) {
		if (i % 2 == 0) {
			temp[i] = poly[i];
		}
		else {
			temp[i] = (-1) * poly[i];
		}
	}
	if (n <= 50 && n >= 0) {
		if (temp[n] < 0) {
			for (int i = 0; i <= n; i++) {
				temp[i] *= (-1);
			}
			lower_bound = (-1) * upper(lower_bound, temp, n);
		}
		else {
			lower_bound = (-1) * upper(lower_bound, temp, n);
		}
	}
	else {
		exit(0);
	}

	file << endl << "Can duoi cua mien chua nghiem la: " << lower_bound;
	file << endl << "--------------------------------------" << endl;
	
	file.close();
	return lower_bound;
}

int check(double x0, double der[], int n) {
	if (f1(x0, der, n) == 0) {
		return 0;
	}
	else if (f1(x0, der, n) > 0) {
		return 1;
	}
	else {
		return -1;
	}
}
double gradient_descent(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta) {
	double x_new, x0 = lower_bound;
	double deltaX;
	int sign = check(x0, der, n);
	int it = 0;

	varX.push_back(x0);

	while (it <= 300000) {
		deltaX = eta * f1(x0, der, n);

		if (deltaX > 0.2) {
			deltaX = 0.2;
		}
		if (deltaX < -0.2) {
			deltaX = -0.2;
		}

		x_new = x0 + sign * deltaX;

		if (fabs(f1(x_new, der, n)) < 1.0e-20 || x_new > upper_bound) {
			break;
		}
		if (f1(x_new, der, n) * f1(x0, der, n) > 0) {
			eta *= 3;
		}
		if (f1(x_new, der, n) * f1(x0, der, n) < 0) {
			eta /= 5;
		}

		x0 = x_new;
		varX.push_back(x_new);
		
		it++;
	}

	return x_new;
}
void all_critical_points(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta) {
	double y = lower_bound;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	file << "Tim cac diem cuc tri" << endl;

	local.push_back(lower_bound);

	while (y < upper_bound) {
		y = gradient_descent(y, upper_bound, poly, der, n, eta);

		if (y < upper_bound && fabs(f(y, poly, n)) != 0) {
			local.push_back(y);
			file << "Diem cuc tri: (" << y << "; " << f(y, poly, n) << ")" << endl;
		}
		if (fabs(f(y, poly, n)) == 0) {
			weird.push_back(y);
			file << "Nghiem ky di: (" << y << "; " << f(y, poly, n) << ")" << endl;
		}

		y += step;		
	}

	local.push_back(upper_bound);

	file << "--------------------------------------" << endl;
	file.close();
}
void root_interval(double lower_bound, double upper_bound, double poly[], double der[], int n, double eta, int& count) {
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	all_critical_points(lower_bound, upper_bound, poly, der, n, eta);

	file << "Cac khoang phan ly nghiem (truoc khi dung chia doi):" << endl;

	for (size_t i = 0; i + 1 < local.size(); i++) {
		if (f(local[i], poly, n) * f(local[i + 1], poly, n) < 0) {
			intervals[count].push_back(local[i] + step);
			intervals[count].push_back(local[i + 1] - step);
			file << "(" << intervals[count][0] << "; " << intervals[count][1] << ")" << endl;
			count++;
		}
	}

	file << "--------------------------------------" << endl;
	file.close();
}
void show_intervals(int count) {
	string str[20] = { "The First ", "The Second ", "The Third ", "The Forth ", "The Fifth ", "The Sixth " };

	std::cout << endl;
	for (int i = 0; i < count; i++) {
		std::cout << str[i] << "interval: (" << intervals[i][0] << "; " << intervals[i][1] << ")";
		std::cout << endl;
	}
}
void show_weird_roots(int count) {
	int weird_size = weird.size();
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this faile!";
		exit(0);
	}

	file << "Cac nghiem ki di (nghiem boi) (neu co): ";

	for (int i = 0; i < weird_size; i++) {
		recta(40, 2 * (weird_size - i), 70, 2 * (weird_size - i + 1), -1, count);
		std::cout << weird_size - i << ". " << weird[weird_size - i - 1];
		file << weird[i] << " ";
	}

	recta(40, 0, 70, 2, -1, count);

	std::cout << setw(23) << "Some weird roots!";
	file << endl;
	file.close();
}

void bisection(double poly[], int n, int count) {
	double c;
	double a, b;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	file << "Cac khoang phan ly nghiem sau khi dung chia doi: " << endl;

	for (int i = 0; i < count; i++) {
		file << "khoang so " << i + 1 << ": " << endl;
		if (!intervals[i].empty()) {
			a = intervals[i][0];
			b = intervals[i][1];
			do {
				c = (a + b) / 2;

				file << "a = " << setw(8) << a << " | b = " << b << " | c = " << c << " | f(a) * f(c) = " << f(a, poly, n) * f(c, poly, n) << endl;
				
				if (f(c, poly, n) * f(a, poly, n) < 0) {
					b = c;
				}
				else if (f(c, poly, n) * f(a, poly, n) > 0) {
					a = c;
				}
				else {
					break;
				}
			} while (fabs(a - b) > 0.5);

			if (f(c, poly, n) != 0) {
				intervals[i][0] = a;
				intervals[i][1] = b;
				file << "(" << a << "; " << b << ")" << endl;
			}
		}
		else {
			continue;
		}
	}
	file << "--------------------------------------" << endl;
	file.close();
}

void regula(double& x0, double d, double poly[], double der[], int n) {
	x0 = x0 - f(x0, poly, n) * ((d - x0) / (f(d, poly, n) - f(x0, poly, n)));
}
void m1_M1(double& m1, double& M1, double poly[], double der[], double der2[], int n, int number) {
	double a = intervals[number][0];
	double b = intervals[number][1];
	int sign = (f2(a, der2, n) > 0) ? 1 : (-1);
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		cout << "Failed to open this file!" << endl;
		exit(0);
	}

	if (sign == 1 && f1(a, der, n) > 0) {
		m1 = f1(a, der, n);
	}
	else if (sign == 1 && f1(a, der, n) < 0) {
		m1 = (-1) * f1(b, der, n);
	}
	else if (sign == -1 && f1(a, der, n) > 0) {
		m1 = f1(b, der, n);
	}
	else {
		m1 = (-1) * f1(a, der, n);
	}

	if (m1 == fabs(f1(a, der, n))) {
		M1 = fabs(f1(b, der, n));
	}
	else {
		M1 = fabs(f1(a, der, n));
	}

	file << "Gia tri nho nhat va lon nhat cua f'(x) tren (" << a << "; " << b << ") la : m1 = " << m1 << " va M1 = " << M1 << endl;
	file.close();
}
void fourier_point(double& x0, double& d, double poly[], double der2[], int n, double a, double b) {
	if (f(a, poly, n) * f2(a, der2, n) < 0) {
		x0 = a;
		d = b;
	}
	else {
		x0 = b;
		d = a;
	}
}
void iteration_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count) {
	int max_ite;
	double x_old = 0;
	double x0, d;
	double a, b;
	double err;
	int number;
	int dec;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		std::cout << "Failed to open this file!" << endl;
		exit(0);
	}

	file << "Ban dang dung chuc nang so 3" << endl;

	number = sub_menu(count);
	if (number == -1) {
		return;
	}

	a = intervals[number][0];
	b = intervals[number][1];

	m1_M1(m1, M1, poly, der, der2, n, number);

	fourier_point(x0, d, poly, der2, n, a, b);

	std::cout << "Number of iteration: ";
	std::cin >> max_ite;

	file << "Diem fourier: x0 = " << x0 << " va d = " << d << endl;
	file << "So lan lap: " << max_ite << endl;
	file << "Qua trinh lap: " << endl;

	for (int i = 0; i < max_ite; i++) {
		regula(x0, d, poly, der, n);
		if (i == max_ite - 2) {
			x_old = x0;
		}
		file << setw(8) << "x" << i + 1 << " = " << x0 << endl;
	}

	std::cout << "Number of decimal places: ";
	std::cin >> dec;

	std::cout << "After " << max_ite << " iteration, the root is: " << setprecision(dec) << x0 << setprecision(6) << endl;
	std::cout << "Estimate error (formula 1): ";
	std::cout << fabs(f(x0, poly, n)) / m1;

	if (M1 <= 2 * m1) {
		err = fabs(x0 - x_old);
		std::cout << endl << "Estimate error (formula 2): " << err;
	}
	else {
		err = ((M1 - m1) / m1) * fabs(x0 - x_old);
		std::cout << endl << "Estimate error (formula 2): " << err;
	}

	file << "=> Nghiem tim duoc la: " << x0 << endl;
	file << "Voi sai so theo cong thuc 1 la: " << fabs(f(x0, poly, n)) / m1 << endl;
	file << "Voi sai so theo cong thuc 2 la: " << err << endl;
	file << "--------------------------------------" << endl;
	file.close();
}
void epsilon_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count) {
	int dec;
	int i = 0, j = 0;
	double a, b, c;
	double x0, d, temp, x_old;
	double epsilon;
	int number;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		cout << "Failed to open this file!" << endl;
		exit(0);
	}

	file << "Ban dang dung chuc nang so 4" << endl;

	number = sub_menu(count);
	if (number == -1) {
		return;
	}

	m1_M1(m1, M1, poly, der, der2, n, number);

	a = intervals[number][0];
	b = intervals[number][1];
	c = (M1 - m1) / m1;

	std::cout << "Enter the epsilon: ";
	std::cin >> epsilon;

	std::cout << "Number of decimal places: ";
	std::cin >> dec;

	file << "Epsilon ma ban da nhap: " << epsilon << endl;

	fourier_point(x0, d, poly, der2, n, a, b);

	file << "Diem fourier: x0 = " << x0 << " va d = " << d << endl;
	file << "Qua trinh lap theo cong thuc tien nghiem:" << endl;

	temp = x0;
	do {
		file << setw(8) << "x" << i++ << " = " << x0 << endl;
		regula(x0, d, poly, der, n);
	} while (fabs(f(x0, poly, n)) / m1 >= epsilon);

	std::cout << "Root with the error " << epsilon << " is (formula 1): " << setprecision(dec) << x0 << setprecision(6) << endl;
	
	file << "=> Nghiem theo cong thuc sai so tien nghiem: " << x0 << "\n\n";
	
	x0 = temp;		

	file << "Qua trinh lap theo cong thuc hau nghiem: " << endl;

	if (c <= 1) {
		do {
			x_old = x0;
			regula(x0, d, poly, der, n);
			file << setw(8) << "x" << j++ << " = " << x_old << " va x" << j << " = " << x0 << endl;
		} while (fabs(x0 - x_old) > epsilon);
	}
	else {
		do {
			x_old = x0;
			regula(x0, d, poly, der, n);
			file << setw(8) << "x" << j++ << " = " << x_old << " va x" << j << " = " << x0 << endl;
		} while (c * fabs(x0 - x_old) > epsilon);
	}

	std::cout << "Root with the error " << epsilon << " is (formula 2): " << setprecision(dec) << x0 << setprecision(6) << endl;

	file << "=> Nghiem theo cong thuc sai so hau nghiem: " << x0 << endl;
	file << "--------------------------------------" << endl;
	file.close();
}
void last_one(double m1, double M1, double poly[], double der[], double der2[], int n, int count) {
	int i = 0;
	int dec;
	double a, b;
	double x0, d, x_old;
	double epsilon;
	int number;
	fstream file;

	file.open("test.txt", ios::app);
	if (file.fail()) {
		cout << "Failed to open this file!" << endl;
		exit(0);
	}

	file << "Ban dang dung chuc nang so 5" << endl;

	number = sub_menu(count);
	if (number == -1) {
		return;
	}

	a = intervals[number][0];
	b = intervals[number][1];

	std::cout << "Enter the epsilon: ";
	std::cin >> epsilon;

	std::cout << "Number of decimal places: ";
	std::cin >> dec;

	file << "Ban chon khoang nghiem: (" << a << "; " << b << ")" << endl;
	file << "Epsilon ma ban da nhap: " << epsilon << endl;

	fourier_point(x0, d, poly, der2, n, a, b);

	file << "Diem fourier: x0 = " << x0 << " va d = " << d << endl;
	file << "Qua trinh lap: " << endl;

	do {
		x_old = x0;
		regula(x0, d, poly, der, n);
		file << setw(8) << "x" << i++ << " = " << x_old << " va x" << i << " = " << x0 << endl;
	} while (fabs(x0 - x_old) >= epsilon);

	std::cout << "The root is: " << setprecision(dec) << x0 << setprecision(6);

	file << "=> Nghiem thu duoc la: " << x0 << endl;
	file << "--------------------------------------" << endl;
	file.close();
}