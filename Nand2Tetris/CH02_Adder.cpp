#include "CH02_Adder.h"
#include "CH01_boolean.h"

bool CH02_Adder::HalfAdder(bool a, bool b, bool& sum, bool& carry)
{
	// a ^ b
	sum = CH01_boolean::Xor(a, b);		
	
	// a & b
	carry = CH01_boolean::And(a, b);	
	return true;
}

bool CH02_Adder::FullAdder(bool a, bool b, bool c, bool& sum, bool& carry)
{
	// HalfAdder(c, HalfAdder(b, c, sum, carry), sum, carry)
	// a ^ (b ^ c)
	sum = CH01_boolean::Xor(a, CH01_boolean::Xor(b, c));	

	// (a & b) | (c & (a ^ b))
	carry = CH01_boolean::Or(
		CH01_boolean::And(a, b), 
		CH01_boolean::And(c, CH01_boolean::Xor(a, b)));		
	return true;
}

bool CH02_Adder::Incrementer(const bool* a, bool* sum, bool& carry, int bitSize)
{
	// �־��� ���� 1�� �����ִ� �Լ�

	bool c = true;  // ù �ڸ����� 1�� ���ؾ� �ϹǷ� �ʱ� carry-in = true

	for (int i = 0; i < bitSize; ++i)  // ���� ��Ʈ �� ����: �ִ� 64��Ʈ���� ����
	{
		bool isSum = false, nextCarry = false;
		FullAdder(a[i], false, c, isSum, nextCarry);  // b=false �� a + 0 + carry
		sum[i] = isSum;
		c = nextCarry;
	}

	carry = c;
	return true;
}

bool CH02_Adder::Adder(const bool* a, const bool* b, bool* sum, bool& carry, int bitSize)
{
	// �־��� �� ���� ���ϴ� �Լ�
	// incrementer�� ���� �ִ� ��Ʈ���� ���� ����

	bool isOverFlow = false;  // �����÷ο� ���θ� �����ϴ� ����	

	bool c = false;

	for (int i = 0; i < bitSize; ++i)  // ���� ��Ʈ �� ����: �ִ� 64��Ʈ���� ����
	{
		bool isSum = false, nextCarry = false;
		FullAdder(a[i], b[i], c, isSum, nextCarry);  // b=false �� a + 0 + carry
		sum[i] = isSum;
		c = nextCarry;
	}

	carry = c;

	if (isOverFlow)
	{
		return false;
	}
	return true;
}
