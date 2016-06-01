//
// Created by Justin Weich on 5/29/16.
//

#ifndef ECS_060_PROGRAM_05_TRAINSTATIONS_H
#define ECS_060_PROGRAM_05_TRAINSTATIONS_H


#include "BinaryHeap.h"
#include "TrainRunner.h"
#include "CarNode.h"


class StationNode

{
public:
  //neccesary stuff for
  StationNode* path;
  bool known;
  int distance;
  int distance_to_path;
  int stationID;

  StationNode();
  friend bool operator<(StationNode& lhs, StationNode& rhs);

};


class StationMap
{


public:

  int stationID;
  bool changed;
  bool mapped;
  Station* stations;
  StationNode* nodes;

  CarNode* parkedCarHead;
  CarNode* parkedCarTail;

  int parkedCars;

  BinaryHeap<StationNode*>* unknown_heap;
  StationMap();
  StationMap(int stationID, Station* stations);
  void map(int numStations);

};



#endif //ECS_060_PROGRAM_05_TRAINSTATIONS_H
