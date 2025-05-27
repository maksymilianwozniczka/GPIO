#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

#define S0_bm   0x00000010  
#define S1_bm   0x00000040  
#define S2_bm   0x00000020  
#define S3_bm   0x00000080  

unsigned int uiLedIndex = 0;

void Delay(int iOpoznienieMS){
    int iLicznikPetli;
    iOpoznienieMS = iOpoznienieMS * 2500;
    for(iLicznikPetli = 0; iLicznikPetli < iOpoznienieMS; iLicznikPetli++) {}
}

void LedInit() {
    IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
}

void LedOn(unsigned char ucLedIndeks){
    IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
    switch (ucLedIndeks) {
        case 0: IO1SET = LED0_bm; break;
        case 1: IO1SET = LED1_bm; break;
        case 2: IO1SET = LED2_bm; break;
        case 3: IO1SET = LED3_bm; break;
    }
}

void KeyboardInit() {
    IO0DIR &= ~(S0_bm | S1_bm | S2_bm | S3_bm);  
}

enum eKeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3 };

enum eKeyboardState eKeyboardRead(){
	
	if ((IO0PIN & S0_bm) == 0){
		
		return BUTTON_0;
	
	}
	else if ((IO0PIN & S1_bm) == 0){
		
		return BUTTON_1;
	
	}
	else if ((IO0PIN & S2_bm) == 0){
		
		return BUTTON_2;
		
	}
	else if ((IO0PIN & S3_bm) == 0){
		
		return BUTTON_3;
		
	}
	else{
		
		return RELASED;
	
	}
}

void StepLeft(void){
	
	uiLedIndex = (uiLedIndex + 1) % 4; 
	LedOn(uiLedIndex);

}	

void StepRight(void){
	
	uiLedIndex= (uiLedIndex - 1) % 4;
	LedOn(uiLedIndex);

}

int main(){
		LedInit();
    KeyboardInit();
    
    while(1) {
        switch (eKeyboardRead()) {
            case BUTTON_0:
                StepLeft();
                Delay(250);
                while(eKeyboardRead() == BUTTON_0);
                break;
                
            case BUTTON_1:
                StepRight();
								Delay(250);
								while(eKeyboardRead() == BUTTON_1);
								break;
                
            case BUTTON_2:
                LedOn(2);
                break;
                
            case BUTTON_3:
                LedOn(3);
                break;
                
            case RELASED:
                LedOn(uiLedIndex);  
                break;
        }
        Delay(10);
    }
}

//test_gita
