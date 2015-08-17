/*
#include "../lib/stm32f0xx.h"
#include "lcd3310.h"
#include "f8x6fv.h"
#include "../delay/delay.h"
#include "../gpio/gpio.h"

#define  ADDR_SPI_DR_8B  (( uint32_t )SPI1 + 0x0C )

uint8_t lcdRAM[84][6];

static void __reverse( char * begin, char * end );
static char * itoa( int value, char* buffer, int base );

void lcd3310_write( uint8_t dane )
{
    CS_0;
	while( !( SPI1->SR & SPI_SR_TXE ));
	*( volatile uint8_t * ) ( ADDR_SPI_DR_8B ) = dane;
	while( SPI1->SR & SPI_SR_BSY );
	CS_1;
}

void lcd3310_data_buffer( uint8_t * data, uint16_t len )
{
    DC_1;
	while( len-- )
        lcd3310_write( *data++ );
}

void lcd3310_data( uint8_t data )
{
    DC_1;
    lcd3310_write( data );
}

void lcd3310_command( uint8_t cmd )
{
    DC_0;
	lcd3310_write( cmd );
}

void lcd3310_set_address( uint8_t x, uint8_t y )
{
     DC_0;
	 lcd3310_command( y | 0x40 );
	 lcd3310_command( x | 0x80 );
}

void lcd3310_clear( void )
{
    uint8_t i, j;

	for( j = 0; j < 6; j++ )
		for( i = 0; i < 84; i++ )
				lcdRAM[i][j] = 0x00;
			
    DC_1;
	lcd3310_data_buffer( *lcdRAM, 504 );
}

void lcd3310_init( void )
{ 
    // clock spi1 and gpioa
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	gpioa_init();

	// gpioa as af
	gpio_pin_cfg( GPIOA, 5, GPIO_AF0_PP_50MHz ); // sck
	gpio_pin_cfg( GPIOA, 6, GPIO_AF0_PP_50MHz ); // miso
	gpio_pin_cfg( GPIOA, 7, GPIO_AF0_PP_50MHz ); // mosi

	gpio_pin_cfg( GPIOA, 1, GPIO_OUT_PP_50MHz ); // d/c
	gpio_pin_cfg( GPIOA, 2, GPIO_OUT_PP_50MHz ); // res
	gpio_pin_cfg( GPIOA, 3, GPIO_OUT_PP_50MHz ); // sce

	// D/C, RES, SCE = 1
	DC_1;
	RST_1;
	CS_1;

	// init spi1
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
	delay_ms( 2 );
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
	SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_1 | SPI_CR1_BR_0;
	SPI1->CR2 |= SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
    SPI1->CR1 |= SPI_CR1_SPE;

	delay_ms( 10 );
	RST_0;
	delay_ms( 1 );
	RST_1;
	delay_ms( 1 );

	lcd3310_command( 0x21 );     //H=1
	lcd3310_command( 0xC8 );     //Vop setting
	lcd3310_command( 0x06 );     //set temp.
	lcd3310_command( 0x13 );     //wspólczynnik multipleksowania
	lcd3310_command( 0x20 );     //h=0 <- standardowe ustawnia
	lcd3310_command( 0x0C );     //tryb normlany
	lcd3310_command( 0x40 );     //set x-address of RAM
	lcd3310_command( 0x80 );     //set y-address of RAM

    delay_ms( 10 );
    lcd3310_clear();
}

void lcd3310_char( char znak, uint8_t x, uint8_t y )
{
    uint8_t i;
    uint8_t temp[6];

    for( i = 0; i < 6; i++ )
    	temp[i] = f8x6fv[ ( uint8_t ) znak ][i];

	lcd3310_set_address( x, y );

	delay_ms( 5 );
	lcd3310_data_buffer( ( uint8_t * ) temp, 6 );
}

void lcd3310_string( char * str, uint8_t x, uint8_t y )
{
     while( *str )
     {
    	 lcd3310_char( *str++, x, y );
    	 x+=6;
     }
}

void lcd3310_value_integer( int32_t liczba, uint8_t x, uint8_t y )
{
    char buffer[10];
	itoa( liczba, buffer, 10 );
	lcd3310_string( buffer, x, y );
}

void lcd3310_value_float( float liczba, uint8_t x, uint8_t y )
{
	char przed[5];
	char po[5];
	uint8_t a = 0, b = 0;
	a = ( int ) liczba;
	b = ( int )( liczba * 100 ) % 100;
	itoa( a, przed, 10 );
	itoa( b, po, 10 );

    lcd3310_string( przed, x, y );

    if( a > 9 )
    {
        lcd3310_string( ".", x + 12, y );
        lcd3310_string( po, x + 18, y );
    }
    else
    {
    	lcd3310_string( ".", x + 6, y );
    	lcd3310_string( po, x + 12, y );
    }
}

void lcd3310_set_pixel( uint8_t x, uint8_t y )
{
    uint8_t dy, offset;

	if( !(( x > 84 ) & ( y > 48 )))
	{
	    dy = y / 8;
	    offset = y % 8;
	    lcd3310_set_address( x, dy );
	    lcd3310_data( 1 << offset );
	}
}

static char* itoa(int value, char* buffer, int base)
{
	static const char digits[]="0123456789abcdef";

	char* buffer_copy=buffer;
	int32_t sign=0;
	int32_t quot,rem;

	if ((base>=2)&&(base<=16))				// is the base valid?
	{
		if (base == 10 && (sign = value) < 0)// negative value and base == 10? store the copy (sign)
		value = -value;					// make it positive

		do
		{
			quot=value/base;				// calculate quotient and remainder
			rem=value%base;
			*buffer++ = digits[rem];		// append the remainder to the string
		} while ((value=quot));				// loop while there is something to convert

		if (sign<0)							// was the value negative?
			*buffer++='-';					// append the sign

		__reverse(buffer_copy,buffer-1);		// reverse the string
	}


	*buffer='\0';
	return buffer_copy;
}

static void __reverse( char * begin, char * end )
{
	char temp;

	while( end > begin )
	{
		temp = * end;
		*end-- =* begin;
		*begin++ = temp;
	}
}
*/
