ENTRY(Reset_Handler)

MEMORY {
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS {
    .text : {
        KEEP(*(.vectors))   /* Vector table MUST be first */
        *(.text*)
        *(.rodata*)
        _sidata = .;        /* Start of init data in Flash */
    } > FLASH

    .data : AT(_sidata) {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    .bss : {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    /* Stack at top of RAM */
    _estack = ORIGIN(RAM) + LENGTH(RAM);
}
