#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <err.h>

#include <dynamic.h>

#include "graph.h"

typedef struct rule rule;
struct rule
{
  char *name;
  char *input;
};

void rules_add(list *rules, char *name, char *input)
{
  rule *r;

  r = list_push_back(rules, NULL, sizeof *r);
  r->name = strdup(name);
  r->input = strdup(input);
}

void rule_env(node *n)
{
  node **i;

  setenv(n->type, n->value, 1);
  list_foreach(&n->edges, i)
    rule_env(*i);
}

void rule_run(rule *rule, node *node, graph *graph)
{
  FILE *f;
  char *line, *delim;
  size_t size;
  ssize_t n;

  rule_env(node);
  f = popen(rule->name, "r");
  if (!f)
    return;
  line = NULL;
  while (1)
    {
      n = getline(&line, &size, f);
      if (n == -1)
        break;
      line[n - 1] = 0;
      delim = strchr(line, ' ');
      if (delim)
        {
          *delim = 0;
          delim ++;
          graph_connect(graph_node(graph, line, delim), node);
        }
    }
  free(line);
  pclose(f);
}

void rules_apply(list *rules, node *node, graph *graph)
{
  rule *rule;

  list_foreach(rules, rule)
    if (strcmp(rule->input, node->type) == 0)
      rule_run(rule, node, graph);
}

int main()
{
  list rules;
  graph graph;
  node **i;

  //rules_add(&rules, "tcp:scan");

  list_construct(&rules);
  rules_add(&rules, "scan-ip", "net");
  rules_add(&rules, "scan-tcp", "ip");
  rules_add(&rules, "scan-udp", "ip");
  rules_add(&rules, "scan-http", "tcp");

  graph_construct(&graph);
  graph_node(&graph, "net", "1.2.3.4/30");
  list_foreach(&graph.nodes, i)
    rules_apply(&rules, *i, &graph);
  graph_print(&graph);
}
