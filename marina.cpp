#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // устанавливаем ширину выводв переменных

#include < stdlib.h >  //Для exit () и atexit ()
#include <locale.h> // ипользуется для распознавания русского языка
#include <stdio.h>  // Описания функций ввода-вывода
#include <math.h>   // Описания математических функций
#include <stdlib.h> // Описания функций malloc и free

void MATRIX_print(int n, int m, std::vector <std::vector <double> > matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << std::left << std::setw(10) << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

//функция поиска базисных столбцов с преобразованием полной матрицы
std::vector <std::vector <double> > zero(int n, int m, std::vector <std::vector <double> > matrix, int* bazis, int vec_j, int vec_i, int colvo) {
	// i, j перебор по номеру элемента, который необходимо превратить в 1 
	double tmp = 0;
	int count = 0;
	int j = vec_j;

	for (int i = vec_i; i < n; i++) {
		j++;
		if (count == colvo) {
			break;
		}
		if (matrix[i][j] == 0) {
			j++;
		}
		//std::cout << "j = " << j <<"\n";
		bazis[vec_j] = j;
		vec_j++;
		for (int a = 0; a < n; a++) { // строчки обнуления
			if (a == i) {

			}
			else {
				double main_val = matrix[i][j];
				double P = matrix[a][j];
				for (int p = 0; p < m; p++) { // делим строку на i, j элемент, чтобы i, j стал = 1
					matrix[i][p] = matrix[i][p] / main_val;
					if (matrix[i][p] == -0) {
						matrix[i][p] = 0;
					}
				}

				for (int k = 0; k < m; k++) { // столбцы обнуления
					tmp = matrix[i][k] * P;
					matrix[a][k] = matrix[a][k] - tmp;
					if (matrix[a][k] == -0) {
						matrix[a][k] = 0;
					}
				}
				//MATRIX_print(n, m, matrix);
			}
		}
		count++;
	}
	return matrix;
}

//функция для обнуления столбца №1
std::vector <std::vector <double> > zero_1(int n, int m, std::vector <std::vector <double> > matrix) {
	double  tmp = 0;
	double  P = 0;
	int stolb = 1;

	double main_val = matrix[0][stolb];
	for (int p = 0; p < m; p++) { // делим строку на i, j элемент, чтобы i, j стал = 1
		matrix[0][p] = matrix[0][p] / main_val;
		if (matrix[0][p] == -0) {
			matrix[0][p] = 0;
		}
	}

	for (int i = 1; i < n; i++) {
		tmp = matrix[i][stolb];
		for (int k = 0; k < m; k++) {
			P = matrix[0][k] * tmp;
			matrix[i][k] = matrix[i][k] - P;
		}
	}
	return matrix;
}

std::vector <std::vector <double> > LABOR(int n, int m, std::vector <std::vector <double> > matrix, int* bazis, int form) {
	std::cout << "матрица на вход: \n";
	MATRIX_print(n, m, matrix);

	if (form == 1) {
		int vec_j = 0;
		int vec_i = 2;
		int count = 4;
		std::cout << "приводим еще четыре любых столбеца х: \n";
		matrix = zero(n, m, matrix, bazis, vec_j, vec_i, count);
		MATRIX_print(n, m, matrix);
	}
	else {
		matrix = zero_1(n, m, matrix);
		std::cout << "привели первый столбец х: \n";
		MATRIX_print(n, m, matrix);

		int vec_j = 1;
		int vec_i = 1;
		int count = 2;
		std::cout << "приводим еще два любых столбеца х: \n";
		matrix = zero(n, m, matrix, bazis, vec_j, vec_i, count);
		MATRIX_print(n, m, matrix);
	}
	return matrix;
}

int check_negative(int n, int m, std::vector <std::vector <double> > b_X_F) {
	int i = n - 1;
	int count = 0;
	for (int j = 1; j < m; j++) {
		if (b_X_F[i][j] < 0) {
			count++;
		}
	}
	return count;
}

// находим разрешающий столбец (максимальный эелемент по модулю)
std::pair<int, double> Resolv_col(int n, int m, std::vector <std::vector <double> > b_X_F) {
	double min = 10000;
	int k = 0;
	int i = n - 1;


	for (int j = 1; j < m; j++) {
		if (b_X_F[i][j] < min) {
			k = j;
			min = b_X_F[i][j];
		}
	}
	std::cout << "\n";
	std::cout << "min = " << min << "\n";

	return std::make_pair(k, min);
}

// находим разрешающую строку
std::pair<int, double> Resolv_row(int n, int col, std::vector <std::vector <double> > b_X_F) {
	double min_el_str = 1000;
	double raz;
	int j = 0;
	int num = 0;
	double R = 0;
	int count = 0;
	for (int p = 0; p < (n - 1); p++) {
		j = col;
		if ((b_X_F[p][j] > 0 && b_X_F[p][0] > 0) || (b_X_F[p][j] < 0 && b_X_F[p][0] < 0)) {
			if (b_X_F[p][j] == 0) {

			}
			else {
				raz = b_X_F[p][0] / b_X_F[p][j];
				if (raz < min_el_str) {
					min_el_str = raz;
					R = b_X_F[p][j];
					num = p;
				}
			}
			count++;
		}
	}
	if (count == 0) {
		std::cout << "Невозможно найти ведущую строку, так как нет положительных элементов в ведущем столбце и в векторе B одновременно, поэтому функция в области допустимых решений задачи не ограничена – алгоритм завершает работу.\n";
		return std::make_pair(-1, -1);
	}
	return std::make_pair(num, R);
}

std::vector <std::vector <double> > Simplex_method(int n, int m, std::vector <std::vector <double> > b_X_F, int bazis[6]) {

	auto col = Resolv_col(n, m, b_X_F);
	auto row = Resolv_row(n, col.first, b_X_F);
	if (row.second == -1 && row.first == -1) {
		exit(EXIT_SUCCESS);
	}

	std::cout << "\n";
	std::cout << "максимальный эелемент по модулю:  " << col.second << "\n";
	std::cout << "Разрешающий столбец:  " << col.first << "\n";
	std::cout << "Разрешающая строка:  " << row.first << "\n";



	std::cout << "\n";
	int num_col = 0;
	switch (col.first) {
	case 1:
		num_col = 1;
		break;
	case 2:
		num_col = 2;
		break;
	case 3:
		num_col = 3;
		break;
	case 4:
		num_col = 4;
		break;
	case 5:
		num_col = 5;
		break;
	case 6:
		num_col = 6;
		break;
	case 7:
		num_col = 7;
		break;
	case 8:
		num_col = 8;
		break;
	case 9:
		num_col = 9;
		break;
	case 10:
		num_col = 10;
		break;
	case 11:
		num_col = 11;
		break;
	case 12:
		num_col = 12;
		break;
	case 13:
		num_col = 13;
		break;
	case 14:
		num_col = 14;
		break;
	}

	std::cout << "\n";
	int num_row = 0;
	switch (row.first) {
	case 0:
		num_row = 0;
		break;
	case 1:
		num_row = 1;
		break;
	case 2:
		num_row = 2;
		break;
	case 3:
		num_row = 3;
		break;
	case 4:
		num_row = 4;
		break;
	case 5:
		num_row = 5;
		break;
	case 6:
		num_row = 6;
		break;
	}

	bazis[num_row] = num_col;
	for (int i = 0; i < (n - 1); i++) {
		std::cout << bazis[i] << " ";
	}
	std::cout << "\n";
	std::cout << "__________________________________________________________________________________________________________________________________________________________________________________________________________________________\n";


	int l = 0;
	int w = 0;
	//col - столбец
	//row - строка
	for (w = 0; w < n; w++) {
		for (l = 0; l < m; l++) {
			if (w < row.first || w > row.first) {
				if (l == col.first) {

				}
				else {
					b_X_F[w][l] = b_X_F[w][l] - (b_X_F[row.first][l] * b_X_F[w][col.first] / b_X_F[row.first][col.first]);
				}
			}
		}
	}

	// разрешающую строку делим на разрешающий элемент
	int i = row.first;
	for (int j = 0; j < m; j++) {
		b_X_F[i][j] = b_X_F[i][j] / row.second;
	}

	// обнуляем разрешающий столбец
	for (int i = 0; i < n; i++) {
		int j = col.first;
		if (i != row.first) {
			b_X_F[i][j] = 0;
		}
	}

	std::cout << "Преобразование: \n";
	// проверка 
	std::cout << " +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n";
	std::cout << " +       B      +      x1      +       x2     +       x3     +       x4     +       x5     +       x6     +       x7     +       x8     +       x9     +      x10     +      x11     +      x12     +      x13     +\n";
	std::cout << " +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n";
	for (int i = 0; i < n; i++) {
		if (i == (n - 1)) {
			std::cout << " +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n";
		}
		for (int j = 0; j < m; j++) {
			if (abs(b_X_F[i][j]) < 1e-6) {
				b_X_F[i][j] = 0;
			}
			std::cout << " | " << std::left << std::setw(12) << b_X_F[i][j];
			if (j == (m - 1)) {
				std::cout << " | ";
			}
			if (i == (n - 1) && j == (m - 1)) {
				std::cout << "   F | ";
			}
		}
		std::cout << "\n";
	}
	std::cout << " +--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+--------------+\n";
	return b_X_F;
}


int bazis_o[6] = { 1, 0, 0, 11, 12, 13 };
int bazis_d[6] = { 0, 0, 0,  0, 10, 11 };

int main() {
	setlocale(LC_CTYPE, "Russian"); // ипользуется для распознавания русского языка (LC_ALL - не использовать)

	int n_1 = 7;
	int m_1 = 14;
	std::vector <std::vector <double> > O{
		{2,  1,  2,  7, -7,  3, -3, 1, -1,  7, -7, 0, 0, 0},
		{1,  2,  3,  6, -6,  9, -9, 2, -2,  5, -5, 0, 0, 0},
		{9,  3,  9,  9, -9,  2, -2, 3, -3,  4, -4, 0, 0, 0},
		{4,  2,  8,  6, -6,  3, -3, 5, -5,  6, -6, 1, 0, 0},
		{6,  1,  4,  5, -5,  1, -1, 6, -6,  4, -4, 0, 1, 0},
		{7,  2,  3,  8, -8,  4, -4, 7, -7,  5, -5, 0, 0,-1},
		{0, -2, -4, -6,  6, -1,  1, -9, 9, -3,  3, 0, 0, 0}
	};


	int n_2 = 7;
	int m_2 = 12;
	std::vector <std::vector <double> > D{
		{2,  1, -1,  2, -2,  3, -3,  2,  1, -2, -1,  0},
		{4,  2, -2,  3, -3,  9, -9,  8,  4, -3,  0, -1},
		{6,  7, -7,  6, -6,  9, -9,  6,  5, -8,  0,  0},
		{1,  3, -3,  9, -9,  2, -2,  3,  1, -4,  0,  0},
		{9,  1, -1,  2, -2,  3, -3,  5,  6, -7,  0,  0},
		{3,  7, -7,  5, -5,  4, -4,  6,  4, -5,  0,  0},
		{0, -2,  2, -1,  1, -9,  9, -4, -6,  7,  0,  0}
	};

	int form = 0;
	std::cout << " (-1 = нет ; 1 = да)\n Форма общая -> форма двойственная -> форма каноническая?\n Ответ: ";
	std::cin >> form;

	if (form == 1) {
		std::vector <std::vector <double> > matrix;
		matrix = LABOR(n_2, m_2, D, bazis_d, form);

		for (int g = 0; g < n_2; g++) {
			for (int i = 0; i < n_2; i++) {
				if (matrix[i][bazis_d[g]] == -1) {
					for (int j = 0; j < m_2; j++) {
						matrix[i][j] = matrix[i][j] * -1;
						if (matrix[i][j] == -0) {
							matrix[i][j] = 0;
						}
					}
				}
			}
		}

		std::cout << "матрица на выходе: \n";
		MATRIX_print(n_2, m_2, matrix);

		std::cout << "Базисные вектора: \n";
		for (int i = 0; i < (n_2 - 1); i++) {
			std::cout << bazis_d[i] << "\n";
		}

		double ptr = -1000;
		while (ptr != 0) {
			matrix = Simplex_method(n_2, m_2, matrix, bazis_d);
			ptr = check_negative(n_2, m_2, matrix);

		}
		std::cout << "РЕШЕНИЕ ОПТИМАЛЬНОЕ, если все оценки в последней строке >= 0 \n";
		std::cout << "ЕСЛИ среди базисных переменных присутствуют отрицательные значения. Целевая функция не ограничена. Решения не существует.\n";
	}
	else {
		std::vector <std::vector <double> > matrix;
		matrix = LABOR(n_1, m_1, O, bazis_o, form);

		for (int g = 0; g < n_1; g++) {
			for (int i = 0; i < n_1; i++) {
				if (matrix[i][bazis_o[g]] == -1) {
					for (int j = 0; j < m_1; j++) {
						matrix[i][j] = matrix[i][j] * -1;
						if (matrix[i][j] == -0) {
							matrix[i][j] = 0;
						}
					}
				}
			}
		}

		std::cout << "матрица на выходе: \n";
		MATRIX_print(n_1, m_1, matrix);

		std::cout << "Базисные вектора: \n";
		for (int i = 0; i < (n_1 - 1); i++) {
			std::cout << bazis_o[i] << "\n";
		}

		double ptr = -1000;
		while (ptr != 0) {
			matrix = Simplex_method(n_1, m_1, matrix, bazis_o);
			ptr = check_negative(n_1, m_1, matrix);

		}
		std::cout << "РЕШЕНИЕ ОПТИМАЛЬНОЕ:\n1. ЕСЛИ все оценки в последней строке >= 0\n";
		std::cout << "2. ЕСЛИ среди базисных переменных присутствуют отрицательные значения. Целевая функция не ограничена. Решения не существует.\n";
	}
	return 0;
}