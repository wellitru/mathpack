#include "matrix.h"
#include<iostream>

// Matrix constructer
Matrix::Matrix(int *s, int initial_value)
{
   // getting the length out of the shape array, and saving the shape array
   shape_length = sizeof(s)/sizeof(s[0]);
   shape = new int[shape_length];
   multiplier = new int[shape_length];
   ind_order = new int[shape_length];
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
         ind_order[0] = 0;
      }
      else
      {
         // We swap the order so that we can print in and have it look normal
         if(i==0)
         {
            ind_order[0] = 1;
            ind_order[1] = 0;
         }
         else if(i>1)
         {
            ind_order[i] = i;
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
   delete [] ind_order;
}

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
         counters[ind_order[j]]++;
         // if the counter has wrapped around we set it to zero and increment
         // the next counter in the ordering.
         if(counters[ind_order[j]]>=shape[ind_order[j]])
         {
            counters[ind_order[j]] = 0;
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