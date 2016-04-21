//Garage.h

#ifndef GARAGE_H
#define GARAGE_H
#include <iostream>
#include <string>
#include "Stack.h"
#include <fstream>

using namespace std;


class Garage {
private:

	//Stuct containing car information
	struct Car {
		string plate;
		int counter = 0;
		Car(){}
		Car(string inPlate, int inCounter){ inPlate = plate; inCounter = counter; }
		bool operator!=(Car vehicle) //Overloaded function for not equal
		{
			if (vehicle.plate != plate) return true; else return false;
		}
		bool operator == (Car vehicle) //Overloaded function for is equal
		{
			if (vehicle.plate == plate) return true; else return false;
		}
	};

	//Declaring my lanes of Car type
	Stack<Car> lane1;
	Stack<Car> lane2;
	Stack<Car> street;

public:
	Garage();
	void arrive(Car plate);
	void depart(Car plate);


};

Garage::Garage()
{
	//OPENING AND CHECKING FILE OF CARS
	ifstream carsFile;
	carsFile.open("CARS.txt");
	if (!carsFile.is_open())
	{
		cout << "Problem opening file!" << endl;
		exit(1);
	}

	char arrivingOrDeparting;
	Car vehicle;

	//Reading in cars from file
	while (!carsFile.eof())
	{
		carsFile >> arrivingOrDeparting;

		//If the car is arriving:
		if (arrivingOrDeparting == 'A')
		{
			carsFile >> vehicle.plate;
			arrive(vehicle);
		}

		//If the car is departing:
		if (arrivingOrDeparting == 'D')
		{
			carsFile >> vehicle.plate;
			depart(vehicle);
		}
	}
}

void Garage::arrive(Car vehicle) //Arrival method
{
	//If both lanes are full - tell customer to come back later
	if (lane1.IsFull() && lane2.IsFull())
	{
		cout << "Both lanes are full! Please come back later" << endl;
	}

	//If lane one has space - park car here
	else if (!lane1.IsFull())
	{
		cout << "Lane 1 has " << lane1.numberOfSpacesAvail() << " space(s) available" << endl;
		lane1.push(vehicle);
		cout << "Car " << vehicle.plate << " is arriving in lane 1" << endl << endl;
	}

	//If lane two has space - park car here
	else if (!lane2.IsFull())
	{
		cout << "Lane 1 is full!" << endl;
		cout << "Lane 2 has " << lane2.numberOfSpacesAvail() << " space(s) available" << endl;
		lane2.push(vehicle);
		cout << "Car " << vehicle.plate << " is arriving in lane 2" << endl << endl;
	}

}

void Garage::depart(Car vehicle) //Departure method
{
	Car currentCar; //Temp car

	if (vehicle == lane1.Top()) //If passed car is in front of lane - pop
	{
		cout << endl;
		currentCar = lane1.Top();
		cout << "Turns out car " << vehicle.plate << " is in front! Coming out now.." << endl;
		lane1.pop();
		cout << "Car " << vehicle.plate << " has left!" << endl;
		cout << "Car " << vehicle.plate << " moved " << currentCar.counter
			<< " time(s) for other cars" << endl << endl;
	}

	else if (lane1.search(vehicle)) //Otherwise look in lanes for passed car
	{
		cout << "Car " << vehicle.plate << " in lane 1 wants to come out" << endl;
		cout << "One moment, moving cars in front out of the way..." << endl;
		while (vehicle != lane1.Top()) //While passed car is not in the front
		{
			currentCar = lane1.Top();
			if (!lane2.IsFull()) //Push car in front to lane 2 if there is space
			{
				currentCar.counter++;
				lane2.push(lane1.Top());
				lane1.pop();
			}
			else //Push car to street if lane 2 is full
			{
				cout << "Other lane full! Moving car " << currentCar.plate
					<< " into the street temporarily..." << endl;
				currentCar.counter++;
				street.push(lane1.Top());
				lane1.pop();
			}
		}

		lane1.pop(); //Finally pop the passed car
		cout << "Car " << vehicle.plate << " has left!" << endl;
		cout << "Car " << vehicle.plate << " moved " << currentCar.counter
			<< " time(s) for other cars" << endl << endl;

		while (!street.IsEmpty()) //While the street has some cars in it:
		{
			currentCar = street.Top();
			if (!lane1.IsFull()) //Park cars in lane 1 if it has space
			{
				cout << "Moving car " << currentCar.plate
					<< " back into the garage" << endl;
				lane1.push(street.Top());
				street.pop();
			}
			else if (!lane2.IsFull()) //Park cars in lane 2 if it has space
			{
				cout << "Moving car " << currentCar.plate
					<< " back into the garage" << endl;
				lane2.push(street.Top());
				street.pop();
			}
		}
	}

	else if (lane2.search(vehicle))
	{
		if (vehicle == lane2.Top())
		{
			cout << endl;
			currentCar = lane2.Top();
			cout << "Turns out car " << vehicle.plate << " is in front! Coming out now.." << endl;
			lane2.pop();
			cout << "Car " << vehicle.plate << " has left!" << endl;
			cout << "Car " << vehicle.plate << " moved " << currentCar.counter
				<< " time(s) for other cars" << endl << endl;
		}

		cout << "Car " << vehicle.plate << " in lane 1 wants to come out" << endl;
		cout << "One moment, moving cars in front out of the way..." << endl;
		while (vehicle != lane2.Top())
		{
			currentCar = lane2.Top();
			if (!lane1.IsFull())
			{
				currentCar.counter++;
				lane1.push(lane2.Top());
				lane2.pop();
			}
			else
			{
				cout << "Other lane full! Moving car " << currentCar.plate
					<< " into the street temporarily..." << endl;
				currentCar.counter++;
				street.push(lane2.Top());
				lane2.pop();
			}
		}

		lane2.pop();
		cout << "Car " << vehicle.plate << " has left!" << endl;
		cout << "Car " << vehicle.plate << " moved " << currentCar.counter
			<< " time(s) for other cars" << endl << endl;

		while (!street.IsEmpty())
		{
			currentCar = street.Top();
			if (!lane1.IsFull())
			{
				cout << "Moving car " << currentCar.plate
					<< " back into the garage" << endl;
				lane1.push(street.Top());
				street.pop();
			}
			else if (!lane2.IsFull())
			{
				cout << "Moving car " << currentCar.plate
					<< " back into the garage" << endl;
				lane2.push(street.Top());
				street.pop();
			}
		}
	}
}

#endif
