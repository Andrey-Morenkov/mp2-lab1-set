// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
/*#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <conio.h>
using namespace std;*/

TBitField::TBitField(int len)
{
	if (len < 0)
		throw len;
	else
	{
		BitSize = len;
        size = BitSize/(sizeof(TELEM)*8)+1;
        mas = new TELEM[size];
        for (int i = 0; i<size; i++)
      	  mas[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	size = bf.size;
	BitSize = bf.BitSize;
	mas = new TELEM[size];
	for(int i = 0; i<size; i++)
	    mas[i] = bf.mas[i];
}

TBitField::~TBitField() // деструктор
{
  delete []mas;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n // номер ячейки которая int
{
	if ((n < 0) || (n > BitSize))
		throw n;
	else
      return(n / (sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitSize))
		throw n;
	else
	{
		int tmp = n % (sizeof(TELEM)*8);
        TELEM mask  = 1;
        mask=(mask << tmp);
        return (mask);
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return (BitSize);
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0)||(n > BitSize))
		throw n;
	else
	{
		int m = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        mas[m] = (mas[m] | mask);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0)||(n > BitSize))
		throw n;
	else
	{
	   int m = GetMemIndex(n);
	   TELEM mask = GetMemMask(n);
	   mas[m]= (mas[m] & ~mask);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0)||(n > BitSize))
		throw n;
	else
	{
		int m = GetMemIndex(n); // ищем ячейку
        TELEM mask = GetMemMask(n); // маска на эту ячейку
        int result = (mask & mas[m]); 
        if (result == 0)
        	return(0);
        else
        	return(1);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitSize=bf.BitSize;
	size=bf.size;
	mas = new TELEM[size]; //?
	for(int i=0;i<size;i++)
		mas[i]=bf.mas[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitSize != bf.BitSize)
		return 0;
	else
	{
		for (int i = 0;i < BitSize; i++)
			if (GetBit(i) != bf.GetBit(i))
				return 0;
        return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
   if (BitSize != bf.BitSize)
		return 1;
	else
	{
		for (int i = 0;i < BitSize; i++)
			if (GetBit(i) != bf.GetBit(i))
				return 1;
        return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitSize == bf.BitSize)
	{
		TBitField tmp(BitSize);
	    for (int i=0; i< BitSize; i++)
	    {
		    int tmpval = (GetBit(i) || bf.GetBit(i));
		    if (tmpval == 0)
			    tmp.ClrBit(i);
		    else
			    tmp.SetBit(i);
	    }
	    return tmp;
	}
	else
	{
		if (BitSize > bf.BitSize)
		{
			TBitField tmp(BitSize);
			for (int i = 0; i < bf.BitSize; i++)
			{
				int tmpval = (GetBit(i) || bf.GetBit(i));
		        if (tmpval == 0)
			        tmp.ClrBit(i);
		        else
			        tmp.SetBit(i);
			}
			for (int i = bf.BitSize; i < BitSize; i++)
				if (GetBit(i) == 1)
					tmp.SetBit(i);
				else
					tmp.ClrBit(i);
			return tmp;
		}
		else
		{
			TBitField tmp(bf.BitSize);
			for (int i = 0; i < BitSize; i++)
			{
				int tmpval = (GetBit(i) || bf.GetBit(i));
		        if (tmpval == 0)
			        tmp.ClrBit(i);
		        else
			        tmp.SetBit(i);
			}
			for (int i = BitSize; i < bf.BitSize; i++)
				if (bf.GetBit(i) == 1)
					tmp.SetBit(i);
				else
					tmp.ClrBit(i);
			return tmp;
		}
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitSize == bf.BitSize)
	{
		TBitField tmp(BitSize);
	    for (int i=0; i< BitSize; i++)
	    {
		    int tmpval = (GetBit(i) && bf.GetBit(i));
		    if (tmpval == 0)
			    tmp.ClrBit(i);
		    else
			    tmp.SetBit(i);
	    }
	    return tmp;
	}
	else
	{
		if (BitSize > bf.BitSize)
		{
			TBitField tmp(BitSize);
			for (int i = 0; i < bf.BitSize; i++)
			{
				int tmpval = (GetBit(i) && bf.GetBit(i));
		        if (tmpval == 0)
			        tmp.ClrBit(i);
		        else
			        tmp.SetBit(i);
			}
			for (int i = bf.BitSize; i < BitSize; i++)
				tmp.ClrBit(i);
			return tmp;
		}
		else
		{
			TBitField tmp(bf.BitSize);
			for (int i = 0; i < BitSize; i++)
			{
				int tmpval = (GetBit(i) && bf.GetBit(i));
		        if (tmpval == 0)
			        tmp.ClrBit(i);
		        else
			        tmp.SetBit(i);
			}
			for (int i = BitSize; i < bf.BitSize; i++)
				tmp.ClrBit(i);
			return tmp;
		}
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitSize);
	for (int i=0;i<size;i++)
		tmp.mas[i]= ~mas[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.BitSize))
	{
		bf.SetBit(i); 
		istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitSize; i++)
		ostr << bf.GetBit(i);
	return ostr;
}