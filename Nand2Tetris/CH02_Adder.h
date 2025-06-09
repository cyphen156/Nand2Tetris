#pragma once
class CH02_Adder
{
public:
	static bool HalfAdder(bool a, bool b, bool& sum, bool& carry);
	static bool FullAdder(bool a, bool b, bool c, bool& sum, bool& carry);
	static bool Incrementer(const bool* a, bool* sum, bool& carry);
	static bool Adder4Bit(const bool* a, const bool* b, bool* sum, bool& carry);
	static bool Adder8Bit(const bool* a, const bool* b, bool* sum, bool& carry);
	static bool Adder16Bit(const bool* a, const bool* b, bool* sum, bool& carry);
	static bool Adder32Bit(const bool* a, const bool* b, bool* sum, bool& carry);
	static bool Adder64Bit(const bool* a, const bool* b, bool* sum, bool& carry);
};

