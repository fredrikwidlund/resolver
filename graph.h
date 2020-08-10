#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct node  node;
typedef struct graph graph;

struct node
{
  size_t  id;
  char   *type;
  char   *value;
  list    edges;
};

struct graph
{
  list    nodes;
  size_t  count;
};

void  graph_construct(graph *);
node *graph_node(graph *, char *, char *);
void  graph_connect(node *, node *);
void  graph_print(graph *);

/*
struct graph_edge
{
  graph_properties  properties;
  graph_node       *source;
  graph_node       *destination;
};


struct graph_node
{
  graph_properties  properties;
  list              edges;
};

struct graph
{
  graph_properties  properties;
  list              nodes;
};
*/


#endif /* GRAPH_H_INCLUDED */
