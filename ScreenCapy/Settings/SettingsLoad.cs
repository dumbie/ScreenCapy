using ArnoldVinkCode;
using System;
using System.Diagnostics;
using System.Linq;
using static ArnoldVinkCode.AVClasses;
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
                checkbox_CaptureSoundEffect.IsChecked = vSettings.Load("CaptureSoundEffect", typeof(bool));
                checkbox_CaptureDrawBorder.IsChecked = vSettings.Load("CaptureDrawBorder", typeof(bool));
                checkbox_CaptureDrawMouseCursor.IsChecked = vSettings.Load("CaptureDrawMouseCursor", typeof(bool));

                textblock_CaptureMonitorId.Text = textblock_CaptureMonitorId.Tag + vSettings.Load("CaptureMonitorId", typeof(string));
                slider_CaptureMonitorId.Value = vSettings.Load("CaptureMonitorId", typeof(double));

                //Saving
                checkbox_SaveWindowTitle.IsChecked = vSettings.Load("SaveWindowTitle", typeof(bool));
                textblock_CaptureLocation.Text = textblock_CaptureLocation.Tag + vSettings.Load("CaptureLocation", typeof(string));

                //Screenshot
                combobox_ScreenshotSaveFormat.SelectedIndex = vSettings.Load("ScreenshotSaveFormat", typeof(int));

                textblock_ScreenshotSaveQuality.Text = textblock_ScreenshotSaveQuality.Tag + vSettings.Load("ScreenshotSaveQuality", typeof(string)) + "%";
                slider_ScreenshotSaveQuality.Value = vSettings.Load("ScreenshotSaveQuality", typeof(double));

                textblock_ScreenshotMaxPixelDimension.Text = textblock_ScreenshotMaxPixelDimension.Tag + vSettings.Load("ScreenshotMaxPixelDimension", typeof(string)) + " px";
                slider_ScreenshotMaxPixelDimension.Value = vSettings.Load("ScreenshotMaxPixelDimension", typeof(double));

                //Recording
                combobox_VideoSaveFormat.SelectedIndex = vSettings.Load("VideoSaveFormat", typeof(int));

                int VideoFrameRate = vSettings.Load("VideoFrameRate", typeof(int));
                textblock_VideoFrameRate.Text = textblock_VideoFrameRate.Tag + VideoFrameRate.ToString() + " fps";
                slider_VideoFrameRate.Value = VideoFrameRate;

                combobox_VideoRateControl.SelectedIndex = vSettings.Load("VideoRateControl", typeof(int));

                textblock_VideoBitRate.Text = textblock_VideoBitRate.Tag + vSettings.Load("VideoBitRate", typeof(string)) + " Kbps";
                slider_VideoBitRate.Value = vSettings.Load("VideoBitRate", typeof(double));

                textblock_VideoMaxPixelDimension.Text = textblock_VideoMaxPixelDimension.Tag + vSettings.Load("VideoMaxPixelDimension", typeof(string)) + " px";
                slider_VideoMaxPixelDimension.Value = vSettings.Load("VideoMaxPixelDimension", typeof(double));

                combobox_AudioSaveFormat.SelectedIndex = vSettings.Load("AudioSaveFormat", typeof(int));

                int AudioChannels = vSettings.Load("AudioChannels", typeof(int));
                combobox_AudioChannels.SelectedItem = combobox_AudioChannels.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioChannels.ToString());

                textblock_AudioBitRate.Text = textblock_AudioBitRate.Tag + vSettings.Load("AudioBitRate", typeof(string)) + " kbps";
                slider_AudioBitRate.Value = vSettings.Load("AudioBitRate", typeof(double));

                int AudioBitDepth = vSettings.Load("AudioBitDepth", typeof(int));
                combobox_AudioBitDepth.SelectedItem = combobox_AudioBitDepth.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioBitDepth.ToString());

                int AudioSampleRate = vSettings.Load("AudioSampleRate", typeof(int));
                combobox_AudioSampleRate.SelectedItem = combobox_AudioSampleRate.Items.Cast<ComboBoxItemValue>().FirstOrDefault(x => x.Value == AudioSampleRate.ToString());

                //Overlay
                checkbox_OverlayShowScreenshot.IsChecked = vSettings.Load("OverlayShowScreenshot", typeof(bool));
                checkbox_OverlayShowRecording.IsChecked = vSettings.Load("OverlayShowRecording", typeof(bool));

                string OverlayPosition = vSettings.Load("OverlayPosition", typeof(string));
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