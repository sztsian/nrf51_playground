/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x0001B000, LENGTH = 0x25000
  RAM (rwx) :  ORIGIN = 0x200013C8, LENGTH = 0x8000
}


INCLUDE "nrf51_common.ld"
