
#pragma once

#include "executer.h"
#include "decoder.h"

unsigned disasm_instr(instr_info* pinfo, char* str);

unsigned disasm_doubleop(instr_info* pinfo, char* str);
unsigned disasm_regop(instr_info* pinfo, char* str);
unsigned disasm_singleop(instr_info* pinfo, char* str);
unsigned disasm_branch(instr_info* pinfo, char* str);
