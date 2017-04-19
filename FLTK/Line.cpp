/******************************************************************************
* 
*  Andrew Douglass
*  April 19th 2017
*  Line.cpp
* 
*******************************************************************************
* 
*  Description: This file holds the member function definitions for the Line 
*               class. The specifications of the line including thickness, 
*               coordinates, and color can all be retrieved and set. The draw 
*               and print parameter functions override those from the Shape 
*               class.  
* 
******************************************************************************/

#include <iostream>
#include <FL/fl_draw.H>
#include "Line.h"

using std::cout;
using std::endl;

/* Default constructor to initialize a default line */
Line::Line()
  :Shape(Point(0,0), black), second(Point(0,0)), thickness(0) { }

/* Constructor to initialize the line parameters */
Line::Line(Point p1, Point p2, Color c, int thick)
  :Shape(p1, c), second(p2), thickness(thick) { }

/* Return the X coordinate of the first point */
int Line::getX1() const {
  return position.x;
}

/* Return the Y coordinate of the first point */
int Line::getY1() const {
  return position.y;
}

/* Return the X coordinate of the second point */
int Line::getX2() const {
  return second.x;
}

/* Return the Y coordinate of the second point */
int Line::getY2() const {
  return second.y;
}

/* Return the thickness of the line */
unsigned int Line::getThickness() const {
  return thickness;
}

/* Set the new thickness of the line */
void Line::setThickness(unsigned int newThick) {
  thickness = newThick; 
}

/* Set the new color of the line */
void Line::setColor(Color newColor) {
  linecolor = newColor; 
}

/* Set the new starting and ending point of the line */
void Line::setPoints(Point newP1, Point newP2) {
  position.x = newP1.x;
  position.y = newP1.y;
  second.x = newP2.x;
  second.y = newP2.y;
}

/* Draw the line on the respective window */
void Line::draw() {
  /* Change the color that will be drawn */
  fl_color(linecolor);   
  /* Change the thickness of the line */
  fl_line_style(0, thickness, 0);
  /* Draw the line with the respective coordinates */
  fl_line(position.x, position.y, second.x, second.y);
}

/* Print the coordinates, color, and thickness of the line to cout */
void Line::print_parameters() {
  cout << "Line: x1=" << position.x << "; y1=" << position.y 
       << "; x2=" << second.x << "; y2=" << second.y << "; color="
       << linecolor << "; thickness=" << thickness << endl;
}
