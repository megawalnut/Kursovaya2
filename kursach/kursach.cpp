#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define INF 999	//Нет дорожки из одной вершины в другую

//Функция создания взвешенной ориентированной матрицы смежности
void creatematrix(int** x, int y) 	//Принимает указатель на матрицу A и ее размер size
{
	for (int i = 0; i < y; i++)
	{
		int count = 0;	//Чтобы не было изолированной вершины
		for (int j = 0; j < y; j++)
		{
			int N = rand() % 2;	//50% шанс, что будет ребро
			if (N == 0)
			{
				x[i][j] = INF;	// вводим бесконечность(999)
				count++;	
			}
			else
				x[i][j] = -15 + rand() % 31;	//Заполняем матрицу числами, диапазоном [-15:15]
			if (count == y - 1)
				x[i][j] = -15 + rand() % 31;	//Заполняем матрицу числами, диапазоном [-15:15]
		} 
		x[i][i] = 0;
	}
}

//Функция, выполняющая алгоритм Флойда-Уоршелла
void floyd(int** x, int y)	//Принимает указатель на матрицу A и ее размер size
{
	for (int k = 0; k < y; k++)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < y; j++)
			{
				if (x[i][k] < INF && x[k][j] < INF)
				{
					if (x[i][j] > (x[i][k] + x[k][j]))	//Если сумма веса дорог  < веса записанной дороги 
						x[i][j] = x[i][k] + x[k][j];	//Записываем новый вес дороги
				}
			}
		}
	}
}

//Функция, выполняющая проверку ввода
int scan()	//Принимает размер матрицы size
{
	char input[20];
	int input_success = 0;
	int y;

	while (!input_success) {
		printf("Введите размер матрицы: ");
		if (scanf("%s", input) == 1) {
			// Проверка, является ли введенный символ числом
			int is_digit = 1;
			for (int i = 0; input[i] != '\0'; ++i) {
				if (!isdigit(input[i])) {
					is_digit = 0;
					break;
				}
			}

			if (is_digit) {
				y = atoi(input);
				input_success = 1;
			}
			else {
				printf("Ошибка! \n");
			}
		}
		else {
			printf("Некорректный ввод. \n");
			// Очистка буфера ввода
			while (getchar() != '\n');
		}
	}
	return y;
}

//Функция, выполняющая проверку ввода(можно отрицательные числа)
int input() { 
	char input[20];
	int input_success = 0;
	int y;

	while (!input_success) {
		if (scanf("%s", input) == 1) {
			// Проверка, является ли введенный символ числом
			int is_digit = 1;
			int start_index = 0;

			// Проверка наличия знака минуса в начале строки
			if (input[0] == '-') {
				start_index = 1;
			}

			for (int i = start_index; input[i] != '\0'; ++i) {
				if (!isdigit(input[i])) {
					is_digit = 0;
					break;
				}
			}

			if (is_digit) {
				y = atoi(input);
				input_success = 1;
			}
			else {
				printf("Ошибка! \n");
			}
		}
		else {
			printf("Некорректный ввод. \n");
			// Очистка буфера ввода
			while (getchar() != '\n');
		}
	}
	return y;
}

//Функция, выполняющая ввод матрицы с клавиатуры
int** scan_key(int y) 
{
	int** A = (int**)malloc(y * sizeof(int*));
	for (int i = 0; i < y; i++)
	{
		A[i] = (int*)malloc(y * sizeof(int));	//Создание матрицы
	}

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < y; j++)
		{
				A[i][j] = 0;	//Обнуляем матрицу
		}
	}

	printf("999 - отсутствие ребра\n");
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < y; j++) {
			if (!(i == j)) {
				A[i][j] = 1000;
				while (A[i][j] > 999 || A[i][j] < -999)
				{
					printf("Введите строку %d столбец %d:\n", i + 1, j + 1);
					A[i][j] = input(); // Используем функцию для ввода числа
				}
			}
			else {
				A[i][j] = 0;
			}
		}
	}
	return A;
}

//Функция, выполняющая вывод матрицы на экран
void print(int** x, int y) 
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < y; j++)
		{
			printf("%5d ", x[i][j]);	//Выводим матрицу
		}
		printf("\n");
	}
	printf("\n");
}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int size;	//Размер матрицы
	int** A = 0;	//Указатель на матрицу смежности
	int r = 0;		//Для поиска отрицательного цикла
	int menu = 1;	//переменная меню
	char name[50];	//Наименование файла
	int cycle = 0;	//Для числа отрицательных циклов
	char results[20];	//Для содания файла
	//_________________________________________________________________________________________________________________

	while (menu != 0)
	{
		printf("Выберите пункт:\n");
		printf("Для генерации матрицы случайными числами нажмите 1:\n");
		printf("Для ввода матрицы с клавиатуры нажмите 2:\n");
		printf("Для считывания матрицы с файла нажмите 3:\n");
		printf("Для просмотра титульного листа нажмите 4:\n");
		printf("Для выхода нажмите 0:\n");


		scanf("%d", &menu);

		switch (menu)
		{
		case 0:
			return 0;
			break;
		case 1:
			size = scan();	//Проверка ввода

			A = (int**)malloc(size * sizeof(int*));
			for (int i = 0; i < size; i++)
			{
				A[i] = (int*)malloc(size * sizeof(int));	//Создание матрицы
			}

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					A[i][j] = 0;	//Обнуляем матрицу
				}
			}

			creatematrix(A, size);	//Вызываем функцию генерации матрицы

			print(A, size);	//Выводим матрицу

			floyd(A, size);	//Вызываем функцию Флойда-Уоршелла

			for (int i = 0; i < size; i++)
				if (A[i][i] < 0)
					r++;
			if (r >= 1)
			{
				printf("Обнаружено: %d отрицательных циклов\n", r);
				cycle = 1;
			}

			if (!cycle)
				print(A, size);	//Выводим матрицу

			break;
		case 2:
			
			size = scan();	//Проверка ввода

			A = scan_key(size);

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					while(A[i][j] == 999)
					{
						printf("Ошибка! Возникла изолированная вершина. Пожалуйста введите число отличное 999.\n");
						printf("Введите число в %d столбец и %d строку:\n", i + 1, j + 1);
						scanf("%d", &A[i][j]);
					}
				}
				A[i][i] = 0;
			}

			print(A, size);	//Выводим матрицу

			floyd(A, size);	//Вызываем функцию Флойда-Уоршелла

			for (int i = 0; i < size; i++)
				if (A[i][i] < 0)
					r++;
			if (r >= 1)
			{
				printf("Обнаружено: %d отрицательных циклов\n", r);
				cycle = 1;
			}

			if (!cycle)
				print(A, size);	//Выводим матрицу 

			break;
		case 3:
			printf("Введите название файла с расширением:\n");
			scanf("%s", name);
			FILE* file;
			file = fopen(name, "r");
			while ((file = fopen(name, "r")) == NULL) 
			{
				printf("Не удалось открыть файл\n");
				printf("Введите название файла с расширением или с полным путем, если он находится в другом месте:\n");
				scanf("%s", name);
			}

			if (fgetc(file) == EOF)
			{
				printf("Файл пустой!\n");
				break;
			}

			fscanf(file, "%d", &size);

			for (int i = 0; i < size && !feof(file); i++) {
				for (int j = 0; j < size && !feof(file); j++) {
					fscanf(file, "%f", &A[i][j]);
					printf("%d ", A[i][j]);
				}
				putchar('\n');
			}

			fclose(file);
			break;
		case 4:
			printf("\n\t\t\tКурсовая работа\n\t\tПо дисциплине Логика и основы алгоритмизации в инжинерных задачах\n\t\tНа тему: \"Реализация алгоритма Флойда-Уоршелла поиска кратчайших путей в графе\"\n\n\tВыполнил студент группы 22ВВП1: Изосин Михаил\n\tПринял: к.э.н. доцент Акифьев И.В.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			getchar();
			break;
		}
	}
	return 0;
}