#include "MazeGenerator.h"
#include "World.h"
#include "Random.h"
#include <climits>

bool MazeGenerator::Step(World* world) {
	//if first step, choose a random point
		// Add to list
		// Set as visited
		// Change color to red
		// Mark the first step as having been completed
		// return true
	if (isFirstStep) {
		auto startPoint = randomPoint(world);
		cells.push_back(startPoint);
		visited[startPoint.x][startPoint.y] = true;
        world->SetNodeColor(startPoint, Color::Red.Dark());
		isFirstStep = false;
		return true;
	}
	else if (!cells.empty()) {
		auto randIndex = Random::Range(0, cells.size()-1);
		auto newPoint = cells[randIndex];

		std::vector<Point2D> neighbors = getNeighbors(world, newPoint);

		if (neighbors.empty()) {
			world->SetNodeColor(newPoint, Color::Black);
			cells.erase(cells.begin()+randIndex);

			return true;
		}
		else {
			auto r = Random::Range(0, neighbors.size()-1);
			auto randNeighbor = neighbors[r];

			cells.push_back(randNeighbor);
			visited[randNeighbor.x][randNeighbor.y] = true;
			world->SetNodeColor(randNeighbor, Color::Red.Dark());

			auto delta = randNeighbor - newPoint;
			if (delta.y == -1) {
				world->SetNorth(newPoint, false);
			} 
			else if (delta.x == 1) {
				world->SetEast(newPoint, false);
			}
			else if (delta.y == 1) {
				world->SetSouth(newPoint, false);
			}
			else if (delta.x == -1) {
				world->SetWest(newPoint, false);
			}

			return true;
		}
	}
	//if not first step, choose random point in list
		//Choose random viable neighbor
			//add neighbor to list
			//change neighbor color to red
			//carve a path from random point to random neighbor (destroy the wall between them)
			// return true
		//If no viable neighbors
			//change color to black
			// remove from list
			// return true

	//if list is empty and is not first step, return false

  return false;
}

void MazeGenerator::Clear(World* world) {
  cells.clear();
  visited.clear();
  isFirstStep = true;
}

Point2D MazeGenerator::randomPoint(World* world) {
  auto gridSize = world->GetSize() / 2;

  for (int y = -gridSize; y <= gridSize; y++) {
    for (int x = -gridSize; x <= gridSize; x++) {
      if (!visited[y][x]) {
        return {x, y};
      }
	}
  }

  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> MazeGenerator::getNeighbors(World* world, const Point2D& point) {
  auto gridSize = world->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // Checks for each direction if inside the board, if its been visited, if there is a wall
	//If any of these are not viable then it is not added to the list of viable neighbors
  // North Neighbor
  if ((abs(point.x) <= gridSize && abs(point.y - 1) <= gridSize) && !visited[point.x][point.y - 1] && world->GetNorth({ point.x, point.y - 1 })) {
    neighbors.emplace_back(point.x, point.y - 1);
  }
  // East Neighbor
  if ((abs(point.x + 1) <= gridSize && abs(point.y) <= gridSize) && !visited[point.x + 1][point.y] && world->GetNorth({ point.x + 1, point.y })) {
    neighbors.emplace_back(point.x + 1, point.y);
  }
  // South Neighbor
  if ((abs(point.x) <= gridSize && abs(point.y + 1) <= gridSize) && !visited[point.x][point.y + 1] && world->GetNorth({ point.x, point.y + 1 })) {
    neighbors.emplace_back(point.x, point.y + 1);
  }
  // West Neighbor
  if ((abs(point.x - 1) <= gridSize && abs(point.y) <= gridSize) && !visited[point.x - 1][point.y] && world->GetNorth({ point.x - 1, point.y })) {
    neighbors.emplace_back(point.x - 1, point.y);
  }

  return neighbors;
}