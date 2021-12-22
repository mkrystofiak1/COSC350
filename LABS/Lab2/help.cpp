//C++ Trial for task6a.sh
//

#include <iostream>

using namespace std;

int main()
{
	int base;
	cout << "Enter the odd base: ";
	cin >> base;
	int space = base -1;
	if (base%2 != 1)
	{
		cout << "Base must be odd." << endl;
		return 1;
	}
	
	for (int i = 0; i < base-1; i++) //this will serve as the number of lines to produce
	{
		for (int j = 0; j < space; j++)
			cout << " ";
		for (int j = 0; j <= i; j++)
			cout << "* ";
		cout << endl;
		space--;
	}

	space = 0;
	for (int i = base; i > 0; i--)
	{
		for (int j = 0; j < space; j++)
			cout << " ";
		for (int j = 0; j < i; j++)
			cout << "* ";
		cout << endl;
		space++;
	}
	cout << endl;

	return 0;
}
