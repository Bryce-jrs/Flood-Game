#ifndef _FLOOD_FILE_MANAGER_H_
#define _FLOOD_FILE_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LENGTH 20002

/**
 * Returns 'indLine' line of file, NULL on error.
 */
char *readFileLine(char *filename, int lineNb);

#endif // _FLOOD_FILE_MANAGER_H_
