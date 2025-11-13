using System;
using System.Diagnostics;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    public partial class WindowMain
    {
        //Check - Application Settings
        public void Settings_Check()
        {
            try
            {
                //First Launch
                if (!vSettings.Check("AppFirstLaunch")) { vSettings.Set("AppFirstLaunch", "True"); }

                //Server settings
                if (!vSettings.Check("ServerPort")) { vSettings.Set("ServerPort", "26762"); }

                //General
                if (!vSettings.Check("CaptureSoundEffect")) { vSettings.Set("CaptureSoundEffect", "True"); }
                if (!vSettings.Check("CaptureMonitorId")) { vSettings.Set("CaptureMonitorId", "1"); }
                if (!vSettings.Check("CaptureDrawBorder")) { vSettings.Set("CaptureDrawBorder", "False"); }
                if (!vSettings.Check("CaptureDrawMouseCursor")) { vSettings.Set("CaptureDrawMouseCursor", "True"); }

                //Saving
                if (!vSettings.Check("SaveWindowTitle")) { vSettings.Set("SaveWindowTitle", "True"); }
                if (!vSettings.Check("CaptureLocation")) { vSettings.Set("CaptureLocation", "Captures"); }

                //Screenshot
                if (!vSettings.Check("ScreenshotSaveFormat")) { vSettings.Set("ScreenshotSaveFormat", "0"); }
                if (!vSettings.Check("ScreenshotSaveQuality")) { vSettings.Set("ScreenshotSaveQuality", "80"); }
                if (!vSettings.Check("ScreenshotMaxPixelDimension")) { vSettings.Set("ScreenshotMaxPixelDimension", "4320"); }

                //Recording
                if (!vSettings.Check("VideoSaveFormat")) { vSettings.Set("VideoSaveFormat", "0"); }
                if (!vSettings.Check("VideoFrameRate")) { vSettings.Set("VideoFrameRate", "60"); }
                if (!vSettings.Check("VideoRateControl")) { vSettings.Set("VideoRateControl", "0"); }
                if (!vSettings.Check("VideoBitRate")) { vSettings.Set("VideoBitRate", "35000"); }
                if (!vSettings.Check("VideoMaxPixelDimension")) { vSettings.Set("VideoMaxPixelDimension", "1440"); }
                if (!vSettings.Check("AudioSaveFormat")) { vSettings.Set("AudioSaveFormat", "1"); }
                if (!vSettings.Check("AudioChannels")) { vSettings.Set("AudioChannels", "2"); }
                if (!vSettings.Check("AudioBitRate")) { vSettings.Set("AudioBitRate", "192"); }
                if (!vSettings.Check("AudioBitDepth")) { vSettings.Set("AudioBitDepth", "16"); }
                if (!vSettings.Check("AudioSampleRate")) { vSettings.Set("AudioSampleRate", "48000"); }

                //Overlay
                if (!vSettings.Check("OverlayShowScreenshot")) { vSettings.Set("OverlayShowScreenshot", "True"); }
                if (!vSettings.Check("OverlayShowRecording")) { vSettings.Set("OverlayShowRecording", "True"); }
                if (!vSettings.Check("OverlayPosition")) { vSettings.Set("OverlayPosition", "BottomCenter"); }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to check the application settings: " + ex.Message);
            }
        }
    }
}