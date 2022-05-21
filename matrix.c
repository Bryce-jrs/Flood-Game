#include "matrix.h"

gsl_spmatrix_uint* empty_matrix(size_t size1, size_t size2) {
  gsl_spmatrix_uint *t = gsl_spmatrix_uint_alloc(size1, size2);
  gsl_spmatrix_uint_set_zero(t);
  return t;
}

gsl_spmatrix_uint* matrix_coo_to_csr(gsl_spmatrix_uint *t) {
  return gsl_spmatrix_uint_compress(t, GSL_SPMATRIX_CSR);
}

void matrix_free(gsl_spmatrix_uint *t) {
  gsl_spmatrix_uint_free(t);
}

int matrix_get_edge(gsl_spmatrix_uint *t, size_t i, size_t j) {
  return gsl_spmatrix_uint_get(t, i, j);
}

void matrix_add_edge(gsl_spmatrix_uint *t, size_t i, size_t j) {
  gsl_spmatrix_uint_set(t, i, j, 1);
}

gsl_spmatrix_uint* matrix_copy(gsl_spmatrix_uint* t) {
  gsl_spmatrix_uint *cpy = empty_matrix(t->size1, t->size2);

  for(size_t i = 0; i < t->size1; ++i) {
    for(size_t j = 0; j < t->size2; ++j) {
      if (matrix_get_edge(t, i, j) == 1) {
        matrix_add_edge(cpy, i, j);
      }
    }
  }

  return cpy;
}

void matrix_fill_neighbours(gsl_spmatrix_uint *t, size_t position, int *neighbours) {
  gsl_spmatrix_uint *csr = matrix_coo_to_csr(t);
  int i = 0;

  for (int k = csr->p[position]; k < csr->p[position+1]; ++k) {
    neighbours[i] = csr->i[k];
    i++;
  }
  neighbours[i] = -1;

  matrix_free(csr);
}

char *matrix_display(gsl_spmatrix_uint *t) {
  size_t rows = t->size1;
  size_t columns = t->size2;
  int length = 3+columns*rows+(columns-1)*rows+(rows-1);
  char *output = malloc(sizeof(*output)*length);
  int k = 0;

  output[k++] = '(';

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns-1 ; ++j) {
      output[k++] = matrix_get_edge(t, i, j) + '0';
      output[k++] = ',';
    }

    output[k++] = matrix_get_edge(t, i, columns-1) + '0';

    if (i < rows-1) {
      output[k++] = ';';
    }
  }

  output[k++] = ')';
  output[k++] = '\0';
  return output;
}

void matrix_display_graph_drawing(gsl_spmatrix_uint *t) {
  size_t rows = t->size1;
  size_t root = floor(sqrt(rows));

  printf("\n");

  for (size_t i = 0; i < rows-1 ; ++i) {
    printf(" %ld ", i);
    size_t tmp = i%root;

    if (gsl_spmatrix_uint_get(t, i, i+1) == 1) {
      if (i >= 10) {
	printf("--- ");
      } else {
	printf(" --- ");
      }
    }

    if ((tmp == root-1) && (i != 0)) {
      printf("\n");

      size_t k = 1;
      for(size_t j = i+1; j <= i+root; j++) {
	if ((j < rows) && (gsl_spmatrix_uint_get(t, i-root+k, j) == 1)) {
	  printf(" |      ");
	}

	k++;
      }

      printf("\n");
    }
  }

  printf(" %ld ", rows);
}
