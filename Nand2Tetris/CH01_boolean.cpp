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
// ���� ��ȣ(sel)�� ���� �Է� a �Ǵ� b�� ����ϴ� �Լ�
bool CH01_boolean::MUX(bool a, bool b, bool sel)
{
	bool notSel = Not(sel);
	bool aAnd = And(a, notSel);
	bool bAnd = And(b, sel);
	return Or(aAnd, bAnd);
}

// DEMUX: Demultiplexer
// �Է� in�� ���� ��ȣ(sel)�� ���� a �Ǵ� b�� �й��ϴ� �Լ�
void CH01_boolean::Demux(bool in, bool sel, bool& a, bool& b)
{
	bool notSel = Not(sel);
	a = And(in, notSel);
	b = And(in, sel);    
}
