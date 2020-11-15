#pragma once
#include "Ente.h"
#include "CEscenario.h"

#define celda_width 32
#define celda_height 30

class CMovil{
protected:
	RECTANGULO area_dibujo, area_recorte, hitbox;
	int dx, dy, n_fil, n_col, n_sub_img, indice_col;
public:
	CMovil(int n_fil, int n_col) : n_fil(n_fil), n_col(n_col) {
		this->dx = this->dy = 0;
	}
	virtual void animar(Graphics^ g, Bitmap^ img) {}
	virtual void dibujar(Graphics^ g, Bitmap^ img) abstract;
};

//ENEMIGO V. MIGUEL (DESPUES VEMOS SI LO OTRO LO BORRAMOS O QUE)

enum Movimientos_enemigo {
	CaminarArriba_e = 8,
	CaminarIzquierda_e,
	CaminarAbajo_e,
	CaminarDerecha_e
};

class CEnemigo : public CMovil {
	int x, y, fin_f, fin_c;
	Movimientos_enemigo accion;
	vector<CCoord*> CaminoASeguir;
	int indice_caminos, indice = 0, dir, value_dir;
	bool finish, movible;
public:
	CEnemigo(CCaminos* escenario, int x, int y, int ancho, int alto, int n_fil, int n_col, int value_dir) :
		CMovil(n_fil, n_col), value_dir(value_dir) {
		indice_col = 0;
		area_dibujo = RECTANGULO(x, y, ancho, alto);
		escenario->get_pos(this->x, this->y);
		escenario->get_pos(fin_c, fin_f);
		camino(escenario, this->x, this->y, this->fin_f, this->fin_c);
		this->fin_c *= celda_width;
		this->fin_f *= celda_height;
		normalizar_dimensiones();
		this->x *= celda_width;
		this->y *= celda_height;
		this->area_dibujo.X = this->x;
		this->area_dibujo.Y = this->y;
		this->accion = CaminarDerecha_e;
		finish = false;
		//this->dx = this->dy = 0;
		this->hitbox = RECTANGULO(this->x, this->y, celda_width / 2, celda_height / 2);
		movible = true;
		//this->dx = 10;
	}
	~CEnemigo() {
		eliminar_camino();
	}
	void animar(Graphics^ g, Bitmap^ img) override {
		if (finish == false) {
			if (movible == true) {
				cambio_direccion();
			}
			mover_en_direccion();
			if (indice == 0) {
				finish = true;
			}
		}
		else {

		}
		dibujar(g, img);
	}
	void dibujar_meta(Graphics^ g) {
		for (int i = 1; i < CaminoASeguir.size(); ++i) {
			g->FillRectangle(Brushes::Green, RECTANGULO(CaminoASeguir[i]->x_t, CaminoASeguir[i]->y_t, celda_width, celda_height));
		}
	}
	bool get_finish() {
		return finish;
	}
	void dibujar(Graphics^ g, Bitmap^ img) override {
		setear_area_recorte(img);
		setear_hitbox();
		g->DrawImage(img, area_dibujo, area_recorte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Red, hitbox);
		++indice_col %= 9;
	}
private:
	void setear_hitbox() {
		hitbox.X = area_dibujo.X + area_dibujo.Width / 2;
		hitbox.Y = area_dibujo.Y + area_dibujo.Height / 2;
		hitbox.Width = area_dibujo.Width / 2;
		hitbox.Height = area_dibujo.Height / 2;
	}
	void setear_area_recorte(Bitmap^ img) {
		area_recorte.Width = img->Width / n_col;
		area_recorte.Height = img->Height / n_fil;
		area_recorte.X = indice_col * area_recorte.Width;
		area_recorte.Y = accion * area_recorte.Height;
	}
	bool estoy_en_la_posición(int x, int y) {
		return (RECTANGULO(x, y, celda_width, celda_height).Contains(this->hitbox.X, this->hitbox.Y) == true
			&& RECTANGULO(x, y, celda_width, celda_height).Contains(this->hitbox.X + hitbox.Width, this->hitbox.Y + hitbox.Height));
	}
	void normalizar_dimensiones() {
		for (int i = 0; i < CaminoASeguir.size(); ++i) {
			CaminoASeguir[i]->x_t *= celda_width;
			CaminoASeguir[i]->y_t *= celda_height;
		}
	}
	void eliminar_camino() {
		if (CaminoASeguir.empty() == false) {
			for (int i = 0; i < CaminoASeguir.size(); ++i) {
				delete CaminoASeguir[i];
			}
			CaminoASeguir.clear();
		}
	}
	void calcular_camino(CCaminos* escenario) {
		camino(escenario, this->x, this->y, this->fin_f, this->fin_c);
	}
	void mover_en_direccion() {
		if (estoy_en_la_posición(CaminoASeguir[indice]->x_t, CaminoASeguir[indice]->y_t) == false) {
			area_dibujo.X += dx;
			area_dibujo.Y += dy;
		}
		else {
			movible = true;
			indice = (indice + 1) % (indice_caminos);
		}
	}
	void cambio_direccion() {
		int distancia_x;
		int distancia_y;
		if (estoy_en_la_posición(CaminoASeguir[indice]->x_t, CaminoASeguir[indice]->y_t) == false) {
			distancia_x = pow(CaminoASeguir[indice]->x_t - hitbox.X, 2);
			distancia_y = pow(CaminoASeguir[indice]->y_t - hitbox.Y, 2);
			if (distancia_x > distancia_y) {
				distancia_x = CaminoASeguir[indice]->x_t - hitbox.X;
				if (distancia_x > 0) {
					dx = value_dir;
					dy = 0;
					dir = 1;//derecha
					movible = false;
				}
				else {
					if (distancia_x < 0) {
						dx = (value_dir * -1);
						dy = 0;
						dir = 2;//izquierda
						movible = false;
					}
				}
			}
			else {
				if (distancia_x < distancia_y) {
					distancia_y = CaminoASeguir[indice]->y_t - hitbox.Y;
					if (distancia_y > 0) {
						dx = 0;
						dy = value_dir;
						dir = 3;//abajo
						movible = false;
					}
					else {
						if (distancia_y < 0) {
							dx = 0;
							dy = (value_dir * -1);
							dir = 4;//arriba
							movible = false;
						}
					}
				}
			}
		}
	}
	bool seguro(CCaminos* escenario, int x, int y) {

		if (x >= 0 && x < M_size && y >= 0 && y < M_size && escenario->M[y][x] == 0 && HaSidoVisitado(x, y) == false) {
			return true;
		}
		return false;
	}
	bool camino(CCaminos* escenario, int x, int y, int finf, int finc) {
		if (x == finc && y == finf) {
			escenario->M[y][x] = 3;
			CaminoASeguir.push_back(new CCoord(x, y));
			indice_caminos = CaminoASeguir.size();
			finish = false;
			indice = 1;
			return true;
		}
		if (seguro(escenario, x, y) == true) {
			CaminoASeguir.push_back(new CCoord(x, y));
			escenario->M[y][x] = 3;
			if (camino(escenario, x + 1, y, finf, finc) == true)
				return true;
			if (camino(escenario, x - 1, y, finf, finc) == true)
				return true;
			if (camino(escenario, x, y - 1, finf, finc) == true)
				return true;
			if (camino(escenario, x, y + 1, finf, finc) == true)
				return true;
			escenario->M[y][x] = 0;
			CaminoASeguir.pop_back();
			return false;
		}
		return false;
	}
	bool HaSidoVisitado(int x, int y) {
		for (int i = 0; i < CaminoASeguir.size(); ++i) {
			if (CaminoASeguir[i]->x_t == x && CaminoASeguir[i]->y_t == y) {
				return true;
				break;
			}
		}
		return false;
	}
};