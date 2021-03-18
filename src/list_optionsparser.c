/**
 * @file list_optionsparser.c
 * @author your name (you@domain.com)
 * @brief Source file for an options parser for a linked list implementation of Conway's game of life
 * @date 2021-03-16
 */

#include "list_optionsparser.h"

list_options list_default_options()
{
  list_options defaults;

  defaults.consider_torus = false;
  defaults.generate_images = false;
  defaults.expandable = false;
  defaults.print_formatting_help = false;
  defaults.print_to_console = false;

  return defaults;
}

void print_usage(char *exec_name)
{
  fprintf(stderr, "USAGE: %s [-ipte?] filename\n\nOptions:\n  -i: generate image output for each step\n  -p: print simulation steps to console\n  -t: consider the universe as a torus\n  -e: consider the universe as expandable (incompatible with a torus universe!)\n  -?: print source textfile formatting help\n  filename: source textfile to load universe from\n", exec_name);
  exit(EXIT_FAILURE);
}

void do_print_formatting_help()
{
  printf("Source textfiles should be formatted as follows:\n  width height\n  number_of_steps\n  cell structure\n\nIn the cell structure, a dead cell should be represented by . and a live cell by o.\n\nHere is an example for a 3x4 structure:\n  3 4\n  3\n  .o..\n  ..o.\n  ooo.\n");
  exit(EXIT_SUCCESS);
}

list_options parse_options(int argc, char **argv)
{
  list_options options = list_default_options();

  // go through all keyword options (options starting with with -)
  int opt_idx;
  for (opt_idx = 1; opt_idx < argc && argv[opt_idx][0] == '-'; ++opt_idx)
  {
    int idx = 1;
    char opt = argv[opt_idx][idx];
    while (opt != '\0')
    {
      switch (opt)
      {
      case '?':
        options.print_formatting_help = true;
        break;
      case 'p':
        options.print_to_console = true;
        break;
      case 'i':
        options.generate_images = true;
        break;
      case 't':
        options.consider_torus = true;
        break;
      case 'e':
        options.expandable = true;
        break;
      default:
        print_usage(argv[0]);
      }

      ++idx;
      opt = argv[opt_idx][idx];
    }
  }

  if (options.consider_torus && options.expandable)
  {
    fprintf(stderr, "[!] An expandable universe cannot be expandable\n\n");
    print_usage(argv[0]);
  }

  // here, argv[opt_idx] points to the first positional argument, which should be the filename
  char *filename = argv[opt_idx];
  if (filename == NULL && !options.print_formatting_help)
  {
    fprintf(stderr, "[!] Missing filename argument\n\n");
    print_usage(argv[0]);
  }
  options.filename = filename;

  return options;
}
