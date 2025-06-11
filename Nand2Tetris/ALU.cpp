#include "ALU.h"
#include "CH01_boolean.h"
#include "CH02_Adder.h"

bool ALU::Compute(
	// 피연산자 섹터
	const bool* x, 	const bool* y, 

	// 제어 신호 섹터
	bool zx, bool nx,	// X 피연산자 제로화, Not연산
	bool zy, bool ny,	// Y 피연산자 제로화, Not연산
	bool f,				// true면 ADD(x+y), false면 AND(x&y)
	bool no,			// 출력 Not연산

	// 출력 섹터
	bool* out, // 연산 결과

	// 플래그 섹터
	bool& zr,	// 제로 플래그
	bool& ng,	// MSB 확인용
	
	// 연산되는 비트 크기
	int bitSize	// (기본값: 16, 최대: 64, 최소: 1, 0은 에러)
)
{

	// 0. 예외 처리 및 변수 선언
	if (bitSize < 1 || bitSize > 64)  // 에러: 비트 크기 범위 초과
	{
		return false;
	}

	bool _x[64] = { false }; // X 피연산자 (최대 64비트)
	bool _y[64] = { false }; // Y 피연산자 (최대 64비트)
	bool _out[64] = { false }; // 연산 결과 (최대 64비트)

	// 1. 입력값을 zx, nx, zy, ny에 따라 전처리
	for (int i = 0; i < bitSize; ++i)
	{
		_x[i] = x[i]; // X 피연산자 복사
		_y[i] = y[i]; // Y 피연산자 복사
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

	// 2. f에 따라 ADD 또는 AND 수행
	bool carry = false;

	if (f)
	{
		// ADD 연산 (X + Y)
		CH02_Adder::Adder(_x, _y, _out, carry, bitSize);
	}
	else
	{
		// AND 연산 (X & Y)
		for (int i = 0; i < bitSize; ++i)
		{
			_out[i] = CH01_boolean::And(_x[i], _y[i]);
		}
	}
	
	// 3. no에 따라 결과를 반전
	if (no)
	{
		for (int i = 0; i < bitSize; ++i)
		{
			_out[i] = CH01_boolean::Not(_out[i]);
		}
	}
	
	// 4. 결과를 out[]에 저장
	for (int i = 0; i < bitSize; ++i)
	{
		out[i] = _out[i];
	}
	
	// 5. zr, ng 플래그 계산 및 반환
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
