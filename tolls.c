#include <stdlib.h>
#include <stdio.h>
#include "trip-conditions.h"

#define true 1
#define false 0
typedef char bool;

void validate_condition_params(int, int, int, int);
void validate_roads_params(int, int, int);

void main()
{
  int citiesCount, roadsCount, currCity, maxTools;
  Condition *conditionNode = NULL;
  Condition *conditions = NULL;
  Road *roads = NULL;

  while (true) {
    printf("Add new condition: "); // DEBUG: remove on production
    scanf("%i %i %i %i", &citiesCount, &roadsCount, &currCity, &maxTools);

    if (citiesCount == 0 && roadsCount == 0 && currCity == 0 && maxTools == 0) break;
    validate_condition_params(citiesCount, roadsCount, currCity, maxTools);

    roads = (Road *) malloc(sizeof(Road) * roadsCount);
    int i;
    for (i = 0; i < roadsCount; i++) {
      printf("Add road %i of %i: ", i + 1, roadsCount); // DEBUG: remove on production
      scanf("%i %i", &roads[i].city1, &roads[i].city2);
      validate_roads_params(citiesCount, roads[i].city1, roads[i].city2);
    }

    conditionNode = create_condition_node(citiesCount, roadsCount, currCity, maxTools, roads);
    add_condition_node(&conditions, conditionNode);
  }

  conditionNode = conditions;
  while (conditionNode) {
    printf("%i - %i - %i - %i - Roads: ",
      conditionNode->citiesCount,
      conditionNode->roadsCount,
      conditionNode->currCity,
      conditionNode->maxTools
    );
    int i;
    for (i = 0; i < conditionNode->roadsCount; i++) {
      printf("(%i, %i)",
      conditionNode->roads[i].city1,
      conditionNode->roads[i].city2
      );
      printf("%s", i == conditionNode->roadsCount -1 ? "\n" : ", ");
    }
    conditionNode = conditionNode->next;
  }

  destroy_condition_structures(conditions);
}

void validate_condition_params(int citiesCount, int roadsCount, int currCity, int maxTools)
{
  if (citiesCount < 1 || citiesCount > 50) {
    printf("\tNumero de cidades deve ser entre 1 e 50\n");
    exit(1);
  }
  if (roadsCount < 1 || roadsCount > 2500) {
    printf("\tNumero de estradas deve ser entre 1 e 2500\n");
    exit(1);
  }
  if (currCity < 1 || currCity > citiesCount) {
    printf("\tCidade atual deve ser entre 1 e %i\n", citiesCount);
    exit(1);
  }
  if (maxTools < 1 || maxTools > citiesCount) {
    printf("\tQuantidade de pedagios a pagar deve ser entre 1 e %i\n", citiesCount);
    exit(1);
  }
}

void validate_roads_params(int citiesCount, int city1, int city2)
{

  if (city1 < 1 || city1 > citiesCount || city2 < 1 || city2 > citiesCount) {
    printf("\tAs cidades identificadas devem ser entre 1 e %i\n", citiesCount);
    exit(1);
  }
}
