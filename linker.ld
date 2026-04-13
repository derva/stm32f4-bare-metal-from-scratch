MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x80000
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x30000
}
_estack = ORIGIN(SRAM) + LENGTH(SRAM);
SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		*(.isr_vector)
		. = ALIGN(4);
	} > FLASH
	.text : {
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH
	.bss : {
		. = ALIGN(4);
		_sbss =	.;
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		_ebss = .;
	} > SRAM
	.data : {
		. = ALIGN(4);
		_sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > SRAM AT > FLASH
	_sidata = LOADADDR(.data);
}
