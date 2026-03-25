#pragma once
#include "CaptureIncludes.h"
#include "CaptureVariables.h"
#include "CaptureReset.cpp"
#include "CaptureTexture.cpp"
#include "CaptureRender.cpp"

namespace
{
	CaptureResult UpdateScreenTexture()
	{
		AVFinally(
			{
				//Release resources
				DirectXResetVariablesLoop();
			});
		try
		{
			//Get frame from capture pool
			auto frame = vWgcInstance.vGraphicsCaptureFramePool.TryGetNextFrame();

			//Check if screen capture failed
			if (frame == NULL)
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Frame is empty skipping convert") };
			}

			//Convert frame capture to texture
			auto access = frame.Surface().as<Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess>();
			hResult = access->GetInterface(winrt::guid_of<ID3D11Texture2D>(), (void**)&vDirectXInstance.iD3D11Texture2D0ScreenCapture);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Failed converting frame capture to texture") };
			}

			//Draw screen capture texture
			capResult = RenderDrawTexture2D(vDirectXInstance.iD3D11Texture2D0ScreenCapture, VertexVerticesCountScreen);
			if (capResult.Status != CaptureStatus::Success)
			{
				return capResult;
			}

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"UpdateScreenTexture failed") };
		}
	}

	std::vector<BYTE> GetScreenBytes(BOOL flipScreen)
	{
		AVFinally(
			{
				//Release resources
				DirectXResetVariablesLoop();
			});
		try
		{
			//Check if initialized
			if (!vCaptureInstance.vInstanceInitialized)
			{
				return {};
			}

			//Update screen texture
			capResult = UpdateScreenTexture();
			if (capResult.Status != CaptureStatus::Success)
			{
				return {};
			}

			//Convert to cpu read texture
			capResult = Texture2DConvertToCpuRead(vDirectXInstance.PixelShaderMultiPass ? vDirectXInstance.iD3D11Texture2D0RenderTargetViewPass2 : vDirectXInstance.iD3D11Texture2D0RenderTargetViewPass1);
			if (capResult.Status != CaptureStatus::Success)
			{
				return {};
			}

			//Convert texture to screen bytes
			return Texture2DConvertToScreenBytes(vDirectXInstance.iD3D11Texture2D0CpuRead, flipScreen);
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("GetScreenBytes failed.");
			return {};
		}
	}
}