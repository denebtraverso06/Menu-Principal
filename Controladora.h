#pragma once
#include "MC.h"
#include "Corrupto.h"
#include "Aliado.h"
#include "Ente.h"
#include "Asesino.h"

ref class Controladora{
	MC* jugador;

	Bitmap^ imgJugador;
public:
	Controladora(Graphics^ g) {
		this->imgJugador = gcnew Bitmap("imagenes\\mc.png");
		this->jugador = new MC(imgJugador);
	}
	~Controladora() {
		delete this->jugador;
	}
	void MoverJugador(bool accion, Keys key)
	{
		if (accion == true)
		{
			if (key == Keys::W)
			{
				jugador->setDY(-5);
				jugador->SetAccion(CaminarArriba);
			}
			else if (key == Keys::S)
			{
				jugador->setDY(5);
				jugador->SetAccion(CaminarAbajo);
			}
			else if (key == Keys::A)
			{
				jugador->setDX(-5);
				jugador->SetAccion(CaminarIzquierda);
			}
			else if (key == Keys::D)
			{
				jugador->setDX(5);
				jugador->SetAccion(CaminarDerecha);
			}
		}
		else
		{
			if (key == Keys::W)
				jugador->setDY(0);
			else if (key == Keys::S)
				jugador->setDY(0);
			else if (key == Keys::A)
				jugador->setDX(0);
			else if (key == Keys::D)
				jugador->setDX(0);
		}
	}
	void Animar(Graphics^ g) {
		jugador->dibujar(g, imgJugador);
		jugador->Movimiento(g);

	}
};

