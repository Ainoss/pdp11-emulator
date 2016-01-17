
#ifndef EMULATOR_H
#define EMULATOR_H

#define EXTERN __declspec(dllexport)

extern "C"
{
	EXTERN unsigned pdp11_step();
	EXTERN unsigned pdp11_init(void* initial_rom);
//	EXTERN unsigned pdp11_debug();
    EXTERN unsigned pdp11_disasm(u_int16_t *ppc);
    EXTERN unsigned pdp11_get_reg(struct pdp11_reg *preg);
}

typedef struct pdp11_reg {
    u_int16_t reg[8];
    //struct psw_reg psw_reg;
};

#endif //EMULATOR_H
