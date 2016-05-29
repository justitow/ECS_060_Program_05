#ifndef TRAIN_H
#define	TRAIN_H

#include "TrainRunner.h"
#include "StationMap.h"


class Train
{
private:
  int numStations;
  int numCars;
  Station* stations;
  StationMap* stationMaps;
  int* distances;

public:
  Train(Station *stations, int numStations, int numCars);
  void run(Car *cars, Operation *operations, int *numOperations);

}; // class train 

#endif	// TRAIN_H

