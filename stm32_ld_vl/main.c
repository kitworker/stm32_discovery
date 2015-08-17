#include "stm32f10x.h"
uint8_t i=0;
// _______
int main(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;  // Enable PORTC Periph clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable TIM2 Periph clock
  // Clear PC8 and PC9 control register bits
  GPIOC->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8 |
          GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
  // Configure PC8 and PC9 as Push Pull output at max 10Mhz
  GPIOC->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE9_0;
  TIM2->PSC = SystemCoreClock / 1000 - 1; // 1000 tick/sec
  TIM2->ARR = 1000;  // 1 Interrupt/sec (1000/100)
  TIM2->DIER |= TIM_DIER_UIE; // Enable tim2 interrupt
  TIM2->CR1 |= TIM_CR1_CEN;   // Start count
  NVIC_EnableIRQ(TIM2_IRQn);  // Enable IRQ
  while(1); // Infinity loop
}
void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~TIM_SR_UIF; //Clean UIF Flag
  if (1 == (i++ & 0x1)) {
    GPIOC->BSRR = GPIO_BSRR_BS8;   // Set PC8 bit
    GPIOC->BSRR = GPIO_BSRR_BR9;   // Reset PC9 bit
  } else {
    GPIOC->BSRR = GPIO_BSRR_BS9;   // Set PC9 bit
    GPIOC->BSRR = GPIO_BSRR_BR8;   // Reset PC8 bit
  }
}
