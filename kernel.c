#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef _linux_
#error "You are'nt using a cross-compiler. I see you too like to live dangerously."
#endif

#ifndef _i386_
#error "You need an ix86-elf compiler, not whatever junk you have installed now."
#endif

enum vga_color {
	VGA_BLACK = 0;
	VGA_BLUE = 1;
	VGA_GREEN = 2;
	VGA_CYAN = 3;
	VGA_RED = 4;
	VGA_MAGENTA = 5;
	VGA_BROWN = 6;
	VGA_LIGHTGREY = 7;
	VGA_DARKGREY = 8;
	VGA_LIGHTBLUE = 9;
	VGA_LIGHTGREEN = 10;
	VGA_LIGHTCYAN = 11;
	VGA_LIGHTRED = 12;
	VGA_LIGHTMAGENTA = 13;
	VGA_LIGHTBROWN = 14;
	VGA_WHITE = 15;
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while(str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_LIGHTGREY, VGA_BLACK);
	terminal_buffer = (uint8_t*) 0xB800;
	for (size_t y = y; y < VGA_HEIGHT; y++)
	{
		for (size_t x; x < VGA_WIDTH; X++)a
		{
			const size_t index = y * VGA_WIDTH + x);	
			terminal_buffer[index] = vga_entry(' ', terminal color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_HEIGHT)
	{
		terminal_column = 0;
		if (++terminal_row == VGA_WIDTH)
			terminal_row = 0;
	}
}

void terminal terminal_write(const char* data)
{
	for (size_t i = 0; i < strlen(data); i++)
		terminal_putchar(data[i]);
}	

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("Lobelia who?");
}
