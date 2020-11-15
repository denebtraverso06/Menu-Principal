#pragma once
#include "Ente.h"

class Aliado : public Ente{
public:
	Aliado(Bitmap^ img) {
		x = y = 200;
		dx = dy = 0;
		ancho = img->Width / 6;
		alto = img->Height / 15;
	}

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

class AAliados {
	vector<Aliado*> Aliados;
	int cant_aliados;
public:
	AAliados(int cant_aliados, Bitmap^ img) {
		this->cant_aliados = cant_aliados;
		for (int i = 0; i < cant_aliados; i++) {
			Aliados.push_back(new Aliado(img));
		}
	}
	int getCantAliados() { return this->cant_aliados; }
	void Mover() {

	}
	void EliminarAliados() {

	}
};

