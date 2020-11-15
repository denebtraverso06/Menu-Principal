#pragma once
#include "MC.h"
#include "Corrupto.h"
#include "Aliado.h"
#include "Ente.h"
#include "Asesino.h"
#include "CEscenario.h"
#include "Movil.h"

ref class Controladora{
	MC* jugador;
	CEscenario^ mi_escenario;
	CCaminos* caminos;
	CEnemigo* enemigo;

	Bitmap^ imgJugador;
	Bitmap^ img_muro;
	Bitmap^ img_camino;
	Bitmap^ img_enemigo;

public:
	Controladora(Graphics^ g) {
		this->imgJugador = gcnew Bitmap("imagenes\\mc.png");
		this->jugador = new MC(imgJugador);
	/*	this->enemigo = new CEnemigo(caminos, 31, 31, 25, 25, 21, 13, 10);
		this->img_enemigo = gcnew Bitmap("imagenes\\corrupt.png");*/
		
		/*this->caminos = new CCaminos;
		this->mi_escenario = gcnew CEscenario(caminos);
		this->img_muro = gcnew Bitmap("imagenes\\muro_juego.png");
		this->img_camino = gcnew Bitmap("imagenes\\newcamino.png");
		this->img_enemigo = gcnew Bitmap("imagenes\\corrupt.png");*/
	}
	~Controladora() {
		delete this->jugador, this->imgJugador,
			this->enemigo, this->img_enemigo,
			this->caminos, this->img_camino,
			this->img_muro, this->mi_escenario;
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

		//mi_escenario->mostrar_muros(g, img_muro);
		//mi_escenario->mostrar_celdas(g, img_camino);
		/*enemigo->animar(g, img_enemigo);*/
		//this->enemigo->dibujar_meta(g);
		//this->enemigo->animar(g, this->img_enemigo);
		jugador->Movimiento(g);
		jugador->dibujar(g, imgJugador);

	}
};

