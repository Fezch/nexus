#pragma once
#include "game.h"

namespace Nexus {
	//Variables
	//Used for position of last clicked ball
	int selectedX = 0;
	int selectedY = 0;
	int selectedColour = 0;

	//Boolean for identifying if user has selected a ball
	bool selected = false;

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
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
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

		//Click on Restart Button
	private: System::Void restart_Click(System::Object^  sender, System::EventArgs^  e)
	{
				 //Reset Board
				 initBoard();

				 //Draw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}

			 //Click on PictureBox
	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
				 //If nothing has been selected AND the user clicked on a TAKEN space
				 if ((selected == false) && (gameBoard[(e->X) / RECTSIZE][(e->Y) / RECTSIZE] != FREE))
				 {
					 //Save location of selected ball
					 selectedX = e->X / RECTSIZE;
					 selectedY = e->Y / RECTSIZE;

					 //Save colour of selected ball
					 selectedColour = gameBoard[selectedX][selectedY];

					 //Change colour of selected ball
					 gameBoard[selectedX][selectedY] = SELECTED;

					 //Make selected true
					 selected = true;
				 }

				 //Else if something has already been selected AND the user clicked on a TAKEN space
				 else if ((selected == true) && (gameBoard[(e->X) / RECTSIZE][(e->Y) / RECTSIZE] != FREE))
				 {
					 //Revert colour of previously selected ball
					 gameBoard[selectedX][selectedY] = selectedColour;

					 //Change current selection to new selection
					 selectedX = e->X / RECTSIZE;
					 selectedY = e->Y / RECTSIZE;

					 //Save colour of new selected ball
					 selectedColour = gameBoard[selectedX][selectedY];

					 //Change colour of new selected ball
					 gameBoard[selectedX][selectedY] = SELECTED;

					 //Make selected true
					 selected = true;
				 }

				 //Else if something has already been selected AND the user clicked on a FREE space
				 else if ((selected == true) && (gameBoard[(e->X) / RECTSIZE][(e->Y) / RECTSIZE] == FREE))
				 {
					 //Revert colour of selected ball
					 gameBoard[selectedX][selectedY] = selectedColour;

					 //Swap contents of cells
					 gameBoard[(e->X) / RECTSIZE][(e->Y) / RECTSIZE] = gameBoard[selectedX][selectedY];
					 gameBoard[selectedX][selectedY] = FREE;

					 //Make selected false
					 selected = false;

					 //Check if there is not a line
					 if (checkForLine() != true)
					 {
						 //Int for free space counting
						 int freeSpaces = 0;

						 //Find number of free spaces
						 for (int x = 0; x < BOARDWIDTH; x++)
						 {
							 for (int y = 0; y < BOARDHEIGHT; y++)
							 {
								 //If there is a free space
								 if (gameBoard[x][y] == FREE)
								 {
									 //Add to free space counter
									 freeSpaces++;
								 }
							 }
						 }
						 //Add needed number of balls
						 addNew(freeSpaces);
					 }
				 }

				 //Redraw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}
			 //Click on Next Button
	private: System::Void next_Click(System::Object^  sender, System::EventArgs^  e)
	{
				 //Boolean for game over
				 bool gameOver = true;

				 //Int for number of free spaces
				 int freeSpaces = 0;

				 //Check to see if game is finished
				 for (int x = 0; x < BOARDWIDTH; x++)
				 {
					 for (int y = 0; y < BOARDHEIGHT; y++)
					 {
						 //If there is a free space
						 if (gameBoard[x][y] == FREE)
						 {
							 //The game is not over
							 gameOver = false;

							 //Add to free space counter
							 freeSpaces++;
						 }
					 }
				 }

				 //If game is not over
				 if (gameOver == false)
				 {
					 //Add New Balls
					 addNew(freeSpaces);

					 //Draw Board
					 drawBoard(pictureBox1->CreateGraphics());
				 }
				 else
				 {
					 MessageBox::Show("Game Over! No more spaces left!");
				 }
	}
	};
}

