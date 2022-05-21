#include "file_manager.h"

char *readFileLine(char *filename, int lineNb) {
    FILE *f = fopen(filename, "r" );
    int i = 0;
    char *line = NULL;

    if (f == NULL) {
      return NULL;
    }

    line = malloc(sizeof(*line)*MAX_LENGTH);
    
    while (!feof(f) && i < lineNb) {
        fgets(line, MAX_LENGTH, f);
	
    	if (ferror(f)) {
    	  free(line);
    	  fclose(f);
    	  return NULL;
    	}
	
    	++i;
    }

    fclose(f);

    return line;
}
