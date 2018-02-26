#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
  Inputs:   struct matrix * points
  int x
  int y
  int z 
  Returns: 
  adds point (x, y, z) to points and increment points.lastcol
  if points is full, should call grow on points
  ====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol==points->cols)
    grow_matrix(points,points->cols+1);
  points->m[0][points->lastcol]=x;
  points->m[1][points->lastcol]=y;
  points->m[2][points->lastcol]=z;
  points->m[3][points->lastcol]=1;
  points->lastcol++;
}

/*======== void add_edge() ==========
  Inputs:   struct matrix * points
  int x0, int y0, int z0, int x1, int y1, int z1
  Returns: 
  add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
  should use add_point
  ====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points,x0,y0,z0);
  add_point(points,x1,y1,z1);
}

/*======== void draw_lines() ==========
  Inputs:   struct matrix * points
  screen s
  color c 
  Returns: 
  Go through points 2 at a time and call draw_line to add that line
  to the screen
  ====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int col=0;
  int x,y,x1,y1;
  while (col<points->lastcol) {
    x=points->m[0][col];
    y=points->m[1][col];
    col++;
    x1=points->m[0][col];
    y1=points->m[1][col];
    draw_line(x,y,x1,y1,s,c);
    col++;
  }
}


void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if(x0 > x1)
    draw_line(x1,y1,x0,y0,s,c);
  int a = y1-y0;
  int b = x0-x1;
  int d;

  double m = ((double)a) / (x1-x0);

  //octants 1 and 5
  if(m >= 0 && m <= 1){
    d = 2 * a + b;
    while(x0 <= x1){
      plot(s, c, x0, y0);
			
      if(d > 0){
	y0++;
	d += 2 * b;
      }
      x0++;
      d += 2 * a;
    }
  }
  //octants 2 and 6
  else if(m > 1){
    d = a + 2 * b;
    while (y0 <= y1){
      plot(s, c, x0, y0);
      if(d < 0){
	x0++;
	d += 2 * a;
      }
      y0++;
      d += 2 * b;
    }
  }
  //octants 3 and 7
  else if(m < -1){
    d = a - 2 * b;
    while (y0 >= y1){
      plot(s, c, x0, y0);
      if(d > 0){
	x0++;
	d += 2 * a;
      }
      y0--;
      d -= 2 * b;
    }
  }
  //octants 4 and 8
  else if(m < 0 && m >= -1){		
    d = 2 * a - b;
    while (x0 <= x1){
      plot(s, c, x0, y0);
      if(d < 0){
	y0--;
	d -= 2 * b;
      }			
      x0++;
      d += 2 * a;
    }
  }
} //end draw_line
