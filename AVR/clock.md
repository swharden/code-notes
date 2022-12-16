# AVR Clock Configuration

### ccp_write()

Changing clock settings requires temporarially disabling Configuration Change Protection (CCP). 
After four clock cycles this setting clears. 
This is too fast to allow inline operations like OR statements, so using a function helps.

```c
void ccp_write(volatile register8_t* reg, uint8_t value){
	CCP = CCP_IOREG_gc;
	*reg = value;
}
```

### 20 MHz with CKOUT
```c
void configure_clock(){
	CCP = CCP_IOREG_gc;
	ccp_write(&CLKCTRL.MCLKCTRLA, CLKCTRL.MCLKCTRLA | CLKCTRL_CLKOUT_bm); // 20 MHz internal clock, enable CKOUT
	ccp_write(&CLKCTRL.MCLKCTRLB, 0); // disable prescaler
}
```
