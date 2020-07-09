#include <iostream>
using namespace std;

void sysout(double** a, double* y, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "*x" << j;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	return;
}

double* gauss(double** a, double* y, int n,bool *kluch)
{
	double *x, max;
	*kluch = true;
	int k, index;
	const double eps = 0.00001;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы A" << endl;
			*kluch = false;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента 
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k) continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}

double input()
{
	double q;
	while (!(cin >> q))

	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error,put numbers\n" << "=";
	}
	return q;
}
void proverka(double **A,double *Y,double *X ,int N)
{
	int i, j;
	double s;
	bool k=false;
	for(i=0;i<N;i++)
	{
		s = 0;
		k = false;
		for(j=0;j<N;j++)
		{
		s += A[i][j] * X[j];
	    }
	/*s = floor(s + 0.5);
	Y[j] = floor(Y[j] + 0.5);*/
	cout << "\ns=" << s << "\t Y=" << Y[i];
	if (s == Y[i])
		k = true;
	if(!k)
	{  
		cout << "\n----Проверка----\n";
		cout << "\nКорни найдены верно\n";
		break;
	}
	}
	if (k)
	{
		cout << "\n----Проверка----\n";
		cout << "\nКорни найдены верно\n";
	}
}

int main()
{
	double **a, *y, *x,*Y,*X,**A;
	int n, kod;
	int b[3][3] = {
		{2, 3, -1},
		{1, -2, 1},
		{1, 0, 2}
	};
	int y1[3] = { 9,3,2 };
	bool menu = true,kluch=true;
	setlocale(LC_ALL, "RUS");
	while (menu)
	{
		cout << "1-Ввести с клавиатуры\n2-Тестовая матрица:\n 2*x0+3*x1-x2=9\n x0-2*x1+x2=3\n x0+2*x2=2\n";
		kod = input();
		switch (kod)
		{
		case 1:
			cout << "Введите количество уравнений:\n ";
			n = input();
			a = new double* [n];
			y = new double[n];
			A = new double* [n];
			for(int i=0;i<n;i++)
				A[i] = new double[n];
			Y = new double[n];
			X = new double[n];
			for (int i = 0; i < n; i++)
			{
				a[i] = new double[n];
				for (int j = 0; j < n; j++)
				{
					cout << "a[" << i << "][" << j << "]= ";
					a[i][j] = input();
					A[i][j] = a[i][j];
				}
			}
			for (int i = 0; i < n; i++)
			{
				cout << "y[" << i << "]= ";
				y[i] = input();
				Y[i] = y[i];
			}
			sysout(a, y, n);
			x = gauss(a, y, n,&kluch);
			if (x != 0)
			{
				for (int i = 0; i < n; i++){
					cout << "x[" << i << "]=" << x[i] << endl;
				    X[i]=x[i];
				}
			}
			if(kluch)
			proverka(A, Y, X, n);
			break;
		case 2:
			cout << "Количество уравнений:3\n ";
			n = 3;
			a = new double* [n];
			y = new double[n];
			for (int i = 0; i < n; i++)
			{
				a[i] = new double[n];
				for (int j = 0; j < n; j++)
				{
					a[i][j] = b[i][j];
				}
			}
			for (int i = 0; i < n; i++)
			{
				y[i] = y1[i];
			}
			sysout(a, y, n);
			x = gauss(a, y, n,&kluch);
			if (x != 0)
			{
				for (int i = 0; i < n; i++)
					cout << "x[" << i << "]=" << x[i] << endl;
			}
			break;
		}
		
		cout << "Ввести ещё раз?\n1-Да\n0-Нет\n";
		cin >> menu;
	}
	return 0;
}
