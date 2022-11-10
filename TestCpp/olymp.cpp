#include <iostream>
#include <vector>
using namespace std;
bool unsigned_dots(vector<vector<int>> Matrix)
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
	{
		if (alpha[i] == value) return false;
	}
	return true;
}
vector<vector<int>> MakinNewPaths(vector<vector<int>> Mat, vector<int> CurPath, int fir) //создание последующих
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
vector<vector<int>> CountPathsCheck(vector<vector<int>> Mat, int fir) //создание первых путей
{
	vector<vector<int>> Path;
	for (int i = 0; i < Mat.size(); i++)
	{
		if (Mat[fir - 1][i])
		{
			Path.push_back({ Mat[fir - 1][i], fir, i + 1});
		}
	}
	return Path;
}
int main()
{
	int first, last, roads, houses;

	cin >> houses >> roads; //кол-во домов и дорог
	cin >> first >> last; //начало и конец маршрута

	vector<vector<int>> Matrix(last); //матрица смежности
	vector<vector<int>> TempPaths; //неоконченные пути
	vector<vector<int>> Paths; //завершенные пути

	for (int i = 0; i < last; i++) //создание матрицы
		for (int j = 0; j < last; j++)
			Matrix[i].push_back(0);

	for (int i = 0; i < roads; i++) //вводимые значения
	{
		int h1, h2, distance;
		cin >> h1 >> h2 >> distance;
		Matrix[h1 - 1][h2 - 1] = distance;
		Matrix[h2 - 1][h1 - 1] = distance;
	}

	if (unsigned_dots(Matrix)) return 1; //проверка на неподведенные точки
	TempPaths = CountPathsCheck(Matrix, first); // присвоение первых путей

		for (int i = 0; i < TempPaths.size(); i++)//цикл создания путей
		{
			for (int seven = 0; seven < roads; seven++)//цикл с максимальной длиной пути если возможно
			{
				for (int give = 0; give < houses; give++) //цикл присвоение следующей конечной точки
				{
					if (Matrix[TempPaths[i].back() - 1][give] && unique(TempPaths[i], give + 1) && TempPaths[i].back() != last) //если валидно значение в матрице смежности 1- конечная точка в пути + след. конечная точка и такой точки не было
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
		for (int i = 0; i < TempPaths.size(); i++)
			if (TempPaths[i].back() == last)
				Paths.push_back(TempPaths[i]);

		int min = Paths[0][0];
		for (int i = 0; i < Paths.size(); i++)
			if (Paths[i][0] < min) min = Paths[i][0];

		vector<vector<int>> ShortestPaths;
		for (int i = 0; i < Paths.size(); i++)
			if (Paths[i][0] == min)
				ShortestPaths.push_back(Paths[i]);

		int maxlength = ShortestPaths[0].size();
		for (int i = 0; i < ShortestPaths.size(); i++)
			if (ShortestPaths[i].size() > maxlength) maxlength = ShortestPaths[i].size();

		for (int i = 0; i < ShortestPaths.size(); i++)
		{
			if (ShortestPaths[i].size() == maxlength)
			{
				for (int j = 2; j < ShortestPaths[i].size() - 1; j++)
				{
					cout << ShortestPaths[i][j] << " ";
				}
				return 0;
			}
		}
}