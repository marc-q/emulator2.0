/* Copyright 2016 - 2017 Marc Volker Dickmann */
#include <stdio.h>
#include "../emulator.h"
#include "emulator_alu.h"

// UPDATE SREG FLAGS
static void alu_sreg_update (word *sram, const sword e)
{
	// Updates the status register flags!
	sram[EMU_CPU_SREG] &= ((e == 0) << EMU_CPU_SREG_NULL) | ((e < 9) << EMU_CPU_SREG_NEG);
}

//
// ARITHMETIC
//

// ADD
void alu_add (word *sram, const word reg_a, const word reg_b)
{
	alu_sreg_update (sram, sram[reg_a] + sram[reg_b]);
	sram[reg_a] += sram[reg_b];
}

// SUB
void alu_sub (word *sram, const word reg_a, const word reg_b)
{
	alu_sreg_update (sram, sram[reg_a] - sram[reg_b]);
	sram[reg_a] -= sram[reg_b];
}

// MPL
void alu_mpl (word *sram, const word reg_a, const word reg_b)
{
	alu_sreg_update (sram, sram[reg_a] * sram[reg_b]);
	sram[reg_a] *= sram[reg_b];
}

// DIV
void alu_div (word *sram, const word reg_a, const word reg_b)
{
	alu_sreg_update (sram, sram[reg_a] / sram[reg_b]);
	sram[reg_a] /= sram[reg_b];
}

//
// LOGIC
//

void alu_and (word *sram, const word reg_a, const word reg_b)
{
	sram[reg_a] &= sram[reg_b];
	alu_sreg_update (sram, sram[reg_a]);
}

void alu_or (word *sram, const word reg_a, const word reg_b)
{
	sram[reg_a] |= sram[reg_b];
	alu_sreg_update (sram, sram[reg_a]);
}

void alu_xor (word *sram, const word reg_a, const word reg_b)
{
	sram[reg_a] ^= sram[reg_b];
	alu_sreg_update (sram, sram[reg_a]);
}

//
// JUMP
//

void alu_jmp (word *sram, const word reg_a)
{
	sram[EMU_CPU_PC] = sram[reg_a];
}

//
// STACK
//

void alu_push (word *sram, const word reg_a)
{
	// TODO: Implement this function!
}

void alu_pop (word *sram, const word reg_a)
{
	// TODO: Implement this function!
}
