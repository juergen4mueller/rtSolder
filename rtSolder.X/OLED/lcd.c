

#include <xc.h>
#include <stdint.h>
#include "lcd.h"
#include "i2c1.h"
#include "font.h"

/*******************************************************************************
 * Framebuffer
 */

uint8_t buffer[SSD1306_BUFFERSIZE] = { // Hier kommt der Startup-Screen rein, Speicher wird ja sowieso schon verwendet
/* Screen Solder*/ //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x40, 0x60, 0x60, 0x60, 0x20, 0x30, 0x30, 0x30, 0x10, 0x18, 0x18, 0x18, 0x08, 0x0c, 0x0c, 0x0c, 0x04, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x1c, 0x78, 0xf0, 0xc0, 0x1c, 0xfc, 0xf8, 0xc0, 0x1c, 0x7c, 0xf0, 0x40, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xc8, 0x34, 0x0b, 0xc4, 0x21, 0x50, 0x26, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe3, 0x7f, 0x1e, 0x00, 0x03, 0xc3, 0xe1, 0x30, 0x10, 0x10, 0x10, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x09, 0x0e, 0x1f, 0x64, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x30, 0x30, 0x10, 0x18, 0x18, 0x88, 0x8c, 0xcc, 0xc6, 0xc7, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0x80, 0x00, 0x20, 0x30, 0x30, 0x18, 0x98, 0x98, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x83, 0x07, 0x06, 0x06, 0x8c, 0xfc, 0xf8, 0x00, 0x00, 0x7e, 0xff, 0x81, 0x00, 0x00, 0x00, 0x81, 0xff, 0x7e, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x7e, 0xff, 0x81, 0x00, 0x00, 0x81, 0xc3, 0xff, 0xff, 0x00, 0x00, 0x7e, 0xff, 0x89, 0x08, 0x08, 0x09, 0x8f, 0x8f, 0x00, 0x00, 0xff, 0xff, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x70, 0x30, 0x28, 0x2c, 0x3e, 0x3f, 0x3b, 0x31, 0x31, 0x19, 0x18, 0x18, 0x0c, 0x0c, 0x0c, 0x06, 0x06, 0x02, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x03, 0x03, 0x06, 0x02, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x40, 0x60, 0x60, 0x60, 0x20, 0x30, 0x30, 0x30, 0x10, 0x18, 0x18, 0x18, 0x08, 0x0c, 0x0c, 0x0c, 0x04, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x0c, 0x78, 0xf0, 0xc0, 0x1c, 0xfc, 0xf8, 0xc0, 0x1c, 0x7c, 0x70, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xc8, 0x34, 0x0b, 0xc4, 0x21, 0x50, 0x26, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe3, 0x7f, 0x1e, 0x00, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x09, 0x0e, 0x1f, 0x24, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x30, 0x30, 0x10, 0x18, 0x18, 0x88, 0x8c, 0xcc, 0xc6, 0xc7, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0x80, 0x00, 0x20, 0x30, 0x30, 0x18, 0x98, 0x98, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x04, 0x0e, 0xfc, 0xfe, 0xfe, 0xfe, 0x1e, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0xce, 0xce, 0xee, 0xe6, 0xe0, 0xee, 0xee, 0xce, 0xce, 0x04, 0x60, 0x60, 0xf0, 0xf8, 0xf8, 0xfc, 0xf8, 0x60, 0x60, 0x20, 0xf8, 0xfc, 0xfc, 0xee, 0xce, 0xde, 0x9c, 0x08, 0xc4, 0xec, 0xee, 0xee, 0xe4, 0x00, 0x00, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x80, 0xe0, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x70, 0x30, 0x28, 0x2c, 0x3e, 0x3f, 0x3b, 0x31, 0x31, 0x19, 0x18, 0x18, 0x0c, 0x0c, 0x0c, 0x06, 0x06, 0x02, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x70, 0x70, 0x70, 0x78, 0x3c, 0x08, 0x1f, 0x3f, 0x7f, 0x7f, 0x7c, 0x70, 0x77, 0x3f, 0x3f, 0x1f, 0x0f, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x7f, 0x7f, 0x70, 0x30, 0x10, 0x21, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x21, 0x00, 0x70, 0x7f, 0x7f, 0x7f, 0x7f, 0x70, 0x00, 0x60, 0x70, 0x7d, 0x0f, 0x0f, 0x7f, 0x7f, 0x7f, 0x7f, 0x78, 0x60, 0x00, 0x00
};
/*******************************************************************************
 * Initialisierung des OLED-Displays
 */

void lcd_init(void)
{
    //i2c.init(SSD1306_DEFAULT_ADDRESS);

    // Turn display off
    lcd_sendCommand(SSD1306_DISPLAYOFF);

    lcd_sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
    lcd_sendCommand(0x80);

    lcd_sendCommand(SSD1306_SETMULTIPLEX);
    //lcd_sendCommand(0x3F); // f�r 128x64
    lcd_sendCommand(0x1F); // f�r 128x32
    
    
    lcd_sendCommand(SSD1306_SETDISPLAYOFFSET);
    lcd_sendCommand(0x00);
    
    lcd_sendCommand(SSD1306_SETSTARTLINE | 0x00);
    
    // We use internal charge pump
    lcd_sendCommand(SSD1306_CHARGEPUMP);
    lcd_sendCommand(0x14);
    
    // Horizontal memory mode
    lcd_sendCommand(SSD1306_MEMORYMODE);
    lcd_sendCommand(0x00);
    
    lcd_sendCommand(SSD1306_SEGREMAP | 0x01);

    lcd_sendCommand(SSD1306_COMSCANDEC);

    lcd_sendCommand(SSD1306_SETCOMPINS);
    //lcd_sendCommand(0x12); // f�r 128x64
    lcd_sendCommand(0x02); // f�r 128x32

    // Max contrast
    lcd_sendCommand(SSD1306_SETCONTRAST);
    //lcd_sendCommand(0xCF); // f�r 128x64
    lcd_sendCommand(0x8F); // f�r 128x32

    lcd_sendCommand(SSD1306_SETPRECHARGE);
    lcd_sendCommand(0xF1);

    lcd_sendCommand(SSD1306_SETVCOMDETECT);
    lcd_sendCommand(0x40);

    lcd_sendCommand(SSD1306_DISPLAYALLON_RESUME);

    // Non-inverted display
    lcd_sendCommand(SSD1306_NORMALDISPLAY);

    // Turn display back on
    lcd_sendCommand(SSD1306_DISPLAYON);
}

/*******************************************************************************
 * Übertragen eines Befehls an das OLED-Display
 */

void lcd_sendCommand(uint8_t command)
{
    startI2C();
    sendI2C(SSD1306_DEFAULT_ADDRESS);
    
    sendI2C(0x00);
    sendI2C(command);
    
    stopI2C();
}

/*******************************************************************************
 * Invertierung des OLED-Display
 */

void lcd_invert(uint8_t inverted)
{
    if (inverted)
    {
        lcd_sendCommand(SSD1306_INVERTDISPLAY);
    }
    else
    {
        lcd_sendCommand(SSD1306_NORMALDISPLAY);
    }
}

/*******************************************************************************
 * Übertragen des Framebuffers an das OLED-Display
 */
 
void lcd_sendFramebuffer(uint8_t *buffer)
{
    lcd_sendCommand(SSD1306_COLUMNADDR);
    lcd_sendCommand(0x00);
    lcd_sendCommand(0x7F);

    lcd_sendCommand(SSD1306_PAGEADDR);
    lcd_sendCommand(0x00);
    lcd_sendCommand(0x07);

    // We have to send the buffer as 16 bytes packets
    // Our buffer is 1024 bytes long, 1024/16 = 64
    // We have to send 64 packets
    
    for (uint8_t packet = 0; packet < 32; packet++)
    {
        startI2C();
        sendI2C(SSD1306_DEFAULT_ADDRESS);
        sendI2C(0x40);
        
        for (uint8_t packet_byte = 0; packet_byte < 16; ++packet_byte)
        {
            sendI2C(buffer[packet*16+packet_byte]);
        }
        
        stopI2C();
    }
}


/*******************************************************************************
 * Zeichnen eines Pixels in den Framebuffer an die Position (pos_x|pos_y).
 * Setzten des Pixels mit pixel_status = 1, loeschen mit pixel_status = 0
 */

void fb_drawPixel(uint8_t pos_x, uint8_t pos_y, uint8_t pixel_status)
{
    if (pos_x >= SSD1306_WIDTH || pos_y >= SSD1306_HEIGHT)
    {
        return;
    }

    if (pixel_status)
    {
        buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] |= (1 << (pos_y&7));
    }
    else
    {
        buffer[pos_x+(pos_y/8)*SSD1306_WIDTH] &= ~(1 << (pos_y&7));
    }
}

/*******************************************************************************
 * Zeichnen einer vertikalen Linie in den Framebuffer von (x,y) der Laenge 
 * length.
 */

void fb_drawVLine(uint8_t x, uint8_t y, uint8_t length)
{
    for (uint8_t i = 0; i < length; ++i)
    {
        fb_drawPixel(x, i+y, 1);
    }
}

/*******************************************************************************
 * Zeichnen einer horizontalen Linie in den Framebuffer von (x|y) der Laenge
 * length.
 */

void fb_drawHLine(uint8_t x, uint8_t y, uint8_t length)
{
    for (uint8_t i = 0; i < length; ++i)
    {
        fb_drawPixel(i+x, y, 1);
    }
}

/*******************************************************************************
 * Zeichnen eines Rechtecks in den Framebuffer von (x1|y1) zu (x2|y2).
 * Das Rechteck kann gefuellt werden (1 = fill) oder leer sein (0 = fill).
 */

void fb_drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fill)
{
    uint8_t length = x2 - x1 + 1;
    uint8_t height = y2 - y1;
        
    if (!fill)
    {
        fb_drawHLine(x1, y1, length);
        fb_drawHLine(x1, y2, length);
        fb_drawVLine(x1, y1, height);
        fb_drawVLine(x2, y1, height);
    }
    else
    {
        for (uint8_t x = 0; x < length; ++x)
        {
            for (uint8_t y = 0; y <= height; ++y)
            {
                fb_drawPixel(x1+x, y+y1, 1);
            }
        }
    }
}

/*******************************************************************************
 * Löschen des Framebuffers
 */

void fb_clear(void)
{
    for (uint16_t buffer_location = 0; buffer_location < SSD1306_BUFFERSIZE; buffer_location++)
    {
        buffer[buffer_location] = 0x00;
    }
}

/*******************************************************************************
 * Invertieren des Framebuffers
 */

void fb_invert(uint8_t status)
{
    lcd_invert(status);
}

/*******************************************************************************
 * Darstellen des Framebuffers auf dem OLED-Display
 */

void fb_show(void)
{
    lcd_sendFramebuffer(buffer);
}
//
//void fb_show_bmp(uint8_t *pBmp)
//{
//    lcd_sendFramebuffer(pBmp);
//}

/*******************************************************************************
 * Zeichnen eines Zeichens an Position (x,y) - Diese Funktion kann nur indirekt
 * mit Hilfe der Funktion lcd_draw_string aufgerufen werden, da diese den 
 * entsprechenden Index fuer den font-Vector berechnet!
 */

void fb_draw_char (uint16_t x, uint16_t y, uint16_t fIndex)
{
    uint16_t bufIndex = (y << 7) + x;
    uint8_t j;
    
    for(j=0; j < FONT_WIDTH; j++)
    {
        buffer[bufIndex + j] = font[fIndex + j + 1];
    }
}

void fb_draw_char_big (uint16_t x, uint16_t y, const char fIndex) // 12x16px
{
    uint8_t k;
    for(k=0; k<12; k++)
    {
        buffer[( y    << 7) + x + k] = font2[fIndex - ' '][k*2  ];
        buffer[((y+1) << 7) + x + k] = font2[fIndex - ' '][k*2+1];
    }
}
void fb_draw_char_super_big (uint16_t x_offset_px, uint16_t y_offset_page, uint16_t fIndex){
    uint8_t k;    
    for(k=0; k<15; k++)
    {
        buffer[(y_offset_page << 7) + x_offset_px+k] = font_3[fIndex][k*3]; // das nochmal durchdenken // Buffer 0 startet bei 0
        buffer[((y_offset_page+1) << 7) + x_offset_px+k] = font_3[fIndex][k*3+1];                            // Buffer 1 startet bei 128
        buffer[((y_offset_page+2) << 7) + x_offset_px+k] = font_3[fIndex][k*3+2];                            // Buffer 2 startet bei 256

    }        
}
/*******************************************************************************
 * Zeichnen einer Zeichenkette ab Position (x,y)
 */

void fb_draw_string (uint16_t x, uint16_t y, const char *pS)
{    
    uint16_t lIndex, k;
    
    while(*pS)
    {
        /* index the width information of character <c> */
        lIndex = 0;
        for(k=0; k < (*pS - ' '); k++)
        {
            lIndex += (font[lIndex]) + 1;
        }
        
        /* draw character */
        fb_draw_char(x, y, lIndex);
        
        /* move the cursor forward for the next character */
        x += font[lIndex] + 1;
        
        /* next charachter */
        pS++;
    }
}

void fb_draw_string_big (uint16_t x, uint16_t y, const char *pS) // 12x16px
{
    uint8_t k;

    while(*pS)
    {
        for(k=0; k<12; k++)
        {
            buffer[( y    << 7) + x + k] = font2[*pS - ' '][k*2  ];
            buffer[((y+1) << 7) + x + k] = font2[*pS - ' '][k*2+1];
        }
        
        x += 12;
        
        /* next charachter */
        pS++;
    }    
}
