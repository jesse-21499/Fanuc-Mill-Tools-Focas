#include "pch.h"
#include "MainForm.h"
#include "FanucMillTools.h"
namespace FanucMillTools
{
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew FanucMillTools::MainForm());
  return 0;
}
short FocasReadNumParams(Form^MainFrm)
{
    ODBPARANUM ParamsNum;
    TextBox^ FromParam_tb = (TextBox^)MainFrm->Controls["FromParam_tb"];
    TextBox^ ToParam_tb = (TextBox^)MainFrm->Controls["ToParam_tb"];
    unsigned short Param_min = 0;    //minimum number of parameter
    unsigned short Param_max = 0;    //maximum number of parameter
    unsigned short Total_Params = 0;    //total number of parameter
    short ret = cnc_rdparanum(FHndl, &ParamsNum); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparanum: " + ret.ToString()); return ret; }
    Param_min = ParamsNum.para_min;
    Param_max = ParamsNum.para_max;
    FromParam_tb->Text = Param_min.ToString();
    ToParam_tb->Text = Param_max.ToString();
    MaxParamNo = ParamsNum.para_max;
    return ret;
}



short FocasReadParams(Form^ MainFrm)
{   DataGridView^ Params_dgv = (DataGridView^) MainFrm->Controls["Params_dgv"];
    TextBox^ FromParam_tb=(TextBox^)MainFrm->Controls["FromParam_tb"];
    TextBox^ ToParam_tb=(TextBox^)MainFrm->Controls["ToParam_tb"];
    Label^ FromParam_lbl=(Label^)MainFrm->Controls["FromParam_lbl"];
    Label^ ToParam_lbl=(Label^)MainFrm->Controls["ToParam_lbl"];
    Label^ Param_no_lbl=(Label^)MainFrm->Controls["Param_no_lbl"];
    TextBox^ CNC_IP_tb=(TextBox^)MainFrm->Controls["CNC_IP_tb"];
    String^ CncIP=CNC_IP_tb->Text;
    Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
    Params_dgv->Rows->Clear();
    InfoLabel_lbl->Visible = true;
    InfoLabel_lbl->Text = "READING PARAMETERS FROM CNC";
    InfoLabel_lbl->BackColor = Color::Orange;
    InfoLabel_lbl->Update();
    /////////////////////////
    short ret = 0;//return value
    ODBSYS CncSysInfo;
    IODBPSD Param;
    short StartParam = 0;
    short ParamsToRead = 100; //Limit to 100 in each iteration to avoid overflow
    ODBPARAIF2 ParamInfo[100];
    IODBPRM ParamExtens;
    long prm_no[1];
    unsigned short ParamInfoNum = 0;
    short PrevParam = 0;
    short NextParam = 0;
    short ParamNo = 0; //Parameter Number
    short ParamAttrib = 0;
    short ParamType = 0;
    bool IsAxisParam_attr = 0;
    bool IsSignedParam_attr = 0;
    bool Param_SettingsInput_attr = 0;
    bool Param_WriteProtect_attr = 0;
    bool Param_PowerMBeOff_atrr = 0;
    bool Param_ReadProtect_attr = 0;
    bool Param_Spindle_attr = 0;
    short Param_reserved = 0;
    short Param_reserved2 = 0;
    bool Param_IsRealType_attr = 0;
    short ParamSize = 0;
    String^ ParamArrangeType = "";
    String^ ParamUnitType = "";
    String^ ParamUnitDimens = "";
    String^ ParamInputType = "";
    String^ ParamDisplay = "";
    String^ ParamOthers = "";
    BYTE cdata = 0, cdata_x = 0, cdata_y = 0, cdata_z = 0;
    String^ s_cdata = ""; //String representation (8-bits Binary format string in case of 8-BIT Parameter TYpe)
    String^ s_cdata_x = "";
    String^ s_cdata_y = "";
    String^ s_cdata_z = "";
    String^ s_idata = ""; String^ s_idata_x = ""; String^ s_idata_y = ""; String^ s_idata_z = "";
    String^ s_ldata = ""; String^ s_ldata_x = ""; String^ s_ldata_y = ""; String^ s_ldata_z = "";
    String^ s_rdata = ""; String^ s_rdata_x = ""; String^ s_rdata_y = ""; String^ s_rdata_z = "";
    BYTE ParamType_UpperByte, ParamAxis_LowerByte;
    String^ strParamType = "";
    String^ ParamAxis = "";
    DateTime now_time = DateTime::Now;
    String^ ActualDate = now_time.ToString("MM/dd/yyyy HH:mm:ss");
    //////////////////////////////////////////////////
    short FromParam = short::Parse(FromParam_tb->Text);
    short ToParam = short::Parse(ToParam_tb->Text);
    short Total_Params = ToParam - FromParam + 1;
    //////////////////////////////////////////////////
    ret = cnc_sysinfo(FHndl, &CncSysInfo); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_sysinfo: " + ret.ToString()); return ret; }
    short NumAxes = (short)atoi(CncSysInfo.axes);
    short ParamLength = 0;
    StartParam = FromParam;
    
    
    //////////////////////////////////////////////////
    for (int i = 0; i <= (Total_Params / ParamsToRead) + 1; i++)
    {
        ret = cnc_rdparainfo3(FHndl, StartParam, &ParamsToRead, &PrevParam, &NextParam, ParamInfo); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparainfo3: " + ret.ToString()); return ret; }
        for (int j = 0; j < ParamsToRead; j++)
        {
            ParamNo = ParamInfo[j].prm_no;
            if ((ParamNo > ToParam) || (ParamNo > MaxParamNo))break;
            prm_no[0] = ParamNo;
            ret = cnc_rdparam_ext(FHndl, prm_no, 1, &ParamExtens); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparam_ext: " + ret.ToString() + "Param: " + ParamNo.ToString()); return ret; }
            if (ParamNo != ParamExtens.datano) { MessageBox::Show("ParamNo != ParamExtens.datano: " + "Param: " + ParamNo.ToString()); return ret; }
            
            switch (ParamExtens.type)
            {
            case 0:
                ParamSize = 1;
                break;
            case 1:
                ParamSize = 1;
                break;
            case 2:
                ParamSize = 2;
                break;
            case 3:
                ParamSize = 4;
                break;
            case 4:
                ParamSize = 8;
                break;
            case -1:
                MessageBox::Show("INVALID PARAMETER TYPE (-1) " + "Parameter_No" + ParamNo.ToString());
                break;
            }
            IsAxisParam_attr = GetBit(ParamExtens.axis, 0);
            Param_Spindle_attr = GetBit(ParamExtens.axis, 1);
            IsSignedParam_attr = !GetBit(ParamExtens.info, 0);
            Param_SettingsInput_attr = GetBit(ParamExtens.info, 1);
            Param_WriteProtect_attr = !GetBit(ParamExtens.info, 2);
            Param_PowerMBeOff_atrr = GetBit(ParamExtens.info, 3);
            Param_ReadProtect_attr = !GetBit(ParamExtens.info, 4);
            
            switch (ParamInfo[j].array)
            {
            case 0:
                ParamArrangeType = "Independent";
                break;
            case 1:
                ParamArrangeType = "Axes";
                break;
            case 2:
                ParamArrangeType = "Spindle";
                break;
            case 3:
                ParamArrangeType = "Paths";
                break;
            case 4:
                ParamArrangeType = "Machine Group";
                break;
            default:
                break;
            }
            switch (ParamInfo[j].unit)
            {
            case 0:
                ParamUnitType = "No Real Type";
                break;
            case 1:
                ParamUnitType = "Input Unit";
                break;
            case 2:
                ParamUnitType = "Output Unit";
                break;
            case 3:
                ParamUnitType = "Offset Unit";
                break;
            default:
                break;
            }
            switch (ParamInfo[j].dim)
            {
            case 0:
                ParamUnitDimens = "Without Unit";
                break;
            case 1:
                ParamUnitDimens = "Length Unit";
                break;
            case 2:
                ParamUnitDimens = "Angle Unit";
                break;
            case 3:
                ParamUnitDimens = "Length+Angle Unit";
                break;
            case 4:
                ParamUnitDimens = "Velocity Unit";
                break;
            default:
                break;
            }
            switch (ParamInfo[j].input)
            {
            case 0:
                ParamInputType = "Normal";
                break;
            case 1:
                ParamInputType = "Setting Parameter";
                break;
            case 2:
                ParamInputType = "Input Prohibit";
                break;
            default:
                break;
            }
            ParamDisplay = "";
            ParamOthers = "";
            bool DisplayBit0 = GetBit(ParamInfo->display, 0);
            if (DisplayBit0 == 1)ParamDisplay = "Symbol Exists";
            bool DisplayBit1 = GetBit(ParamInfo->display, 1);
            if (DisplayBit1 == 1) ParamDisplay = String::Concat(ParamDisplay, ";Top of Group");
            bool DisplayBit2 = GetBit(ParamInfo->display, 2);
            if (DisplayBit2 == 1) ParamDisplay = String::Concat(ParamDisplay, ";Bottom of Group");
            bool DisplayBit3 = GetBit(ParamInfo->display, 3);
            if (DisplayBit3 == 1) ParamDisplay = String::Concat(ParamDisplay, ";Gap Required");
            bool OthersBit0 = GetBit(ParamInfo->others, 0);
            if (OthersBit0 == 1) ParamOthers = "Unsigned";
            bool OthersBit1 = GetBit(ParamInfo->others, 1);
            if (OthersBit1 == 1) ParamOthers = String::Concat(ParamOthers, ";Power Off Required");
            bool OthersBit2 = GetBit(ParamInfo->others, 2);
            if (OthersBit2 == 1) ParamOthers = String::Concat(ParamOthers, ";Not Output");
            bool OthersBit3 = GetBit(ParamInfo->others, 3);
            if (OthersBit3 == 1) ParamOthers = String::Concat(ParamOthers, ";Not Compared");
            bool OthersBit4 = GetBit(ParamInfo->others, 4);
            if (OthersBit4 == 1) ParamOthers = String::Concat(ParamOthers, ";Loader Attribute");
            ParamLength = 4 + (ParamSize * MAX_AXIS) + ParamSize;
            //ret = cnc_rdparam3(FHndl, ParamNo, ALL_AXES, ParamLength,0, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdParam3: " + ret.ToString()+ "Param: "+ParamNo.ToString()); return; }
            ret = cnc_rdparar(FHndl, &ParamNo, ALL_AXES, &ParamNo, &ParamLength, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparar: " + ret.ToString() + "Param: " + ParamNo.ToString()); return ret; }
            ParamType = Param.type;
            ParamType_UpperByte = (BYTE)(Param.type >> 8); //0:BIT 1:BYTE 2:WORD 3:2WRD 4:REAL
            ParamAxis_LowerByte = (BYTE)(Param.type & 0xFF);
            cdata = 0; s_idata = ""; s_ldata = ""; s_rdata = "";
            cdata_x = 0; cdata_y = 0; cdata_z = 0; s_idata_x = ""; s_idata_y = ""; s_idata_z = ""; s_ldata_x = ""; s_ldata_y = ""; s_ldata_z = ""; s_rdata_x = ""; s_rdata_y = ""; s_rdata_z = "";
            s_cdata = ""; s_cdata_x = "", s_cdata_y = "", s_cdata_z = "";
            switch (Param.type & 0xFF) //Lower Byte
            {
            case 0: //Parameter without axis
                ParamAxis = "";
                switch (Param.type >> 8) //Upper Byte 0:BitType(8bits) 1:ByteType 2:WordType 3:2-WordType 4:RealType
                {
                case 0:
                    strParamType = "8-BIT";
                    cdata = Param.u.cdata;
                    s_cdata = Convert::ToString(cdata, 2)->PadLeft(8, L'0');
                    s_idata = ""; s_ldata = ""; s_rdata = "";
                    break;
                case 1:
                    strParamType = "SBYTE"; //Signed byte
                    cdata = (SByte)Param.u.cdata;
                    s_cdata = Param.u.cdata.ToString();
                    s_idata = ""; s_ldata = ""; s_rdata = "";
                    break;
                case 2:
                    strParamType = "WORD";
                    s_idata = Param.u.idata.ToString();
                    s_cdata = ""; s_ldata = ""; s_rdata = "";
                    break;
                case 3:
                    strParamType = "DWORD";
                    s_ldata = Param.u.ldata.ToString();
                    s_cdata = ""; s_idata = ""; s_rdata = "";
                    break;
                case 4:
                    strParamType = "REAL";
                    s_rdata = (Param.u.rdata.prm_val * pow(10, -Param.u.rdata.dec_val)).ToString();
                    s_cdata = ""; s_idata = ""; s_ldata = "";
                    break;
                default:
                    break;
                }
                
                Params_dgv->Rows->Add(CncIP, ParamNo, ParamType, strParamType, ParamAxis, s_cdata, s_idata, s_ldata, s_rdata, s_cdata_x, s_cdata_y, s_cdata_z, s_idata_x, s_idata_y, s_idata_z, s_ldata_x, s_ldata_y, s_ldata_z, s_rdata_x, s_rdata_y, s_rdata_z, IsAxisParam_attr, Param_Spindle_attr, IsSignedParam_attr, Param_SettingsInput_attr, Param_WriteProtect_attr, Param_PowerMBeOff_atrr, Param_ReadProtect_attr, ParamArrangeType, ParamUnitType, ParamUnitDimens, ParamInputType, ParamDisplay, ParamOthers, ActualDate);
                break;
            case 1:
                ParamAxis = "X";
                break;
            case 2:
                ParamAxis = "Y";
                break;
            case 3:
                ParamAxis = "Z";
                break;
            case 0xFF: //(Lower Byte 255 (-1) Parameter with All Axis
                ParamAxis = "ALL_AXES";
                for (short k = 0; k < NumAxes; k++)
                {
                    switch (Param.type >> 8) //Upper Byte 0:BitType 1:ByteType 2:WordType 3:DWordType 4:RealType
                    {
                    case 0:
                        strParamType = "8-BIT";
                        if (k == 0) { cdata_x = Param.u.cdatas[k]; s_cdata_x = Convert::ToString(cdata_x, 2)->PadLeft(8, L'0'); s_idata_x = ""; s_ldata_x = ""; s_rdata_x = ""; }
                        if (k == 1) { cdata_y = Param.u.cdatas[k]; s_cdata_y = Convert::ToString(cdata_y, 2)->PadLeft(8, L'0'); s_idata_y = ""; s_ldata_y = ""; s_rdata_y = ""; }
                        if (k == 2) { cdata_z = Param.u.cdatas[k]; s_cdata_z = Convert::ToString(cdata_z, 2)->PadLeft(8, L'0'); s_idata_z = ""; s_ldata_z = ""; s_rdata_z = ""; }
                        break;
                    case 1:
                        strParamType = "SBYTE"; //Signed Byte
                        if (k == 0) { cdata_x = (SByte)Param.u.cdatas[k]; s_cdata_x = Param.u.cdatas[k].ToString(); s_idata_x = ""; s_ldata_x = ""; s_rdata_x = ""; }
                        if (k == 1) { cdata_y = (SByte)Param.u.cdatas[k]; s_cdata_y = Param.u.cdatas[k].ToString(); s_idata_y = ""; s_ldata_y = ""; s_rdata_y = ""; }
                        if (k == 2) { cdata_z = (SByte)Param.u.cdatas[k]; s_cdata_z = Param.u.cdatas[k].ToString(); s_idata_z = ""; s_ldata_z = ""; s_rdata_z = ""; }
                        break;
                    case 2:
                        strParamType = "WORD";
                        if (k == 0) { s_idata_x = Param.u.idatas[k].ToString(); s_cdata_x = ""; s_ldata_x = ""; s_rdata_x = ""; }
                        if (k == 1) { s_idata_y = Param.u.idatas[k].ToString(); s_cdata_y = ""; s_ldata_y = ""; s_rdata_y = ""; }
                        if (k == 2) { s_idata_z = Param.u.idatas[k].ToString(); s_cdata_z = ""; s_ldata_z = ""; s_rdata_z = ""; }
                        
                        break;
                    case 3:
                        strParamType = "DWORD";
                        if (k == 0) { s_ldata_x = Param.u.ldatas[k].ToString(); s_cdata_x = ""; s_idata_x = ""; s_rdata_x = ""; }
                        if (k == 1) { s_ldata_y = Param.u.ldatas[k].ToString(); s_cdata_y = ""; s_idata_y = ""; s_rdata_y = ""; }
                        if (k == 2) {
                            s_ldata_z = Param.u.ldatas[k].ToString(); s_cdata_z = ""; s_idata_z = ""; s_rdata_z = "";
                        }
                        
                        break;
                    case 4:
                        strParamType = "REAL";
                        if (k == 0) { s_rdata_x = (Param.u.rdatas[k].prm_val * pow(10, -Param.u.rdatas[k].dec_val)).ToString(); s_cdata_x = ""; s_idata_x = ""; s_ldata_x = ""; }
                        if (k == 1) { s_rdata_y = (Param.u.rdatas[k].prm_val * pow(10, -Param.u.rdatas[k].dec_val)).ToString(); s_cdata_y = ""; s_idata_y = ""; s_ldata_y = ""; }
                        if (k == 2) { s_rdata_z = (Param.u.rdatas[k].prm_val * pow(10, -Param.u.rdatas[k].dec_val)).ToString(); s_cdata_z = ""; s_idata_z = ""; s_ldata_z = ""; }
                        //s_cdata_x = ""; s_cdata_y = ""; s_cdata_z = "";
                        break;
                    default:
                        break;
                    }
                }
                
                Params_dgv->Rows->Add(CncIP, ParamNo, ParamType, strParamType, ParamAxis, s_cdata, s_idata, s_ldata, s_rdata, s_cdata_x, s_cdata_y, s_cdata_z, s_idata_x, s_idata_y, s_idata_z, s_ldata_x, s_ldata_y, s_ldata_z, s_rdata_x, s_rdata_y, s_rdata_z, IsAxisParam_attr, Param_Spindle_attr, IsSignedParam_attr, Param_SettingsInput_attr, Param_WriteProtect_attr, Param_PowerMBeOff_atrr, Param_ReadProtect_attr, ParamArrangeType, ParamUnitType, ParamUnitDimens, ParamInputType, ParamDisplay, ParamOthers, ActualDate);
                
                break;
            default:
                break;
            }
            StartParam = ParamNo + 1;
            Param_no_lbl->Text = "Param No: " + ParamNo.ToString();
            Param_no_lbl->Update();
        }
    }
    
    InfoLabel_lbl->BackColor = Color::Transparent;
    InfoLabel_lbl->Visible = false;
    return ret;
}
short FocasConnect(Form^ MainFrm)
{   if (Connected) {MessageBox::Show("ALREADY CONNECTED"); return 0; }
    TextBox^ CNC_IP_tb = (TextBox^)MainFrm->Controls["CNC_IP_tb"];
    TextBox^ FocasHndl_tb = (TextBox^)MainFrm->Controls["FocasHndl_tb"];
    Button^ Connect_btn=(Button^)MainFrm->Controls["Connect_btn"];
    Button^ Disconnect_btn = (Button^)MainFrm->Controls["Disconnect_btn"];
    msclr::interop::marshal_context ctx;
    CNC_IP = ctx.marshal_as<const char*>(CNC_IP_tb->Text);
    CNC_Port = 8193;
    int Connect_timeout = 10;
    short ret = cnc_allclibhndl3(CNC_IP, CNC_Port, Connect_timeout, &FHndl);
    FocasReadCNCInfo(MainFrm);
    if (ret == EW_OK)
    {   FocasHndl_tb->Text = FHndl.ToString();
        Connect_btn->BackColor = Color::Green;
        Connect_btn->Text = "CONNECTED";
        Connected = true;
    }
    if (ret != EW_OK)
    {
        MessageBox::Show("Unable to connect to " + CNC_IP_tb->Text + " On Port " + CNC_Port.ToString() + "\nReturn Code: " + ret.ToString() + "\nExiting....");
        Connected = false;
    }
    return ret;
}
short FocasDisconnect(Form^ MainFrm)
{  short ret = cnc_freelibhndl(FHndl);
    if (ret==EW_OK)
    {

    TextBox^ FocasHndl_tb = (TextBox^)MainFrm->Controls["FocasHndl_tb"];
    FocasHndl_tb->Text = "0";
    Button^ Connect_btn = (Button^)MainFrm->Controls["Connect_btn"];
    Connect_btn->BackColor = Color::Transparent;
    Connect_btn->Text = "CONNECT";
    Label^ CncInfo_lbl = (Label^)MainFrm->Controls["CncInfo_lbl"];
    CncInfo_lbl->Visible = false;
    Connected = false;
    }
    if (ret != EW_OK)
    { MessageBox::Show("Error returned by cnc_freelibhndl: " + ret.ToString()); return ret; }
    return ret;
}
short FocasWriteParam(Form^ MainFrm)
{DataGridView^ Params_dgv = (DataGridView^)MainFrm->Controls["Params_dgv"];
 TextBox^ Param_data_tb = (TextBox^)MainFrm->Controls["Param_data_tb"];
 TextBox^ Param_Xdata_tb = (TextBox^)MainFrm->Controls["Param_Xdata_tb"];
 TextBox^ Param_Ydata_tb = (TextBox^)MainFrm->Controls["Param_Ydata_tb"];
 TextBox^ Param_Zdata_tb = (TextBox^)MainFrm->Controls["Param_Zdata_tb"];
 Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
 InfoLabel_lbl->Visible = true;
 InfoLabel_lbl->BackColor = Color::Orange;
 InfoLabel_lbl->Text = "WRITING PARAMETER TO CNC";
 InfoLabel_lbl->Update();
 IODBPSD Param;
 short ParamType = 0;
 int SelRows = Params_dgv->SelectedRows->Count;
 int SelCells = Params_dgv->SelectedCells->Count;
 msclr::interop::marshal_context ctx;
 const char* cdata = nullptr;
 const char* cdataX = nullptr;
 const char* cdataY = nullptr;
 const char* cdataZ = nullptr;
 const char* rdata = nullptr;
 cdata= ctx.marshal_as<const char*>(Param_data_tb->Text);
 int DecPointPos = 0;
 String^ str1 = ""; String^ str2 = "";
 int strlen = 0;
 if (SelRows == 0 && SelCells > 0) Params_dgv->SelectedCells[0]->OwningRow->Selected = true;
 if (SelRows != 1) {MessageBox::Show("Select Only one parameter"); return 1; }
 int CurrRowindex = Params_dgv->CurrentRow->Index;
 Param.datano = short::Parse(Params_dgv->CurrentRow->Cells[1]->Value->ToString());
 ParamType = short::Parse(Params_dgv->CurrentRow->Cells[2]->Value->ToString());
 short NoAxis = 0;
 //REALPRM ParamRealPrm;
 switch (ParamType & 0xFF)
        {case 0:
            NoAxis = 1;
            Param.type = 0;
            switch (ParamType >> 8)
            {case 0:
               cdata = ctx.marshal_as<const char*>(Param_data_tb->Text);
               Param.u.cdata = (Byte) stoi(cdata, 0, 2);
                break;
            case 1:
               Param.u.cdata = SByte::Parse(Param_data_tb->Text);
                break;
            case 2:
               Param.u.idata = short::Parse(Param_data_tb->Text);
                break;
            case 3:
                Param.u.ldata = long::Parse(Param_data_tb->Text);
                break;
            case 4:
                strlen = Param_data_tb->Text->Length;
                DecPointPos = Param_data_tb->Text->IndexOf(".");
                if (DecPointPos!=-1)
                {
                str1 = Param_data_tb->Text->Substring(0, DecPointPos);
                str2 = Param_data_tb->Text->Substring(DecPointPos+1);
                rdata = ctx.marshal_as<const char*>(str1 + str2);
                Param.u.rdata.dec_val = strlen - DecPointPos - 1;
                }
                else
                {rdata = ctx.marshal_as<const char*>(Param_data_tb->Text);
                 Param.u.rdata.dec_val =0 ;
                }
                Param.u.rdata.prm_val=atol(rdata);
                break;
            }
            break;
        case 1:
            Param.type = 1;
            NoAxis = 1;
            break;
        case 2:
            Param.type = 2;
            NoAxis = 1;
            break;
        case 3:
            Param.type = 3;
            NoAxis = 1;
            break;
        case 0xFF:
            Param.type = -1;
            NoAxis = MAX_AXIS;
            switch (ParamType >> 8)
            {
            case 0:
                cdataX=ctx.marshal_as<const char*>(Param_Xdata_tb->Text);
                cdataY=ctx.marshal_as<const char*>(Param_Ydata_tb->Text);
                cdataZ=ctx.marshal_as<const char*>(Param_Zdata_tb->Text);
                Param.u.cdatas[0] = (Byte)stoi(cdataX, 0, 2);
                Param.u.cdatas[1] = (Byte)stoi(cdataY, 0, 2);
                Param.u.cdatas[2] = (Byte)stoi(cdataZ, 0, 2);
                break;
            case 1:
                Param.u.cdatas[0] = SByte::Parse(Param_Xdata_tb->Text);
                Param.u.cdatas[1] = SByte::Parse(Param_Ydata_tb->Text);
                Param.u.cdatas[2] = SByte::Parse(Param_Zdata_tb->Text);
                
                break;
            case 2:
                Param.u.idatas[0] = short::Parse(Param_Xdata_tb->Text);
                Param.u.idatas[1] = short::Parse(Param_Ydata_tb->Text);
                Param.u.idatas[2] = short::Parse(Param_Zdata_tb->Text);
                break;
            case 3:
                Param.u.ldatas[0] = long::Parse(Param_Xdata_tb->Text);
                Param.u.ldatas[1] = long::Parse(Param_Ydata_tb->Text);
                Param.u.ldatas[2] = long::Parse(Param_Zdata_tb->Text);
                break;
            case 4:
                strlen=Param_Xdata_tb->Text->Length;
                DecPointPos=Param_Xdata_tb->Text->IndexOf(".");
                if (DecPointPos!=-1)
                {
                str1=Param_Xdata_tb->Text->Substring(0,DecPointPos);
                str2=Param_Xdata_tb->Text->Substring(DecPointPos + 1);
                rdata=ctx.marshal_as<const char*>(str1+str2);
                Param.u.rdatas[0].dec_val = strlen - DecPointPos - 1;
                }
                else
                {rdata = ctx.marshal_as<const char*>(Param_Xdata_tb->Text);
                Param.u.rdatas[0].dec_val = 0;
                }
                Param.u.rdatas[0].prm_val = atol(rdata);
                strlen = Param_Ydata_tb->Text->Length;
                DecPointPos = Param_Ydata_tb->Text->IndexOf(".");
                if (DecPointPos!=-1)
                {
                str1 = Param_Ydata_tb->Text->Substring(0, DecPointPos);
                str2 = Param_Ydata_tb->Text->Substring(DecPointPos + 1);
                rdata = ctx.marshal_as<const char*>(str1 + str2);
                Param.u.rdatas[1].dec_val = strlen - DecPointPos - 1;
                }
                else
                {rdata = ctx.marshal_as<const char*>(Param_Ydata_tb->Text);
                 Param.u.rdatas[1].dec_val = 0;
                }
                Param.u.rdatas[1].prm_val = atol(rdata);
                strlen = Param_Zdata_tb->Text->Length;
                DecPointPos = Param_Zdata_tb->Text->IndexOf(".");
                if (DecPointPos!=-1)
                {
                str1 = Param_Zdata_tb->Text->Substring(0, DecPointPos);
                str2 = Param_Zdata_tb->Text->Substring(DecPointPos + 1);
                rdata = ctx.marshal_as<const char*>(str1 + str2);
                Param.u.rdatas[2].dec_val = strlen - DecPointPos - 1;
                }
                else
                {   rdata = ctx.marshal_as<const char*>(Param_Zdata_tb->Text);
                    Param.u.rdatas[2].dec_val = 0;
                }
                Param.u.rdatas[2].prm_val = atol(rdata);
                
                break;
            }
            break;
        }
        short ParamSize = 0;
        switch (ParamType >> 8)
        {
        case 0:
            ParamSize = 1;
            break;
        case 1:
            ParamSize = 1;
            break;
        case 2:
            ParamSize = 2;
            break;
        case 3:
            ParamSize = 4;
            break;
        case 4:
            ParamSize = 8;
            break;
        case -1:
            //MessageBox::Show("INVALID PARAMETER TYPE (-1) " + "Parameter_No" + ParamNo.ToString());
            break;
        }
    short ParamLength = 4 + (ParamSize * NoAxis);
    short ret = cnc_wrparam(FHndl, ParamLength, &Param); 
    if (ret == EW_OK)
    {
        InfoLabel_lbl->BackColor = Color::Transparent;
        InfoLabel_lbl->Visible = false;
        MessageBox::Show("UPDATED PARAMETER IN CNC");
    }
    if (ret != EW_OK)
    {
        InfoLabel_lbl->BackColor = Color::Transparent;
        InfoLabel_lbl->Visible = false;
        MessageBox::Show("ERROR: " + ret.ToString());

    }
    return ret;
    //Param_data_tb->Update();
}
short FocasReadCNCInfo(Form^ MainFrm)
{Label^ CncInfo_lbl = (Label^)MainFrm->Controls["CncInfo_lbl"];
 ODBSYS CNCSysInfo;
 short ret = cnc_sysinfo(FHndl, &CNCSysInfo); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_sysinfo: " + ret.ToString());return ret;}
 String^ Cnc_Type = gcnew String(CNCSysInfo.cnc_type, 0, 2);
 String^ Cnc_Serie = gcnew String(CNCSysInfo.series, 0, 4);
 String^ Cnc_Version = gcnew String(CNCSysInfo.version, 0, 4);
 String^ CncModel;
 if (GetBit(CNCSysInfo.addinfo, 1) == 1)Cnc_Type = Cnc_Type + "i";
 switch (ExtractBits(CNCSysInfo.addinfo, 8, 15))
 {case 1:
     CncModel = "MODEL A";
     break;
 case 2:
     CncModel = "MODEL B";
     break;
 case 3:
     CncModel = "MODEL C";
     break;
 case 4:
     CncModel = "MODEL D";
     break;
 case 6:
     CncModel = "MODEL F";
     break;
 }
 CncInfo_lbl->Text = "NC Type: " + Cnc_Type + " "+CncModel+ " Serie: " + Cnc_Serie + " Version: " + Cnc_Version;
 CncInfo_lbl->Visible = true;
 return ret;
}
short FocasReadToolOffsets(Form^ MainFrm)
{DataGridView^ ToolOffsets_dgv = (DataGridView^) MainFrm->Controls["ToolOffsets_dgv"];
 //Label^ FromToolOffset_lbl = (Label^)MainFrm->Controls["FromToolOffset_lbl"];
 TextBox^ FromToolOffset_tb = (TextBox^)MainFrm->Controls["FromToolOffset_tb"];
 //Label^ ToToolOffset_lbl = (Label^)MainFrm->Controls["ToToolOffset_lbl"];
 TextBox^ ToToolOffset_tb = (TextBox^)MainFrm->Controls["ToToolOffset_tb"];
 Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
 Label^ ToolOffset_no_lbl = (Label^)MainFrm->Controls["ToolOffset_no_lbl"];
 short FirstToolOffset = short::Parse(FromToolOffset_tb->Text);
 short LastToolOffset= short::Parse(ToToolOffset_tb->Text);
 ToolOffsets_dgv->Rows->Clear();
 InfoLabel_lbl->Visible = true;
 InfoLabel_lbl->Text = "READING TOOL OFFSETS FROM CNC";
 InfoLabel_lbl->BackColor = Color::Orange;
 InfoLabel_lbl->Update();
 short ToolOffsets = 0;
 short ToolOffMemType = 0;
 String^ sToolOffMemType = "";
 ODBTLINF ToolOffsInfo;
 ODBTLINF2 ToolOffsInfo2;
    ODBTOFS ToolOffsRad;
    ODBTOFS ToolOffsRadWear;
    ODBTOFS ToolOffsLen;
    ODBTOFS ToolOffsLenWear;
    IODBPSD Param;
    double ToolOffsetUnit = 0;
    bool AvailableXOffset = false;
    bool AvailableYOffset = false;
    bool AvailableZOffset = false;
    bool AvailableNoseRadOffset = false;
    bool AvailableImagToolNoseOffset = false;
    bool AvailableSecondGeomOffset = false;
    bool Available4thAxisOffset = false;
    bool Available5thAxisOffset = false;
    //Read tool offset information
    short ret = cnc_rdtofsinfo(FHndl, &ToolOffsInfo); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdtofsinfo: " + ret.ToString()); return ret;} 
    switch (ToolOffsInfo.ofs_type)
    {case 0:
     sToolOffMemType = "memory type A";
     break;
     case 1:
     sToolOffMemType = "memory type B"; //Includes wear offset
     break;
     case 2:
     sToolOffMemType = "memory type C";//Includes wear offset
     break;
     default:
     sToolOffMemType = "Not Specified";
     break;
    }
    ret = cnc_rdparam(FHndl, 5042, ALL_AXES, 4 + MAX_AXIS, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparam (Param 5042): " + ret.ToString()); return ret; }
    switch (Param.u.cdata)
    {case 0:
     ToolOffsetUnit = 0.001;
     break;
     case 1:
     ToolOffsetUnit = 0.01;
     break;
     case 2:
     ToolOffsetUnit = 0.0001;
     break;
     case 4:
     ToolOffsetUnit = 0.00001;
     break;
     case 8:
     ToolOffsetUnit = 0.000001;
     break;
    }
    ToolOffsets = ToolOffsInfo.use_no;
    //Read tool offset information (2) includes offsets available information
    ret = cnc_rdtofsinfo2(FHndl, &ToolOffsInfo2);  if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdtofsinfo2: " + ret.ToString()); return ret; }
    AvailableXOffset = GetBit(ToolOffsInfo2.ofs_enable, 0);
    AvailableYOffset = GetBit(ToolOffsInfo2.ofs_enable, 1);
    AvailableZOffset = GetBit(ToolOffsInfo2.ofs_enable, 2);
    AvailableNoseRadOffset = GetBit(ToolOffsInfo2.ofs_enable, 3);
    AvailableImagToolNoseOffset = GetBit(ToolOffsInfo2.ofs_enable, 4);
    AvailableSecondGeomOffset = GetBit(ToolOffsInfo2.ofs_enable, 5);
    Available4thAxisOffset = GetBit(ToolOffsInfo2.ofs_enable,7);
    Available5thAxisOffset = GetBit(ToolOffsInfo2.ofs_enable, 8);
    for (int i=FirstToolOffset;i<=LastToolOffset;i++)
    {ret = cnc_rdtofs(FHndl, i, 1, 8, &ToolOffsRad); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdtofs: " + ret.ToString()+ " Offset No (Radius): "+i.ToString()); return ret;}
     ret = cnc_rdtofs(FHndl, i, 0, 8, &ToolOffsRadWear); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdtofs: " + ret.ToString() + "Offset No (Radius Wear): " + i.ToString()); return ret;}
     ret = cnc_rdtofs(FHndl, i, 3, 8, &ToolOffsLen); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdtofs: " + ret.ToString() + "Offset No (Length): " + i.ToString()); return ret;}
     ret = cnc_rdtofs(FHndl, i, 2, 8, &ToolOffsLenWear); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdtofs: " + ret.ToString() + "Offset No (Length Wear): " + i.ToString()); return ret;}
     ToolOffsets_dgv->Rows->Add(ToolOffsRad.datano, ToolOffsLen.data * ToolOffsetUnit, ToolOffsLenWear.data * ToolOffsetUnit,ToolOffsRad.data * ToolOffsetUnit, ToolOffsRadWear.data * ToolOffsetUnit );
     ToolOffset_no_lbl->Text = "Tool No: " + i.ToString();
     ToolOffset_no_lbl->Update();
    }
    InfoLabel_lbl->BackColor = Color::Transparent;
    InfoLabel_lbl->Visible = false;
    //cnc_rdtofsr //Read tool offset value(area specified)
    //cnc_tofs_rnge //Read the effective setting range of tool offset value
    return ret;
}
short FocasWriteToolOffset(Form^ MainFrm)
{
    //cnc_wrtofsr //Write tool offset value(area specified)
    DataGridView^ ToolOffsets_dgv = (DataGridView^)MainFrm->Controls["ToolOffsets_dgv"];
    TextBox^ ToolRadius_tb = (TextBox^)MainFrm->Controls["ToolRadius_tb"];
    TextBox^ ToolRadiusWear_tb = (TextBox^)MainFrm->Controls["ToolRadiusWear_tb"];
    TextBox^ ToolLength_tb = (TextBox^)MainFrm->Controls["ToolLength_tb"];
    TextBox^ ToolLengthWear_tb = (TextBox^)MainFrm->Controls["ToolLengthWear_tb"];
    Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
    InfoLabel_lbl->Visible = true;
    InfoLabel_lbl->BackColor = Color::Orange;
    InfoLabel_lbl->Text = "WRITING TOOL OFFSET TO CNC";
    InfoLabel_lbl->Update();
    int SelRows = ToolOffsets_dgv->SelectedRows->Count;
    int SelCells = ToolOffsets_dgv->SelectedCells->Count;
    
    if (SelRows == 0 && SelCells > 0) ToolOffsets_dgv->SelectedCells[0]->OwningRow->Selected = true;
    if (SelRows != 1) { MessageBox::Show("Select only one ToolOffset"); return 1; }
    int CurrRowindex = ToolOffsets_dgv->CurrentRow->Index;
    short ToolOffsetNo = short::Parse(ToolOffsets_dgv->CurrentRow->Cells[0]->Value->ToString());
    IODBPSD Param;
    //float ToolOffsetUnit = 0;
    short DecimalsNum = 0;
    short ret = cnc_rdparam(FHndl, 5042, ALL_AXES, 4 + MAX_AXIS, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparam (Param 5042): " + ret.ToString()); return ret; }
    switch (Param.u.cdata)
    {
    case 0:
        //ToolOffsetUnit = 0.001;
        DecimalsNum = 3;
        break;
    case 1:
        //ToolOffsetUnit = 0.01;
        DecimalsNum = 2;
        break;
    case 2:
        //ToolOffsetUnit = 0.0001;
        DecimalsNum = 4;
        break;
    case 4:
        //ToolOffsetUnit = 0.00001;
        DecimalsNum = 5;
        break;
    case 8:
        //ToolOffsetUnit = 0.000001;
        DecimalsNum = 6;
        break;
    }
    
    if ((ToolLength_tb->Text->Length - ToolLength_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    if ((ToolLengthWear_tb->Text->Length - ToolLengthWear_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    if ((ToolRadius_tb->Text->Length - ToolRadius_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    if ((ToolRadiusWear_tb->Text->Length - ToolRadiusWear_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    
    ret = cnc_wrtofs(FHndl, ToolOffsetNo, 3, 8, Convert::ToInt32(Convert::ToSingle(ToolLength_tb->Text)*Math::Pow(10,DecimalsNum))); if (ret != EW_OK) goto finish; // Write Tool Length offset value
    ret = cnc_wrtofs(FHndl, ToolOffsetNo, 2, 8, Convert::ToInt32(Convert::ToSingle(ToolLengthWear_tb->Text)*Math::Pow(10,DecimalsNum))); if (ret != EW_OK) goto finish; // Write Tool Length Wear offset value
    ret = cnc_wrtofs(FHndl, ToolOffsetNo, 1, 8, Convert::ToInt32(Convert::ToSingle(ToolRadius_tb->Text)*Math::Pow(10,DecimalsNum))); if (ret != EW_OK) goto finish; // Write Tool Radius offset value
    ret = cnc_wrtofs(FHndl, ToolOffsetNo, 0, 8, Convert::ToInt32(Convert::ToSingle(ToolRadiusWear_tb->Text)*Math::Pow(10,DecimalsNum))); if (ret != EW_OK) goto finish; // Write Tool Radius Wear offset value
    InfoLabel_lbl->BackColor = Color::Transparent;
    InfoLabel_lbl->Visible = false;
    MessageBox::Show("UPDATED TOOL OFFSET IN CNC");
    finish:
    if (ret != EW_OK)
    {InfoLabel_lbl->BackColor = Color::Transparent;
     InfoLabel_lbl->Visible = false;
     MessageBox::Show("ERROR RETURNED BY cnc_wrtofs: " + ret.ToString());
    }
    return ret;
}
short FocasReadNumToolOffsets(Form^ MainFrm,short &ToolOffsets)
{
    short ret = 0;
    //TextBox^ FromToolOffset_tb = (TextBox^)MainFrm->Controls["FromToolOffset_tb"];
    //TextBox^ ToToolOffset_tb = (TextBox^)MainFrm->Controls["ToToolOffset_tb"];
    ToolOffsets = 0;
    //short ToolOffMemType = 0;
    //String^ sToolOffMemType = "";
    ODBTLINF ToolOffsInfo;
    //ODBTLINF2 ToolOffsInfo2;
    //ODBTOFS ToolOffsRad;
    //ODBTOFS ToolOffsRadWear;
    //ODBTOFS ToolOffsLen;
    //ODBTOFS ToolOffsLenWear;
    //IODBPSD Param;
    //float ToolOffsetUnit = 0;
    //bool AvailableXOffset = false;
    //bool AvailableYOffset = false;
    //bool AvailableZOffset = false;
    //bool AvailableNoseRadOffset = false;
    //bool AvailableImagToolNoseOffset = false;
    //bool AvailableSecondGeomOffset = false;
    //bool Available4thAxisOffset = false;
    //bool Available5thAxisOffset = false;
    //Read tool offset information
    ret = cnc_rdtofsinfo(FHndl, &ToolOffsInfo); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdtofsinfo: " + ret.ToString()); return ret; }
    //FromToolOffset_tb->Text = "1";
    ToolOffsets = ToolOffsInfo.use_no;
    //ToToolOffset_tb->Text = ToolOffsets.ToString();
    //ToToolOffset_tb->Update();
    return ret;
}
short FocasReadWorkZeroOffsets(Form^ MainFrm)
{
    short ret = 0;
    DataGridView^ WorkZeroOffsets_dgv = (DataGridView^)MainFrm->Controls["WorkZeroOffsets_dgv"];
    //Label^ FromToolOffset_lbl = (Label^)MainFrm->Controls["FromToolOffset_lbl"];
    TextBox^ FromWorkZeroOffset_tb = (TextBox^)MainFrm->Controls["FromWorkZeroOffset_tb"];
    //Label^ ToToolOffset_lbl = (Label^)MainFrm->Controls["ToToolOffset_lbl"];
    TextBox^ ToWorkZeroOffset_tb = (TextBox^)MainFrm->Controls["ToWorkZeroOffset_tb"];
    Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
    Label^ WorkZeroOffset_no_lbl = (Label^)MainFrm->Controls["WorkZeroOffset_no_lbl"];
    short FirstWorkZeroOffset = short::Parse(FromWorkZeroOffset_tb->Text);
    short LastWorkZeroOffset = short::Parse(ToWorkZeroOffset_tb->Text);
    WorkZeroOffsets_dgv->Rows->Clear();
    InfoLabel_lbl->Visible = true;
    InfoLabel_lbl->Text = "READING WORK ZERO OFFSETS FROM CNC";
    InfoLabel_lbl->BackColor = Color::Orange;
    InfoLabel_lbl->Update();
    //short WorkZeroOffsets = 0;
    //short ToolOffMemType = 0;
    //String^ sToolOffMemType = "";
    IODBZOFS WorkZeroOffset;
    IODBPSD Param;
    double ToolOffsetUnit = 0;
    ret = cnc_rdparam(FHndl, 1013, ALL_AXES, 4 + MAX_AXIS, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparam (Param 1013): " + ret.ToString()); return ret; }
    switch (Param.u.cdata)
    {
    case 0:
        ToolOffsetUnit = 0.001;
        break;
    case 1:
        ToolOffsetUnit = 0.01;
        break;
    case 2:
        ToolOffsetUnit = 0.0001;
        break;
    case 4:
        ToolOffsetUnit = 0.00001;
        break;
    case 8:
        ToolOffsetUnit = 0.000001;
        break;
    }
    //ToolOffsets = ToolOffsInfo.use_no;
    
    for (int i = FirstWorkZeroOffset; i < LastWorkZeroOffset; i++)
    {
        ret = cnc_rdzofs(FHndl, i, -1, 4+4*MAX_AXIS, &WorkZeroOffset); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdzofs: " + ret.ToString() + " Work Zero Offset No: " + i.ToString()); return ret; }
        
        WorkZeroOffsets_dgv->Rows->Add(WorkZeroOffset.datano, WorkZeroOffset.data[0] * ToolOffsetUnit, WorkZeroOffset.data[1] * ToolOffsetUnit, WorkZeroOffset.data[2] * ToolOffsetUnit);
        WorkZeroOffset_no_lbl->Text = "Work Zero Offset No: " + i.ToString();
        WorkZeroOffset_no_lbl->Update();
    }
    InfoLabel_lbl->BackColor = Color::Transparent;
    InfoLabel_lbl->Visible = false;
    
    return ret;
}
short FocasWriteWorkZeroOffset(Form^ MainFrm)
{
    //cnc_wrtofsr //Write WorkZero offset value(area specified)
    DataGridView^ WorkZeroOffsets_dgv = (DataGridView^)MainFrm->Controls["WorkZeroOffsets_dgv"];
    TextBox^ WorkZeroOffsetX_tb = (TextBox^)MainFrm->Controls["WorkZeroOffsetX_tb"];
    TextBox^ WorkZeroOffsetY_tb = (TextBox^)MainFrm->Controls["WorkZeroOffsetY_tb"];
    TextBox^ WorkZeroOffsetZ_tb = (TextBox^)MainFrm->Controls["WorkZeroOffsetZ_tb"];
    Label^ InfoLabel_lbl = (Label^)MainFrm->Controls["InfoLabel_lbl"];
    InfoLabel_lbl->Visible = true;
    InfoLabel_lbl->BackColor = Color::Orange;
    InfoLabel_lbl->Text = "WRITING WorkZero OFFSET TO CNC";
    InfoLabel_lbl->Update();
    int SelRows = WorkZeroOffsets_dgv->SelectedRows->Count;
    int SelCells = WorkZeroOffsets_dgv->SelectedCells->Count;

    if (SelRows == 0 && SelCells > 0) WorkZeroOffsets_dgv->SelectedCells[0]->OwningRow->Selected = true;
    if (SelRows != 1) { MessageBox::Show("Select only one WorkZeroOffset"); return 1; }
    int CurrRowindex = WorkZeroOffsets_dgv->CurrentRow->Index;
    short WorkZeroOffsetNo = short::Parse(WorkZeroOffsets_dgv->CurrentRow->Cells[0]->Value->ToString());
    IODBPSD Param;
    IODBZOFS WorkZeroOffset;
    //float WorkZeroOffsetUnit = 0;
    short DecimalsNum = 0;
    short ret = cnc_rdparam(FHndl, 1013, ALL_AXES, 4 + MAX_AXIS, &Param); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdparam (Param 1013): " + ret.ToString()); return ret; }
    switch (Param.u.cdata)
    {
    case 0:
        //WorkZeroOffsetUnit = 0.001;
        DecimalsNum = 3;
        break;
    case 1:
        //WorkZeroOffsetUnit = 0.01;
        DecimalsNum = 2;
        break;
    case 2:
        //WorkZeroOffsetUnit = 0.0001;
        DecimalsNum = 4;
        break;
    case 4:
        //WorkZeroOffsetUnit = 0.00001;
        DecimalsNum = 5;
        break;
    case 8:
        //WorkZeroOffsetUnit = 0.000001;
        DecimalsNum = 6;
        break;
    }

    if ((WorkZeroOffsetX_tb->Text->Length - WorkZeroOffsetX_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    if ((WorkZeroOffsetY_tb->Text->Length - WorkZeroOffsetY_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    if ((WorkZeroOffsetZ_tb->Text->Length - WorkZeroOffsetZ_tb->Text->IndexOf('.') - 1) != DecimalsNum) { MessageBox::Show("ENTER " + DecimalsNum + " DECIMALS"); ret = 1; goto finish; }
    WorkZeroOffset.datano = WorkZeroOffsetNo;
    WorkZeroOffset.type = -1;
    WorkZeroOffset.data[0] = Convert::ToInt32(Convert::ToSingle(WorkZeroOffsetX_tb->Text)*Math::Pow(10,DecimalsNum));
    WorkZeroOffset.data[1] = Convert::ToInt32(Convert::ToSingle(WorkZeroOffsetY_tb->Text) * Math::Pow(10, DecimalsNum));
    WorkZeroOffset.data[2] = Convert::ToInt32(Convert::ToSingle(WorkZeroOffsetZ_tb->Text) * Math::Pow(10, DecimalsNum));
    
    ret = cnc_wrzofs(FHndl,4+4*MAX_AXIS,&WorkZeroOffset); if (ret != EW_OK) goto finish; // Write WorkZero Offset value
    InfoLabel_lbl->BackColor = Color::Transparent;
    InfoLabel_lbl->Visible = false;
    MessageBox::Show("UPDATED WorkZero OFFSET IN CNC");
finish:
    if (ret != EW_OK)
    {
        InfoLabel_lbl->BackColor = Color::Transparent;
        InfoLabel_lbl->Visible = false;
        MessageBox::Show("ERROR RETURNED BY cnc_wrzofs: " + ret.ToString());
    }
    return ret;
}
short FocasDownloadNCFile(Form^ MainFrm,StreamReader^ NCFileStreamReader, StreamReader^ ZSurfInspectStreamReader)
{short ret = 0;
bool EndOfProgram = false;
//bool CorrectZSurfacePoints = false;
CheckBox^ ZSurfInspectFile_chkbox = (CheckBox^)MainFrm->Controls["ZSurfInspectFile_chkbox"];
bool CorrectZSurfacePoints = ZSurfInspectFile_chkbox->Checked;
 msclr::interop::marshal_context ctx;
 String^ NCFileLine;
 String^ ZSurfInspectFileLine;
 const char* cNCFileLine = "";
 int ZIndex = 0;
 int EndOfZIndex = 0;
 float ZDeviatCoord = 0;
 float FlatZ = 0;
 int FlatZIndex = 0;
 float CorrectedZ = 0;
 int CorrectedZIndex = 0;
 bool IsPointToCorrect = false;
 int InspectedPointNumb = 0;
 List<float> PointsZLevel;
 if (CorrectZSurfacePoints)
 {
  while (!ZSurfInspectStreamReader->EndOfStream)
  {ZSurfInspectFileLine=ZSurfInspectStreamReader->ReadLine();
   ZIndex = ZSurfInspectFileLine->IndexOf("Z");
   EndOfZIndex = ZSurfInspectFileLine->IndexOf("(");
   ZDeviatCoord = Convert::ToSingle(ZSurfInspectFileLine->Substring(ZIndex+1, EndOfZIndex - ZIndex - 1));
   PointsZLevel.Add(ZDeviatCoord);
  }
 }

 long NCLineLength = 1;
 ret = cnc_dwnstart3(FHndl, 0);
 ret = cnc_download3(FHndl, &NCLineLength, "\n;");
 while (!NCFileStreamReader->EndOfStream)
 {NCFileLine = NCFileStreamReader->ReadLine();
  if (NCFileLine->IndexOf("M30") != -1 || NCFileLine->IndexOf("M02") != -1) EndOfProgram = true;
  if (NCFileLine->IndexOf("%")!=-1 && EndOfProgram==false) continue;
  if (!(NCFileLine->IndexOf("%") != -1 && EndOfProgram == true)) NCFileLine += "\n";
  if (CorrectZSurfacePoints ) //Corrects flatness defects
  {
      IsPointToCorrect = (NCFileLine->LastIndexOf("(#") != -1 && NCFileLine->LastIndexOf(")") != -1 && NCFileLine->IndexOf("Z") != -1);
      if (IsPointToCorrect)
      {
      InspectedPointNumb = Convert::ToInt32(NCFileLine->Substring(NCFileLine->LastIndexOf("(#")+2, NCFileLine->LastIndexOf(")") - NCFileLine->LastIndexOf("(")-2));
      FlatZ = Convert::ToSingle(NCFileLine->Substring(NCFileLine->IndexOf("Z")+1, NCFileLine->IndexOf(" ", NCFileLine->IndexOf("Z") + 1) - NCFileLine->IndexOf("Z") - 1));
      CorrectedZ = FlatZ+PointsZLevel[InspectedPointNumb];
      NCFileLine=NCFileLine->Replace(FlatZ.ToString(), CorrectedZ.ToString());
      }
  }
  NCLineLength = NCFileLine->Length;
  cNCFileLine = ctx.marshal_as<const char*>(NCFileLine);
  ret=cnc_download3(FHndl, &NCLineLength,(char*) cNCFileLine);

 }
 
ret = cnc_dwnend3(FHndl);
MessageBox::Show("NC FILE REGISTERED IN CNC");
return ret;
}
short FocasReadMachinePos(Form^ MainFrm)
{NumberOfAxis = MAX_AXIS;
 Label^ XMachinePos_lbl = (Label^)MainFrm->Controls["XMachinePos_lbl"];
 Label^ YMachinePos_lbl = (Label^)MainFrm->Controls["YMachinePos_lbl"];
 Label^ ZMachinePos_lbl = (Label^)MainFrm->Controls["ZMachinePos_lbl"];
 Label^ XAbsPos_lbl = (Label^)MainFrm->Controls["XAbsPos_lbl"];
 Label^ YAbsPos_lbl = (Label^)MainFrm->Controls["YAbsPos_lbl"];
 Label^ ZAbsPos_lbl = (Label^)MainFrm->Controls["ZAbsPos_lbl"];
 Label^ XPos_lbl = (Label^)MainFrm->Controls["XPos_lbl"];
 Label^ YPos_lbl = (Label^)MainFrm->Controls["YPos_lbl"];
 Label^ ZPos_lbl = (Label^)MainFrm->Controls["ZPos_lbl"];
 Label^ XRelPos_lbl = (Label^)MainFrm->Controls["XRelPos_lbl"];
 Label^ YRelPos_lbl = (Label^)MainFrm->Controls["YRelPos_lbl"];
 Label^ ZRelPos_lbl = (Label^)MainFrm->Controls["ZRelPos_lbl"];
 Label^ XDTGPos_lbl = (Label^)MainFrm->Controls["XDTGPos_lbl"];
 Label^ YDTGPos_lbl = (Label^)MainFrm->Controls["YDTGPos_lbl"];
 Label^ ZDTGPos_lbl = (Label^)MainFrm->Controls["ZDTGPos_lbl"];
 Label^ SpindleSpeed_lbl = (Label^)MainFrm->Controls["SpindleSpeed_lbl"];
 Label^ FeedRate_lbl = (Label^)MainFrm->Controls["FeedRate_lbl"];
 Label^ CurrentTime_lbl = (Label^)MainFrm->Controls["CurrentTime_lbl"];
 Label^ EllapsedTime_lbl = (Label^)MainFrm->Controls["EllapsedTime_lbl"];
 Label^ ExecProgName_lbl = (Label^)MainFrm->Controls["ExecProgName_lbl"];
 Label^ GModalData_lbl = (Label^)MainFrm->Controls["GModalData_lbl"];
 Label^ NoGModalData_lbl = (Label^)MainFrm->Controls["NoGModalData_lbl"];
 ListBox^ ExecProg_lbox = (ListBox^)MainFrm->Controls["ExecProg_lbox"];
 ListBox^ MacroVars_lbox = (ListBox^)MainFrm->Controls["MacroVars_lbox"];
 //ODBEXEPRG ExecutingProgram;
 //char ExecProgName[256];
 ret = cnc_exeprgname2(FHndl, ExecProgName);if (ret!=EW_OK) {MessageBox::Show("Error returned by cnc_exeprgname2: " + ret.ToString()); return ret;}
 msclr::interop::marshal_context ctx;
 String^ ProgBlock;
 //gcnew String(ExecProgBlock);
 // CNC_IP = ctx.marshal_as<const char*>(CNC_IP_tb->Text);
 unsigned long ProgBlockNumb = 0;
 unsigned long ProgBlocksToRead = 1;
 unsigned long ProgBlockLength = 256;
 bool IsEndOfProgram = false;
 
 while (!IsEndOfProgram)
 {
     ProgBlocksToRead = 1;
     ProgBlockLength = 256;
     char ExecProgBlock[256] = "";
     ret = cnc_rdpdf_line(FHndl, ExecProgName, ProgBlockNumb, ExecProgBlock, &ProgBlocksToRead, &ProgBlockLength); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdpdf_line: " + ret.ToString()); return ret; }
     ProgBlock= gcnew String(ExecProgBlock);
     ExecProg_lbox->Items->Add(ProgBlock);
     if ((ProgBlock->IndexOf("%") != -1) && ProgBlockNumb > 0) IsEndOfProgram = true;
     ProgBlockNumb++;
 }
 for (int i = 1; i < 1200; i++)
 {
     if (i <= 33) MacroVars_lbox->Items->Add("#" + i.ToString());
     if (i>=34 && i<=133) MacroVars_lbox->Items->Add("#" + (i+66).ToString());
     if (i >=134) MacroVars_lbox->Items->Add("#" + (i +366).ToString());

 }
 
 ret = cnc_pdf_rdactpt(FHndl, ExecProgName, &ExecProgBlockNum); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_pdf_rdactpt: " + ret.ToString()); return ret; }
 
 
 //ODBPOS MachinePos[MAX_AXIS];
 ret = cnc_rdposition(FHndl,-1, &NumberOfAxis, MachinePos); if (ret != EW_OK) {MessageBox::Show("Error returned by cnc_rdposition: " + ret.ToString());return ret;}
 //ODBACT ActualSpindleSpeed;
 //ODBACT ActualFeedRate;
 ret = cnc_acts(FHndl, &ActualSpindleSpeed);if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_acts: " + ret.ToString()); return ret;}
 SpindleSpeed = ActualSpindleSpeed.data;
 ret = cnc_actf(FHndl, &ActualFeedRate); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_actf: " + ret.ToString()); return ret; }
 FeedRate = ActualFeedRate.data;
 
// ret = cnc_rdopnlsgnl(FHndl,6, &OutputSignalImage); if (ret != EW_OK) { MessageBox::Show("Error returned by cnc_rdopnlsgnl: " + ret.ToString()); return ret; }
 xAbs = MachinePos[0].abs.data * pow(10, -MachinePos[0].abs.dec);
 yAbs = MachinePos[1].abs.data * pow(10, -MachinePos[1].abs.dec);
 zAbs = MachinePos[2].abs.data * pow(10, -MachinePos[2].abs.dec);
 x = MachinePos[0].mach.data * pow(10, -MachinePos[0].mach.dec);
 y = MachinePos[1].mach.data * pow(10, -MachinePos[1].mach.dec);
 z = MachinePos[2].mach.data * pow(10, -MachinePos[2].mach.dec);
 xRel = MachinePos[0].rel.data * pow(10, -MachinePos[0].rel.dec);
 yRel = MachinePos[1].rel.data * pow(10, -MachinePos[1].rel.dec);
 zRel = MachinePos[2].rel.data * pow(10, -MachinePos[2].rel.dec);
 xDtg = MachinePos[0].dist.data * pow(10, -MachinePos[0].dist.dec);
 yDtg = MachinePos[1].dist.data * pow(10, -MachinePos[1].dist.dec);
 zDtg = MachinePos[2].dist.data * pow(10, -MachinePos[2].dist.dec);
 if (xDtg >= 0) XMachinePos_lbl->Text = "+MX"; else XMachinePos_lbl->Text = "-MX";
 if (yDtg >= 0) YMachinePos_lbl->Text = "+MY"; else YMachinePos_lbl->Text = "-MY";
 if (zDtg >= 0) ZMachinePos_lbl->Text = "+MZ"; else ZMachinePos_lbl->Text = "-MZ";
 XAbsPos_lbl->Text = xAbs.ToString();
 YAbsPos_lbl->Text = yAbs.ToString();
 ZAbsPos_lbl->Text = zAbs.ToString();
 XPos_lbl->Text = x.ToString();
 YPos_lbl->Text = y.ToString();
 ZPos_lbl->Text = z.ToString();
 XRelPos_lbl->Text = xRel.ToString();
 YRelPos_lbl->Text = yRel.ToString();
 ZRelPos_lbl->Text = zRel.ToString();
 XDTGPos_lbl->Text = xDtg.ToString();
 YDTGPos_lbl->Text = yDtg.ToString();
 ZDTGPos_lbl->Text = zDtg.ToString();
 SpindleSpeed_lbl->Text = "S "+SpindleSpeed.ToString()+ " rpm";
 FeedRate_lbl->Text = "F " + FeedRate + " mm/min";
 ExecProgName_lbl->Text = gcnew String(ExecProgName);
 return ret;
}
short FocasMonitorMachinePos(Form^ MainFrm,Stopwatch^ stopwatch)
{    
    //ret = pmc_rdpmcrng(FHndl, 1, 0, 0, 0, 9, &IODBPmc); if (ret != EW_OK) { return ret; }
    //if (GetBit(IODBPmc.u.cdata[0], 7) == 1) OperationSignal = 1; else OperationSignal = 0;
    ret = cnc_statinfo(FHndl, &MachineStatusInfo); if (ret != EW_OK) { return ret; }
    MachineIsMoving = MachineStatusInfo.motion;
    
    
        PreviousBlockNumb = ExecProgBlockNum;
        ret = cnc_pdf_rdactpt(FHndl, ExecProgName, &ExecProgBlockNum); if (ret != EW_OK) { return ret; }
        //Read modal data
        if (ExecProgBlockNum > PreviousBlockNumb)
        {
            ret = cnc_modal(FHndl, -1, 0, &GModalData); if (ret != EW_OK) return ret;
            MainFrm->Controls["GModalData_lbl"]->Text = GetGModalData(GModalData);
            //ret = cnc_modal(FHndl, -3, 0, &NoGAxisModalData);
            ret = cnc_modal(FHndl, -2, 0, &NoGModalData); if (ret != EW_OK) return ret;
            MainFrm->Controls["NoGModalData_lbl"]->Text = GetNoGModalData(NoGModalData);
            /*
            FirstMacroVariable = 1;
            NumbOfMacroVarsToRead = 33;
            
             ret = cnc_rdmacror2(FHndl, FirstMacroVariable, &NumbOfMacroVarsToRead, MacroVars1); if (ret != EW_OK) { return ret; }
            for (int i = 1; i <= 33; i++)
            {
                
                ((ListBox^)MainFrm->Controls["MacroVars_lbl"])->Items[i-1] = "#" + i.ToString()+ "="+ MacroVars1[i-1].ToString();
            }
            FirstMacroVariable = 100;
            NumbOfMacroVarsToRead = 100;
            ret = cnc_rdmacror2(FHndl, FirstMacroVariable, &NumbOfMacroVarsToRead, MacroVars2); if (ret != EW_OK) { return ret; }
            for (int i = 1; i <= 100; i++)
            {
                ((ListBox^)MainFrm->Controls["MacroVars_lbl"])->Items[i+32] = "#" + (i+99).ToString() + "=" + MacroVars2[i-1].ToString();
            }
            FirstMacroVariable = 500;
            NumbOfMacroVarsToRead = 1067;
            ret = cnc_rdmacror2(FHndl, FirstMacroVariable, &NumbOfMacroVarsToRead, MacroVars3); if (ret != EW_OK) { return ret; }
            for (int i = 1; i <= 1067; i++)
            {
                ((ListBox^)MainFrm->Controls["MacroVars_lbl"])->Items[i+132] = "#" + (i + 499).ToString() + "=" + MacroVars3[i-1].ToString();
            }
            */
        }
        if (MachineIsMoving == 1)
        {//ret=cnc_rdexecpt(FHndl,)
        ret = cnc_rdposition(FHndl, -1, &NumberOfAxis, MachinePos); if (ret != EW_OK) {  return ret; }
        //ODBACT ActualSpindleSpeed;
        //ODBACT ActualFeedRate;
        ret = cnc_acts(FHndl, &ActualSpindleSpeed); if (ret != EW_OK) { return ret; }
        SpindleSpeed = ActualSpindleSpeed.data;
        ret = cnc_actf(FHndl, &ActualFeedRate); if (ret != EW_OK) { return ret; }
        FeedRate = ActualFeedRate.data;
        //IODBSGNL OutputSignalImage;
        //ret = cnc_rdopnlsgnl(FHndl, 6, &OutputSignalImage);  if (ret != EW_OK) { stopwatch->Stop(); MessageBox::Show("Error returned by cnc_rdopnlsgnl: " + ret.ToString()); stopwatch->Stop();  return ret; }//Spindle Speed Override (Not available in Fanuc 30i-31i series)
        xAbs = MachinePos[0].abs.data * pow(10, -MachinePos[0].abs.dec);
        yAbs = MachinePos[1].abs.data * pow(10, -MachinePos[1].abs.dec);
        zAbs = MachinePos[2].abs.data * pow(10, -MachinePos[2].abs.dec);
        x = MachinePos[0].mach.data * pow(10, -MachinePos[0].mach.dec);
        y = MachinePos[1].mach.data * pow(10, -MachinePos[1].mach.dec);
        z = MachinePos[2].mach.data * pow(10, -MachinePos[2].mach.dec);
        xRel = MachinePos[0].rel.data * pow(10, -MachinePos[0].rel.dec);
        yRel = MachinePos[1].rel.data * pow(10, -MachinePos[1].rel.dec);
        zRel = MachinePos[2].rel.data * pow(10, -MachinePos[2].rel.dec);
        xDtg = MachinePos[0].dist.data * pow(10, -MachinePos[0].dist.dec);
        yDtg = MachinePos[1].dist.data * pow(10, -MachinePos[1].dist.dec);
        zDtg = MachinePos[2].dist.data * pow(10, -MachinePos[2].dist.dec);
        MainFrm->Controls["XMachinePos_lbl"]->ForeColor = Color::Green;
        MainFrm->Controls["YMachinePos_lbl"]->ForeColor = Color::Green;
        MainFrm->Controls["ZMachinePos_lbl"]->ForeColor = Color::Green;
        if (xDtg >= 0) MainFrm->Controls["XMachinePos_lbl"]->Text = "+MX"; else MainFrm->Controls["XMachinePos_lbl"]->Text = "-MX";
        if (yDtg >= 0) MainFrm->Controls["YMachinePos_lbl"]->Text = "+MY"; else MainFrm->Controls["YMachinePos_lbl"]->Text = "-MY";
        if (zDtg >= 0) MainFrm->Controls["ZMachinePos_lbl"]->Text = "+MZ"; else MainFrm->Controls["ZMachinePos_lbl"]->Text = "-MZ";
        MainFrm->Controls["XAbsPos_lbl"]->Text = xAbs.ToString();
        MainFrm->Controls["YAbsPos_lbl"]->Text = yAbs.ToString();
        MainFrm->Controls["ZAbsPos_lbl"]->Text = zAbs.ToString();
        MainFrm->Controls["XPos_lbl"]->Text = x.ToString();
        MainFrm->Controls["YPos_lbl"]->Text = y.ToString();
        MainFrm->Controls["ZPos_lbl"]->Text = z.ToString();
        MainFrm->Controls["XRelPos_lbl"]->Text = xRel.ToString();
        MainFrm->Controls["YRelPos_lbl"]->Text = yRel.ToString();
        MainFrm->Controls["ZRelPos_lbl"]->Text = zRel.ToString();
        MainFrm->Controls["XDTGPos_lbl"]->Text = xDtg.ToString();
        MainFrm->Controls["YDTGPos_lbl"]->Text = yDtg.ToString();
        MainFrm->Controls["ZDTGPos_lbl"]->Text = zDtg.ToString();
        MainFrm->Controls["SpindleSpeed_lbl"]->Text = "S " + SpindleSpeed.ToString() + " rpm";
        MainFrm->Controls["FeedRate_lbl"]->Text = "F " + FeedRate + " mm/min";
        MainFrm->Controls["CurrentTime_lbl"]->Text = DateTime::Now.ToLongTimeString();
        MainFrm->Controls["EllapsedTime_lbl"]->Text = ((float)stopwatch->ElapsedMilliseconds / 1000).ToString();;
        
        ((ListBox^)MainFrm->Controls["ExecProg_lbox"])->SelectedIndex = ExecProgBlockNum;
        
        
    }
    else
    {
      MainFrm->Controls["XMachinePos_lbl"]->ForeColor = Color::Black;
      MainFrm->Controls["YMachinePos_lbl"]->ForeColor = Color::Black;
      MainFrm->Controls["ZMachinePos_lbl"]->ForeColor = Color::Black;
      
    }
    return ret;

}
 String^  GetGModalData(ODBMDL GModalData)
 {
     String^ sGModal;
     
     short   GModal = 0;
     for (int i = 0; i <= 34; i++)
     {
         
         if (GetBit((short)GModalData.modal.g_rdata[i], 7) == 1) GModal = abs(GModalData.modal.g_rdata[i]) - 128;
         else GModal = (short)GModalData.modal.g_rdata[i];
         if (i==0)
         {
         switch (GModal)
         {case 0:
          sGModal += "G00 ";
          
          break;
          case 1:
          sGModal += "G01 ";
          
          break;
          case 2:
          sGModal += "G02 ";
          
          break;
          case 3:
          sGModal += "G03 ";
          
          break;
          case 4:
          sGModal += "G33 ";
          
          break;
          case 5:
          sGModal += "G75 ";
          
          break;
          case 6:
          sGModal += "G77 ";
          
          break;
          case 7:
          sGModal += "G78 ";
          
          break;
          case 8:
          sGModal += "G79 ";
          
          break;
          case 10:
          sGModal += "G02.2 ";
          
          break;
          case 11:
          sGModal += "G03.2 ";
          
          break;
          case 12:
          sGModal += "G02.3 ";
          
          break;
          case 13:
          sGModal += "G03.3 ";
          
          break;
          case 14:
          sGModal += "G06.2 ";
          
          break;
          case 15:
          sGModal += "G02.4 ";
          
          break;
          case 16:
          sGModal += "G03.4 ";
          
          break;
          case 22:
          sGModal += "G35 ";
          
          break;
          case 23:
          sGModal += "G36 ";
          
          break;
          case 24:
          sGModal += "G34 ";
          
          break;
          default:
          break;
          }
         }
         if (i == 1)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G17 ";
                 
                 break;
             case 4:
                 sGModal += "G19 ";
                 
                 break;
             case 8:
                 sGModal += "G18 ";
                 
                 break;
             case 10:
                 sGModal += "G17.1 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 2)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G90 ";
                 
                 break;
             case 1:
                 sGModal += "G91 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 3)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G23 ";
                 
                 break;
             case 1:
                 sGModal += "G22 ";
                 
                 break;

             default:
                 break;
             }
         }
         if (i == 4)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G94 ";
                 
                 break;
             case 1:
                 sGModal += "G95 ";
                 
                 break;
             case 2:
                 sGModal += "G93 ";
                 
                 break;
             case 3:
                 sGModal += "G93.2 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 5)
         {switch (GModal)
             {
             case 0:
                 sGModal += "G20 ";
                 
                 break;
             case 1:
                 sGModal += "G21 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 6)
         {switch (GModal)
             {
             case 0:
             sGModal += "G40 ";
             
             break;
             case 1:
             sGModal += "G41 ";
             
             break;
             case 2:
             sGModal += "G42 ";
             
             break;
             case 3:
             sGModal += "G41.2 ";
             
             break;
             case 4:
             sGModal += "G42.2 ";
             
             break;
             case 5:
             sGModal += "G41.3 ";
             
             break;
             case 6:
             sGModal += "G41.4 ";
             
             break;
             case 7:
             sGModal += "G42.4 ";
             
             break;
             case 8:
             sGModal += "G41.5 ";
             
             break;
             case 9:
             sGModal += "G42.5 ";
             
             break;
             case 10:
             sGModal += "G41.6 ";
             
             break;
             case 11:
             sGModal += "G42.6 ";
             
             break;

             default:
             break;
             }
         }
         if (i == 7)
         {switch (GModal)
             {case 0:
                 sGModal += "G49(G49.1) ";
                 
                 break;
             case 1:
                 sGModal += "G43 ";
                 
                 break;
             case 2:
                 sGModal += "G44 ";
                 
                 break;
             case 3:
                 sGModal += "G43.1 ";
                 
                 break;
             case 4:
                 sGModal += "G43.4 ";
                 
                 break;
             case 5:
                 sGModal += "G43.5 ";
                 
                 break;
             case 6:
                 sGModal += "G43.2 ";
                 
                 break;
             case 7:
                 sGModal += "G43.3 ";
                 
                 break;
                 default:
                 break;
             }
         }
         if (i == 8)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G80 ";
                 
                 break;
             case 1:
                 sGModal += "G81 ";
                 
                 break;
             case 2:
                 sGModal += "G82 ";
                 
                 break;
             case 3:
                 sGModal += "G83 ";
                 
                 break;
             case 4:
                 sGModal += "G84 ";
                 
                 break;
             case 5:
                 sGModal += "G85 ";
                 
                 break;
             case 6:
                 sGModal += "G86 ";
                 
                 break;
             case 7:
                 sGModal += "G87 ";
                 
                 break;
             case 8:
                 sGModal += "G88 ";
                 
                 break;
             case 9:
                 sGModal += "G89 ";
                 
                 break;
             case 10:
                 sGModal += "G73 ";
                 
                 break;
             case 11:
                 sGModal += "G74 ";
                 
                 break;
             case 12:
                 sGModal += "G76 ";
                 
                 break;
             case 13:
                 sGModal += "G84.2 ";
                 
                 break;
             case 14:
                 sGModal += "G84.3 ";
                 
                 break;
             case 15:
                 sGModal += "G81.2 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 9)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G98 ";
                 
                 break;
             case 1:
                 sGModal += "G99 ";
                 
                 break;

             default:
                 break;
             }
         }
         if (i == 10)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G50 ";
                 
                 break;
             case 1:
                 sGModal += "G51 ";
                 
                 break;

             default:
                 break;
             }
         }
         if (i == 11)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G67 ";
                 
                 break;
             case 1:
                 sGModal += "G66 ";
                 
                 break;
             case 2:
                 sGModal += "G66.1 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 12)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G97 ";
                 
                 break;
             case 1:
                 sGModal += "G96 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 13)
         {switch (GModal)
             {
             case 0:
                 sGModal += "G54(G54.1) ";
                 
                 break;
             case 1:
                 sGModal += "G55 ";
                 
                 break;
             case 2:
                 sGModal += "G56 ";
                 
                 break;
             case 3:
                 sGModal += "G57 ";
                 
                 break;
             case 4:
                 sGModal += "G58 ";
                 
                 break;
             case 5:
                 sGModal += "G59 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 14)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G64 ";
                 
                 break;
             case 1:
                 sGModal += "G61 ";
                 
                 break;
             case 2:
                 sGModal += "G62 ";
                 
                 break;
             case 3:
                 sGModal += "G63 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 15)
         {switch (GModal)
             {
             case 0:
                 sGModal += "G69 ";
                 
                 break;
             case 1:
                 sGModal += "G68 ";
                 
                 break;
             case 2:
                 sGModal += "G68.2 ";
                 
                 break;
             case 3:
                 sGModal += "G68.3 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 16)
         {switch (GModal)
             {
             case 0:
                 sGModal += "G15 ";
                 
                 break;
             case 1:
                 sGModal += "G16 ";
                 
                 break;
             
             default:
                 break;
             }
         }
         if (i == 17)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G40.1 ";
                 
                 break;
             case 1:
                 sGModal += "G41.1 ";
                 
                 break;
             case 2:
                 sGModal += "G42.1 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 18)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G25 ";
                 
                 break;
             case 1:
                 sGModal += "G26 ";
                 
                 break;
             default:
             break;
             }
         }
         if (i == 19)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G160 ";
                 
                 break;
             case 1:
                 sGModal += "G161 ";
                 
                 break;
             default:
                 break;
             }
         }
         if (i == 20)
         {
             switch (GModal)
             {
             case 0:
                 sGModal += "G13.1(G113) ";
                 
                 break;
             case 1:
                 sGModal += "G12.1(G112) ";
                 
                 break;
             default:
                 break;
             }
         }
     }
     return sGModal;
}
 String^ GetNoGModalData(ODBMDL NoGModalData)
 {String^ sNoGModal;
  short  NoGModalType = 0;
  long NoGModal;
  for (int i = 0; i <= 27; i++)
  {
      NoGModal = NoGModalData.modal.raux1[i].aux_data;
      //NoGModalType = (short)NoGModalData.modal.raux1[i].flag1 >> 5;
      //if (GetBit((short)NoGModalData.modal.raux1[i].aux_data, 7) == 1) NoGModal = abs(NoGModalData.modal.raux1[i].aux_data) - 128;
      //else NoGModal = (short)GModalData.modal.raux1[i].aux_data;
      switch (i)
      {
      case 0:
          if (NoGModal>0) sNoGModal += "B"+ NoGModal.ToString() + " ";
          break;
      case 1:
          if (NoGModal > 0) sNoGModal += "D" + NoGModal.ToString()+ " ";
          break;
      case 3:
          if (NoGModal > 0) sNoGModal += "F" + NoGModal.ToString()+ " ";
          break;
      case 4:
          if (NoGModal > 0) sNoGModal += "H" + NoGModal.ToString() + " ";
          break;
      case 5:
          if (NoGModal > 0) sNoGModal += "L" + NoGModal.ToString() + " ";
          break;
      case 6:
          if (NoGModal > 0) sNoGModal += "M" + NoGModal.ToString() + " ";
          break;
      case 7:
          if (NoGModal > 0) sNoGModal += "S" + NoGModal.ToString() + " ";
          break;
      case 8:
          if (NoGModal > 0) sNoGModal += "T" + NoGModal.ToString() + " ";
          break;
      case 9:
          if (NoGModal > 0) sNoGModal += "R" + NoGModal.ToString() + " ";
          break;
      case 10:
          if (NoGModal > 0)sNoGModal += "P" + NoGModal.ToString() + " ";
          break;
      case 11:
          if (NoGModal > 0)sNoGModal += "Q" + NoGModal.ToString() + " ";
          break;
      case 12:
          if (NoGModal > 0) sNoGModal += "A" + NoGModal.ToString() + " ";
          break;
      case 13:
          if (NoGModal > 0) sNoGModal += "C" + NoGModal.ToString() + " ";
          break;
      case 14:
          if (NoGModal > 0) sNoGModal += "I" + NoGModal.ToString() + " ";
          break;
      case 15:
          if (NoGModal > 0) sNoGModal += "J" + NoGModal.ToString() + " ";
          break;
      case 16:
          if (NoGModal > 0) sNoGModal += "K" + NoGModal.ToString() + " ";
          break;
      case 17:
          if (NoGModal > 0) sNoGModal += "N" + NoGModal.ToString() + " ";
          break;
      case 18:
          if (NoGModal > 0) sNoGModal += "O" + NoGModal.ToString() + " ";
          break;
      case 19:
          if (NoGModal > 0) sNoGModal += "U" + NoGModal.ToString() + " ";
          break;
      case 20:
          if (NoGModal > 0) sNoGModal += "V" + NoGModal.ToString() + " ";
          break;
      case 21:
          if (NoGModal > 0) sNoGModal += "W" + NoGModal.ToString() + " ";
          break;
      case 22:
          if (NoGModal > 0) sNoGModal += "X" + NoGModal.ToString() + " ";
          break;
      case 23:
          if (NoGModal > 0) sNoGModal += "Y" + NoGModal.ToString() + " ";
          break;
      case 24:
          if (NoGModal > 0) sNoGModal += "Z" + NoGModal.ToString() + " ";
          break;
      case 25:
          if (NoGModal > 0) sNoGModal += "2M" + NoGModal.ToString() + " ";
          break;
      case 26:
          if (NoGModal > 0) sNoGModal += "3M" + NoGModal.ToString() + " ";
          break;
      default:
          break;
      }
  
  }
  return sNoGModal;
 }
}
