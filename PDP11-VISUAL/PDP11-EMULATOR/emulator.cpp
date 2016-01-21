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
#include "emulator.h"
#include "disassembler.h"
#include <stdint.h>

#define PDP11_VRAM_ADDR 16*1024
#define PDP11_VRAM_SIZE 16*1024
#define PDP11_ROM_ADDR  32*1024
#define PDP11_ROM_SIZE  32*1024

typedef uint16_t u_int16_t;

pdp_machine_state gstate;

unsigned pdp11_step()
{
	u_int16_t pc = gstate.reg[7];
	instr_info ii;
	unsigned st;

	st = decode_instr((u_int16_t*)&gstate.mem_raw[pc], &ii);
	if (st) {
		fprintf(stderr, "instruction not supported: pc=%X\n", pc);
		return 1;
	}
	st = execute_instr(&gstate, &ii);
	return st;
}

unsigned pdp11_init()
{
	uint16_t rom[16 * 1024];
	FILE* fin;
	if (fopen_s(&fin, "rom.raw", "r")){
		perror("opening rom file");
		return 1;
	}
	if (!fread(rom, sizeof(rom), 1, fin)){
		perror("reading rom file");
		return 1;
	}

	state_init(&gstate);
	load_rom(&gstate, &rom);

	fclose(fin);
	return 0;
}

unsigned pdp11_close()
{
	state_deinit(&gstate);
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

unsigned pdp11_get_reg(struct pdp11_reg *preg)
{
	for (int i = 0; i < 8; i++)
		preg->reg[i] = gstate.reg[i];
	preg->c_f = gstate.psw_reg.c_f;
	preg->n_f = gstate.psw_reg.n_f;
	preg->z_f = gstate.psw_reg.z_f;
	preg->v_f = gstate.psw_reg.v_f;
	return 0;
}

unsigned pdp11_disasm(u_int16_t *ppc, char *str)
{
	instr_info ii;
	unsigned st;
	if (!str)
		return 1;

	st = decode_instr((u_int16_t*)&gstate.mem_raw[*ppc], &ii);
	if (st) {
		fprintf(stderr, "instruction not supported: pc=%X\n", *ppc);
		return 1;
	}
	st = disasm_instr(&ii, str);
	*ppc += ii.length * 2;

	return st;
}

unsigned pdp11_get_frame(void *buffer)
{
	if (!buffer)
		return 1;
	memcpy(buffer, &gstate.mem_raw[PDP11_VRAM_ADDR], PDP11_VRAM_SIZE);
	return 0;
}