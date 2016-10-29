// DigitizerConfigure.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: Thu Apr 28 22:16:56 2016 (+0800)
// Last-Updated: Sat Sep  3 12:58:33 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 180
// URL: http://wuhongyi.cn 

#include "DigitizerGlobals.hh"
#include "DigitizerConfigure.hh"
#include "DigitizerUser.hh"
//#include "DigitizerAdmin.hh"
// #include "TAxis.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int DigitizerInit(CAEN_DGTZ_DPP_PHA_Params_t *PKU_DGTZ_DPPParams,DigitizerParams_t *PKU_DGTZ_Params,int *PKU_DGTZ_handle,CAEN_DGTZ_BoardInfo_t PKU_DGTZ_BoardInfo)
{
  int b;
  int ret;
  std::string tempstring1,tempstring2;

  // Set Parameters 
  memset(PKU_DGTZ_Params, 0, MAXNB * sizeof(DigitizerParams_t));
  memset(PKU_DGTZ_DPPParams, 0, MAXNB * sizeof(CAEN_DGTZ_DPP_PHA_Params_t));

  for (b = 0; b < MAXNB; b++) 
    {
      // if(ReadGlobalsParameters(&PKU_DGTZ_Params[b]) < 0) return -1;
      //=====LinkType=====
      tempstring1 = ReadValue<std::string>("LinkType",PKU_DGTZ_GlobalParametersFileName);
      tempstring2 = ReadValue<std::string>("VMEBaseAddress",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"LinkType:"<<" "<<tempstring1<<" "<<"VMEBaseAddress:"<<" "<<tempstring2<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_PCI_OpticalLink")
      	{
      	  PKU_DGTZ_Params[b].LinkType = CAEN_DGTZ_PCI_OpticalLink;
      	  if(tempstring2=="0")
      	    {
      	      PKU_DGTZ_Params[b].VMEBaseAddress = 0;
      	      PKU_DGTZ_Params[b].LinkNum = 0;
      	      PKU_DGTZ_Params[b].ConetNode = b;
      	    }
      	  else 
      	    {
      	      if(tempstring2=="0x32100000")
      		{
      		  PKU_DGTZ_Params[b].VMEBaseAddress = 0x32100000;
      		  PKU_DGTZ_Params[b].LinkNum = 0;
      		  PKU_DGTZ_Params[b].ConetNode = 0;
      		}
      	      else {printf("VMEBaseAddress error \n");return -1;} 
      	    }
      	}
      else 
      	{
      	  if(tempstring1 == "CAEN_DGTZ_USB")
      	    {
      	      PKU_DGTZ_Params[b].LinkType = CAEN_DGTZ_USB;
      	      if(tempstring2=="0")
      		{
      		  PKU_DGTZ_Params[b].VMEBaseAddress = 0;
      		  PKU_DGTZ_Params[b].LinkNum = b;
      		  PKU_DGTZ_Params[b].ConetNode =0;
      		}
      	      else 
      		{
      		  if(tempstring2=="0x32100000")
      		    {
      		      PKU_DGTZ_Params[b].VMEBaseAddress = 0x32100000;
      		      PKU_DGTZ_Params[b].LinkNum = 0;
      		      PKU_DGTZ_Params[b].ConetNode =0;
      		    }
      		  else {printf("VMEBaseAddress error \n");return -1;} 
      		}
      	    }
      	  else 
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_PCIE_OpticalLink")
      		{
      		  PKU_DGTZ_Params[b].LinkType = CAEN_DGTZ_PCIE_OpticalLink;
      		  if(tempstring2=="0x32100000")
      		    {
      		      PKU_DGTZ_Params[b].VMEBaseAddress = 0x32100000;
      		      PKU_DGTZ_Params[b].LinkNum = 0;
      		      PKU_DGTZ_Params[b].ConetNode = 0;
      		    }
      		  else {printf("VMEBaseAddress error \n");return -1;} 
      		}
      	      else 
      		{
      		  printf("LinkType error \n");return -1;
      		}
      	    }
      	}

      //=====IOlev=====
      tempstring1 = ReadValue<std::string>("IOlev",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"IOlev:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_IOLevel_TTL")
      	{
      	  PKU_DGTZ_Params[b].IOlev = CAEN_DGTZ_IOLevel_TTL;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_IOLevel_NIM")
      	    {
      	      PKU_DGTZ_Params[b].IOlev = CAEN_DGTZ_IOLevel_NIM;
      	    }
      	  else
      	    {
      	      printf("IOlev error \n");return -1;
      	    }
      	}

      //=====DPPAcqMode=====
      // CAEN_DGTZ_DPP_ACQ_MODE_Oscilloscope / CAEN_DGTZ_DPP_ACQ_MODE_List / CAEN_DGTZ_DPP_ACQ_MODE_Mixed  
      tempstring1 = ReadValue<std::string>("DPPAcqMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"DPPAcqMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_DPP_ACQ_MODE_Mixed")
      	{
      	  PKU_DGTZ_Params[b].DPPAcqMode = CAEN_DGTZ_DPP_ACQ_MODE_Mixed;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_DPP_ACQ_MODE_Oscilloscope")
      	    {
      	      PKU_DGTZ_Params[b].DPPAcqMode = CAEN_DGTZ_DPP_ACQ_MODE_Oscilloscope;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_DPP_ACQ_MODE_List")
      		{
      		  PKU_DGTZ_Params[b].DPPAcqMode = CAEN_DGTZ_DPP_ACQ_MODE_List;
      		}
      	      else
      		{
      		  printf("DPPAcqMode error \n");return -1;
      		}
      	    }
      	}

      //=====AcqMode=====
      // CAEN_DGTZ_SW_CONTROLLED / CAEN_DGTZ_S_IN_CONTROLLED / CAEN_DGTZ_FIRST_TRG_CONTROLLED
      tempstring1 = ReadValue<std::string>("AcqMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"AcqMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_SW_CONTROLLED")
      	{
      	  PKU_DGTZ_Params[b].AcqMode = CAEN_DGTZ_SW_CONTROLLED;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_S_IN_CONTROLLED")
      	    {
      	      PKU_DGTZ_Params[b].AcqMode = CAEN_DGTZ_S_IN_CONTROLLED;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_FIRST_TRG_CONTROLLED")
      		{
      		  PKU_DGTZ_Params[b].AcqMode = CAEN_DGTZ_FIRST_TRG_CONTROLLED;
      		}
      	      else
      		{
      		  printf("DPPAcqMode error \n");return -1;
      		}
      	    }
      	}    
      
      //=====SaveParam=====
      // CAEN_DGTZ_DPP_SAVE_PARAM_EnergyOnly   Only energy (DPP-PHA) or charge (DPP-PSD/DPP-CI v2) is returned 
      // CAEN_DGTZ_DPP_SAVE_PARAM_TimeOnly   Only time is returned 
      // CAEN_DGTZ_DPP_SAVE_PARAM_EnergyAndTime  Both energy/charge and time are returned 
      // CAEN_DGTZ_DPP_SAVE_PARAM_ChargeAndTime  deprecated On DPP-PSD and DPP-CI use CAEN_DGTZ_DPP_SAVE_PARAM_EnergyAndTime 
      // CAEN_DGTZ_DPP_SAVE_PARAM_None    No histogram data is returned 
      tempstring1 = ReadValue<std::string>("SaveParam",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"SaveParam:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_DPP_SAVE_PARAM_EnergyOnly")
      	{
      	  PKU_DGTZ_Params[b].SaveParam = CAEN_DGTZ_DPP_SAVE_PARAM_EnergyOnly;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_DPP_SAVE_PARAM_TimeOnly")
      	    {
      	      PKU_DGTZ_Params[b].SaveParam = CAEN_DGTZ_DPP_SAVE_PARAM_TimeOnly;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_DPP_SAVE_PARAM_EnergyAndTime")
      		{
      		  PKU_DGTZ_Params[b].SaveParam = CAEN_DGTZ_DPP_SAVE_PARAM_EnergyAndTime;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_DPP_SAVE_PARAM_ChargeAndTime")
      		    {
      		      PKU_DGTZ_Params[b].SaveParam = CAEN_DGTZ_DPP_SAVE_PARAM_ChargeAndTime;
      		    }
      		  else
      		    {
      		      if(tempstring1 == "CAEN_DGTZ_DPP_SAVE_PARAM_None")
      			{
      			  PKU_DGTZ_Params[b].SaveParam = CAEN_DGTZ_DPP_SAVE_PARAM_None;
      			}
      		      else
      			{
      			  printf("SaveParam error \n");return -1;
      			}
      		    }
      		}
      	    }
      	}


      //=====EventAggr=====
      std::cout<<"EventAggr:"<<" "<<ReadValue<int>("EventAggr", PKU_DGTZ_GlobalParametersFileName)<<std::endl;
      PKU_DGTZ_Params[b].EventAggr = ReadValue<int>("EventAggr", PKU_DGTZ_GlobalParametersFileName);
      
      //=====ExtTrgMode=====
      // CAEN_DGTZ_TRGMODE_DISABLED: do nothing
      // CAEN_DGTZ_TRGMODE_EXTOUT_ONLY: generate the Trigger Output signal
      // CAEN_DGTZ_TRGMODE_ACQ_ONLY = generate acquisition trigger
      // CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT = generate both Trigger Output and acquisition trigger
      tempstring1 = ReadValue<std::string>("ExtTrgMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"ExtTrgMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_TRGMODE_DISABLED")
      	{
      	  PKU_DGTZ_Params[b].ExtTrgMode = CAEN_DGTZ_TRGMODE_DISABLED;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_TRGMODE_EXTOUT_ONLY")
      	    {
      	      PKU_DGTZ_Params[b].ExtTrgMode = CAEN_DGTZ_TRGMODE_EXTOUT_ONLY;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_ONLY")
      		{
      		  PKU_DGTZ_Params[b].ExtTrgMode = CAEN_DGTZ_TRGMODE_ACQ_ONLY;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT")
      		    {
      		      PKU_DGTZ_Params[b].ExtTrgMode = CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT;
      		    }
      		  else
      		    {
      		      printf("ExtTrgMode error \n");return -1;
      		    }
      		}
      	    }
      	}

      //=====SWTrgMode=====
      // CAEN_DGTZ_TRGMODE_DISABLED: do nothing
      // CAEN_DGTZ_TRGMODE_EXTOUT_ONLY: generate the Trigger Output signal
      // CAEN_DGTZ_TRGMODE_ACQ_ONLY = generate acquisition trigger
      // CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT = generate both Trigger Output and acquisition trigger
      tempstring1 = ReadValue<std::string>("SWTrgMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"SWTrgMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_TRGMODE_DISABLED")
      	{
      	  PKU_DGTZ_Params[b].SWTrgMode = CAEN_DGTZ_TRGMODE_DISABLED;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_TRGMODE_EXTOUT_ONLY")
      	    {
      	      PKU_DGTZ_Params[b].SWTrgMode = CAEN_DGTZ_TRGMODE_EXTOUT_ONLY;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_ONLY")
      		{
      		  PKU_DGTZ_Params[b].SWTrgMode = CAEN_DGTZ_TRGMODE_ACQ_ONLY;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT")
      		    {
      		      PKU_DGTZ_Params[b].SWTrgMode = CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT;
      		    }
      		  else
      		    {
      		      printf("SWTrgMode error \n");return -1;
      		    }
      		}
      	    }
      	}

      //=====SelfTrgMode=====
      // CAEN_DGTZ_TRGMODE_DISABLED: do nothing
      // CAEN_DGTZ_TRGMODE_EXTOUT_ONLY: generate the Trigger Output signal
      // CAEN_DGTZ_TRGMODE_ACQ_ONLY = generate acquisition trigger
      // CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT = generate both Trigger Output and acquisition trigger
      tempstring1 = ReadValue<std::string>("SelfTrgMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"SelfTrgMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_TRGMODE_DISABLED")
      	{
      	  PKU_DGTZ_Params[b].SelfTrgMode = CAEN_DGTZ_TRGMODE_DISABLED;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_TRGMODE_EXTOUT_ONLY")
      	    {
      	      PKU_DGTZ_Params[b].SelfTrgMode = CAEN_DGTZ_TRGMODE_EXTOUT_ONLY;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_ONLY")
      		{
      		  PKU_DGTZ_Params[b].SelfTrgMode = CAEN_DGTZ_TRGMODE_ACQ_ONLY;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT")
      		    {
      		      PKU_DGTZ_Params[b].SelfTrgMode = CAEN_DGTZ_TRGMODE_ACQ_AND_EXTOUT;
      		    }
      		  else
      		    {
      		      printf("SelfTrgMode error \n");return -1;
      		    }
      		}
      	    }
      	}

      //=====RunSyncMode=====
      // CAEN_DGTZ_RUN_SYNC_Disabled / CAEN_DGTZ_RUN_SYNC_TrgOutTrgInDaisyChain / CAEN_DGTZ_RUN_SYNC_TrgOutSinDaisyChain / CAEN_DGTZ_RUN_SYNC_SinFanout / CAEN_DGTZ_RUN_SYNC_GpioGpioDaisyChain
      tempstring1 = ReadValue<std::string>("RunSyncMode",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"RunSyncMode:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_RUN_SYNC_Disabled")
      	{
      	  PKU_DGTZ_Params[b].RunSyncMode = CAEN_DGTZ_RUN_SYNC_Disabled;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_RUN_SYNC_TrgOutTrgInDaisyChain")
      	    {
      	      PKU_DGTZ_Params[b].RunSyncMode = CAEN_DGTZ_RUN_SYNC_TrgOutTrgInDaisyChain;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_RUN_SYNC_TrgOutSinDaisyChain")
      		{
      		  PKU_DGTZ_Params[b].RunSyncMode = CAEN_DGTZ_RUN_SYNC_TrgOutSinDaisyChain;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_RUN_SYNC_SinFanout")
      		    {
      		      PKU_DGTZ_Params[b].RunSyncMode = CAEN_DGTZ_RUN_SYNC_SinFanout;
      		    }
      		  else
      		    {
      		      if(tempstring1 == "CAEN_DGTZ_RUN_SYNC_GpioGpioDaisyChain")
      			{
      			  PKU_DGTZ_Params[b].RunSyncMode = CAEN_DGTZ_RUN_SYNC_GpioGpioDaisyChain;
      			}
      		      else
      			{
      			  printf("RunSyncMode error \n");return -1;
      			}
      		    }
      		}
      	    }
      	}
 
      //=====AnalogMonOutput=====
      // CAEN_DGTZ_AM_TRIGGER_MAJORITY / CAEN_DGTZ_AM_TEST / CAEN_DGTZ_AM_ANALOG_INSPECTION / CAEN_DGTZ_AM_BUFFER_OCCUPANCY / CAEN_DGTZ_AM_VOLTAGE_LEVEL
      tempstring1 = ReadValue<std::string>("AnalogMonOutput",PKU_DGTZ_GlobalParametersFileName);
      std::cout<<"AnalogMonOutput:"<<" "<<tempstring1<<std::endl;
      if(tempstring1 == "CAEN_DGTZ_AM_TRIGGER_MAJORITY")
      	{
      	  PKU_DGTZ_Params[b].AnalogMonOutput = CAEN_DGTZ_AM_TRIGGER_MAJORITY;
      	}
      else
      	{
      	  if(tempstring1 == "CAEN_DGTZ_AM_TEST")
      	    {
      	      PKU_DGTZ_Params[b].AnalogMonOutput = CAEN_DGTZ_AM_TEST;
      	    }
      	  else
      	    {
      	      if(tempstring1 == "CAEN_DGTZ_AM_ANALOG_INSPECTION")
      		{
      		  PKU_DGTZ_Params[b].AnalogMonOutput = CAEN_DGTZ_AM_ANALOG_INSPECTION;
      		}
      	      else
      		{
      		  if(tempstring1 == "CAEN_DGTZ_AM_BUFFER_OCCUPANCY")
      		    {
      		      PKU_DGTZ_Params[b].AnalogMonOutput = CAEN_DGTZ_AM_BUFFER_OCCUPANCY;
      		    }
      		  else
      		    {
      		      if(tempstring1 == "CAEN_DGTZ_AM_VOLTAGE_LEVEL")
      			{
      			  PKU_DGTZ_Params[b].AnalogMonOutput = CAEN_DGTZ_AM_VOLTAGE_LEVEL;
      			}
      		      else
      			{
      			  printf("AnalogMonOutput error \n");return -1;
      			}
      		    }
      		}
      	    }
      	}
    }

  //=====Read Board Parameters=====
  if(ReadDPPParameters_PHA(PKU_DGTZ_Params,PKU_DGTZ_DPPParams)<0) 
    {
      printf("ReadDPPParameters_PHA(DigitizerParams_t *Params, CAEN_DGTZ_DPP_PHA_Params_t *DPPParams) error \n");return -1;
    }

  // Open the digitizer and read board information   
  for(b=0; b<MAXNB; b++)
    {
      ret = CAEN_DGTZ_OpenDigitizer(PKU_DGTZ_Params[b].LinkType, PKU_DGTZ_Params[b].LinkNum, PKU_DGTZ_Params[b].ConetNode, PKU_DGTZ_Params[b].VMEBaseAddress, &PKU_DGTZ_handle[b]);//
      if (ret) 
	{
	  printf("Can't open digitizer %d\n",b);
	  QuitProgram(PKU_DGTZ_handle);
	  return ret;
	}

      // Once we have the handler to the digitizer, we use it to call the other functions
      ret = CAEN_DGTZ_GetInfo(PKU_DGTZ_handle[b], &PKU_DGTZ_BoardInfo);
      if (ret) 
	{
	  printf("Can't read board info\n");
	  QuitProgram(PKU_DGTZ_handle);
	  return ret;
	}
      printf("\nConnected to CAEN Digitizer Model %s, recognized as board %d\n", PKU_DGTZ_BoardInfo.ModelName, b);
      printf("ROC FPGA Release is %s\n", PKU_DGTZ_BoardInfo.ROC_FirmwareRel);
      printf("AMC FPGA Release is %s\n", PKU_DGTZ_BoardInfo.AMC_FirmwareRel);

      // GOTO
      // int MajorNumber;
      // // Check firmware revision (only DPP firmwares can be used with this Demo)
      // sscanf(PKU_DGTZ_BoardInfo.AMC_FirmwareRel, "%d", &MajorNumber);
      // if (MajorNumber != V1724_DPP_PHA_CODE)// && MajorNumber != V1730_DPP_PHA_CODE
      // 	{
      // 	  printf("This digitizer has not a DPP-PHA firmware V1724\n");
      // 	  QuitProgram(handle,buffer);
      // 	  return ret;
      // 	}
    }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // Program the digitizer (see function ProgramDigitizer_V1724) 
  for (b = 0; b < MAXNB; b++) 
    {
      if (ProgramDigitizer_V1724(PKU_DGTZ_handle[b], PKU_DGTZ_Params[b], PKU_DGTZ_DPPParams[b])) 
	{
	  printf("Failed to program the digitizer\n");
	  QuitProgram(PKU_DGTZ_handle);
	  return ret;
	}
    }

  for(b=0; b<MAXNB; b++) 
    {
      ret |= CAEN_DGTZ_SetAnalogMonOutput(PKU_DGTZ_handle[b], PKU_DGTZ_Params[b].AnalogMonOutput);
    }

  // GOTO
  for(b=0; b<MAXNB; b++) 
    {
      // Get board info
      std::cout<<std::endl;
      std::cout<<"== Start Board:"<<b<<" Info"<<std::endl;
      ret = Read_DGTZ_Info(PKU_DGTZ_handle[b]);
      if(ret) 
      	{
      	  printf("Read Board Info ERROR!\n");
      	  return -1;
      	}
      std::cout<<"== End Board:"<<b<<" Info"<<std::endl;

      // Read  registers
      printf("\n********* Register Readout for Board %d **************\n", b);
      Read_DGTZ_V1724_Register(PKU_DGTZ_handle[b]);
      if(ret) 
      	{
      	  printf("Read registers ERROR!\n");
      	  return -1;
      	}
    }

  return 0;
}

void RunManagerInit(DigitizerRun_t *RunManager)
{

  RunManager->RunNumber = -1;
  RunManager->FileNo = -1;
  
  RunManager->Quit = false;
  RunManager->AcqRun = false;
  RunManager->Nb = 0;

  RunManager->WriteFlag = false;
  
  memset(RunManager->PrevTime, 0, MAXNB*MaxNChannels*sizeof(uint64_t));
  memset(RunManager->ECnt, 0, MAXNB*MaxNChannels*sizeof(int));
  memset(RunManager->TrgCnt, 0, MAXNB*MaxNChannels*sizeof(int));
  memset(RunManager->PurCnt, 0, MAXNB*MaxNChannels*sizeof(int));

  std::string PathToRawData = ReadValue<std::string>("PathToRawData",PKU_DGTZ_GlobalParametersFileName);
  sprintf(RunManager->PathToRawData,"%s",PathToRawData.c_str());
  // std::cout<<RunManager->PathToRawData<<std::endl;

  RunManager->PlotFlag = false;
  RunManager->DoPlotBoard = 0;
  RunManager->DoPlotChannel = 0;
  RunManager->PlotChooseN = ReadValue<int>("PlotChooseN",PKU_DGTZ_GlobalParametersFileName);
}


void CheckKeyboard(DigitizerRun_t *PKU_DGTZ_RunManager,int *PKU_DGTZ_handle,CAEN_DGTZ_DPP_PHA_Params_t *PKU_DGTZ_DPPParams,DigitizerParams_t *PKU_DGTZ_Params)
{
  // printf("Type a command: \n");
  int b;
  // Check keyboard
  if(kbhit())
    {
      PKU_DGTZ_RunManager->Key = getch();
      std::cout<<PKU_DGTZ_RunManager->Key<<std::endl;
      switch(PKU_DGTZ_RunManager->Key)
	{
	case 'q' :
	  {
	    if(PKU_DGTZ_RunManager->AcqRun) 
	      {
		printf("Please enter [s] to stop and enter [q] to quit.\n");
		break;
	      }
	    PKU_DGTZ_RunManager->Quit = true;
	    break;
	  }
	      
	case 's' :
	  {
	    if(PKU_DGTZ_RunManager->AcqRun)
	      {//running,do stop
		for (b = 0; b < MAXNB; b++) 
		  {
		    CAEN_DGTZ_SWStopAcquisition(PKU_DGTZ_handle[b]); // Stop Acquisition
		    printf("Acquisition Stopped for Board %d\n", b);
		  }
		PKU_DGTZ_RunManager->AcqRun = false;

		CloseFile();
		strcpy(PKU_DGTZ_RunManager->StopRunningTime,GetTimeStringYmdHMS());
		WriteRunLog("\ntime: ");
		WriteRunLog(PKU_DGTZ_RunManager->StopRunningTime);
		WriteRunLog("\n==========RunStop==========\n");
		CloseRunLog();
	      }
	    else
	      {//stop,do run
		for (b = 0; b < MAXNB; b++) 
		  {
		    OpenRunLog();
		    strcpy(PKU_DGTZ_RunManager->StartRunningTime,GetTimeStringYmdHMS());
		    WriteRunLog("\n==========RunStart==========\ntime: ");
		    WriteRunLog(PKU_DGTZ_RunManager->StartRunningTime);

		    // NB: the acquisition for each board starts when the following line is executed
		    // so in general the acquisition does NOT starts syncronously for different boards
		    CAEN_DGTZ_SWStartAcquisition(PKU_DGTZ_handle[b]);
		    printf("Acquisition Started for Board %d\n", b);
		  }
		PKU_DGTZ_RunManager->AcqRun = true;
	      }
	    break;
	  }

	case 't' :
	  {
	    for (b = 0; b < MAXNB; b++)
	      CAEN_DGTZ_SendSWtrigger(PKU_DGTZ_handle[b]); // Send a software trigger to each board
	    break;
	  }

	case 'w' :
	  {
	    if(!PKU_DGTZ_RunManager->AcqRun)
	      {
		printf("Please enter [s] start and enter [w] to write data.\n");
		break;
	      }
	    if(PKU_DGTZ_RunManager->WriteFlag)
	      {//writting, do stop
		PKU_DGTZ_RunManager->WriteFlag = false;
		strcpy(PKU_DGTZ_RunManager->StopWritingTime,GetTimeStringYmdHMS());

		CloseFile();
	      }
	    else
	      {//not write, do start
		PKU_DGTZ_RunManager->WriteFlag = true;
		PKU_DGTZ_RunManager->RunNumber = ReadAndUpdateRunNumber("../Log/RunNumber");
		PKU_DGTZ_RunManager->FileNo = -1;//important

		strcpy(PKU_DGTZ_RunManager->StartWritingTime,GetTimeStringYmdHMS());
		SaveLogFile(PKU_DGTZ_RunManager->StartWritingTime,PKU_DGTZ_GlobalParametersFileName);
		SaveLogFile(PKU_DGTZ_RunManager->StartWritingTime,PKU_DGTZ_BoardParametersFileName);
		char templog[32];
		sprintf(templog,"\nFileNumber: %04d",PKU_DGTZ_RunManager->RunNumber);
		WriteRunLog(templog);

		UpdateFileName(PKU_DGTZ_RunManager);
		OpenFile(PKU_DGTZ_RunManager);
	      }	
	    break;
	  }

	case 'R' :
	  {
	    if(PKU_DGTZ_RunManager->WriteFlag)
	      {
		printf("Please enter [w] stop write data and enter [R] restart.\n");
		break;
	      }
	    for (b = 0; b < MAXNB; b++) 
	      {
		CAEN_DGTZ_SWStopAcquisition(PKU_DGTZ_handle[b]); 
		printf("Restarted\n");
		CAEN_DGTZ_ClearData(PKU_DGTZ_handle[b]);
		memset(PKU_DGTZ_DPPParams, 0, MAXNB * sizeof(CAEN_DGTZ_DPP_PHA_Params_t));
		if(ReadDPPParameters_PHA(PKU_DGTZ_Params,PKU_DGTZ_DPPParams)<0) 
		  {
		    printf("ReadDPPParameters_PHA(DigitizerParams_t *Params, CAEN_DGTZ_DPP_PHA_Params_t *DPPParams) Error,Can't Restart Acquisition \n");
		    exit(-1);
		  }
		CAEN_DGTZ_SWStartAcquisition(PKU_DGTZ_handle[b]);
	      }
	    PKU_DGTZ_RunManager->PlotChooseN = ReadValue<int>("PlotChooseN",PKU_DGTZ_GlobalParametersFileName);
	    WriteRunLog("\nRestart");
	    break;
	  }

	case 'p' :
	  {
	    if(PKU_DGTZ_RunManager->PlotFlag)
	      {//ploting,do stop
		PKU_DGTZ_RunManager->PlotFlag = false;
		if(PKU_DGTZ_Graph != NULL)
		  {
		    delete PKU_DGTZ_Graph;
		    PKU_DGTZ_Graph = NULL;
		  }
		if(PKU_DGTZ_Canvas != NULL)
		  {
		    delete PKU_DGTZ_Canvas;
		    PKU_DGTZ_Canvas = NULL;
		  }
	      }
	    else
	      {// not plot ,do start
		PKU_DGTZ_RunManager->PlotFlag = true;
		PKU_DGTZ_RunManager->DoPlotBoard = 0;
		PKU_DGTZ_RunManager->DoPlotChannel = 0;
		PKU_DGTZ_RunManager->PlotEveryN = 0;
		PKU_DGTZ_RunManager->PlotColor = true;
		
		if(PKU_DGTZ_Canvas == NULL)
		  PKU_DGTZ_Canvas = new TCanvas("PKU_DGTZ_Canvas","PKU Digitizer Online",CANVASX,CANVASY);
		if(PKU_DGTZ_Graph == NULL)
		  {
		    PKU_DGTZ_Graph = new TGraph();
		    // PKU_DGTZ_Graph->GetXaxis()->SetTitle("time[10us/1000]");
		    // PKU_DGTZ_Graph->GetYaxis()->SetTitle("channel");
		  }
	      }
	    break;
	  }

	case '0' :
	  {
	    PKU_DGTZ_RunManager->PlotEveryN = 0;
	    break;
	  }
	  
	case '4' :
	  {
	    if(PKU_DGTZ_RunManager->DoPlotBoard > 0)
	      {
		PKU_DGTZ_RunManager->DoPlotBoard--;
		PKU_DGTZ_RunManager->PlotEveryN = 0;
	      }
	    break;
	  }
	case '6' :
	  {
	    if(PKU_DGTZ_RunManager->DoPlotBoard < MAXNB-1)
	      {
		PKU_DGTZ_RunManager->DoPlotBoard++;
		PKU_DGTZ_RunManager->PlotEveryN = 0;
	      }
	    break;
	  }
	case '2' :
	  {
	    if(PKU_DGTZ_RunManager->DoPlotChannel > 0)
	      {
		PKU_DGTZ_RunManager->DoPlotChannel--;
		PKU_DGTZ_RunManager->PlotEveryN = 0;
	      }
	    break;
	  }
	case '8' :
	  {
	    if(PKU_DGTZ_RunManager->DoPlotChannel < MaxNChannels-1)
	      {
		PKU_DGTZ_RunManager->DoPlotChannel++;
		PKU_DGTZ_RunManager->PlotEveryN = 0;
	      }
	    break;
	  }

	default: break;
	}
    }
}

void PrintRunningStatus(DigitizerRun_t *PKU_DGTZ_RunManager)
{
  PKU_DGTZ_RunManager->CurrentTime = get_time();
  PKU_DGTZ_RunManager->ElapsedTime = PKU_DGTZ_RunManager->CurrentTime - PKU_DGTZ_RunManager->PrevRateTime; /* milliseconds */

  if (PKU_DGTZ_RunManager->ElapsedTime > 1000)
    {
      // GOTO
      UpdateWhenFileFillUp(PKU_DGTZ_RunManager);
      
      int b,i;
      system(CLEARSCR);
      PrintInterface();

      printf("Readout Rate=%.2f MB\n", (float)PKU_DGTZ_RunManager->Nb/((float)PKU_DGTZ_RunManager->ElapsedTime*1048.576f));

      // GOTO ,need to beautify in screen
      for(b=0; b<MAXNB; b++)
	{
	  printf("\nBoard %d:\n",b);
	  for(i=0; i<MaxNChannels; i++)
	    {
	      if (PKU_DGTZ_RunManager->TrgCnt[b][i]>0)
		printf("\tCh %d:\tTrgRate=%.3f kHz\tPileUpRate=%.2f%%\n", i, (float)PKU_DGTZ_RunManager->TrgCnt[b][i]/(float)PKU_DGTZ_RunManager->ElapsedTime, (float)PKU_DGTZ_RunManager->PurCnt[b][i]*100/(float)PKU_DGTZ_RunManager->TrgCnt[b][i]);
	      else
		printf("\tCh %d:\tNo Data\n", i);
	      
	      PKU_DGTZ_RunManager->TrgCnt[b][i]=0;
	      PKU_DGTZ_RunManager->PurCnt[b][i]=0;
	    }
	}

      PKU_DGTZ_RunManager->Nb = 0;
      PKU_DGTZ_RunManager->PrevRateTime = PKU_DGTZ_RunManager->CurrentTime;

      printf("Status:\n");
      if(PKU_DGTZ_RunManager->AcqRun) printf("Start acquisition,");
      if(PKU_DGTZ_RunManager->WriteFlag) printf(" Writing file Number: %d\n",PKU_DGTZ_RunManager->RunNumber);
      else printf(" Not Write ......\n");
      if(PKU_DGTZ_RunManager->PlotFlag)
	printf("Monitor: B-%d Ch-%d\n",PKU_DGTZ_RunManager->DoPlotBoard,PKU_DGTZ_RunManager->DoPlotChannel);
      // GOTO
    }
}

void PlotROOTGraph(DigitizerRun_t *PKU_DGTZ_RunManager,int b,int ch,int size,int16_t *WaveData)
{
  char picturename[32];
  int i;
  sprintf(picturename, "Board %d - Channel %d;time[10us/1000];channel",b,ch);
  // if(PKU_DGTZ_Graph == NULL) std::cout<<"^^^^^^^^^"<<std::endl;
  PKU_DGTZ_Graph->SetTitle(picturename);
  for(i=0; i<size; i++)
    {
      PKU_DGTZ_Graph->SetPoint(i,i,WaveData[i]);
    }
  if(PKU_DGTZ_RunManager->PlotColor)
    {
      PKU_DGTZ_Graph->SetLineColor(2);
      PKU_DGTZ_RunManager->PlotColor = false;
    }
  else
    {
      PKU_DGTZ_Graph->SetLineColor(1);
      PKU_DGTZ_RunManager->PlotColor = true;
    }
  PKU_DGTZ_Canvas->cd();
  PKU_DGTZ_Graph->Draw("AL");
  // PKU_DGTZ_Canvas->Modified();
  PKU_DGTZ_Canvas->Update();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Quit the Program
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QuitProgram(int *PKU_DGTZ_handle)
{
  // stop the acquisition, close the device and free the buffers
  int b;
  for (b =0 ; b < MAXNB; b++) 
    {
      CAEN_DGTZ_SWStopAcquisition(PKU_DGTZ_handle[b]);
      CAEN_DGTZ_CloseDigitizer(PKU_DGTZ_handle[b]);
    }
}
void QuitProgram(int *PKU_DGTZ_handle,char *PKU_DGTZ_buffer)
{
  // stop the acquisition, close the device and free the buffers
  int b;
  for (b =0 ; b < MAXNB; b++) 
    {
      CAEN_DGTZ_SWStopAcquisition(PKU_DGTZ_handle[b]);
      CAEN_DGTZ_CloseDigitizer(PKU_DGTZ_handle[b]);
    }
  CAEN_DGTZ_FreeReadoutBuffer(&PKU_DGTZ_buffer);
}

int ProgramDigitizer_V1724(int handle, DigitizerParams_t Params, CAEN_DGTZ_DPP_PHA_Params_t DPPParams)
{
  // uint32_t ReadRegister;
  
  // This function uses the CAENDigitizer API functions to perform the digitizer's initial configuration
  int i, ret = 0;

  // Reset the digitizer
  ret |= CAEN_DGTZ_Reset(handle);
  if (ret) 
    {
      printf("ERROR: can't reset the digitizer.\n");
      return -1;
    }

  // set the configuration register for basic function
  ret |= CAEN_DGTZ_WriteRegister(handle, 0x8000, 0x01000114);  // Channel Control Reg (indiv trg, seq readout) ??
  // ret |= CAEN_DGTZ_WriteRegister(handle,0x811C, 0xC003C); // serve per mandare SW trg individuali e per abilitare il ts reset
  // ret |= CAEN_DGTZ_WriteRegister(handle,0x8004, 0x00000004); // Enable indiv trgin

  // Set the DPP acquisition mode
  //   This setting affects the modes Mixed and List (see CAEN_DGTZ_DPP_AcqMode_t definition for details)
  ret |= CAEN_DGTZ_SetDPPAcquisitionMode(handle, Params.DPPAcqMode, Params.SaveParam);

  // Set the digitizer acquisition mode (CAEN_DGTZ_SW_CONTROLLED or CAEN_DGTZ_S_IN_CONTROLLED)
  ret |= CAEN_DGTZ_SetAcquisitionMode(handle, Params.AcqMode);

  // Set the number of samples for each waveform
  ret |= CAEN_DGTZ_SetRecordLength(handle, Params.RecordLength);

  // Set the I/O level (CAEN_DGTZ_IOLevel_NIM or CAEN_DGTZ_IOLevel_TTL)
  ret |= CAEN_DGTZ_SetIOLevel(handle, Params.IOlev);

  /* Set the digitizer's behaviour when an external trigger arrives:
     see CAENDigitizer user manual, chapter "Trigger configuration" for details */
  ret |= CAEN_DGTZ_SetExtTriggerInputMode(handle, Params.ExtTrgMode);

  // Set the digitizer's behaviour when a software trigger arrives
  ret |= CAEN_DGTZ_SetSWTriggerMode(handle, Params.SWTrgMode);

  // Set the enabled channels
  ret |= CAEN_DGTZ_SetChannelEnableMask(handle, Params.ChannelMask);

  // Set the digitizer's behaviour when a self trigger arrives
  ret |= CAEN_DGTZ_SetChannelSelfTrigger(handle, Params.SelfTrgMode, Params.ChannelMask);

  // Set how many events to accumulate in the board memory before being available for readout
  ret |= CAEN_DGTZ_SetDPPEventAggregation(handle, Params.EventAggr, 0);




  /* Set the mode used to syncronize the acquisition between different boards.
     In this example the sync is disabled */
  ret |= CAEN_DGTZ_SetRunSynchronizationMode(handle, Params.RunSyncMode);

  // Set the delay time between the arrival of the start signal at the input of the board (either SIN or TRGIN) and the actual start of run
  ret |= CAEN_DGTZ_WriteRegister(handle, 0x8170, Params.Run_Start_Stop_Delay);

  // Set the DPP specific parameters for the channels in the given channelMask
  ret |= CAEN_DGTZ_SetDPPParameters(handle, Params.ChannelMask, &DPPParams);

  for(i=0; i<MaxNChannels; i++) 
    {
      if (Params.ChannelMask & (1<<i)) 
	{
	  // Set a DC offset to the input signal to adapt it to digitizer's dynamic range
	  ret |= CAEN_DGTZ_SetChannelDCOffset(handle, i,Params.ChannelDCOffset[i] );

	  // Set the Pre-Trigger size (in samples)
	  ret |= CAEN_DGTZ_SetDPPPreTriggerSize(handle, i, Params.DPPPreTriggerSize[i]);

	  // Set the polarity for the given channel (CAEN_DGTZ_PulsePolarityPositive or CAEN_DGTZ_PulsePolarityNegative)
	  ret |= CAEN_DGTZ_SetChannelPulsePolarity(handle, i, Params.PulsePolarity[i]);
	}
    }

  // GOTO
  // 这里涉及到采样频率问题。全采样或者降低一半频率来记录两种信息。
  // ret |= CAEN_DGTZ_SetDPP_VirtualProbe(handle, ANALOG_TRACE_1, CAEN_DGTZ_DPP_VIRTUALPROBE_Input);
  // ret |= CAEN_DGTZ_SetDPP_VirtualProbe(handle, ANALOG_TRACE_2, CAEN_DGTZ_DPP_VIRTUALPROBE_TrapezoidReduced);
  // ret |= CAEN_DGTZ_SetDPP_VirtualProbe(handle, DIGITAL_TRACE_1, CAEN_DGTZ_DPP_DIGITALPROBE_Peaking);

  /* Set the virtual probes settings
     DPP-PHA can save:
     2 analog waveforms:
     the first and the second can be specified with the VIRTUALPROBE 1 and 2 parameters
        
     4 digital waveforms:
     the first is always the trigger
     the second is always the gate
     the third and fourth can be specified with the DIGITALPROBE 1 and 2 parameters

     CAEN_DGTZ_DPP_VIRTUALPROBE_SINGLE -> Save only the Input Signal waveform
     CAEN_DGTZ_DPP_VIRTUALPROBE_DUAL   -> Save also the waveform specified in VIRTUALPROBE

     Virtual Probes 1 types:
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_trapezoid
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_Delta
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_Delta2
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_Input
    
     Virtual Probes 2 types:
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_Input
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_S3
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_DigitalCombo
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_trapBaseline
     CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_None

     Digital Probes types:
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_trgKln
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_Armed
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_PkRun
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_PkAbort
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_Peaking
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_PkHoldOff
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_Flat
     CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_trgHoldOff */

  ret |= CAEN_DGTZ_SetDPP_PHA_VirtualProbe(handle, CAEN_DGTZ_DPP_VIRTUALPROBE_SINGLE, CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_Input, CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_None, CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_Peaking);
  // ret |= CAEN_DGTZ_SetDPP_PHA_VirtualProbe(handle, CAEN_DGTZ_DPP_VIRTUALPROBE_DUAL, CAEN_DGTZ_DPP_PHA_VIRTUALPROBE1_Delta2, CAEN_DGTZ_DPP_PHA_VIRTUALPROBE2_Input, CAEN_DGTZ_DPP_PHA_DIGITAL_PROBE_TRGHoldoff);

  
  if (ret) 
    {
      printf("Warning: errors found during the programming of the digitizer.\nSome settings may not be executed\n");
      return ret;
    }

  return 0;
}



int ReadDPPParameters_PHA(DigitizerParams_t *Params, CAEN_DGTZ_DPP_PHA_Params_t *DPPParams)
{
  int b,ch,i;
  FILE *file;
  int RecLen;
  int ChaMas;
  char chamas[16];//
  int Board_Read;
  char All[4], Pol[4];
  char str[255], BoardTag[MAXNB][255];
  float Params_Data[MaxNChannels][PARAMS_NUM];
  int ChNo;
  long file_pos1, file_pos2;
  uint32_t RunStartStopDelay;
  file = fopen(PKU_DGTZ_BoardParametersFileName, "r");

  for(b=0; b<MAXNB; b++) 
    {
      sprintf(BoardTag[b], "*** Board: %02d ***\n", b);
      Board_Read=0;
      ChaMas=0;

      // read file
      while(fgets(str,255,file)!=NULL) 
	{
	  // for Board tag
	  if(strcmp(str,BoardTag[b])!=0) continue;
	  printf("\n%s", str);
	  Board_Read=1;

	  if(strcmp(fgets(str,255,file),"[RunStartStopDelay]\n")!=0) 
	    {
	      printf("Read [RunStartStopDelay] ERROR! <DPP_Parameters.txt>\n"); 
	      return -1;
	    }
	  fscanf(file,"%u\n",&RunStartStopDelay);
	  Params[b].Run_Start_Stop_Delay = RunStartStopDelay;
	  printf("[RunStartStopDelay]\n%u\n",RunStartStopDelay);

	  if(strcmp(fgets(str,255,file),"[RecordLength]\n")!=0) 
	    {
	      printf("Read [RecordLength] ERROR! <DPP_Parameters.txt>\n"); 
	      return -1;
	    }
	  fscanf(file,"%d\n",&RecLen);
	  Params[b].RecordLength = RecLen;
	  printf("[RecordLength]\n%d\n",RecLen);

	  if(strcmp(fgets(str,255,file),"[ChannelMask]\n")!=0) 
	    {
	      printf("Read [ChannelMask] ERROR! <DPP_Parameters.txt>\n"); 
	      return -1;
	    }
	  ChaMas=0;
	  fscanf(file,"\n%s\n",&chamas);//
	  // printf ("%s\n",chamas);
	  for(i=0;chamas[i]!='\0';i++)
	    {
	      if(chamas[i]=='1'||chamas[i]=='0')
		{
		  ChaMas<<=1;
		  ChaMas+=chamas[i]-'0';
		}
	      else 
		{
		  printf ("[ChannelMask] input error \n");
		}
	    }  
	  Params[b].ChannelMask=ChaMas;
	  // printf("[ChannelMask]\n%d\n",ChaMas);
	  printf ("[ChannelMask]\n%s\n",chamas);

	  // for [COMMON] tag
	  fgets(str,255,file); // Parameter names
	  if(strcmp(fgets(str,255,file),"[COMMON]\n")!=0) 
	    {
	      printf("Read [COMMEN] ERROR! <DPP_Parameters.txt>\n"); 
	      return -1;
	    }
	  printf("%s", str);
	  fscanf(file,"%s %s",All,Pol);
	  if(strcmp(All,"ALL")!=0) 
	    {
	      printf("Read [ALL] ERROR! <DPP_Parameters.txt>\n"); 
	      return -1;
	    }
	  for(i=0; i<PARAMS_NUM; i++) 
	    fscanf(file,"%f",&Params_Data[0][i]);
	  printf("%s %s %f %f %f ...\n", All, Pol, Params_Data[0][0], Params_Data[0][1], Params_Data[0][2]);
	  
	  for(ch=0; ch<MaxNChannels; ch++) 
	    {
	      // Pulse Polarity (CAEN_DGTZ_PulsePolarityPositive or CAEN_DGTZ_PulsePolarityNegative)
	      if(strcmp(Pol,"POS")==0)
		Params[b].PulsePolarity[ch] = CAEN_DGTZ_PulsePolarityPositive;
	      else if(strcmp(Pol,"NEG")==0)
		Params[b].PulsePolarity[ch] = CAEN_DGTZ_PulsePolarityNegative;
	      else
		{
		  printf("Read [POL] ERROR! <DPP_Parameters.txt>\n"); 
		  return -1;
		}
	      // set all channels
	      for(i=0; i<PARAMS_NUM; i++) 
		{
		  if(ch!=0)
		    {
		      Params_Data[ch][i] = Params_Data[0][i];
		    }
		}
	    }

	  // for [INDIVIDUAL] tag
	  fgets(str,255,file); // for "\n"
	  if(strcmp(fgets(str,255,file),"[INDIVIDUAL]\n")!=0) 
	    {
	      printf("Read [INDIVIDUAL] ERROR! <DPP_Parameters.txt> \n"); 
	      return -1;
	    }
	  printf("%s", str);
	  for(ch=0; ch<MaxNChannels; ch++) 
	    { 
	      // individual loop
	      file_pos1=ftell(file);
	      fgets(str,255,file); // for individual parameters
	      if(strlen(str)<50) break;
	      file_pos2=ftell(file);
	      fseek(file,file_pos1-file_pos2,SEEK_CUR);
	      fscanf(file,"%d %s",&ChNo,Pol);
	      if(ChNo<0 || ChNo>=MaxNChannels) {
		fseek(file,file_pos2,SEEK_SET);
		continue;
	      }
	      // Pulse Polarity (CAEN_DGTZ_PulsePolarityPositive or CAEN_DGTZ_PulsePolarityNegative)
	      if(strcmp(Pol,"POS")==0)
		Params[b].PulsePolarity[ChNo] = CAEN_DGTZ_PulsePolarityPositive;
	      else if(strcmp(Pol,"NEG")==0)
		Params[b].PulsePolarity[ChNo] = CAEN_DGTZ_PulsePolarityNegative;
	      else
		{
		  printf("Read [POL] ERROR! <DPP_Parameters.txt>\n"); 
		  return -1;
		}
	      for(i=0; i<PARAMS_NUM; i++)
		fscanf(file,"%f",&Params_Data[ChNo][i]);
	      fgets(str,255,file); // for "\n"
	      printf("%d %s %f %f %f ...\n", ChNo, Pol, Params_Data[ChNo][0], Params_Data[ChNo][1], Params_Data[ChNo][2]);
	    } // individual loop
	} // board tag loop

      if(Board_Read==0) 
	{
	  printf("Read [Board Tag] ERROR! <DPP_Parameters.txt>\n"); 
	  return -1;
	}


      //GOTO
      // Set corresponding DPP parameters
      for(ch=0; ch<MaxNChannels; ch++) 
	{
	  // DC offset for the input signal to adapt it to digitizer's dynamic range
	  Params[b].ChannelDCOffset[ch] = 0x7FFF+Params_Data[ch][0]/100*0xFFFF;   // 0x7FFF+(XXXX)*0xFFFF
	  printf ("%f\n",Params_Data[ch][0]);
	  /* Params[b].ChannelDCOffset[ch] = Params_Data[ch][0]; */
	  printf ("%f\n\n",Params[b].ChannelDCOffset[ch]);

	  // Pre-Trigger size (in samples)
	  Params[b].DPPPreTriggerSize[ch] = Params_Data[ch][1];
	  // DPP_PHA Parameters
	  DPPParams[b].thr[ch] = Params_Data[ch][2]; // Trigger Threshold
	  DPPParams[b].a[ch] = Params_Data[ch][3]; // Trigger Filter smoothing factor
	  DPPParams[b].b[ch] = Params_Data[ch][4]; // Input Signal Rise time (Delay(b)) (Unit: ns)
	  DPPParams[b].trgho[ch] = Params_Data[ch][5]; // Trigger Hold Off (Unit: ns) (0 - 5.040 us)
	  DPPParams[b].M[ch] = Params_Data[ch][6]; // Decay Time Constant (Unit: ns)
	  DPPParams[b].k[ch] = Params_Data[ch][7]; // Trapezoid Rise Time (Unit: ns)
	  DPPParams[b].m[ch] = Params_Data[ch][8]; // Trapezoid Flat Top  (Unit: ns)
	  DPPParams[b].nsbl[ch] = Params_Data[ch][9]; // Number of sample for Baseline Mean (3 = bx10 = 64 samples)
	  DPPParams[b].enf[ch] = Params_Data[ch][10]; // Energy Normalization Factor (Trapezoid Gain)
	  DPPParams[b].ftd[ch] = Params_Data[ch][11]; // Flat top delay (peaking delay) (Unit: ns)
	  DPPParams[b].nspk[ch] = Params_Data[ch][12]; // Number of sample for Peak Mean (2 = bx10 = 16 samples)
	  DPPParams[b].blho[ch] = Params_Data[ch][13]; // Base Line Hold Off (Unit: ns) (0 - 2.550 us)
	  DPPParams[b].pkho[ch] = Params_Data[ch][14]; // Peak Hold Off (Unit: ns) (0 - 20.40 us)
	  DPPParams[b].twwdt[ch] = Params_Data[ch][15]; // Time window for rise time discrimination (Unit: ns) (0 - 1.023 us)
	  DPPParams[b].dgain[ch] = Params_Data[ch][16]; // Digital Probe Gain
	  DPPParams[b].decimation[ch] = Params_Data[ch][17]; // Decimation of Input Signal
	  DPPParams[b].trgwin[ch] = Params_Data[ch][18]; // Trigger acceptance window in coincidence mode(int) (Unit: ns)
	  DPPParams[b].otrej[ch] = Params_Data[ch][19];
	}

      printf("Read parameters for board %02d successfully!\n\n", b);
      rewind(file);
    }
  fclose(file);
  return 0;
}

// Read DGTZ Registers 
// return  0=success; -1=error
int Read_DGTZ_Register(int handle,int MaxNChInBoard)
{
  int ret=0;
  uint32_t Register_Data;
  char bstr[64];
  bzero(bstr, sizeof(bstr));

  // CONFIG
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8000, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIG (0x8000,rw): %s\n",bstr);

  // CONFIG(BitSet)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8004, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIG (BitSet) (0x8004,rw): %s\n",bstr);

  // CONFIG(BitClear)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8008, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIG (BitClear) (0x8008,rw): %s\n",bstr);

  // BUFF_ORG
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x800C, &Register_Data);
  // printf("BUFF_ORG (0x800C): %u\n",Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BUFF_ORG (0x800C,rw): %s\n",bstr);

  // CUST_SIZE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8020, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CUST_SIZE (0x8020,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1020 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CUST_SIZE (0x1%d20,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // ACQUISITION_CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8100, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ACQUISITION_CONTROL (0x8100,rw): %s\n",bstr);

  // ACQUISITION_STATUS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8104, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ACQUISITION_STATUS (0x8104,r): %s\n",bstr);

  // SOFTWARE_TRIGGER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8108, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE_TRIGGER (0x8108,w): %s\n",bstr);   

  // GLOBAL_TRIGGER_MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x810C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("GLOBAL_TRIGGER_MASK (0x810C,rw): %s\n",bstr);

  // TRIGGER_OUT_MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8110, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("TRIGGER_OUT_MASK (0x8110,rw): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8114, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8114): %s\n",bstr);
      
  // LVDS_DATA
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8118, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("LVDS_DATA (0x8118,rw): %s\n",bstr);

  // FRONT_PANEL_CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x811C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FRONT_PANEL_CONTROL (0x811C,rw): %s\n",bstr);

  // CHANNEL_ENABLE_MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8120, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CHANNEL_ENABLE_MASK (0x8120,rw): %s\n",bstr);

  // FIRMWARE_REVISION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8124, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FIRMWARE_REVISION (0x8124,r): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x812C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x812C): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8130, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8130): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8134, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8134): %s\n",bstr);
      
  // MONITOR_DAC_CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8138, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("MONITOR_DAC_CONTROL (0x8138,rw): %s\n",bstr);

  // SW_CLOCK_SYNC
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x813C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SW_CLOCK_SYNC (0x813C,w): %s\n",bstr);
      
  // BOARD_INFO
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8140, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BOARD_INFO (0x8140,r): %s\n",bstr);

  // MINITOR_DAC_MODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8144, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("MINITOR_DAC_MODE (0x8144,rw): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8148, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8148): %s\n",bstr);
      
  // EVENT_SIZE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x814C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("EVENT_SIZE (0x814C,rw): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8150, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8150): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8154, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8154): %s\n",bstr);
      
  // TIME_BOMB_DOWNCOUNTER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8158, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("TIME_BOMB_DOWNCOUNTER (0x8158,r): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x815C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x815C): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8164, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8164): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x816C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x816C): %s\n",bstr);
           
  // RUN_START_STOP_DELAY
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8170, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("RUN_START_STOP_DELAY (0x8170,rw): %s\n",bstr);

  // Reserved
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8174, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("Reserved (0x8174): %s\n",bstr);
      
  // VETO
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x817C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VETO (0x817C,rw): %s\n",bstr);

  printf("Reserved (0x8180-0x819C)\n");
  printf("Reserved (0x8200-0x83FC)\n");
      
  // READOUT_CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF00, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("READOUT_CONTROL (0xEF00,rw): %s\n",bstr);

  // READOUT_STATUS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF04, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("READOUT_STATUS (0xEF04,rw): %s\n",bstr);

  // VME_GEO_ADDRESS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF08, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME_GEO_ADDRESS (0xEF08,rw): %s\n",bstr);

  // VME_MULITCAST_CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF0C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME_MULITCAST_CONTROL (0xEF0C,rw): %s\n",bstr);

  // VME_ADDRESS_RELOCATION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF10, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME_ADDRESS_RELOCATION (0xEF10,rw): %s\n",bstr);

  // VME_INTERRUPT_ID
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF14, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME_INTERRUPT_ID (0xEF14,rw): %s\n",bstr);

  // READOUT_INTERRUPT_CONDITION(EVENT NUMBER)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF18, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("READOUT_INTERRUPT_CONDITION(EVENT NUMBER) (0xEF18,rw): %s\n",bstr);

  // READOUT_BLT_AGGREGATE_NUMBER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF1C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("READOUT_BLT_AGGREGATE_NUMBER (0xEF1C,rw): %s\n",bstr);

  // DUMMY
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF20, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DUMMY (0xEF20,rw): %s\n",bstr);

  // SOFTWARE_RESET
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF24, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE_RESET (0xEF24,w): %s\n",bstr);

  // SOFTWARE_CLEAR
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF28, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE_CLEAR (0xEF28,w): %s\n",bstr);
      
  // BOARD_CONFIGURATION_RELOAD
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF34, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BOARD_CONFIGURATION_RELOAD (0xEF34,rw): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF000, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM (0xF000,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF004, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH2 (0xF004,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF008, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH1 (0xF008,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF00C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH0 (0xF00C,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF010, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT2 (0xF010,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF014, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT1 (0xF014,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF018, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT0 (0xF018,r): %s\n",bstr);

  // CONFIGURATION_ROM_C_CODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF01C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_C_CODE (0xF01C,r): %s\n",bstr);

  // CONFIGURATION_ROM_R_CODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF020, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_R_CODE (0xF020,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF024, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI2 (0xF024,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF028, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI1 (0xF028,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF02C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI0 (0xF02C,r): %s\n",bstr);

  // CONFIGURATION_ROM_VERSION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF030, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_VERSION (0xF030,r): %s\n",bstr);

  // CONFIGURATION_ROM_FORM_FACTOR
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF034, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_FORM_FACTOR (0xF034,r): %s\n",bstr);

  // CONFIGURATION_ROM_BOARD_ID1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF038, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_BOARD_ID1 (0xF038,r): %s\n",bstr);

  // CONFIGURATION_ROM_BOARD_ID0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF03C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_BOARD_ID0 (0xF03C,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS3
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF040, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS3 (0xF040,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF044, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS2 (0xF044,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF048, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS1 (0xF048,r): %s\n",bstr);

  // CONFIGURATION_ROM_PCB_RESION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF04C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_PCB_RESION (0xF04C,r): %s\n",bstr);

  // CONFIGURATION_ROM_SERNUM1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF080, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_SERNUM1 (0xF080,r): %s\n",bstr);

  // CONFIGURATION_ROM_SERNUM0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF084, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_SERNUM0 (0xF084,r): %s\n",bstr);

  // CONFIGURATION_ROM_VCXO_TYPE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF088, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_VCXO_TYPE (0xF088,r): %s\n",bstr);

  // PRE_TRG
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8038, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("PRE_TRG (0x8038,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1038 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("PRE_TRG (0x1%d38,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // NEV_AGGREGATE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8034, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("NEV_AGGREGATE (0x8034,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1034 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("NEV_AGGREGATE (0x1%d34,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_TRG_FILTER_SMOOTHING(a)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8054, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_TRG_FILTER_SMOOTHING(a) (0x8054,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1054 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_TRG_FILTER_SMOOTHING(a) (0x1%d54,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_INPUT_RISE_TIME(Tirt)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8058, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_INPUT_RISE_TIME(Tirt) (0x8058,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1058 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_INPUT_RISE_TIME(Tirt) (0x1%d58,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_TRAPEZOID_RISE_TIME(Trise)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x805C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_TRAPEZOID_RISE_TIME(Trise) (0x805C,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x105C | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_TRAPEZOID_RISE_TIME(Trise) (0x1%d5C,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_TRAPEZOID_FLAT_TOP(Tflattop)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8060, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_TRAPEZOID_FLAT_TOP(Tflattop) (0x8060,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1060 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_TRAPEZOID_FLAT_TOP(Tflattop) (0x1%d60,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_PEAKINGTIME(Tpk)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8064, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_PEAKINGTIME(Tpk) (0x8064,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1064 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_PEAKINGTIME(Tpk) (0x1%d64,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_DECAY_TIME(M)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8068, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_DECAY_TIME(M) (0x8068,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1068 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_DECAY_TIME(M) (0x1%d68,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_TRG_THRESHOLD(thr)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x806C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_TRG_THRESHOLD(thr) (0x806C,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x106C | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_TRG_THRESHOLD(thr) (0x1%d6C,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_RTD_WINDOW_WIDTH(Trtdw)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8070, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_RTD_WINDOW_WIDTH(Trtdw) (0x8070,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1070 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_RTD_WINDOW_WIDTH(Trtdw) (0x1%d70,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_RTRG_HOLD_OFF(Ttrgho)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8074, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_RTRG_HOLD_OFF(Ttrgho) (0x8074,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1074 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_RTRG_HOLD_OFF(Ttrgho) (0x1%d74,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_PEAK_HOLD_OFF_EXTENSION(Tpkhoe)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8078, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_PEAK_HOLD_OFF_EXTENSION(Tpkhoe) (0x8078,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1078 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_PEAK_HOLD_OFF_EXTENSION(Tpkhoe) (0x1%d78,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_BASELINE_HOLD_OFF_EXTENSION(Tblhoe)
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x807C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_BASELINE_HOLD_OFF_EXTENSION(Tblhoe) (0x807C,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x107C | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_BASELINE_HOLD_OFF_EXTENSION(Tblhoe) (0x1%d7C,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // DPP_MISC
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8080, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("DPP_MISC (0x8080,rw) (all channels): %s\n",bstr);
  for (int ch = 0; ch < MaxNChInBoard; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1080 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("DPP_MISC (0x1%d80,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  if(ret) {
    return -1;
  }
  return 0;
}


int Read_DGTZ_V1724_Register(int handle)
{
  int ret=0;
  uint32_t Register_Data;
  char bstr[64];
  bzero(bstr, sizeof(bstr));

  // CONFIGURATION_ROM_CHECKSUM
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF000, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM (0xF000,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF004, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH2 (0xF004,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF008, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH1 (0xF008,r): %s\n",bstr);

  // CONFIGURATION_ROM_CHECKSUM_LENGTH0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF00C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CHECKSUM_LENGTH0 (0xF00C,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF010, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT2 (0xF010,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF014, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT1 (0xF014,r): %s\n",bstr);

  // CONFIGURATION_ROM_CONSTANT0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF018, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_CONSTANT0 (0xF018,r): %s\n",bstr);

  // CONFIGURATION_ROM_C_CODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF01C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_C_CODE (0xF01C,r): %s\n",bstr);

  // CONFIGURATION_ROM_R_CODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF020, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_R_CODE (0xF020,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF024, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI2 (0xF024,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF028, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI1 (0xF028,r): %s\n",bstr);

  // CONFIGURATION_ROM_OUI0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF02C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_OUI0 (0xF02C,r): %s\n",bstr);

  // CONFIGURATION_ROM_VERSION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF030, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_VERSION (0xF030,r): %s\n",bstr);

  // CONFIGURATION_ROM_BOARD2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF034, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_BOARD2 (0xF034,r): %s\n",bstr);

  // CONFIGURATION_ROM_BOARD1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF038, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_BOARD1 (0xF038,r): %s\n",bstr);

  // CONFIGURATION_ROM_BOARD0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF03C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_BOARD0 (0xF03C,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS3
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF040, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS3 (0xF040,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS2
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF044, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS2 (0xF044,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF048, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS1 (0xF048,r): %s\n",bstr);

  // CONFIGURATION_ROM_REVIS1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF04C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_REVIS1 (0xF04C,r): %s\n",bstr);

  // CONFIGURATION_ROM_SERNUM1
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF080, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_SERNUM1 (0xF080,r): %s\n",bstr);

  // CONFIGURATION_ROM_SERNUM0
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xF084, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION_ROM_SERNUM0 (0xF084,r): %s\n",bstr);

  // CHANNEL n ZS_THRES
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1024 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n ZS_THRES (0x1%d24,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CANNEL n ZS_MSAMP
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1028 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CANNEL n ZS_MSAMP (0x1%d28,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n THRESHOLD
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1080 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n THRESHOLD (0x1%d80,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n OVER/UNDER THRESHOLD
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1084 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n OVER/UNDER THRESHOLD (0x1%d84,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n STATUS
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1088 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n STATUS (0x1%d88,r) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n AMC FPGA FIREWARE
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x108C | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n AMC FPGA FIREWARE (0x1%d8C,r) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n BUFFER OCCUPANCY
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1094 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n BUFFER OCCUPANCY (0x1%d94,r) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANEL n DAC
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x1098 | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANEL n DAC (0x1%d98,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL n ADC CONFIGURATION
  for (int ch = 0; ch < 8; ++ch)
    {
      ret |= CAEN_DGTZ_ReadRegister(handle, (0x109C | (ch<<8)), &Register_Data);
      Decimal2Binary(Register_Data,bstr);
      printf("CHANNEL n ADC CONFIGURATION (0x1%d9C,rw) (channel %d): %s\n",ch,ch,bstr);
    }

  // CHANNEL CONFIGURATION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8000, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CHANNEL CONFIGURATION (0x8000,rw): %s\n",bstr);

  // CHANNEL CONFIGURATION BIT SET
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8004, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CHANNEL CONFIGURATION BIT SET (0x8004,w): %s\n",bstr);

  // CHANNEL CONFIGURATION BIT CLEAR
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8008, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CHANNEL CONFIGURATION BIT CLEAR (0x8008,w): %s\n",bstr);

  // BUFFER_ORGANIZATION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x800C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BUFFER_ORGANIZATION (0x800C,rw): %s\n",bstr);

  // BUFFER_FREE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8010, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BUFFER_FREE (0x8010,rw): %s\n",bstr);

  // CUSTOM_SIZE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8020, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CUSTOM_SIZE (0x8020,rw): %s\n",bstr);

  // ANALOG MONITOR POLARITY AND SHIFT
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x802A, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ANALOG MONITOR POLARITY AND SHIFT (0x802A,rw): %s\n",bstr);

  // ACQUISITION CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8100, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ACQUISITION CONTROL (0x8100,rw): %s\n",bstr);

  // ACQUISITION STATUS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8104, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ACQUISITION STATUS (0x8104,r): %s\n",bstr);

  // SOFTWARE TRIGGER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8108, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE TRIGGER (0x8108,w): %s\n",bstr);

  // TRIGGER SOURCE ENABLE MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x810C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("TRIGGER SOURCE ENABLE MASK (0x810C,rw): %s\n",bstr);

  // FRONT PANEL TRIGGER OUT ENABLE MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8110, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FRONT PANEL TRIGGER OUT ENABLE MASK (0x8110,rw): %s\n",bstr);

  // POST TRIGGER SETTING
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8114, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("POST TRIGGER SETTING (0x8114,rw): %s\n",bstr);

  // FRONT PANEL I/O DATA
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8118, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FRONT PANEL I/O DATA (0x8118,rw): %s\n",bstr);

  // FRONT PANEL I/O CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x811C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FRONT PANEL I/O CONTROL (0x811C,rw): %s\n",bstr);

  // CHANNEL ENABLE MASK
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8120, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CHANNEL ENABLE MASK (0x8120,rw): %s\n",bstr);

  // ROC FPGA FIRMWARE REVISION
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8124, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ROC FPGA FIRMWARE REVISION (0x8124,r): %s\n",bstr);

  // EVENT STORED
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x812C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("EVENT STORED (0x812C,r): %s\n",bstr);

  // SET MONITOR DAC
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8138, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SET MONITOR DAC (0x8138,rw): %s\n",bstr);

  // BOARD INFO
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8140, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BOARD INFO (0x8140,r): %s\n",bstr);

  // MONITOR MODE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8144, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("MONITOR MODE (0x8144,rw): %s\n",bstr);

  // EVENT SIZE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x814C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("EVENT SIZE (0x814C,r): %s\n",bstr);

  // ANALOG MONITOR
  ret |= CAEN_DGTZ_ReadRegister(handle, 0x8150, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("ANALOG MONITOR (0x8150,rw): %s\n",bstr);

  // VME CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF00, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME CONTROL (0xEF00,rw): %s\n",bstr);

  // VME STATUS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF04, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("VME STATUS (0xEF04,r): %s\n",bstr);

  // BOARD ID
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF08, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BOARD ID (0xEF08,rw): %s\n",bstr);

  // MCST BASE ADDRESS AND CONTROL
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF0C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("MCST BASE ADDRESS AND CONTROL (0xEF0C,rw): %s\n",bstr);

  // RELOCATION ADDRESS
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF10, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("RELOCATION ADDRESS (0xEF10,rw): %s\n",bstr);

  // INTERRUPT STATUS ID
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF14, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("INTERRUPT STATUS ID (0xEF14,rw): %s\n",bstr);

  // INTERRUPT EVENT NUMBER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF18, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("INTERRUPT EVENT NUMBER (0xEF18,rw): %s\n",bstr);

  // BLT EVENT NUMBER
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF1C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("BLT EVENT NUMBER (0xEF1C,rw): %s\n",bstr);

  // SCRATCH
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF20, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SCRATCH (0xEF20,rw): %s\n",bstr);

  // SOFTWARE RESET
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF24, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE RESET (0xEF24,w): %s\n",bstr);

  // SOFTWARE CLEAR
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF28, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("SOFTWARE CLEAR (0xEF28,w): %s\n",bstr);

  // FLASH ENABLE
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF2C, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FLASH ENABLE (0xEF2C,rw): %s\n",bstr);

  // FLASH DATA
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF30, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("FLASH DATA (0xEF30,rw): %s\n",bstr);

  // CONFIGURATION RELOAD
  ret |= CAEN_DGTZ_ReadRegister(handle, 0xEF34, &Register_Data);
  Decimal2Binary(Register_Data,bstr);
  printf("CONFIGURATION RELOAD (0xEF34,w): %s\n",bstr);

  if(ret) {
    return -1;
  }
  return 0;
}


// Read DGTZ Info
// return  0=success; -1=error
int Read_DGTZ_Info(int handle)
{
  // typedef struct {
  //     char                        ModelName[12];
  //     uint32_t                    Model;
  //     uint32_t                    Channels;
  //     uint32_t                    FormFactor;
  //     uint32_t                    FamilyCode;
  //     char                        ROC_FirmwareRel[20];
  //     char                        AMC_FirmwareRel[40];
  //     uint32_t                    SerialNumber;
  //     uint32_t                    PCB_Revision;
  //     uint32_t                    ADC_NBits;
  //     uint32_t                    SAMCorrectionDataLoaded;        //used only for x743 boards
  //     int                         CommHandle;
  //     char                        License[MAX_LICENSE_LENGTH];
  // } CAEN_DGTZ_BoardInfo_t;

  int ret;// CAEN_DGTZ_ErrorCode ret;
  CAEN_DGTZ_BoardInfo_t BoardInfo;
  ret = CAEN_DGTZ_GetInfo(handle, &BoardInfo);
  if(ret)
    {
      printf("Get CAEN DGTZ Info error.\n");
      return -1;
    }
  printf("ModelName:%s\n",BoardInfo.ModelName);
  printf("Model:%u\n",BoardInfo.Model);
  printf("Channels:%u\n",BoardInfo.Channels);
  printf("FormFactor:%u\n",BoardInfo.FormFactor);
  printf("FamilyCode:%u\n",BoardInfo.FamilyCode);
  printf("ROC_FirmwareRel:%s\n",BoardInfo.ROC_FirmwareRel);
  printf("AMC_FirmwareRel:%s\n",BoardInfo.AMC_FirmwareRel);
  printf("SerialNumber:%u\n",BoardInfo.SerialNumber);
  printf("PCB_Revision:%u\n",BoardInfo.PCB_Revision);
  printf("ADC_NBits:%u\n",BoardInfo.ADC_NBits);
  printf("SAMCorrectionDataLoaded:%u\n",BoardInfo.SAMCorrectionDataLoaded);
  printf("CommHandle:%d\n",BoardInfo.CommHandle);
  printf("License:%s\n",BoardInfo.License);

  return 0;
}


// 
// DigitizerConfigure.cc ends here
