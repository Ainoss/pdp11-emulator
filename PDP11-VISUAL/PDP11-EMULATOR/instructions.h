

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "executer.h"
#include "decoder.h"

unsigned exec_add(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_mov(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_cmp(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_bis(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_bic(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_bit(pdp_machine_state* pstate, instr_info* pinfo);

unsigned exec_br(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_bne(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_beq(pdp_machine_state* pstate, instr_info* pinfo);

unsigned exec_inc(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_dec(pdp_machine_state* pstate, instr_info* pinfo);

unsigned exec_mul(pdp_machine_state* pstate, instr_info* pinfo);
unsigned exec_ash(pdp_machine_state* pstate, instr_info* pinfo);

#endif //INSTRUCTIONS_H

