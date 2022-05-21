#ifndef _FLOOD_MATRIX_H_
#define _FLOOD_MATRIX_H_

#include <time.h>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>

/**
 * Returns an adjacency matrix with zero.
 */
gsl_spmatrix_uint* empty_matrix(size_t size1, size_t size2);

/**
 * Clears matrix memory blocs. 
 */
void matrix_free(gsl_spmatrix_uint *t);

/**
 * Returns graph edge corresponding to (i,j) matrix element value. 
 */
int matrix_get_edge(gsl_spmatrix_uint *t, size_t i, size_t j);

/**
 * Appends an edge the graph by changing matrix (i,j) value to 1. 
 */
void matrix_add_edge(gsl_spmatrix_uint *t, size_t i, size_t j);

/**
 * Returns a t matrix copy. 
 */
gsl_spmatrix_uint* matrix_copy(gsl_spmatrix_uint* t);

/**
 * Fills neighbour array with existing neighbours indexes of 'position' element.
 * Put -1 for element not neighbours of i element.
 */
void matrix_fill_neighbours(gsl_spmatrix_uint *t, size_t position, int *neighbours);

/**
 * Returns matrix as a string.
 */
char *matrix_display(gsl_spmatrix_uint *t);

/**
 * Displays the drawing of the graph corresponding to 't' matrix.
 */
void matrix_display_graph_drawing(gsl_spmatrix_uint *t);


#endif // _FLOOD_MATRIX_H_
