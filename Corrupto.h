#pragma once
#include "Ente.h"


enum DireccionesC
{
	DispararArribaC,
	DispararIzquierdaC,
	DispararAbajoC,
	DispararDerechaC,

	PalaArribaC,
	PalaIzquierdaC,
	PalaAbajoC,
	PalaDerechaC,

	CaminarArribaC,
	CaminarIzquierdaC,
	CaminarAbajoC,
	CaminarDerechaC,

	AtacarArribaC,
	AtacarAbajoC,
	AtacarIzqC,
	AtacarDerechaC,

	FlechaArribaC,
	FlechaAbajoC,
	FlechaIzqC,
	FlechaDerechaC,

	MorirC
};

class Corrupt : public Ente{
	DireccionesC accionC;
public:
	Corrupt(Bitmap^ img) {
		x = y = 200;
		dx = dy = 0;
		ancho = img->Width / 13;
		alto = img->Height / 21;

		accionC = CaminarAbajoC;
	}

	void SetAccionC(DireccionesC mov) {
		accionC = mov;
	}
	void dibujar(Graphics^ g, Bitmap^ img) override {
		RECTANGULO corte = RECTANGULO(IDx * ancho, accionC * alto, ancho, alto);
		g->DrawImage(img, AreaActual(), corte, GraphicsUnit::Pixel);
		//area_recorte();
	}
	void Movimiento(Graphics^ g)override { //falta Mundo^ mundo
		if (x + dx >= 0 && x + dx + ancho < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + dy + alto < g->VisibleClipBounds.Height)
			y += dy;
	}
	void Camuflaje(Graphics^ g, Bitmap^ img) {

	}
private:
	/*
	RECTANGULO area_recorte() {
		//if()
	}
	*/
};



