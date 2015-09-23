#pragma once
#include "game.h"

namespace Nexus {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			initBoard();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  restart;
	private: System::Windows::Forms::Button^  next;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->restart = (gcnew System::Windows::Forms::Button());
			this->next = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(451, 451);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// restart
			// 
			this->restart->Location = System::Drawing::Point(469, 12);
			this->restart->Name = L"restart";
			this->restart->Size = System::Drawing::Size(75, 23);
			this->restart->TabIndex = 1;
			this->restart->Text = L"Restart";
			this->restart->UseVisualStyleBackColor = true;
			this->restart->Click += gcnew System::EventHandler(this, &Form1::restart_Click);
			// 
			// next
			// 
			this->next->Location = System::Drawing::Point(469, 41);
			this->next->Name = L"next";
			this->next->Size = System::Drawing::Size(75, 23);
			this->next->TabIndex = 2;
			this->next->Text = L"Next";
			this->next->UseVisualStyleBackColor = true;
			this->next->Click += gcnew System::EventHandler(this, &Form1::next_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(551, 476);
			this->Controls->Add(this->next);
			this->Controls->Add(this->restart);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Nexus 2015";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void restart_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Reset Board
				 initBoard();

				 //Draw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void next_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Randomise New Balls
				 addNew();

				 //Draw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}
	};
}

