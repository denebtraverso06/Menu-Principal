#pragma once
#include "MC.h"
#include "Controladora.h"
#include "CEscenario.h"
#include "Movil.h"

namespace MenuPrincipal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class MyJuego : public System::Windows::Forms::Form
	{
		Graphics^ g;
		Controladora^ NovoJogo;

		Graphics^ graficador;
		BufferedGraphics^ buffer;
		BufferedGraphics^ buffer_escenario;
		CEscenario^ mi_escenario;
		CCaminos* caminos;
		Bitmap^ img_muro;
		Bitmap^ img_camino;
		CEnemigo* enemigo;
		Bitmap^ img_enemigo;

	private: System::Windows::Forms::Timer^ timer_animacion;
	public:
		MyJuego(void)
		{
			srand(time(NULL));
			InitializeComponent();

			this->g = CreateGraphics();
			this->NovoJogo = gcnew Controladora(g);
			
	/*		graficador = CreateGraphics();
			buffer = BufferedGraphicsManager::Current->Allocate(graficador, this->ClientRectangle);
			buffer_escenario = BufferedGraphicsManager::Current->Allocate(buffer->Graphics, this->ClientRectangle);*/
			caminos = new CCaminos;
			mi_escenario = gcnew CEscenario(caminos);
			img_muro = gcnew Bitmap("imagenes\\muro_juego.png");
			img_camino = gcnew Bitmap("imagenes\\newcamino.png");
			img_enemigo = gcnew Bitmap("imagenes\\corrupt.png");
			enemigo = new CEnemigo(caminos, 31, 31, 25, 25, 21, 13, 10);
		}

	protected:

		~MyJuego()
		{
			delete this->NovoJogo;
			delete this->g;
			if (components)
			{
				delete components;
			}
			delete enemigo;
			delete img_camino;
			delete img_enemigo;
			delete img_muro;
			delete mi_escenario;
			delete graficador;
			delete buffer;
			delete caminos;
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer_animacion = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer_animacion
			// 
			this->timer_animacion->Enabled = true;
			this->timer_animacion->Interval = 5;
			this->timer_animacion->Tick += gcnew System::EventHandler(this, &MyJuego::Animacion);
			// 
			// MyJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1379, 838);
			this->Name = L"MyJuego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyJuego";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyJuego::MyJuego_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyJuego::MyJuego_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Animacion(System::Object^ sender, System::EventArgs^ e) {
		BufferedGraphicsContext^ bfc = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = bfc->Allocate(g, this->ClientRectangle);

		bf->Graphics->Clear(Color::White);//
		//this->mi_escenario->mostrar_muros(bf->Graphics, this->img_muro);//
		this->mi_escenario->mostrar_celdas(bf->Graphics, this->img_camino);//

		this->enemigo->dibujar_meta(bf->Graphics);
		this->enemigo->animar(bf->Graphics, this->img_enemigo);
		//bf->Render();
		NovoJogo->Animar(bf->Graphics);

		bf->Render(g);
	}
	private: System::Void MyJuego_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		NovoJogo->MoverJugador(false, e->KeyCode);
	}
	private: System::Void MyJuego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		NovoJogo->MoverJugador(true, e->KeyCode);
	}
	};
}
