#pragma once
#include "pch.h"
#include "CaptureVariables.h"

namespace
{
	std::vector<BYTE> Texture2DConvertToScreenBytes(CComPtr<ID3D11Texture2D>& textureTarget, BOOL textureFlip)
	{
		try
		{
			//Map texture to subresource
			D3D11_MAPPED_SUBRESOURCE iD3DMappedSubResource;
			hResult = vDirectXInstance.iD3D11DeviceContext4->Map(textureTarget, 0, D3D11_MAP_READ, 0, &iD3DMappedSubResource);
			if (FAILED(hResult))
			{
				return {};
			}

			//Create image byte array
			std::vector<BYTE> bitmapBytes(vCaptureDetails.MediaTotalByteSize);

			//Write image byte array
			BYTE* sourceBuffer = (BYTE*)iD3DMappedSubResource.pData;
			if (textureFlip)
			{
				BYTE* bitmapBuffer = bitmapBytes.data() + vCaptureDetails.MediaTotalByteSize - vCaptureDetails.MediaRowByteSize;
				for (UINT i = 0; i < vCaptureDetails.MediaRowCount; i++)
				{
					memcpy(bitmapBuffer, sourceBuffer, vCaptureDetails.MediaRowByteSize);
					sourceBuffer += iD3DMappedSubResource.RowPitch;
					bitmapBuffer -= vCaptureDetails.MediaRowByteSize;
				}
			}
			else
			{
				BYTE* bitmapBuffer = bitmapBytes.data();
				for (UINT i = 0; i < vCaptureDetails.MediaRowCount; i++)
				{
					memcpy(bitmapBuffer, sourceBuffer, vCaptureDetails.MediaRowByteSize);
					sourceBuffer += iD3DMappedSubResource.RowPitch;
					bitmapBuffer += vCaptureDetails.MediaRowByteSize;
				}
			}

			//Unmap texture from subresource
			vDirectXInstance.iD3D11DeviceContext4->Unmap(textureTarget, 0);

			//Return result
			return bitmapBytes;
		}
		catch (...)
		{
			//Return result
			return {};
		}
	}

	CaptureResult Texture2DConvertToCpuRead(CComPtr<ID3D11Texture2D>& textureTarget)
	{
		try
		{
			//Read texture description
			D3D11_TEXTURE2D_DESC iD3DTexture2D0DescCpuRead{};
			textureTarget->GetDesc(&iD3DTexture2D0DescCpuRead);

			//Update texture description
			iD3DTexture2D0DescCpuRead.Usage = D3D11_USAGE_STAGING;
			iD3DTexture2D0DescCpuRead.BindFlags = 0;
			iD3DTexture2D0DescCpuRead.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			iD3DTexture2D0DescCpuRead.MiscFlags = 0;

			//Create cpu texture
			hResult = vDirectXInstance.iD3D11Device5->CreateTexture2D(&iD3DTexture2D0DescCpuRead, NULL, &vDirectXInstance.iD3D11Texture2D0CpuRead);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"CreateTexture2D CpuRead failed") };
			}

			//Copy target to cpu texture
			vDirectXInstance.iD3D11DeviceContext4->CopySubresourceRegion(vDirectXInstance.iD3D11Texture2D0CpuRead, 0, 0, 0, 0, textureTarget, 0, NULL);

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"Texture2DConvertToCpuRead failed") };
		}
	}
}