/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#include <iostream>
#include <list>
#include <set>
#include <cstdlib>
#include <limits>

#include "operation.h"
#include "node.h"
#include "memory_manager.h"

using std::list;
using std::set;
using std::labs;
using std::ostream;
using std::endl;

// Internal functions and data.
namespace {
	// Insert element in reverse-ordered list.
	template <class T>
	void insert_ordered(list<T> &thelist, const T &elem)
	{
		typedef typename list<T>::iterator iter;
		for (iter ii = thelist.begin(); ii != thelist.end(); ++ii)
			if (*ii <= elem) {
				thelist.insert(ii, elem);
				return;
			}
		thelist.push_back(elem);
	}

	// Create new list from list, excluding two elements.
	template <class T>
	void append_from_except(const list<T> &ls,
				const typename list<T>::const_iterator &ii,
				const typename list<T>::const_iterator &jj,
				list<T> &newls)
	{
		typedef typename list<T>::const_iterator iter;
		for (iter kk = ls.begin(); kk != ls.end(); ++kk)
			if (kk != ii && kk != jj)
				newls.push_back(*kk);
	}
}

// Node constructor. Builds full solution graph.
Node::Node(const list<const Operation *> &prev_steps, long new_num, long target,
	   const list<long> &basics, set<list<long> > &explored, Node *parent)
	: thesteps(prev_steps), successors(), thevalue(new_num), best_child(0)
{
	// Target found or leaf: try to self-proclaim best.
	if (parent != 0 && (new_num == target || basics.size() == 1)) {
		parent->best_child = ((parent->best_child == 0)?
			    this : best_node(parent->best_child, this, target));
		return;
	}

	// Target not found and not leaf: generate children.
	long lf;
	long rg;
	long result;
	list<long> rest;
	list<long> new_nums;
	list<const Operation *> new_steps;
	MemoryManager *mm = MemoryManager::instance();
	Operation *step;
	Node *child;

	typedef list<long>::const_iterator iter;
	for (iter ii = basics.begin(); ii != basics.end(); ++ii)
		for (iter jj = ii; ++jj != basics.end(); ) { // Weird "for"
			// Choose a pair.
			lf = *ii;
			rg = *jj;
			rest.clear();
			append_from_except(basics, ii, jj, rest);

			for (int op = Op_Sum; op <= Op_Div; ++op) {
				// Operate them if possible.
				step = mm->build_operation(OpCode(op), lf, rg);
				if (! step->valid())
					continue;

				// Create new number list for child.
				result = step->result();
				new_nums = rest;
				insert_ordered(new_nums, result);

				// Avoid list re-exploration.
				if (explored.find(new_nums) != explored.end())
					continue;
				explored.insert(new_nums);

				// Build new child.
				new_steps = prev_steps;
				new_steps.push_back(step);
				child = mm->build_node(new_steps, result,
					    target, new_nums, explored, this);
				successors.push_back(child);
			}
		}

	// After generating children, try to set parent best to our best.
	if (parent != 0 && best_child != 0)
		parent->best_child = ((parent->best_child == 0)? best_child :
			     best_node(parent->best_child, best_child, target));
}

// Best of two nodes.
Node *best_node(Node *first, Node *second, const long &target)
{
	long fdiff = labs(first->value() - target);
	long sdiff = labs(second->value() - target);

	if (fdiff < sdiff || (first->value() == second->value() &&
			      first->steps().size() < second->steps().size()))
		return first;
	return second;
}

// Print node to output stream.
ostream &operator<<(ostream &out, const Node &node)
{
	typedef list<const Operation *>::const_iterator iter;
	const list<const Operation *>&steps = node.steps();
	for (iter ii = steps.begin(); ii != steps.end(); ++ii)
		out << *(*ii) << endl;
	return out;
}
