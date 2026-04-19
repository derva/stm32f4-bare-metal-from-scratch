#include <stdint.h>

// Defined in linker script
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;

// Forward declare main
int main(void);

// Fault handlers (minimal — just loop)
void Default_Handler(void) { while(1); }
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));

void Reset_Handler(void) {
    // 1. Copy .data from Flash to RAM
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++;

    // 2. Zero .bss
    dst = &_sbss;
    while (dst < &_ebss) *dst++ = 0;

    // 3. Call main
    main();

    // Should never return
    while(1);
}

// Vector table — placed in .vectors section
__attribute__((section(".vectors")))
uint32_t vector_table[] = {
    (uint32_t)&_estack,          // Stack pointer
    (uint32_t)&Reset_Handler,    // Reset
    (uint32_t)&NMI_Handler,      // NMI
    (uint32_t)&HardFault_Handler,// Hard fault
    // ... add more as needed
};
