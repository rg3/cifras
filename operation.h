/*
 * Author: Ricardo Garcia Gonzalez
 * License: Public domain code
 */
#ifndef __OPERATION_HEADER__
#define __OPERATION_HEADER__
#include <iostream>

// Operation class.
class Operation {
protected:
	long lf;
	long rg;

public:
	Operation(const long &a, const long &b) : lf(a), rg(b) {}
	virtual ~Operation() {}
	virtual const long &left() const { return lf; }
	virtual const long &right() const { return rg; }
	virtual char opchar() const = 0;
	virtual long result() const = 0;
	virtual bool valid() const { return true; }
};

// Operation-derived subclasses.
class Sum: public Operation {
public:
	Sum(long a, long b) : Operation(a, b) {}
	virtual char opchar() const { return '+'; }
	virtual long result() const { return lf + rg; }
	virtual bool valid() const {
		return((std::numeric_limits<long>::max() - lf) >= rg);
	}
};

class Mul: public Operation {
public:
	Mul(long a, long b) : Operation(a, b) {}
	virtual char opchar() const { return '*'; }
	virtual long result() const { return lf * rg; }
	virtual bool valid() const {
		return((std::numeric_limits<long>::max() / lf) + 1 >= rg);
	}
};

class Sub: public Operation {
public:
	Sub(long a, long b) : Operation(a, b) {}
	virtual char opchar() const { return '-'; }
	virtual long result() const { return lf - rg; }
	virtual bool valid() const { return lf > rg; }
};

class Div: public Operation {
public:
	Div(long a, long b) : Operation(a, b) {}
	virtual char opchar() const { return '/'; }
	virtual long result() const { return lf / rg; }
	virtual bool valid() const { return rg != 0 && lf % rg == 0; }
};

// Output a given operation.
std::ostream &operator<<(std::ostream &out, const Operation &op);

// Operation codes.
enum OpCode { Op_Sum, Op_Mul, Op_Sub, Op_Div };

#endif
