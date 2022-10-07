#include "matrix.h"
#include<iostream>

// Matrix constructer
Matrix::Matrix(int *s, int sl, int initial_value)
{
   // getting the length out of the shape array, and saving the shape array
   shape_length = sl;
   shape = new int[shape_length];
   multiplier = new int[shape_length];
   print_ind_ord = new int[shape_length];
   for(int i = 0; i < shape_length; i++)
   {
      // Multiplier initialization
      if(i==0)
      {
         multiplier[i] = 1;
      }
      else
      {
         multiplier[i] = multiplier[i-1]*s[i-1];
      }

      // Shape initialization
      shape[i] = s[i];

      // index order initialization
      if(shape_length == 1)
      {
         print_ind_ord[0] = 0;
      }
      else
      {
         // We swap the order so that we can print in and have it look normal
         if(i==0)
         {
            print_ind_ord[0] = 1;
            print_ind_ord[1] = 0;
         }
         else if(i>1)
         {
            print_ind_ord[i] = i;
         }
      }
   }

   // Allocating the array and initializing the values
   mat = new int[multiplier[shape_length-1]*s[shape_length-1]];
   for(int i = 0; i<multiplier[shape_length-1]*s[shape_length-1]; i++)
   {
      mat[i] = initial_value;
   }
}

// Matrix destructor
Matrix::~Matrix()
{
   delete [] mat;
   delete [] shape;
   delete [] multiplier;
   delete [] print_ind_ord;
}

///////////////////////////////////////////////////////////////////////////////
// Input/Output Functions
///////////////////////////////////////////////////////////////////////////////

int get_index(int* loc, int shape_length, int* multiplier)
{
   int index = 0;
   for(int i = 0; i<shape_length; i++)
   {
      index += loc[i]*multiplier[i];
   }
   return index;
}

void print_opening_closing_braces(int num_wrapped, int shape_length)
{
   // Prints a tab if nothing wrapped
   if (num_wrapped == 0)
   {
      std::cout << "\t";
   }
   // Prints the number of closing and opening braces
   else if((num_wrapped > 0) && (num_wrapped <= shape_length))
      {
         for(int i=0; i<num_wrapped; i++)
         {
            std::cout << "]";
         }
         std::cout << std::endl;
         if (num_wrapped < shape_length)
         {
            for(int i=0; i<shape_length; i++)
            {
               if(i<shape_length-num_wrapped)
               {
                  std::cout << " ";
               }
               else if ((i>=shape_length-num_wrapped)&&(i<shape_length))
               {
                  std::cout << "[";
               }
            }
         }
      }
   return;
}

// Prints the array
void Matrix::print()
{
   // first we get counters so that we print the dimensions correctly
   //int* counters = NULL;
   int counters[shape_length];

   // Initializing the counters values to zero
   for(int i=0; i<shape_length; i++)
   {
      counters[i] = 0;
   }

   // Print an opening bracket for each dimension
   for(int i = 0; i<shape_length; i++)
   {
      std::cout << "[";
   }

   // We print, we increment the counters each time and print endl and brackets
   // as the counter hits the size of its dimension and rolls back to zero.
   for(int i=0; i<multiplier[shape_length-1]*shape[shape_length-1]; i++)
   {
      std::cout << mat[get_index(counters, shape_length, multiplier)];
      // Incrementing to the next index in the array to print and printing
      // closing braces
      int wrapped = 0;
      for(int j=0; j<shape_length; j++)
      {
         // increment the counter in the current index
         counters[print_ind_ord[j]]++;
         // if the counter has wrapped around we set it to zero and increment
         // the next counter in the ordering.
         if(counters[print_ind_ord[j]]>=shape[print_ind_ord[j]])
         {
            counters[print_ind_ord[j]] = 0;
            wrapped++;
         }
         else
         {
            break;
         }
      }
      print_opening_closing_braces(wrapped, shape_length);
   }

   return;
}



///////////////////////////////////////////////////////////////////////////////
// Setting Functions
///////////////////////////////////////////////////////////////////////////////
// Setting a value in the matrix based on matrix/array style indexing
void Matrix::set_value(int* loc, int value)
{
   mat[get_index(loc,shape_length,multiplier)] = value;

   return;
}

// Setting a value in the matrix based on the integer single digit location
void Matrix::set_value(int ind, int value)
{
   mat[ind] = value;

   return;
}




///////////////////////////////////////////////////////////////////////////////
// Overloaded Operators
///////////////////////////////////////////////////////////////////////////////
int max(int first, int second)
{
   if(first >= second)
   {
      return first;
   }
   else
   {
      return second;
   }
}

Matrix Matrix::operator+(Matrix &mat1)
{
   // // Checking that the shapes match
   // if(shape_length != mat.get_num_dimensions())
   // {
   //    RAISE_ERROR("ERROR: The matrices do not have same number of dimensions.")
   //    // At some point we will include array broadcasting and this will change
   // }
   // // Checking that each dimension is the same size
   // for(int i = 0; i<shape_length; i++)
   // {
   //    if (shape[i] != mat.get_shape(i))
   //    {
   //       RAISE_ERROR("ERROR: The matrices need to match in each dimension.")
   //    }
   // }

   // Creating the result matrix that we will return
   int ret_dim = max(shape_length, mat1.get_num_dimensions());
   int ret_shape[ret_dim];
   int init_val = 0;
   for(int i = 0; i < ret_dim; i++)
   {
      ret_shape[i] = shape[i];
   }
   Matrix result(ret_shape, ret_dim, init_val);

   // Summing element by element
   for(int i=0; i<multiplier[shape_length-1]*shape[shape_length-1]; i++)
   {
      result.set_value(i, mat1.get_val(i)+mat[i]);
   }

   return result;
}





