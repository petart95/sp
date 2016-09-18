#ifndef MEMORY_H_
#define MEMORY_H_

#include <vector>

#define GETMASK(index, size) (((1L << (size)) - 1L) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITETO(data, index, size, value) ((data) = ((data) & (~GETMASK((index), (size)))) | ((value) << (index)))

unsigned long long readFromMem(unsigned long long memIndex, int bitOffset, unsigned long long size);
void writeToMem(unsigned long long memIndex, int bitOffset, unsigned long long size, unsigned long long value);

unsigned long long readFromMem(unsigned long long memIndex, unsigned long long size);
void writeToMem(unsigned long long memIndex, unsigned long long size, unsigned long long value);

typedef char 	  byte;  // 1B - 8b
typedef short	  hword;  // 2B - 16b
typedef long 	  word; // 4B - 32b
typedef long long dword; // 8B - 64b

typedef unsigned char 	   ubyte;  // 1B - 8b
typedef unsigned short	   uhword;  // 2B - 16b
typedef unsigned long 	   uword; // 4B - 32b
typedef unsigned long long udword;  // 8B - 64b

#define MEMORY_SIZE 0x10000

// memorija emulirane masine
extern ubyte *MEM;

extern std::vector<char> inputBuffer;

typedef word reg;
typedef uword ureg;

// lokacije flagov-a u psw-u
#define FLAG_Z_MASK 0x0001
#define FLAG_O_MASK 0x0002
#define FLAG_C_MASK 0x0004
#define FLAG_N_MASK 0x0008

#define FLAG_Z_POS 0
#define FLAG_O_POS 1
#define FLAG_C_POS 2
#define FLAG_N_POS 3

#define REGS_COUNT 16

struct CPU {
	reg regs[REGS_COUNT + 4];

	CPU() {
		regs[16] = 0;
		regs[18] = 0xffff;
	}
} extern cpu;

#define TEST_FLAG(mask) ((PSW & (mask)) != 0)
#define SET_FLAG(mask) PSW |= (mask)
#define CLEAR_FLAG(mask) PSW &= ~(mask)
// sets or clears flag u zavisnosto od val ( val je 0 ili 1)
#define SET_OR_CLEAR_FLAG(mask, val)\
	if(val)\
		SET_FLAG(mask);\
	else\
		CLEAR_FLAG(mask);

#define TEST_FLAG_Z() TEST_FLAG(FLAG_Z_MASK)
#define TEST_FLAG_O() TEST_FLAG(FLAG_O_MASK)
#define TEST_FLAG_C() TEST_FLAG(FLAG_C_MASK)
#define TEST_FLAG_N() TEST_FLAG(FLAG_N_MASK)

#define SET_FLAG_Z() SET_FLAG(FLAG_Z_MASK)
#define SET_FLAG_O() SET_FLAG(FLAG_O_MASK)
#define SET_FLAG_C() SET_FLAG(FLAG_C_MASK)
#define SET_FLAxG_N() SET_FLAG(FLAG_N_MASK)

#define CLEAR_FLAG_Z() CLEAR_FLAG(FLAG_Z_MASK)
#define CLEAR_FLAG_O() CLEAR_FLAG(FLAG_O_MASK)
#define CLEAR_FLAG_C() CLEAR_FLAG(FLAG_C_MASK)
#define CLEAR_FLAG_N() CLEAR_FLAG(FLAG_N_MASK)

#define SET_OR_CLEAR_FLAG_Z(val) SET_OR_CLEAR_FLAG(FLAG_Z_MASK, val)
#define SET_OR_CLEAR_FLAG_O(val) SET_OR_CLEAR_FLAG(FLAG_O_MASK, val)
#define SET_OR_CLEAR_FLAG_C(val) SET_OR_CLEAR_FLAG(FLAG_C_MASK, val)
#define SET_OR_CLEAR_FLAG_N(val) SET_OR_CLEAR_FLAG(FLAG_N_MASK, val)

#define PC_POS 16
#define LR_POS 17
#define SP_POS 18
#define PSW_POS 19

#define REG cpu.regs
#define PC REG[PC_POS]
#define LR REG[LR_POS]
#define SP REG[SP_POS]
#define PSW REG[PSW_POS]

inline ubyte read_ubyte(uword location) {
	return MEM[location];
}

inline word read_word(uword location) {
	return *(word*)(MEM + location);
}

inline ubyte read_next_ubyte() {
	return read_ubyte(PC++);
}

inline word read_next_word() {
	word ret = read_word(PC);
	PC += 4;
	return ret;
}

inline void write_word(uword location, word data) {
	*(word*)(MEM + location) = data;
}

inline void push(word data) {
	SP -= 4;
	write_word(SP, data);
}

inline word pop() {
	word ret = read_word(SP);
	SP += 4;
	return ret;
}

#endif
