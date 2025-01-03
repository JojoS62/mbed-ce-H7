#ifndef __FONTS_H
#define __FONTS_H

#include <stdint.h>


typedef struct _pFont
{    
	const uint8_t 		*pTable;
	uint16_t 			Width;
	uint16_t 			Height;
	uint16_t 			Sizes;
	uint16_t			Table_Rows;
} pFONT;

/*------------------------------------ �������� ---------------------------------------------*/

extern	pFONT	CH_Font12;
extern	pFONT	CH_Font16;
extern	pFONT	CH_Font20;
extern	pFONT	CH_Font24;
extern	pFONT	CH_Font32;

/*------------------------------------ ASCII���� ---------------------------------------------*/

extern pFONT Font32;
extern pFONT Font24;
extern pFONT Font20;
extern pFONT Font16;
extern pFONT Font12;

#endif 
 
