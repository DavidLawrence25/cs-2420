#include "labs/07_gumball_guess/queue.h"

#include <ostream>

namespace rose {

template <typename _T>
std::ostream &operator<<(std::ostream &out, const Queue<_T> &queue) {
  // Not using the default behavior of delimiting with ' '.
  for (_T x : queue.data_) out << x << '\n';
  return out;
}

}  // namespace rose
