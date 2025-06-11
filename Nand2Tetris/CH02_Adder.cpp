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

/// <summary>
/// �־��� �� ���� ���ϴ� �Լ�
/// ����� �����Ϳ� ���� ���޵Ǹ�
/// ����� �����÷ο� �߻� ���θ� ��ȯ
/// </summary>
/// <param name="a">inputA</param>
/// <param name="b">inputB</param>
/// <param name="sum">���� ����� ������ �迭 (bitSize ũ��)</param>
/// <param name="carry">���� ĳ�� �ƿ� ��Ʈ (bool ����)</param>
/// <param name="bitSize">���꿡 ����� ��Ʈ �� (�ִ� 64)</param>
/// <returns> isOverFlow == �����÷ο� �߻� ���� </returns>
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

	bool signA = a[bitSize - 1];    // MSB of a
	bool signB = b[bitSize - 1];    // MSB of b
	bool signSum = sum[bitSize - 1]; // MSB of result

	isOverFlow = (signA == signB) && (signSum != signA);

	return isOverFlow;
}