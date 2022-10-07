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
   int *print_ind_ord;
   int shape_length;

public:
   // Constructor/Destructor
   Matrix(int *s, int sl, int initial_value=0);
   ~Matrix(void);

   // Input/Output functions
   void print();

   // Retrival Functions
   int get_dimensions() { return shape_length; }
   int get_shape(int dimension) { return shape[dimension]; }
   int get_num_dimensions() { return shape_length; }
   int* get_multiplier() { return multiplier; }
   int get_val(int index) { return mat[index]; }

   // Setting functions
   void set_value(int* loc, int value);
   void set_value(int ind, int value);


   // Overloading Operators
   Matrix operator+ (Matrix &mat);

};


#endif