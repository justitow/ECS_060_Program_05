//
// Created by Justin Weich on 5/31/16.
//

#include "CarNode.h"


CarNode::CarNode(int ori, int dest, int ident) : origin(ori), destination(dest), ID(ident)
{
  next = NULL;
  prev = NULL;

  distance = 0;
}

