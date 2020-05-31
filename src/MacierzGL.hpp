#ifndef MACIERZGL_H
#define MACIERZGL_H

#include "Matrix.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include <exception>

template<typename T>
T degToRad(T deg)
{
	return (T)(M_PI * deg / (T)180);
}

template<typename T>
T radToDeg(T rad)
{
	return (T)(180 * rad / M_PI);
}

#include "Wektor.hpp"

template<typename T>
struct TMacierzGrafika3D : public TMacierzKwadratowa<T, 4>
{
public:
	TMacierzGrafika3D(): TMacierzKwadratowa<T, 4>() {}
	TMacierzGrafika3D(const T elementy[16]): TMacierzKwadratowa<T, 4>(elementy)	{ }

	TMacierzGrafika3D(const TMacierzKwadratowa<T, 4>& m)
		: TMacierzKwadratowa<T, 4>(m)
	{
	}

	Wektor4 KopiaKolumny(const int indeksKolumny) const
	{
		T elementyKolumny[4];
		TMacierzKwadratowa<T,4>::KopiaKolumny(indeksKolumny, elementyKolumny);
		return Wektor4(elementyKolumny);
	}

	Wektor4 KopiaWiersza(const int indeksWiersza) const
	{
		T elementyWiersza[4];
		KopiaWiersza(indeksWiersza, elementyWiersza);
		return Wektor4(elementyWiersza);
	}

	void setScale(T sx, T sy, T sz)
	{
		this->ZerujElementy();
		this->UstawElement(0, 0, sx);
		this->UstawElement(1, 1, sy);
		this->UstawElement(2, 2, sz);
		this->UstawElement(3, 3, 1);
	}
	static TMacierzGrafika3D Skalowanie(T sx, T sy, T sz) {
		TMacierzGrafika3D m;
		m.setScale(sx, sy, sz);
		return m;
	}
	void setPosition(T tx, T ty, T tz) {
		this->UstawJednostkow();
		this->UstawElement(0, 3, tx);
		this->UstawElement(1, 3, ty);
		this->UstawElement(2, 3, tz);
	}
	void setPosition(Wektor3 t)	{
		setPosition(t[0], t[1], t[2]);
	}
	static TMacierzGrafika3D Move(T tx, T ty, T tz)	{
		TMacierzGrafika3D<T> m;
		m.setPosition(tx, ty, tz);
		return m;
	}
	static TMacierzGrafika3D move(Wektor3 t) {
		return move(t[0], t[1], t[2]);
	}
	void rotateX(T angle, bool radians = false)
	{
		if (!radians) angle = degToRad(angle);
		this->UstawJednostkow();
		T s = sin(angle);
		T c = cos(angle);
		this->UstawElement(1, 1, c);
		this->UstawElement(1, 2, -s);
		this->UstawElement(2, 1, s);
		this->UstawElement(2, 2, c);
	}

	static TMacierzGrafika3D RotationX(T angle, bool radioans = false)
	{
		TMacierzGrafika3D m;
		m.rotateX(angle, radioans);
		return m;
	}

	void rotateY(T angle, bool angleWRadianach = false)
	{
		if (!angleWRadianach) angle = degToRad(angle);
		this->UstawJednostkow();
		T s = sin(angle);
		T c = cos(angle);
		this->UstawElement(0, 0, c);
		this->UstawElement(0, 2, s);
		this->UstawElement(2, 0, -s);
		this->UstawElement(2, 2, c);
	}
	static TMacierzGrafika3D RotationY(T angle, bool angleWRadianach = false)
	{
		TMacierzGrafika3D m;
		m.rotateY(angle, angleWRadianach);
		return m;
	}
	void rotateZ(T angle, bool angleWRadianach = false)
	{
		if (!angleWRadianach) angle = degToRad(angle);
		this->UstawJednostkow();
		T s = sin(angle);
		T c = cos(angle);
		this->UstawElement(0, 0, c);
		this->UstawElement(0, 1, -s);
		this->UstawElement(1, 0, s);
		this->UstawElement(1, 1, c);
	}
	static TMacierzGrafika3D RotationZ(T angle, bool angleWRadianach = false)
	{
		TMacierzGrafika3D m;
		m.rotateZ(angle, angleWRadianach);
		return m;
	}

	//yaw, pitch, roll
	void rotateXYZ(T angleX, T angleY, T angleZ, bool angleWRadianach = false)
	{
		if (!angleWRadianach)
		{
			angleX = degToRad(angleX);
			angleY = degToRad(angleY);
			angleZ = degToRad(angleZ);
		}
		T sx = sin(angleX); T cx = cos(angleX);
		T sy = sin(angleY); T cy = cos(angleY);
		T sz = sin(angleZ); T cz = cos(angleZ);
		this->ZerujElementy();
		this->UstawElement(0, 0, cy*cz);
		this->UstawElement(0, 1, -cy*sz);
		this->UstawElement(0, 2, sy);
		this->UstawElement(1, 0, sx*sy*cz + cx*sz);
		this->UstawElement(1, 1, -sx*sy*sz + cx*cz);
		this->UstawElement(1, 2, -sx*cy);
		this->UstawElement(2, 0, -cx*sy*cz + sx*sz);
		this->UstawElement(2, 1, cx*sy*sz + sx*cz);
		this->UstawElement(2, 2, cx*cy);
		this->UstawElement(3, 3, 1);
	}
	static TMacierzGrafika3D RotationXYZ(T angleX, T angleY, T angleZ, bool angleWRadianach = false) {
		TMacierzGrafika3D m;
		m.rotateXYZ(angleX, angleY, angleZ, angleWRadianach);
		return m;
	}
	void rotateZXZ(T angleZ2, T angleX, T angleZ1, bool angleWRadianach = false) {
		if (!angleWRadianach)
		{
			angleZ2 = degToRad(angleZ2);
			angleX = degToRad(angleX);
			angleZ1 = degToRad(angleZ1);
		}
		T sz2 = sin(angleZ2); T cz2 = cos(angleZ2);
		T sx = sin(angleX); T cx = cos(angleX);
		T sz1 = sin(angleZ1); T cz1 = cos(angleZ1);
		this->ZerujElementy();
		this->UstawElement(0, 0, cz2*cz1 - sz2*cx*sz1);
		this->UstawElement(0, 1, -cz2*sz1 - sz2*cx*cz1);
		this->UstawElement(0, 2, sz2*sx);
		this->UstawElement(1, 0, sz2*cz1 + cz2*cx*sz1);
		this->UstawElement(1, 1, -sz2*sz1 + cz2*cx*cz1);
		this->UstawElement(1, 2, -cz2*sx);
		this->UstawElement(2, 0, sx*sz1);
		this->UstawElement(2, 1, sx*cz1);
		this->UstawElement(2, 2, cx);
		this->UstawElement(3, 3, 1);
	}
	static TMacierzGrafika3D RotationZXZ(T angleZ2, T angleX, T angleZ1, bool angleWRadianach = false)
	{
		TMacierzGrafika3D m;
		m.rotateZXZ(angleZ2, angleX, angleZ1, angleWRadianach);
		return m;
	}
	void rotateAlongAxis(T angle, T ux, T uy, T uz, bool angleWRadianach = false)
	{
		if (!angleWRadianach) angle = degToRad(angle);
		T s = sin(angle); 
		T c = cos(angle);
		this->ZerujElementy();
		this->UstawElement(0, 0, c + (1 - c)*ux*ux);
		this->UstawElement(0, 1, (1 - c)*ux*uy - s*uz);
		this->UstawElement(0, 2, (1 - c)*uz*ux + s*uy);
		this->UstawElement(1, 0, (1 - c)*ux*uy + s*uz);
		this->UstawElement(1, 1, c + (1 - c)*uy*uy);
		this->UstawElement(1, 2, (1 - c)*uy*uz - s*ux);
		this->UstawElement(2, 0, (1 - c)*uz*ux - s*uy);
		this->UstawElement(2, 1, (1 - c)*uy*uz + s*ux);
		this->UstawElement(2, 2, c + (1 - c)*uz*uz);
		this->UstawElement(3, 3, 1);
	}

	void rotateAlongAxis(T angle, Wektor3 u, bool angleWRadianach = false)
	{
		rotateAlongAxis(angle, u[0], u[1], u[2], angleWRadianach);
	}

	static TMacierzGrafika3D RotationAlongAxis(T angle, T ux, T uy, T uz, bool angleWRadianach = false)
	{
		TMacierzGrafika3D m;
		m.rotateAlongAxis(angle, ux, uy, uz, angleWRadianach);
		return m;
	}

	static TMacierzGrafika3D RotationAlongAxis(T angle, Wektor3 u, bool angleWRadianach = false)
	{
		return RotationAlongAxis(angle, u[0], u[1], u[2], angleWRadianach);
	}

	void UstawProjectionMatrix(Wektor3 worldCenter, Wektor3 normalToProejctionPane, float moveProjectionMatrix)
	{		
		Wektor4 L = Wektor4(worldCenter[0], worldCenter[1], worldCenter[2], 1);
		Wektor4 N = Wektor4(normalToProejctionPane[0], normalToProejctionPane[1], normalToProejctionPane[2], moveProjectionMatrix);
		float alfa = Wektor4::dot(N, L);
		//
		this->UstawElement(0, 0, alfa - N[0] * L[0]);
		this->UstawElement(0, 1, -N[1] * L[0]);
		this->UstawElement(0, 2, -N[2] * L[0]);
		this->UstawElement(0, 3, -N[3] * L[0]);
		//
		this->UstawElement(1, 0, -N[0] * L[1]);
		this->UstawElement(1, 1, alfa - N[1] * L[1]);		
		this->UstawElement(1, 2, -N[2] * L[1]);
		this->UstawElement(1, 3, -N[3] * L[1]);
		//
		this->UstawElement(2, 0, -N[0] * L[2]);
		this->UstawElement(2, 1, -N[1] * L[2]);
		this->UstawElement(2, 2, alfa - N[2] * L[2]);
		this->UstawElement(2, 3, -N[3] * L[2]);
		//
		this->UstawElement(3, 0, -N[0] * L[3]);
		this->UstawElement(3, 1, -N[1] * L[3]);
		this->UstawElement(3, 2, -N[2] * L[3]);
		this->UstawElement(3, 3, alfa - N[3] * L[3]);
	}

	static TMacierzGrafika3D ProjectionMatrix(Wektor3 worldCenter, Wektor3 normalToProejctionPane, float moveProjectionMatrix)
	{
		TMacierzGrafika3D m;
		m.UstawProjectionMatrix(worldCenter, normalToProejctionPane, moveProjectionMatrix);
		return m;
	}

	void UstawRzutIzometryczny(T l, T r, T b, T t, T n, T f)
	{
		T w = r - l;
		T h = t - b;
		T d = f - n;
		setScale(2 / w, 2 / h, -2 / d);
		UstawElement(0, 3, -(r + l) / w);
		UstawElement(1, 3, -(t + b) / h);
		UstawElement(2, 3, -(f + n) / d);
	}

	static TMacierzGrafika3D RzutIzometryczny(T l, T r, T b, T t, T n, T f)
	{
		TMacierzGrafika3D m;
		m.UstawRzutIzometryczny(l, r, b, t, n, f);
		return m;
	}

	void UstawRzutPerspektywiczny(T l, T r, T b, T t, T n, T f)
	{
		T w = r - l;
		T h = t - b;
		T d = f - n;
		setScale(2 * n / w, 2 * n / h, -(f + n) / d);
		this->UstawElement(0, 2, (r + l) / w);
		this->UstawElement(1, 2, (t + b) / h);
		this->UstawElement(3, 2, -1);
		this->UstawElement(2, 3, -2 * n * f / d);
		this->UstawElement(3, 3, 0);
	}

	static TMacierzGrafika3D RzutPerspektywiczny(T l, T r, T b, T t, T n, T f)
	{
		TMacierzGrafika3D m;
		m.UstawRzutPerspektywiczny(l, r, b, t, n, f);
		return m;
	}

	static TMacierzGrafika3D UstawRzutPerspektywiczny2(T anglePionowegoPolaWidzeniaWStopniach, T proporcjaEkranu, T n, T f)
	{
		T anglePionowegoPolaWidzenia = degToRad(anglePionowegoPolaWidzeniaWStopniach);
		T h = 2 * n * tan(anglePionowegoPolaWidzenia / 2);
		T w = proporcjaEkranu * h;
		UstawRzutPerspektywiczny(-w / 2, w / 2, -h / 2, h / 2, n, f);
	}

	static TMacierzGrafika3D RzutPerspektywiczny2(T anglePionowegoPolaWidzeniaWStopniach, T proporcjaEkranu, T n, T f)
	{
		TMacierzGrafika3D m;
		m.UstawRzutPerspektywiczny2(anglePionowegoPolaWidzeniaWStopniach, proporcjaEkranu, n, f);
		return m;
	}

	void UstawWidokPatrzNa(
		Wektor3 kamera,
		Wektor3 centrum,
		Wektor3 polaryzacja)
	{
		Wektor3 E = kamera;
		Wektor3 C = centrum;
		Wektor3 U = polaryzacja;
		Wektor3 F = C - E;
		Wektor3 Fp = F.Unormowany();
		Wektor3 R = Wektor3::vecMul(Fp, U);
		R.norm();
		Wektor3 Up = Wektor3::vecMul(R, Fp);
		this->ZerujElementy();
		for (int kolumna = 0; kolumna < 3; kolumna++)
		{
			this->UstawElement(0, kolumna, R[kolumna]);
			this->UstawElement(1, kolumna, Up[kolumna]);
			this->UstawElement(2, kolumna, -Fp[kolumna]);
		}
		this->UstawElement(0, 3, -Wektor3::dot(R, E));
		this->UstawElement(1, 3, -Wektor3::dot(Up, E));
		this->UstawElement(2, 3, Wektor3::dot(Fp, E));
		this->UstawElement(3, 3, 1);
	}
	void UstawWidokPatrzNa(
		T kameraX, T kameraY, T kameraZ,
		T centrumX, T centrumY, T centrumZ,
		T polaryzacjaX, T polaryzacjaY, T polaryzacjaZ)
	{
		Wektor3 kamera(kameraX, kameraY, kameraZ);
		Wektor3 centrum(centrumX, centrumY, centrumZ);
		Wektor3 polaryzacja(polaryzacjaX, polaryzacjaY, polaryzacjaZ);
		UstawWidokPatrzNa(kamera, centrum, polaryzacja);
	}

	static TMacierzGrafika3D WidokPatrzNa(
		Wektor3 kamera,
		Wektor3 centrum,
		Wektor3 polaryzacja)
	{
		TMacierzGrafika3D m;
		m.UstawWidokPatrzNa(kamera, centrum, polaryzacja);
		return m;
	}

	static TMacierzGrafika3D WidokPatrzNa(
		T kameraX, T kameraY, T kameraZ,
		T centrumX, T centrumY, T centrumZ,
		T polaryzacjaX, T polaryzacjaY, T polaryzacjaZ)
	{
		TMacierzGrafika3D m;
		m.UstawWidokPatrzNa(
			kameraX, kameraY, kameraZ,
			centrumX, centrumY, centrumZ,
			polaryzacjaX, polaryzacjaY, polaryzacjaZ);
		return m;
	}

	//PRZETESTOWAC!!!!!!!!!!!!!!!!!!!!!!
	static TMacierzGrafika3D OperatorGwiazdki(T x, T y, T z)
	{
		TMacierzGrafika3D m;
		m.UstawElement(0, 1, -z);
		m.UstawElement(0, 2, y);
		m.UstawElement(1, 0, z);
		m.UstawElement(1, 2, -x);
		m.UstawElement(2, 0, -y);
		m.UstawElement(2, 1, x);
		m.UstawElement(3, 3, 1);
		return m;
	}

	//http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	TMacierzGrafika3D Odwrotna() const
	{
		TMacierzGrafika3D m = *this;
		T elementyMacierzyOdwrotnej[16];

		elementyMacierzyOdwrotnej[0] = 
			m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		elementyMacierzyOdwrotnej[4] = 
		    -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		elementyMacierzyOdwrotnej[8] = 
			m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		elementyMacierzyOdwrotnej[12] = 
		    -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		elementyMacierzyOdwrotnej[1] = 
			-m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		elementyMacierzyOdwrotnej[5] = 
			m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		elementyMacierzyOdwrotnej[9] = 
			-m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		elementyMacierzyOdwrotnej[13] = 
			m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		elementyMacierzyOdwrotnej[2] = 
			m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		elementyMacierzyOdwrotnej[6] = 
			-m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		elementyMacierzyOdwrotnej[10] = 
			m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		elementyMacierzyOdwrotnej[14] = 
			-m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		elementyMacierzyOdwrotnej[3] = 
			-m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		elementyMacierzyOdwrotnej[7] = 
			m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		elementyMacierzyOdwrotnej[11] = 
			-m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		elementyMacierzyOdwrotnej[15] = 
			m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		T wyznacznik = m[0] * elementyMacierzyOdwrotnej[0] + m[1] * elementyMacierzyOdwrotnej[4] + m[2] * elementyMacierzyOdwrotnej[8] + m[3] * elementyMacierzyOdwrotnej[12];
		if (wyznacznik == 0) throw std::exception("Macierz osobliwa");
		for (int i = 0; i < 16; i++) elementyMacierzyOdwrotnej[i] /= wyznacznik;
		return TMacierzGrafika3D(elementyMacierzyOdwrotnej);
	}
};

/* --------------------------------------------------------------------------------------- */
#include <GL/glew.h>

struct MacierzOpenGL : public TMacierzGrafika3D<float>
{
private:
	GLint identyfikatorMacierzy; //uniform location

public:
	MacierzOpenGL()
		: TMacierzGrafika3D<float>(), identyfikatorMacierzy(-1)
	{
	}
	MacierzOpenGL(const TMacierzKwadratowa<float, 4>& m)
		: TMacierzGrafika3D<float>(m), identyfikatorMacierzy(-1)
	{
	}
	MacierzOpenGL(const TMacierzGrafika3D<float>& m)
		: TMacierzGrafika3D<float>(m), identyfikatorMacierzy(-1)
	{
	}
	void setGLMatrixId(GLint identyfikatorMacierzy, bool setValuesFlag = false) {
		this->identyfikatorMacierzy = identyfikatorMacierzy;
		if (setValuesFlag) 
			setValues();
	}
	GLint PobierzIdentyfikator()
	{
		return identyfikatorMacierzy;
	}

	void setValues(bool raiseException = false)
	{
		if (identyfikatorMacierzy < 0) {
			if (raiseException) throw std::runtime_error("Aby przesłać macierz do programu shaderów ustaw wpierw jej identyfikator (uniform location)");
			else return;
		}
		glUniformMatrix4fv(identyfikatorMacierzy, 1, false, elementy);
	}
	static const MacierzOpenGL Jednostkowa;
	static const MacierzOpenGL Zerowa;
};

typedef MacierzOpenGL Macierz4;

/* --------------------------------------------------------------------------------------- */

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


template<typename T>
bool TestyMacierzyGrafika3D(unsigned int ziarno, T tolerancjaBledu = (T)1E-9)
{
	bool wynik = true;
	const T zakres = 10;	
	//T tolerancjaBledu = (T)1E-9; //dla double
	//if (typeif(T) == typeid(float)) tolerancjaBledu = (T)1E-5; //dla float

	//zerowa macierz
	TMacierzGrafika3D<T> m;
	for (int i = 0; i < TMacierzGrafika3D<T>::Rozmiar; ++i) if (m[i] != 0) wynik = false;

	//skalowanie
	TWektor<T,4> wektor;
	T scaleFactor[3];
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
		scaleFactor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	TMacierzGrafika3D<T> macierzSkalowania = TMacierzGrafika3D<T>::Skalowanie(scaleFactor[0], scaleFactor[1], scaleFactor[2]);
	TWektor<T,4> wynikWektor = macierzSkalowania.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != scaleFactor[i] * wektor[i]) wynik = false;

	//translacja
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	T move[3];
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
		move[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	TMacierzGrafika3D<T> macierzTranslacji = TMacierzGrafika3D<T>::move(move[0], move[1], move[2]);
	wynikWektor = macierzTranslacji.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != wektor[i] + move[i]) wynik = false;

	//obr�t OZ o 0 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	TMacierzGrafika3D<T> macierzObrotuZ = TMacierzGrafika3D<T>::RotationZ(0);
	wynikWektor = macierzObrotuZ.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != wektor[i]) wynik = false;

	//obr�t OZ o 360 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuZ = TMacierzGrafika3D<T>::RotationZ(360);
	wynikWektor = macierzObrotuZ.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (fabs(wynikWektor[i] - wektor[i])>tolerancjaBledu) wynik = false;

	//obr�t OZ o 180 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuZ = TMacierzGrafika3D<T>::RotationZ(180);
	wynikWektor = macierzObrotuZ.PrzetransformowanyWektor(wektor);
	if (wynikWektor[2] != wektor[2]) wynik = false;
	if (fabs(wynikWektor[1] + wektor[1])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[0] + wektor[0])>tolerancjaBledu) wynik = false;

	//obr�t OZ o 90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuZ = TMacierzGrafika3D<T>::RotationZ(90);
	wynikWektor = macierzObrotuZ.PrzetransformowanyWektor(wektor);
	if (wynikWektor[2] != wektor[2]) wynik = false;
	if (fabs(wynikWektor[1] - wektor[0])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[0] + wektor[1])>tolerancjaBledu) wynik = false;

	//obr�t OZ o -90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuZ = TMacierzGrafika3D<T>::RotationZ(-90);
	wynikWektor = macierzObrotuZ.PrzetransformowanyWektor(wektor);
	if (wynikWektor[2] != wektor[2]) wynik = false;
	if (fabs(wynikWektor[1] + wektor[0])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[0] - wektor[1])>tolerancjaBledu) wynik = false;


	//obr�t OX o 0 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	TMacierzGrafika3D<T> macierzObrotuX = TMacierzGrafika3D<T>::RotationX(0);
	wynikWektor = macierzObrotuX.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != wektor[i]) wynik = false;

	//obr�t OX o 360 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuX = TMacierzGrafika3D<T>::RotationX(360);
	wynikWektor = macierzObrotuX.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (fabs(wynikWektor[i] - wektor[i])>tolerancjaBledu) wynik = false;

	//obr�t OX o 180 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuX = TMacierzGrafika3D<T>::RotationX(180);
	wynikWektor = macierzObrotuX.PrzetransformowanyWektor(wektor);
	if (wynikWektor[0] != wektor[0]) wynik = false;
	if (fabs(wynikWektor[1] + wektor[1])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[2] + wektor[2])>tolerancjaBledu) wynik = false;

	//obr�t OX o 90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuX = TMacierzGrafika3D<T>::RotationX(90);
	wynikWektor = macierzObrotuX.PrzetransformowanyWektor(wektor);
	if (wynikWektor[0] != wektor[0]) wynik = false;
	if (fabs(wynikWektor[2] - wektor[1])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[1] + wektor[2])>tolerancjaBledu) wynik = false;

	//obr�t OX o -90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuX = TMacierzGrafika3D<T>::RotationX(-90);
	wynikWektor = macierzObrotuX.PrzetransformowanyWektor(wektor);
	if (wynikWektor[0] != wektor[0]) wynik = false;
	if (fabs(wynikWektor[2] + wektor[1])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[1] - wektor[2])>tolerancjaBledu) wynik = false;

	//obr�t OY o 0 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	TMacierzGrafika3D<T> macierzObrotuY = TMacierzGrafika3D<T>::RotationY(0);
	wynikWektor = macierzObrotuY.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (wynikWektor[i] != wektor[i]) wynik = false;

	//obr�t OY o 360 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuY = TMacierzGrafika3D<T>::RotationY(360);
	wynikWektor = macierzObrotuY.PrzetransformowanyWektor(wektor);
	for (int i = 0; i < 3; ++i) if (fabs(wynikWektor[i] - wektor[i])>tolerancjaBledu) wynik = false;

	//obr�t OY o 180 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuY = TMacierzGrafika3D<T>::RotationY(180);
	wynikWektor = macierzObrotuY.PrzetransformowanyWektor(wektor);
	if (wynikWektor[1] != wektor[1]) wynik = false;
	if (fabs(wynikWektor[0] + wektor[0])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[2] + wektor[2])>tolerancjaBledu) wynik = false;

	//obr�t OY o 90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuY = TMacierzGrafika3D<T>::RotationY(90);
	wynikWektor = macierzObrotuY.PrzetransformowanyWektor(wektor);
	if (wynikWektor[1] != wektor[1]) wynik = false;
	if (fabs(wynikWektor[0] - wektor[2])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[2] + wektor[0])>tolerancjaBledu) wynik = false;

	//obr�t OY o -90 stopni
	for (int i = 0; i < 4; ++i)
	{
		wektor[i] = 0;
		wynikWektor[i] = 0;
	}
	for (int i = 0; i < 3; ++i)
	{
		wektor[i] = zakres*rand() / RAND_MAX;
	}
	wektor[3] = 1;
	macierzObrotuY = TMacierzGrafika3D<T>::RotationY(-90);
	wynikWektor = macierzObrotuY.PrzetransformowanyWektor(wektor);
	if (wynikWektor[1] != wektor[1]) wynik = false;
	if (fabs(wynikWektor[0] + wektor[2])>tolerancjaBledu) wynik = false;
	if (fabs(wynikWektor[2] - wektor[0])>tolerancjaBledu) wynik = false;

	//zgodno�� obrot�w OX
	T angle = 15;
	TMacierzGrafika3D<T> wzorzec = TMacierzGrafika3D<T>::RotationX(angle);
	TMacierzGrafika3D<T> compared = TMacierzGrafika3D<T>::RotationXYZ(angle, 0, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationZXZ(0, angle, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationAlongAxis(angle, 1, 0, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	
	//zgodno�� obrot�w OY
	wzorzec = TMacierzGrafika3D<T>::RotationY(angle);
	compared = TMacierzGrafika3D<T>::RotationXYZ(0, angle, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationAlongAxis(angle, 0, 1, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	
	//zgodno�� obrot�w OZ
	wzorzec = TMacierzGrafika3D<T>::RotationZ(angle);
	compared = TMacierzGrafika3D<T>::RotationXYZ(0, 0, angle); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationZXZ(angle, 0, 0); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationZXZ(0, 0, angle); if (!wzorzec.almostEqual(compared)) wynik = false;
	compared = TMacierzGrafika3D<T>::RotationAlongAxis(angle, 0, 0, 1); if (!wzorzec.almostEqual(compared)) wynik = false;


	//rzut izometryczny
	T l = -1;
	T r = 1;
	T b = (T)-0.71;
	T t = (T)0.71;
	T n = 1;
	T f = 10;
	TMacierzGrafika3D<T> macierzRzutu = TMacierzGrafika3D<T>::RzutIzometryczny(l, r, b, t, n, f);
	T elementyMacierzyWzorcowej[16];
	for (int i = 0; i < 16; ++i) elementyMacierzyWzorcowej[i] = 0;
	elementyMacierzyWzorcowej[0] = 2 / (r - l);
	elementyMacierzyWzorcowej[5] = 2 / (t - b);
	elementyMacierzyWzorcowej[10] = -2 / (f - n);
	elementyMacierzyWzorcowej[12] = -(r + l) / (r - l);
	elementyMacierzyWzorcowej[13] = -(t + b) / (t - b);
	elementyMacierzyWzorcowej[14] = -(f + n) / (f - n);
	elementyMacierzyWzorcowej[15] = 1;
	TMacierzGrafika3D<T> macierzWzorcowa(elementyMacierzyWzorcowej);
	for (int i = 0; i<TMacierzGrafika3D<T>::Rozmiar; ++i)
	{
		if (fabs(macierzRzutu[i] - macierzWzorcowa[i]) > tolerancjaBledu) wynik = false;
		if (fabs(macierzRzutu[i] - elementyMacierzyWzorcowej[i]) > tolerancjaBledu) wynik = false;
	}

	//rzut perspektywiczny
	macierzRzutu = TMacierzGrafika3D<T>::RzutPerspektywiczny(l, r, b, t, n, f);
	for (int i = 0; i < 16; ++i) elementyMacierzyWzorcowej[i] = 0;
	elementyMacierzyWzorcowej[0] = 2 * n / (r - l);
	elementyMacierzyWzorcowej[5] = 2 * n / (t - b);
	elementyMacierzyWzorcowej[8] = (r + l) / (r - l);
	elementyMacierzyWzorcowej[9] = (t + b) / (t - b);
	elementyMacierzyWzorcowej[10] = -(f + n) / (f - n);
	elementyMacierzyWzorcowej[11] = -1;
	elementyMacierzyWzorcowej[14] = -2 * n * f / (f - n);
	macierzWzorcowa.UstawElementy(elementyMacierzyWzorcowej);
	for (int i = 0; i<TMacierzGrafika3D<T>::Rozmiar; ++i)
	{
		if (fabs(macierzRzutu[i] - macierzWzorcowa[i]) > tolerancjaBledu) wynik = false;
		if (fabs(macierzRzutu[i] - elementyMacierzyWzorcowej[i]) > tolerancjaBledu) wynik = false;
	}

	//TMacierzGrafika3D<T> ig = TMacierzGrafika3D<T>::Jednostkowa*TMacierzGrafika3D<T>::OperatorGwiazdki(1, 0, 0);
	//if (ig.KopiaKolumny(0,))

	TMacierzGrafika3D<T> macierz = TMacierzGrafika3D<T>::RotationXYZ(10, 15, 20);
	TMacierzGrafika3D<T> macierzOdwrotna = macierz.Odwrotna();
	TMacierzGrafika3D<T> macierzTransponowana = macierz.Transponowana();
	TMacierzGrafika3D<T> roznica = macierzOdwrotna - macierzTransponowana;
	if (!macierzTransponowana.almostEqual(macierzOdwrotna, tolerancjaBledu)) wynik = false; //dla ortonormalnych odwrotna = transponowana
	TMacierzGrafika3D<T> macierzOdwrotna2 = macierzOdwrotna.Odwrotna();
	wynik = true;
	if (!macierzOdwrotna2.almostEqual(macierz, tolerancjaBledu)) wynik = false;

	return wynik;
}

#endif