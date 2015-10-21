/*
	Program name:				Nexus 2015
	Project file name:			Nexus.sln
	Author:						Andrew Thomas Fletcher
	Date:						21/10/2015
	Language:					C++
	Platform:					Microsoft Visual Studio 2013
	Purpose:					Creates a game of Nexus
	Description:				This program creates a Windows form and displays a game of Nexus on it. The user can
								click Start to draw the board, then Restart if they wish to start over. The Next button
								puts three randomly coloured balls in three random positions on the board, unless the
								board is full. The Shuffle button randomises the contents of the board. The user can
								click on a ball to select it, then either click on an empty position to move it, or
								click on another ball to select a different ball. A ball will only move to the desired
								position if a clear path is available. If the user or the game puts five or more balls
								in a row either vertically or horizontally, the line is deleted and the user gets points
								based upon the length of the deleted line. The game is over if there are no more spaces
								to put more balls.
	File Description:			This file contains everything related to the form. This includes:
									+Drawing the Form and the controls
									+Listeners for the buttons and Board
									+Initialising the Board
									+Drawing the Board
	Known Bugs:					-If the shuffle button is pushed near the end of the game, free spaces can be accidently
									put in. I couldn't find what was causing this, so it stays, unfortunately.
								-Because of the above bug, and the ability to push the shuffle button as many times as
									you want, the game can be played infinitely.
	Additional Features:		+Shuffle Button.
								+Breadth-first Pathfinding.
								+Reset Button.
								+Score.
*/

#pragma once
#include "game.h" //Holds all game methods and objects
#include <time.h> //Used to seed srand
#include <stdlib.h> //Holds srand

namespace Nexus {
	//Variables
	//Used for position of last clicked ball
	int selectedX = 0;
	int selectedY = 0;
	int selectedColour = 0;

	//Boolean for identifying if user has selected a ball
	bool selected = false;

	//Constant for number of times to randomise (used for shuffling board)
	const int LOOPTIMES = 100;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			//Initialise Board
			initBoard();
		}

	protected:
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
	private: System::Windows::Forms::Label^  labelScore;
	private: System::Windows::Forms::Label^  scoreCounter;
	private: System::Windows::Forms::Button^  shuffle;


	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->restart = (gcnew System::Windows::Forms::Button());
			this->next = (gcnew System::Windows::Forms::Button());
			this->labelScore = (gcnew System::Windows::Forms::Label());
			this->scoreCounter = (gcnew System::Windows::Forms::Label());
			this->shuffle = (gcnew System::Windows::Forms::Button());
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
			this->restart->Size = System::Drawing::Size(75, 75);
			this->restart->TabIndex = 1;
			this->restart->Text = L"Start";
			this->restart->UseVisualStyleBackColor = true;
			this->restart->Click += gcnew System::EventHandler(this, &Form1::restart_Click);
			// 
			// next
			// 
			this->next->Location = System::Drawing::Point(469, 93);
			this->next->Name = L"next";
			this->next->Size = System::Drawing::Size(75, 75);
			this->next->TabIndex = 2;
			this->next->Text = L"Next";
			this->next->UseVisualStyleBackColor = true;
			this->next->Click += gcnew System::EventHandler(this, &Form1::next_Click);
			// 
			// labelScore
			// 
			this->labelScore->AutoSize = true;
			this->labelScore->Font = (gcnew System::Drawing::Font(L"Corbel", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelScore->Location = System::Drawing::Point(470, 391);
			this->labelScore->Name = L"labelScore";
			this->labelScore->Size = System::Drawing::Size(81, 33);
			this->labelScore->TabIndex = 3;
			this->labelScore->Text = L"Score";
			// 
			// scoreCounter
			// 
			this->scoreCounter->AutoSize = true;
			this->scoreCounter->Font = (gcnew System::Drawing::Font(L"Agency FB", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->scoreCounter->Location = System::Drawing::Point(470, 429);
			this->scoreCounter->Name = L"scoreCounter";
			this->scoreCounter->Size = System::Drawing::Size(75, 34);
			this->scoreCounter->TabIndex = 4;
			this->scoreCounter->Text = L"00000";
			// 
			// shuffle
			// 
			this->shuffle->Location = System::Drawing::Point(469, 174);
			this->shuffle->Name = L"button1";
			this->shuffle->Size = System::Drawing::Size(75, 75);
			this->shuffle->TabIndex = 5;
			this->shuffle->Text = L"Shuffle";
			this->shuffle->UseVisualStyleBackColor = true;
			this->shuffle->Click += gcnew System::EventHandler(this, &Form1::shuffle_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(551, 476);
			this->Controls->Add(this->shuffle);
			this->Controls->Add(this->scoreCounter);
			this->Controls->Add(this->labelScore);
			this->Controls->Add(this->next);
			this->Controls->Add(this->restart);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Nexus 2015";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//Click on Restart Button
	private: System::Void restart_Click(System::Object^  sender, System::EventArgs^  e)
	{
				 //Change name of button
				 this->restart->Text = "Restart";

				 //Reset Board
				 initBoard();

				 //Draw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}

			 //Click on PictureBox
	private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
				 //If nothing has been selected AND the user clicked on a TAKEN space
				 if ((selected == false) && (gameBoard[e->X / RECTSIZE][e->Y / RECTSIZE] != FREE))
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
				 else if ((selected == true) && (gameBoard[e->X / RECTSIZE][e->Y / RECTSIZE] != FREE))
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
				 else if ((selected == true) && (gameBoard[e->X / RECTSIZE][e->Y / RECTSIZE] == FREE))
				 {
					 //if a path has been found
					 if (checkForPath(selectedX, selectedY, (e->X / RECTSIZE), (e->Y / RECTSIZE)))
					 {
						 //Revert colour of selected ball
						 gameBoard[selectedX][selectedY] = selectedColour;

						 //Swap contents of cells
						 gameBoard[e->X / RECTSIZE][e->Y / RECTSIZE] = gameBoard[selectedX][selectedY];
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
						 //Else there was a line so update score
						 this->scoreCounter->Text = getScore().ToString();
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

					 //Check for lines created by adding balls
					 checkForLine();

					 //Draw Board
					 drawBoard(pictureBox1->CreateGraphics());
				 }
				 else
				 {
					 MessageBox::Show("Game Over! You got " + getScore().ToString() + " points!");
				 }
	}
			 //Click on Shuffle button
	private: System::Void shuffle_Click(System::Object^  sender, System::EventArgs^  e) {
				 int firstIndexX;
				 int firstIndexY;
				 int secondIndexX;
				 int secondIndexY;
				 int temp;
				 srand(time(NULL)); //Seeding srand

				 //Randomise array
				 for (int i = 0; i < LOOPTIMES; i++)
				 {
					 //Randomise two places to swapped
					 firstIndexX = rand() % BOARDWIDTH;
					 firstIndexY = rand() % BOARDHEIGHT;
					 secondIndexX = rand() % BOARDWIDTH;
					 secondIndexY = rand() % BOARDHEIGHT;

					 //Swap index contents
					 temp = gameBoard[firstIndexX][firstIndexY];
					 gameBoard[firstIndexX][firstIndexY] = gameBoard[secondIndexX][secondIndexY];
					 gameBoard[secondIndexX][secondIndexY] = temp;
				 }
				 //Check for any lines
				 checkForLine();

				 //Draw Board
				 drawBoard(pictureBox1->CreateGraphics());
	}
};
}

