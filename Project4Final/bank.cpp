#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "simulate.h"

using namespace std;

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::ifstream;
using std::ofstream;

int main()
//int main(int argc, char*argv[])
{
	string inputfilename;

	cout << "What is the name of your file?" << endl;
	cin >> inputfilename; 

	ifstream in(inputfilename);

	if (in.fail())
	{
		throw std::invalid_argument("could not open file");
	}

	int arrival = 0;
	int wait = 0;

	simulate transactions = simulate();

	while (!in.fail())
	{
		in >> arrival;
		in >> wait;

		transactions.addPerson(arrival, wait);
	}

	cout << "t = 0: Simulation begins" << endl;

	transactions.action();
	transactions.printEvents();
	cout << " " << endl;
	transactions.endResults();

}