#ifndef __OLED_CONFIG_H
#define	__OLED_CONFIG_H
#include "sys.h"


void OLEDcard(void);	
void OLEDtime(void);	
void OLED24C256check(void);
void ShowKeyValue(void);
void Showpasserr(void);
void Showpasscor(void);
void OLEDStandby(void);	
void ShowSTATUS(void) ;
void SHOWWIFIRest(void);
void SHOWSYSRest_factory(void);
void OLEDICcard(void);		
void OLEDshowfrequency(void);
void OLEDNOWhitelist(void);		
void OLEDBlacklist(void)	;
void	OLEDClock_delay(void);
void OLEDPasswordREE(void);		
void OLEDPasswordZQ(void);
void OLEDSector_Write_Failure(void);	
void OLEDSector_Read_Failure(void);
void OLEDName(void)	;
void OLEDSector_NO_Jurisdiction(void);
void OLEDSector_NO_HOliJurisdiction(void)	;





void initlcm(void);

void display(unsigned char x_add,unsigned char *ptr);


#endif /* __RC522_CONFIG_H */









