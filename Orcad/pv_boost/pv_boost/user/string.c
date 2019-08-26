#include "types.h"


void hex2dec(BYTE *ptr,WORD wVal,BYTE uPos,BYTE bFrac)
{
	BYTE uRem;

    //leading zero removal
	bFrac |= 0x80;

	while (uPos>0)
	{
		uRem=wVal%10;
		wVal=wVal/10;
		uPos--;
        
        *(ptr+uPos)=uRem+0x30;
        
        //comma display		
        bFrac &=0x7F;
        if (bFrac)
        {
	        if (bFrac == 1)
	        {
		        uPos--;
				*(ptr+uPos)=',';
				bFrac = 0x80;
		    }
		    else
		    {
			    bFrac--;
			}  
	    } 
        
        if ((0==wVal) && (0==bFrac))
        {
             uPos = 0;
        }
	}
}

//  hex2text ===========================================
//
void hex2text(BYTE *ptr,WORD wVal)
{
	BYTE uRem;
	BYTE uPos = 4;

	while (uPos>0)
	{
		uRem=wVal & 0x0F ;
		wVal=wVal >> 4;
		uPos--;
        
        if (uRem>9)
        {
	        uRem +=0x37;
	    }
	    else
	    {
		    uRem +=0x30;
		}  
        
        *(ptr+uPos)=uRem;
	}
}

void hex2text_b(BYTE *ptr,byte bVal)
{
	BYTE uRem;
	BYTE uPos = 2;

	while (uPos>0)
	{
		uRem=bVal & 0x0F ;
		bVal=bVal >> 4;
		uPos--;
        
        if (uRem>9)
        {
	        uRem +=0x37;
	    }
	    else
	    {
		    uRem +=0x30;
		}  
        
        *(ptr+uPos)=uRem;
	}
}