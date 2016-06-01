// Author: Sean Davis

#include "TrainRunner.h"
#include "train.h"
#include <cstring>

Train::Train(Station *stns, int numstns, int numcrs) : numStations(numstns), numCars(numcrs)
{
  this->stations = new Station[numstns];
  memcpy(this->stations, stns, numstns *  sizeof *stns);
  stationz = NULL;

  currentStation = 0;

  loadedCars = 0;
  totalCars = numcrs;

  trainHead = NULL;
  trainTail = NULL;

  curr_time = 0;
} // Train()


void Train::run(Car *cars, Operation *operations, int *numOperations)
{
  *numOperations = 0;
  stationz = new StationMap[numStations];


  CarNode* node;

  for (int i = 0; i < numCars; i++)
  {
    node = new CarNode(cars[i].origin, cars[i].destination, i);
    if (stationz[node->origin].parkedCarHead == NULL)
    {
      stationz[node->origin].parkedCarHead = node;
      stationz[node->origin].parkedCarTail = node;
      stationz[node->origin].parkedCars += 1;
    }
    else
    {
      stationz[node->origin].parkedCarTail->next = node;
      node->prev = stationz[node->origin].parkedCarTail;
      stationz[node->origin].parkedCarTail = node;
      stationz[node->origin].parkedCars += 1;
    }


  }


  for (int i = 0; i < numStations; i++)
  {
    stationz[i].stationID = i;
    stationz[i].stations = this->stations;
  }


  while(totalCars > 0)
  {
    if (!stationz[currentStation].mapped)
      stationz[currentStation].map(numStations);

    if (stationz[currentStation].parkedCars > 0) {
      while (stationz[currentStation].parkedCars > 0 && loadedCars < 50)
      {

        if (trainHead == NULL)
        {
          trainHead = stationz[currentStation].parkedCarHead;
          trainTail = trainHead;
          if (stationz[currentStation].parkedCarHead->next)
            stationz[currentStation].parkedCarHead->next->prev = NULL;
          if (stationz[currentStation].parkedCarHead == stationz[currentStation].parkedCarTail)
            stationz[currentStation].parkedCarTail = NULL;
          stationz[currentStation].parkedCarHead = stationz[currentStation].parkedCarHead->next;
          trainHead->next = NULL;
          stationz[currentStation].parkedCars -= 1;
          loadedCars += 1;
          operations[*numOperations].ID = trainHead->ID;
          operations[*numOperations].time = curr_time;
          operations[*numOperations].operation = 'P';
          *numOperations += 1;
        }
        else
        {
          trainTail->next = stationz[currentStation].parkedCarHead;
          trainTail->next->prev = trainTail;

          if (stationz[currentStation].parkedCarHead->next != NULL)
          {
            stationz[currentStation].parkedCarHead->next->prev = NULL;
          }
          if (stationz[currentStation].parkedCarHead == stationz[currentStation].parkedCarTail)
            stationz[currentStation].parkedCarTail = NULL;
          stationz[currentStation].parkedCarHead = stationz[currentStation].parkedCarHead->next;
          trainTail->next->next = NULL;
          trainTail = trainTail->next;
          stationz[currentStation].parkedCars -= 1;
          loadedCars += 1;
          operations[*numOperations].ID = trainTail->ID;
          operations[*numOperations].time = curr_time;
          operations[*numOperations].operation = 'P';
          *numOperations += 1;
        }
      }
    }

    if (this->loadedCars > 0)
    {
      node = trainHead;
      while (node != NULL) {
        node->distance = stationz[currentStation].nodes[node->destination].distance;
        int curr_min = 2147483647;

        if (node->distance < curr_min) {
          this->destination = node->destination;
          curr_min = node->distance;
        }

        node = node->next;
      }
    }

   if (this->loadedCars == 0)
   {
     int curr_min = 2147483647;

     for (int i = 0; i < numStations; i++)
     {
       if (stationz[i].parkedCars > 0) {
         if (stationz[currentStation].nodes[i].distance < curr_min && stationz[currentStation].nodes[i].distance > 0) {
           this->destination = i;
         }
       }
     }
   }

    this->mov(operations, numOperations, &stationz[currentStation].nodes[destination]);
    node = trainHead;
    while (node != NULL)
    {
      if (node->destination == currentStation)
      {
        if (node == trainHead)
          trainHead = node->next;
        if (node->prev != NULL)
          node->prev->next = node->next;
        if (node->next != NULL)
          node->next->prev = node->prev;
        if (node == trainTail)
          trainTail = node->prev;
        this->loadedCars -= 1;
        totalCars -= 1;
        operations[*numOperations].ID = node->ID;
        operations[*numOperations].time = curr_time;
        operations[*numOperations].operation = 'D';
        *numOperations += 1;

        cout << "dropped car " << node->ID << endl;

      }

      node = node->next;


    }

  }


  //cout <<
} // run()

void Train::mov(Operation *operations, int *numOperations, StationNode* node)
{
  if (node->path != NULL)
  {
    this->mov(operations, numOperations, node->path);
    operations[*numOperations].ID = node->stationID;
    curr_time += node->distance_to_path;
    operations[*numOperations].time = curr_time;
    operations[*numOperations].operation = 'M';
    *numOperations += 1;
    currentStation = node->stationID;

    if (stationz[currentStation].parkedCars > 0)
    {
      while (stationz[currentStation].parkedCars > 0 && loadedCars < 50)
      {
        if (trainHead == NULL)
        {
          trainHead = stationz[currentStation].parkedCarHead;
          trainTail = trainHead;
          if (stationz[currentStation].parkedCarHead->next)
            stationz[currentStation].parkedCarHead->next->prev = NULL;
          stationz[currentStation].parkedCarHead = stationz[currentStation].parkedCarHead->next;
          trainHead->next = NULL;
          stationz[currentStation].parkedCars -= 1;
          loadedCars += 1;
          operations[*numOperations].ID = trainTail->ID;
          operations[*numOperations].time = curr_time;
          operations[*numOperations].operation = 'P';
          *numOperations += 1;
        }
        else
        {
          trainTail->next = stationz[currentStation].parkedCarHead;
          trainTail->next->prev = trainTail;
          if (stationz[currentStation].parkedCarHead->next != NULL)
          {
            stationz[currentStation].parkedCarHead->next->prev = NULL;
          }
          stationz[currentStation].parkedCarHead = stationz[currentStation].parkedCarHead->next;
          trainTail->next->next = NULL;
          trainTail = trainTail->next;
          stationz[currentStation].parkedCars -= 1;
          loadedCars += 1;
          operations[*numOperations].ID = trainTail->ID;
          operations[*numOperations].time = curr_time;
          operations[*numOperations].operation = 'P';
          *numOperations += 1;
        }
      }


    }
  }

}
