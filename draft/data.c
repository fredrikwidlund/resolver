#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dynamic.h>

typedef struct point point;
typedef struct data  data;
typedef struct rule  rule;

struct point
{
  char *key;
  char *value;
  list  parents;
};

struct data
{
  list  points;
};

struct rule
{
  char *name;
  list  inputs;
};

void data_construct(data *d)
{
  list_construct(&d->points);
}

point *data_add_point(data *d, char *key, char *value)
{
  point *p;

  p = list_push_back(&d->points, NULL, sizeof (point));
  p->key = strdup(key);
  p->value = strdup(value);
  list_construct(&p->parents);
  return p;
}

void point_add_parent(point *p, point *parent)
{
  if (parent)
    list_push_back(&p->parents, &parent, sizeof parent);
}

void data_export_point(point *p)
{
  point **i;
  int next = 0;

  list_foreach(&p->parents, i)
    {
      if (next)
        printf(",");
      data_export_point(*i);
      next = 1;
    }
  if (next)
    printf(",");
  printf("%s=%s", p->key, p->value);
}

void data_export(data *d)
{
  point *p;

  list_foreach(&d->points, p)
    {
      printf("[data] ");
      data_export_point(p);
      printf("\n");
    }
}

void rule_construct(rule *r, char *name)
{
  r->name = strdup(name);
  list_construct(&r->inputs);
}

void rule_add_input(rule *r, char *input)
{
  list_push_back(&r->inputs, input, strlen(input) + 1);
}

void apply(data *d, rule *r)
{
  
}

int main()
{
  data d;
  point *p1, *p2, *p3, *p4, *p5;
  rule r;

  data_construct(&d);
  p1 = data_add_point(&d, "user", "svt");
  p2 = data_add_point(&d, "net", "185.102.101.0/28");
  data_add_point(&d, "net", "185.102.103.0/28");
  p3 = data_add_point(&d, "ip", "185.102.101.1");
  point_add_parent(p3, p2);
  p4 = data_add_point(&d, "tcp", "80");
  point_add_parent(p4, p3);
  p5 = data_add_point(&d, "password", "secret");
  point_add_parent(p5, p1);
  point_add_parent(p5, p4);


  rule_construct(&r, "scan-alive");
  rule_add_input(&r, "net");

  apply(&d, &r);

  data_export(&d);
}
