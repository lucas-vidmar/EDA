#include "Point.h"

using namespace std;

Point::Point() //constructor default
{
	x = 0;
	y = 0;
	angle = 0;
}

void Point::Set_Position(float x_,float y_) 
{
	x = x_;
	y = y_;
}

void Point::Set_Angle(int angle_)
{
	angle = angle_;
}

double Point::getX()
{
	return x;
}
double Point::getY() 
{
	return y;
}


double Point::Get_Angle() 
{
	return angle;
}


void Point::setEverything(double x_, double y_, double angle_) {
	x = x_;
	y = y_;
	angle = angle_;
}


    
