#include "STM32F3xx.h"
#include "common.h"

/**
 * Initialize the HSI clock source and reset the PLL configuration. This
 * function is called by the startup_common.s file, just before calling the
 * main() function.
 *
 * You can adapt this function to fit your needs, however, do not change its
 * name! It is called in the startup code.
 */
void SystemInit (void) {
  // FPU settings
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  // Set CP10 and CP11 Full Access
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
#endif

  // Set HSION bit
  RCC->CR |= 0x00000001U;

  // Reset CFGR register
  RCC->CFGR &= 0xF87FC00CU;

  // Reset HSEON, CSSON and PLLON bits
  RCC->CR &= 0xFEF6FFFFU;

  // Reset HSEBYP bit
  RCC->CR &= 0xFFFBFFFFU;

  // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE bits
  RCC->CFGR &= 0xFF80FFFFU;

  // Reset PREDIV1[3:0] bits
  RCC->CFGR2 &= 0xFFFFFFF0U;

  // Reset USARTSW[1:0], I2CSW and TIMs bits
  RCC->CFGR3 &= 0xFF00FCCCU;

  // Disable all interrupts
  RCC->CIR = 0x00000000U;
}

// These symbols are provided by the linker
extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

/**
 * Calls the functions in the preinit and init arrays. The start and end
 * addresses of these arrays are provided by the linker.
 *
 * You can adapt this function to fit your needs, however, do not change its
 * name! It is called in the startup code.
 */
void __main () {
  for (void (**f)() = __preinit_array_start; f < __preinit_array_end; ++f) {
    (*f)();
  }

  for (void (**f)() = __init_array_start; f < __init_array_end; ++f) {
    (*f)();
  }
}
