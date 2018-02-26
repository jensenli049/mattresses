#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  srand(time(NULL));
  
  screen s;
  color c;
  struct matrix * edges = new_matrix(4, 4);

  struct matrix * square = new_matrix(3,3);
  struct matrix * test = new_matrix(3,2);

  //Testing functions
  printf("Identity Matrix\n");
  ident(square);
  print_matrix(square);

  printf("Random Matrix\n");
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 2; j++)
      test->m[i][j] = rand() % 10;
  print_matrix(test);
  
  printf("Matrix Multiplicaiton(Identity Matrix)\n");
  printf("Start:\n");
  print_matrix(test);
  matrix_mult(square,test);
  printf("Finish:\n");
  print_matrix(test);

  printf("Matrix Multiplicaiton(Normal Matrix)\n");
  square->m[0][2]=3;
  square->m[1][1]=4;
  square->m[2][0]=7;
  print_matrix(square);
  printf("times\n");
  print_matrix(test);
  matrix_mult(square,test);
  printf("Answer:\n");
  print_matrix(test);

  free_matrix(square);
  free_matrix(test);
  
  //---------------------------------------------------------------

  //Drawing  
  int i,j;
  clear_screen(s);

  c.red = 128;
  c.green = 10;
  c.blue = 128;
  
  for(i = 0, j = YRES-1; i < XRES, j >= 0; i+=5, j-=5)
    add_edge(edges, 0, j/2, 0, i/2, 0, 0);
  
  for(i = XRES/2; i < XRES; i+=5)
    add_edge(edges, i, 0, 0, XRES, i-XRES/2, 0);
  
  for(i = XRES/2, j = YRES-1; i < XRES, j >= YRES/2; i+=5, j-=5)
    add_edge(edges, XRES, i, 0, j, YRES, 0);
  
  for(i = XRES/2; i < XRES; i+=5)
    add_edge(edges, 0, i, 0, i-XRES/2, YRES, 0);
  
  draw_lines(edges, s, c);
  
  display(s);
  save_extension(s,"mattresses.png");
  free_matrix( edges );
}
