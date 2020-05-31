//Jacek Matulewski, e-mail: jacek@fizyka.umk.pl
//wersja 1.1

//pomoc w optymalizacji: Krzystof ChyziDski, MichaB ZieliDski
#ifndef MACIERZ_H
#define MACIERZ_H

#include "Wektor.hpp"
#include <cassert>
#include <algorithm>
#include <functional>

template<typename T, int stopieD> 
struct TMacierzKwadratowa
{
public:
	static const int Rozmiar = stopieD * stopieD;
	static const int StopieD = stopieD;

protected: 
	T elementy[Rozmiar]; 

private:
	//iteratory
	T* pocztek()
	{
		return elementy;
	}
	T* koniec()
	{
		return elementy + Rozmiar;
	}
	const T* pocztek() const
	{
		return elementy;
	}
	const T* koniec() const
	{
		return elementy + Rozmiar;
	}

public:
	//dostp do element�w
	T& operator[](const int indeks)
	{
		assert(indeks >= 0 && indeks < Rozmiar);
		return elementy[indeks];
	};
	const T& operator[](const int indeks) const
	{
		assert(indeks >= 0 && indeks < Rozmiar);
		return elementy[indeks];
	};
	T& operator()(const int wiersz, const int kolumna)
	{
		assert(kolumna >= 0 && kolumna < stopieD);
		assert(wiersz >= 0 && wiersz < stopieD);
		return elementy[wiersz + stopieD*kolumna];
	}
	const T& operator()(const int wiersz, const int kolumna) const
	{
		assert(0 <= kolumna && kolumna < stopieD);
		assert(0 <= wiersz  && wiersz  < stopieD);
		return elementy[wiersz + stopieD*kolumna];
	}

	T PobierzElement(const int indeks) const
	{
		//return const_cast<TMacierzKwadratowa*>(this)->KontrolowanyDostepDoElementu(indeks);		
		return this->operator[](indeks);
	}
	T PobierzElement(const int wiersz, const int kolumna) const
	{
		//return const_cast<TMacierzKwadratowa*>(this)->KontrolowanyDostepDoElementu(wiersz, kolumna);		
		return this->operator()(wiersz, kolumna);
	}

	void ZerujElementy()
	{
		for (int i = 0; i < Rozmiar; ++i) this->operator[](i) = 0;
		//for (auto &element : elementy) element = 0;
	}
	void UstawJednostkow()
	{
		ZerujElementy();
		for (int kolumnaWiersz = 0; kolumnaWiersz < stopieD; ++kolumnaWiersz)
			this->operator()(kolumnaWiersz, kolumnaWiersz) = 1;
	}

	void UstawElement(const int indeksElementu, T wartosc)
	{
		this->operator[](indeksElementu) = wartosc;
	}
	void UstawElement(const int wiersz, const int kolumna, T wartosc)
	{
		this->operator()(wiersz, kolumna) = wartosc;
	}
	void UstawElementy(const T* elementyMacierzy)
	{
		//for (int i = 0; i < Rozmiar; ++i) UstawElement(i, elementy[i]);
		std::copy(elementyMacierzy, elementyMacierzy + Rozmiar, elementy);
	}
	void Ustaw(const TMacierzKwadratowa& m)
	{
		UstawElementy(m.elementy);
	}

	T* KopiaElementow(T* bufor) const {
		std::copy(pocztek(), koniec(), bufor);
		return bufor;
	}
	T* KopiaKolumny(const int indeksKolumny, T* bufor) const
	{		
		assert(indeksKolumny >= 0 && indeksKolumny < stopieD);
		const T* pocztekKolumny = pocztek() + indeksKolumny * stopieD;
		std::copy(pocztekKolumny, pocztekKolumny + stopieD, bufor);
		return bufor;
	}
	T* KopiaWiersza(const int indeksWiersza, T* bufor) const
	{
		assert(indeksWiersza >= 0 && indeksWiersza < stopieD);
		for (int i = 0; i < stopieD; ++i) bufor[i] = PobierzElement(indeksWiersza, i);
		return bufor;
	}

	//konstruktory
	TMacierzKwadratowa()
	{
		ZerujElementy();
	};
	TMacierzKwadratowa(const T* elementy)
	{
		UstawElementy(elementy);
	};

	//operatory relacji
	bool operator==(const TMacierzKwadratowa& m) const
	{
		/*
		for (int i = 0; i < Rozmiar; ++i)
			if (PobierzElement(i) != m.PobierzElement(i))
				return false;
		return true;
		*/
		return std::equal(pocztek(), koniec(), m.pocztek());
	}
	bool operator!=(const TMacierzKwadratowa& w) const
	{
		return !(*this == w);
	}
	bool almostEqual(const TMacierzKwadratowa& m, T tolerancjaBledu = 0) const
	{
		for (int i = 0; i<Rozmiar; ++i)
			if (fabs(PobierzElement(i) - m.PobierzElement(i))>tolerancjaBledu)
				return false;
		return true;
	}

	//operatory arytmetyczne
	//NIE TESTOWANE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	TMacierzKwadratowa& operator+=(const TMacierzKwadratowa& m)
	{
		//for (int i = 0; i < Rozmiar; ++i) KontrolowanyDostepDoElementu(i) += m.PobierzElement(i);
		std::transform(pocztek(), koniec(), m.pocztek(), pocztek(), std::plus<T>());
		return *this;
	}
	//NIE TESTOWANE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	TMacierzKwadratowa operator+(const TMacierzKwadratowa& m) const
	{
		//return TMacierzKwadratowa(*this) += m;
		//*
		TMacierzKwadratowa wynik;
		std::transform(pocztek(), koniec(), m.pocztek(), wynik.pocztek(), std::plus<T>());
		return wynik;
		//*/
	};
	TMacierzKwadratowa& operator-=(const TMacierzKwadratowa& m)
	{
		//for (int i = 0; i < Rozmiar; ++i) this->operator[](i) -= m.PobierzElement(i);
		std::transform(pocztek(), koniec(), m.pocztek(), pocztek(), std::minus<T>());
		return *this;
	}
	TMacierzKwadratowa operator-(const TMacierzKwadratowa& m) const
	{
		//return TMacierzKwadratowa(*this) -= m;
		//*
		TMacierzKwadratowa wynik;
		std::transform(pocztek(), koniec(), m.pocztek(), wynik.pocztek(), std::minus<T>());
		return wynik;
		//*/
	};
	TMacierzKwadratowa& operator*=(const T a)
	{
		for (int i = 0; i < Rozmiar; ++i) this->operator[](i) *= a;
		//for (T &element : *this) element *= a; // C++11 
		return *this;
	};
	TMacierzKwadratowa operator*(const T a) const
	{
		return TMacierzKwadratowa(*this) *= a;
	};
	TMacierzKwadratowa& operator/=(const T a)
	{
		assert(a != 0);
		for (int i = 0; i < Rozmiar; ++i) this->operator[](i) /= a;
		return *this;
	};
	TMacierzKwadratowa operator/(const T a) const
	{
		return TMacierzKwadratowa(*this) /= a;
	};

	TMacierzKwadratowa& rmul(const TMacierzKwadratowa& m)
	{
		TMacierzKwadratowa kopia = *this;
		this->ZerujElementy();
		for (int kolumna = 0; kolumna < stopieD; ++kolumna)
			for (int wiersz = 0; wiersz < stopieD; ++wiersz)
				for (int i = 0; i < stopieD; ++i)
					this->operator()(wiersz, kolumna) += kopia.PobierzElement(wiersz, i)*m.PobierzElement(i, kolumna);
		return *this;
	};
	TMacierzKwadratowa& lmul(const TMacierzKwadratowa& m)
	{
		//tu wystarczy dodatkowy wiersz (wyzej wypelniac oryginalna)	
		TMacierzKwadratowa kopia = *this;
		this->ZerujElementy();
		for (int kolumna = 0; kolumna < stopieD; ++kolumna)
			for (int wiersz = 0; wiersz < stopieD; ++wiersz)
				for (int i = 0; i < stopieD; ++i)
					this->operator()(wiersz, kolumna) += m.PobierzElement(wiersz, i)*kopia.PobierzElement(i, kolumna);
		return *this;
	};
	TMacierzKwadratowa& operator*=(const TMacierzKwadratowa& m)
	{
		return rmul(m);
	}
	TMacierzKwadratowa operator*(const TMacierzKwadratowa m) const
	{
		return TMacierzKwadratowa(*this) *= m;
	};
	void TransformujWektor(TWektor<T, stopieD>& wektor) const
	{
		TWektor<T, stopieD> kopia = wektor;
		for (int wiersz = 0; wiersz < stopieD; ++wiersz)
		{
			wektor[wiersz] = 0;
			for (int kolumna = 0; kolumna < stopieD; ++kolumna)
				wektor[wiersz] += this->PobierzElement(wiersz, kolumna)*kopia[kolumna];
		}
	}
	TWektor<T, stopieD> PrzetransformowanyWektor(const TWektor<T, stopieD>& wektor) const
	{		
		TWektor<T, stopieD> wynik = wektor;
		TransformujWektor(wynik);
		return wynik;
	}
	TMacierzKwadratowa Transponowana() const
	{
		TMacierzKwadratowa m;
		m.ZerujElementy();
		for (int kolumna = 0; kolumna < stopieD; ++kolumna)
			for (int wiersz = 0; wiersz < stopieD; ++wiersz)
				m(wiersz, kolumna) = PobierzElement(kolumna, wiersz);
		return m;
	}	

protected:
	static TMacierzKwadratowa CreateDiagonal()
	{
		TMacierzKwadratowa m;
		m.UstawJednostkow();
		return m;
	}
};

/* --------------------------------------------------------------------------------------- */

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

template<typename T, int stopieD> 
bool TestyMacierzyKwadratowej(unsigned int ziarno)
{
	bool wynik = true;

	const int rozmiar = stopieD * stopieD;
	if (TMacierzKwadratowa<T, stopieD>::Rozmiar != rozmiar) wynik = false;

	//test kolejnosci elementow (do obejrzenia w Locals lub Watch)
	T elementyMacierzyKolejnosc[rozmiar];
	for (int i = 0; i < rozmiar; ++i) elementyMacierzyKolejnosc[i] = (T)i;
	TMacierzKwadratowa<T, stopieD> mKolejnosc(elementyMacierzyKolejnosc);
	for (int i = 0; i < rozmiar; ++i)
	{
		if (mKolejnosc[i] != i) wynik = false;
		if (mKolejnosc.PobierzElement(i) != i) wynik = false;
	}
	for (int kolumna = 0; kolumna < stopieD; ++kolumna)
	{
		for (int wiersz = 0; wiersz < stopieD; ++wiersz)
		{
			if (mKolejnosc.PobierzElement(wiersz, kolumna) != wiersz + stopieD*kolumna) wynik = false;
		}
	}

	//testy na macierzy jednostkowej
	TMacierzKwadratowa<T, stopieD> mI;
	mI.UstawJednostkow();
	//if (mI.Slad() != stopieD) wynik = false;
	if (mI*mI != mI) wynik = false;
	if (mI*mI*mI != mI) wynik = false;
	if (mI.Transponowana() != mI) wynik = false;

	//tworzenie macierzy z elementami losowymi
	const T zakres = 10;
	//T tolerancjaBledu=(T)1E-9; //dla double
	T elementyMacierzy[rozmiar];
	for (int i = 0; i < rozmiar; ++i) elementyMacierzy[i] = zakres*rand() / RAND_MAX;
	TMacierzKwadratowa<T, stopieD> m(elementyMacierzy);

	//kontrola konstruktora kopiujcego
	TMacierzKwadratowa<T, stopieD> m2(m);
	for (int i = 0; i < rozmiar; ++i)
	{
		if (m[i] != m2[i]) wynik = false;
		m2[i] += 1;
		if (m[i] == m2[i]) wynik = false;
	}

	//test kopiowania wskaznika
	TMacierzKwadratowa<T, stopieD> m3 = m;
	for (int i = 0; i < rozmiar; ++i)
	{
		if (m[i] != m3[i]) wynik = false;
		m2[i] += 1;
		if (m[i] != m3[i]) wynik = false;
	}

	//odczyt elementow
	for (int i = 0; i < rozmiar; ++i)
	{
		if (m.PobierzElement(i) != elementyMacierzy[i]) wynik = false;
		if (m[i] != elementyMacierzy[i]) wynik = false;
	}
	for (int kolumna = 0; kolumna < stopieD; ++kolumna)
		for (int wiersz = 0; wiersz < stopieD; ++wiersz)
			if (m.PobierzElement(wiersz, kolumna) != elementyMacierzy[wiersz + stopieD*kolumna]) wynik = false;
	T kopiaElementow[rozmiar];
	m.KopiaElementow(kopiaElementow);
	for (int i = 0; i < rozmiar; ++i) if (kopiaElementow[i] != elementyMacierzy[i]) wynik = false;

	//odczyt kolumn
	for (int kolumna = 0; kolumna < stopieD; ++kolumna)
	{
		T kopiaElementowKolumny[stopieD];
		m.KopiaKolumny(kolumna, kopiaElementowKolumny);
		for (int wiersz = 0; wiersz < stopieD; ++wiersz)
			if (kopiaElementowKolumny[wiersz] != elementyMacierzy[wiersz + stopieD*kolumna]) wynik = false;
	}

	//zapis elementow
	m.ZerujElementy();
	if (m != TMacierzKwadratowa<T, stopieD>()) wynik = false;
	for (int i = 0; i < rozmiar; ++i) m.UstawElement(i, elementyMacierzy[i]);
	for (int i = 0; i < rozmiar; ++i) if (m[i] != elementyMacierzy[i]) wynik = false;
	m.ZerujElementy();
	for (int kolumna = 0; kolumna < stopieD; ++kolumna)
		for (int wiersz = 0; wiersz < stopieD; ++wiersz)
			m.UstawElement(wiersz, kolumna, elementyMacierzy[wiersz + stopieD*kolumna]);
	for (int i = 0; i < rozmiar; ++i) if (m[i] != elementyMacierzy[i]) wynik = false;

	//testy operatorow mno|enia i metod
	if (m*mI != m) wynik = false;
	if (mI*m != m) wynik = false;
	TMacierzKwadratowa<T, stopieD> kopia = m;
	kopia *= mI;
	if (kopia != m) wynik = false;
	
	kopia = m; 
	if (kopia.rmul(mI) != m) wynik = false;
	if (mI.rmul(m) != m) wynik = false;
	mI.UstawJednostkow();
	kopia = m; 
	if (kopia.lmul(mI) != m) wynik = false;
	if (mI.lmul(m) != m) wynik = false;
	mI.UstawJednostkow();

	if (m.Transponowana().Transponowana() != m) wynik = false;
	
	TMacierzKwadratowa<T, stopieD> m0;
	m0.ZerujElementy();
	if (m + m0 != m) wynik = false;
	if (m0 + m != m) wynik = false;
	kopia = m; kopia += m0;
	if (kopia != m) wynik = false;
	kopia = m; kopia -= m0;
	if (kopia != m) wynik = false;

	kopia = m + m;
	for (int i = 0; i < rozmiar; ++i) if (kopia[i] != 2 * m[i]) wynik = false;
	kopia = m; kopia += m;
	for (int i = 0; i < rozmiar; ++i) if (kopia[i] != 2 * m[i]) wynik = false;

	//transformacja wektora
	TWektor<T,stopieD> wektor;
	TWektor<T, stopieD> wektorWynik;
	for (int i = 0; i < stopieD; ++i) wektor[i] = zakres*rand() / RAND_MAX;
	wektorWynik = mI.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < stopieD; ++i)
	{
		if (wektor[i] != wektorWynik[i]) wynik = false;
	}
	mI.TransformujWektor(wektor);
	for (int i = 0; i < stopieD; ++i) if (wektor[i] != wektorWynik[i]) wynik = false;

	return wynik;
}
#endif
