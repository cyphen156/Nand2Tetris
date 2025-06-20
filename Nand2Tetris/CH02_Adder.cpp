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
	// 주어진 수에 1을 더해주는 함수

	bool c = true;  // 첫 자리에는 1을 더해야 하므로 초기 carry-in = true

	for (int i = 0; i < bitSize; ++i)  // 가변 비트 수 대응: 최대 64비트까지 대응
	{
		bool isSum = false, nextCarry = false;
		FullAdder(a[i], false, c, isSum, nextCarry);  // b=false → a + 0 + carry
		sum[i] = isSum;
		c = nextCarry;
	}

	carry = c;
	return true;
}

/// <summary>
/// 주어진 두 수를 더하는 함수
/// 결과는 포인터에 의해 전달되며
/// 출력은 오버플로우 발생 여부를 반환
/// </summary>
/// <param name="a">inputA</param>
/// <param name="b">inputB</param>
/// <param name="sum">덧셈 결과를 저장할 배열 (bitSize 크기)</param>
/// <param name="carry">최종 캐리 아웃 비트 (bool 참조)</param>
/// <param name="bitSize">연산에 사용할 비트 수 (최대 64)</param>
/// <returns> isOverFlow == 오버플로우 발생 여부 </returns>
bool CH02_Adder::Adder(const bool* a, const bool* b, bool* sum, bool& carry, int bitSize)
{
	// 주어진 두 수를 더하는 함수
	// incrementer에 의해 최대 비트가지 대응 가능

	bool isOverFlow = false;  // 오버플로우 여부를 저장하는 변수	

	bool c = false;

	for (int i = 0; i < bitSize; ++i)  // 가변 비트 수 대응: 최대 64비트까지 대응
	{
		bool isSum = false, nextCarry = false;
		FullAdder(a[i], b[i], c, isSum, nextCarry);  // b=false → a + 0 + carry
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