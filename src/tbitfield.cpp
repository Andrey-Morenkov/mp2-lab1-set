// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <dos.h>
using namespace std;

TBitField::TBitField(int len)
{
  BitSize = len;
  size = (BitSize/(sizeof(TELEM)*8))+1;
  mas = new TELEM[size];
  for (int i = 0; i<size; i++)
	mas[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	size = bf.size;
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
  return(n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  int tmp = n%(sizeof(TELEM)*8);
  TELEM mask  = 1;
  mask=(mask << (tmp-1));
  return (mask);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return (BitSize);
}

void TBitField::SetBit(const int n) // установить бит
{
  int m = GetMemIndex(n);
  TELEM mask = GetMemMask(n);
  mas[m]=mas[m]| mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int m = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mas[m]= (mas[m]&(!mask));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  int m = GetMemIndex(n); // ищем ячейку
  TELEM mask = GetMemMask(n); // маска на эту ячейку
  int result = mask & mas[m]; 
  if (result == 0)
	return(0);
  else
	return(1);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitSize=bf.BitSize;
	size=bf.size;
	for(int i=0;i<size;i++)
		mas[i]=bf.mas[i];
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int sum1=0,sum2=0;
	for(int i=0;i<size;i++)
	{
		sum1+=mas[i];
	}
	for(int i=0;i<size;i++)
	{
		sum2+=bf.mas[i];
	}
	if (sum1 == sum2)
		return 1;
	else
		return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int sum1=0,sum2=0;
  for(int i=0; i<size; i++)
  {
	sum1 += mas[i];
  }
  for(int i=0; i<size; i++)
  {
	sum2 += bf.mas[i];
  }
  if (sum1 == sum2)
	return 0;
  else
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp (BitSize);
	for (int i=0; i<size; i++)
	{
		tmp.mas[i] = mas[i] | bf.mas[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp (BitSize);
	for (int i=0; i<size; i++)
	{
		tmp.mas[i] = mas[i] & bf.mas[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp (BitSize);
	for (int i=0; i<size; i++)
	{
		tmp.mas[i] = ~mas[i];
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{


}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr<<"[";
	for(int i=0;i<(bf.BitSize - 1);i++)
	{
	   ostr<<bf.GetBit(i);
	}
	int z = bf.BitSize;
	ostr<<bf.GetBit(z)<<"]"<<endl;
	return ostr;
}
