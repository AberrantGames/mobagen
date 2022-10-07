#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <algorithm>

Point2D Cat::Move(World* world) {
  visited.clear();
  from.clear();
  std::vector<queueEntry> queue;
  bool pathExists = false;

  queue.push_back({world->getCat(), 0});
  Point2D outsideEntry = world->getCat();

  while (!queue.empty()) {
    std::sort(queue.begin(), queue.end());

    //for (int i = 0; i < queue.size(); i++) {
    //  std::cout << "Pos" << i << " " << queue[i].position.x << " " << queue[i].position.y << " " << queue[i].accumulatedWeight << std::endl;
    //}

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

  //Takes the point that was outside the map and goes through from list to find where to move
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

    for (int i = 0; i < path.size(); i++) {
      std::cout << "Pos" << i << " " << path[i].x << " " << path[i].y << std::endl;
    }

    return path[pathCount - 2];
  } 
  else {
      auto rand = Random::Range(0, 5);
    auto pos = world->getCat();
      switch (rand) {
        case 0:
          return World::NE(pos);
        case 1:
          return World::NW(pos);
        case 2:
          return World::E(pos);
        case 3:
          return World::W(pos);
        case 4:
          return World::SW(pos);
        case 5:
          return World::SE(pos);
        default:
          throw "random out of range";
      }
  }
}