#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
   // 0 - int, 1 - float, 2 - double, 3 - complex double
   // uint dtype;
   // This is an improvement that will come later, for now only interger arrays
   // will be supported
   // This is 1-dimensional because we will use math indexing
   int *mat;
   int *shape;
   int *multiplier;
   int *ind_order;
   int shape_length;

public:
   Matrix(int *s, int initial_value=0);
   ~Matrix(void);

   void print();

   int dimensions() { return shape_length; }
   int get_shape(int dimension) { return shape[dimension];}
};


#endif