#ifndef POINT_H
#define POINT_H

#include <cstdlib>
#include <iostream>

#define MAX_SYZE_X 70
#define MAX_SYZE_Y 100
#define MAX_ANGLE 360


class Point {
public:

	Point();
	void Set_Position(float x_,float y_);
	void Set_Angle(int angle_);
	double getX();
	double getY();
	double Get_Angle();
	void setEverything(double x_, double y_, double angle_);					
		
private:				

	/*Data*/
	double x;
	double y;
	double angle;
};


#endif