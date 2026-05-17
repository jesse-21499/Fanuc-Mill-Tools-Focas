
#pragma once
#include "Fwlib64.h"
namespace FanucMillTools
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::IO;
	using namespace System::Diagnostics;
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
	short FocasDownloadNCFile(Form^ MainFrm,StreamReader^ NCFileStreamReader,StreamReader^ ZSurfInspectStreamReader);
	short FocasReadMachinePos(Form^ MainFrm);
	short FocasMonitorMachinePos(Form^ MainFrm,Stopwatch^ stopwatch);
	double x = 0, y = 0, z = 0, xAbs = 0, yAbs = 0, zAbs = 0, xRel = 0, yRel = 0, zRel = 0, xDtg = 0, yDtg = 0, zDtg = 0;
	short NumberOfAxis = MAX_AXIS;
	char ExecProgName[256];
	long ExecProgNum = 0;
	long ExecProgBlockNum = 0;
	long PreviousBlockNumb = 0;
	//char ExecProgBlock[256];
	//unsigned long ExecProgLinesToRead = 1;
	//unsigned long ExecProgBlockLength = 256;
	static ODBPOS MachinePos[MAX_AXIS];
	static ODBACT ActualSpindleSpeed;
	static ODBACT ActualFeedRate;
	static IODBSGNL OutputSignalImage;
	static ODBMDL GModalData;
	static ODBMDL NoGModalData;
	static ODBMDL NoGAxisModalData;
	static IODBPMC IODBPmc;
	static ODBST MachineStatusInfo;
	long SpindleSpeed = 0;
	long FeedRate = 0;
	bool OperationSignal = 0;
	short MachineIsMoving = 0;
	unsigned long FirstMacroVariable = 0;
	unsigned long NumbOfMacroVarsToRead = 0;
	double MacroVars1[33];
	//IODBMRN3 MacroVars1[33];
	double MacroVars2[100];
	//IODBMRN3 MacroVars2[100];
	double MacroVars3[1068];
	//IODBMRN3 MacroVars3[1068];
	String^ GetGModalData(ODBMDL GModalData);
	String^ GetNoGModalData(ODBMDL NoGModalData);
	short ret = 0;//return value
}