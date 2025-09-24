using System;
using System.Diagnostics;
using static ArnoldVinkCode.AVSettings;
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
                if (!SettingCheck(vConfigurationScreenCapy, "AppFirstLaunch")) { SettingSave(vConfigurationScreenCapy, "AppFirstLaunch", "True"); }

                //Server settings
                if (!SettingCheck(vConfigurationScreenCapy, "ServerPort")) { SettingSave(vConfigurationScreenCapy, "ServerPort", "26762"); }

                //General
                if (!SettingCheck(vConfigurationScreenCapy, "CaptureSoundEffect")) { SettingSave(vConfigurationScreenCapy, "CaptureSoundEffect", "True"); }
                if (!SettingCheck(vConfigurationScreenCapy, "CaptureMonitorId")) { SettingSave(vConfigurationScreenCapy, "CaptureMonitorId", "1"); }
                if (!SettingCheck(vConfigurationScreenCapy, "CaptureDrawBorder")) { SettingSave(vConfigurationScreenCapy, "CaptureDrawBorder", "False"); }
                if (!SettingCheck(vConfigurationScreenCapy, "CaptureDrawMouseCursor")) { SettingSave(vConfigurationScreenCapy, "CaptureDrawMouseCursor", "True"); }

                //Saving
                if (!SettingCheck(vConfigurationScreenCapy, "SaveWindowTitle")) { SettingSave(vConfigurationScreenCapy, "SaveWindowTitle", "True"); }
                if (!SettingCheck(vConfigurationScreenCapy, "CaptureLocation")) { SettingSave(vConfigurationScreenCapy, "CaptureLocation", "Captures"); }

                //Screenshot
                if (!SettingCheck(vConfigurationScreenCapy, "ScreenshotSaveFormat")) { SettingSave(vConfigurationScreenCapy, "ScreenshotSaveFormat", "0"); }
                if (!SettingCheck(vConfigurationScreenCapy, "ScreenshotSaveQuality")) { SettingSave(vConfigurationScreenCapy, "ScreenshotSaveQuality", "80"); }
                if (!SettingCheck(vConfigurationScreenCapy, "ScreenshotMaxPixelDimension")) { SettingSave(vConfigurationScreenCapy, "ScreenshotMaxPixelDimension", "4320"); }

                //Recording
                if (!SettingCheck(vConfigurationScreenCapy, "VideoSaveFormat")) { SettingSave(vConfigurationScreenCapy, "VideoSaveFormat", "0"); }
                if (!SettingCheck(vConfigurationScreenCapy, "VideoFrameRate")) { SettingSave(vConfigurationScreenCapy, "VideoFrameRate", "60"); }
                if (!SettingCheck(vConfigurationScreenCapy, "VideoRateControl")) { SettingSave(vConfigurationScreenCapy, "VideoRateControl", "0"); }
                if (!SettingCheck(vConfigurationScreenCapy, "VideoBitRate")) { SettingSave(vConfigurationScreenCapy, "VideoBitRate", "35000"); }
                if (!SettingCheck(vConfigurationScreenCapy, "VideoMaxPixelDimension")) { SettingSave(vConfigurationScreenCapy, "VideoMaxPixelDimension", "1440"); }
                if (!SettingCheck(vConfigurationScreenCapy, "AudioSaveFormat")) { SettingSave(vConfigurationScreenCapy, "AudioSaveFormat", "1"); }
                if (!SettingCheck(vConfigurationScreenCapy, "AudioChannels")) { SettingSave(vConfigurationScreenCapy, "AudioChannels", "2"); }
                if (!SettingCheck(vConfigurationScreenCapy, "AudioBitRate")) { SettingSave(vConfigurationScreenCapy, "AudioBitRate", "192"); }
                if (!SettingCheck(vConfigurationScreenCapy, "AudioBitDepth")) { SettingSave(vConfigurationScreenCapy, "AudioBitDepth", "16"); }
                if (!SettingCheck(vConfigurationScreenCapy, "AudioSampleRate")) { SettingSave(vConfigurationScreenCapy, "AudioSampleRate", "48000"); }

                //Overlay
                if (!SettingCheck(vConfigurationScreenCapy, "OverlayShowScreenshot")) { SettingSave(vConfigurationScreenCapy, "OverlayShowScreenshot", "True"); }
                if (!SettingCheck(vConfigurationScreenCapy, "OverlayShowRecording")) { SettingSave(vConfigurationScreenCapy, "OverlayShowRecording", "True"); }
                if (!SettingCheck(vConfigurationScreenCapy, "OverlayPosition")) { SettingSave(vConfigurationScreenCapy, "OverlayPosition", "BottomCenter"); }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to check the application settings: " + ex.Message);
            }
        }
    }
}