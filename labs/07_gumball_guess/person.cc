#include "labs/07_gumball_guess/person.h"

#include <math.h>

namespace rose {

Queue<Person> Person::FindWinners(int num_candies, Queue<Person> players) {
  int min_delta = INT_MAX;
  Queue<Person> winners;
  while (players) {
    Person player = players.PeekFront().value();
    int delta = abs(player.guess() - num_candies);
    players.Dequeue();
    // When a new-lowest delta is found, all previous winners can be discarded.
    if (delta < min_delta) {
      min_delta = delta;
      winners.Clear();
    }
    if (delta <= min_delta) winners.Enqueue(player);
  }
  return winners;
}

}  // namespace rose
