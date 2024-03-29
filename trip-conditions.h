#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "avl-tree.h"

typedef bool** GraphMatrix;

typedef struct _road {
  int city1, city2;
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
    destroy_condition_structures(condition->next);
    free(condition->roads);
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

void visit_city(GraphMatrix graph, int citiesCount, int currCity, int availableTolls, TreeNode **tree)
{
  *tree = tree_add_node(*tree, tree_create_node(currCity));

  if (availableTolls) {
    int i, j = currCity - 1;
    for (i = 0; i < citiesCount; i++) {
      if (graph[i][j]) {
        visit_city(graph, citiesCount, i + 1, availableTolls - 1, tree);
      }
    }
  }
}

int *evaluate_visitable_cities(Condition *condition)
{
  TreeNode *tree = NULL;
  GraphMatrix graph = graph_mount(condition);

  visit_city(graph, condition->citiesCount, condition->currCity, condition->maxTools, &tree);
  graph_destroy(graph);

  int citiesCount = tree_count_nodes(tree);
  tree = tree_remove_node(tree, condition->currCity);
  int *visitedCities = (int *) calloc(citiesCount, sizeof(int));
  add_to_list(tree, visitedCities, 0);

  return visitedCities;
}
