//
// Created by Justin Weich on 5/29/16
//

#include "StationNode.h"
#include <iostream>

using namespace std;


StationNode::StationNode()
{
  path = NULL;
  known = false;
  distance = 1000000000;
}

StationMap::StationMap()
{
  mapped = false;
  nodes = NULL;
  stationID = -1;
  stations = NULL;
  parkedCars = 0;
  futureCars = 0;

  futureCarHead = NULL;
  futureCarTail = NULL;
  parkedCarHead = NULL;
  parkedCarTail = NULL;
}


StationMap::StationMap(int ID, Station* stns) : stationID(ID), stations(stns)
{

  mapped = false;
  nodes = NULL;
}


void StationMap::map(int numStations)
{

  unknown_heap = new BinaryHeap<StationNode*>(numStations);

  nodes = new StationNode[numStations];
  StationNode* node;
  //this is so that I can control the vertex
  for (int i = 0; i < stationID; i++)
  {
    nodes[i].stationID = i;
    unknown_heap->insert(&nodes[i]);
  }
  for (int i = stationID + 1; i < numStations; i++)
  {
    nodes[i].stationID = i;
    unknown_heap->insert(&nodes[i]);
  }

  nodes[this->stationID].stationID = this->stationID;

  node = &nodes[this->stationID];
  node->distance = 0;
  unknown_heap->insert(node);
  while(!unknown_heap->isEmpty())
  {
    changed = false;
    node = unknown_heap->findMin();
    unknown_heap->deleteMin();

    node->known = true;

    for (int i = 0; i < stations[node->stationID].adjCount; i++)
    {

      if (!nodes[stations[node->stationID].adjacent[i]].known)
      {
        int cvw = stations[node->stationID].distances[i];

        if (node->distance + cvw < nodes[stations[node->stationID].adjacent[i]].distance)
        {
          if (nodes[stations[node->stationID].adjacent[i]].distance < 2147483647)
            changed = true;
          nodes[stations[node->stationID].adjacent[i]].distance = node->distance + cvw;
          nodes[stations[node->stationID].adjacent[i]].distance_to_path = cvw;
          nodes[stations[node->stationID].adjacent[i]].path = node;
        }
      }
    }

    if (changed)
      unknown_heap->buildHeap();

  }


  this->mapped = true;
  //home = new StationNode(stationID);
}
