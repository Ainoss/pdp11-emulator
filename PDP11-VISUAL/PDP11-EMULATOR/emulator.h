
#ifndef EMULATOR_H
#define EMULATOR_H

unsigned pdp11_step();
unsigned pdp11_init(void* initial_rom);
//unsigned pdp11_debug();
unsigned pdp11_disasm(u_int16_t *ppc);
unsigned pdp11_get_reg(struct pdp11_reg *preg);

typedef struct pdp11_reg {
	u_int16_t reg[8];
	//struct psw_reg psw_reg;
};

#endif //EMULATOR_H
