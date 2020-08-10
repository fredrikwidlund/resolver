
typedef struct point point;
typedef struct data  data;

struct point
{
  list  parents;
  char *key;
  char *value;
};

struct data
{
  list  points;
};

void data_construct(data *d)
{
  list_construct(&data->points);
}

int main()
{
  data d;

  data_construct(&d);
}
