#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;
int main(){
	int build, road, home, school;
	scanf_s("%d %d", &build, &road);
	scanf_s("%d %d", &home, &school);
	map <pair<int, int>, int> mapa;
	if (build > 0 && road > 0 && home > 0 && school > 0)
	{

		int house1, house2, distance, ansr_distance, ansr_houses;
		for (int i = 0; i != road; i++)
		{
			scanf_s("%d %d %d", &house1, &house2, &distance);
			pair<int, int> b;
			b = make_pair(house1, house2);
			mapa.insert(pair<pair<int, int>, int>(b, distance));
		}	
		cout << endl;
		for (auto i = mapa.begin(); i != mapa.end(); i++)
		{
			if (i->first.first == 0)
			{
				
			}
		}

	}
}
	