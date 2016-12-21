/* Copyright 2016 Marc Volker Dickmann */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include "emulator.h"
#include "src/emulator_alu.h"

/////////////
//   CPU   //
/////////////
void emu_cpu_init (emu_cpu *a)
{
	// Init the sram!
	memset (a->sram, 0, EMU_CPU_SRAM_MAX * sizeof (byte));
	
	// Init the flash!
	memset (a->flash, 0, EMU_CPU_FLASH_MAX * sizeof (byte));
}

bool emu_cpu_cycle (emu_cpu *a)
{
	word reg_a;
	
	reg_a = EMU_CPU_INSREG (a->flash[a->sram[EMU_CPU_PC]]);
	
	switch (a->flash[a->sram[EMU_CPU_PC]] & EMU_CPU_MASK_INST)
	{
		case EMU_CPU_MKOPC ('L', 'D', 'I', 0):
			a->sram[reg_a] = a->flash[++a->sram[EMU_CPU_PC]];
			break;
		case EMU_CPU_MKOPC ('A', 'D', 'D', 0):
			alu_add (a->sram, reg_a, a->flash[++a->sram[EMU_CPU_PC]]);
			break;
		case EMU_CPU_MKOPC ('S', 'U', 'B', 0):
			alu_sub (a->sram, reg_a, a->flash[++a->sram[EMU_CPU_PC]]);
			break;
		case EMU_CPU_MKOPC ('M', 'P', 'L', 0):
			alu_mpl (a->sram, reg_a, a->flash[++a->sram[EMU_CPU_PC]]);
			break;
		case EMU_CPU_MKOPC ('D', 'I', 'V', 0):
			alu_div (a->sram, reg_a, a->flash[++a->sram[EMU_CPU_PC]]);
			break;
		case EMU_CPU_MKOPC ('A', 'N', 'D', 0):
			alu_and (a->sram, reg_a, a->flash[++a->sram[EMU_CPU_PC]]);
			break;
		case EMU_CPU_MKOPC ('O', 'U', 'T', 0):
			printf ("%i\n", a->sram[reg_a]);
			break;
		default:
			// Print the mnemonics!
			printf ("%c %c %c %c\n", (a->flash[a->sram[EMU_CPU_PC]] & 0xff000000) >> 24, (a->flash[a->sram[EMU_CPU_PC]] & 0xff0000) >> 16, (a->flash[a->sram[EMU_CPU_PC]] & 0xff00) >> 8, a->flash[a->sram[EMU_CPU_PC]] & 0xff);
		case 0:
			return false;
	}
	
	a->sram[EMU_CPU_PC]++;
	return true;
}

void emu_cpu_program_load_file (emu_cpu *a, const char *filename)
{
	word i;
	FILE *prg_file;
	
	prg_file = fopen (filename, "r");
	
	// Check if the file is opened!
	assert (prg_file != NULL);
	
	// Copy the program into the flash memory!
	i = 0;
	while (fread (&a->flash[i], sizeof (word), 1, prg_file) != 0)
	{
		i++;
	}
	
	fclose (prg_file);
}

//////////////
// COMPILER //
//////////////
void emu_compiler_write (FILE *f, const word i)
{
	fwrite (&i, sizeof (i), 1, f);
}

char *emu_compiler_parse_arg (word *arg, char *str, const char delim)
{
	*arg = 0;
	
	str = strchrnul (str, delim);
	if (str != NULL)
	{
		str++;
		*arg = (isdigit (*str) ? atoi (str) : *str + EMU_CPU_REG_EAX); 
	}
	return str;
}

word emu_compiler_parse_line (char *line, word *arg_b)
{
	word arg_a;
	char *ptr;
	
	ptr = emu_compiler_parse_arg (&arg_a, line, ' ');
	emu_compiler_parse_arg (arg_b, ptr, ' ');
	
	return EMU_CPU_MKOPC (line[0], line[1], line[2], (byte)arg_a);
}

void emu_compiler_file (const char *filename, const char *filename_src)
{
	char line[250];
	word arg;
	FILE *fprg, *fsrc;
	
	fsrc = fopen (filename_src, "r");
	assert (fsrc != NULL);
	
	fprg = fopen (filename, "w");
	if (fprg == NULL)
	{
		fclose (fsrc);
		return;
	}
	
	while (fgets (line, sizeof (line), fsrc) != NULL)
	{
		emu_compiler_write (fprg, emu_compiler_parse_line (line, &arg));
		
		if (arg != 0)
		{
			emu_compiler_write (fprg, arg);
		}
	}
	
	fclose (fsrc);
	fclose (fprg);
}

int main (int argc, char *argv[])
{
	emu_cpu mycpu;
	
	printf ("Emulator v. 0.0.1 A (C) 2016 Marc Volker Dickmann\n\n");
	
	if (argc == 2)
	{
		emu_cpu_init (&mycpu);
		emu_cpu_program_load_file (&mycpu, argv[1]);
		
		// Run the program!
		while (emu_cpu_cycle (&mycpu))
		{
		}
	}
	else if (argc == 3)
	{
		emu_compiler_file (argv[1], argv[2]);
	}
	else
	{
		printf ("USAGE: %s <program> [source]!\n", argv[0]);
	}
	
	return 0;
}
