#include <iostream>
#include <vector>
using namespace std;
bool unsigned_dots(vector<vector<int>> Matrix) //проверка на наличие изолированных вершин
{
	for (int i = 0; i != Matrix.size(); i++)
		for (int j = 0; j != Matrix.size(); j++)
		{
			if (Matrix[i][j]) break;
			else if (j == Matrix.size() - 1) return true;
		}
	return false;
}
bool unique(vector<int> alpha, int value) //проверка на уникальность значения
{
	for (int i = 1; i < alpha.size(); i++)
		if (alpha[i] == value) return false;
	return true;
}
vector<vector<int>> MakinNewPaths(vector<vector<int>> Mat, vector<int> CurPath, int fir) //создание последующих точек в путях
{
	vector<vector<int>> Path;
	for (int i = 0; i < Mat.size(); i++)
	{
		vector<int> FuncPath = CurPath;
		if (Mat[fir - 1][i] && unique(CurPath, i + 1))
		{
			FuncPath.push_back(i + 1);
			FuncPath.front() += Mat[fir - 1][i];
			Path.push_back(FuncPath);
		}
	}
	return Path;
}
int main()
{
	int first, last, roads, houses; //переменные исходной и конечной точки, количества дорог и точек
	cin >> houses >> roads >> first >> last; //ввод значений

	vector<vector<int>> 
		Matrix(houses), TempPaths, Paths, ShortestPaths; //матрица смежности, неоконченные, завершенные, кратчайшие пути

	for (int i = 0; i < houses; i++) //создание матрицы смежности
		for (int j = 0; j < houses; j++)
			Matrix[i].push_back(0);

	for (int i = 0; i < roads; i++) //вводимые значения
	{
		int h1, h2, distance; //переменные начальной и конечной точки пути + длина пути
		cin >> h1 >> h2 >> distance; //ввод значений 
		Matrix[h1 - 1][h2 - 1] = distance; //запись введенных значений в матрицу смежности
		Matrix[h2 - 1][h1 - 1] = distance; //зеркальная запись в нижнюю часть
	}

	if (unsigned_dots(Matrix)) return 1; //проверка на изолированные вершины. если есть программа обрывается
	TempPaths.push_back({0 , first}); //создание первого пути с нулевым расстоянием и стартовой точкой
	for (int i = 0; i < TempPaths.size(); i++)//цикл создания путей
	{
		for (int seven = 0; seven < roads; seven++)//цикл с максимальной длиной пути если возможно
		{
			for (int give = 0; give < houses; give++) //цикл присвоение следующей конечной точки
			{
				/*  если валидно значение в матрице текущей конечной точки пути и след. точки && значение нет в пути &&
				↓ конечная точка не равна требуемой конечной (это завершенный путь и он не нуждается в повторном продлении)*/
				if (Matrix[TempPaths[i].back() - 1][give] && unique(TempPaths[i], give + 1) && TempPaths[i].back() != last) 
				{
					vector<vector<int>> Iter = MakinNewPaths(Matrix, TempPaths[i], TempPaths[i].back()); //временный вектор путей
					TempPaths.erase(TempPaths.begin() + i); //удалить вектор, так как он будет множиться
					for (int j = 0; j < Iter.size(); j++) //запись новых путей в вектор
						TempPaths.push_back(Iter[j]);
					i = 0;
					break;
				}
			}
		}	
	}
	for (int i = 0; i < TempPaths.size(); i++) //создание массива полных путей
		if (TempPaths[i].back() == last)
			Paths.push_back(TempPaths[i]); 

	int min = Paths[0][0];
	for (int i = 0; i < Paths.size(); i++) //поиск минимальной длины пути
		if (Paths[i][0] < min) min = Paths[i][0]; 

	for (int i = 0; i < Paths.size(); i++) //создание массива кратчайших путей
		if (Paths[i][0] == min)
			ShortestPaths.push_back(Paths[i]);

	int maxlength = ShortestPaths[0].size(); //создание массива путей с максимальным кол-вом точек
	for (int i = 0; i < ShortestPaths.size(); i++) 
		if (ShortestPaths[i].size() > maxlength) maxlength = ShortestPaths[i].size();

	for (int i = 0; i < ShortestPaths.size(); i++)//вывод требуемых значений
	{
		if (ShortestPaths[i].size() == maxlength)
		{
			cout << ShortestPaths[i][0] << endl;
			for (int j = 2; j < ShortestPaths[i].size() - 1; j++)
				cout << ShortestPaths[i][j] << " ";
			return 0;
		}
	}
}