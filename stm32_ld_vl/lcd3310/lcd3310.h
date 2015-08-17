#ifndef LCD3310_H__
#define LCD3310_H__

#include "../gpio/gpio.h"

#define DC_0    gpio_reset_pin( GPIOA, 1 )
#define DC_1	gpio_set_pin( GPIOA, 1 )
#define CS_0	gpio_reset_pin( GPIOA, 3 )
#define CS_1	gpio_set_pin( GPIOA, 3 )
#define RST_0	gpio_reset_pin( GPIOA, 2 )
#define RST_1	gpio_set_pin( GPIOA, 2 )

void lcd3310_write( uint8_t dane );
void lcd3310_data_buffer( uint8_t * data, uint16_t len );
void lcd3310_data( uint8_t data );
void lcd3310_command( uint8_t cmd );
void lcd3310_set_address( uint8_t x, uint8_t y );
void lcd3310_clear( void );
void lcd3310_init( void );
void lcd3310_char( char znak, uint8_t x, uint8_t y );
void lcd3310_string( char * str, uint8_t x, uint8_t y );
void lcd3310_value_integer( int32_t liczba, uint8_t x, uint8_t y );
void lcd3310_value_float( float liczba, uint8_t x, uint8_t y );
void lcd3310_set_pixel( uint8_t x, uint8_t y );


#endif
