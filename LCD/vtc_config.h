/*
 * vtc_config.h
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 * */

#ifndef VTC_CONFIG_H_
#define VTC_CONFIG_H_

#include "xil_types.h"
#include "xvtc.h"

#define VTC_DEV_ID              XPAR_VTC_0_DEVICE_ID


// Video Pattern Generator - Video Resolution values
#define VIDEO_RESOLUTION_VGA       0
#define VIDEO_RESOLUTION_480P      1
#define VIDEO_RESOLUTION_576P      2
#define VIDEO_RESOLUTION_WVGA      3
#define VIDEO_RESOLUTION_SVGA      4
#define VIDEO_RESOLUTION_WSVGA     5
#define VIDEO_RESOLUTION_XGA       6
#define VIDEO_RESOLUTION_720P      7
#define VIDEO_RESOLUTION_SXGA      8
#define VIDEO_RESOLUTION_1080P     9
#define VIDEO_RESOLUTION_UXGA      10
#define NUM_VIDEO_RESOLUTIONS      11

XVtc Vtc;
XVtc_Timing	Vtc_timing;


struct video_timing_t
{
    char *pName;
    u32 VActiveVideo;
    u32 VFrontPorch;
    u32 VSyncWidth;
    u32 VBackPorch;
    u32 VSyncPolarity;
    u32 HActiveVideo;
    u32 HFrontPorch;
    u32 HSyncWidth;
    u32 HBackPorch;
    u32 HSyncPolarity;
    u32 ClockFrequency;
};
typedef struct video_timing_t video_timing;

void Vtc_timing_config(XVtc_Timing *vtc_timing, u32 resolutionId);
void Vtc_init(XVtc *InstancePtr, u32 DeviceId, XVtc_Timing *vtc_timing, u32 resolutionId);


#endif /* VTC_CONFIG_H_ */
