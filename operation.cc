/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#include <iostream>
#include <limits>

#include "operation.h"

using std::ostream;

// Output a given operation.
ostream &operator<<(ostream &out, const Operation &op)
{
	return out << op.left() << ' ' << op.opchar() << ' ' << op.right()
		   << " = " << op.result();
}
