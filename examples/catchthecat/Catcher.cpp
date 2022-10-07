#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  visited.clear();
  from.clear();
  std::vector<queueEntry> queue;
  bool pathExists = false;

  queue.push_back({world->getCat(), 0});
  Point2D outsideEntry = world->getCat();

  while (!queue.empty()) {
    std::sort(queue.begin(), queue.end());
    //remove the head
    auto head = queue[0];
    queue.erase(queue.begin());
    //mark the head as visited
    visited[head.position.x][head.position.y] = true; 
    //for each neighbor:
        //if it is not visited (nor the cat), add to queue with weight++ and mark where this element came from
    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::NE(head.position))) {
      outsideEntry = World::NE(head.position);
      from[World::NE(head.position).x][World::NE(head.position).y] = head.position;
      pathExists = true;
      break;
    } 
    else if (!visited[World::NE(head.position).x][World::NE(head.position).y] && !world->getContent(World::NE(head.position))) { //Checks the NE neighbor 
      //Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::NE(head.position), newWeight});
      from[World::NE(head.position).x][World::NE(head.position).y] = head.position;
    }

    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::NW(head.position))) {
      outsideEntry = World::NW(head.position);
      from[World::NW(head.position).x][World::NW(head.position).y] = head.position;
      pathExists = true;
      break;
    }
    else if (!visited[World::NW(head.position).x][World::NW(head.position).y] && !world->getContent(World::NW(head.position))) { //checks to NW neighbor
      // Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::NW(head.position), newWeight});
      from[World::NW(head.position).x][World::NW(head.position).y] = head.position;
    }

    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::W(head.position))) {
      outsideEntry = World::W(head.position);
      from[World::W(head.position).x][World::W(head.position).y] = head.position;
      pathExists = true;
      break;
    }
    else if (!visited[World::W(head.position).x][World::W(head.position).y] && !world->getContent(World::W(head.position))) { //Checks to W neighbor
      // Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::W(head.position), newWeight});
      from[World::W(head.position).x][World::W(head.position).y] = head.position;
    }

    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::SW(head.position))) {
      outsideEntry = World::SW(head.position);
      from[World::SW(head.position).x][World::SW(head.position).y] = head.position;
      pathExists = true;
      break;
    }
    else if (!visited[World::SW(head.position).x][World::SW(head.position).y] && !world->getContent(World::SW(head.position))) { //Checks to SW neigbor
      // Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::SW(head.position), newWeight});
      from[World::SW(head.position).x][World::SW(head.position).y] = head.position;
    }

    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::SE(head.position))) {
      outsideEntry = World::SE(head.position);
      from[World::SE(head.position).x][World::SE(head.position).y] = head.position;
      pathExists = true;
      break;
    }
    else if (!visited[World::SE(head.position).x][World::SE(head.position).y] && !world->getContent(World::SE(head.position))) { //Checks to SE neighbor
      // Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::SE(head.position), newWeight});
      from[World::SE(head.position).x][World::SE(head.position).y] = head.position;
    }

    // Checks to see if the position is outside the map AKA a win state
    if (!world->World::isValidPosition(World::E(head.position))) {
      outsideEntry = World::E(head.position);
      from[World::E(head.position).x][World::E(head.position).y] = head.position;
      pathExists = true;
      break;
    }
    else if (!visited[World::E(head.position).x][World::E(head.position).y] && !world->getContent(World::E(head.position))) { //Checks the E neighbor
      // Adds the neighbor to the queue and marks where it was from
      int newWeight = head.accumulatedWeight + 1;
      queue.push_back({World::E(head.position), newWeight});
      from[World::E(head.position).x][World::E(head.position).y] = head.position;
    }
  }

  // Takes the point that was outside the map and goes through from list to find
  // where to move
  std::vector<Point2D> path;
  int pathCount = 0;

  if (pathExists) {
    path.push_back(outsideEntry);
    pathCount++;

    while (outsideEntry != world->getCat()) {
      outsideEntry = from[outsideEntry.x][outsideEntry.y];
      path.push_back(outsideEntry);
      pathCount++;
    }

    return path[1];
  } 
  else {
    int rand;
    Point2D pos = world->getCat();
    Point2D newPos;
    bool canMove = false;

    do {
      rand = Random::Range(0, 5);

      switch (rand) {
        case 0:
          if (!world->getContent(World::NE(pos))) {
            newPos = World::NE(pos);
            canMove = true;
          }
          break;
        case 1:
          if (!world->getContent(World::NW(pos))) {
            newPos = World::NW(pos);
            canMove = true;
          }
          break;
        case 2:
          if (!world->getContent(World::E(pos))) {
            newPos = World::E(pos);
            canMove = true;
          }
          break;
        case 3:
          if (!world->getContent(World::W(pos))) {
            newPos = World::W(pos);
            canMove = true;
          }
          break;
        case 4:
          if (!world->getContent(World::SW(pos))) {
            newPos = World::SW(pos);
            canMove = true;
          }
          break;
        case 5:
          if (!world->getContent(World::SE(pos))) {
            newPos = World::SE(pos);
            canMove = true;
          }
          break;
        default:
          throw "random out of range";
      }
    } while (!canMove);

    return newPos;
  }
}
