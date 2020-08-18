#include "Random.h"
#include <cstdlib>

namespace Random
{

	int integer(int low, int high) {
		return rand() % (high - low + 1) + low;
	}

}
