#ifndef DRIVE_H
#define DRIVE_H

#include <iostream>
#include <string>
using namespace std;

class Driver
{
public:
	Driver(Car&, double);

	void drive(int);
	void repairCar(string);
	void display();
	void fullFuel();

private:
	double budget;
	Car &car; //the car object is a reference since we want all the driver objects to share the same car object
};

Driver::Driver(Car &c, double b)
		:car(c), budget(b)
{}

void Driver::drive(int km) //the driver drived the given kilometers, so the total distance of the car increases
						   //and the fuel level decreases
{
	int d = car.getDistance();
	d += km;
	car.setDistance(d);

	double cost = km * 0.25;
	double f = car.getFuel();
	f -= cost;
	car.setFuel(f);
}

//according to the accident type, the budget of the driver decreases and the insurance fee increases
void Driver::repairCar(string type) 
{
	if (type == "SMALL")
	{
		budget -= 50;

		int i = car.getInsurance();
		i = i + (i * 5 / 100);
		car.setInsurance(i);

		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl
			<< "Yearly insurance fee is increased to " << i << " because of the SMALL accident" << endl;
	}
	else if (type == "MEDIUM")
	{
		budget -= 150;

		int i = car.getInsurance();
		i = i + (i * 10 / 100);
		car.setInsurance(i);

		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl
			<< "Yearly insurance fee is increased to " << i << " because of the MEDIUM accident" << endl;
	}
	else
	{
		budget -= 300;

		int i = car.getInsurance();
		i = i + (i * 20 / 100);
		car.setInsurance(i);

		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl
			<< "Yearly insurance fee is increased to " << i << " because of the LARGE accident" << endl;
	}
}
	
void Driver::display() //to display driver's current budget
{
	cout << "Driver Budget: " << budget << endl;
}
	
void Driver::fullFuel() //makes the fuel maximum (300 dolars) and cuts that cost from the driver's budget
{
	double fuel = car.getFuel();
	double num = 300 - fuel;
	car.setFuel(300);
	budget -= num;

	cout << "Fuel is full" << endl << endl;
}

#endif