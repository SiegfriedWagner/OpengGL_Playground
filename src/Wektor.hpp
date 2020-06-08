//Jacek Matulewski, e-mail: jacek@fizyka.umk.pl
//wersja 1.0

#ifndef WEKTOR_H
#define WEKTOR_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

template<typename T, int size>
class TWektor
{
private: 
	T elementy[size];

public:
	T& operator[](const int indeks)
	{
		assert(indeks >= 0 && indeks < size);
		return elementy[indeks];
	}

	const T& operator[](const int indeks) const
	{
		assert(indeks >= 0 && indeks < size);
		return elementy[indeks];
	}
	TWektor()
	{
		Zeruj();
	}

	TWektor(T* elementy)
	{
		for (int i = 0; i < size; ++i) this->operator[](i) = elementy[i];
	}

	void KopiujElementy(T* bufor) const
	{
		for (int i = 0; i < size; ++i) bufor[i] = this->operator[](i);
	}

	void Zeruj()
	{
		for (int i = 0; i < size; ++i) elementy[i] = 0;
	}

	TWektor operator-() const
	{
		TWektor wynik;
		for (int i = 0; i < 3; ++i) wynik[i] = -this->operator[](i);
		return wynik;
	}

	TWektor& operator-=(const TWektor& wektor)
	{
		for (int i = 0; i < size; ++i) this->operator[](i) -= wektor[i];
		return *this;
	}

	TWektor operator+(const TWektor& wektor) const
	{
		TWektor wynik;
		for (int i = 0; i < size; ++i) wynik[i] = this->operator[](i) + wektor[i];
		return wynik;
	}

	TWektor operator+=(const TWektor& wektor)
	{
		for (int i = 0; i < size; ++i) this->operator[](i) += wektor[i];
		return *this;
	}

	TWektor operator-(const TWektor& wektor) const
	{
		TWektor wynik;
		for (int i = 0; i < size; ++i) wynik[i] = this->operator[](i) - wektor[i];
		return wynik;
	}

	TWektor operator*(const T& a) const
	{
		TWektor wynik;
		for (int i = 0; i < size; ++i) wynik[i] = this->operator[](i) * a;
		return wynik;
	}

	static T dot(const TWektor& wektor1, const TWektor& wektor2) // iloczyn skalarny
	{
		T iloczynSkalarny = 0;
		for (int i = 0; i < size; ++i) iloczynSkalarny += wektor1[i] * wektor2[i];
		return iloczynSkalarny;
	}

	T operator*(const TWektor& wektor) const //iloczyn skalarny
	{
		return dot(*this, wektor);
	}

	T squareMagnitude() const
	{
		return dot(*this, *this);
	}

	T magnitude()
	{
		return sqrt(squareMagnitude());
	}

	void norm()
	{
		T magnitude = magnitude();
		for (int i = 0; i < size; ++i) elementy[i] /= magnitude;
	}

	TWektor Unormowany() const
	{
		TWektor wynik = *this;
		wynik.Normuj  ();
		return wynik;
	}
};

template<typename T, int size> TWektor<T, size> inline operator*(const T a, const TWektor<T, size> &w)
{
	return w*a;
	//return TWektor<T>(a*w.X,a*w.Y,a*w.Z);	
}

template<typename T>
class TWektor3 : public TWektor<T, 3>
{
public:
	TWektor3(): TWektor<T, 3>() {}
	TWektor3(T* elementy): TWektor<T,3>(elementy) {}
	TWektor3(T x, T y, T z)
	{
		this->operator[](0) = x;
		this->operator[](1) = y;
		this->operator[](2) = z;
	}
	TWektor3(const TWektor<T, 3>& wektor): TWektor<T, 3>(wektor) {}	

	static TWektor3 vecMul(TWektor3 wektor1, TWektor3 wektor2)  //IloczynWektorowy3fv
	{
		TWektor3 wynik;
		wynik[0] = wektor1[1] * wektor2[2] - wektor1[2] * wektor2[1];
		wynik[1] = -(wektor1[0] * wektor2[2] - wektor1[2] * wektor2[0]);
		wynik[2] = wektor1[0] * wektor2[1] - wektor1[1] * wektor2[0];
		return wynik;
	}
	static const TWektor3 WersorX;
	static const TWektor3 WersorY;
	static const TWektor3 WersorZ;
};

template<typename T>
const TWektor3<T> TWektor3<T>::WersorX = TWektor3<T>(1, 0, 0);
template<typename T>
const TWektor3<T> TWektor3<T>::WersorY = TWektor3<T>(0, 1, 0);
template<typename T>
const TWektor3<T> TWektor3<T>::WersorZ = TWektor3<T>(0, 0, 1);


template<typename T>
class TWektor4 : public TWektor<T, 4>
{
public:
	TWektor4(): TWektor<T, 4>() {}
	TWektor4(T* elementy): TWektor<T, 4>(elementy) {}
	TWektor4(T x, T y, T z, T w = 1)
	{
		this->operator[](0) = x;
		this->operator[](1) = y;
		this->operator[](2) = z;
		this->operator[](3) = w;
	}

	TWektor4(const TWektor3<T>& wektor3)
	{
		for (int i = 0; i < 3; ++i) this->operator[](i) = wektor3[i];
		this->operator[](3) = (T)1;
	}

	TWektor3<T> KonwertujDoWektora3()
	{
		TWektor3<T> wynik;
		for (int i = 0; i < 3; ++i) wynik[i] = this->operator[](i) / this->operator[](3);
		return wynik;
	}
};

typedef TWektor3<float> Wektor3;
typedef TWektor4<float> Wektor4;

/* --------------------------------------------------------------------------------------- */

template<typename T>
bool TestyWektora3(unsigned int ziarno)
{
	bool wynik = true;	

	TWektor3<T> w1(1, 2, 3);
	TWektor3<T> w2(4, 5, 6);
	TWektor3<T> wynikWektor;
	wynikWektor = w1 + w2;
	for (int i = 0; i < 3; ++i)	{
		if (wynikWektor[i] != w1[i] + w2[i]) wynik = false;
	}
	wynikWektor = w1 - w2;
	for (int i = 0; i < 3; ++i)	{
		if (wynikWektor[i] != w1[i] - w2[i]) wynik = false;
	}
	T elementyWersoraX[3] = { 1, 0, 0 }; TWektor3<T> wersorX(elementyWersoraX);
	T elementyWersoraY[3] = { 0, 1, 0 }; TWektor3<T> wersorY(elementyWersoraY);
	T elementyWersoraZ[3] = { 0, 0, 1 }; TWektor3<T> wersorZ(elementyWersoraZ);
	wynikWektor = TWektor3<T>::vecMul(wersorX, wersorY);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != wersorZ[i]) wynik = false;
	return wynik;
}
#endif
