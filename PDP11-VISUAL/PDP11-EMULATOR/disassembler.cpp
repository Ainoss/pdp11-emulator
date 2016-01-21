
#include "disassembler.h"
#include "executer.h"
#include "decoder.h"
#include <stdio.h>


unsigned disasm_instr(instr_info* pinfo, char* str)
{
	if (pinfo->icode->disasm_instr == NULL)
		return 1;

	pinfo->icode->disasm_instr(pinfo, str);
	return 0;
}

unsigned disasm_op(struct operand_info op, char *str)
{
	switch (op.type){
	case 0:
		sprintf_s(str, 16, "R%u", op.reg);
		break;
	case 1:
		sprintf_s(str, 16, "(R%u)", op.reg);
		break;
	case 2:
		sprintf_s(str, 16, "(R%u)+", op.reg);
		break;
	case 3:
		sprintf_s(str, 16, "@(R%u)+", op.reg);
		break;
	case 4:
		sprintf_s(str, 16, "-(R%u)", op.reg);
		break;
	case 5:
		sprintf_s(str, 16, "@-(R%u)", op.reg);
		break;
	case 6:
		sprintf_s(str, 16, "%u(R%u)", op.imm, op.reg);
		break;
	case 7:
		sprintf_s(str, 16, "@%u(R%u)", op.imm, op.reg);
		break;
	default:
		return 1;
	}
	return 0;
}

unsigned disasm_doubleop(instr_info* pinfo, char* str)
{
	char str_op1[32], str_op2[32];
	if (disasm_op(pinfo->op1, str_op1))
		return 1;
	if (disasm_op(pinfo->op2, str_op2))
		return 1;
	sprintf_s(str, 32, "%s %s, %s", pinfo->icode->name, str_op1, str_op2);
	return 0;
}

unsigned disasm_regop(instr_info* pinfo, char* str)
{
	char str_op[32];
	if (disasm_op(pinfo->op2, str_op))
		return 1;
	sprintf_s(str, 32, "%s R%u, %s", pinfo->icode->name, pinfo->op1.reg, str_op);
	return 0;
}

unsigned disasm_singleop(instr_info* pinfo, char* str)
{
	char str_op[32];
	if (disasm_op(pinfo->op1, str_op))
		return 1;
	sprintf_s(str, 32, "%s %s", pinfo->icode->name, str_op);
	return 0;
}

unsigned disasm_branch(instr_info* pinfo, char* str)
{
	sprintf_s(str, 32, "%s %d", pinfo->icode->name, (int8_t) pinfo->op1.imm);
	return 0;
}
