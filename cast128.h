#pragma once
#include<cstdint>
#include<string>
static const int keyLength = 128;
static const int blockLength = 64;
static const int keysCount = 32;
static const int roundCount = 16;

static class Cast128 {
public:
	typedef uint32_t uint;
	typedef uint8_t  uint8;
	typedef uint Key[keyLength / sizeof(uint) / 8];
	struct Block {
		uint Msg[blockLength / sizeof(uint) / 8];
	};
	
private:
	static const Cast128::uint8 getByte(Cast128::Key key, Cast128::uint8 i);
	static Cast128::uint* Cast128::generateKeys(const Cast128::Key key);

private:
	typedef uint sBlock[256];
	static const sBlock S1;
	static const sBlock S2;
	static const sBlock S3;
	static const sBlock S4;
	static const sBlock S5;
	static const sBlock S6;
	static const sBlock S7;
	static const sBlock S8;

public:
	static Block encrypt(const Key key, const Block msg);
	static Block decrypt(const Key key, const Block msg);
	
	static uint sumMod2_32(uint a, uint b);
	static Block go(const Key key, const Block msg, bool isEncrypt);
	static uint subtractMod2_32(uint a, uint b);
	static uint cyclicShift(uint x, uint8 shift);
	static void splitI(uint I, uint8* Ia, uint8* Ib, uint8* Ic, uint8* Id);
	static void encryptFile(std::string inputFile, std::string outFile);
};


