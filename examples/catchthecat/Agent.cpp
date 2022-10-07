#include "Agent.h"

bool queueEntry::operator<(const queueEntry& rhs) const {
  return this->accumulatedWeight < rhs.accumulatedWeight;
}