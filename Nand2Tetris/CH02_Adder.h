#pragma once
class CH02_Adder
{
public:
	static bool HalfAdder(bool a, bool b, bool& sum, bool& carry);
	static bool FullAdder(bool a, bool b, bool c, bool& sum, bool& carry);
	static bool Incrementer(const bool* a, bool* sum, bool& carry, int bitSize);
	static bool Adder(const bool* a, const bool* b, bool* sum, bool& carry, int bitSize);
};

