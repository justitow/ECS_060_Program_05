#ifndef TRAIN_H
#define	TRAIN_H

#include "TrainRunner.h"

class Train
{
private:
  int numStations;
  int numCars;
  Station *stations;

  int* distances;

public:
  Train(Station *stations, int numStations, int numCars);
  void run(Car *cars, Operation *operations, int *numOperations);
  void explore_options();

}; // class train 

#endif	// TRAIN_H

