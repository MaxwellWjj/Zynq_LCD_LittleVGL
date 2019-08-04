/*
 * vtc_config.c
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */


#include "vtc_config.h"


video_timing video_resolutions[NUM_VIDEO_RESOLUTIONS] =
{
    // name     vav,  vfp,  vsw,  vbp,  vsp,  hav,  hfp,  hsw,  hbp,  hsp
    { "VGA",    480,   10,    2,   33,    1,  640,   16,   96,   48,    1,  25175000 }, // VIDEO_RESOLUTION_VGA
    { "480P",   480,    9,    6,   30,    0,  720,   16,   62,   60,    0,  27000000 }, // VIDEO_RESOLUTION_480P
    { "576P",   576,    5,    5,   39,    0,  720,   12,   64,   68,    0,  27000000 }, // VIDEO_RESOLUTION_576P
    { "WVGA",   480,    8,    2,   35,    1,  800,   40,  128,   88,    1,  33000000 }, // VIDEO_RESOLUTION_WVGA
    { "SVGA",   600,    1,    4,   23,    1,  800,   40,  128,   88,    1,  40000000 }, // VIDEO_RESOLUTION_SVGA
    { "WSVGA",  600,    8,    4,   23,    1, 1024,   24,  136,  160,    1,  51200000 }, // VIDEO_RESOLUTION_WSVGA
    { "XGA",    768,    3,    6,   29,    1, 1024,   24,  136,  160,    1,  65000000 }, // VIDEO_RESOLUTION_XGA
    { "720P",   720,    5,    5,   20,    1, 1280,  110,   40,  220,    1,  74250000 }, // VIDEO_RESOLUTION_720P
    { "SXGA",  1024,    1,    3,   26,    0, 1280,   48,  184,  200,    0, 110000000 }, // VIDEO_RESOLUTION_SXGA
    { "1080P", 1080,    4,    5,   36,    1, 1920,   88,   44,  148,    1, 148500000 }, // VIDEO_RESOLUTION_1080P
    { "UXGA",  1200,    1,    3,   46,    0, 1600,   64,  192,  304,    0, 162000000 }  // VIDEO_RESOLUTION_UXGA
};


void Vtc_timing_config(XVtc_Timing *vtc_timing, u32 resolutionId)
{


	vtc_timing->HActiveVideo  = video_resolutions[resolutionId].HActiveVideo;
	vtc_timing->HFrontPorch   = video_resolutions[resolutionId].HFrontPorch;
	vtc_timing->HSyncWidth    = video_resolutions[resolutionId].HSyncWidth;
	vtc_timing->HBackPorch    = video_resolutions[resolutionId].HBackPorch;
	vtc_timing->HSyncPolarity = video_resolutions[resolutionId].HSyncPolarity;
	vtc_timing->VActiveVideo  = video_resolutions[resolutionId].VActiveVideo;
	vtc_timing->V0FrontPorch  = video_resolutions[resolutionId].VFrontPorch;
	vtc_timing->V0SyncWidth   = video_resolutions[resolutionId].VSyncWidth;
	vtc_timing->V0BackPorch   = video_resolutions[resolutionId].VBackPorch;
	vtc_timing->VSyncPolarity = video_resolutions[resolutionId].VSyncPolarity;

	vtc_timing->Interlaced = 0;

}

void Vtc_init(XVtc *InstancePtr, u32 DeviceId, XVtc_Timing *vtc_timing, u32 resolutionId)
{
	int status;
	XVtc_Config	*vtc_Config;

	vtc_Config = XVtc_LookupConfig(DeviceId);
	if(vtc_Config == NULL)
	{
		xil_printf("ERR:: VTC device not found\r\n");
		return;
	}
	status = XVtc_CfgInitialize(InstancePtr, vtc_Config, vtc_Config->BaseAddress);
	if(status != XST_SUCCESS)
	{
		xil_printf("ERR:: VTC Initialization failed %d\r\n", status);
		return;
	}

	status = XVtc_SelfTest(InstancePtr);
	if(status != XST_SUCCESS)
	{
		xil_printf("ERR:: VTC SelfTest failed %d\r\n", status);
		return;
	}

	Vtc_timing_config(vtc_timing, resolutionId);

	XVtc_SetGeneratorTiming(InstancePtr, vtc_timing);
	//XVtc_Enable(InstancePtr);
	XVtc_EnableGenerator(InstancePtr);
	XVtc_RegUpdateEnable(InstancePtr);

}
