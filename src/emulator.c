/*
 * emulator.c 
 * Used to emulate pdp-11 computer
 * @ainoss
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decoder.h"
#include "executer.h"


pdp_machine_state gstate;

unsigned pdp11_step()
{
    u_int16_t pc = gstate.reg[7];
    instr_info ii;
    unsigned st;

    st = decode_instr((u_int16_t*) &gstate.mem_raw[pc], &ii);
    if (st) {
        fprintf(stderr, "instruction not supported: pc=%X\n", pc);
        return 1;
    }
    st = execute_instr(&gstate, &ii);
    if (st)
        return 1;

    return 0;
}

unsigned pdp11_init(void* initial_rom)
{
    state_init(&gstate);
    load_rom(&gstate, initial_rom);
    return 0;
}

unsigned pdp11_debug()
{
    int i;

    printf("Registers: ");
    for (i = 0; i < 8; i++)
        printf("%d:%04X  ", i, gstate.reg[i]);
    printf("\n");

    printf("psw: ");
    printf("n=%u, ", gstate.psw_reg.n_f);
    printf("z=%u, ", gstate.psw_reg.z_f);
    printf("v=%u, ", gstate.psw_reg.v_f);
    printf("c=%u", gstate.psw_reg.c_f);
    printf("\n");

    return 0;
}

