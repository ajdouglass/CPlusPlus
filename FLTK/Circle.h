/******************************************************************************
* 
*  Andrew Douglass
*  April 19th 2017
*  Circle.h
* 
*******************************************************************************
* 
*  Description: This class is designed to draw a circle in the FLTK package. 
*               The circle can be hollow or filled in and can contain an 
*               optional border around the shape. The color, position, and 
*               thickness of the circle can be customized along with the color 
*               and thickness of the border. Note that the circle thickness 
*               will only apply when the circle is not suppossed to be filled.  
* 
******************************************************************************/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

/* Line is inherited through the Shape class */
class Circle : public Shape {
public:
  /* Default constructor to create non-showing circle */
  Circle();
  /* Constructor to a filled circle with the following parameters */
  Circle(unsigned int r, Point p, Color c, bool fill);
  /* Constructor to intialize the parameters of the circle */
  Circle(unsigned int r, Point p, Color c, bool fill, unsigned int thick);

  /* Set the parameters of the border for the circle */
  void setBorder(bool bord, Color bColor, unsigned int thick); 
  /* Set the new radius of the circle */
  void setRadius(unsigned int r);
  /* Set the new center of the circle */
  void setCenter(Point newCenter); 
  /* Set the new color of the circle */
  void setColor(Color newColor); 
  /* True will fill the circle while false will leave it hallow */
  void setFill(bool newFill); 
  
  /* Return the radius of the circle */
  unsigned int getRadius() const;
  /* Return the thickness of the circle */
  unsigned int getCircleThickness() const; 
  /* Get X coordinate of the circle center */
  int getCenterX() const; 
  /* Get Y coordinate of the circle center */
  int getCenterY() const; 
  /* Return true if the circle should be filled in */
  bool isFilled() const; 
  /* Return true if the circle has a border */
  bool hasBorder() const; 
  /* Get the thickness of the border around the circle */
  unsigned int getBorderThickness() const; 
  
  /* Override the Shape draw function to draw the line */
  void draw();
  /* Override the Shape function to print the line parameters to cout */
  void print_parameters();
private:
  /* Hold the parameters for the circle */
  unsigned int radius, circleThickness;
  bool fillCircle; 
  
  /* This will hold true if the circle has a border */
  bool border; 
  /* Hold the border color and thickness for the circle */
  Color borderColor; 
  unsigned int borderThickness; 
};

#endif
