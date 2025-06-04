#pragma once
class CH01_boolean
{
public:
	static bool And(bool a, bool b);
	static bool Or(bool a, bool b);	
	static bool Not(bool a);

	static bool Xor(bool a, bool b);
	static bool Nor(bool a, bool b);
	static bool Nand(bool a, bool b);

	static bool MUX(bool a, bool b, bool sel);
	static void Demux(bool in, bool sel, bool& a, bool& b);
};

