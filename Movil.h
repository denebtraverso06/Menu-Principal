#pragma once
#include "Ente.h"
#include "CEscenario.h"
#include "MC.h"
class CMovil { //////// creo que se debe borrar
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

enum Movimientos_enemigo {
	estirar_arriba,
	estirar_izquierda,
	estirar_frente,
	estirar_derecha,

	ataca_arriba_e,
	ataca_izquierda_e,
	ataca_frente_e,
	ataca_derecha_e,

	camina_arriba_e,
	camina_izquierda_e,
	camina_abajo_e,
	camina_derecha_e,

	sacas_arriba_e,
	sacas_izquierda_e,
	sacas_frente_e,
	sacas_derecha_e,

	apunta_arriba_e,
	apunta_izquierda_e,
	apunta_frente_e,
	apunta_derecha_e,

	muere_e
};

class CEnemigo : public CMovil {
	int x, y, fin_f, fin_c, fin_c_matriz, fin_f_matriz;
	Movimientos_enemigo accion;
	vector<CCoord*> CaminoASeguir;
	int indice_caminos, indice = 0, dir, value_dir;
	bool finish, movible;
	int IDx;
public:
	CEnemigo(CCaminos* escenario, int x, int y, int ancho, int alto, int n_fil, int n_col, int value_dir, int fin_c, int fin_f) :
		CMovil(n_fil, n_col), value_dir(value_dir), fin_c(fin_c), fin_f(fin_f) {
		fin_f_matriz = fin_f;
		fin_c_matriz = fin_c;
		IDx = 0;
		indice_col = 0;
		area_dibujo = RECTANGULO(x, y, ancho, alto);
		escenario->get_pos(this->x, this->y);
		//escenario->get_pos(fin_c, fin_f);
		camino(escenario, this->x, this->y, this->fin_f, this->fin_c);
		this->fin_c *= celda_width;
		this->fin_f *= celda_height;
		normalizar_dimensiones();
		this->x *= celda_width;
		this->y *= celda_height;
		this->area_dibujo.X = this->x;
		this->area_dibujo.Y = this->y;
		this->accion = camina_abajo_e;
		finish = false;
		//this->dx = this->dy = 0;
		this->hitbox = RECTANGULO(this->x, this->y, celda_width / 2, celda_height / 2);
		movible = true;
		
		accion = camina_abajo_e;
		//this->dx = 10;
	}
	~CEnemigo() {
		eliminar_camino();
	}
	void cambiar_objetivo(MC* jugador, CEscenario^ escenario, CCaminos* caminos) {
		jugador->get_pos_matriz(escenario);
		if (fin_f_matriz != jugador->get_y_matriz() || fin_c_matriz != jugador->get_x_matriz()) {
			fin_f_matriz = jugador->get_y_matriz();
			fin_c_matriz = jugador->get_x_matriz();
			determinar_posicion_matriz(escenario);
			eliminar_posiciones();
			fin_f = fin_f_matriz;
			fin_c = fin_c_matriz;
			camino(caminos, this->x, this->y, fin_f, fin_c);
			this->fin_c *= celda_width;
			this->fin_f *= celda_height;
			normalizar_dimensiones();
			this->x *= celda_width;
			this->y *= celda_height;
			this->area_dibujo.X = this->x;
			this->area_dibujo.Y = this->y;
			this->dx = dy = 0;
			//imprimir_pos();

		}
	}
	void determinar_posicion_matriz(CEscenario^ escenario) {
		x = hitbox.X;
		y = hitbox.Y;
		escenario->determinar_ubicacion_personaje(x, y);
		x;
		y;

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
	void imprimir_pos() {
		for (int i = 1; i < CaminoASeguir.size(); ++i) {
			cout << "X: " << CaminoASeguir[i]->x_t << " Y: " << CaminoASeguir[i]->y_t << endl;
		}
	}
	bool get_finish() {
		return finish;
	}
	void dibujar(Graphics^ g, Bitmap^ img) override {
		//setear_area_recorte(img);
		//setear_hitbox();
		//g->DrawImage(img, area_dibujo, area_recorte, GraphicsUnit::Pixel);
		//g->DrawRectangle(Pens::Red, hitbox);
		//++indice_col %= 9;

		setear_area_recorte(img);
		setear_hitbox();
		g->DrawImage(img, area_dibujo, area_recorte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Red, hitbox);

		if (accion >= estirar_arriba && accion <= estirar_derecha) {
			IDx = (IDx + 1) % 7;
		}
		else if (accion >= camina_arriba_e && accion <= camina_derecha_e && (dx != 0 || dy != 0)) {

			IDx = (IDx + 1) % 8;
		}
		else if (accion >= ataca_arriba_e && accion <= ataca_derecha_e) {
			IDx = (IDx + 1) % 9;
			if (IDx == 0) {
				if (accion == ataca_arriba_e)
					accion = camina_arriba_e;
				else if (accion == ataca_derecha_e)
					accion = camina_derecha_e;
				else if (accion == ataca_frente_e)
					accion = camina_abajo_e;
				else if (accion == ataca_izquierda_e)
					accion == camina_izquierda_e;
			}
		}
		else if (accion >= sacas_arriba_e && accion <= sacas_derecha_e) {
			IDx = (IDx + 1) % 6;
		}
		else if (accion >= apunta_arriba_e && accion <= apunta_derecha_e) {
			IDx = (IDx + 1) % 13;
		}
		else if (accion == muere_e) {
			IDx = (IDx + 1) % 1;
		}
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
			&& RECTANGULO(x, y, celda_width, celda_height).Contains(this->hitbox.X + hitbox.Width, this->hitbox.Y + hitbox.Height) == true);
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
	void eliminar_posiciones() {
		if (CaminoASeguir.empty() == false) {
			for (int i = 0; i < CaminoASeguir.size(); ++i) {
				CaminoASeguir.erase(CaminoASeguir.begin() + 1);
			}
			CaminoASeguir.clear();
		}
	}
	void SetAccion(Movimientos_enemigo value) {
		if (accion != value) {
			IDx = 0;
		}
		accion = value;
	}
	Movimientos_enemigo GetAccion() {
		return accion;
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
					SetAccion(camina_derecha_e);
					cout << "pa derecha" << endl; ////////
				}
				else {
					if (distancia_x < 0) {
						dx = (value_dir * -1);
						dy = 0;
						dir = 2;//izquierda
						movible = false;
						SetAccion(camina_izquierda_e);
						cout << "pa izquierda" << endl; ////////
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
						SetAccion(camina_abajo_e);
						cout << "pa abajo" << endl; ////////
					}
					else {
						if (distancia_y < 0) {
							dx = 0;
							dy = (value_dir * -1);
							dir = 4;//arriba
							movible = false;
							SetAccion(camina_arriba_e);
							cout << "pa arriba" << endl; ////////
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
			//escenario->M[y][x] = 3;
			CaminoASeguir.push_back(new CCoord(x, y));
			indice_caminos = CaminoASeguir.size();
			finish = false;
			indice = 0;
			movible = true;
			return true;
		}
		if (seguro(escenario, x, y) == true) {
			CaminoASeguir.push_back(new CCoord(x, y));
			//escenario->M[y][x] = 3;
			if (camino(escenario, x + 1, y, finf, finc) == true)
				return true;
			if (camino(escenario, x - 1, y, finf, finc) == true)
				return true;
			if (camino(escenario, x, y - 1, finf, finc) == true)
				return true;
			if (camino(escenario, x, y + 1, finf, finc) == true)
				return true;
			//escenario->M[y][x] = 0;
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