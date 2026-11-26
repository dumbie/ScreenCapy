#pragma once
#include "pch.h"
#include "CaptureVariables.h"

namespace
{
	CaptureResult RenderUpdateVertex(VertexVertice* vertexVerticesArray, UINT vertexVerticesCount)
	{
		try
		{
			//Create buffer description
			D3D11_BUFFER_DESC bufferDescription{};
			bufferDescription.ByteWidth = sizeof(VertexVertice) * vertexVerticesCount;
			bufferDescription.Usage = D3D11_USAGE_DEFAULT;
			bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDescription.CPUAccessFlags = 0;
			bufferDescription.MiscFlags = 0;
			bufferDescription.StructureByteStride = 0;

			//Create sub resource data
			D3D11_SUBRESOURCE_DATA subResourceData{};
			subResourceData.pSysMem = vertexVerticesArray;

			//Create vertex buffer
			hResult = vDirectXInstance.iD3D11Device5->CreateBuffer(&bufferDescription, &subResourceData, &vDirectXInstance.iD3D11BufferVertex0);
			if (FAILED(hResult))
			{
				return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Failed creating vertex buffer") };
			}

			//Set vertex buffer
			UINT bufferOffsets = 0;
			UINT bufferStrides = sizeof(VertexVertice);
			vDirectXInstance.iD3D11DeviceContext4->IASetVertexBuffers(0, 1, &vDirectXInstance.iD3D11BufferVertex0, &bufferStrides, &bufferOffsets);
			vDirectXInstance.iD3D11DeviceContext4->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"RenderUpdateVertex failed") };
		}
	}

	CaptureResult RenderDrawTexture2D(CComPtr<ID3D11Texture2D>& textureTarget, UINT vertexVerticesCount)
	{
		try
		{
			//Create shader resource views
			if (vDirectXInstance.iD3D11ShaderResourceView0PassCapture1 == NULL || vDirectXInstance.iD3D11ShaderResourceView0PassCapture2 == NULL || vDirectXInstance.iD3D11ShaderResourceView0PassOutput1 == NULL)
			{
				hResult = vDirectXInstance.iD3D11Device5->CreateShaderResourceView(textureTarget, NULL, &vDirectXInstance.iD3D11ShaderResourceView0PassCapture1);
				if (FAILED(hResult))
				{
					return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Failed creating shader resource view") };
				}

				hResult = vDirectXInstance.iD3D11Device5->CreateShaderResourceView(vDirectXInstance.iD3D11Texture2D0RenderTargetViewPassCapture1, NULL, &vDirectXInstance.iD3D11ShaderResourceView0PassCapture2);
				if (FAILED(hResult))
				{
					return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Failed creating shader resource view") };
				}

				hResult = vDirectXInstance.iD3D11Device5->CreateShaderResourceView(vDirectXInstance.iD3D11Texture2D0RenderTargetViewPassCapture2, NULL, &vDirectXInstance.iD3D11ShaderResourceView0PassOutput1);
				if (FAILED(hResult))
				{
					return { .Status = CaptureStatus::Failed, .ResultCode = hResult, .Message = SysAllocString(L"Failed creating shader resource view") };
				}

				AVDebugWriteLine("Created shader resource views.");
			}

			//Pixel shader (Pass Capture 1)
			{
				//Set view port
				vDirectXInstance.iD3D11DeviceContext4->RSSetViewports(1, &vDirectXInstance.iD3D11ViewPortFull);

				//Set render target view
				vDirectXInstance.iD3D11DeviceContext4->OMSetRenderTargets(1, &vDirectXInstance.iD3D11RenderTargetView0PassCapture1, NULL);

				//Set shader resource view
				vDirectXInstance.iD3D11DeviceContext4->PSSetShaderResources(0, 1, &vDirectXInstance.iD3D11ShaderResourceView0PassCapture1);

				//Set pixel shader pass
				vDirectXInstance.iD3D11DeviceContext4->PSSetShader(vDirectXInstance.iD3D11ShaderPixel0PassCapture1, NULL, 0);

				//Draw texture with shaders
				vDirectXInstance.iD3D11DeviceContext4->Draw(vertexVerticesCount, 0);
			}

			//Pixel shader (Pass Capture 2)
			{
				//Set view port
				vDirectXInstance.iD3D11DeviceContext4->RSSetViewports(1, &vDirectXInstance.iD3D11ViewPortFull);

				//Set render target view
				vDirectXInstance.iD3D11DeviceContext4->OMSetRenderTargets(1, &vDirectXInstance.iD3D11RenderTargetView0PassCapture2, NULL);

				//Set shader resource view
				vDirectXInstance.iD3D11DeviceContext4->PSSetShaderResources(0, 1, &vDirectXInstance.iD3D11ShaderResourceView0PassCapture2);

				//Set pixel shader pass
				vDirectXInstance.iD3D11DeviceContext4->PSSetShader(vDirectXInstance.iD3D11ShaderPixel0PassCapture2, NULL, 0);

				//Draw texture with shaders
				vDirectXInstance.iD3D11DeviceContext4->Draw(vertexVerticesCount, 0);
			}

			//Pixel shader (Pass Output 1)
			if (vDirectXInstance.TextureFormatOutput == DXGI_FORMAT_NV12 || vDirectXInstance.TextureFormatOutput == DXGI_FORMAT_P010)
			{
				//Convert Luma Chroma YCbCr

				//Set view port (Luma Y)
				vDirectXInstance.iD3D11DeviceContext4->RSSetViewports(1, &vDirectXInstance.iD3D11ViewPortFull);

				//Set render target view
				vDirectXInstance.iD3D11DeviceContext4->OMSetRenderTargets(1, &vDirectXInstance.iD3D11RenderTargetView0PassOutput1, NULL);

				//Set shader resource view
				vDirectXInstance.iD3D11DeviceContext4->PSSetShaderResources(0, 1, &vDirectXInstance.iD3D11ShaderResourceView0PassOutput1);

				//Set pixel shader pass
				vDirectXInstance.iD3D11DeviceContext4->PSSetShader(vDirectXInstance.iD3D11ShaderPixel0PassOutput1, NULL, 0);

				//Draw texture with shaders
				vDirectXInstance.iD3D11DeviceContext4->Draw(vertexVerticesCount, 0);

				//Set view port (Chroma CbCr)
				vDirectXInstance.iD3D11DeviceContext4->RSSetViewports(1, &vDirectXInstance.iD3D11ViewPortHalf);

				//Set render target view
				vDirectXInstance.iD3D11DeviceContext4->OMSetRenderTargets(1, &vDirectXInstance.iD3D11RenderTargetView0PassOutput2, NULL);

				//Set shader resource view
				vDirectXInstance.iD3D11DeviceContext4->PSSetShaderResources(0, 1, &vDirectXInstance.iD3D11ShaderResourceView0PassOutput1);

				//Set pixel shader pass
				vDirectXInstance.iD3D11DeviceContext4->PSSetShader(vDirectXInstance.iD3D11ShaderPixel0PassOutput2, NULL, 0);

				//Draw texture with shaders
				vDirectXInstance.iD3D11DeviceContext4->Draw(vertexVerticesCount, 0);
			}
			else
			{
				//Set view port
				vDirectXInstance.iD3D11DeviceContext4->RSSetViewports(1, &vDirectXInstance.iD3D11ViewPortFull);

				//Set render target view
				vDirectXInstance.iD3D11DeviceContext4->OMSetRenderTargets(1, &vDirectXInstance.iD3D11RenderTargetView0PassOutput1, NULL);

				//Set shader resource view
				vDirectXInstance.iD3D11DeviceContext4->PSSetShaderResources(0, 1, &vDirectXInstance.iD3D11ShaderResourceView0PassOutput1);

				//Set pixel shader pass
				vDirectXInstance.iD3D11DeviceContext4->PSSetShader(vDirectXInstance.iD3D11ShaderPixel0PassOutput1, NULL, 0);

				//Draw texture with shaders
				vDirectXInstance.iD3D11DeviceContext4->Draw(vertexVerticesCount, 0);
			}

			//Return result
			return { .Status = CaptureStatus::Success };
		}
		catch (...)
		{
			//Return result
			return { .Status = CaptureStatus::Failed, .Message = SysAllocString(L"RenderDrawTexture2D failed") };
		}
	}
}