/*
* decoder.c
* Used to decode pdp-11 instructions
* @ainoss
*/

#include <stdlib.h>
#include <string.h>
#include "decoder.h"
#include "instructions.h"
#include "disassembler.h"


struct instr_code instr_table_doubleop[] = {
	{ "", NULL, NULL, &find_singleop },   // 00
	{ "MOV", &exec_mov, &disasm_doubleop, &decode_doubleop }, // 01
	{ "CMP", &exec_cmp, &disasm_doubleop, &decode_doubleop }, // 02
	{ "BIT", &exec_bit, &disasm_doubleop, &decode_doubleop }, // 03
	{ "BIC", &exec_bic, &disasm_doubleop, &decode_doubleop }, // 04
	{ "BIS", &exec_bis, &disasm_doubleop, &decode_doubleop }, // 05
	{ "ADD", &exec_add, &disasm_doubleop, &decode_doubleop }, // 06
	{ "", NULL, NULL, &find_regop },      // 07
	{ "", NULL, NULL, &find_singleop },   // 10
	{ "MOVB", &exec_mov, &disasm_doubleop, &decode_doubleop }, // 11
	{ "CMPB", &exec_cmp, &disasm_doubleop, &decode_doubleop }, // 12
	{ "BITB", &exec_bit, &disasm_doubleop, &decode_doubleop }, // 13
	{ "BICB", &exec_bic, &disasm_doubleop, &decode_doubleop }, // 14
	{ "BISB", &exec_bis, &disasm_doubleop, &decode_doubleop }, // 15
	{ "SUB", &exec_add, &disasm_doubleop, &decode_doubleop }, // 16
	{ "", NULL, NULL, NULL },             // 17
};

struct instr_code instr_table_regop[] = {
	{ "MUL", NULL, &disasm_regop, &decode_regop },    // 0
	{ "DIV", NULL, &disasm_regop, &decode_regop },    // 1
	{ "ASH", NULL, &disasm_regop, &decode_regop },    // 2
	{ "ASHC", NULL, &disasm_regop, &decode_regop },    // 3
	{ "XOR", NULL, &disasm_regop, &decode_regop },    // 4
	{ "", NULL, NULL, NULL },             // 5
	{ "", NULL, NULL, NULL },             // 6
	{ "SOB", NULL, NULL, NULL },             // 7
};

struct instr_code instr_table_singleop[] = {

	{ "", NULL, NULL, NULL },             // b040
	{ "", NULL, NULL, NULL },             // b041
	{ "", NULL, NULL, NULL },             // b042
	{ "", NULL, NULL, NULL },             // b043
	{ "", NULL, NULL, NULL },             // b044
	{ "", NULL, NULL, NULL },             // b045
	{ "", NULL, NULL, NULL },             // b046
	{ "", NULL, NULL, NULL },             // b047
	{ "CLR", NULL, &disasm_singleop, &decode_singleop }, // b050
	{ "COM", NULL, &disasm_singleop, &decode_singleop }, // b051
	{ "INC", &exec_inc, &disasm_singleop, &decode_singleop }, // b052
	{ "DEC", &exec_dec, &disasm_singleop, &decode_singleop }, // b053
	{ "NEG", NULL, &disasm_singleop, &decode_singleop }, // b054
	{ "ADC", NULL, &disasm_singleop, &decode_singleop }, // b055
	{ "SBC", NULL, &disasm_singleop, &decode_singleop }, // b056
	{ "TST", NULL, &disasm_singleop, &decode_singleop }, // b057
	{ "ROR", NULL, &disasm_singleop, &decode_singleop }, // b060
	{ "ROL", NULL, &disasm_singleop, &decode_singleop }, // b061
	{ "ASR", NULL, &disasm_singleop, &decode_singleop }, // b062
	{ "ASL", NULL, &disasm_singleop, &decode_singleop }, // b063
	{ "", NULL, NULL, NULL },             // b064
	{ "", NULL, NULL, NULL },             // b065
	{ "", NULL, NULL, NULL },             // b066
	{ "", NULL, NULL, NULL },             // b067
	{ "", NULL, NULL, NULL },             // b070
	{ "", NULL, NULL, NULL },             // b071
	{ "", NULL, NULL, NULL },             // b072
	{ "", NULL, NULL, NULL },             // b073
	{ "", NULL, NULL, NULL },             // b074
	{ "", NULL, NULL, NULL },             // b075
	{ "", NULL, NULL, NULL },             // b076
	{ "", NULL, NULL, NULL },             // b077
};

struct instr_code instr_table_branch[] = {
	{ "", NULL, NULL, NULL },           // 0000
	{ "BR", &exec_br, &disasm_branch, &decode_branch }, // 0004
	{ "BNE", &exec_bne, &disasm_branch, &decode_branch }, // 0010
	{ "BEQ", &exec_beq, &disasm_branch, &decode_branch }, // 0014
	{ "BGE", NULL, &disasm_branch, &decode_branch }, // 0020
	{ "BLT", NULL, &disasm_branch, &decode_branch }, // 0024
	{ "BGT", NULL, &disasm_branch, &decode_branch }, // 0030
	{ "BLE", NULL, &disasm_branch, &decode_branch }, // 0034
	{ "BPL", NULL, &disasm_branch, &decode_branch }, // 1000
	{ "BMI", NULL, &disasm_branch, &decode_branch }, // 1004
	{ "BHI", NULL, &disasm_branch, &decode_branch }, // 1010
	{ "BLOS", NULL, &disasm_branch, &decode_branch }, // 1014
	{ "BVC", NULL, &disasm_branch, &decode_branch }, // 1020
	{ "BVS", NULL, &disasm_branch, &decode_branch }, // 1024
	{ "BCC", NULL, &disasm_branch, &decode_branch }, // 1030
	{ "BCS", NULL, &disasm_branch, &decode_branch }, // 1034
};

instr_info* decode_doubleop(instr_info* pinfo)
{
	struct doubleop_decoder *decoder = (struct doubleop_decoder*) pinfo->pcode;

	pinfo->op1.type = decoder->op1_mode;
	pinfo->op1.reg = decoder->op1_reg;
	pinfo->op2.type = decoder->op2_mode;
	pinfo->op2.reg = decoder->op2_reg;

	pinfo->length = 1;
	if (pinfo->op1.type == 6 || pinfo->op1.type == 7)
		pinfo->op1.imm = pinfo->pcode[pinfo->length++];
	if (pinfo->op2.type == 6 || pinfo->op2.type == 7)
		pinfo->op2.imm = pinfo->pcode[pinfo->length++];
	return pinfo;
}

instr_info* decode_regop(instr_info* pinfo)
{
	struct regop_decoder *decoder = (struct regop_decoder*) pinfo->pcode;

	pinfo->length = 1;
	pinfo->op1.reg = decoder->op1_reg;
	pinfo->op2.type = decoder->op2_mode;
	pinfo->op2.reg = decoder->op2_reg;
	if (pinfo->op2.type == 6 || pinfo->op2.type == 7)
		pinfo->op2.imm = pinfo->pcode[1];
	return pinfo;
}

instr_info* decode_singleop(instr_info* pinfo)
{
	struct singleop_decoder *decoder = (struct singleop_decoder*) pinfo->pcode;

	pinfo->op1.type = decoder->op1_mode;
	pinfo->op1.reg = decoder->op1_reg;

	pinfo->length = 1;
	if (pinfo->op1.type == 6 || pinfo->op1.type == 7)
		pinfo->op1.imm = pinfo->pcode[pinfo->length++];
	return pinfo;
}

instr_info* decode_branch(instr_info* pinfo)
{
	struct branch_decoder *decoder = (struct branch_decoder*) pinfo->pcode;
	pinfo->op1.imm = decoder->imm;
	pinfo->length = 0;
	return pinfo;
}

instr_info* find_regop(instr_info* pinfo)
{
	unsigned opcode = ((struct regop_decoder*) pinfo->pcode)->opcode;
	struct instr_code* instr = &instr_table_regop[opcode];
	if (instr->decode_instr != NULL){
		pinfo->icode = instr;
		return instr->decode_instr(pinfo);
	}
	else
		return NULL;
}

instr_info* find_singleop(instr_info* pinfo)
{
	unsigned opcode;
	struct instr_code* instr;
	if (((struct singleop_decoder*) pinfo->pcode)->space1){
		opcode = ((struct singleop_decoder*) pinfo->pcode)->opcode;
		instr = &instr_table_singleop[opcode];
	}
	else {
		opcode = ((struct branch_decoder*) pinfo->pcode)->opcode;
		opcode += ((struct branch_decoder*) pinfo->pcode)->opcode_hi << 3;
		instr = &instr_table_branch[opcode];
	}
	if (instr->decode_instr != NULL){
		pinfo->icode = instr;
		return instr->decode_instr(pinfo);
	}
	else
		return NULL;
}

unsigned decode_instr(u_int16_t* code, instr_info* pinfo)
{
	unsigned opcode = ((struct doubleop_decoder*) code)->opcode;
	struct instr_code* instr = &instr_table_doubleop[opcode];

	memset(pinfo, 0, sizeof(*pinfo));
	pinfo->code = *code;
	pinfo->pcode = code;

	if (instr->decode_instr != NULL){
		pinfo->icode = instr;
		return (instr->decode_instr(pinfo) == NULL);
	}
	else
		return 1;
}
