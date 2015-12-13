/*
 * executer.c 
 * Used to execute pdp-11 instructions and to store machine state
 * @ainoss
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "executer.h"
#include "decoder.h"


unsigned state_init(pdp_machine_state* pstate)
{
    memset(pstate, 0, sizeof(*pstate));

    pstate->mem_raw = calloc(32 * 1024, sizeof(u_int16_t));
    pstate->mem_word = (u_int16_t*) pstate->mem_raw;
    pstate->rom = pstate->mem_word + 16 * 1024;

    pstate->reg[7] = 32 * 1024;
    return 0;
}

unsigned load_rom(pdp_machine_state* pstate, void* initial_rom)
{
    memcpy(&pstate->mem_raw[32*1024], initial_rom, 32*1024);
    return 0;
}

unsigned execute_instr(pdp_machine_state* pstate, instr_info* pinfo)
{
    printf("exec: %s, %ubytes\n", pinfo->icode->name, pinfo->length);
    if (pinfo->icode->exec_instr == NULL)
        return 1;

    pinfo->icode->exec_instr(pstate, pinfo);
    pstate->reg[7] += pinfo->length * 2;

    return 0;
}

u_int16_t* get_op_addr(pdp_machine_state* pstate, char byte, struct operand_info op)
{
    u_int16_t value;
    u_int16_t* address;
    u_int16_t pdp_addr;
    switch (op.type >> 1){
        case 0:
            address = &pstate->reg[op.reg];
            break;
        case 1:
            pdp_addr = pstate->reg[op.reg];
            pstate->reg[op.reg] += (op.type & 1) ? 2 : ((byte) ? 1 : 2);
            address = (u_int16_t*) &pstate->mem_raw[pdp_addr];
            break;
        case 2:
            pstate->reg[op.reg] -= (op.type & 1) ? 2 : ((byte) ? 1 : 2);
            pdp_addr = pstate->reg[op.reg];
            address = (u_int16_t*) &pstate->mem_raw[pdp_addr];
            break;
        case 3:
            pdp_addr = pstate->reg[op.reg] + op.imm;
            address = (u_int16_t*) &pstate->mem_raw[pdp_addr];
            break;
        default:
            break;
    }

    if (op.type & 1){
        address = (u_int16_t*) &pstate->mem_raw[*address];
    }
    return address;
}

unsigned update_psw_nz(struct psw_reg* psw, u_int32_t res, char byte)
{
    psw->z_f = !(res & (byte ? (u_int8_t)-1 : (u_int16_t)-1));
    psw->n_f = (byte ? res >> 7 : res >> 15) & 1;
    return 0;
}

#define GET_ADDR(x) get_op_addr(pstate, pinfo->byte, x)
#define GET_VAL(x) ((pinfo->byte) ? (u_int8_t) (x) : (x))
#define SET_VAL(x, y) ((pinfo->byte) ? (*(u_int8_t*)(x) = y) : (*(x) = y))
#define UPD_PSW_NZ(x) {                                                                 \
            pstate->psw_reg.z_f = !(x & (pinfo->byte ? (u_int8_t)-1 : (u_int16_t)-1));  \
            pstate->psw_reg.n_f = (pinfo->byte ? x >> 7 : x >> 15) & 1;                 \
        }


unsigned exec_add(pdp_machine_state* pstate, instr_info* pinfo)
{
    char sub_instr = pinfo->byte;
    pinfo->byte = 0;
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);
    u_int32_t res;

    if (!sub_instr)
        res = GET_VAL(*dst) + GET_VAL(*src);
    else
        res = GET_VAL(*dst) - GET_VAL(*src);
    SET_VAL(dst, res);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    pstate->psw_reg.c_f = pinfo->byte ? (res & (1 << 8)) :(res & (1 << 16));
    return 0;
}

unsigned exec_mov(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);

    SET_VAL(dst, GET_VAL(*src));

    UPD_PSW_NZ(GET_VAL(*src));
    pstate->psw_reg.v_f = 0;
    return 0;
}

unsigned exec_cmp(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);
    u_int32_t res;

    res = GET_VAL(*src) - GET_VAL(*dst);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    pstate->psw_reg.c_f = pinfo->byte ? (res & (1 << 8)) :(res & (1 << 16));
    return 0;
}

unsigned exec_bis(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);
    u_int32_t res;

    res = GET_VAL(*dst) | GET_VAL(*src);
    SET_VAL(dst, res);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    return 0;
}

unsigned exec_bic(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);
    u_int32_t res;

    res = GET_VAL(*dst) & (~GET_VAL(*src));
    SET_VAL(dst, res);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    return 0;
}

unsigned exec_bit(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int16_t* dst = GET_ADDR(pinfo->op2);
    u_int32_t res;

    res = GET_VAL(*dst) & GET_VAL(*src);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    return 0;
}

unsigned exec_br(pdp_machine_state* pstate, instr_info* pinfo)
{
    int8_t offset = pinfo->op1.imm;
    pstate->reg[7] += offset << 1;
    return 0;
}

unsigned exec_bne(pdp_machine_state* pstate, instr_info* pinfo)
{
    int8_t offset = pinfo->op1.imm;
    if (!pstate->psw_reg.z_f)
        pstate->reg[7] += offset << 1;
    else 
        pstate->reg[7] += 2;
    return 0;
}

unsigned exec_beq(pdp_machine_state* pstate, instr_info* pinfo)
{
    int8_t offset = pinfo->op1.imm;
    if (pstate->psw_reg.z_f)
        pstate->reg[7] += offset << 1;
    else 
        pstate->reg[7] += 2;
    return 0;
}

unsigned exec_inc(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int32_t res;

    res = GET_VAL(*src) + 1;
    SET_VAL(src, res);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    return 0;
}

unsigned exec_dec(pdp_machine_state* pstate, instr_info* pinfo)
{
    u_int16_t* src = GET_ADDR(pinfo->op1);
    u_int32_t res;

    res = GET_VAL(*src) - 1;
    SET_VAL(src, res);

    UPD_PSW_NZ(res);
    pstate->psw_reg.v_f = 0;
    return 0;
}

