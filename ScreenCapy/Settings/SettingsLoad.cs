using ArnoldVinkCode;
using System;
using System.Diagnostics;
using System.Linq;
using static ArnoldVinkCode.AVClasses;
using static ArnoldVinkCode.AVSettings;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    partial class WindowMain
    {
        //Load - Application Settings
        public void Settings_Load()
        {
            try
            {
                //ComboBox
                Load_ComboBox_Items();

                //General
                checkbox_CaptureSoundEffect.IsChecked = SettingLoad(vConfigurationScreenCapy, "CaptureSoundEffect", typeof(bool));
                checkbox_CaptureDrawBorder.IsChecked = SettingLoad(vConfigurationScreenCapy, "CaptureDrawBorder", typeof(bool));
                checkbox_CaptureDrawMouseCursor.IsChecked = SettingLoad(vConfigurationScreenCapy, "CaptureDrawMouseCursor", typeof(bool));

                textblock_CaptureMonitorId.Text = textblock_CaptureMonitorId.Tag + SettingLoad(vConfigurationScreenCapy, "CaptureMonitorId", typeof(string));
                slider_CaptureMonitorId.Value = SettingLoad(vConfigurationScreenCapy, "CaptureMonitorId", typeof(double));

                //Saving
                checkbox_SaveWindowTitle.IsChecked = SettingLoad(vConfigurationScreenCapy, "SaveWindowTitle", typeof(bool));
                textblock_CaptureLocation.Text = textblock_CaptureLocation.Tag + SettingLoad(vConfigurationScreenCapy, "CaptureLocation", typeof(string));

                //Screenshot
                combobox_ScreenshotSaveFormat.SelectedIndex = SettingLoad(vConfigurationScreenCapy, "ScreenshotSaveFormat", typeof(int));

                textblock_ScreenshotSaveQuality.Text = textblock_ScreenshotSaveQuality.Tag + SettingLoad(vConfigurationScreenCapy, "ScreenshotSaveQuality", typeof(string)) + "%";
                slider_ScreenshotSaveQuality.Value = SettingLoad(vConfigurationScreenCapy, "ScreenshotSaveQuality", typeof(double));

                textblock_ScreenshotMaxPixelDimension.Text = textblock_ScreenshotMaxPixelDimension.Tag + SettingLoad(vConfigurationScreenCapy, "ScreenshotMaxPixelDimension", typeof(string)) + " px";
                slider_ScreenshotMaxPixelDimension.Value = SettingLoad(vConfigurationScreenCapy, "ScreenshotMaxPixelDimension", typeof(double));

                //Recording
                combobox_VideoSaveFormat.SelectedIndex = SettingLoad(vConfigurationScreenCapy, "VideoSaveFormat", typeof(int));

                int VideoFrameRate = SettingLoad(vConfigurationScreenCapy, "VideoFrameRate", typeof(int));
                textblock_VideoFrameRate.Text = textblock_VideoFrameRate.Tag + VideoFrameRate.ToString() + " fps";
                slider_VideoFrameRate.Value = VideoFrameRate;

                combobox_VideoRateControl.SelectedIndex = SettingLoad(vConfigurationScreenCapy, "VideoRateControl", typeof(int));

                textblock_VideoBitRate.Text = textblock_VideoBitRate.Tag + SettingLoad(vConfigurationScreenCapy, "VideoBitRate", typeof(string)) + " Kbps";
                slider_VideoBitRate.Value = SettingLoad(vConfigurationScreenCapy, "VideoBitRate", typeof(double));

                textblock_VideoMaxPixelDimension.Text = textblock_VideoMaxPixelDimension.Tag + SettingLoad(vConfigurationScreenCapy, "VideoMaxPixelDimension", typeof(string)) + " px";
                slider_VideoMaxPixelDimension.Value = SettingLoad(vConfigurationScreenCapy, "VideoMaxPixelDimension", typeof(double));

                combobox_AudioSaveFormat.SelectedIndex = SettingLoad(vConfigurationScreenCapy, "AudioSaveFormat", typeof(int));

                int AudioChannels = SettingLoad(vConfigurationScreenCapy, "AudioChannels", typeof(int));
                combobox_AudioChannels.SelectedItem = combobox_AudioChannels.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioChannels.ToString());

                textblock_AudioBitRate.Text = textblock_AudioBitRate.Tag + SettingLoad(vConfigurationScreenCapy, "AudioBitRate", typeof(string)) + " kbps";
                slider_AudioBitRate.Value = SettingLoad(vConfigurationScreenCapy, "AudioBitRate", typeof(double));

                int AudioBitDepth = SettingLoad(vConfigurationScreenCapy, "AudioBitDepth", typeof(int));
                combobox_AudioBitDepth.SelectedItem = combobox_AudioBitDepth.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioBitDepth.ToString());

                int AudioSampleRate = SettingLoad(vConfigurationScreenCapy, "AudioSampleRate", typeof(int));
                combobox_AudioSampleRate.SelectedItem = combobox_AudioSampleRate.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioSampleRate.ToString());

                //Overlay
                checkbox_OverlayShowScreenshot.IsChecked = SettingLoad(vConfigurationScreenCapy, "OverlayShowScreenshot", typeof(bool));
                checkbox_OverlayShowRecording.IsChecked = SettingLoad(vConfigurationScreenCapy, "OverlayShowRecording", typeof(bool));

                string OverlayPosition = SettingLoad(vConfigurationScreenCapy, "OverlayPosition", typeof(string));
                combobox_OverlayPosition.SelectedItem = combobox_OverlayPosition.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == OverlayPosition.ToString());

                //Launch on Windows startup
                checkbox_WindowsStartup.IsChecked = AVSettings.StartupShortcutCheck();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to load application settings: " + ex.Message);
            }
        }
    }
}