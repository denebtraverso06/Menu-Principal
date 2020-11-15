#pragma once
#include "MyPantallaPrincipal.h"
#include "Ente.h"

using namespace System;
using namespace System::Drawing;

ref class MenuCreditos{
	Bitmap^ img;
public:
	MenuCreditos() {
		img = gcnew Bitmap("imagenes\\developingscreen.png");
	}
	void mostrar(Graphics^ g, RECTANGULO area_dibujo) {
		g->DrawImage(img, area_dibujo);
	}
};

