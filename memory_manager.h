/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#ifndef __MEMORY_MANAGER_HEADER__
#define __MEMORY_MANAGER_HEADER__

class MemoryManager {
public:
	static MemoryManager *instance();
	Operation *build_operation(OpCode code, long left, long right);
	Node *build_node(const std::list<const Operation *> &prev_steps,
			 long new_num, long target,
			 const std::list<long> &basics,
			 std::set<std::list<long> > &explored_nodes,
			 Node *parent);
	void free();
	
private:
	MemoryManager();
	std::list<const Operation *> operations;
	std::list<const Node *> nodes;
	static MemoryManager *theinstance;
};

#endif
