#include <iostream>
#include <string>
using namespace std;
/*include all the necessary files, libraries, etc. here, if any*/

/*if you choose not to write the 5 required classes in seperate .h and .cpp files, then write them here*/
class shape
{
public:
	shape(string name): myName(name) {}
	~shape() {}

	virtual float perimeter() const = 0;
	virtual float area() const = 0;
	virtual float volume() const  = 0;
	virtual string getName() {return myName;};

protected:
	string myName;
};

float shape::perimeter() const
{
	return 0;
}

float shape::area() const
{
	return 0;
}

float shape::volume() const
{
	return 0;
}

class TwoDShape: public shape
{
public:
	TwoDShape (string name): shape(name) {}
	~TwoDShape() {}

	virtual float volume() const
	{
		return 0;
	}
};

class ThreeDShape: public shape
{
public:
	ThreeDShape (string name): shape(name) {}
	~ThreeDShape() {}

	virtual float perimeter() const
	{
		return 0;
	}
};

class rectangle: public TwoDShape
{
public:
	rectangle(float w, float l, string name): width(w), length(l), TwoDShape(name) {}
	~rectangle() {}

	virtual float perimeter() const
	{
		return 2*(width + length);
	}
	virtual float area() const
	{
		return (width*length);
	}

private:
	float width;
	float length;
};

class box: public ThreeDShape
{
public:
	box(float w, float l, float h, string name): width(w), length(l), height(h), ThreeDShape(name) {}
	~box() {}

	virtual float area() const
	{
		return 2*((width*length)+(width*height)+(length*height));
	}
	virtual float volume() const
	{
		return width*length*height;
	}

private:
	float width;
	float length;
	float height;
};

shape* getShape() 
{
	shape *myshape;
	char option;
	bool loop = 1;
	while(loop)
	{
		cout << endl << "choose an option (1 or 2): " << endl << "1. Rectangle" << endl << "2. Box" << endl;
		cin >> option;

		if (option == '1')
		{
			float width, length;
			string name;
			cout << "You chose rectangle. Give it's width, length and name:" << endl;
			cin >> width >> length >> name;

			myshape = new rectangle(width, length, name);
			loop = 0;
		}
		else if (option == '2')
		{
			float width, length, height;
			string name;
			cout << "You chose box. Give it's width, length, height and name:" << endl;
			cin >> width >> length >> height >> name;

			myshape = new box(width, length, height, name);
			loop = 0;
		}
		else
		{
			cout << "UNAVILABLE OPTION CHOSEN. Try again." << endl;
			loop = 1;
		}
	}

	return myshape;
}

int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		shape_1 = getShape();

		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();

		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}