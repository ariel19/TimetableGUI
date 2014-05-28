#pragma once

#include "GeneticAlgorithmWrapper.h"

namespace TimetableGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections;
	using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class TTGUI : public System::Windows::Forms::Form
	{
	public:
		TTGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TTGUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  btnCalculate;


	private: System::Windows::Forms::ListBox^  lbTeachers;

	private: System::Windows::Forms::Button^  btnAddTeacher;
	private: System::Windows::Forms::TextBox^  txtLastname;
	private: System::Windows::Forms::TextBox^  txtSubject;
	private: System::Windows::Forms::Button^  btnClrTeacher;
	private: System::Windows::Forms::Label^  lblLastname;

	private: System::Windows::Forms::Label^  lblSubject;

	private: System::Windows::Forms::ListBox^  lbClasses;
	private: System::Windows::Forms::GroupBox^  gbTeachers;
	private: System::Windows::Forms::Button^  btnRemoveTeacher;
	private: System::Windows::Forms::GroupBox^  gbClasses;
	private: System::Windows::Forms::TextBox^  txtClassID;
	private: System::Windows::Forms::Button^  btnClearClass;


	private: System::Windows::Forms::Button^  btnAddClass;

	private: System::Windows::Forms::Label^  lblhpw;
	private: System::Windows::Forms::Label^  lblClassID;
	private: System::Windows::Forms::Button^  btnRemoveClass;
	private: System::Windows::Forms::TextBox^  txthpw;
	private: System::Windows::Forms::GroupBox^  gbTFH;
	private: System::Windows::Forms::GroupBox^  gbCCI;
	private: System::Windows::Forms::TabControl^  tcClassesInfo;
	private: System::Windows::Forms::TabControl^  tcTFH;
	private: System::Windows::Forms::ComboBox^  cbTeachers;
	private: System::Windows::Forms::Button^  btnHours;
	private: System::Windows::Forms::TextBox^  txtHours;

	private: System::Windows::Forms::Button^  btnFixedHour;
	private: System::Windows::Forms::TextBox^  txtFixedHour;
	private: System::Windows::Forms::Label^  lblFixedHour;

	private: System::Windows::Forms::ComboBox^  cbDays;
	private: System::Windows::Forms::Button^  btnReadFromFile;
	private: System::Windows::Forms::Button^  btnSaveToFile;
	private: System::Windows::Forms::Label^  lblHours;

			 GeneticAlgorithmWrapper gaw;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCalculate = (gcnew System::Windows::Forms::Button());
			this->lbTeachers = (gcnew System::Windows::Forms::ListBox());
			this->btnAddTeacher = (gcnew System::Windows::Forms::Button());
			this->txtLastname = (gcnew System::Windows::Forms::TextBox());
			this->txtSubject = (gcnew System::Windows::Forms::TextBox());
			this->btnClrTeacher = (gcnew System::Windows::Forms::Button());
			this->lblLastname = (gcnew System::Windows::Forms::Label());
			this->lblSubject = (gcnew System::Windows::Forms::Label());
			this->lbClasses = (gcnew System::Windows::Forms::ListBox());
			this->gbTeachers = (gcnew System::Windows::Forms::GroupBox());
			this->btnRemoveTeacher = (gcnew System::Windows::Forms::Button());
			this->gbClasses = (gcnew System::Windows::Forms::GroupBox());
			this->txthpw = (gcnew System::Windows::Forms::TextBox());
			this->txtClassID = (gcnew System::Windows::Forms::TextBox());
			this->btnClearClass = (gcnew System::Windows::Forms::Button());
			this->btnAddClass = (gcnew System::Windows::Forms::Button());
			this->lblhpw = (gcnew System::Windows::Forms::Label());
			this->lblClassID = (gcnew System::Windows::Forms::Label());
			this->btnRemoveClass = (gcnew System::Windows::Forms::Button());
			this->gbTFH = (gcnew System::Windows::Forms::GroupBox());
			this->btnFixedHour = (gcnew System::Windows::Forms::Button());
			this->txtFixedHour = (gcnew System::Windows::Forms::TextBox());
			this->lblFixedHour = (gcnew System::Windows::Forms::Label());
			this->cbDays = (gcnew System::Windows::Forms::ComboBox());
			this->tcTFH = (gcnew System::Windows::Forms::TabControl());
			this->gbCCI = (gcnew System::Windows::Forms::GroupBox());
			this->btnHours = (gcnew System::Windows::Forms::Button());
			this->txtHours = (gcnew System::Windows::Forms::TextBox());
			this->cbTeachers = (gcnew System::Windows::Forms::ComboBox());
			this->tcClassesInfo = (gcnew System::Windows::Forms::TabControl());
			this->btnReadFromFile = (gcnew System::Windows::Forms::Button());
			this->btnSaveToFile = (gcnew System::Windows::Forms::Button());
			this->lblHours = (gcnew System::Windows::Forms::Label());
			this->gbTeachers->SuspendLayout();
			this->gbClasses->SuspendLayout();
			this->gbTFH->SuspendLayout();
			this->gbCCI->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnCalculate
			// 
			this->btnCalculate->Location = System::Drawing::Point(292, 515);
			this->btnCalculate->Name = L"btnCalculate";
			this->btnCalculate->Size = System::Drawing::Size(75, 23);
			this->btnCalculate->TabIndex = 0;
			this->btnCalculate->Text = L"Calculate";
			this->btnCalculate->UseVisualStyleBackColor = true;
			this->btnCalculate->Click += gcnew System::EventHandler(this, &TTGUI::btnCalculate_Click);
			// 
			// lbTeachers
			// 
			this->lbTeachers->FormattingEnabled = true;
			this->lbTeachers->Location = System::Drawing::Point(6, 17);
			this->lbTeachers->Name = L"lbTeachers";
			this->lbTeachers->Size = System::Drawing::Size(220, 95);
			this->lbTeachers->TabIndex = 3;
			// 
			// btnAddTeacher
			// 
			this->btnAddTeacher->Location = System::Drawing::Point(9, 208);
			this->btnAddTeacher->Name = L"btnAddTeacher";
			this->btnAddTeacher->Size = System::Drawing::Size(100, 23);
			this->btnAddTeacher->TabIndex = 4;
			this->btnAddTeacher->Text = L"Add teacher";
			this->btnAddTeacher->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->btnAddTeacher->UseVisualStyleBackColor = true;
			this->btnAddTeacher->Click += gcnew System::EventHandler(this, &TTGUI::btnAddTeacher_Click);
			// 
			// txtLastname
			// 
			this->txtLastname->Location = System::Drawing::Point(9, 182);
			this->txtLastname->Name = L"txtLastname";
			this->txtLastname->Size = System::Drawing::Size(100, 20);
			this->txtLastname->TabIndex = 5;
			// 
			// txtSubject
			// 
			this->txtSubject->Location = System::Drawing::Point(115, 182);
			this->txtSubject->Name = L"txtSubject";
			this->txtSubject->Size = System::Drawing::Size(100, 20);
			this->txtSubject->TabIndex = 6;
			// 
			// btnClrTeacher
			// 
			this->btnClrTeacher->Location = System::Drawing::Point(115, 208);
			this->btnClrTeacher->Name = L"btnClrTeacher";
			this->btnClrTeacher->Size = System::Drawing::Size(100, 23);
			this->btnClrTeacher->TabIndex = 7;
			this->btnClrTeacher->Text = L"Clear teacher";
			this->btnClrTeacher->UseVisualStyleBackColor = true;
			this->btnClrTeacher->Click += gcnew System::EventHandler(this, &TTGUI::btnClrTeacher_Click);
			// 
			// lblLastname
			// 
			this->lblLastname->AutoSize = true;
			this->lblLastname->Location = System::Drawing::Point(31, 156);
			this->lblLastname->Name = L"lblLastname";
			this->lblLastname->Size = System::Drawing::Size(53, 13);
			this->lblLastname->TabIndex = 8;
			this->lblLastname->Text = L"Lastname";
			// 
			// lblSubject
			// 
			this->lblSubject->AutoSize = true;
			this->lblSubject->Location = System::Drawing::Point(139, 156);
			this->lblSubject->Name = L"lblSubject";
			this->lblSubject->Size = System::Drawing::Size(43, 13);
			this->lblSubject->TabIndex = 9;
			this->lblSubject->Text = L"Subject";
			// 
			// lbClasses
			// 
			this->lbClasses->FormattingEnabled = true;
			this->lbClasses->Location = System::Drawing::Point(6, 19);
			this->lbClasses->Name = L"lbClasses";
			this->lbClasses->Size = System::Drawing::Size(220, 95);
			this->lbClasses->TabIndex = 12;
			// 
			// gbTeachers
			// 
			this->gbTeachers->Controls->Add(this->btnRemoveTeacher);
			this->gbTeachers->Controls->Add(this->lbTeachers);
			this->gbTeachers->Controls->Add(this->lblLastname);
			this->gbTeachers->Controls->Add(this->txtLastname);
			this->gbTeachers->Controls->Add(this->btnClrTeacher);
			this->gbTeachers->Controls->Add(this->lblSubject);
			this->gbTeachers->Controls->Add(this->btnAddTeacher);
			this->gbTeachers->Controls->Add(this->txtSubject);
			this->gbTeachers->Location = System::Drawing::Point(12, 12);
			this->gbTeachers->Name = L"gbTeachers";
			this->gbTeachers->Size = System::Drawing::Size(235, 246);
			this->gbTeachers->TabIndex = 13;
			this->gbTeachers->TabStop = false;
			this->gbTeachers->Text = L"Teacher\'s info";
			// 
			// btnRemoveTeacher
			// 
			this->btnRemoveTeacher->Location = System::Drawing::Point(9, 119);
			this->btnRemoveTeacher->Name = L"btnRemoveTeacher";
			this->btnRemoveTeacher->Size = System::Drawing::Size(100, 23);
			this->btnRemoveTeacher->TabIndex = 10;
			this->btnRemoveTeacher->Text = L"Remove teacher";
			this->btnRemoveTeacher->UseVisualStyleBackColor = true;
			// 
			// gbClasses
			// 
			this->gbClasses->Controls->Add(this->txthpw);
			this->gbClasses->Controls->Add(this->txtClassID);
			this->gbClasses->Controls->Add(this->btnClearClass);
			this->gbClasses->Controls->Add(this->btnAddClass);
			this->gbClasses->Controls->Add(this->lblhpw);
			this->gbClasses->Controls->Add(this->lblClassID);
			this->gbClasses->Controls->Add(this->btnRemoveClass);
			this->gbClasses->Controls->Add(this->lbClasses);
			this->gbClasses->Location = System::Drawing::Point(12, 264);
			this->gbClasses->Name = L"gbClasses";
			this->gbClasses->Size = System::Drawing::Size(235, 245);
			this->gbClasses->TabIndex = 14;
			this->gbClasses->TabStop = false;
			this->gbClasses->Text = L"Classes info";
			// 
			// txthpw
			// 
			this->txthpw->Location = System::Drawing::Point(115, 182);
			this->txthpw->Name = L"txthpw";
			this->txthpw->Size = System::Drawing::Size(100, 20);
			this->txthpw->TabIndex = 11;
			// 
			// txtClassID
			// 
			this->txtClassID->Location = System::Drawing::Point(9, 182);
			this->txtClassID->MaxLength = 1;
			this->txtClassID->Name = L"txtClassID";
			this->txtClassID->Size = System::Drawing::Size(100, 20);
			this->txtClassID->TabIndex = 11;
			// 
			// btnClearClass
			// 
			this->btnClearClass->Location = System::Drawing::Point(115, 208);
			this->btnClearClass->Name = L"btnClearClass";
			this->btnClearClass->Size = System::Drawing::Size(100, 23);
			this->btnClearClass->TabIndex = 11;
			this->btnClearClass->Text = L"Clear class";
			this->btnClearClass->UseVisualStyleBackColor = true;
			this->btnClearClass->Click += gcnew System::EventHandler(this, &TTGUI::btnClearClass_Click);
			// 
			// btnAddClass
			// 
			this->btnAddClass->Location = System::Drawing::Point(9, 208);
			this->btnAddClass->Name = L"btnAddClass";
			this->btnAddClass->Size = System::Drawing::Size(100, 23);
			this->btnAddClass->TabIndex = 11;
			this->btnAddClass->Text = L"Add class";
			this->btnAddClass->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageAboveText;
			this->btnAddClass->UseVisualStyleBackColor = true;
			this->btnAddClass->Click += gcnew System::EventHandler(this, &TTGUI::btnAddClass_Click);
			// 
			// lblhpw
			// 
			this->lblhpw->AutoSize = true;
			this->lblhpw->Location = System::Drawing::Point(124, 156);
			this->lblhpw->Name = L"lblhpw";
			this->lblhpw->Size = System::Drawing::Size(82, 13);
			this->lblhpw->TabIndex = 11;
			this->lblhpw->Text = L"Hours per week";
			// 
			// lblClassID
			// 
			this->lblClassID->AutoSize = true;
			this->lblClassID->Location = System::Drawing::Point(28, 156);
			this->lblClassID->Name = L"lblClassID";
			this->lblClassID->Size = System::Drawing::Size(46, 13);
			this->lblClassID->TabIndex = 11;
			this->lblClassID->Text = L"Class ID";
			// 
			// btnRemoveClass
			// 
			this->btnRemoveClass->Location = System::Drawing::Point(7, 121);
			this->btnRemoveClass->Name = L"btnRemoveClass";
			this->btnRemoveClass->Size = System::Drawing::Size(102, 23);
			this->btnRemoveClass->TabIndex = 13;
			this->btnRemoveClass->Text = L"Remove class";
			this->btnRemoveClass->UseVisualStyleBackColor = true;
			// 
			// gbTFH
			// 
			this->gbTFH->Controls->Add(this->btnFixedHour);
			this->gbTFH->Controls->Add(this->txtFixedHour);
			this->gbTFH->Controls->Add(this->lblFixedHour);
			this->gbTFH->Controls->Add(this->cbDays);
			this->gbTFH->Controls->Add(this->tcTFH);
			this->gbTFH->Location = System::Drawing::Point(272, 12);
			this->gbTFH->Name = L"gbTFH";
			this->gbTFH->Size = System::Drawing::Size(287, 246);
			this->gbTFH->TabIndex = 15;
			this->gbTFH->TabStop = false;
			this->gbTFH->Text = L"Teacher\'s fixed hours";
			// 
			// btnFixedHour
			// 
			this->btnFixedHour->Location = System::Drawing::Point(127, 192);
			this->btnFixedHour->Name = L"btnFixedHour";
			this->btnFixedHour->Size = System::Drawing::Size(100, 23);
			this->btnFixedHour->TabIndex = 4;
			this->btnFixedHour->Text = L"Add hours";
			this->btnFixedHour->UseVisualStyleBackColor = true;
			this->btnFixedHour->Click += gcnew System::EventHandler(this, &TTGUI::btnFixedHour_Click);
			// 
			// txtFixedHour
			// 
			this->txtFixedHour->Location = System::Drawing::Point(127, 165);
			this->txtFixedHour->Name = L"txtFixedHour";
			this->txtFixedHour->Size = System::Drawing::Size(100, 20);
			this->txtFixedHour->TabIndex = 3;
			// 
			// lblFixedHour
			// 
			this->lblFixedHour->AutoSize = true;
			this->lblFixedHour->Location = System::Drawing::Point(53, 168);
			this->lblFixedHour->Name = L"lblFixedHour";
			this->lblFixedHour->Size = System::Drawing::Size(56, 13);
			this->lblFixedHour->TabIndex = 2;
			this->lblFixedHour->Text = L"Fixed hour";
			// 
			// cbDays
			// 
			this->cbDays->FormattingEnabled = true;
			this->cbDays->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Monday", L"Tuesday", L"Wednesday", L"Thursday", 
				L"Friday"});
			this->cbDays->Location = System::Drawing::Point(7, 137);
			this->cbDays->Name = L"cbDays";
			this->cbDays->Size = System::Drawing::Size(222, 21);
			this->cbDays->TabIndex = 1;
			// 
			// tcTFH
			// 
			this->tcTFH->Location = System::Drawing::Point(6, 20);
			this->tcTFH->Name = L"tcTFH";
			this->tcTFH->SelectedIndex = 0;
			this->tcTFH->Size = System::Drawing::Size(268, 110);
			this->tcTFH->TabIndex = 0;
			// 
			// gbCCI
			// 
			this->gbCCI->Controls->Add(this->lblHours);
			this->gbCCI->Controls->Add(this->btnHours);
			this->gbCCI->Controls->Add(this->txtHours);
			this->gbCCI->Controls->Add(this->cbTeachers);
			this->gbCCI->Controls->Add(this->tcClassesInfo);
			this->gbCCI->Location = System::Drawing::Point(272, 264);
			this->gbCCI->Name = L"gbCCI";
			this->gbCCI->Size = System::Drawing::Size(287, 245);
			this->gbCCI->TabIndex = 16;
			this->gbCCI->TabStop = false;
			this->gbCCI->Text = L"Classes info";
			// 
			// btnHours
			// 
			this->btnHours->Location = System::Drawing::Point(127, 189);
			this->btnHours->Name = L"btnHours";
			this->btnHours->Size = System::Drawing::Size(101, 24);
			this->btnHours->TabIndex = 3;
			this->btnHours->Text = L"Add hours";
			this->btnHours->UseVisualStyleBackColor = true;
			this->btnHours->Click += gcnew System::EventHandler(this, &TTGUI::btnHours_Click);
			// 
			// txtHours
			// 
			this->txtHours->Location = System::Drawing::Point(128, 163);
			this->txtHours->Name = L"txtHours";
			this->txtHours->Size = System::Drawing::Size(100, 20);
			this->txtHours->TabIndex = 2;
			// 
			// cbTeachers
			// 
			this->cbTeachers->FormattingEnabled = true;
			this->cbTeachers->Location = System::Drawing::Point(7, 136);
			this->cbTeachers->Name = L"cbTeachers";
			this->cbTeachers->Size = System::Drawing::Size(221, 21);
			this->cbTeachers->TabIndex = 1;
			// 
			// tcClassesInfo
			// 
			this->tcClassesInfo->Location = System::Drawing::Point(6, 19);
			this->tcClassesInfo->Name = L"tcClassesInfo";
			this->tcClassesInfo->SelectedIndex = 0;
			this->tcClassesInfo->Size = System::Drawing::Size(268, 110);
			this->tcClassesInfo->TabIndex = 0;
			// 
			// btnReadFromFile
			// 
			this->btnReadFromFile->Location = System::Drawing::Point(21, 515);
			this->btnReadFromFile->Name = L"btnReadFromFile";
			this->btnReadFromFile->Size = System::Drawing::Size(100, 23);
			this->btnReadFromFile->TabIndex = 17;
			this->btnReadFromFile->Text = L"Read from file";
			this->btnReadFromFile->UseVisualStyleBackColor = true;
			this->btnReadFromFile->Click += gcnew System::EventHandler(this, &TTGUI::btnReadFromFile_Click);
			// 
			// btnSaveToFile
			// 
			this->btnSaveToFile->Location = System::Drawing::Point(127, 515);
			this->btnSaveToFile->Name = L"btnSaveToFile";
			this->btnSaveToFile->Size = System::Drawing::Size(100, 23);
			this->btnSaveToFile->TabIndex = 18;
			this->btnSaveToFile->Text = L"Save to file";
			this->btnSaveToFile->UseVisualStyleBackColor = true;
			this->btnSaveToFile->Click += gcnew System::EventHandler(this, &TTGUI::btnSaveToFile_Click);
			// 
			// lblHours
			// 
			this->lblHours->AutoSize = true;
			this->lblHours->Location = System::Drawing::Point(74, 166);
			this->lblHours->Name = L"lblHours";
			this->lblHours->Size = System::Drawing::Size(35, 13);
			this->lblHours->TabIndex = 4;
			this->lblHours->Text = L"Hours";
			// 
			// TTGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 551);
			this->Controls->Add(this->btnSaveToFile);
			this->Controls->Add(this->btnReadFromFile);
			this->Controls->Add(this->gbCCI);
			this->Controls->Add(this->gbTFH);
			this->Controls->Add(this->gbClasses);
			this->Controls->Add(this->gbTeachers);
			this->Controls->Add(this->btnCalculate);
			this->Name = L"TTGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Timetable";
			this->gbTeachers->ResumeLayout(false);
			this->gbTeachers->PerformLayout();
			this->gbClasses->ResumeLayout(false);
			this->gbClasses->PerformLayout();
			this->gbTFH->ResumeLayout(false);
			this->gbTFH->PerformLayout();
			this->gbCCI->ResumeLayout(false);
			this->gbCCI->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnCalculate_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (lbClasses->Items->Count == 0 || lbTeachers->Items->Count == 0) {
					MessageBox::Show("Empty data, please provide information.", "Incorrect data", MessageBoxButtons::OK);
					return;
				 }

				 gaw.CreateInstance();
			 }
private: System::Void btnClrTeacher_Click(System::Object^  sender, System::EventArgs^  e) {
			 txtLastname->Text = "";
			 txtSubject->Text = "";
		 }
private: System::Void btnAddTeacher_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (String::IsNullOrWhiteSpace(txtLastname->Text) || String::IsNullOrWhiteSpace(txtSubject->Text)) {
				 MessageBox::Show("Please, fill subject and lastname fields", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 String ^ _t = txtSubject->Text + "/" + txtLastname->Text;
			 if (!gaw.add_teacher(_t)) {
				 MessageBox::Show("Please, provide a unique teacher", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 // valid data is presented, so put it in ListBox
			 TabPage ^tp = gcnew TabPage;
			 tp->Controls->Add(gcnew ListBox());
			 tp->Text = txtSubject->Text + "/" + txtLastname->Text;
			 lbTeachers->Items->Add(txtSubject->Text + "/" + txtLastname->Text);
			 tcTFH->Controls->Add(tp);

			 cbTeachers->Items->Add(txtSubject->Text + "/" + txtLastname->Text);
		 }
private: System::Void btnAddClass_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (String::IsNullOrWhiteSpace(txtClassID->Text) || String::IsNullOrWhiteSpace(txthpw->Text)) {
				 MessageBox::Show("Please, fill class id and hours per week fields", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 Int32 hpw;
			 if (!Int32::TryParse(txthpw->Text, hpw)) {
				 MessageBox::Show("Please, enter a numeric value for hours per week field", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 if (!gaw.add_classes((Byte)(txtClassID->Text[0]))) {
				 MessageBox::Show("Please, enter a unique value for class id", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 gaw.add_hpc(Int32::Parse(txthpw->Text));

			 TabPage ^tp = gcnew TabPage;
			 ListBox ^lb = gcnew ListBox;
			 tp->Controls->Add(gcnew ListBox());
			 tp->Text = txtClassID->Text;
			 lbClasses->Items->Add(txtClassID->Text + "/" + txthpw->Text);
			 tcClassesInfo->Controls->Add(tp);
		 }
private: System::Void btnClearClass_Click(System::Object^  sender, System::EventArgs^  e) {
			 txtClassID->Text = "";
			 txthpw->Text = "";
		 }

private: System::Void btnHours_Click(System::Object^  sender, System::EventArgs^  e) {
			 Int32 h;
			 if (String::IsNullOrWhiteSpace(txtHours->Text) && Int32::TryParse(txtHours->Text, h)) {
				 MessageBox::Show("Please, fill Hours per week field with numeric value", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 } 

			 String^ s = (String ^)cbTeachers->SelectedItem;
			 if (String::IsNullOrWhiteSpace(s)) {
				 MessageBox::Show("No teacher was selected", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 TabPage ^tp = tcClassesInfo->SelectedTab;
			 int index = tcClassesInfo->SelectedIndex;

			 // add logic info
			if (gaw.add_classes_curriculum(KeyValuePair<Byte, KeyValuePair<String ^, int>>((Byte)tp->Text[0],
				KeyValuePair<String ^, int>(s, Int32::Parse(txtHours->Text))))) {
				// just for view
				((ListBox ^)(tp->Controls[0]))->Items->Add(s + "/" + txtHours->Text);
				gaw.prepared_data = false;
			}
		 }

private: System::Void btnFixedHour_Click(System::Object^  sender, System::EventArgs^  e) {
			 Int32 h;
			 if (String::IsNullOrWhiteSpace(txtFixedHour->Text) && Int32::TryParse(txtFixedHour->Text, h)) {
				 MessageBox::Show("Please, fill Fixed hours field with numeric value", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 } 

			 String^ s = (String ^)cbDays->SelectedItem;
			 if (String::IsNullOrWhiteSpace(s)) {
				 MessageBox::Show("No day was selected", "Incorrect data", MessageBoxButtons::OK);
				 return;
			 }

			 TabPage ^tp = tcTFH->SelectedTab;
			 int index = tcClassesInfo->SelectedIndex;

			 if(gaw.add_fixed_hours(KeyValuePair<String ^, KeyValuePair<String ^, int>>(tp->Text,
				 KeyValuePair<String ^, int>(s, Int32::Parse(txtFixedHour->Text))))) {
				  ((ListBox ^)(tp->Controls[0]))->Items->Add(s + "/" + txtFixedHour->Text); // visual info
				  gaw.prepared_data = false;
			 }
		 }
		 // TODO: add filter
private: System::Void btnReadFromFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 OpenFileDialog ^ofd = gcnew OpenFileDialog;

			 //ofd->Filter = ".plan";
			 if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				 return;
			 
			 try {
				 StreamReader ^sr = File::OpenText(ofd->FileName);
				 String ^str;
				 int count, i, teachers;
				 str = sr->ReadLine();

				 teachers = Int32::Parse(str);
				 // add teachers
				 for (i = 0; i < teachers; ++i) {
					 str = sr->ReadLine();
					 gaw.add_teacher(str);

					 lbTeachers->Items->Add(str);
					 cbTeachers->Items->Add(str);

					 TabPage ^tp = gcnew TabPage;
					 tp->Controls->Add(gcnew ListBox());
					 tp->Text = str;
					 tcTFH->Controls->Add(tp);
				 }

				 // add classes
				 List<String ^> ^tmp = gcnew List<String ^>;

				 str = sr->ReadLine();
				 count = Int32::Parse(str);
				 for (i = 0; i < count; ++i) {
					 str = sr->ReadLine();
					 gaw.add_classes((Byte)str[0]);

					 tmp->Add(str);
				 }

				 // add hours for classes
				 for (i = 0; i < count; ++i) {
					 str = sr->ReadLine();
					 gaw.add_hpc(Int32::Parse(str));

					 tmp[i] += "/" + str;
					 lbClasses->Items->Add(tmp[i]);

					 TabPage ^tp = gcnew TabPage;
					 tp->Controls->Add(gcnew ListBox());
					 tp->Text = tmp[i];
					 tcClassesInfo->Controls->Add(tp);
				 }

				 // classes curriculum
				 for (i = 0; i < count; ++i) {
					 List<int> ^l = gcnew List<int>;
					 for (int j = 0; j < teachers; ++j) {
						 str = sr->ReadLine();
						 l->Add(Int32::Parse(str));

						 int h = Int32::Parse(str);
						 if (h != 0) {
							 ((ListBox ^)(tcClassesInfo->Controls[i]->Controls[0]))->Items->Add(
								 cbTeachers->Items[j]->ToString() + "/" + str);
							 gaw.add_classes_curriculum((KeyValuePair<Byte, KeyValuePair<String ^, int>>(gaw.classes[i],
								KeyValuePair<String ^, int>(gaw.teachers[j], h))));
						 }
					 }
				 }

				 // fixed hours
				 String ^delim_str = " ";
				 array<Char> ^delim = delim_str->ToCharArray();
				 for (i = 0; i < teachers; ++i) {
					 List<KeyValuePair<int, int>> ^l = gcnew List<KeyValuePair<int, int>>;
					 str = sr->ReadLine();
					 count = Int32::Parse(str);
					 for (int j = 0; j < count; ++j) {
						 str = sr->ReadLine();
						 // split
						 array<String ^> ^words = str->Split(delim);
						 l->Add(KeyValuePair<int, int>(Int32::Parse(words[0]) - 1, Int32::Parse(words[1]) - 1));

						 ((ListBox ^)(tcTFH->Controls[i]->Controls[0]))->Items->Add(gaw.num_to_day(Int32::Parse(words[0]))
							 + "/" + words[1]);
						 gaw.add_fixed_hours(KeyValuePair<String ^, KeyValuePair<String ^, int>>(gaw.teachers[i], 
							 KeyValuePair<String ^, int>(gaw.num_to_day(Int32::Parse(words[0])), Int32::Parse(words[1]))));
					 }
				 }

			 }
			 catch(Exception ^ e) {
				 MessageBox::Show(e->Message, "Read file error", MessageBoxButtons::OK);
			 }

			 delete ofd;
		 }
private: System::Void btnSaveToFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 SaveFileDialog ^sfd = gcnew SaveFileDialog;
			 sfd->DefaultExt = ".plan";

			 if (sfd->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
				 return;
			 }
			 Stream ^stream;
			 if ((stream = sfd->OpenFile()) != nullptr) {

				 array<unsigned char> ^data = gaw.make_conversion(true)->ToArray();
				 stream->Write(data, 0, data->Length);
				 stream->Close();
			 }
		 }
};
}

