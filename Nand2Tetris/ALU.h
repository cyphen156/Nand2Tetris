#pragma once
class ALU
{
public:
    static bool Compute(
        const bool* x, 
        const bool* y,
        bool zx, 
        bool nx, 
        bool zy, 
        bool ny, 
        bool f, 
        bool no,
        bool* out, 
        bool& zr, 
        bool& ng,
        int bitSize = 16  // 기본 16비트
    );
};