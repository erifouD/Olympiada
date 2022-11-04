#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	if (n < 4) cout << "0";
	else if (n == 4) cout << 2 << endl << 1 << " " << 3 << endl << 2 << " " << 4;
	else if (n == 6)
	{
		cout << "3 1" << endl << "3 5" << endl << "3 6" << endl << "1 5";
	}
	else
	{
		int startpoint = n - 1, endpoint = 1;
		cout << n - 3 << endl;
		for (int i = 0; i != n - 3; i++)
		{
			cout << startpoint << " " << endpoint << endl;
			if ((startpoint + endpoint) % 2 == 0)
			{
				startpoint -= 1;
			}
			else
			{
				endpoint += 1;
			}
		}
	}
}
	