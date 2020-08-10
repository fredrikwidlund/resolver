#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <dynamic.h>

typedef struct data data;
struct data
{
  vector values;
};

typedef struct state state;
struct state
{
  list history;
  list rules;
  maps data;
};

static void release(void *o)
{
  free(*(char **) o);
}

static void data(state *state, vector *args)
{
  char *name = *(char **)vector_front(args);

  maps_insert(&state->data, strdup(name),  keys[i], (uintptr_t) values[i], data_release);

}

static void rule(state *state, vector *args)
{
  printf("rule\n");
}

static void command(state *state, vector *args)
{
  if (strcmp(*(char **)vector_front(args), "rule") == 0)
    {
      vector_erase(args, 0, release);
      rule(state, args);
    }
  else if (strcmp(*(char **)vector_front(args), "data") == 0)
    {
      vector_erase(args, 0, release);
      data(state, args);
    }
  else
    printf("<unknown command>\n");
}

static void input(char *prompt, vector *args)
{
  string s;
  char *line;

  while (1)
    {
      line = readline(prompt);
      if (!line)
        return;

      string_construct(&s);
      string_append(&s, line);
      free(line);
      string_split(&s, " ", args);
      string_destruct(&s);
      if (vector_size(args))
        return;
    }
}

int main()
{
  state state;
  vector args;

  list_construct(&state.history);
  list_construct(&state.rules);
  maps_construct(&state.data);

  while (1)
    {
      input("> ", &args);
      if (vector_size(&args) == 0)
        break;
      command(&state, &args);
      vector_destruct(&args, release);
    }

  printf("\n");
  list_destruct(&state.history, NULL);
  list_destruct(&state.rules, NULL);
  maps_destruct(&state.data, NULL);
}
