#ifndef __EMULATOR_H__
#define __EMULATOR_H__

// LIMITS
#define EMU_CPU_SRAM_MAX 512
#define EMU_CPU_FLASH_MAX 512

// ADDRESSES
#define EMU_CPU_PC 0
#define EMU_CPU_SREG 1

// TYPES
typedef unsigned int word;
typedef signed int sword;
typedef unsigned char byte;
typedef signed char sbyte;

// CONCATENATE
#define EMU_CPU_MKOPC(a, b, c, d) ((word)(((a) << 24) | ((b) << 16) | ((c) << 8) | (d)))

// BITMASK
#define EMU_CPU_MASK_INST 0xffffff00
#define EMU_CPU_MASK_REG 0xff

// MACROS
#define EMU_CPU_INSREG(a) ((a) & EMU_CPU_MASK_REG)

// CPU: Status register
enum emu_cpu_sreg
{
	EMU_CPU_SREG_NULL = 0,
	EMU_CPU_SREG_NEG
};

// CPU: Registers
enum emu_cpu_reg
{
	EMU_CPU_REG_EAX = 0xf,
	EMU_CPU_REG_ECX,
	EMU_CPU_REG_EDX,
	EMU_CPU_REG_EBX,
	EMU_CPU_REG_ESP,
	EMU_CPU_REG_EBP,
	EMU_CPU_REG_ESI,
	EMU_CPU_REG_EDI
};

// CPU
struct _emu_cpu
{
	word sram[EMU_CPU_SRAM_MAX];
	word flash[EMU_CPU_FLASH_MAX];
};

typedef struct _emu_cpu emu_cpu;

#endif /* __EMULATOR_H__ */

