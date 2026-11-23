#pragma once
#include "pch.h"

namespace
{
	//Enumerators
	enum class CaptureStatus
	{
		Success = 0,
		Failed = 1,
		Busy = 2
	};

	enum class CaptureTypes
	{
		None = 0,
		Failed = 1,
		Image = 2,
		Video = 3
	};

	enum class ImageFormats
	{
		JXR = 0,
		JPG = 1,
		PNG = 2,
		BMP = 3,
		TIF = 4,
		HEIF = 5
	};

	enum class VideoRateControls
	{
		VBR = 0,
		CBR = 1
	};

	enum class VideoFormats
	{
		H264 = 0,
		HEVC = 1,
		AV1 = 2
	};

	enum class AudioFormats
	{
		MP3 = 0,
		AAC = 1,
		FLAC = 2
	};

	enum class TextureFilters
	{
		Nearest = 0,
		Bilinear = 1
	};

	//Structures
	struct MediaSettings
	{
		AudioFormats AudioFormat = AudioFormats::AAC;
		UINT AudioChannels = 2;
		UINT AudioBitRate = 192;
		UINT AudioBitDepth = 16;
		UINT AudioSampleRate = 48000;
		VideoFormats VideoFormat = VideoFormats::H264;
		VideoRateControls VideoRateControl = VideoRateControls::VBR;
		UINT VideoBitRate = 35000;
		UINT VideoFrameRate = 60;
	};

	struct CaptureSettings
	{
		CaptureTypes CaptureType = CaptureTypes::Image;
		UINT MonitorId = 0;
		UINT MaxPixelDimension = 0;
		BOOL SoundEffect = true;
		BOOL DrawBorder = false;
		BOOL DrawMouseCursor = true;
		BOOL HDRtoSDR = false;
		FLOAT HDRPaperWhite = 80.0F;
		FLOAT HDRBrightness = 2.0F;
		FLOAT Saturation = 1.0F;
		FLOAT RedChannel = 1.0F;
		FLOAT GreenChannel = 1.0F;
		FLOAT BlueChannel = 1.0F;
		FLOAT Brightness = 1.0F;
		FLOAT Contrast = 0.0F;
		FLOAT Gamma = 1.0F;
		FLOAT Blur = 0.0F;
		FLOAT Sharpness = 0.0F;
		TextureFilters TextureFilter = TextureFilters::Bilinear;
	};

	struct CaptureDetails
	{
		UINT OriginalWidth;
		UINT OriginalHeight;
		UINT OriginalRefreshRate;
		UINT MediaWidth;
		UINT MediaHeight;
		UINT MediaRowCount;
		UINT MediaRowByteSize;
		UINT MediaPixelByteSize;
		UINT MediaTotalByteSize;
		UINT MediaTextureFormat;
		BOOL HDREnabled;
		BOOL HDRtoSDR;
		FLOAT SDRWhiteLevel;
	};

	struct ShaderVariables
	{
		int TextureFilter;
		int TextureFormat;
		BOOL HDRtoSDR;
		FLOAT HDRPaperWhite;
		FLOAT HDRBrightness;
		FLOAT SDRWhiteLevel;
		FLOAT Saturation;
		FLOAT RedChannel;
		FLOAT GreenChannel;
		FLOAT BlueChannel;
		FLOAT Brightness;
		FLOAT Contrast;
		FLOAT Gamma;
		FLOAT Blur;
		FLOAT Sharpness;
		FLOAT Unused1;
	};

	struct WgcInstance
	{
		//Frame
		winrt::Windows::Graphics::SizeInt32 vFrameSizeCurrent = { 0 ,0 };
		winrt::Windows::Graphics::DirectX::DirectXPixelFormat vFramePixelFormat = winrt::Windows::Graphics::DirectX::DirectXPixelFormat::Unknown;

		//Direct3D
		winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice vGraphicsD3D11Device = NULL;

		//Capture
		winrt::Windows::Graphics::Capture::GraphicsCaptureItem vGraphicsCaptureItem = NULL;
		winrt::Windows::Graphics::Capture::GraphicsCaptureSession vGraphicsCaptureSession = NULL;
		winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool vGraphicsCaptureFramePool = NULL;
	};

	struct DirectXInstance
	{
		//Information
		DXGI_OUTPUT_DESC1 iDxgiOutputDescription1;

		//Texture
		BOOL TextureResizing;
		UINT TextureWidthCapture;
		UINT TextureHeightCapture;
		DXGI_FORMAT TextureFormatCapture;
		UINT TextureWidthOutput;
		UINT TextureHeightOutput;
		DXGI_FORMAT TextureFormatOutput;

		//Direct3D
		CComPtr<IDXGIDevice4> iDxgiDevice4;
		CComPtr<IDXGIAdapter4> iDxgiAdapter4;
		CComPtr<IDXGIFactory7> iDxgiFactory7;
		CComPtr<IDXGIOutput6> iDxgiOutput6;
		CComPtr<ID3D11Device5> iD3D11Device5;
		CComPtr<ID3D11Multithread> iD3D11Multithread0;
		CComPtr<ID3D11DeviceContext4> iD3D11DeviceContext4;

		//States
		CComPtr<ID3D11SamplerState> iD3D11SamplerState0;

		//Views
		D3D11_VIEWPORT iD3D11ViewPortPass1;
		D3D11_VIEWPORT iD3D11ViewPortPass2;
		D3D11_VIEWPORT iD3D11ViewPortPassOut;
		CComPtr<ID3D11InputLayout> iD3D11InputLayout0;
		CComPtr<ID3D11RenderTargetView> iD3D11RenderTargetView0Pass1;
		CComPtr<ID3D11RenderTargetView> iD3D11RenderTargetView0Pass2;
		CComPtr<ID3D11RenderTargetView> iD3D11RenderTargetView0PassOut;
		CComPtr<ID3D11ShaderResourceView> iD3D11ShaderResourceView0Pass1;
		CComPtr<ID3D11ShaderResourceView> iD3D11ShaderResourceView0Pass2;
		CComPtr<ID3D11ShaderResourceView> iD3D11ShaderResourceView0PassOut;

		//Shaders
		CComPtr<ID3D11Buffer> iD3D11BufferVertex0;
		CComPtr<ID3D11Buffer> iD3D11BufferPixel0;
		CComPtr<ID3DBlob> iD3DBlobShaderVertex0;
		CComPtr<ID3DBlob> iD3DBlobShaderPixel0Pass1;
		CComPtr<ID3DBlob> iD3DBlobShaderPixel0Pass2;
		CComPtr<ID3DBlob> iD3DBlobShaderPixel0PassOut;
		CComPtr<ID3D11VertexShader> iD3D11ShaderVertex0;
		CComPtr<ID3D11PixelShader> iD3D11ShaderPixel0Pass1;
		CComPtr<ID3D11PixelShader> iD3D11ShaderPixel0Pass2;
		CComPtr<ID3D11PixelShader> iD3D11ShaderPixel0PassOut;

		//Textures
		CComPtr<ID3D11Texture2D> iD3D11Texture2D0CpuRead;
		CComPtr<ID3D11Texture2D> iD3D11Texture2D0ScreenCapture;
		CComPtr<ID3D11Texture2D> iD3D11Texture2D0RenderTargetViewPass1;
		CComPtr<ID3D11Texture2D> iD3D11Texture2D0RenderTargetViewPass2;
		CComPtr<ID3D11Texture2D> iD3D11Texture2D0RenderTargetViewPassOut;
	};

	struct BitmapImageInstance
	{
		//Bitmap image
		WICPixelFormatGUID iWicPixelFormatGuidSource = GUID_WICPixelFormatDontCare;
		WICPixelFormatGUID iWicPixelFormatGuidJpeg = GUID_WICPixelFormat24bppBGR;
		CComPtr<IPropertyBag2> iPropertyBag2;
		CComPtr<IWICImagingFactory> iWICImagingFactory;
		CComPtr<IWICStream> iWICStream;
		CComPtr<IWICBitmapEncoder> iWICBitmapEncoder;
		CComPtr<IWICBitmapFrameEncode> iWICBitmapFrameEncode;
		CComPtr<IWICMetadataQueryWriter> iWICMetadataQueryWriter;
		CComPtr<IWICFormatConverter> iWICFormatConverter;
		CComPtr<IWICBitmap> iWICBitmap;
	};

	struct MediaFoundationInstance
	{
		//Media foundation
		CComPtr<IMFSinkWriterEx> imfSinkWriter;
		CComPtr<IMFDXGIDeviceManager> imfDXGIDeviceManager;
		BOOL vMediaCapturing;
		BOOL vMediaWriteLoopAllowed;
		BOOL vMediaWriteLoopFinishedScreen;
		BOOL vMediaWriteLoopFinishedAudio;
		DWORD vImfSinkWriterIndex = 0;
		DWORD vOutVideoStreamIndex = 0;
		DWORD vOutAudioStreamIndex = 0;
		ULONGLONG vMediaTimeStartLoop = 0;

		//Device audio
		CComPtr<IMMDevice> iDevice;
		CComPtr<IAudioClient3> iAudioDeviceCapture;
		CComPtr<IAudioClient3> iAudioDeviceRender;
		CComPtr<IAudioCaptureClient> iAudioClientCapture;
		CComPtr<IAudioRenderClient> iAudioClientRender;
		WAVEFORMATEXTENSIBLE iAudioWaveFormatExCapture;
		CComHeapPtr<WAVEFORMATEXTENSIBLE> iAudioWaveFormatExRender;
	};

	struct VertexVertice
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 TexCoord;
	};

	struct CaptureDataScreen
	{
		//Status
		BOOL Cached;

		//Bytes
		std::vector<BYTE> ScreenBytes;
	};

	struct CaptureDataAudio
	{
		//Status
		BOOL Silent;
		BOOL TimestampError;
		BOOL DataDiscontinuity;

		//Bytes
		std::vector<BYTE> AudioBytes;
	};

	struct CaptureInstance
	{
		//Status
		BOOL vInstanceInitialized;
		BOOL vInstanceInitializing;
		BOOL vCaptureStatusLoopAllowed;
		BOOL vCaptureStatusLoopFinished;

		//Bytes
		CaptureDataScreen vCaptureDataScreenCache;
	};

	struct CaptureResult
	{
		//Status
		CaptureStatus Status;

		//Result Code
		LONG ResultCode;

		//Message
		BSTR Message;
	};
};