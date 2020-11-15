#pragma once
#include "MC.h"
#include "Corrupto.h"
#include "Aliado.h"
#include "Ente.h"
#include "Asesino.h"
#include "CEscenario.h"
#include "Movil.h"

ref class Controladora {
	MC* jugador;
	CEscenario^ mi_escenario;
	CCaminos* caminos;
	CEnemigo* corrupt;
	CEnemigo* assasin;
	CEnemigo* aliado; //esto se va a cambiar, habria que llamar a la clase CEnemigo CSeeker (buscador) o CMovimiento 


	Bitmap^ imgJugador;
	Bitmap^ img_muro;
	Bitmap^ img_camino;
	Bitmap^ img_corrupt;
	Bitmap^ img_assasin;
	Bitmap^ img_aliado;

public:
	Controladora(Graphics^ g) {
		this->imgJugador = gcnew Bitmap("imagenes\\mc.png");
		this->jugador = new MC(imgJugador);
		this->caminos = new CCaminos;
		this->mi_escenario = gcnew CEscenario(caminos);
		jugador->get_pos_matriz(mi_escenario);
		//int c = jugador->get_x_matriz();
		//int f = jugador->get_y_matriz();
		this->corrupt = new CEnemigo(caminos, 31, 31, 25, 25, 21, 13, 10, jugador->get_x_matriz(), jugador->get_y_matriz());
		this->assasin = new CEnemigo(caminos, 35, 35, 25, 25, 21, 13, 10, jugador->get_x_matriz(), jugador->get_y_matriz());
		//this->assasin = new CEnemigo(caminos, jugador->get_x_matriz(), jugador->get_y_matriz(), 25, 25, 21, 13, 10, jugador->get_x_matriz(), jugador->get_y_matriz());/////////7
		this->aliado = new CEnemigo(caminos, 35, 35, 25, 25, 21, 13, 10, jugador->get_x_matriz(), jugador->get_y_matriz());
		this->img_corrupt = gcnew Bitmap("imagenes\\corrupt.png"); // ''        ''         '' ''     ''     ''    ''    ''/////
		this->img_assasin = gcnew Bitmap("imagenes\\assasin.png"); //hacer implementacion de las clases (crear clase padre)
		this->img_aliado = gcnew Bitmap("imagenes\\aliado.png"); /////////////////////////////////////////////////////////////
		this->img_muro = gcnew Bitmap("imagenes\\muro_juego.png");
		this->img_camino = gcnew Bitmap("imagenes\\newcamino.png");
		this->img_corrupt = gcnew Bitmap("imagenes\\corrupt.png");
	}
	~Controladora() {
		delete this->jugador, this->imgJugador,
			this->corrupt, this->img_corrupt,
			this->assasin, this->img_assasin,
			this->aliado, this->img_aliado,
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
	void Animar_escenario(Graphics^ g) {
		mi_escenario->mostrar_muros(g, img_muro);
		mi_escenario->mostrar_celdas(g, img_camino);
	}
	void Animar_personajes(Graphics^ g) {
		corrupt->cambiar_objetivo(jugador, mi_escenario, caminos);
		assasin->cambiar_objetivo(jugador, mi_escenario, caminos);
		aliado->cambiar_objetivo(jugador, mi_escenario, caminos);

		this->corrupt->dibujar_meta(g);

		if (jugador->getDX() != 0 || jugador->getDY() != 0) {
			corrupt->cambiar_objetivo(jugador, mi_escenario, caminos);
		}
		if (jugador->getDX() != 0 || jugador->getDY() != 0) {
			assasin->cambiar_objetivo(jugador, mi_escenario, caminos);
		}
		if (jugador->getDX() != 0 || jugador->getDY() != 0) {
			aliado->cambiar_objetivo(jugador, mi_escenario, caminos); 
		}

		this->corrupt->animar(g, this->img_corrupt);
		this->assasin->animar(g, this->img_assasin);
		this->aliado->animar(g, this->img_aliado);

		jugador->Movimiento(g);
		jugador->dibujar(g, imgJugador);
	}
};

