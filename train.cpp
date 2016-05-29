// Author: Sean Davis

#include "TrainRunner.h"
#include "train.h"
#include <cstring>

Train::Train(Station *stns, int numstns, int numcrs) : numStations(numstns), numCars(numcrs)
{
  this->stations = new Station[numstns];
  memcpy(this->stations, stns, numstns *  sizeof *stns);

  this->distances = new int[numstns];

} // Train()

void Train::explore_options()
{
  for (int i = 0; i < this->numStations; i++)
  {

  }
}

void Train::run(Car *cars, Operation *operations, int *numOperations)
{
  // Students must fill the operations array, and set numOperations.
} // run()
