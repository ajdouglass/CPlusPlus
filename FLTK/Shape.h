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
*  Description: Base Shape class from which other shape classes can be 
*               derived, and Color enum and Point struct for descriptive 
*               shape object feautures. 
* 
******************************************************************************/

#ifndef SHAPE_H
#define SHAPE_H

#include <FL/Fl_Widget.H>

/* Color enum is a simple translation to the FLTK color definitions */
enum Color {
  red = FL_RED,
  blue = FL_BLUE,
  green = FL_GREEN,
  yellow = FL_YELLOW,
  white = FL_WHITE,
  black = FL_BLACK,
  magenta = FL_MAGENTA,
  cyan = FL_CYAN
};

/* Point struct to define the x and y coordinates to position the shapes */
struct Point {
  int x, y;
  Point();
  Point(int x, int y);
};

/* Shape class to define, position, and draw basic shapes in FLTK */
class Shape : public Fl_Widget {
public:
  /* Default constructor to create a default widget */
  Shape();
  /* Constructor to initialize the color and reference point for the shape */
  Shape(Point p, Color c);
  
  /* Set the color of the corresponding shape */
  void set_color(Color c);
  /* Get the color of the corresponding shape */
  Color get_color() const;
  /* Set the reference point for the shape */
  void set_position(Point p);
  /* Get the reference point for the shape */
  Point get_position() const;

  /* Force the inherited shape classes to override these functions */
  virtual void draw() = 0;
  virtual void print_parameters() = 0;
protected:
  /* Position of the point is defined by the top-left corner */
  Point position; 
  /* Hold the color for the shape */
  Color linecolor;
};

#endif
