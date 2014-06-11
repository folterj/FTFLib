#pragma once

#include "FtfImageHelper.h"

namespace FTFImageSample {

	using namespace System;
	using namespace System::Windows::Forms;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::MenuStrip^  mainMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  createToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  mainPicture;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->mainMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mainPicture = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->createToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mainMenuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainPicture))->BeginInit();
			this->SuspendLayout();
			// 
			// mainMenuStrip
			// 
			this->mainMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->fileToolStripMenuItem});
			this->mainMenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainMenuStrip->Name = L"mainMenuStrip";
			this->mainMenuStrip->Size = System::Drawing::Size(284, 24);
			this->mainMenuStrip->TabIndex = 0;
			this->mainMenuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->createToolStripMenuItem, 
				this->openToolStripMenuItem, this->saveAsToolStripMenuItem, this->toolStripSeparator1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// mainPicture
			// 
			this->mainPicture->BackColor = System::Drawing::Color::Transparent;
			this->mainPicture->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->mainPicture->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainPicture->Location = System::Drawing::Point(0, 24);
			this->mainPicture->Name = L"mainPicture";
			this->mainPicture->Size = System::Drawing::Size(284, 238);
			this->mainPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->mainPicture->TabIndex = 1;
			this->mainPicture->TabStop = false;
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"FTF files (*.ftf)|*.ftf|All files (*.*)|*.*";
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->Filter = L"FTF files (*.ftf)|*.ftf|All files (*.*)|*.*";
			// 
			// createToolStripMenuItem
			// 
			this->createToolStripMenuItem->Name = L"createToolStripMenuItem";
			this->createToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->createToolStripMenuItem->Text = L"Create";
			this->createToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::createToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->mainPicture);
			this->Controls->Add(this->mainMenuStrip);
			this->MainMenuStrip = this->mainMenuStrip;
			this->Name = L"MainForm";
			this->Text = L"FTF Image Sample";
			this->mainMenuStrip->ResumeLayout(false);
			this->mainMenuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mainPicture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		MainForm()
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		FtfImageHelper ftfImageHelper;
		Bitmap^ bitmap;

		System::Void createToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			mainPicture->Image = ftfImageHelper.createImage();
		}

		System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				bitmap = ftfImageHelper.readImage(openFileDialog->FileName);
				if (bitmap)
				{
					mainPicture->Image = bitmap;
				}
				else
				{
					MessageBox::Show(ftfImageHelper.getErrorMessage(), "Read error");
				}
			}
		}

		System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (!ftfImageHelper.writeImage(saveFileDialog->FileName))
				{
					MessageBox::Show("Error writing image", "Write error");
				}
			}
		}

		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Close();
		}

	};
}
