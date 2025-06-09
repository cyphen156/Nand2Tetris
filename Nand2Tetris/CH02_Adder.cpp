#include "CH02_Adder.h"
#include "CH01_boolean.h"

bool CH02_Adder::HalfAdder(bool a, bool b, bool& sum, bool& carry)
{
	sum = CH01_boolean::Xor(a, b);		// a ^ b;
	carry = CH01_boolean::And(a, b);	// a & b;
	return true;
}

bool CH02_Adder::FullAdder(bool a, bool b, bool c, bool& sum, bool& carry)
{
	sum = CH01_boolean::Xor(a, CH01_boolean::Xor(b, c));	// a ^ (b ^ c);
	
	carry = CH01_boolean::Or(
		CH01_boolean::And(a, b), 
		CH01_boolean::And(c, CH01_boolean::Xor(a, b)));		// (a & b) | (c & (a ^ b));
	
	return true;
}

bool CH02_Adder::Incrementer(const bool* a, bool* sum, bool& carry)
{
	return false;
}

bool CH02_Adder::Adder4Bit(const bool* a, const bool* b, bool* sum, bool& carry)
{
	return false;
}

bool CH02_Adder::Adder8Bit(const bool* a, const bool* b, bool* sum, bool& carry)
{
	return false;
}

bool CH02_Adder::Adder16Bit(const bool* a, const bool* b, bool* sum, bool& carry)
{
	return false;
}

bool CH02_Adder::Adder32Bit(const bool* a, const bool* b, bool* sum, bool& carry)
{
	return false;
}

bool CH02_Adder::Adder64Bit(const bool* a, const bool* b, bool* sum, bool& carry)
{
	return false;
}
