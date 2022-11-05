#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int main()
{
	int build, road, home, school;
	scanf_s("%d %d", &build, &road);
	scanf_s("%d %d", &home, &school);
	if (build > 0 && road > 0 && home > 0 && school > 0)
	{
		vector<vector<int>> Matrix(build);
		vector<vector<int>> Paths;
		vector<vector<int>> CompPaths;
		vector<vector<int>> ShortestPaths;
		vector<int> Answer;
		int buffer;
		for (int i = 0; i != build; i++)
			for (int j = 0; j != build; j++)
			{
				Matrix[i].push_back(0);
			}


		int house1, house2, distance, ansr_distance = 0, ansr_houses = 0;
		for (int i = 0; i != road; i++)
		{
			scanf_s("%d %d %d", &house1, &house2, &distance);
			Matrix[house1 - 1][house2 - 1] = distance;
		}
		int next_index = home, temp_distance, pathnum = 0;
		while (next_index != build)
		{
			for (int j = 0; j != build; j++)
			{
				if (Matrix[next_index - 1][j])
				{
					if (next_index == 1)
					{
						vector<int> TempVector;
						TempVector.push_back(Matrix[next_index - 1][j]); //расстояние
						TempVector.push_back(next_index);          //начальная точка
						TempVector.push_back(j + 1); //конечная точка
						Paths.push_back(TempVector);
						pathnum++;
					}
					else
					{
						for (int k = 0; k != Paths.size(); k++)
						{
							if (Paths[k].back() == next_index)
							{
								for(int l = 1; l != Paths.size(); l++)
								Paths.push_back(Paths[k]); //создание нового пути на основе старого
								Paths.back().push_back(j + 1); //добавление конечной точки
								Paths.back().front() += Matrix[next_index - 1][j]; //добавление расстояния
								pathnum++;
							}
						}
					}			
				}
			}			
			next_index++;
		}
		for (int i = 0; i != Paths.size(); i++)
			if (Paths[i].back() == school)
				CompPaths.push_back(Paths[i]); //создание массива полных маршрутов

		int minsize = CompPaths[0].front();

		for (int i = 0; i != CompPaths.size(); i++)
			if (CompPaths[i].front() < minsize)
				minsize = CompPaths[0].front(); //нахождение минимальной длины маршрута

		for (int i = 0; i != CompPaths.size(); i++)
			if (CompPaths[i].front() == minsize)
				ShortestPaths.push_back(CompPaths[i]); //запись в финальный массив маршрутов

		int maxsize = 0;
		for (int i = 0; i != ShortestPaths.size(); i++)
			if (ShortestPaths[i].size() > maxsize)
				maxsize = ShortestPaths[i].size(); // нахождение самого длинного пути

		for (int i = 0; i != ShortestPaths.size(); i++)
			if (ShortestPaths[i].size() == maxsize)
				Answer = ShortestPaths[i];
		cout << Answer.front() << endl << Answer.size() - 3 << endl;
		for (int i = 2; i != Answer.size() - 1; i++)
			cout << Answer[i] << " ";
		
	}
}