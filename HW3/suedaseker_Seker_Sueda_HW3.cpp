#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "busline.h"
using namespace std;

int main()
{
	LinkedList linkedlist;
	string filename = "busLines.txt";
	ifstream input;
	input.open(filename.c_str());
	string line, LineName, StopName;

	while(getline(input, line))
	{
		istringstream lineinput(line);
		lineinput >> LineName>> StopName;
		LineName.pop_back();
		linkedlist.BusLineList(LineName, StopName, 1);
		
		while(lineinput >> StopName)
		{
			linkedlist.BusStopList(LineName, StopName);
		}
	}

	linkedlist.processMainMenu();

	system("pause");
	return 0;
}
