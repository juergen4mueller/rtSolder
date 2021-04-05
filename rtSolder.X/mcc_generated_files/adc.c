/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1788
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc.h"
#include "device_config.h"

uint8_t meassure_number;
uint8_t an_in_pos;
uint16_t AN_IN_Temp, AN_IN_U_Supply;
uint16_t AN_Sample[2][16];

/**
  Section: Macro Declarations
*/

#define ACQ_US_DELAY 25

/**
  Section: ADC Module APIs
*/

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // ADRMD 12_bit_mode; GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;
    
    // ADFM 2s_complement; ADNREF VSS; ADPREF FVR; ADCS FOSC/32; 
    ADCON1 = 0xA3;
    
    // TRIGSEL disabled; CHSN ADNREF; 
    ADCON2 = 0x0F;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
    meassure_number = 0;
    an_in_pos = 0;
}

void ADC_StartConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);
    
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}

bool ADC_IsConversionDone()
{
    // Start the conversion
    return ((unsigned char)(!ADCON0bits.GO_nDONE));
}

adc_result_t ADC_GetConversionResult(void)
{
    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // Select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }
    
    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}


void ADC_TemperatureAcquisitionDelay(void)
{
    __delay_us(200);
}
uint8_t i;
void ADC_ISR(void)
{
    // Clear the ADC interrupt flag
    if(!(meassure_number % 2)){
        AN_Sample[0][an_in_pos]= ADC_GetConversionResult();
        ADC_StartConversion(AN3_U_Supply);
        meassure_number ++;
    }
    else if(meassure_number % 2){
        AN_Sample[1][an_in_pos]= ADC_GetConversionResult();
        an_in_pos ++;
        
        if(an_in_pos >= AN_IN_FILTER_SIZE){
            an_in_pos = 0;
            meassure_number = 0;
            AN_IN_Temp=0;
            AN_IN_U_Supply=0;
            for(i=0;i<AN_IN_FILTER_SIZE;i++){
                AN_IN_Temp+= AN_Sample[0][i];
                AN_IN_U_Supply+= AN_Sample[1][i];
            }
            AN_IN_Temp=AN_IN_Temp/AN_IN_FILTER_SIZE;
            AN_IN_U_Supply=AN_IN_U_Supply/AN_IN_FILTER_SIZE;
        }
        else{
            ADC_StartConversion(AN2_Temp_Tip);
            meassure_number ++;
        }
    }        
    PIR1bits.ADIF = 0;    
}
/**
 End of File
*/