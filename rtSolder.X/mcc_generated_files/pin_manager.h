/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F1788
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IOC_PWM_Tip aliases
#define IOC_PWM_Tip_TRIS                 TRISAbits.TRISA0
#define IOC_PWM_Tip_LAT                  LATAbits.LATA0
#define IOC_PWM_Tip_PORT                 PORTAbits.RA0
#define IOC_PWM_Tip_WPU                  WPUAbits.WPUA0
#define IOC_PWM_Tip_ANS                  ANSELAbits.ANSA0
#define IOC_PWM_Tip_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IOC_PWM_Tip_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IOC_PWM_Tip_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IOC_PWM_Tip_GetValue()           PORTAbits.RA0
#define IOC_PWM_Tip_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IOC_PWM_Tip_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IOC_PWM_Tip_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IOC_PWM_Tip_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IOC_PWM_Tip_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define IOC_PWM_Tip_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set AN2_Temp_Tip aliases
#define AN2_Temp_Tip_TRIS                 TRISAbits.TRISA2
#define AN2_Temp_Tip_LAT                  LATAbits.LATA2
#define AN2_Temp_Tip_PORT                 PORTAbits.RA2
#define AN2_Temp_Tip_WPU                  WPUAbits.WPUA2
#define AN2_Temp_Tip_ANS                  ANSELAbits.ANSA2
#define AN2_Temp_Tip_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define AN2_Temp_Tip_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define AN2_Temp_Tip_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define AN2_Temp_Tip_GetValue()           PORTAbits.RA2
#define AN2_Temp_Tip_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define AN2_Temp_Tip_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define AN2_Temp_Tip_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define AN2_Temp_Tip_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define AN2_Temp_Tip_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define AN2_Temp_Tip_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set AN3_U_Supply aliases
#define AN3_U_Supply_TRIS                 TRISAbits.TRISA3
#define AN3_U_Supply_LAT                  LATAbits.LATA3
#define AN3_U_Supply_PORT                 PORTAbits.RA3
#define AN3_U_Supply_WPU                  WPUAbits.WPUA3
#define AN3_U_Supply_ANS                  ANSELAbits.ANSA3
#define AN3_U_Supply_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define AN3_U_Supply_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define AN3_U_Supply_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define AN3_U_Supply_GetValue()           PORTAbits.RA3
#define AN3_U_Supply_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define AN3_U_Supply_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define AN3_U_Supply_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define AN3_U_Supply_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define AN3_U_Supply_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define AN3_U_Supply_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set IN_Switch1 aliases
#define IN_Switch1_TRIS                 TRISAbits.TRISA6
#define IN_Switch1_LAT                  LATAbits.LATA6
#define IN_Switch1_PORT                 PORTAbits.RA6
#define IN_Switch1_WPU                  WPUAbits.WPUA6
#define IN_Switch1_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IN_Switch1_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IN_Switch1_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define IN_Switch1_GetValue()           PORTAbits.RA6
#define IN_Switch1_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define IN_Switch1_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define IN_Switch1_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define IN_Switch1_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)

// get/set OUT_LED_RT aliases
#define OUT_LED_RT_TRIS                 TRISAbits.TRISA7
#define OUT_LED_RT_LAT                  LATAbits.LATA7
#define OUT_LED_RT_PORT                 PORTAbits.RA7
#define OUT_LED_RT_WPU                  WPUAbits.WPUA7
#define OUT_LED_RT_ANS                  ANSELAbits.ANSA7
#define OUT_LED_RT_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define OUT_LED_RT_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define OUT_LED_RT_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define OUT_LED_RT_GetValue()           PORTAbits.RA7
#define OUT_LED_RT_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define OUT_LED_RT_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define OUT_LED_RT_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define OUT_LED_RT_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define OUT_LED_RT_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define OUT_LED_RT_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set IN_Switch2 aliases
#define IN_Switch2_TRIS                 TRISBbits.TRISB0
#define IN_Switch2_LAT                  LATBbits.LATB0
#define IN_Switch2_PORT                 PORTBbits.RB0
#define IN_Switch2_WPU                  WPUBbits.WPUB0
#define IN_Switch2_ANS                  ANSELBbits.ANSB0
#define IN_Switch2_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IN_Switch2_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IN_Switch2_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IN_Switch2_GetValue()           PORTBbits.RB0
#define IN_Switch2_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IN_Switch2_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IN_Switch2_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IN_Switch2_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IN_Switch2_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define IN_Switch2_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set OUT_LED_GN aliases
#define OUT_LED_GN_TRIS                 TRISBbits.TRISB2
#define OUT_LED_GN_LAT                  LATBbits.LATB2
#define OUT_LED_GN_PORT                 PORTBbits.RB2
#define OUT_LED_GN_WPU                  WPUBbits.WPUB2
#define OUT_LED_GN_ANS                  ANSELBbits.ANSB2
#define OUT_LED_GN_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define OUT_LED_GN_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define OUT_LED_GN_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define OUT_LED_GN_GetValue()           PORTBbits.RB2
#define OUT_LED_GN_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define OUT_LED_GN_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define OUT_LED_GN_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define OUT_LED_GN_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define OUT_LED_GN_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define OUT_LED_GN_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set TIP_SUPPLY_EN aliases
#define TIP_SUPPLY_EN_TRIS                 TRISCbits.TRISC0
#define TIP_SUPPLY_EN_LAT                  LATCbits.LATC0
#define TIP_SUPPLY_EN_PORT                 PORTCbits.RC0
#define TIP_SUPPLY_EN_WPU                  WPUCbits.WPUC0
#define TIP_SUPPLY_EN_ANS                  ANSELCbits.ANSC0
#define TIP_SUPPLY_EN_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define TIP_SUPPLY_EN_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define TIP_SUPPLY_EN_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define TIP_SUPPLY_EN_GetValue()           PORTCbits.RC0
#define TIP_SUPPLY_EN_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define TIP_SUPPLY_EN_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define TIP_SUPPLY_EN_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define TIP_SUPPLY_EN_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define TIP_SUPPLY_EN_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define TIP_SUPPLY_EN_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set TIP_PS1 aliases
#define TIP_PS1_TRIS                 TRISCbits.TRISC1
#define TIP_PS1_LAT                  LATCbits.LATC1
#define TIP_PS1_PORT                 PORTCbits.RC1
#define TIP_PS1_WPU                  WPUCbits.WPUC1
#define TIP_PS1_ANS                  ANSELCbits.ANSC1
#define TIP_PS1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define TIP_PS1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define TIP_PS1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define TIP_PS1_GetValue()           PORTCbits.RC1
#define TIP_PS1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define TIP_PS1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define TIP_PS1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define TIP_PS1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define TIP_PS1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define TIP_PS1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set TIP_PS2 aliases
#define TIP_PS2_TRIS                 TRISCbits.TRISC2
#define TIP_PS2_LAT                  LATCbits.LATC2
#define TIP_PS2_PORT                 PORTCbits.RC2
#define TIP_PS2_WPU                  WPUCbits.WPUC2
#define TIP_PS2_ANS                  ANSELCbits.ANSC2
#define TIP_PS2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define TIP_PS2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define TIP_PS2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define TIP_PS2_GetValue()           PORTCbits.RC2
#define TIP_PS2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define TIP_PS2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define TIP_PS2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define TIP_PS2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define TIP_PS2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define TIP_PS2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_ANS                  ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_ANS                  ANSELCbits.ANSC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF0 pin functionality
 * @Example
    IOCAF0_ISR();
 */
void IOCAF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_InterruptHandler);

*/
extern void (*IOCAF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_DefaultInterruptHandler);

*/
void IOCAF0_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/