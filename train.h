#ifndef TRAIN_H
#define	TRAIN_H

#include "TrainRunner.h"
#include "StationNode.h"

#include "CarNode.h"

class Train
{
private:
  int numStations;
  int numCars;

  int loadedCars;
  int totalCars;
  Station* stations;
  StationMap* stationz;
  int currentStation;

  CarNode* trainHead;
  CarNode* trainTail;

  int curr_time;
  int destination;

public:
  Train(Station *stations, int numStations, int numCars);
  void run(Car *cars, Operation *operations, int *numOperations);

  void load(Operation *operations, int *numOperations);
  void unload(Operation *operations, int *numOperations);

  void mov(Operation *operations, int *numOperations, StationNode* node);
}; // class train 

#endif	// TRAIN_H

