#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;


void obzac()
{
	cout << "\n\n//============================================================================//\n\n";
};


class Matrix
{
	vector<vector<int>>data;


	unsigned int size;

public:
	Matrix(unsigned int size) : size(size)
	{
		data.reserve(size);
		for (int j = 0; j < size; j++)
		{
			vector<int> a;
			data.push_back(a);
			data[j].reserve(size);
			for (int d = 0; d < size; d++)
			{
				data[j].push_back(d + j);
			}
		}
	};
	~Matrix() = default;

	void getMatrixWithoutRowAndCol(vector<vector<int>>* matrix, int sizet, int row, int col, vector<vector<int>>* newMatrix) {
		int offsetRow = 0;
		int offsetCol = 0;
		for (int i = 0; i < sizet - 1; i++) {

			if (i == row) {
				offsetRow = 1;
			}

			offsetCol = 0;
			for (int j = 0; j < sizet - 1; j++) {

				if (j == col) {
					offsetCol = 1;
				}

				(*newMatrix)[i].push_back((*matrix)[i + offsetRow][j + offsetCol]);
			}
		}
	}

	int matrixDet(vector<vector<int>> matrix, int sizet) {
		int det = 0;
		int degree = 1;

		if (sizet == 1) {
			return matrix[0][0];
		}

		else if (sizet == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {

			vector<vector<int>> newMatrix;
			for (int i = 0; i < sizet - 1; i++) {
				vector<int> a;
				newMatrix.push_back(a);

			}

			for (int j = 0; j < sizet; j++) {

				getMatrixWithoutRowAndCol(&matrix, sizet, 0, j, &newMatrix);

				det = det + (degree * matrix[0][j] * matrixDet(newMatrix, sizet - 1));

				degree = -degree;
			}
		}

		return det;
	}

	void Print()
	{
		cout << "Матрица:";
		for (int i = 0; i < size; ++i)
		{

			for (int j = 0; j < size; ++j)
				cout << setw(4) << data[i][j];
		}

		cout << " <-Детерменант  ||  Вес-> " << matrixDet(data, size) << endl;

	}

};



template <typename T>
class MyArray
{
	T* arr;
	int _n;
public:
	class Iterator;
	MyArray(int n = 1) : _n(n)
	{
		arr = new T[n];
	}

	T& operator[] (const int& n)
	{
		if (n > 0 && n < _n)
			return arr[n];
		return arr[0];
	}
	Iterator begin() { return arr; }
	Iterator end() { return arr + _n; }

	friend ostream& operator<< (ostream& s, const MyArray<T>& n);

	class Iterator
	{
		T* CurOb;
	public:
		Iterator(T* first) : CurOb(first)
		{}

		T& operator + (int n) { return *(CurOb + n); }
		T& operator - (int n) { return *(CurOb - n); }

		T& operator ++ (int) { return *CurOb++; }
		T& operator -- (int) { return *CurOb--; }
		T& operator ++ () { return *++CurOb; }
		T& operator -- () { return *--CurOb; }

		bool operator != (const Iterator& it) { return CurOb != it.CurOb; }
		bool operator == (const Iterator& it) { return CurOb == it.CurOb; }
		T& operator* () { return *CurOb; }
	};
};

template <typename T>
ostream& operator << (ostream& s, const MyArray<T>& n)
{
	
	s << MyArray<T>::arr[n];
	return s;
}

int main()
{
	setlocale(LC_ALL, "rus");
	{
	
		obzac();
		vector<float> add{ 32, 54, 22, 76, 37, 32.42 };

		float middle = 0;

		for (int i = 0; i < add.size(); i++) middle += add[i];
		middle = middle / add.size();
		cout << "Среднее арифметическое = " << middle << endl;
		add.push_back(middle);
		cout << "Добавляем последний элемент в конец списка: ";
		for (vector<float>::const_iterator i = add.begin(); i != add.end(); ++i)
			cout << *i << ' ';
		cout << endl;
	}

	{

		obzac();
		int size;
		cout << "Размер матрицы: ";
		cin >> size;
		Matrix mat(size);
		mat.Print();
	}

	{

		obzac();
		int ArrSize;
		cout << "Введите размер массива: ";
		cin >> ArrSize;
		int size;
	beck:
		cout << "\nВведите номер элемента масива который желаете вывести на экран ";
		cin >> size;

		MyArray<int> Arr(ArrSize);

		for (int j = 0; j < ArrSize; j++)
		{
			Arr[j] = rand() % 50;
		}

		if (size < 0 || size > ArrSize)
		{
			cout << "\n[Error] Введённое число (" << size << ") не верно \nВведите число в диапазоне размера вашего массива(от 0 до " << ArrSize << ") \n\n";
			goto beck;
		}

		auto it = MyArray<int>::Iterator(Arr.begin());
		cout << "Ваша строка из выбраного массива: " << it + (size - 1) << "\n\n";

		for (auto i : Arr)
		{
			cout << i << " ";
		}

		obzac();
	}
};