#pragma once
#include "pch.h"
#include "CaptureVariables.h"
#include "CaptureMonitorInfo.cpp"
#include "CaptureCodecCheck.cpp"

namespace
{
	CaptureResult SetVideoMediaTypeOutput()
	{
		try
		{
			//Check monitor refresh rate
			UINT targetVideoFrameRate = vMediaSettings.VideoFrameRate;
			if (targetVideoFrameRate > vCaptureDetails.OriginalRefreshRate)
			{
				targetVideoFrameRate = vCaptureDetails.OriginalRefreshRate;
				AVDebugWriteLine("Monitor refresh rate lower, changed video fps to: " << targetVideoFrameRate);
			}

			//Check monitor nominal range
			MFNominalRange targetVideoNominalRange = MFNominalRange_Unknown;
			if (GetMonitorIsLimitedColorRange())
			{
				targetVideoNominalRange = MFNominalRange_16_235;
				AVDebugWriteLine("Set video nominal range to limited (16-235)");
			}
			else
			{
				targetVideoNominalRange = MFNominalRange_0_255;
				AVDebugWriteLine("Set video nominal range to full (0-255)");
			}

			//Check video targeting HDR
			BOOL targetVideoHDR = vCaptureDetails.HDREnabled && !vCaptureDetails.HDRtoSDR;

			//Check video save format
			GUID targetVideoFormat = MFVideoFormat_Base;
			if (vMediaSettings.VideoFormat == VideoFormats::H264)
			{
				if (vCaptureDetails.HDREnabled && !vCaptureDetails.HDRtoSDR)
				{
					return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"Video format does not support HDR") };
				}
				targetVideoFormat = MFVideoFormat_H264;
				AVDebugWriteLine("Set video output format to H264.");
			}
			else if (vMediaSettings.VideoFormat == VideoFormats::HEVC)
			{
				targetVideoFormat = MFVideoFormat_HEVC;
				AVDebugWriteLine("Set video output format to HEVC.");
			}
			else if (vMediaSettings.VideoFormat == VideoFormats::AV1)
			{
				targetVideoFormat = MFVideoFormat_AV1;
				AVDebugWriteLine("Set video output format to AV1.");
			}

			//Check if video format is supported
			if (!CodecCheckVideoEncoder(targetVideoFormat))
			{
				return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"Video format is not supported") };
			}

			//Create video media type
			CComPtr<IMFMediaType> imfMediaTypeVideoOutput;
			hResult = MFCreateMediaType(&imfMediaTypeVideoOutput);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"MFCreateMediaType video output failed") };
			}

			//Set encoding settings
			imfMediaTypeVideoOutput->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
			imfMediaTypeVideoOutput->SetGUID(MF_MT_SUBTYPE, targetVideoFormat);
			imfMediaTypeVideoOutput->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, 1);
			imfMediaTypeVideoOutput->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
			imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_NOMINAL_RANGE, targetVideoNominalRange);
			MFSetAttributeSize(imfMediaTypeVideoOutput, MF_MT_FRAME_SIZE, vCaptureDetails.MediaWidth, vCaptureDetails.MediaHeight);
			MFSetAttributeRatio(imfMediaTypeVideoOutput, MF_MT_FRAME_RATE, targetVideoFrameRate, 1);
			MFSetAttributeRatio(imfMediaTypeVideoOutput, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);

			//Check used video format
			if (targetVideoFormat == MFVideoFormat_HEVC)
			{
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_LEVEL, eAVEncH265VLevel6_2);
				//HDR and SDR settings
				if (targetVideoHDR)
				{
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PROFILE, eAVEncH265VProfile_Main_420_10);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PRIMARIES, MFVideoPrimaries_BT2020);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_YUV_MATRIX, MFVideoTransferMatrix_BT2020_10);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_TRANSFER_FUNCTION, MFVideoTransFunc_2084);
				}
				else
				{
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PROFILE, eAVEncH265VProfile_Main_420_8);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PRIMARIES, MFVideoPrimaries_BT709);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_YUV_MATRIX, MFVideoTransferMatrix_BT709);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_TRANSFER_FUNCTION, MFVideoTransFunc_709);
				}
			}
			else if (targetVideoFormat == MFVideoFormat_AV1)
			{
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_LEVEL, eAVEncAV1VLevel6);
				//HDR and SDR settings
				if (targetVideoHDR)
				{
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PROFILE, eAVEncAV1VProfile_Main_420_10);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PRIMARIES, MFVideoPrimaries_BT2020);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_YUV_MATRIX, MFVideoTransferMatrix_BT2020_10);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_TRANSFER_FUNCTION, MFVideoTransFunc_2084);
				}
				else
				{
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PROFILE, eAVEncAV1VProfile_Main_420_8);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PRIMARIES, MFVideoPrimaries_BT709);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_YUV_MATRIX, MFVideoTransferMatrix_BT709);
					imfMediaTypeVideoOutput->SetUINT32(MF_MT_TRANSFER_FUNCTION, MFVideoTransFunc_709);
				}
			}
			else if (targetVideoFormat == MFVideoFormat_H264)
			{
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_LEVEL, eAVEncH264VLevel6_2);
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PROFILE, eAVEncH264VProfile_Main);
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_VIDEO_PRIMARIES, MFVideoPrimaries_BT709);
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_YUV_MATRIX, MFVideoTransferMatrix_BT709);
				imfMediaTypeVideoOutput->SetUINT32(MF_MT_TRANSFER_FUNCTION, MFVideoTransFunc_709);
			}

			//Add media stream
			hResult = vMediaFoundationInstance.imfSinkWriter->AddStream(imfMediaTypeVideoOutput, &vMediaFoundationInstance.vOutVideoStreamIndex);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"AddStream video output failed") };
			}

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"SetVideoMediaTypeOutput failed") };
		}
	}

	CaptureResult SetVideoMediaTypeInput()
	{
		try
		{
			//Check monitor refresh rate
			UINT targetVideoFrameRate = vMediaSettings.VideoFrameRate;
			if (targetVideoFrameRate > vCaptureDetails.OriginalRefreshRate)
			{
				targetVideoFrameRate = vCaptureDetails.OriginalRefreshRate;
			}

			//Create video encoding parameters
			CComPtr<IMFAttributes> imfAttributesEncoding;
			MFCreateAttributes(&imfAttributesEncoding, 0);

			//Set video rate control
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonMeanBitRate, vMediaSettings.VideoBitRate * 1000);
			if (vMediaSettings.VideoRateControl == VideoRateControls::CBR)
			{
				//Constant Rate Control
				AVDebugWriteLine("Set constant media control rate: " << vMediaSettings.VideoBitRate);
				imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonRateControlMode, eAVEncCommonRateControlMode_CBR);
			}
			else if (vMediaSettings.VideoRateControl == VideoRateControls::VBR)
			{
				//Variable Rate Control
				AVDebugWriteLine("Set variable media control rate: " << vMediaSettings.VideoBitRate);
				imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonRateControlMode, eAVEncCommonRateControlMode_UnconstrainedVBR);
			}

			//Set encoding settings
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonQualityVsSpeed, 100);
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonLowLatency, 1);
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncCommonRealTime, 1);
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncMPVGOPSize, targetVideoFrameRate * 2);
			imfAttributesEncoding->SetUINT32(CODECAPI_AVEncMPVDefaultBPictureCount, 0);

			//Create video media type
			CComPtr<IMFMediaType> imfMediaTypeVideoInput;
			hResult = MFCreateMediaType(&imfMediaTypeVideoInput);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"MFCreateMediaType video input failed") };
			}

			//Set encoding settings
			imfMediaTypeVideoInput->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
			imfMediaTypeVideoInput->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, 1);
			MFSetAttributeSize(imfMediaTypeVideoInput, MF_MT_FRAME_SIZE, vCaptureDetails.MediaWidth, vCaptureDetails.MediaHeight);
			MFSetAttributeRatio(imfMediaTypeVideoInput, MF_MT_FRAME_RATE, targetVideoFrameRate, 1);
			MFSetAttributeRatio(imfMediaTypeVideoInput, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
			if (vDirectXInstance.TextureFormatOutput == DXGI_FORMAT_NV12)
			{
				AVDebugWriteLine("Set media type format to NV12 (SDR)");
				imfMediaTypeVideoInput->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_NV12);
			}
			else if (vDirectXInstance.TextureFormatOutput == DXGI_FORMAT_P010)
			{
				AVDebugWriteLine("Set media type format to P010 (HDR)");
				imfMediaTypeVideoInput->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_P010);
			}

			//Set video media type
			hResult = vMediaFoundationInstance.imfSinkWriter->SetInputMediaType(vMediaFoundationInstance.vOutVideoStreamIndex, imfMediaTypeVideoInput, imfAttributesEncoding);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"SetInputMediaType video input failed") };
			}

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"SetVideoMediaTypeInput failed") };
		}
	}
}