#include "CH01_boolean.h"

bool CH01_boolean::And(bool a, bool b)
{
	return Not(Nand(a, b));
}

bool CH01_boolean::Or(bool a, bool b)
{
	return Nand(Nand(a, a), Nand(b, b));
}

bool CH01_boolean::Not(bool a)
{
	return Nand(a, a);
}

bool CH01_boolean::Xor(bool a, bool b)
{
	bool nand_ab = Nand(a, b);
	bool left = Nand(a, nand_ab);
	bool right = Nand(b, nand_ab);
	return Nand(left, right);
}

bool CH01_boolean::Nor(bool a, bool b)
{
	return Not(Or(a, b));
}

bool CH01_boolean::Nand(bool a, bool b)
{
	return !(a & b);
}

// MUX: Multiplexer
// 선택 신호(sel)에 따라 입력 a 또는 b를 출력하는 함수
bool CH01_boolean::MUX(bool a, bool b, bool sel)
{
	bool notSel = Not(sel);
	bool aAnd = And(a, notSel);
	bool bAnd = And(b, sel);
	return Or(aAnd, bAnd);
}

// DEMUX: Demultiplexer
// 입력 in을 선택 신호(sel)에 따라 a 또는 b로 분배하는 함수
void CH01_boolean::Demux(bool in, bool sel, bool& a, bool& b)
{
	bool notSel = Not(sel);
	a = And(in, notSel);
	b = And(in, sel);    
}
