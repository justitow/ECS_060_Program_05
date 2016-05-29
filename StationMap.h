//
// Created by Justin Weich on 5/29/16.
//

#ifndef ECS_060_PROGRAM_05_TRAINSTATIONS_H
#define ECS_060_PROGRAM_05_TRAINSTATIONS_H


#include "BinaryHeap.h"
#include "TrainRunner.h"

class StationNode
{
  bool known;
  int distance;
  StationNode* start;
  Station* stations;
public:
  StationNode();
};

class StationMap
{

public:
  StationMap();
};


#endif //ECS_060_PROGRAM_05_TRAINSTATIONS_H
