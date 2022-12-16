# AVR Timer Notes

## 1 PPS with overflow events

This example achieves one pulse per second with a 20 MHz internal clock oscillator

```c
void configure_1pps(){
	// 20 MHz system clock with div64 prescaler is 312,500 Hz.
	// Setting a 16-bit timer's period to 31,250 means 10 overflows per second.
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; // overflow interrupt
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc; // normal mode
	TCA0.SINGLE.PER = 31250UL; // timer period
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV64_gc; // set clock source
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm; // start timer
}
```

```c
volatile uint8_t count = 0;
ISR(TCA0_OVF_vect)
{
	if (count+ == 10){
		count = 0;
		PORTA.OUT = PIN4_bm;
		} else {
		PORTA.OUT = 0;
	}
}
```

```c
int main(void)
{
	PORTA.DIR |= PIN4_bm; // set LED pin as output
	sei(); // enable global interrupts
	configure_clock();
	configure_1pps();
	while(1){}
}
```
