#pragma once
#include "pch.h"
#include "CaptureVariables.h"
#include "CaptureMonitorInfo.cpp"

namespace
{
	CaptureResult SetCaptureDetails()
	{
		try
		{
			//Get monitor details
			UINT monitorPixelsWidth = 0;
			UINT monitorPixelsHeight = 0;
			UINT monitorRefreshRate = GetMonitorRefreshRate(vDirectXInstance.iDxgiOutputDescription1.Monitor);
			GetMonitorResolution(vDirectXInstance.iDxgiOutputDescription1.Monitor, monitorPixelsWidth, monitorPixelsHeight);

			//Update capture variables
			vCaptureDetails.OriginalWidth = monitorPixelsWidth;
			vCaptureDetails.OriginalHeight = monitorPixelsHeight;
			vCaptureDetails.OriginalRefreshRate = monitorRefreshRate;

			//Check if texture resizing is needed
			vDirectXInstance.TextureResizing = vCaptureSettings.MaxPixelDimension != 0 && vCaptureDetails.OriginalWidth > vCaptureSettings.MaxPixelDimension && vCaptureDetails.OriginalHeight > vCaptureSettings.MaxPixelDimension;
			if (vDirectXInstance.TextureResizing)
			{
				DOUBLE resizedWidth = 0.01;
				DOUBLE resizedHeight = 0.01;
				UINT minDimension = min(vCaptureDetails.OriginalWidth, vCaptureDetails.OriginalHeight);
				UINT maxDimension = vCaptureSettings.MaxPixelDimension;
				//Find nearest full pixel dimensions to keep original ratio
				while (resizedWidth != (UINT)resizedWidth || resizedHeight != (UINT)resizedHeight)
				{
					DOUBLE differenceRatio = (DOUBLE)minDimension / maxDimension;
					resizedWidth = vCaptureDetails.OriginalWidth / differenceRatio;
					resizedHeight = vCaptureDetails.OriginalHeight / differenceRatio;
					maxDimension++;
				}
				vCaptureDetails.MediaWidth = resizedWidth;
				vCaptureDetails.MediaHeight = resizedHeight;
			}
			else
			{
				vCaptureDetails.MediaWidth = vCaptureDetails.OriginalWidth;
				vCaptureDetails.MediaHeight = vCaptureDetails.OriginalHeight;
			}

			//Check if display HDR is enabled
			DXGI_COLOR_SPACE_TYPE displayColorSpace = vDirectXInstance.iDxgiOutputDescription1.ColorSpace;
			vCaptureDetails.HDREnabled = GetMonitorAdvancedColorEnabled(vDirectXInstance.iDxgiOutputDescription1.Monitor);
			AVDebugWriteLine("Display HDR enabled: " << vCaptureDetails.HDREnabled << " / " << displayColorSpace);

			//Set capture textures and details
			if (vCaptureDetails.HDREnabled)
			{
				if (vCaptureSettings.HDRtoSDR)
				{
					if (vCaptureSettings.CaptureType == CaptureTypes::Image)
					{
						//Image
						vBitmapImageInstance.iWicPixelFormatGuidSource = GUID_WICPixelFormat32bppBGRA;

						//Capture
						vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_R16G16B16A16_FLOAT;

						//Output
						vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_B8G8R8A8_UNORM;

						//Details
						vCaptureDetails.HDRtoSDR = true;
						vCaptureDetails.SDRWhiteLevel = GetMonitorSDRWhiteLevel(vDirectXInstance.iDxgiOutputDescription1.Monitor);

						//Bytes
						vCaptureDetails.MediaPixelByteSize = 4;
						vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
						vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
						vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
					}
					else
					{
						//Capture
						vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_R16G16B16A16_FLOAT;

						//Output
						vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_NV12;

						//Details
						vCaptureDetails.HDRtoSDR = true;
						vCaptureDetails.SDRWhiteLevel = GetMonitorSDRWhiteLevel(vDirectXInstance.iDxgiOutputDescription1.Monitor);

						//Bytes
						vCaptureDetails.MediaPixelByteSize = 4;
						vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
						vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
						vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
					}
				}
				else
				{
					if (vCaptureSettings.CaptureType == CaptureTypes::Image)
					{
						//Image
						vBitmapImageInstance.iWicPixelFormatGuidSource = GUID_WICPixelFormat64bppRGBAHalf;

						//Capture
						vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_R16G16B16A16_FLOAT;

						//Output
						vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_R16G16B16A16_FLOAT;

						//Bytes
						vCaptureDetails.MediaPixelByteSize = 8;
						vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
						vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
						vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
					}
					else
					{
						//Capture
						vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_R16G16B16A16_FLOAT;

						//Output
						vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
						vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
						vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_P010;

						//Bytes
						vCaptureDetails.MediaPixelByteSize = 4;
						vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
						vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
						vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
					}
				}
			}
			else
			{
				if (vCaptureSettings.CaptureType == CaptureTypes::Image)
				{
					//Image
					vBitmapImageInstance.iWicPixelFormatGuidSource = GUID_WICPixelFormat32bppBGRA;

					//Capture
					vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
					vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
					vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_B8G8R8A8_UNORM;

					//Output
					vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
					vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
					vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_B8G8R8A8_UNORM;

					//Bytes
					vCaptureDetails.MediaPixelByteSize = 4;
					vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
					vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
					vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
				}
				else
				{
					//Capture
					vDirectXInstance.TextureWidthCapture = vCaptureDetails.MediaWidth;
					vDirectXInstance.TextureHeightCapture = vCaptureDetails.MediaHeight;
					vDirectXInstance.TextureFormatCapture = DXGI_FORMAT_B8G8R8A8_UNORM;

					//Output
					vDirectXInstance.TextureWidthOutput = vCaptureDetails.MediaWidth;
					vDirectXInstance.TextureHeightOutput = vCaptureDetails.MediaHeight;
					vDirectXInstance.TextureFormatOutput = DXGI_FORMAT_NV12;

					//Bytes
					vCaptureDetails.MediaPixelByteSize = 4;
					vCaptureDetails.MediaRowCount = vDirectXInstance.TextureHeightOutput;
					vCaptureDetails.MediaRowByteSize = vDirectXInstance.TextureWidthOutput * vCaptureDetails.MediaPixelByteSize;
					vCaptureDetails.MediaTotalByteSize = vDirectXInstance.TextureWidthOutput * vDirectXInstance.TextureHeightOutput * vCaptureDetails.MediaPixelByteSize;
				}
			}

			//Return result
			AVDebugWriteLine("Screen capture media dimensions, Width: " << vCaptureDetails.MediaWidth << " Height: " << vCaptureDetails.MediaHeight);
			AVDebugWriteLine("Screen capture media bytes, PixelByteSize: " << vCaptureDetails.MediaPixelByteSize << " RowCount: " << vCaptureDetails.MediaRowCount << " RowByteSize: " << vCaptureDetails.MediaRowByteSize << " TotalByteSize: " << vCaptureDetails.MediaTotalByteSize);
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"SetCaptureDetails failed") };
		}
	}
};