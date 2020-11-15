#pragma once
#include "Ente.h"

enum Direcciones
{
	DispararArriba,
	DispararIzquierda,
	DispararAbajo,
	DispararDerecha,

	PalaArriba,
	PalaIzquierda,
	PalaAbajo,
	PalaDerecha,

	CaminarArriba,
	CaminarIzquierda,
	CaminarAbajo,
	CaminarDerecha,

	AtacarArriba,
	AtacarAbajo,
	AtacarIzq,
	AtacarDerecha,

	FlechaArriba,
	FlechaAbajo,
	FlechaIzq,
	FlechaDerecha,

	Morir
};

class MC :public Ente{
	Direcciones accion;
public:
	MC(Bitmap^ img) {
		x = 30 ;
		y = 30 ;
		dx = dy = 0;
		ancho = img->Width / 13;
		alto = img->Height / 21;

		accion = CaminarAbajo;

	}
	void SetAccion(Direcciones mov) {
		accion = mov;
	}
	Direcciones getAccion() {
		return accion;
	}
	void dibujar(Graphics^ g, Bitmap^ img) override {
		RECTANGULO corte = RECTANGULO(IDx * ancho, accion * alto, ancho, alto);
		RECTANGULO decremento = RECTANGULO(x, y, ancho * 0.6, alto * 0.6);
		//RECTANGULO hitbox = RECTANGULO( x + (ancho*0.5) / 2, y + (alto * 0.5) / 2, ancho, alto);
		//g->DrawImage(img, AreaActual(), corte, GraphicsUnit::Pixel);
		g->DrawImage(img, decremento, corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Black, decremento);
		g->DrawRectangle(Pens::Red, HitBox());
		//g->DrawRectangle(Pens::Black, AreaActual());
	}
	void Movimiento(Graphics^ g)override { //falta Mundo^ mundo
		if (x + dx >= 0 && x + dx + ancho < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + dy + alto < g->VisibleClipBounds.Height)
			y += dy;

		this->EjecutarAccion();

	}
private:
	void EjecutarAccion() {

		if (accion >= DispararArriba && accion <= DispararDerecha)
			IDx = (IDx + 1) % 7;
		else if (accion >= PalaArriba && accion <= PalaDerecha)
			IDx = (IDx + 1) % 8;
		else if (accion >= CaminarArriba && accion <= CaminarDerecha && (dx != 0 || dy != 0))
			IDx = (IDx + 1) % 9;
		else if (accion >= AtacarArriba && accion <= AtacarDerecha)
		{
			IDx = (IDx + 1) % 6;

			if (IDx == 0)
			{
				if (accion == AtacarArriba)
					accion = CaminarArriba;
				else if (accion == AtacarAbajo)
					accion = CaminarAbajo;
				else if (accion == AtacarIzq)
					accion = CaminarIzquierda;
				else if (accion == AtacarDerecha)
					accion = CaminarDerecha;
			}
		}
		else if (accion == Morir)
			IDx = (IDx + 1) % 6;
	}
};

