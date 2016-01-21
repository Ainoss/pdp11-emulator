
#ifndef EMULATOR_H
#define EMULATOR_H


#include <stdint.h>
#define EXTERN __declspec(dllexport)

typedef uint16_t u_int16_t;
typedef uint8_t u_int8_t;

struct pdp11_reg {
	u_int16_t reg[8];

	u_int8_t c_f;
	u_int8_t v_f;
	u_int8_t z_f;
	u_int8_t n_f;

};

unsigned pdp11_init(void* initial_rom);
unsigned pdp11_close();

unsigned pdp11_debug();
unsigned pdp11_step();
unsigned pdp11_disasm(u_int16_t *ppc, char *str);
unsigned pdp11_get_reg(struct pdp11_reg *preg);
unsigned pdp11_get_frame(void *buffer);

#endif //EMULATOR_H
