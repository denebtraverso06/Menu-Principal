#pragma once
#include "Ente.h"
#include "Aliado.h"

class Assasin :public Ente{
public:
	Assasin(Bitmap^ img) {
		x = y = 200;
		dx = dy = 0;
		ancho = img->Width / 6;
		alto = img->Height / 15;

		//accion = CaminarAbajo;

	}
	//void SetAccion(MovimientoJugador mov) {
		//accion = mov;
	//}
	void dibujar(Graphics^ g, Bitmap^ img) override {
		//RECTANGULO corte = RECTANGULO(IDx * ancho, accion * alto, ancho, alto);
		//g->DrawImage(img, AreaActual(), corte, GraphicsUnit::Pixel);
		//area_recorte();
	}
	void Movimiento(Graphics^ g)override { //falta Mundo^ mundo
		if (x + dx >= 0 && x + dx + ancho < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + dy + alto < g->VisibleClipBounds.Height)
			y += dy;
	}
private:
	/*
RECTANGULO area_recorte() {
	//if()
}
*/
};

class AAssasins {
	vector<Assasin*> Asesinos;
	int cant_asesinos;
public:
	AAssasins(AAliados aliado, Bitmap^ img) {
		this->cant_asesinos = (aliado.getCantAliados() * 60) / 100;
		for (int i = 0; i < cant_asesinos; i++) {
			Asesinos.push_back(new Assasin(img));
		}
	}
	void mover() {

	}
	void suplantar(Bitmap^ img) {

	}
private:
	void Aestrella() {

	}
};



