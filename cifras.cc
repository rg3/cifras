/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <limits>

#include "operation.h"
#include "node.h"
#include "memory_manager.h"

using std::list;
using std::vector;
using std::set;
using std::cout;
using std::cerr;
using std::endl;
using std::clock;
using std::strtol;
using std::strlen;
using std::find;
using std::sort;
using std::greater;

int main(int argc, char *argv[])
{
	vector<long> basics_v;
	char *endptr;
	long number;
	
	// Check number of arguments.
	if (argc < 4) {
		cerr << "Usage: " << argv[0] << " num num... target" << endl;
		return -1;
	}

	// Get number list, checking argument format.
	for (int ii = 1; ii < argc; ++ii) {
		number = strtol(argv[ii], &endptr, 0);

		if (endptr != argv[ii] + strlen(argv[ii])) {
			cerr << "Error: \"" << argv[ii] << "\" not a number."
									<< endl;
			return -2;
		}
		
		if (number <= 0) {
			cerr << "Error: numbers below or equal to zero are not "
							     "allowed." << endl;
			return -3;
		}

		basics_v.push_back(number);
	}

	// Separate target.
	long target = basics_v.back();
	basics_v.pop_back();

	// Check target not in numbers.
	if (find(basics_v.begin(), basics_v.end(), target) != basics_v.end()) {
		cerr << "Error: target present in numbers to operate." << endl;
		return -4;
	}

	// Sort initial numbers and change to list.
	sort(basics_v.begin(), basics_v.end(), greater<long>());
	list<long> basics(basics_v.begin(), basics_v.end());

	// Execution.
	MemoryManager *mm = MemoryManager::instance();
	set<list<long> > explored_nodes;
	clock_t before = clock();
	Node *root = mm->build_node(list<const Operation *>(), 0L, target,
				    basics, explored_nodes, 0);
	clock_t after = clock();
	
	// Print results.
	cout << root->best();
	double clocks = static_cast<double>(after - before);
	double cps = static_cast<double>(CLOCKS_PER_SEC);
	cout << "Elapsed time: " << (clocks / cps) << " seconds" << endl;
	cout << "Explored nodes: " << explored_nodes.size() << endl;

	// Free memory.
	mm->free();
		
	return 0;
}
