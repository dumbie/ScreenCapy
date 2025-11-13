using ArnoldVinkCode;
using ScreenCaptureImport;
using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using static ArnoldVinkCode.AVInteropDll;
using static ArnoldVinkCode.AVProcess;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    public partial class CaptureScreen
    {
        public static async Task CaptureImageProcess(int captureDelay)
        {
            try
            {
                //Capture start stop delay
                await Task.Delay(captureDelay);

                //Check active video capture
                if (!CaptureImport.CaptureVideoIsRecording())
                {
                    Debug.WriteLine("Starting image capture process.");
                    Process startProcess = new Process();
                    startProcess.StartInfo.FileName = "ScreenCapy.exe";
                    startProcess.StartInfo.Arguments = "-image";
                    startProcess.Start();
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Screen image capture process start failed: " + ex.Message);
            }
        }

        public static CaptureResult CaptureImageToFile()
        {
            try
            {
                //Capture settings
                ImageFormats ScreenshotSaveFormat = (ImageFormats)vSettings.Load("ScreenshotSaveFormat", typeof(int));
                int ScreenshotSaveQuality = vSettings.Load("ScreenshotSaveQuality", typeof(int));
                int ScreenshotMaxPixelDimension = vSettings.Load("ScreenshotMaxPixelDimension", typeof(int));
                int CaptureMonitorId = vSettings.Load("CaptureMonitorId", typeof(int)) - 1;
                bool CaptureSoundEffect = vSettings.Load("CaptureSoundEffect", typeof(bool));
                bool CaptureDrawBorder = vSettings.Load("CaptureDrawBorder", typeof(bool));
                bool CaptureDrawMouseCursor = vSettings.Load("CaptureDrawMouseCursor", typeof(bool));

                //Screen capture settings
                CaptureSettings captureSettings = new CaptureSettings();
                captureSettings.MonitorId = CaptureMonitorId;
                captureSettings.MaxPixelDimension = ScreenshotMaxPixelDimension;
                captureSettings.SoundEffect = CaptureSoundEffect;
                captureSettings.DrawBorder = CaptureDrawBorder;
                captureSettings.DrawMouseCursor = CaptureDrawMouseCursor;

                //Check HDR to SDR setting
                if (ScreenshotSaveFormat == ImageFormats.JPG || ScreenshotSaveFormat == ImageFormats.PNG || ScreenshotSaveFormat == ImageFormats.BMP || ScreenshotSaveFormat == ImageFormats.TIF || ScreenshotSaveFormat == ImageFormats.HEIF)
                {
                    captureSettings.HDRtoSDR = true;
                }

                //Initialize screen capture
                CaptureResult captureResult = CaptureImport.CaptureInitialize(captureSettings, true);
                Debug.WriteLine("Capture initialize result: " + captureResult.Status + " / " + captureResult.ResultCode + " / " + captureResult.Message);
                if (captureResult.Status == CaptureStatus.Success)
                {
                    vCaptureDetails = CaptureImport.CaptureGetDetails();
                }
                else
                {
                    return captureResult;
                }

                //Set save name
                string fileSaveName = "Screenshot";
                if (vSettings.Load("SaveWindowTitle", typeof(bool)))
                {
                    fileSaveName = Detail_WindowTitleByWindowHandle(GetForegroundWindow());
                    fileSaveName = AVFunctions.StringCut(fileSaveName, 150, string.Empty);
                }

                //Set save date
                string fileSaveDate = " (" + DateTime.Now.ToShortDateString() + ") " + DateTime.Now.ToString("HH.mm.ss.ffff");

                //Set save details
                string fileSaveDetails = string.Empty;
                if (vCaptureDetails.HDREnabled)
                {
                    if (vCaptureDetails.HDRtoSDR)
                    {
                        fileSaveDetails = " (HDRtoSDR)";
                    }
                    else
                    {
                        fileSaveDetails = " (HDR)";
                    }
                }
                else
                {
                    fileSaveDetails = " (SDR)";
                }

                //Replace invalid characters
                vCaptureFileName = AVFiles.FileNameReplaceInvalidChars(fileSaveName + fileSaveDate + fileSaveDetails, "-");

                //Check capture location
                string fileSaveFolder = vSettings.Load("CaptureLocation", typeof(string));
                if (string.IsNullOrWhiteSpace(fileSaveFolder) || !Directory.Exists(fileSaveFolder))
                {
                    //Check captures folder in app directory
                    if (!Directory.Exists("Captures"))
                    {
                        Directory.CreateDirectory("Captures");
                    }

                    //Set save folder to captures in app directory
                    fileSaveFolder = "Captures";
                }

                //Combine save path
                string fileSavePath = fileSaveFolder + "\\" + vCaptureFileName;

                //Set file extension
                string fileExtension = string.Empty;
                if (ScreenshotSaveFormat == ImageFormats.JPG)
                {
                    fileExtension = ".jpg";
                }
                else if (ScreenshotSaveFormat == ImageFormats.PNG)
                {
                    fileExtension = ".png";
                }
                else if (ScreenshotSaveFormat == ImageFormats.BMP)
                {
                    fileExtension = ".bmp";
                }
                else if (ScreenshotSaveFormat == ImageFormats.TIF)
                {
                    fileExtension = ".tif";
                }
                else if (ScreenshotSaveFormat == ImageFormats.HEIF)
                {
                    fileExtension = ".heif";
                }
                else
                {
                    fileExtension = ".jxr";
                }

                //Save screenshot to file
                CaptureResult imageResult = CaptureImport.CaptureImage(fileSavePath + fileExtension, ScreenshotSaveQuality, ScreenshotSaveFormat);
                Debug.WriteLine("Capture " + ScreenshotSaveFormat + " image result: " + imageResult.Status + " / " + imageResult.Message);
                return imageResult;
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Screen image capture failed: " + ex.Message);
                return new CaptureResult() { Status = CaptureStatus.Failed, Message = "Failed: " + ex.Message };
            }
        }
    }
}