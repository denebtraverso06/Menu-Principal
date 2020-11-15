#pragma once
#include "MC.h"
#include "Controladora.h"

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
	private: System::Windows::Forms::Timer^ timer_animacion;
	public:
		MyJuego(void)
		{
			InitializeComponent();
			this->g = CreateGraphics();
			this->NovoJogo = gcnew Controladora(g);
		}

	protected:

		~MyJuego()
		{
			delete this->NovoJogo;
			if (components)
			{
				delete components;
			}
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
			this->timer_animacion->Tick += gcnew System::EventHandler(this, &MyJuego::Animacion);
			// 
			// MyJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1006, 701);
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

		bf->Graphics->Clear(Color::White);
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
