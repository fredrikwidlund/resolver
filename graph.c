#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <dynamic.h>

#include "graph.h"

void graph_construct(graph *g)
{
  list_construct(&g->nodes);
  g->count = 0;
}

node *graph_node(graph *g, char *type, char *value)
{
  node *n;

  n = malloc(sizeof *n);
  n->id = g->count;
  n->type = strdup(type);
  n->value = strdup(value);
  list_construct(&n->edges);
  list_push_back(&g->nodes, &n, sizeof n);
  g->count ++;

  return n;
}

void graph_connect(node *a, node *b)
{
  list_push_back(&a->edges, &b, sizeof b);
}

void graph_print_node(node *n)
{
  node **i;
  int first = 1;

  list_foreach(&n->edges, i)
    {
      first = 0;
      graph_print_node(*i);
    }
  printf("%s%s:%s", first ? "" : ",", n->type, n->value);
}

void graph_print(graph *g)
{
  node **i;

  list_foreach(&g->nodes, i)
    {
      graph_print_node(*i);
      printf("\n");
    }
}
