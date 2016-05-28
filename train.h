#ifndef TRAIN_H
#define	TRAIN_H

#include "TrainRunner.h"

class Train
{
public:
  Train(Station *stations, int numStations, int numCars);
  void run(Car *cars, Operation *operations, int *numOperations);
}; // class train 

#endif	// TRAIN_H

