#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>
using namespace std;

class Car
{
public:
	Car(double, int, int); //car object gets fuel level, insurance fee and the distance that the car have travelled

	void display(); //to display the fuel level, insurance fee and the total distance of the car

	double getFuel(); //to reach the private data fuel from other the class
	int getInsurance(); //to reach the private data insurance fee from other the class
	int getDistance(); //to reach the private data total distance from other the class

	void setFuel(double); //to change the private data fuel from other the class
	void setInsurance(int); //to change the private data insurance fee from other the class
	void setDistance(int); //to change the private data total distance from other the class

private:
	double fuel;
	int insurance, distance;

};

Car::Car(double f, int i, int d) //constructor
	:fuel(f), insurance(i), distance(d)
{}

void Car::display()
{
	cout << "Fuel Level: " << fuel << endl
		 << "Insurance Fee: " << insurance << endl
		 << "Total distance that the car has travelled: " << distance << endl << endl;
}

double Car::getFuel()
{
	return fuel;
}

int Car::getInsurance()
{
	return insurance;
}
	
int Car::getDistance()
{
	return distance;
}

void Car::setFuel(double num) //changes the private data with the given parameter
{
	fuel = num;
}

void Car::setInsurance(int num) //changes the private data with the given parameter
{
	insurance = num;
}

void Car::setDistance(int num) //changes the private data with the given parameter
{
	distance = num;
}

#endif