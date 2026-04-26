#pragma once

#include "FanucMillTools.h"
#include <msclr/marshal.h>
#include "Utils.h"

//#define MAX_AXIS 32

namespace FanucMillTools {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  //using namespace System::Reflection::Emit;
  using namespace System::Data;
  using namespace System::Data::SqlClient;
  using namespace System::Drawing;
  using namespace System::Collections::Generic;
  
  using namespace std;
  using namespace Utils;
  /// <summary>
  /// Summary for MainForm
  /// </summary>
  public ref class MainForm : public System::Windows::Forms::Form
  {
  public:
    MainForm(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //
      CNC_IP_tb->Text = "127.0.0.1";
      

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




  private: MenuStrip^ menuStrip1;
  private: ToolStripMenuItem^ fanucToolStripMenuItem;
  private: ToolStripMenuItem^ nCDataToolStripMenuItem;
  private: ToolStripMenuItem^ readParameterToolStripMenuItem;
  private: System::Windows::Forms::Label^ CNC_IP_lbl;
  private: TextBox^ CNC_IP_tb;
  private: Button^ Connect_btn;
  private: Button^ Disconnect_btn;
  private: System::Windows::Forms::Label^ FocasHndl_lbl;
  private: TextBox^ FocasHndl_tb;
  private: ToolStripMenuItem^ testToolStripMenuItem;
  private: System::Windows::Forms::Label^ CncInfo_lbl;
  private: ToolStripMenuItem^ toolOffsetsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ workZeroOffsetsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ axisSpindleToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ downloadNCToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ downloadDNCToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ uploadNCToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ uploadDNCToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^ verifyNCToolStripMenuItem;
  private: StreamReader^ ZSurfInspectStreamReader;


  protected:

  private:
    /// <summary>
    /// Required designer variable.
   
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
        this->fanucToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->nCDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->readParameterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolOffsetsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->workZeroOffsetsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->testToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->CNC_IP_lbl = (gcnew System::Windows::Forms::Label());
        this->CNC_IP_tb = (gcnew System::Windows::Forms::TextBox());
        this->Connect_btn = (gcnew System::Windows::Forms::Button());
        this->Disconnect_btn = (gcnew System::Windows::Forms::Button());
        this->FocasHndl_lbl = (gcnew System::Windows::Forms::Label());
        this->FocasHndl_tb = (gcnew System::Windows::Forms::TextBox());
        this->CncInfo_lbl = (gcnew System::Windows::Forms::Label());
        this->axisSpindleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->downloadNCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->downloadDNCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->uploadNCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->uploadDNCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->verifyNCToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->menuStrip1->SuspendLayout();
        this->SuspendLayout();
        // 
        // menuStrip1
        // 
        this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fanucToolStripMenuItem });
        this->menuStrip1->Location = System::Drawing::Point(0, 0);
        this->menuStrip1->Name = L"menuStrip1";
        this->menuStrip1->Size = System::Drawing::Size(1305, 24);
        this->menuStrip1->TabIndex = 4;
        this->menuStrip1->Text = L"menuStrip1";
        // 
        // fanucToolStripMenuItem
        // 
        this->fanucToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->axisSpindleToolStripMenuItem,
                this->testToolStripMenuItem, this->nCDataToolStripMenuItem
        });
        this->fanucToolStripMenuItem->Name = L"fanucToolStripMenuItem";
        this->fanucToolStripMenuItem->Size = System::Drawing::Size(51, 20);
        this->fanucToolStripMenuItem->Text = L"Fanuc";
        // 
        // nCDataToolStripMenuItem
        // 
        this->nCDataToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->readParameterToolStripMenuItem,
                this->toolOffsetsToolStripMenuItem, this->workZeroOffsetsToolStripMenuItem
        });
        this->nCDataToolStripMenuItem->Name = L"nCDataToolStripMenuItem";
        this->nCDataToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->nCDataToolStripMenuItem->Text = L"NCData";
        // 
        // readParameterToolStripMenuItem
        // 
        this->readParameterToolStripMenuItem->Name = L"readParameterToolStripMenuItem";
        this->readParameterToolStripMenuItem->Size = System::Drawing::Size(175, 22);
        this->readParameterToolStripMenuItem->Text = L"Get-Set Parameters";
        this->readParameterToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::readParameterToolStripMenuItem_Click);
        // 
        // toolOffsetsToolStripMenuItem
        // 
        this->toolOffsetsToolStripMenuItem->Name = L"toolOffsetsToolStripMenuItem";
        this->toolOffsetsToolStripMenuItem->Size = System::Drawing::Size(175, 22);
        this->toolOffsetsToolStripMenuItem->Text = L"Tool Offsets";
        this->toolOffsetsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::toolOffsetsToolStripMenuItem_Click);
        // 
        // workZeroOffsetsToolStripMenuItem
        // 
        this->workZeroOffsetsToolStripMenuItem->Name = L"workZeroOffsetsToolStripMenuItem";
        this->workZeroOffsetsToolStripMenuItem->Size = System::Drawing::Size(175, 22);
        this->workZeroOffsetsToolStripMenuItem->Text = L"Work Zero Offsets";
        this->workZeroOffsetsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::workZeroOffsetsToolStripMenuItem_Click);
        // 
        // testToolStripMenuItem
        // 
        this->testToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
            this->downloadNCToolStripMenuItem,
                this->downloadDNCToolStripMenuItem, this->uploadNCToolStripMenuItem, this->uploadDNCToolStripMenuItem, this->verifyNCToolStripMenuItem
        });
        this->testToolStripMenuItem->Name = L"testToolStripMenuItem";
        this->testToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->testToolStripMenuItem->Text = L"NCProgram";
        // 
        // CNC_IP_lbl
        // 
        this->CNC_IP_lbl->AutoSize = true;
        this->CNC_IP_lbl->Location = System::Drawing::Point(486, 39);
        this->CNC_IP_lbl->Name = L"CNC_IP_lbl";
        this->CNC_IP_lbl->Size = System::Drawing::Size(45, 13);
        this->CNC_IP_lbl->TabIndex = 5;
        this->CNC_IP_lbl->Text = L"CNC IP:";
        // 
        // CNC_IP_tb
        // 
        this->CNC_IP_tb->Location = System::Drawing::Point(537, 36);
        this->CNC_IP_tb->Name = L"CNC_IP_tb";
        this->CNC_IP_tb->Size = System::Drawing::Size(72, 20);
        this->CNC_IP_tb->TabIndex = 6;
        // 
        // Connect_btn
        // 
        this->Connect_btn->Location = System::Drawing::Point(621, 36);
        this->Connect_btn->Name = L"Connect_btn";
        this->Connect_btn->Size = System::Drawing::Size(91, 23);
        this->Connect_btn->TabIndex = 7;
        this->Connect_btn->Text = L"CONNECT";
        this->Connect_btn->UseVisualStyleBackColor = true;
        this->Connect_btn->Click += gcnew System::EventHandler(this, &MainForm::Connect_btn_Click);
        // 
        // Disconnect_btn
        // 
        this->Disconnect_btn->Location = System::Drawing::Point(725, 36);
        this->Disconnect_btn->Name = L"Disconnect_btn";
        this->Disconnect_btn->Size = System::Drawing::Size(87, 23);
        this->Disconnect_btn->TabIndex = 8;
        this->Disconnect_btn->Text = L"DISCONNECT";
        this->Disconnect_btn->UseVisualStyleBackColor = true;
        this->Disconnect_btn->Click += gcnew System::EventHandler(this, &MainForm::Disconnect_btn_Click);
        // 
        // FocasHndl_lbl
        // 
        this->FocasHndl_lbl->AutoSize = true;
        this->FocasHndl_lbl->Location = System::Drawing::Point(821, 41);
        this->FocasHndl_lbl->Name = L"FocasHndl_lbl";
        this->FocasHndl_lbl->Size = System::Drawing::Size(76, 13);
        this->FocasHndl_lbl->TabIndex = 9;
        this->FocasHndl_lbl->Text = L"Focas Handle:";
        // 
        // FocasHndl_tb
        // 
        this->FocasHndl_tb->Enabled = false;
        this->FocasHndl_tb->Location = System::Drawing::Point(902, 38);
        this->FocasHndl_tb->Name = L"FocasHndl_tb";
        this->FocasHndl_tb->Size = System::Drawing::Size(50, 20);
        this->FocasHndl_tb->TabIndex = 10;
        // 
        // CncInfo_lbl
        // 
        this->CncInfo_lbl->AutoSize = true;
        this->CncInfo_lbl->Location = System::Drawing::Point(983, 40);
        this->CncInfo_lbl->Name = L"CncInfo_lbl";
        this->CncInfo_lbl->Size = System::Drawing::Size(0, 13);
        this->CncInfo_lbl->TabIndex = 11;
        // 
        // axisSpindleToolStripMenuItem
        // 
        this->axisSpindleToolStripMenuItem->Name = L"axisSpindleToolStripMenuItem";
        this->axisSpindleToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->axisSpindleToolStripMenuItem->Text = L"Axis/Spindle";
        // 
        // downloadNCToolStripMenuItem
        // 
        this->downloadNCToolStripMenuItem->Name = L"downloadNCToolStripMenuItem";
        this->downloadNCToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->downloadNCToolStripMenuItem->Text = L"Download NC";
        this->downloadNCToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::downloadNCToolStripMenuItem_Click);
        // 
        // downloadDNCToolStripMenuItem
        // 
        this->downloadDNCToolStripMenuItem->Name = L"downloadDNCToolStripMenuItem";
        this->downloadDNCToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->downloadDNCToolStripMenuItem->Text = L"Download DNC";
        // 
        // uploadNCToolStripMenuItem
        // 
        this->uploadNCToolStripMenuItem->Name = L"uploadNCToolStripMenuItem";
        this->uploadNCToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->uploadNCToolStripMenuItem->Text = L"Upload NC";
        // 
        // uploadDNCToolStripMenuItem
        // 
        this->uploadDNCToolStripMenuItem->Name = L"uploadDNCToolStripMenuItem";
        this->uploadDNCToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->uploadDNCToolStripMenuItem->Text = L"Upload DNC";
        // 
        // verifyNCToolStripMenuItem
        // 
        this->verifyNCToolStripMenuItem->Name = L"verifyNCToolStripMenuItem";
        this->verifyNCToolStripMenuItem->Size = System::Drawing::Size(180, 22);
        this->verifyNCToolStripMenuItem->Text = L"Verify NC";
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->BackColor = System::Drawing::SystemColors::Control;
        this->ClientSize = System::Drawing::Size(1305, 681);
        this->Controls->Add(this->CncInfo_lbl);
        this->Controls->Add(this->FocasHndl_tb);
        this->Controls->Add(this->FocasHndl_lbl);
        this->Controls->Add(this->Disconnect_btn);
        this->Controls->Add(this->Connect_btn);
        this->Controls->Add(this->CNC_IP_tb);
        this->Controls->Add(this->CNC_IP_lbl);
        this->Controls->Add(this->menuStrip1);
        this->MainMenuStrip = this->menuStrip1;
        this->Name = L"MainForm";
        this->Text = L"MainForm";
        this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
        this->menuStrip1->ResumeLayout(false);
        this->menuStrip1->PerformLayout();
        this->ResumeLayout(false);
        this->PerformLayout();

    }
#pragma endregion

   // You can call the functions at a button click. If you prefer, 
    // you can call them by clicking a menu item.

  private: System::Void readParameterToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
  {
      List <Control^> DynamicControls;
      for each(Control^ ctrl in this->Controls)
      {if (ctrl->Tag == "Dynamic") DynamicControls.Add(ctrl);
      }
      for each (Control ^ ctrl in DynamicControls)
      {Controls->Remove(ctrl);
      }
      Label^ InfoLabel_lbl = gcnew Label(); InfoLabel_lbl->Name = "InfoLabel_lbl"; InfoLabel_lbl->Tag = "Dynamic"; InfoLabel_lbl->SetBounds(1200, 60, 250, 20); InfoLabel_lbl->Visible = false;
      TextBox^ FromParam_tb = gcnew TextBox(); FromParam_tb->Name = "FromParam_tb"; FromParam_tb->Tag = "Dynamic"; FromParam_tb->SetBounds(150, 100, 50, 20);
      TextBox^ ToParam_tb = gcnew TextBox(); ToParam_tb->Name = "ToParam_tb"; ToParam_tb->Tag = "Dynamic"; ToParam_tb->SetBounds(150, 140, 50, 20);
      Button^ ReadParams_btn = gcnew Button(); ReadParams_btn->Name = "ReadParams_btn"; ReadParams_btn->Text = "GET PARAMETERS"; ReadParams_btn->Tag = "Dynamic"; ReadParams_btn->SetBounds(250, 120, 125, 20);
      Label^ FromParam_lbl = gcnew Label(); FromParam_lbl->Name = "FromParam_lbl"; FromParam_lbl->Text = "FROM PARAM:"; FromParam_lbl->Tag = "Dynamic"; FromParam_lbl->SetBounds(50, 100, 150, 20);
      Label^ ToParam_lbl = gcnew Label(); ToParam_lbl->Name = "ToParam_lbl"; ToParam_lbl->Text = "TO PARAM:"; ToParam_lbl->Tag = "Dynamic"; ToParam_lbl->SetBounds(50, 140, 150, 20);
      Label^ Param_no_lbl = gcnew Label(); Param_no_lbl->Name = "Param_no_lbl";  Param_no_lbl->Tag = "Dynamic"; Param_no_lbl->SetBounds(450, 120, 150, 20);
      
      /////////////////////////////////////////
      Label^ Param_data_lbl = gcnew Label(); Param_data_lbl->Name = "Param_data_lbl"; Param_data_lbl->Text = "PARAMETER VALUE:"; Param_data_lbl->Tag = "Dynamic"; Param_data_lbl->SetBounds(650, 100, 150, 20);
      Label^ Param_Xdata_lbl = gcnew Label(); Param_Xdata_lbl->Name = "Param_Xdata_lbl"; Param_Xdata_lbl->Text = "PARAMETER VALUE(X):"; Param_Xdata_lbl->Tag = "Dynamic"; Param_Xdata_lbl->SetBounds(650, 130, 150, 20);
      Label^ Param_Ydata_lbl = gcnew Label(); Param_Ydata_lbl->Name = "Param_Ydata_lbl"; Param_Ydata_lbl->Text = "PARAMETER VALUE(Y):"; Param_Ydata_lbl->Tag = "Dynamic"; Param_Ydata_lbl->SetBounds(650, 160, 150, 20);
      Label^ Param_Zdata_lbl = gcnew Label(); Param_Zdata_lbl->Name = "Param_Zdata_lbl"; Param_Zdata_lbl->Text = "PARAMETER VALUE(Z):"; Param_Zdata_lbl->Tag = "Dynamic"; Param_Zdata_lbl->SetBounds(650, 190, 150, 20);
      TextBox^ Param_data_tb = gcnew TextBox(); Param_data_tb->Name = "Param_data_tb"; Param_data_tb->Enabled = false; Param_data_tb->Tag = "Dynamic"; Param_data_tb->SetBounds(850, 100, 75, 20);
      TextBox^ Param_Xdata_tb = gcnew TextBox(); Param_Xdata_tb->Name = "Param_Xdata_tb"; Param_Xdata_tb->Enabled = false; Param_Xdata_tb->Tag = "Dynamic"; Param_Xdata_tb->SetBounds(850, 130, 75, 20);
      TextBox^ Param_Ydata_tb = gcnew TextBox(); Param_Ydata_tb->Name = "Param_Ydata_tb"; Param_Ydata_tb->Enabled = false; Param_Ydata_tb->Tag = "Dynamic"; Param_Ydata_tb->SetBounds(850, 160, 75, 20);
      TextBox^ Param_Zdata_tb = gcnew TextBox(); Param_Zdata_tb->Name = "Param_Zdata_tb"; Param_Zdata_tb->Enabled = false; Param_Zdata_tb->Tag = "Dynamic"; Param_Zdata_tb->SetBounds(850, 190, 75, 20);

      ReadParams_btn->Click += gcnew EventHandler(this,&MainForm::ReadParams_btn_Clicked);
      
      ///////////////////////////////////////////////////
      Button^ SetParam_btn = gcnew Button();
      SetParam_btn->Name = "SetParam_btn"; SetParam_btn->Text = "SET PARAMETER"; SetParam_btn->Tag = "Dynamic"; SetParam_btn->SetBounds(970, 150, 150, 20); SetParam_btn->Enabled = false;
      SetParam_btn->Click += gcnew EventHandler(this, &MainForm::SetParams_btn_Clicked);
      //////////////Data Grid Creation/////////////////////
      DataGridView^ Params_dgv = gcnew DataGridView();
      Params_dgv->Name = "Params_dgv";
      Params_dgv->Tag = "Dynamic";
      Params_dgv->SetBounds(50,230, 1750, 800);
      Params_dgv->Columns->Add("CNCIP_col", "CNC IP");
      Params_dgv->Columns->Add("ParamNum_col", "Param Num");
      Params_dgv->Columns->Add("ParamType_col", "Param Type");
      Params_dgv->Columns->Add("ParType_Ubyte_col", "ParType_Ubyte");
      Params_dgv->Columns->Add("ParAxis_Lbyte_col", "ParAxis_Lbyte");
      Params_dgv->Columns->Add("cdata_col", "cdata");
      Params_dgv->Columns->Add("idata_col", "idata");
      Params_dgv->Columns->Add("ldata_col", "ldata");
      Params_dgv->Columns->Add("rdata_col", "rdata");
      Params_dgv->Columns->Add("cdataX_col", "cdataX");
      Params_dgv->Columns->Add("cdataY_col", "cdataY");
      Params_dgv->Columns->Add("cdataZ_col", "cdataZ");
      Params_dgv->Columns->Add("idataX_col", "idataX");
      Params_dgv->Columns->Add("idataY_col", "idataY");
      Params_dgv->Columns->Add("idataZ_col", "idataZ");
      Params_dgv->Columns->Add("ldataX_col", "ldataX");
      Params_dgv->Columns->Add("ldataY_col", "ldataY");
      Params_dgv->Columns->Add("ldataZ_col", "ldataZ");
      Params_dgv->Columns->Add("rdataX_col", "rdataX");
      Params_dgv->Columns->Add("rdataY_col", "rdataY");
      Params_dgv->Columns->Add("rdataZ_col", "rdataZ");
      DataGridViewCheckBoxColumn^ AxisParam_col = gcnew DataGridViewCheckBoxColumn();
      AxisParam_col->Name = "AxisParam_col";
      AxisParam_col->HeaderText = "AxisParam";
      AxisParam_col->ReadOnly = true;
      Params_dgv->Columns->Add(AxisParam_col);
      DataGridViewCheckBoxColumn^ SpindleParam_col =gcnew DataGridViewCheckBoxColumn();
      SpindleParam_col->Name = "SpindleParam_col";
      SpindleParam_col->HeaderText = "SpindleParam";
      SpindleParam_col->ReadOnly = true;
      Params_dgv->Columns->Add(SpindleParam_col);
      DataGridViewCheckBoxColumn^ SignedParam_col = gcnew DataGridViewCheckBoxColumn();
      SignedParam_col->Name = "SignedParam_col";
      SignedParam_col->HeaderText = "SignedParam";
      SignedParam_col->ReadOnly = true;
      Params_dgv->Columns->Add(SignedParam_col);
      DataGridViewCheckBoxColumn^ SettingsInput_col = gcnew DataGridViewCheckBoxColumn();
      SettingsInput_col->Name = "SettingsInput_col";
      SettingsInput_col->HeaderText = "SettingsInput";
      SettingsInput_col->ReadOnly = true;
      Params_dgv->Columns->Add(SettingsInput_col);
      DataGridViewCheckBoxColumn^ WriteProtect_col = gcnew DataGridViewCheckBoxColumn();
      WriteProtect_col->Name = "WriteProtect_col";
      WriteProtect_col->HeaderText = "WriteProtect";
      WriteProtect_col->ReadOnly = true;
      Params_dgv->Columns->Add(WriteProtect_col);
      DataGridViewCheckBoxColumn^ PowerMustBeOff_col = gcnew DataGridViewCheckBoxColumn();
      PowerMustBeOff_col->Name = "PowerMustBeOff_col";
      PowerMustBeOff_col->HeaderText = "PowerMustBeOff";
      PowerMustBeOff_col->ReadOnly = true;
      Params_dgv->Columns->Add(PowerMustBeOff_col);
      DataGridViewCheckBoxColumn^ ReadProtect_col = gcnew DataGridViewCheckBoxColumn();
      ReadProtect_col->Name = "ReadProtect_col";
      ReadProtect_col->HeaderText = "ReadProtect";
      ReadProtect_col->ReadOnly = true;
      Params_dgv->Columns->Add(ReadProtect_col);
      Params_dgv->Columns->Add("ArrangeType_col", "ArrangeType");
      Params_dgv->Columns->Add("ParamUnitType_col", "ParamUnitType");
      Params_dgv->Columns->Add("ParamUnitDimens_col", "ParamUnitDimens");
      Params_dgv->Columns->Add("ParamInputType_col", "ParamInputType");
      Params_dgv->Columns->Add("ParamDisplay_col", "ParamDisplay");
      Params_dgv->Columns->Add("ParamOthers_col", "ParamOthers");
      Params_dgv->Columns->Add("ParamReadDate_col", "ParamReadDate");
      //Params_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::Params_dgv_SelectionChanged); Event Handler added after reading Parameters ( because event is fired when adding rows to DataGridView)
      Controls->Add(InfoLabel_lbl);
      Controls->Add(FromParam_tb);
      Controls->Add(ToParam_tb);
      Controls->Add(ReadParams_btn);
      Controls->Add(FromParam_lbl);
      Controls->Add(ToParam_lbl);
      Controls->Add(Param_no_lbl);
      Controls->Add(Params_dgv);
      Controls->Add(SetParam_btn);
      Controls->Add(Param_data_lbl);
      Controls->Add(Param_Xdata_lbl);
      Controls->Add(Param_Ydata_lbl);
      Controls->Add(Param_Zdata_lbl);
      Controls->Add(Param_data_tb);
      Controls->Add(Param_Xdata_tb);
      Controls->Add(Param_Ydata_tb);
      Controls->Add(Param_Zdata_tb);
      
      //////////////////////////////////////
      FocasReadNumParams(this);
  }
private: System::Void ReadParams_btn_Clicked(Object^ sender, EventArgs^ e)
{
    DataGridView^ Params_dgv = (DataGridView^)Controls["Params_dgv"];
    FocasReadParams(this);
    Params_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::Params_dgv_SelectionChanged);
}
private: System::Void SetParams_btn_Clicked(Object^ sender, EventArgs^ e)
{short ret=FocasWriteParam(this);
}
private: System::Void Connect_btn_Click(System::Object^ sender, System::EventArgs^ e)
{
 FocasConnect(this);
}
private: System::Void Disconnect_btn_Click(System::Object^ sender, System::EventArgs^ e) 
{
    FocasDisconnect(this);
}

       
  private:System::Void Params_dgv_SelectionChanged(Object^ sender, EventArgs^ e)
  {   DataGridView^ Params_dgv = (DataGridView^)Controls["Params_dgv"];
      TextBox^ Param_data_tb = (TextBox^)Controls["Param_data_tb"];
      TextBox^ Param_Xdata_tb = (TextBox^)Controls["Param_Xdata_tb"];
      TextBox^ Param_Ydata_tb = (TextBox^)Controls["Param_Ydata_tb"];
      TextBox^ Param_Zdata_tb = (TextBox^)Controls["Param_Zdata_tb"];
      Label^ Param_no_lbl = (Label^)Controls["Param_no_lbl"]; 
      Controls["SetParam_btn"]->Enabled = true;
      //////////////////////////////////////////////////
      short ParamNo = 0;
      short ParamType = 0;
      int SelRows =Params_dgv->SelectedRows->Count;
      int SelCells = Params_dgv->SelectedCells->Count;
      if (SelRows == 0 && SelCells > 0) Params_dgv->SelectedCells[0]->OwningRow->Selected = true;
      if (SelRows>1) { MessageBox::Show("Select Only one parameter");return;}
      
         int CurrRowindex = Params_dgv->CurrentRow->Index;
          ParamNo = short::Parse(Params_dgv->CurrentRow->Cells[1]->Value->ToString());
          ParamType = short::Parse(Params_dgv->CurrentRow->Cells[2]->Value->ToString());
          switch (ParamType & 0xFF)
          {
          case 0:
              Param_data_tb->Enabled = true; Param_Xdata_tb->Enabled = false; Param_Ydata_tb->Enabled = false; Param_Zdata_tb->Enabled = false;
              Param_Xdata_tb->Text = ""; Param_Ydata_tb->Text = ""; Param_Zdata_tb->Text = "";
              switch (ParamType >> 8)
              {
                  
              case 0:
                  Param_data_tb->Text = Params_dgv->CurrentRow->Cells[5]->Value->ToString();
                  
                  break;
              case 1:
                  Param_data_tb->Text = Params_dgv->CurrentRow->Cells[5]->Value->ToString();
                  
                  
                  break;
              case 2:
                  Param_data_tb->Text = Params_dgv->CurrentRow->Cells[6]->Value->ToString();
                  
                  break;
              case 3:
                  Param_data_tb->Text = Params_dgv->CurrentRow->Cells[7]->Value->ToString();
                  
                  break;
              case 4:
                  Param_data_tb->Text = Params_dgv->CurrentRow->Cells[8]->Value->ToString();
               break;
              }
          case 1:
              
              break;
          case 2:
              
              break;
          case 3:
              
              break;
          case 0xFF:
              Param_data_tb->Enabled = false; Param_Xdata_tb->Enabled = true; Param_Ydata_tb->Enabled = true; Param_Zdata_tb->Enabled = true;
              Param_data_tb->Text = "";
              switch (ParamType >> 8)
              {case 0:
                  Param_Xdata_tb->Text = Params_dgv->CurrentRow->Cells[9]->Value->ToString();
                  Param_Ydata_tb->Text = Params_dgv->CurrentRow->Cells[10]->Value->ToString();
                  Param_Zdata_tb->Text = Params_dgv->CurrentRow->Cells[11]->Value->ToString();
                  break;
              case 1:
                  Param_Xdata_tb->Text = Params_dgv->CurrentRow->Cells[9]->Value->ToString();
                  Param_Ydata_tb->Text = Params_dgv->CurrentRow->Cells[10]->Value->ToString();
                  Param_Zdata_tb->Text = Params_dgv->CurrentRow->Cells[11]->Value->ToString();
                  break;
              case 2:
                  Param_Xdata_tb->Text = Params_dgv->CurrentRow->Cells[12]->Value->ToString();
                  Param_Ydata_tb->Text = Params_dgv->CurrentRow->Cells[13]->Value->ToString();
                  Param_Zdata_tb->Text = Params_dgv->CurrentRow->Cells[14]->Value->ToString();
                  break;
              case 3:
                  Param_Xdata_tb->Text = Params_dgv->CurrentRow->Cells[15]->Value->ToString();
                  Param_Ydata_tb->Text = Params_dgv->CurrentRow->Cells[16]->Value->ToString();
                  Param_Zdata_tb->Text = Params_dgv->CurrentRow->Cells[17]->Value->ToString();
                  break;
              case 4:
                  Param_Xdata_tb->Text = Params_dgv->CurrentRow->Cells[18]->Value->ToString();
                  Param_Ydata_tb->Text = Params_dgv->CurrentRow->Cells[19]->Value->ToString();
                  Param_Zdata_tb->Text = Params_dgv->CurrentRow->Cells[20]->Value->ToString();
                  break;
              }
          }
      Param_no_lbl->Text = "Param No: " +ParamNo.ToString();
  }
private: System::Void toolOffsetsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
{short ToolOffsets = 0;
 List <Control^> DynamicControls;
 for each (Control ^ ctrl in this->Controls)
    {
        if (ctrl->Tag == "Dynamic") DynamicControls.Add(ctrl);
    }
 for each (Control ^ ctrl in DynamicControls)
    {
        Controls->Remove(ctrl);
    }
 Label^ InfoLabel_lbl = gcnew Label(); InfoLabel_lbl->Name = "InfoLabel_lbl"; InfoLabel_lbl->Tag = "Dynamic"; InfoLabel_lbl->SetBounds(1200, 60, 250, 20); InfoLabel_lbl->Visible = false;
 Label^ FromToolOffset_lbl = gcnew Label(); FromToolOffset_lbl->Name = "FromToolOffset_lbl"; FromToolOffset_lbl->Text = "FROM Tool:"; FromToolOffset_lbl->Tag = "Dynamic"; FromToolOffset_lbl->SetBounds(50, 100, 150, 20);
 TextBox^ FromToolOffset_tb = gcnew TextBox(); FromToolOffset_tb->Name = "FromToolOffset_tb"; FromToolOffset_tb->Tag = "Dynamic"; FromToolOffset_tb->SetBounds(200, 100, 50, 20); FromToolOffset_tb->TabIndex = 0;
 Label^ ToToolOffset_lbl = gcnew Label(); ToToolOffset_lbl->Name = "ToToolOffset_lbl"; ToToolOffset_lbl->Text = "TO Tool:"; ToToolOffset_lbl->Tag = "Dynamic"; ToToolOffset_lbl->SetBounds(50, 140, 150, 20);
 TextBox^ ToToolOffset_tb = gcnew TextBox(); ToToolOffset_tb->Name = "ToToolOffset_tb"; ToToolOffset_tb->Tag = "Dynamic"; ToToolOffset_tb->SetBounds(200, 140, 50, 20); ToToolOffset_tb->TabIndex = 1;
 Button^ ReadToolOffsets_btn = gcnew Button(); ReadToolOffsets_btn->Name = "ReadToolOffsets_btn"; ReadToolOffsets_btn->Text = "READ TOOL OFFSETS"; ReadToolOffsets_btn->Tag = "Dynamic"; ReadToolOffsets_btn->SetBounds(275, 120, 175, 20);
 Label^ ToolOffset_no_lbl = gcnew Label(); ToolOffset_no_lbl->Name = "ToolOffset_no_lbl";  ToolOffset_no_lbl->Tag = "Dynamic"; ToolOffset_no_lbl->SetBounds(450, 120, 150, 20);
 ReadToolOffsets_btn->Click += gcnew EventHandler(this, &MainForm::ReadToolOffsets_btn_Click);
 Label^ ToolRadius_lbl = gcnew Label(); ToolRadius_lbl->Name = "ToolRadius_lbl"; ToolRadius_lbl->Text = "RADIUS:"; ToolRadius_lbl->Tag = "Dynamic"; ToolRadius_lbl->SetBounds(650, 160, 150, 20);
 Label^ ToolRadiusWear_lbl = gcnew Label(); ToolRadiusWear_lbl->Name = "ToolRadiusWear_lbl"; ToolRadiusWear_lbl->Text = "RADIUS (WEAR):"; ToolRadiusWear_lbl->Tag = "Dynamic"; ToolRadiusWear_lbl->SetBounds(650, 190, 150, 20);
 Label^ ToolLength_lbl = gcnew Label(); ToolLength_lbl->Name = "ToolLength_lbl"; ToolLength_lbl->Text = "LENGTH:"; ToolLength_lbl->Tag = "Dynamic"; ToolLength_lbl->SetBounds(650, 100, 150, 20);
 Label^ ToolLengthWear_lbl = gcnew Label(); ToolLengthWear_lbl->Name = "ToolLengthWear_lbl"; ToolLengthWear_lbl->Text = "LENGTH (WEAR):"; ToolLengthWear_lbl->Tag = "Dynamic"; ToolLengthWear_lbl->SetBounds(650, 130, 150, 20);
 TextBox^ ToolRadius_tb = gcnew TextBox(); ToolRadius_tb->Name = "ToolRadius_tb"; ToolRadius_tb->Enabled = false; ToolRadius_tb->Tag = "Dynamic"; ToolRadius_tb->SetBounds(850, 160, 75, 20); ToolRadius_tb->TabIndex = 3;
 TextBox^ ToolRadiusWear_tb = gcnew TextBox(); ToolRadiusWear_tb->Name = "ToolRadiusWear_tb"; ToolRadiusWear_tb->Enabled = false; ToolRadiusWear_tb->Tag = "Dynamic"; ToolRadiusWear_tb->SetBounds(850, 190, 75, 20); ToolRadiusWear_tb->TabIndex = 4;
 TextBox^ ToolLength_tb = gcnew TextBox(); ToolLength_tb->Name = "ToolLength_tb"; ToolLength_tb->Enabled = false; ToolLength_tb->Tag = "Dynamic"; ToolLength_tb->SetBounds(850, 100, 75, 20); ToolLength_tb->TabIndex = 5;
 TextBox^ ToolLengthWear_tb = gcnew TextBox(); ToolLengthWear_tb->Name = "ToolLengthWear_tb"; ToolLengthWear_tb->Enabled = false; ToolLengthWear_tb->Tag = "Dynamic"; ToolLengthWear_tb->SetBounds(850, 130, 75, 20); ToolLengthWear_tb->TabIndex = 6;
 
 Button^ SetToolOffset_btn = gcnew Button();
 SetToolOffset_btn->Name = "SetToolOffset_btn"; SetToolOffset_btn->Text = "SET TOOL OFFSET"; SetToolOffset_btn->Tag = "Dynamic"; SetToolOffset_btn->SetBounds(970, 150, 150, 20); SetToolOffset_btn->Enabled = false;
 SetToolOffset_btn->Click += gcnew EventHandler(this, &MainForm::SetToolOffsets_btn_Click);

 DataGridView^ ToolOffsets_dgv = gcnew DataGridView(); ToolOffsets_dgv->TabIndex = 2;
 ToolOffsets_dgv->Name = "ToolOffsets_dgv";
 ToolOffsets_dgv->Tag = "Dynamic";
 ToolOffsets_dgv->SetBounds(50, 230, 600, 800);
 ToolOffsets_dgv->Columns->Add("ToolOffset_No_col", "Tool Offset No");
 ToolOffsets_dgv->Columns->Add("ToolLength_col", "Tool Length");
 ToolOffsets_dgv->Columns["ToolLength_col"]->DefaultCellStyle->Format = "N3";
 ToolOffsets_dgv->Columns->Add("ToolLengthWear_col", "Tool Length Wear");
 ToolOffsets_dgv->Columns["ToolLengthWear_col"]->DefaultCellStyle->Format = "N3";
 ToolOffsets_dgv->Columns->Add("ToolRadius_col", "Tool Radius");
 ToolOffsets_dgv->Columns["ToolRadius_col"]->DefaultCellStyle->Format = "N3";
 ToolOffsets_dgv->Columns->Add("ToolRadiusWear_col", "Tool Radius Wear");
 ToolOffsets_dgv->Columns["ToolRadiusWear_col"]->DefaultCellStyle->Format = "N3";
 //ToolOffsets_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::ToolOffsets_dgv_SelectionChanged);
 Controls->Add(InfoLabel_lbl);
 Controls->Add(FromToolOffset_lbl);
 Controls->Add(FromToolOffset_tb);
 Controls->Add(ToToolOffset_lbl);
 Controls->Add(ToToolOffset_tb);
 Controls->Add(ReadToolOffsets_btn);
 Controls->Add(ToolOffset_no_lbl);
 Controls->Add(ToolRadius_lbl);
 Controls->Add(ToolRadiusWear_lbl);
 Controls->Add(ToolLength_lbl);
 Controls->Add(ToolLengthWear_lbl);
 Controls->Add(ToolRadius_tb);
 Controls->Add(ToolRadiusWear_tb);
 Controls->Add(ToolLength_tb);
 Controls->Add(ToolLengthWear_tb);
 Controls->Add(ToolOffsets_dgv);
 Controls->Add(SetToolOffset_btn);
 FocasReadNumToolOffsets(this,ToolOffsets);
 FromToolOffset_tb->Text = "1";
 ToToolOffset_tb->Text = ToolOffsets.ToString();
 //ToToolOffset_tb->Update();
}
 private: System::Void ReadToolOffsets_btn_Click(System::Object^ sender, System::EventArgs^ e)
 {DataGridView^ ToolOffsets_dgv = (DataGridView^)Controls["ToolOffsets_dgv"];
  FocasReadToolOffsets(this);
  ToolOffsets_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::ToolOffsets_dgv_SelectionChanged);
 }
  private: System::Void SetToolOffsets_btn_Click(System::Object^ sender, System::EventArgs^ e)
  {
   FocasWriteToolOffset(this);
  }
  private:System::Void ToolOffsets_dgv_SelectionChanged(Object^ sender, EventArgs^ e)
  {   DataGridView^ ToolOffsets_dgv = (DataGridView^)Controls["ToolOffsets_dgv"];
      TextBox^ ToolRadius_tb = (TextBox^)Controls["ToolRadius_tb"];
      TextBox^ ToolRadiusWear_tb = (TextBox^)Controls["ToolRadiusWear_tb"];
      TextBox^ ToolLength_tb = (TextBox^)Controls["ToolLength_tb"];
      TextBox^ ToolLengthWear_tb = (TextBox^)Controls["ToolLengthWear_tb"];
      Label^ ToolOffset_no_lbl = (Label^)Controls["ToolOffset_no_lbl"];
      Button^ SetToolOffset_btn = (Button^)Controls["SetToolOffset_btn"];
      Controls["SetToolOffset_btn"]->Enabled = true;
      //////////////////////////////////////////////////
      short ToolOffsetNo = 0;
      short ToolOffsetType = 0;
      int SelRows = ToolOffsets_dgv->SelectedRows->Count;
      int SelCells = ToolOffsets_dgv->SelectedCells->Count;
      if (SelRows == 0 && SelCells > 0) ToolOffsets_dgv->SelectedCells[0]->OwningRow->Selected = true;
      if (SelRows > 1) {MessageBox::Show("Select Only one ToolOffset"); return; }
      int CurrRowindex = ToolOffsets_dgv->CurrentRow->Index;
      ToolOffsetNo = short::Parse(ToolOffsets_dgv->CurrentRow->Cells[0]->Value->ToString());
      //ToolOffsetType = short::Parse(ToolOffsets_dgv->CurrentRow->Cells[2]->Value->ToString());
      ToolRadius_tb->Enabled = true; ToolRadiusWear_tb->Enabled = true; ToolLength_tb->Enabled = true; ToolLengthWear_tb->Enabled = true;
      ToolRadius_tb->Text = Convert::ToSingle(ToolOffsets_dgv->CurrentRow->Cells[3]->Value).ToString("N3");
      ToolRadiusWear_tb->Text = Convert::ToSingle(ToolOffsets_dgv->CurrentRow->Cells[4]->Value).ToString("N3");
      ToolLength_tb->Text = Convert::ToSingle(ToolOffsets_dgv->CurrentRow->Cells[1]->Value).ToString("N3");
      ToolLengthWear_tb->Text = Convert::ToSingle(ToolOffsets_dgv->CurrentRow->Cells[2]->Value).ToString("N3");
      ToolOffset_no_lbl->Text = "ToolOffset No: " + ToolOffsetNo.ToString();
  }
private: System::Void workZeroOffsetsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
{   List <Control^> DynamicControls;
    for each (Control ^ ctrl in this->Controls)
    {
     if (ctrl->Tag == "Dynamic") DynamicControls.Add(ctrl);
    }
    for each (Control ^ ctrl in DynamicControls)
    {
     Controls->Remove(ctrl);
    }
    Label^ InfoLabel_lbl = gcnew Label(); InfoLabel_lbl->Name = "InfoLabel_lbl"; InfoLabel_lbl->Tag = "Dynamic"; InfoLabel_lbl->SetBounds(1200, 60, 250, 20); InfoLabel_lbl->Visible = false;
    Label^ FromWorkZeroOffset_lbl = gcnew Label(); FromWorkZeroOffset_lbl->Name = "FromWorkZeroOffset_lbl"; FromWorkZeroOffset_lbl->Text = "FROM WorkOffset:"; FromWorkZeroOffset_lbl->Tag = "Dynamic"; FromWorkZeroOffset_lbl->SetBounds(50, 100, 150, 20);
    TextBox^ FromWorkZeroOffset_tb = gcnew TextBox(); FromWorkZeroOffset_tb->Name = "FromWorkZeroOffset_tb"; FromWorkZeroOffset_tb->Tag = "Dynamic"; FromWorkZeroOffset_tb->SetBounds(200, 100, 50, 20); FromWorkZeroOffset_tb->TabIndex = 0;
    Label^ ToWorkZeroOffset_lbl = gcnew Label(); ToWorkZeroOffset_lbl->Name = "ToWorkZeroOffset_lbl"; ToWorkZeroOffset_lbl->Text = "TO WorkOffset:"; ToWorkZeroOffset_lbl->Tag = "Dynamic"; ToWorkZeroOffset_lbl->SetBounds(50, 140, 150, 20);
    TextBox^ ToWorkZeroOffset_tb = gcnew TextBox(); ToWorkZeroOffset_tb->Name = "ToWorkZeroOffset_tb"; ToWorkZeroOffset_tb->Tag = "Dynamic"; ToWorkZeroOffset_tb->SetBounds(200, 140, 50, 20); ToWorkZeroOffset_tb->TabIndex = 1;
    Button^ ReadWorkZeroOffsets_btn = gcnew Button(); ReadWorkZeroOffsets_btn->Name = "ReadWorkZeroOffsets_btn"; ReadWorkZeroOffsets_btn->Text = "READ WorkZero OFFSETS"; ReadWorkZeroOffsets_btn->Tag = "Dynamic"; ReadWorkZeroOffsets_btn->SetBounds(275, 120, 175, 20);
    Label^ WorkZeroOffset_no_lbl = gcnew Label(); WorkZeroOffset_no_lbl->Name = "WorkZeroOffset_no_lbl";  WorkZeroOffset_no_lbl->Tag = "Dynamic"; WorkZeroOffset_no_lbl->SetBounds(450, 120, 150, 20);
    ReadWorkZeroOffsets_btn->Click += gcnew EventHandler(this, &MainForm::ReadWorkZeroOffsets_btn_Click);
    Label^ WorkZeroOffsetX_lbl = gcnew Label(); WorkZeroOffsetX_lbl->Name = "WorkZeroOffsetX_lbl"; WorkZeroOffsetX_lbl->Text = "X:"; WorkZeroOffsetX_lbl->Tag = "Dynamic"; WorkZeroOffsetX_lbl->SetBounds(750, 100, 20, 20);
    Label^ WorkZeroOffsetY_lbl = gcnew Label(); WorkZeroOffsetY_lbl->Name = "WorkZeroOffsetY_lbl"; WorkZeroOffsetY_lbl->Text = "Y:"; WorkZeroOffsetY_lbl->Tag = "Dynamic"; WorkZeroOffsetY_lbl->SetBounds(750, 130, 20, 20);
    Label^ WorkZeroOffsetZ_lbl = gcnew Label(); WorkZeroOffsetZ_lbl->Name = "WorkZeroOffsetZ_lbl"; WorkZeroOffsetZ_lbl->Text = "Z:"; WorkZeroOffsetZ_lbl->Tag = "Dynamic"; WorkZeroOffsetZ_lbl->SetBounds(750, 160, 20, 20);
    
    TextBox^ WorkZeroOffsetX_tb = gcnew TextBox(); WorkZeroOffsetX_tb->Name = "WorkZeroOffsetX_tb"; WorkZeroOffsetX_tb->Enabled = false; WorkZeroOffsetX_tb->Tag = "Dynamic"; WorkZeroOffsetX_tb->SetBounds(850, 100, 75, 20); WorkZeroOffsetX_tb->TabIndex = 3;
    TextBox^ WorkZeroOffsetY_tb = gcnew TextBox(); WorkZeroOffsetY_tb->Name = "WorkZeroOffsetY_tb"; WorkZeroOffsetY_tb->Enabled = false; WorkZeroOffsetY_tb->Tag = "Dynamic"; WorkZeroOffsetY_tb->SetBounds(850, 130, 75, 20); WorkZeroOffsetY_tb->TabIndex = 4;
    TextBox^ WorkZeroOffsetZ_tb = gcnew TextBox(); WorkZeroOffsetZ_tb->Name = "WorkZeroOffsetZ_tb"; WorkZeroOffsetZ_tb->Enabled = false; WorkZeroOffsetZ_tb->Tag = "Dynamic"; WorkZeroOffsetZ_tb->SetBounds(850, 160, 75, 20); WorkZeroOffsetZ_tb->TabIndex = 5;
    

    Button^ SetWorkZeroOffset_btn = gcnew Button();
    SetWorkZeroOffset_btn->Name = "SetWorkZeroOffset_btn"; SetWorkZeroOffset_btn->Text = "SET WorkZero OFFSET"; SetWorkZeroOffset_btn->Tag = "Dynamic"; SetWorkZeroOffset_btn->SetBounds(970, 150, 150, 20); SetWorkZeroOffset_btn->Enabled = false;
    SetWorkZeroOffset_btn->Click += gcnew EventHandler(this, &MainForm::SetWorkZeroOffsets_btn_Click);

    DataGridView^ WorkZeroOffsets_dgv = gcnew DataGridView(); WorkZeroOffsets_dgv->TabIndex = 2;
    WorkZeroOffsets_dgv->Name = "WorkZeroOffsets_dgv";
    WorkZeroOffsets_dgv->Tag = "Dynamic";
    WorkZeroOffsets_dgv->SetBounds(50, 230, 600, 800);
    WorkZeroOffsets_dgv->Columns->Add("WorkZeroOffset_No_col", "WorkZero Offset No");
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset_No_col"]->Width = 120;
    WorkZeroOffsets_dgv->Columns->Add("WorkZeroOffset[X]_col", "WorkZero Offset[X]");
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[X]_col"]->Width = 120;
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[X]_col"]->DefaultCellStyle->Format = "N3";
    WorkZeroOffsets_dgv->Columns->Add("WorkZeroOffset[Y]_col", "WorkZero Offset[Y]");
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[Y]_col"]->Width = 120;
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[Y]_col"]->DefaultCellStyle->Format = "N3";
    WorkZeroOffsets_dgv->Columns->Add("WorkZeroOffset[Z]_col", "WorkZero Offset[Z]");
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[Z]_col"]->Width = 120;
    WorkZeroOffsets_dgv->Columns["WorkZeroOffset[Z]_col"]->DefaultCellStyle->Format = "N3";
    
    //WorkZeroOffsets_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::WorkZeroOffsets_dgv_SelectionChanged);
    Controls->Add(InfoLabel_lbl);
    Controls->Add(FromWorkZeroOffset_lbl);
    Controls->Add(FromWorkZeroOffset_tb);
    Controls->Add(ToWorkZeroOffset_lbl);
    Controls->Add(ToWorkZeroOffset_tb);
    Controls->Add(ReadWorkZeroOffsets_btn);
    Controls->Add(WorkZeroOffset_no_lbl);
    Controls->Add(WorkZeroOffsetX_lbl);
    Controls->Add(WorkZeroOffsetY_lbl);
    Controls->Add(WorkZeroOffsetZ_lbl);
    Controls->Add(WorkZeroOffsetX_tb);
    Controls->Add(WorkZeroOffsetY_tb);
    Controls->Add(WorkZeroOffsetZ_tb);
    Controls->Add(WorkZeroOffsets_dgv);
    Controls->Add(SetWorkZeroOffset_btn);

   short WorkZeroOffsets = 0;
   short ret = cnc_rdzofsinfo(FHndl, &WorkZeroOffsets); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdzofsinfo: " + ret.ToString()); return; }
   FromWorkZeroOffset_tb->Text = "0";
   ToWorkZeroOffset_tb->Text = WorkZeroOffsets.ToString();
}
       private: System::Void ReadWorkZeroOffsets_btn_Click(System::Object^ sender, System::EventArgs^ e)
       {
           DataGridView^ WorkZeroOffsets_dgv = (DataGridView^)Controls["WorkZeroOffsets_dgv"];
           FocasReadWorkZeroOffsets(this);
           WorkZeroOffsets_dgv->SelectionChanged += gcnew EventHandler(this, &MainForm::WorkZeroOffsets_dgv_SelectionChanged);
       }
  private: System::Void SetWorkZeroOffsets_btn_Click(System::Object^ sender, System::EventArgs^ e)
  {
      FocasWriteWorkZeroOffset(this);
  }
  private:System::Void WorkZeroOffsets_dgv_SelectionChanged(Object^ sender, EventArgs^ e)
  {DataGridView^ WorkZeroOffsets_dgv = (DataGridView^)Controls["WorkZeroOffsets_dgv"];
   TextBox^ WorkZeroOffsetX_tb = (TextBox^)Controls["WorkZeroOffsetX_tb"];
   TextBox^ WorkZeroOffsetY_tb = (TextBox^)Controls["WorkZeroOffsetY_tb"];
   TextBox^ WorkZeroOffsetZ_tb = (TextBox^)Controls["WorkZeroOffsetZ_tb"];
   Label^ WorkZeroOffset_no_lbl = (Label^)Controls["WorkZeroOffset_no_lbl"];
   Button^ SetWorkZeroOffset_btn = (Button^)Controls["SetWorkZeroOffset_btn"];
   Controls["SetWorkZeroOffset_btn"]->Enabled = true;
   //////////////////////////////////////////////////
   short WorkZeroOffsetNo = 0;
   short WorkZeroOffsetType = 0;
   int SelRows = WorkZeroOffsets_dgv->SelectedRows->Count;
   int SelCells = WorkZeroOffsets_dgv->SelectedCells->Count;
   if (SelRows == 0 && SelCells > 0) WorkZeroOffsets_dgv->SelectedCells[0]->OwningRow->Selected = true;
   if (SelRows > 1) { MessageBox::Show("Select Only one WorkZeroOffset"); return; }
   int CurrRowindex = WorkZeroOffsets_dgv->CurrentRow->Index;
   WorkZeroOffsetNo = short::Parse(WorkZeroOffsets_dgv->CurrentRow->Cells[0]->Value->ToString());
   //WorkZeroOffsetType = short::Parse(WorkZeroOffsets_dgv->CurrentRow->Cells[2]->Value->ToString());
   WorkZeroOffsetX_tb->Enabled = true; WorkZeroOffsetY_tb->Enabled = true; WorkZeroOffsetZ_tb->Enabled = true;
   WorkZeroOffsetX_tb->Text = Convert::ToSingle(WorkZeroOffsets_dgv->CurrentRow->Cells[1]->Value).ToString("N3");
   WorkZeroOffsetY_tb->Text = Convert::ToSingle(WorkZeroOffsets_dgv->CurrentRow->Cells[2]->Value).ToString("N3");
   WorkZeroOffsetZ_tb->Text = Convert::ToSingle(WorkZeroOffsets_dgv->CurrentRow->Cells[3]->Value).ToString("N3");
   
   WorkZeroOffset_no_lbl->Text = "WorkZeroOffset No: " + WorkZeroOffsetNo.ToString();
  }
private: System::Void downloadNCToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    List <Control^> DynamicControls;
    for each (Control^ ctrl in this->Controls)
    {
        if (ctrl->Tag == "Dynamic")DynamicControls.Add(ctrl);

    }
    for each (Control^ ctrl in DynamicControls)
    {
        Controls->Remove(ctrl);
    }
    
    Button^ DownloadNCFile_btn = gcnew Button(); DownloadNCFile_btn->Name = "DownloadNCFile_btn"; DownloadNCFile_btn->Text = "DOWNLOAD NC FILE"; DownloadNCFile_btn->Tag = "Dynamic"; DownloadNCFile_btn->SetBounds(250, 120, 125, 20);
    Button^ ZSurfInspectFile_btn = gcnew Button(); ZSurfInspectFile_btn->Name = "ZSurfInspectFile_btn"; ZSurfInspectFile_btn->Text = "OPEN SURFACE Z INSPECTION FILE"; ZSurfInspectFile_btn->Tag = "Dynamic"; ZSurfInspectFile_btn->SetBounds(250, 150, 220, 20);
    CheckBox^ ZSurfInspectFile_chkbox = gcnew CheckBox(); ZSurfInspectFile_chkbox->Name = "ZSurfInspectFile_chkbox"; ZSurfInspectFile_chkbox->Tag = "Dynamic"; ZSurfInspectFile_chkbox->Text = "CORRECT Z FLATNESS DEFECTS"; ZSurfInspectFile_chkbox->SetBounds(500, 150, 200, 20);
    DownloadNCFile_btn->Click += gcnew EventHandler(this, &MainForm::DownloadNCFile_btn_Click);
    ZSurfInspectFile_btn->Click += gcnew EventHandler(this, &MainForm::ZSurfInspectFile_btn_Click);
    Controls->Add(DownloadNCFile_btn);
    Controls->Add(ZSurfInspectFile_btn);
    Controls->Add(ZSurfInspectFile_chkbox);
}
        private: System::Void DownloadNCFile_btn_Click(System::Object^ sender, System::EventArgs^ e)
        {
            StreamReader^ NCFileStreamReader;
            
            OpenFileDialog^ DownloadNCFileDlg = gcnew OpenFileDialog();
            DownloadNCFileDlg->InitialDirectory = "C:\\TEMP\\";
            DownloadNCFileDlg->Filter= "NC Files (*.nc)|*.nc|All files (*.*)|*.*";
            DownloadNCFileDlg->FilterIndex = 1;
            DownloadNCFileDlg->RestoreDirectory = true;
            if (DownloadNCFileDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                NCFileStreamReader = gcnew StreamReader(DownloadNCFileDlg->FileName);   
            }
            

            FocasDownloadNCFile(this,NCFileStreamReader, ZSurfInspectStreamReader);
            NCFileStreamReader->Close();
            ZSurfInspectStreamReader->Close();
        }
  private: System::Void ZSurfInspectFile_btn_Click(System::Object^ sender, System::EventArgs^ e)
  {
      //StreamReader^ ZSurfInspectStreamReader;
      OpenFileDialog^ ZSurfInspectFileDlg = gcnew OpenFileDialog();
      ZSurfInspectFileDlg->InitialDirectory = "C:\\TEMP\\";
      ZSurfInspectFileDlg->Filter = "NC Files (*.txt)|*.txt|All files (*.*)|*.*";
      ZSurfInspectFileDlg->FilterIndex = 1;
      ZSurfInspectFileDlg->RestoreDirectory = true;
      if (ZSurfInspectFileDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
          ZSurfInspectStreamReader = gcnew StreamReader(ZSurfInspectFileDlg->FileName);
          
      }
      
      
  }
}; // end of class MainForm
} // end of namespace FanucMillTools

