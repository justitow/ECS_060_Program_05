//
// Created by Justin Weich on 5/31/16.
//

#ifndef ECS_060_PROGRAM_05_CARNODE_H
#define ECS_060_PROGRAM_05_CARNODE_H

#include <iostream>

using namespace std;

class CarNode
{
public:
  CarNode* next;
  CarNode* prev;

  int origin;
  int destination;
  int ID;
  int distance;

  CarNode(int origin, int destination, int identity);
};

#endif //ECS_060_PROGRAM_05_CARNODE_H
