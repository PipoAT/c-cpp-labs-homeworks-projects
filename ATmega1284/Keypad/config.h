/**
 * \file config.h
 * \author Tim Robbins
 * \brief The mcu_utils configuration file for mcu_lib and system definitions.
 */
#ifndef CONFIG_H_
#define CONFIG_H_   1



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__XC)


///The frequency being used for the controller
#define _XTAL_FREQ                                  64000000

#else

///The frequency being used for the controller
#define F_CPU                                       12000000UL

#endif


///The baud rate for serial communications
#define BAUD										1200



#define KP_COLUMN_PORT PORTA // defined what ports the inputs and outputs are
#define KP_COLUMN_READ PINA
#define KP_COLUMN_DIR DDRA
#define KP_ROW_PORT PORTA
#define KP_ROW_READ PINA
#define KP_ROW_DIR DDRA
#define KP_COLUMNS 3 // defined the size of the pad rows by columns
#define KP_ROWS 4




#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif

