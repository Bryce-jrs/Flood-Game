#include "options.h"

void init_options(struct options_t *options){
  options->player_names[0] = "./player_min.so";
  options->player_names[1] = "./player_min2.so";
  options->shape = 0;
  options->color_algo = RANDOM;
  options->width = 8;
  options->color_nb = 4;
  options->forbidden_nb=0;
}

void parse_options(int argc, char* argv[], struct options_t *options){
  int opt ;
  init_options(options);
  
  int i = 1;
  while ((opt = getopt(argc, argv, "m:t:c:a:f:")) != -1) {
    switch (opt) {
      case 'm':
        options->width = atoi(optarg);
        i += 2;
        break;
      case 't':
        options->shape = atoi(optarg);
        i += 2;
        break;
      case 'c':
        options->color_nb = atoi(optarg);
        i += 2;
        break;
      case 'a':
        options->color_algo = atoi(optarg);
        i += 2;
        break;
      case 'f':
        options->forbidden_nb= atoi(optarg);
        i += 2;
        break;
      default:
        break;
    }
  }
  
  if (i <= argc) {
    options->player_names[0] = argv[i++];
  }
  if (i <= argc) {
    options->player_names[1] = argv[i];
  }
}
