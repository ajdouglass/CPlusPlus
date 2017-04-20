/******************************************************************************
* 
*  Texas A&M University Computer Science Department
*  April 19th 2017
*  Shape.h
* 
*******************************************************************************
* 
*  Citation: Credit goes to the CSCE 121 course at Texas A&M University. 
*  
*  Description: This contains the member function definitions for the base 
*               shape class. The shape class is derived by other classes to 
*               create the drawing shapes like circle and line. This also 
*               has the two constructors for the Point struct.  
* 
******************************************************************************/

#include <FL/Fl.H>
#include "Shape.h"

/* Create a point with the top-left corner as the coordinates */
Point::Point()
  :x(0), y(0) { }

/* Constructor to initialize the location of the point */
Point::Point(int x, int y)
  :x(x), y(y) { }

/* Default constructor to create a default widget */
Shape::Shape()
  :Fl_Widget(0, 0, 0, 0), position(Point(0,0)), linecolor(black) { }

/* Constructor to initialize the color and reference point for the shape */
Shape::Shape(Point p, Color c)
  :Fl_Widget(p.x, p.y, 0, 0), position(p), linecolor(c) { }

/* Set the color of the shape and its inherited classes */  
void Shape::set_color(Color c) {
  linecolor = c;
}

/* Get the color of the shape and its inherited classes */ 
Color Shape::get_color() const {
  return linecolor;
}

/* Set the top-left corner reference point for the shape */
void Shape::set_position(Point p) {
  position = p;
}

/* Get the top-left corner reference point for the shape */
Point Shape::get_position() const {
  return position;
}
