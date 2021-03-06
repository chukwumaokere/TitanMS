 /*
	This file is part of TitanMS.
	Copyright (C) 2008 koolk

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "MapleEncryption.h"

unsigned char values[256] = {0xEC, 0x3F, 0x77, 0xA4, 0x45, 0xD0, 0x71, 0xBF, 0xB7, 0x98, 0x20, 0xFC,
	0x4B, 0xE9, 0xB3, 0xE1, 0x5C, 0x22, 0xF7, 0x0C,	0x44, 0x1B, 0x81, 0xBD, 0x63, 0x8D, 0xD4, 0xC3,
	0xF2, 0x10, 0x19, 0xE0, 0xFB, 0xA1, 0x6E, 0x66,	0xEA, 0xAE, 0xD6, 0xCE, 0x06, 0x18, 0x4E, 0xEB,
	0x78, 0x95, 0xDB, 0xBA, 0xB6, 0x42, 0x7A, 0x2A, 0x83, 0x0B, 0x54, 0x67, 0x6D, 0xE8, 0x65, 0xE7,
	0x2F, 0x07, 0xF3, 0xAA, 0x27, 0x7B, 0x85, 0xB0,	0x26, 0xFD, 0x8B, 0xA9, 0xFA, 0xBE, 0xA8, 0xD7,
	0xCB, 0xCC, 0x92, 0xDA, 0xF9, 0x93, 0x60, 0x2D,	0xDD, 0xD2, 0xA2, 0x9B, 0x39, 0x5F, 0x82, 0x21,
	0x4C, 0x69, 0xF8, 0x31, 0x87, 0xEE, 0x8E, 0xAD, 0x8C, 0x6A, 0xBC, 0xB5, 0x6B, 0x59, 0x13, 0xF1,
	0x04, 0x00, 0xF6, 0x5A, 0x35, 0x79, 0x48, 0x8F,	0x15, 0xCD, 0x97, 0x57, 0x12, 0x3E, 0x37, 0xFF,
	0x9D, 0x4F, 0x51, 0xF5, 0xA3, 0x70, 0xBB, 0x14,	0x75, 0xC2, 0xB8, 0x72, 0xC0, 0xED, 0x7D, 0x68,
	0xC9, 0x2E, 0x0D, 0x62, 0x46, 0x17, 0x11, 0x4D,	0x6C, 0xC4, 0x7E, 0x53, 0xC1, 0x25, 0xC7, 0x9A,
	0x1C, 0x88, 0x58, 0x2C, 0x89, 0xDC, 0x02, 0x64,	0x40, 0x01, 0x5D, 0x38, 0xA5, 0xE2, 0xAF, 0x55,
	0xD5, 0xEF, 0x1A, 0x7C, 0xA7, 0x5B, 0xA6, 0x6F,	0x86, 0x9F, 0x73, 0xE6, 0x0A, 0xDE, 0x2B, 0x99,
	0x4A, 0x47, 0x9C, 0xDF, 0x09, 0x76, 0x9E, 0x30,	0x0E, 0xE4, 0xB2, 0x94, 0xA0, 0x3B, 0x34, 0x1D,
	0x28, 0x0F, 0x36, 0xE3, 0x23, 0xB4, 0x03, 0xD8, 0x90, 0xC8, 0x3C, 0xFE, 0x5E, 0x32, 0x24, 0x50,
	0x1F, 0x3A, 0x43, 0x8A, 0x96, 0x41, 0x74, 0xAC,	0x52, 0x33, 0xF0, 0xD9, 0x29, 0x80, 0xB1, 0x16,
	0xD3, 0xAB, 0x91, 0xB9, 0x84, 0x7F, 0x61, 0x1E,	0xCF, 0xC5, 0xD1, 0x56, 0x3D, 0xCA, 0xF4, 0x05,
	0xC6, 0xE5, 0x08, 0x49};

void MapleEncryption::nextIV(unsigned char* vector){
	unsigned char x[4] = {0xF2, 0x53, 0x50, 0xC6};
	for(int i=0; i<4; i++){
		unsigned char a = x[1];
		unsigned char b =  a;
		b = values[b];
		b -= vector[i];
		x[0] += b;
		b = x[2];
		b = b ^ values[vector[i]];
		a -= b;
		x[1] = a;
		a = x[3];
		b = a;
		a -= x[0];
		b = values[b];
		b += vector[i];
		b = b ^ x[2];
		x[2] = b;
		a += values[vector[i]];
		x[3] = a;
		unsigned int c, d;
		for(int j=0; j<4; j++){
			c = x[0] + x[1]*0x100 + x[2]*0x100*0x100 + x[3]*0x100*0x100*0x100;
			d = c;
		}
		c = c >> 0x1D;
		d = d << 0x03;
		c = c | d;
		x[0] = c%0x100;
		c = c / 0x100;
		x[1] = c%0x100;
		c = c / 0x100;
		x[2] = c%0x100;
		x[3] = c / 0x100;
	}
	for(int i=0; i<4; i++)
		vector[i] = x[i];
}
#define WORD_LEN(w) (8*sizeof(w))
int WORD_LENGTH = WORD_LEN(unsigned char);
unsigned char MapleEncryption::rol(unsigned char val, int num) {
	return (val<<num)|(val>>(WORD_LENGTH-num));
}
unsigned char MapleEncryption::ror(unsigned char val, int num) {
	return (val>>num)|(val<<(WORD_LENGTH-num));
}

void MapleEncryption::mapleEncrypt(unsigned char* buf, int size){
	int i,j,a;
	unsigned char c, k;
	for(i=0; i<3; i++){
		a=0;
		for(j=size; j>0; j--){
			c = buf[size - j];
			c = rol (c, 3);
			c += j;
			c ^= a;
			a = c;
			for(k=0; k<j%8; k++)
				__asm ror c, 1
			c ^= 0xFF;
			c += 0x48;
			buf[size - j] = c;
		}

		a=0;
		for(j=size; j>0; j--){
			c = buf[j - 1];
			__asm rol c, 4
			c += j;
			c ^= a;
			a = c;
			c ^= 0x13;
			__asm ror c, 3
			buf[j - 1] = c;
		}
	}
}


void MapleEncryption::mapleDecrypt(unsigned char* buf, int size){
	int i,j,a,b;
	unsigned char c, k;
	for(i=0; i<3; i++){
		a=0;
		b=0;
		for(j=size; j>0; j--){
			c = buf[j - 1];
			__asm rol c, 3
			c ^= 0x13;
			a = c;
			c ^= b;
			c -= j;
			__asm ror c, 4
			b = a;
			buf[j - 1] = c;
		}

		a=0;
		b=0;
		for(j=size; j>0; j--){
			c = buf[size - j];
			c -= 0x48;
			c ^= 0xFF;
			for(k=0; k<j%8; k++)
				__asm rol c, 1
			a = c;
			c ^= b;
			c -= j;
			__asm ror c, 3
			b = a;
			buf[size - j] = c;
		}
	}
}