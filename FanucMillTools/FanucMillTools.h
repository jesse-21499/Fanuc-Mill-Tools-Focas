
#pragma once
#include "Fwlib64.h"
namespace FanucMillTools
{
	using namespace System;
	using namespace System::Windows::Forms;
	// Windows Forms types can be used in this header file.
	const char* CNC_IP="";
	unsigned short CNC_Port=8193;
	unsigned short FHndl = 0;
	short MaxParamNo = 0;
	bool Connected = false;
	double EllapsedTime = 0; //Ellapsed time in millisecs
	short FocasReadNumParams(Form^ MainFrm);
	short FocasReadNumToolOffsets(Form^ MainFrm,short &ToolOffsets);
	short FocasConnect(Form^ MainFrm);
	short FocasDisconnect(Form^ MainFrm);
	short FocasReadParams(Form^ MainFrm);
	short FocasWriteParam(Form^ MainFrm);
	short FocasReadCNCInfo(Form^ MainFrm);
	short FocasReadToolOffsets(Form^ MainFrm);
	short FocasWriteToolOffset(Form^ MainFrm);
	short FocasReadWorkZeroOffsets(Form^ MainFrm);
	short FocasWriteWorkZeroOffset(Form^ MainFrm);
	
}