all: firmware.bin
.PHONY: all clean flash

startup.o: startup.s
	arm-none-eabi-gcc -c startup.s -o startup.o
main.o: main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb main.c -o main.o
firmware.elf: linker.ld startup.o main.o
	arm-none-eabi-gcc -T linker.ld -nostdlib -mcpu=cortex-m4 -mthumb startup.o main.o -o firmware.elf
firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
flash: firmware.bin
	st-flash write firmware.bin 0x08000000
clean:
	rm -f *.o *.elf *.bin
