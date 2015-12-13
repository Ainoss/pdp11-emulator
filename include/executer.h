/*
 * executer.c 
 * Used to execute pdp-11 instructions and to store machine state
 * @ainoss
 */

#ifndef EXECUTER_H
#define EXECUTER_H

#include <stdlib.h>
#include <string.h>
#include "decoder.h"


struct psw_reg {
    u_int8_t c_f: 1;
    u_int8_t v_f: 1;
    u_int8_t z_f: 1;
    u_int8_t n_f: 1;
};

typedef struct pdp_machine_state {
    char* mem_raw;
    u_int16_t* mem_word;
    u_int16_t* rom;

    u_int16_t reg[8];
    struct psw_reg psw_reg;
} pdp_machine_state;


unsigned state_init(pdp_machine_state* pstate);
unsigned execute_instr(pdp_machine_state* pstate, instr_info* pinfo);
unsigned load_rom(pdp_machine_state* pstate, void* initial_rom);


#endif //EXECUTER_H

