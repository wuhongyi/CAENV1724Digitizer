// DigitizerConfigure.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Apr 28 22:16:47 2016 (+0800)
// Last-Updated: Fri Apr 29 19:25:14 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 37
// URL: http://wuhongyi.cn 

#ifndef _DIGITIZERCONFIGURE_H_
#define _DIGITIZERCONFIGURE_H_

// #include "TCanvas.h"
// #include "TGraph.h"

#include "DigitizerGlobals.hh"
#include "DigitizerAdmin.hh"

#include "CAENDigitizerType.h"
#include "CAENDigitizer.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Only use in V1724 now!!! need update for other board!!!
// return  0=success; -1=error
int DigitizerInit(CAEN_DGTZ_DPP_PHA_Params_t *PKU_DGTZ_DPPParams,DigitizerParams_t *PKU_DGTZ_Params,int *PKU_DGTZ_handle,CAEN_DGTZ_BoardInfo_t PKU_DGTZ_BoardInfo);

void RunManagerInit(DigitizerRun_t *RunManager);

void CheckKeyboard(DigitizerRun_t *PKU_DGTZ_RunManager,int *PKU_DGTZ_handle,CAEN_DGTZ_DPP_PHA_Params_t *PKU_DGTZ_DPPParams,DigitizerParams_t *PKU_DGTZ_Params);

// Calculate throughput and trigger rate (every second),print something about running information.
void PrintRunningStatus(DigitizerRun_t *PKU_DGTZ_RunManager);

void PlotROOTGraph(DigitizerRun_t *PKU_DGTZ_RunManager,int b,int ch,int size,int16_t *WaveData);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Quit the Program
void QuitProgram(int *handle);
void QuitProgram(int *handle,char *buffer);

// Program the registers of the digitizer with the relevant parameters
// return  0=success; -1=error 
int ProgramDigitizer_V1724(int handle, DigitizerParams_t Params, CAEN_DGTZ_DPP_PHA_Params_t DPPParams);

// return  0=success; -1=error
int ReadDPPParameters_PHA(DigitizerParams_t *Params, CAEN_DGTZ_DPP_PHA_Params_t *DPPParams);

// Read DGTZ Registers 
// return  0=success; -1=error
int Read_DGTZ_Register(int handle,int MaxNChInBoard);
int Read_DGTZ_V1724_Register(int handle);

// Read DGTZ Info
// return  0=success; -1=error
int Read_DGTZ_Info(int handle);

#endif /* _DIGITIZERCONFIGURE_H_ */
// 
// DigitizerConfigure.hh ends here
