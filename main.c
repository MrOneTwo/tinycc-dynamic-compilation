#include "tcc_local/libtcc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>


void signal_handler(int sig)
{
  exit(EXIT_SUCCESS);
}


// Here, a set of functions that the dynamically compiled script has to have get typedefed.
typedef char* (*script_hello)(void);
typedef char* (*script_bye)(void);


typedef struct
script_t
{
  char* path;
  void* program;
  time_t time_modified;

  script_hello hello;
  script_bye bye;
} script_t;


static void
tcc_error(void* opaque, const char* msg)
{
  printf("[TCC:ERR] %s\n", msg);
}


static int
compile_program(script_t* script)
{
  TCCState* tcc = tcc_new();
  if (!tcc)
  {
    printf("[TCC:ERR] Failed to create tcc context!\n");
    return -1;
  }

  tcc_set_lib_path(tcc, "./tcc_local");
  tcc_add_include_path(tcc, "./tcc_local");

  tcc_set_error_func(tcc, 0x0, tcc_error);
  tcc_set_options(tcc, "-g");
  tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);

  int ret = tcc_add_file(tcc, script->path);
  if (ret < 0)
  {
    printf("[TCC:ERR] Failed to add tcc file!\n");
    tcc_delete(tcc);
    return -1;
  }

  // tcc_relocate called with NULL returns the size that's necessary for the added files.
  script->program = calloc(1, tcc_relocate(tcc, NULL));
  if (!script->program)
  {
    printf("[TCC:ERR] Failed to allocate memory for the program!\n");
    tcc_delete(tcc);
    return -1;
  }

  // Copy code to memory passed by the caller. This is where the compilation happens (I think...).
  ret = tcc_relocate(tcc, script->program);
  if (ret < 0)
  {
    printf("[TCC:ERR] Failed to allocate memory for the program!\n");
    tcc_delete(tcc);
    return -1;
  }

  script->hello = (script_hello)tcc_get_symbol(tcc, "target_hello");
  script->bye = (script_bye)tcc_get_symbol(tcc, "target_bye");
  
  return 0;
}


int
main(int argc, char* argv[])
{
  signal(SIGINT, signal_handler);

  script_t script;
  script.path = argv[1];

  while (1)
  {
    struct timespec t = {};
    t.tv_sec = 0;
    t.tv_nsec = 200000000;
    nanosleep(&t, &t);

    compile_program(&script);
    printf("%s\n", script.hello());
    printf("%s\n", script.bye());
  }

}
