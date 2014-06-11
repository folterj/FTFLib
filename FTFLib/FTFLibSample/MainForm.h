#pragma once

#include "FtfHelper.h"

namespace FTFLibSample {

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
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->mainMenuStrip->SuspendLayout();
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
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->openToolStripMenuItem, 
				this->saveAsToolStripMenuItem, this->toolStripSeparator1, this->exitToolStripMenuItem});
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
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"FTF files (*.ftf)|*.ftf|All files (*.*)|*.*";
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->Filter = L"FTF files (*.ftf)|*.ftf|All files (*.*)|*.*";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->mainMenuStrip);
			this->MainMenuStrip = this->mainMenuStrip;
			this->Name = L"MainForm";
			this->Text = L"FTF Sample";
			this->mainMenuStrip->ResumeLayout(false);
			this->mainMenuStrip->PerformLayout();
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
		System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			array<Byte>^ content;
			String^ s = "File content:\n";

			if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				content = FtfHelper::readFile(openFileDialog->FileName);
				if (content->Length > 0)
				{
					if (content->Length < 1000)
					{
						for each (Byte x in content)
						{
							s += String::Format("{0:X2} ", x);
						}
						MessageBox::Show(s, "FTF File");
					}
					else
					{
						MessageBox::Show(String::Format("Content length : {0}", content->Length), "FTF File");
					}
				}
			}
		}

		System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			array<Byte>^ content = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

			if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (FtfHelper::writeFile(saveFileDialog->FileName, content))
				{
					MessageBox::Show("File content written ok", "FTF File");
				}
			}
		}

		System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			Close();
		}

	};
}
