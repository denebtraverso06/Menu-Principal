#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <math.h>
#include "Ente.h"
using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

#define aleatorio(inicio,fin) inicio+rand()%((fin-inicio)+1)
#define width 25
#define height 25
#define M_size 23
#define m_size 11
#define celda_width 32
#define celda_height 30
ref class CGrafico {
protected:
	RECTANGULO area_dibujo;
	int x, y, dx, dy;
public:
	CGrafico(RECTANGULO area_dibujo) : area_dibujo(area_dibujo) {
		this->dx = this->dy = 0;
	}
	virtual void dibujar(Graphics^ g, Bitmap^ img) {}
	int get_x() {
		return area_dibujo.X;
	}
	int get_y() {
		return area_dibujo.Y;
	}
	void set_x(int x) {
		this->x = x;
	}
	void set_y(int y) {
		this->y = y;
	}
};

ref class CMuro : public CGrafico {
public:
	CMuro(RECTANGULO area_dibujo) : CGrafico(area_dibujo) {}
	void dibujar(Graphics^ g, Bitmap^ imagen) override {
		g->DrawImage(imagen, this->area_dibujo);
	}
};

ref class CCelda : public CGrafico {
public:
	CCelda(RECTANGULO area_dibujo) : CGrafico(area_dibujo) {}
	void dibujar(Graphics^ g, Bitmap^ imagen) override {
		g->DrawImage(imagen, this->area_dibujo);
	}
	bool contiene_a_un_personaje(int x, int y) {
		return (this->area_dibujo.Contains(x, y));
	}
};

class CCoord {
public:
	int x, y, x_t, y_t;
	bool visit;
	CCoord(int x, int y, int x_t, int y_t) : x(x), y(y), x_t(x_t), y_t(y_t) {
		this->visit = false;
	}
	CCoord(int x_t, int y_t) : x_t(x_t), y_t(y_t) {}
	bool visited(int x, int y) {
		return (this->x == x && this->y == y);
	}
};

class CCaminos {
public:
	int** M;
private:
	CCoord*** m;
	CCoord* guidecell;
	vector<CCoord*> visitedcells;
	int i_m;
	int j_m;
public:
	CCaminos() {
		i_m = 0;
		j_m = 0;
		reservar_M();
		reservar_m();
		setear_M();
		guidecell = m[0][2];
		visitedcells.push_back(new CCoord(guidecell->x, guidecell->y, guidecell->x_t, guidecell->y_t));
		while (terminar() == false) {
			mov(guidecell);
		}
	}
	~CCaminos() {
		eliminar_M();
		eliminar_m();
		eliminar_visitedcells();
		guidecell = nullptr;
	}
private:
	void setear_M() {
		for (int i = 0; i < M_size; ++i) {
			for (int j = 0; j < M_size; ++j) {
				if ((i % 2) != 0 && (j % 2) != 0 && i != 0 && j != 0) {
					inicializar_m(i, j);
				}
				M[i][j] = 1;
			}
		}
	}
public:
	bool es_camino(int x, int y) {
		return (M[y][x] == 0);
	}
	void get_pos(int& x, int& y) {
		int x1, y1;
		while (true) {
			x1 = aleatorio(0, M_size - 1);
			y1 = aleatorio(0, M_size - 1);
			if (M[y1][x1] == 0) {
				x = x1;
				y = y1;
				break;
			}
		}
	}
private:
	void mov(CCoord* obj) {
		vector<int*> nros;
		if (validar_y(obj->y - 1) == true && visitado(obj->x, obj->y - 1) == false && m[obj->y - 1][obj->x]->visit == false) {
			int* num = new int;
			*num = 1;
			nros.push_back(num);
		}
		if (validar_y(obj->y + 1) == true && visitado(obj->x, obj->y + 1) == false && m[obj->y + 1][obj->x]->visit == false) {
			int* num = new int;
			*num = 2;
			nros.push_back(num);
		}
		if (validar_x(obj->x - 1) == true && visitado(obj->x - 1, obj->y) == false && m[obj->y][obj->x - 1]->visit == false) {
			int* num = new int;
			*num = 3;
			nros.push_back(num);
		}
		if (validar_x(obj->x + 1) == true && visitado(obj->x + 1, obj->y) == false && m[obj->y][obj->x + 1]->visit == false) {
			int* num = new int;
			*num = 4;
			nros.push_back(num);
		}
		if (nros.size() == 0) {
			if (terminar() == false) {
				m[obj->y][obj->x]->visit = true;
				visitedcells.pop_back();
				guidecell->x = visitedcells[visitedcells.size() - 1]->x;
				guidecell->y = visitedcells[visitedcells.size() - 1]->y;
				guidecell->x_t = visitedcells[visitedcells.size() - 1]->x_t;
				guidecell->y_t = visitedcells[visitedcells.size() - 1]->y_t;
				mov(guidecell);
				for (int i = 0; i < nros.size(); ++i) { delete nros[i]; }
				nros.clear();
			}
			else {
				for (int i = 0; i < nros.size(); ++i) { delete nros[i]; }
				nros.clear();
			}
		}
		else {
			int r = aleatorio(0, nros.size() - 1);
			int r1 = *nros[r];
			m[obj->y][obj->x]->visit = true;
			switch (r1) {
			case 1:
				definir_caminos(obj->x_t, obj->y_t, m[obj->y - 1][obj->x]->x_t, m[obj->y - 1][obj->x]->y_t, r1);
				visitedcells.push_back(new CCoord(m[obj->y - 1][obj->x]->x, m[obj->y - 1][obj->x]->y, m[obj->y - 1][obj->x]->x_t, m[obj->y - 1][obj->x]->y_t));
				guidecell = nullptr;
				guidecell = m[obj->y - 1][obj->x];
				break;
			case 2:
				definir_caminos(obj->x_t, obj->y_t, m[obj->y + 1][obj->x]->x_t, m[obj->y + 1][obj->x]->y_t, r1);
				visitedcells.push_back(new CCoord(m[obj->y + 1][obj->x]->x, m[obj->y + 1][obj->x]->y, m[obj->y + 1][obj->x]->x_t, m[obj->y + 1][obj->x]->y_t));
				guidecell = nullptr;
				guidecell = m[obj->y + 1][obj->x];
				break;
			case 3:
				definir_caminos(obj->x_t, obj->y_t, m[obj->y][obj->x - 1]->x_t, m[obj->y][obj->x - 1]->y_t, r1);
				visitedcells.push_back(new CCoord(m[obj->y][obj->x - 1]->x, m[obj->y][obj->x - 1]->y, m[obj->y][obj->x - 1]->x_t, m[obj->y][obj->x - 1]->y_t));
				guidecell = nullptr;
				guidecell = m[obj->y][obj->x - 1];
				break;
			case 4:
				definir_caminos(obj->x_t, obj->y_t, m[obj->y][obj->x + 1]->x_t, m[obj->y][obj->x + 1]->y_t, r1);;
				visitedcells.push_back(new CCoord(m[obj->y][obj->x + 1]->x, m[obj->y][obj->x + 1]->y, m[obj->y][obj->x + 1]->x_t, m[obj->y][obj->x + 1]->y_t));

				guidecell = nullptr;
				guidecell = m[obj->y][obj->x + 1];
				break;
			}
			for (int i = 0; i < nros.size(); ++i) { delete nros[i]; }
			nros.clear();
		}
	}
	void definir_caminos(int x, int y, int x1, int y1, int dir) {
		switch (dir) {
		case 4:
			for (int j = x; j <= x1; ++j) {
				M[y][j] = 0;
			}
			break;
		case 3:
			for (int j = x; j >= x1; --j) {
				M[y][j] = 0;
			}
			break;
		case 1:
			for (int i = y; i >= y1; --i) {
				M[i][x] = 0;
			}
			break;
		case 2:
			for (int i = y; i <= y1; ++i) {
				M[i][x] = 0;
			}
		}
	}
	bool validar_x(int x) {
		return (x >= 0 && x <= (m_size - 1));
	}
	bool validar_y(int y) {
		return (y >= 0 && y <= (m_size - 1));
	}
	bool visitado(int x, int y) {
		for (int i = 0; i < visitedcells.size(); ++i) {
			if (visitedcells[i]->visited(x, y) == true) {
				return true;
				break;
			}
		}
		return false;
	}
	bool terminar() {
		int cont = 0;
		for (int i = 0; i < m_size; ++i) {
			for (int j = 0; j < m_size; ++j) {
				if (m[i][j]->visit == true) {
					++cont;
				}
			}
		}
		if (cont == (m_size * m_size)) {
			return true;
		}
		else {
			return false;
		}
	}
	void inicializar_m(int i_M, int j_M) {
		m[i_m][j_m] = new CCoord(j_m, i_m, j_M, i_M);
		j_m = (j_m + 1) % m_size;
		if (j_m == 0) {
			++i_m;
		}
	}
	void reservar_M() {
		M = new int* [M_size];
		for (int i = 0; i < M_size; ++i) {
			M[i] = new int[M_size];
		}
	}
	void reservar_m() {
		m = new CCoord * *[m_size];
		for (int i = 0; i < m_size; ++i) {
			m[i] = new CCoord * [m_size];
		}
	}
	void eliminar_M() {
		for (int i = 0; i < M_size; ++i) {
			delete[] M[i];
		}
		delete[] M;
	}
	void eliminar_m() {
		for (int i = 0; i < m_size; ++i) {
			for (int j = 0; j < m_size; ++j) {
				delete m[i][j];
			}
			delete m[i];
		}
		delete m;
	}
	void eliminar_visitedcells() {
		for (int i = 0; i < visitedcells.size(); ++i) {
			delete visitedcells[i];
		}
		visitedcells.clear();
	}
};

ref class CEscenario {
	int** mapa;
	List<CMuro^> muros;
	List<CCelda^> celdas_libres;
public:
	CEscenario(CCaminos* caminos) {
		dibujar_muro(caminos);
	}
	~CEscenario() {
		for (int i = 0; i < muros.Count; ++i) {
			delete muros[i];
		}
		muros.Clear();
		for (int i = 0; i < celdas_libres.Count; ++i) {
			delete celdas_libres[i];
		}
		celdas_libres.Clear();
	}
	void mostrar_muros(Graphics^ g, Bitmap^ img) {
		for (int i = 0; i < muros.Count; ++i) {
			muros[i]->dibujar(g, img);
		}
	}
	void determinar_ubicacion_personaje(int& x, int& y) {
		int x1 = x;
		int y1 = y;
		for (int i = 0; i < celdas_libres.Count; ++i) {
			if (celdas_libres[i]->contiene_a_un_personaje(x1, y1)) {
				x = celdas_libres[i]->get_x() / celda_width;
				y = celdas_libres[i]->get_y() / celda_height;
				break;
			}
		}
	}
	void mostrar_celdas(Graphics^ g, Bitmap^ img) {
		for (int i = 0; i < celdas_libres.Count; ++i) {
			celdas_libres[i]->dibujar(g, img);
		}
	}
	RECTANGULO celda_libre(int x, int y) {
		return RECTANGULO(x, y, 32, 30);
	}
private:
	void dibujar_muro(CCaminos* caminos) {
		int x = 0; int y = 0;
		for (int i = 0; i < M_size; ++i) {
			for (int j = 0; j < M_size; ++j) {
				if (caminos->M[i][j] == 1) {
					muros.Add(gcnew CMuro(RECTANGULO(x, y, 32, 30)));
				}
				else {
					celdas_libres.Add(gcnew CCelda(RECTANGULO(x, y, 32, 30)));
				}
				x += 32;
			}
			y += 30;
			x = 0;
		}
	}
};
