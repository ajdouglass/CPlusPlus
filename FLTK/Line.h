/******************************************************************************
* 
*  Andrew Douglass
*  April 19th 2017
*  Line.h
* 
*******************************************************************************
* 
*  Description: This class is designed to draw a line in the FLTK package. 
*               The color, thickness, and location of the line can all be 
*               set through the constructor or the series of public member 
*               functions. 
* 
******************************************************************************/

#ifndef LINE_H
#define LINE_H

#include "Shape.h"

/* Line is inherited through the Shape class */
class Line : public Shape {
public:
  /* Default constructor creates a line that starts and ends at (0, 0), has 
     a thickness of zero and is the color black */
  Line(); 
  /* Constructor to initialize the aspects of the line */
  Line(Point p1, Point p2, Color c, int thick);

  /* Return the X coordinate of the first point */
  int getX1() const;
  /* Return the Y coordinate of the first point */
  int getY1() const; 
  /* Return the X coordinate of the second point */
  int getX2() const;
  /* Return the Y coordinate of the second point */
  int getY2() const;
  /* Return the thickness of the line */
  unsigned int getThickness() const;

  /* Set the new thickness of the line */
  void setThickness(unsigned int newThick); 
  /* Set the new color of the line */
  void setColor(Color newColor); 
  /* Set the new coordinates for the lines two connecting points */
  void setPoints(Point newP1, Point newP2); 
 
  /* Override the Shape draw function to draw the line */
  void draw();
  /* Override the Shape function to print the line parameters to cout */
  void print_parameters();
private:
  /* Hold the coordinates for the second point */
  Point second;
  /* Hold the thickness of the line */
  unsigned int thickness; 
};

#endif

