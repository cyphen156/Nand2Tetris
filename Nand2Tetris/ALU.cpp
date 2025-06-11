#include "ALU.h"
#include "CH01_boolean.h"
#include "CH02_Adder.h"

bool ALU::Compute(
	// �ǿ����� ����
	const bool* x, 	const bool* y, 

	// ���� ��ȣ ����
	bool zx, bool nx,	// X �ǿ����� ����ȭ, Not����
	bool zy, bool ny,	// Y �ǿ����� ����ȭ, Not����
	bool f,				// true�� ADD(x+y), false�� AND(x&y)
	bool no,			// ��� Not����

	// ��� ����
	bool* out, // ���� ���

	// �÷��� ����
	bool& zr,	// ���� �÷���
	bool& ng,	// MSB Ȯ�ο�
	
	// ����Ǵ� ��Ʈ ũ��
	int bitSize	// (�⺻��: 16, �ִ�: 64, �ּ�: 1, 0�� ����)
)
{

	// 0. ���� ó�� �� ���� ����
	if (bitSize < 1 || bitSize > 64)  // ����: ��Ʈ ũ�� ���� �ʰ�
	{
		return false;
	}

	bool _x[64] = { false }; // X �ǿ����� (�ִ� 64��Ʈ)
	bool _y[64] = { false }; // Y �ǿ����� (�ִ� 64��Ʈ)
	bool _out[64] = { false }; // ���� ��� (�ִ� 64��Ʈ)

	// 1. �Է°��� zx, nx, zy, ny�� ���� ��ó��
	for (int i = 0; i < bitSize; ++i)
	{
		_x[i] = x[i]; // X �ǿ����� ����
		_y[i] = y[i]; // Y �ǿ����� ����
	}

	for (int i = 0; i < bitSize; ++i)
	{
		if (zx)
		{
			_x[i] = false;
		}

		if (nx)
		{
			_x[i] = CH01_boolean::Not(_x[i]);
		}

		if (zy)
		{
			_y[i] = false;
		}

		if (ny)
		{
			_y[i] = CH01_boolean::Not(_y[i]);
		}
	}

	// 2. f�� ���� ADD �Ǵ� AND ����
	bool carry = false;

	if (f)
	{
		// ADD ���� (X + Y)
		CH02_Adder::Adder(_x, _y, _out, carry, bitSize);
	}
	else
	{
		// AND ���� (X & Y)
		for (int i = 0; i < bitSize; ++i)
		{
			_out[i] = CH01_boolean::And(_x[i], _y[i]);
		}
	}
	
	// 3. no�� ���� ����� ����
	if (no)
	{
		for (int i = 0; i < bitSize; ++i)
		{
			_out[i] = CH01_boolean::Not(_out[i]);
		}
	}
	
	// 4. ����� out[]�� ����
	for (int i = 0; i < bitSize; ++i)
	{
		out[i] = _out[i];
	}
	
	// 5. zr, ng �÷��� ��� �� ��ȯ
	zr = true;
	for (int i = 0; i < bitSize; ++i)
	{
		if (out[i])
		{
			zr = false;
			break;
		}
	}

	ng = out[bitSize - 1];
	
	return true;
}
