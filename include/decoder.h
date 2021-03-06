/*
 * decoder.h
 * @ainoss
 */

#ifndef DECODER_H
#define DECODER_H

#include <stdlib.h>

struct operand_info {
    char type;
    char reg;
    u_int16_t imm;
};

typedef struct instr_info {
    u_int16_t           code;
    u_int16_t*          pcode;
    struct instr_code*  icode;
    struct operand_info op1;
    struct operand_info op2;
    char                length;
    char                byte;
} instr_info;

struct pdp_machine_state;

struct instr_code {
    char name[8];
    unsigned (*exec_instr)(struct pdp_machine_state* pstate, instr_info* pinfo);
    void (*disasm_instr)();
    struct instr_info* (*decode_instr)(struct instr_info*);
};

struct doubleop_decoder {
    u_int32_t op2_reg: 3;
    u_int32_t op2_mode: 3;
    u_int32_t op1_reg: 3;
    u_int32_t op1_mode: 3;
    u_int32_t opcode: 4;
} __attribute__ ((__packed__));

struct regop_decoder {
    u_int32_t op2_reg: 3;
    u_int32_t op2_mode: 3;
    u_int32_t op1_reg: 3;
    u_int32_t opcode: 3;
    u_int32_t space1: 4;
} __attribute__ ((__packed__));

struct singleop_decoder {
    u_int32_t op1_reg: 3;
    u_int32_t op1_mode: 3;
    u_int32_t opcode: 5;
    u_int32_t space1: 4;
    u_int32_t byte: 1;
} __attribute__ ((__packed__));

struct branch_decoder {
    u_int32_t imm: 8;
    u_int32_t opcode: 3;
    u_int32_t space1: 4;
    u_int32_t opcode_hi: 1;
} __attribute__ ((__packed__));

instr_info* decode_doubleop(instr_info* pinfo);
instr_info* decode_regop(instr_info* pinfo);
instr_info* decode_singleop(instr_info* pinfo);
instr_info* decode_branch(instr_info* pinfo);

instr_info* find_regop(instr_info* pinfo);
instr_info* find_singleop(instr_info* pinfo);

unsigned decode_instr(u_int16_t* code, instr_info* pinfo);

#endif //DECODER_H

