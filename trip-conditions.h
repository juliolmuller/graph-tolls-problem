#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0
typedef char bool;
typedef bool** GraphMatrix;

typedef struct _road {
  int city1, city2;
  struct _road *next;
} Road;

typedef struct _condition {
  int citiesCount, roadsCount, currCity, maxTools;
  Road *roads;
  struct _condition *next;
} Condition;

Condition *create_condition_node(int citiesCount, int roadsCount, int currCity, int maxTools, Road *roads)
{
  Condition *condition = (Condition *) malloc(sizeof(Condition));
  condition->citiesCount = citiesCount;
  condition->roadsCount = roadsCount;
  condition->currCity = currCity;
  condition->maxTools = maxTools;
  condition->roads = roads;
  condition->next = NULL;

  return condition;
}

void add_condition_node(Condition **conditionsList, Condition *newCondition)
{
  if (*conditionsList == NULL) {
    *conditionsList = newCondition;
  } else {
    Condition *aux = *conditionsList;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = newCondition;
  }
}

void destroy_condition_structures(Condition *condition)
{
  if (condition) {
    Road *road, *aux = condition->roads;
    while (aux) {
      road = aux;
      aux = aux->next;
      free(road);
    }
    destroy_condition_structures(condition->next);
    free(condition);
  }
}

GraphMatrix graph_mount(Condition *condition)
{
  int roadsCount = condition->roadsCount;
  int citiesCount = condition->citiesCount;
  GraphMatrix matrix = (bool **) malloc(sizeof(bool *) * citiesCount);

  int i;
  for (i = 0; i < citiesCount; i++) {
    matrix[i] = (bool *) calloc(citiesCount, sizeof(bool));
  }

  for (i = 0; i < roadsCount; i++) {
    int index1 = condition->roads[i].city1 - 1;
    int index2 = condition->roads[i].city2 - 1;
    matrix[index1][index2] = true;
    matrix[index2][index1] = true;
  }

  return matrix;
}

void graph_print(GraphMatrix graph, int size)
{
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      printf("%i ", graph[i][j]);
    }
    printf("\n");
  }
}

void graph_destroy(GraphMatrix graph)
{
  bool **matrix = graph;
  free(*matrix);
  free(matrix);
}
