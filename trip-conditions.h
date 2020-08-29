#include <stdlib.h>
#include <stdio.h>

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
