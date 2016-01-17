
#ifndef EMULATOR_H
#define EMULATOR_H

#define EXTERN __declspec(dllexport)

extern "C"
{
	EXTERN unsigned pdp11_step();
	EXTERN unsigned pdp11_init(void* initial_rom);
	EXTERN unsigned pdp11_debug();
}

#endif //EMULATOR_H
