/* Select Chip */
#define SelectChannel(i) PORTB=i;o_CH_LE=1;o_CH_LE=0;
/* Select PIN */
#define AddressAsic(pin) PORTB=pin;o_AD_LE=1;o_AD_LE=0;
/* Reset Chip */
#define SoftReset() PORTB=0x40;o_AD_LE=1;o_AD_LE=1;o_AD_LE=1;o_AD_LE=0;

/* Write to ASIC PIN0 to PIN43 */
void SendData(volatile BYTE *input) {
  BYTE adr;
  SoftReset();
  for(adr=0;adr<44;adr++) { 
    AddressAsic(adr);	
    PORTB = input[adr];
    o_Write=1; o_Write=0; 
  }
}

/* Read 4 Byte nonce from PIN44 to PIN47 */
void GetNonce(void) {
  BYTE adr,b;
  for(adr=0;adr<4;adr++) {
    AddressAsic(adr+44);
    /* Set PORTB as input */
    TRISB = 0xff;
    /* Disable Interrupt */
    INTCONbits.GIEH = 0;
    o_Read=1; Nop(); Nop(); b=PORTB; o_Read=0;
    /* Enable Interrupt */
    INTCONbits.GIEH = 1;
    nonce[adr]=b;
    /* Set PORTB as output */
    TRISB = 0x00;
  }
}



