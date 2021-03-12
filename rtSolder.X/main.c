/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F1788
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "OLED/i2c1.h"
#include "OLED/lcd.h"
#include "OLED/font.h"
#include <stdio.h>
#include <string.h>

uint16_t loads_per_minute;
uint16_t time_counter;
uint16_t counter_200ms;
uint8_t counter_minutes;
//#define TEST_POWER_MODULE

__EEPROM_DATA(0x02/*default power*/, 0x35/*default temperature*/, 0x01/*auto off nach 5 min*/, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF); // Fill first 8 bytes of EEPROM
/*            SW1                              SW2
            +++++++++                       +++++++++
 *          +       +    **************     +       +
 *          +   o   +    **************     +   o   +
 *          +       +    **************     +       +
 *          +++++++++                       +++++++++
 
 *          
 *          Menü ON   LP                    ON SP 
 *          Menü Skip LP                    OFF LP
 *          Temperatur -                  Temperatur +  
 * 
 *  Im Menü:
 *  - Solltemperatur gespeichert im EEPROM
 *  - Leistung      gespeichert im EEPROM
 * 
 * 
 * 
 *  OFF 
 * 
 */

/*
RC1+RC2 0 -> U = 9,1V P= 41 W (TIP_PS1+TIP_PS2)
RC1 0 ???> U = 7,4V P= 27W (TIP_PS1)
RC2 0 ???> U = 6,1V P= 18W (TIP_PS2)
nichts 0 ??> U = 4,4V P= 10W (kein TIP_PS geschalten)
*/

uint8_t counter2ms_solder, counter2ms_switch;
uint8_t tmr_2ms, tmr1_msg;
uint8_t Switch_1, Switch_2, Switch_1_alt, Switch_2_alt;
uint8_t counter_LP_SW1, counter_LP_SW2;
uint16_t Temperatur_TIP;
uint16_t U_Supply;
uint16_t TEMP_SOLL;
uint16_t AN_out;

uint16_t Temp_Anz_Filter[16];
uint8_t  Temp_Anz_pos;

char text_out[30];

extern uint16_t AN_IN_Temp, AN_IN_U_Supply;



uint8_t mode, mode_alt;
#define mode_startup 0x00
#define mode_off 0x01
#define mode_menue 0x02
#define mode_work  0x03

#define solder_display_normal   0x00
#define solder_display_dev      0x01
uint8_t solder_display_mode;

uint8_t EE_solltemperatur;  // Faktor 10
uint8_t EE_soll_Power;       // Faktor 10
#define Auto_off_disabled   0x00
#define Auto_off_5_min      0x01
#define Auto_off_10_min     0x02
#define Auto_off_15_min     0x03
uint8_t EE_AutoOff;         //
uint8_t x;

void timer1_fired(void){
    tmr1_msg ++;
}

void init_system(void){
    counter2ms_solder = 0;
    solder_display_mode = solder_display_normal;
#ifdef TEST_POWER_MODULE
    
#else
    initI2C();
    lcd_init();
#endif
    Temp_Anz_pos = 0;
    mode = mode_startup;
    EE_soll_Power = DATAEE_ReadByte(0x00);
    EE_solltemperatur = DATAEE_ReadByte(0x01);
    EE_AutoOff = DATAEE_ReadByte(0x02);
    
    if(EE_soll_Power > 4){
        EE_soll_Power = 4;
    }
    if(EE_soll_Power < 1){
        EE_soll_Power = 1;
    }
    if(EE_solltemperatur > 45){
        EE_solltemperatur = 35;
    }
    if(EE_AutoOff > Auto_off_15_min){
        EE_AutoOff = Auto_off_15_min;
    }
}


uint16_t calc_tip_temperatur(uint16_t adc_value){
    // ADC-Wert ist 12 Bit lang -> 0...4095
    // mit Referenzspannugn 2.048V (FVR) 500 µV pro Bit
    // Temperaturmessung: bei 450 Grad sind 7mV messbar
    // bei 7mV soll der ADC-Wert 3600 sein -> ADC-Wert / 8 ergibt Temperatur
    // -> 7mV am OP Eingang sollen 1,950 Volt am OP-Ausgang ergeben
    // Verstärkungsfaktor soll 279 sein.-> 33kOhm und 120 Ohm
    uint16_t calcValue = adc_value;
    return ((calcValue >> 3));
}
uint16_t calc_supply_voltage(uint16_t adc_value){
    // Messung soll bis 30V gehen (30/4095 = 7,33mV je Bit)
    // 30,0V -> 300 als Ergebnis (2400 / 8)
    // bei 30V sollen 1,2V am ADC anliegen
    // 56kOhm zu 2,2 kOhm -> Messfehler 1,8%
    
    //bei 19,6V werden 18,3V angezeigt
    // -> 
    return (adc_value >> 3);
}

#define sw1_short   0x01
#define sw1_long    0x10
#define sw2_short   0x02
#define sw2_long    0x20
#define sw1_u_sw2   0x04



/*            SW1                              SW2
            +++++++++                       +++++++++
 *          +       +    **************     +       +
 *          +   o   +    **************     +   o   +
 *          +       +    **************     +       +
 *          +++++++++                       +++++++++
 
 *          
 *          Menü ON   LP                    ON SP 
 *          Menü Skip LP                    OFF LP
 *          Temperatur -                  Temperatur +  
 * 
 *  Im Menü:
 *  - Solltemperatur gespeichert im EEPROM
 *  - Max. Strom     gespeichert im EEPROM
 * 
 * 
 * 
 *  OFF 
 * 
 */

unsigned char get_switch_state(void){
    // wird alle 2ms aufgerufen
    static uint8_t sw1, sw2, sw1_alt, sw2_alt;
    static uint8_t sw1_cnt, sw2_cnt;
    static uint8_t sw1_long_done, sw2_long_done;
    static uint8_t counter_switch;
    static uint8_t init_switch;
    uint8_t switch_state = 0;
    
    sw1 = IN_Switch1_GetValue();
    sw2 = IN_Switch2_GetValue();
    counter_switch ++;
    if(counter_switch >= 50){
        counter_switch = 0;
        // alle 100 ms
        init_switch = 1;
        
        if(sw1 == 0)sw1_cnt ++; else sw1_cnt = 0;
        if(sw2 == 0)sw2_cnt ++; else sw2_cnt = 0;
        
        if((sw1_cnt >= 10)&&(sw1_long_done == 0)){ switch_state = sw1_long; sw1_long_done = 1;} // longpress nach 1s
        if((sw2_cnt >= 10)&&(sw2_long_done == 0)){ switch_state = sw2_long; sw2_long_done = 1;} // longpress nach 1s
    }
    if((sw1==1)&&(sw1_alt==0)){
        if(sw1_long_done == 1){
            sw1_long_done = 0;
        }
        else{
            switch_state = sw1_short;
        }
    }
    if((sw2==1)&&(sw2_alt==0)){
        if(sw2_long_done == 1)
        sw2_long_done = 0;
        else
        switch_state = sw2_short;
    }
    
    sw1_alt = sw1;
    sw2_alt = sw2;
    if(init_switch) return switch_state;
    else return 0;
}

void proc_off(void){
    uint8_t switch_state = get_switch_state();
    static uint16_t counter_display_2ms;
    counter_display_2ms ++;
    
//    switch_state = get_switch_state();
    if(switch_state == sw1_long){        
        // Enter Menü
        mode = mode_menue;
        counter_display_2ms = 0;
    }
    else if(switch_state == sw2_short){        
        mode = mode_work;
        counter_display_2ms = 0;
    }
    else if(switch_state == sw2_long){        
        mode = mode_work;
        counter_display_2ms = 0;
    }
     if(counter_display_2ms >= 500){  
            counter_display_2ms = 0;
            fb_clear();
            fb_draw_char_super_big(0, 1, BIG_CHAR_SETUP); // Setup-Symbol links
            fb_draw_char_super_big(40, 1, BIG_CHAR_O); // 'O'
            fb_draw_char_super_big(55, 1, BIG_CHAR_F); // 'F'
            fb_draw_char_super_big(70, 1, BIG_CHAR_F); // 'F'
            fb_draw_char_super_big(112, 1, BIG_CHAR_ON_OFF); // ON-OFF-Symbol rechts            
            fb_show();
        }
}

void proc_menue(void){
    static uint8_t menue_state;    
    uint8_t switch_state = get_switch_state();
//    switch_state = get_switch_state();
    if(switch_state == sw2_long){        
        // Exit Menü
        fb_clear();
        fb_draw_string_big(20, 1, "CANCEL");
        fb_show();
        menue_state = 0;
        mode = mode_off;
    }
    else{
         switch(menue_state){
            case 0:
                fb_clear();
                fb_draw_string_big( 20, 0, "SETUP");
                sprintf(text_out,"T:%3dC", (EE_solltemperatur * 10));
                fb_draw_string_big( 20, 2, text_out);
                fb_draw_char_super_big(0, 1, BIG_CHAR_FORWARD); // Forward
                fb_draw_char_super_big(104, 1, BIG_CHAR_CANCEL); // Cancel
                fb_show();
                menue_state = 1;
                break;
            case 1: // Einstellung Solltemperatur
                    if(switch_state == sw1_long){
                        // Einstellwert 2 auf Display anzeigen
                        fb_clear();
                        fb_draw_string_big( 20, 0, "SETUP");
                        sprintf(text_out,"P: %dW", EE_soll_Power*10);
                        fb_draw_string_big( 20, 2, text_out);
                        fb_draw_char_super_big(0, 1, BIG_CHAR_SAVE); // Save
                        fb_draw_char_super_big(104, 1, BIG_CHAR_CANCEL); // Cancel
                        fb_show();
                        menue_state = 2;
                    }
                    else if(switch_state == sw1_short){
                        if(EE_solltemperatur > 15){
                            EE_solltemperatur --;
                            sprintf(text_out,"T:%3dC", (EE_solltemperatur * 10));
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                    else if(switch_state == sw2_short){
                        if(EE_solltemperatur < 43){
                            EE_solltemperatur ++;
                            sprintf(text_out,"T:%3dC", (EE_solltemperatur * 10));
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                break;
            case 2: // Einstellung max. Strom
                    if(switch_state == sw1_long){
                        // Setup Auto off time
                        fb_clear();
                        if(EE_AutoOff == Auto_off_disabled){sprintf(text_out,"off: never");}
                        else if(EE_AutoOff == Auto_off_5_min){sprintf(text_out,"off: 5 min");}
                        else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                        else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                        else {sprintf(text_out,"off: 30 min");}
                        fb_draw_string_big(20, 1, text_out);
                        fb_show();
                        menue_state = 3;
                        mode = mode_off;
                    }
                    else if(switch_state == sw1_short){
                        if(EE_soll_Power > 1){
                            EE_soll_Power --;
                            sprintf(text_out,"P: %dW", EE_soll_Power*10);
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                    else if(switch_state == sw2_short){
                        if(EE_soll_Power < 4){
                            EE_soll_Power ++;
                            sprintf(text_out,"P: %dW", EE_soll_Power*10);
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                break;                
            case 3: // Einstellung max. Strom
                    if(switch_state == sw1_long){
                        // Werte im EEPROM speichern und Menü verlassen zu letztem Status (Aus oder Löten)
                        DATAEE_WriteByte(0x00, EE_soll_Power);                   
                        DATAEE_WriteByte(0x01, EE_solltemperatur);               
                        DATAEE_WriteByte(0x02, EE_AutoOff);
                        fb_clear();
                        fb_draw_string_big(20, 1, "SAVE");
                        fb_show();
                        menue_state = 0;
                        mode = mode_off;
                        // Anzeige "SAVE"
                    }
                    else if(switch_state == sw1_short){
                        if(EE_AutoOff > Auto_off_disabled){
                            EE_AutoOff --;
                            if(EE_AutoOff == Auto_off_disabled){sprintf(text_out,"off: never");}
                            else if(EE_AutoOff == Auto_off_5_min){sprintf(text_out,"off: 5 min");}
                            else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                            else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                            else {sprintf(text_out,"off: 30 min");}
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                    else if(switch_state == sw2_short){
                        if(EE_AutoOff < Auto_off_15_min){
                            EE_AutoOff ++;
                            if(EE_AutoOff == Auto_off_disabled){sprintf(text_out,"off: never");}
                            else if(EE_AutoOff == Auto_off_5_min){sprintf(text_out,"off: 5 min");}
                            else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                            else if(EE_AutoOff == Auto_off_10_min){sprintf(text_out,"off: 10 min");}
                            else {sprintf(text_out,"off: 30 min");}
                            fb_draw_string_big( 20, 2, text_out);
                            fb_show();
                            // Wert auf Display aktualisieren
                        }
                    }
                break;
            default:
                menue_state = 0;
        }
    }
   
}

uint8_t nh, nz, ne;
uint16_t Temperatur_Anzeige;
uint16_t display_pulses_per_minute;
uint8_t counter2ms_blink;


void proc_solder(void){
    static uint8_t counter2ms_solder;

#ifdef TEST_POWER_MODULE    
    if((IN_Switch1_GetValue()==0)&&(IN_Switch2_GetValue()==0)){
        TIP_SUPPLY_EN_SetDigitalOutput();
        TIP_SUPPLY_EN_SetHigh();
        TIP_PS1_SetLow();
        TIP_PS1_SetDigitalOutput();
        TIP_PS2_SetLow();
        TIP_PS2_SetDigitalOutput();
    }
    else if(IN_Switch1_GetValue()==0){
        TIP_SUPPLY_EN_SetDigitalOutput();
        TIP_SUPPLY_EN_SetHigh();
        TIP_PS1_SetLow();
        TIP_PS1_SetDigitalOutput();
        TIP_PS2_SetLow();
        TIP_PS2_SetDigitalInput();
    }
    else if(IN_Switch2_GetValue()==0){
        TIP_SUPPLY_EN_SetDigitalOutput();
        TIP_SUPPLY_EN_SetHigh();
        TIP_PS1_SetLow();
        TIP_PS1_SetDigitalInput();
        TIP_PS2_SetLow();
        TIP_PS2_SetDigitalOutput();
    }
    else{
        TIP_SUPPLY_EN_SetDigitalOutput();
        TIP_SUPPLY_EN_SetLow();
        TIP_PS1_SetLow();
        TIP_PS1_SetDigitalInput();
        TIP_PS2_SetLow();
        TIP_PS2_SetDigitalInput();
    }
#else
    // <editor-fold defaultstate="collapsed" desc="Schalter verarbeiten">

    uint8_t switch_State = get_switch_state();
    if (switch_State == sw1_short) {
        if (EE_solltemperatur > 15)
            EE_solltemperatur--;
    }
    if (switch_State == sw1_long) {
        if (solder_display_mode != solder_display_dev) {
            solder_display_mode = solder_display_dev;
        } else {
            solder_display_mode = solder_display_normal;
        }
    }
    if (switch_State == sw2_short) {
        if (EE_solltemperatur < 45)
            EE_solltemperatur++;
    }
    if (switch_State == sw2_long) {
        mode = mode_off;
    }// </editor-fold>

    TEMP_SOLL = EE_solltemperatur * 10;
    
    counter2ms_solder ++;
    if(counter2ms_solder==3){ // 4ms nach dem Abschalten den ADC starten
        ADC_StartConversion(AN2_Temp_Tip);
    }
    if(counter2ms_solder==4){
        // <editor-fold defaultstate="collapsed" desc="Temperatur berechnen und Leistung einstellen">

        Temperatur_TIP = calc_tip_temperatur(AN_IN_Temp);
        Temp_Anz_Filter[Temp_Anz_pos++]= Temperatur_TIP;
        if(Temp_Anz_pos >= 8){
            Temp_Anz_pos = 0;
        }
        Temperatur_Anzeige = 0;
        for(x=0;x<8;x++){
            Temperatur_Anzeige += Temp_Anz_Filter[x];
        }
        Temperatur_Anzeige = Temperatur_TIP;//(Temperatur_Anzeige>>3);
        
        switch (EE_soll_Power) {
            case 1: // 10 Watt
                TIP_PS1_SetLow();
                TIP_PS1_SetDigitalInput();
                TIP_PS2_SetLow();
                TIP_PS2_SetDigitalInput();
                break;
            case 2:
                TIP_PS1_SetLow();
                TIP_PS1_SetDigitalInput();
                TIP_PS2_SetLow();
                TIP_PS2_SetDigitalOutput();
                break;
            case 3:
                TIP_PS1_SetLow();
                TIP_PS1_SetDigitalOutput();
                TIP_PS2_SetLow();
                TIP_PS2_SetDigitalInput();
                break;
            case 4:
                TIP_PS1_SetLow();
                TIP_PS1_SetDigitalOutput();
                TIP_PS2_SetLow();
                TIP_PS2_SetDigitalOutput();
                break;
            default:
                TIP_PS1_SetLow();
                TIP_PS1_SetDigitalInput();
                TIP_PS2_SetLow();
                TIP_PS2_SetDigitalInput();
                break;
        }
        // Wenn die Temperatur zu klein ist heizen
        if (Temperatur_TIP < TEMP_SOLL) {
            loads_per_minute ++;
            TIP_SUPPLY_EN_SetHigh();
        }
        else {
            TIP_SUPPLY_EN_SetLow();
        }
        time_counter ++;
        // </editor-fold>
    }
    
    if(counter2ms_solder >= 100){ // alle 200ms messen und das Display aktualisieren
        counter2ms_solder = 0;
        counter_200ms ++;
        if(counter_200ms >= 300){
            counter_200ms = 0;
            counter_minutes ++;
            switch(EE_AutoOff){
                case Auto_off_disabled:
                    counter_minutes = 0;
                    break;
                case Auto_off_5_min:
                    if(counter_minutes >= 5){
                        mode = mode_off;
                        counter_minutes = 0;
                    }
                    break;
                case Auto_off_10_min:
                    if(counter_minutes >= 10){
                        mode = mode_off;
                        counter_minutes = 0;
                    }
                    break;
                case Auto_off_15_min:
                    if(counter_minutes >= 15){
                        mode = mode_off;
                        counter_minutes = 0;
                    }
                    break;
                default:
                    if(counter_minutes >= 30){
                        mode = mode_off;
                        counter_minutes = 0;
                    }
                    break;
            }
        }
        counter2ms_blink ++;
        TIP_SUPPLY_EN_SetLow(); // Ausgang abschalten damit dann die Temperatur gemessen werden kann
        U_Supply = calc_supply_voltage(AN_IN_U_Supply);
//        solder_display_mode = solder_display_dev;
        if(solder_display_mode == solder_display_dev){
            // <editor-fold defaultstate="collapsed" desc="Display Output developer-edition">
                // Anzeige der Relevanten Daten auf dem Display
                fb_clear();
                if(time_counter >= 5*10){ // 5 pro Sekunde
                    display_pulses_per_minute = loads_per_minute;
                    time_counter = 0;
                    loads_per_minute = 0;
                            
                }
                // Pulse pro Zeiteinheit                
//                sprintf(text_out, "%3d", display_pulses_per_minute);
//                fb_draw_string_big(0, 2, text_out);
                //gemessene Versorgungsspannung
                sprintf(text_out, "%2d.%dV", (U_Supply/10), U_Supply%10);
                fb_draw_string_big(0, 0, text_out);
                // eingestellte Maximalleistung
                sprintf(text_out, "%2dW", EE_soll_Power*10);
                fb_draw_string_big(64, 0, text_out);
                
                
                // Ist-Temperatur
                if(Temperatur_TIP < 500){
                    sprintf(text_out, "%3dC", Temperatur_TIP);
                }
                else{
                    sprintf(text_out, "TIP!");
                }
                fb_draw_string_big(64, 2, text_out);

                fb_show(); // </editor-fold>
        }
        else if(solder_display_mode == solder_display_normal){
            // <editor-fold defaultstate="collapsed" desc="Display Output normal">
            // Anzeige der Relevanten Daten auf dem Display
            fb_clear();
            
            if (Temperatur_TIP > 490) {
                fb_draw_char_super_big(0, 1, BIG_CHAR_DOWN);
                fb_draw_char_super_big(50, 1, BIG_CHAR_T); // 'T'
                fb_draw_char_super_big(65, 1, BIG_CHAR_I); // 'I'
                fb_draw_char_super_big(80, 1, BIG_CHAR_P); // 'P'
                fb_draw_char_super_big(112, 1, BIG_CHAR_UP);
            } 
            else {
                if (counter2ms_blink >= 15) {
                    counter2ms_blink = 0;
                }
                if (Temperatur_Anzeige < (TEMP_SOLL - 30)) {
//                    Temperatur_Anzeige = Temperatur_TIP;
                    if (counter2ms_blink < 5) {
                        fb_draw_char_super_big(20, 1, BIG_CHAR_HEATING);
                    }
                }
                else{                
                    Temperatur_Anzeige = TEMP_SOLL;
                }
                nh = Temperatur_Anzeige / 100;
                nz = (Temperatur_Anzeige % 100) / 10;
                ne = Temperatur_Anzeige % 10;
                fb_draw_char_super_big(0, 1, BIG_CHAR_DOWN); 
                if (nh > 0) {
                    fb_draw_char_super_big(40, 1, nh); 
                    fb_draw_char_super_big(55, 1, nz);
                    fb_draw_char_super_big(70, 1, ne);
                } else {
                    if (nz > 0) {
                        fb_draw_char_super_big(55, 1, nz);
                        fb_draw_char_super_big(70, 1, ne);
                    } else {
                        fb_draw_char_super_big(70, 1, ne);
                    }
                }
                fb_draw_char_big(87, 1, '?'); // '°C'
                fb_draw_char_super_big(112, 1, BIG_CHAR_UP); 
            }
            if (EE_solltemperatur > 15) {
                sprintf(text_out, "%3d", (EE_solltemperatur - 1)*10);
                fb_draw_string(0, 0, text_out);
            }
            sprintf(text_out, "%2dW/%2d,%1dV", EE_soll_Power * 10, U_Supply/10, U_Supply%10);
            fb_draw_string(40, 0, text_out);

            if (EE_solltemperatur < 45) {
                sprintf(text_out, "%3d", (EE_solltemperatur + 1)*10);
                fb_draw_string(108, 0, text_out);
            }

            fb_show(); // </editor-fold>
        }
    }
#endif
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    init_system();
    TMR1_SetInterruptHandler(&timer1_fired);
    
    TMR1_StartTimer();
    TIP_SUPPLY_EN_SetDigitalOutput();
    
#ifdef TEST_POWER_MODULE
    mode = mode_work;
#else
      fb_show();
    __delay_ms(2000); // Delay nach einblenden Start-Screen //
#endif
  
    while (1)
    {        
        // Aufruf der Routine alle 2ms
        if(tmr_2ms != tmr1_msg){
            tmr_2ms ++; 
            
            switch (mode){
                case mode_startup: // warten bis Taster betätigt wurde
                    if(get_switch_state()){
                        mode = mode_off;
                    }
                    mode = mode_off;
                    break;
                case mode_off: // AUS-Zustand
                    TIP_SUPPLY_EN_SetLow();
                    proc_off();
                    break;                
                case mode_work: // normaler Betrieb
                    proc_solder();
                    break;                
                case mode_menue: // Setup-Mode
                    TIP_SUPPLY_EN_SetLow();
                    proc_menue();
                    break;
                default:
                    mode = 0;
                    break;
            }
        }    
    }
}