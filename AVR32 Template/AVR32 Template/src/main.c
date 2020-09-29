#include <asf.h>
#include <board.h>
#include <gpio.h>
#include <sysclk.h>
#include "busy_delay.h"

#define CONFIG_USART_IF (AVR32_USART2)

// defines for BRTT interface
#define TEST_A      AVR32_PIN_PA31
#define RESPONSE_A  AVR32_PIN_PA30
#define TEST_B      AVR32_PIN_PA29
#define RESPONSE_B  AVR32_PIN_PA28
#define TEST_C      AVR32_PIN_PA27
#define RESPONSE_C  AVR32_PIN_PB00


__attribute__((__interrupt__)) static void interrupt_J3(void);

volatile int flagA = 0;
volatile int flagB = 0;
volatile int flagC = 0;

void init(){
    sysclk_init();
    board_init();
    busy_delay_init(BOARD_OSC0_HZ);
    
    cpu_irq_disable();
    INTC_init_interrupts();
    INTC_register_interrupt(&interrupt_J3, AVR32_GPIO_IRQ_3, AVR32_INTC_INT1);
    cpu_irq_enable();
    
    stdio_usb_init(&CONFIG_USART_IF);

    #if defined(__GNUC__) && defined(__AVR32__)
        setbuf(stdout, NULL);
        setbuf(stdin,  NULL);
    #endif
}

__attribute__((__interrupt__)) static void interrupt_J3(void){
	if (gpio_get_pin_interrupt_flag(TEST_C)) {
		gpio_clear_pin_interrupt_flag(TEST_C);
		flagC = 1;
	}
	if (gpio_get_pin_interrupt_flag(TEST_B)) {
		gpio_clear_pin_interrupt_flag(TEST_B);
		flagB = 1;
	}
	if (gpio_get_pin_interrupt_flag(TEST_A)) {
		gpio_clear_pin_interrupt_flag(TEST_A);
		flagA = 1;
	}
}


int main (void){
    init();
    gpio_toggle_pin(LED0_GPIO);
	gpio_enable_pin_interrupt(TEST_A, GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(TEST_B, GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(TEST_C, GPIO_PIN_CHANGE);
	
	// sett opp inngang
	// sett opp utgang
	// sett respons til 1
	
	gpio_configure_pin (TEST_A, GPIO_DIR_INPUT); 
	gpio_configure_pin (RESPONSE_A, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH); 
	gpio_configure_pin (TEST_B, GPIO_DIR_INPUT); 
	gpio_configure_pin (RESPONSE_B, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH); 
	gpio_configure_pin (TEST_C, GPIO_DIR_INPUT); 
	gpio_configure_pin (RESPONSE_C, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH); 
	
	
    while(1){
	    if (flagC) {
		    gpio_toggle_pin(RESPONSE_C);
			flagC = 0;
		}
		if (flagB) {
			gpio_toggle_pin(RESPONSE_B);
			
			flagB = 0;
			busy_delay_us(100);
		}
		if (flagA) {
			gpio_toggle_pin(RESPONSE_A);
			flagA = 0;
		}
	}
}
