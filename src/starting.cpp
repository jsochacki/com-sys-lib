#include <iostream>

#include <com_sys_lib/inc/starting.h>
#include <gsl/gsl_linalg.h>

namespace com_sys_lib
{
   namespace matrix_decompositions
   {
      void CSLDECLSPEC
      lu_decomposition(double A_data[], double b_data[])
      {
         // Access the above C arrays through GSL views
         gsl_matrix_view A = gsl_matrix_view_array(A_data, 4, 4);
         gsl_vector_view b = gsl_vector_view_array(b_data, 4);

         // Print the values of A and b using GSL print functions
         std::cout << "A = \n";
         gsl_matrix_fprintf(stdout, &A.matrix, "%lf");

         std::cout << "\nb = \n";
         gsl_vector_fprintf(stdout, &b.vector, "%lf");

         // Allocate memory for the solution vector x and the permutation perm:
         gsl_vector*      x    = gsl_vector_alloc(4);
         gsl_permutation* perm = gsl_permutation_alloc(4);

         // Decompose A into the LU form:
         int signum;
         gsl_linalg_LU_decomp(&A.matrix, perm, &signum);

         // Solve the linear system
         gsl_linalg_LU_solve(&A.matrix, perm, &b.vector, x);

         // Print the solution
         std::cout << "\nx = \n";
         gsl_vector_fprintf(stdout, x, "%lf");

         // Release the memory previously allocated for x and perm
         gsl_vector_free(x);
         gsl_permutation_free(perm);
      }

   }   // namespace matrix_decompositions
}   // namespace com_sys_lib
