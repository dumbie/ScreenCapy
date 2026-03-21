#pragma once
#include "CaptureVariables.h"

namespace
{
	BOOL CodecCheckVideoEncoder(GUID subType)
	{
		try
		{
			//Get video encoders
			UINT32 numMFTActivate = 0;
			auto pppMFTActivate = AVFin<IMFActivate**>(AVFinMethod::Custom);
			pppMFTActivate.SetReleaser([&](auto releasePointer)
				{
					for (int i = 0; i < numMFTActivate; i++)
					{
						releasePointer[i]->Release();
					}
					CoTaskMemFree(releasePointer);
				});
			MFT_REGISTER_TYPE_INFO mftRegisterTypeInfo = { MFMediaType_Video, subType };
			hResult = MFTEnumEx(MFT_CATEGORY_VIDEO_ENCODER, MFT_ENUM_FLAG_HARDWARE, NULL, &mftRegisterTypeInfo, &pppMFTActivate.Get(), &numMFTActivate);

			//Check result
			if (SUCCEEDED(hResult) && numMFTActivate > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		catch (...)
		{
			AVDebugWriteLine("CodecCheckVideoEncoder failed.");
			return false;
		}
	}
}