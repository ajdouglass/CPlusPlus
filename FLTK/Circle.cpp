/******************************************************************************
* 
*  Andrew Douglass
*  April 19th 2017
*  Circle.cpp
* 
*******************************************************************************
* 
*  Description: This file has the member function definitions for the Circle 
*               class. This includes the functions to set and retrieve the 
*               different aspects of the circle including color, thickness, 
*               radius, and circle center. 
* 
******************************************************************************/

#include <iostream>
#include <FL/fl_draw.H>
#include "Circle.h"

using std::cout;
using std::endl;

/* Default constructor to create a non-showing circle */
Circle::Circle()
  :Shape(Point(0,0), black), radius(0), fillCircle(false), circleThickness(0), 
         border(false), borderColor(black), borderThickness(0) { }

/* Constructor to intialize the a filled circle with the corresponding 
   parameters */
Circle::Circle(unsigned int r, Point p, Color c, bool fill)
  :Shape(p, c), radius(r), fillCircle(fill), circleThickness(0), 
         border(false), borderColor(black), borderThickness(0) { }
         
/* Constructor to intialize the parameters of the circle, this sets the 
   default parameters for the border */
Circle::Circle(unsigned int r, Point p, Color c, bool fill, unsigned int thick)
  :Shape(p, c), radius(r), fillCircle(fill), circleThickness(thick), 
         border(false), borderColor(black), borderThickness(0) { }

/* Set the border parameters for the circle */
void Circle::setBorder(bool bord, Color bColor, unsigned int thick) {
  border = bord;
  borderColor = bColor; 
  borderThickness = thick; 
}

/* Set the radius of the circle */
void Circle::setRadius(unsigned int r) {
  radius = r;
}

/* Set the new center of the circle */
void Circle::setCenter(Point newCenter) {
  position.x = newCenter.x;
  position.y = newCenter.y;
}

/* Set the new color of the circle */
void Circle::setColor(Color newColor) {
  linecolor = newColor; 
}

/* True will fill the circle while false will leave it hallow. If set to 
   false the border properties will be disabled. */
void Circle::setFill(bool newFill) {
  fillCircle = newFill; 
}

/* Return the radius of the circle */
unsigned int Circle::getRadius() const {
  return radius;
}

/* Return the thickness of the circle. Note this is not used when 
   the fillCircle data member is true. */
unsigned int Circle::getCircleThickness() const {
  return circleThickness; 
}

/* Get X coordinate of the circle center */
int Circle::getCenterX() const {
  return position.x;
}

/* Get Y coordinate of the circle center */
int Circle::getCenterY() const {
  return position.y;
}

/* Return true if the circle should be filled in */
bool Circle::isFilled() const {
  return fillCircle; 
}

/* Return true if the circle has a border */
bool Circle::hasBorder() const {
  return border; 
}

/* Get the thickness of the border around the circle */
unsigned int Circle::getBorderThickness() const {
  return borderThickness; 
}

/* Draw the circle based on its parameters to the respective window */
void Circle::draw() {
  fl_color(linecolor);
  if(fillCircle) {
    /* Draw a filled circle with the corresponding color */
    fl_pie(position.x, position.y, 2*radius, 2*radius, 0, 360);
    if(border) {
      /* Draw the border with the respective color */
      fl_line_style(0, borderThickness, 0);
      fl_color(borderColor); 
      fl_arc(position.x, position.y, 2*radius, 2*radius, 0, 360);
    }
  }
  else {
    /* Draw a hallow circle with the respective color */
    fl_line_style(0, circleThickness, 0); 
    fl_arc(position.x, position.y, 2*radius, 2*radius, 0, 360);
  }
}

/* Print the circle attributes to cout */
void Circle::print_parameters() {
  cout << "Circle: " << "radius=" << radius << "; centerX=" << position.x
       << "; centerY=" << position.y << "; fill=" << fillCircle << "; border="
       << border << endl;
}
