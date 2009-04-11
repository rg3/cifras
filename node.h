/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#ifndef __NODE_HEADER__
#define __NODE_HEADER__

// Node class. Builds full solution graph in constructor.
class Node {
private:
	std::list<const Operation *> thesteps;
	std::list<Node *> successors;
	long thevalue;
	Node *best_child;

public:
	Node(const std::list<const Operation *> &prev_steps, long new_num,
	     long target, const std::list<long> &usable_nums,
	     std::set<std::list<long> > &explored_nodes, Node *parent);

	long value() const { return thevalue; }
	const std::list<const Operation *> &steps() const { return thesteps; }
	const Node &best() const { return *best_child; }
};

// Best of two nodes.
Node *best_node(Node *first, Node *second, const long &target);

// Print node to output stream.
std::ostream &operator<<(std::ostream &out, const Node &node);

#endif
