/*
MIT License

Copyright 2018 Luis Delgado
Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:
The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
*/

#ifndef _UTF8DEC_H
#define _UTF8DEC_H

#include <stdio.h>
#include <string.h>


/*-----------------------------------------------------------------------------
 *  DECL
 *-----------------------------------------------------------------------------*/
int utf8dec(uint8_t * input, uint32_t * output, int SizeofInput);



/*-----------------------------------------------------------------------------
 *  DEFS
 *-----------------------------------------------------------------------------*/
int utf8dec(uint8_t * input, uint32_t * output, int SizeofInput)
{
	int Ret =0;
	uint32_t Mark =0;

	do
	{
		uint8_t * initptr = input+Mark;
		uint8_t tmpbyte=*initptr;
		(*Mark)++;
		uint8_t tmp [4];
		uint8_t ret [4];

		uint8_t pnum = 192;
		uint8_t pnum2 = 32;
		char i;
		for(i = 0;i<3;i++)
		{
			uint8_t r1 = (tmpbyte & /*^*/pnum);
			uint8_t r2 = (tmpbyte & pnum2);
			if((r1  == pnum) && (r2 == 0)) 
			{			
				(*Mark)+=i+1;
				memcpy(tmp,initptr,i+2);
				break;
			}
			
			pnum>>=1;
			pnum|=128;
			pnum2>>=1;
		}
		if(i==3){i=0;}else{i+=1;} 
		*(int*)ret = 0;

		

		if(i==0){ret[0]=tmpbyte;}
		else
		{
			char o = i;
			char clear = 192;
			char clear_3 = clear;
			char cont=2;

			for(i++;--i;) 
			{
				ret[i] = tmp[i] & (~clear);
				clear_3+=(16*(i));
			}
			ret[0] = tmp[0] & (~clear_3);

			i=o; o=0;
			int u = 1;
			

			*(int*)tmp = *(int*)ret;
			*(int*)ret = 0;

			for(;--i;)
			{
				tmp[i+1] |= (tmp[i]<<(6 -(2*(u-1))) );
				tmp[i]>>=2*u;
				ret[o] = tmp[i+1];

				u++;o++;
			}

			i=0;
			tmp[i+1] |= (tmp[i]<<(6 -(2*(u-1))) );
			tmp[i]>>=2*u;
			ret[o] = tmp[i+1];

		}

		output[Ret] = ret; 
		Ret++;

	}while(Mark<SizeofInput);

	return Ret;
}

#endif
