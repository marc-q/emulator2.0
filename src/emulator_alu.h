#ifndef __EMULATOR_EMULATOR_H__
#define __EMULATOR_EMULATOR_H__

//
// ARITHMETIC
//

// ADD
void alu_add (word*, const word, const word);

// SUB
void alu_sub (word*, const word, const word);

// MPL
void alu_mpl (word*, const word, const word);

// DIV
void alu_div (word*, const word, const word);

//
// LOGIC
//

void alu_and (word*, const word, const word);
void alu_or (word*, const word, const word);
void alu_xor (word*, const word, const word);

//
// JUMP
//

void alu_jmp (word*, const word);

#endif /* __EMULATOR_EMULATOR_H__ */
