/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#include <algorithm>
#include <cassert>
#include <list>
#include <set>
#include <limits>

#include "operation.h"
#include "node.h"
#include "memory_manager.h"

using std::for_each;
using std::list;
using std::set;

// Internal functions and data types.
namespace {
	template <class T>
	struct delete_ptr {
		typedef const T *argument_type;
		typedef void result_type;
		delete_ptr() {}
		result_type operator()(argument_type ptr) { delete ptr; }
	};
}

MemoryManager *MemoryManager::instance()
{
	if (theinstance == 0)
		theinstance = new MemoryManager;
	return theinstance;
}

Operation *MemoryManager::build_operation(OpCode code, long left, long right)
{
	Operation *op = 0;
	switch (code) {
	case Op_Sum:
		op = new Sum(left, right);
		break;
	case Op_Mul:
		op = new Mul(left, right);
		break;
	case Op_Sub:
		op = new Sub(left, right);
		break;
	case Op_Div:
		op = new Div(left, right);
		break;
	default:
		assert(0 == "Error: unexpected operation code.");
		break;
	}
	operations.push_back(op);
	return op;
}

Node *MemoryManager::build_node(const list<const Operation *> &prev_steps,
				long new_num, long target,
				const list<long> &basics,
				set<list<long> > &explored_nodes, Node *parent)
{
	Node *node = new Node(prev_steps, new_num, target,
			      basics, explored_nodes, parent);
	nodes.push_back(node);
	return node;
}

void MemoryManager::free()
{
	for_each(operations.begin(), operations.end(), delete_ptr<Operation>());
	for_each(nodes.begin(), nodes.end(), delete_ptr<Node>());
	operations.clear();
	nodes.clear();
}

MemoryManager::MemoryManager()
	: operations(), nodes()
{
}

MemoryManager *MemoryManager::theinstance = 0;
