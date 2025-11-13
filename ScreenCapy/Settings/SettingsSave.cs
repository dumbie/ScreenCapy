using ArnoldVinkCode;
using System;
using System.Diagnostics;
using static ArnoldVinkCode.AVClasses;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    partial class WindowMain
    {
        //Save - Application Settings
        public void Settings_Save()
        {
            try
            {
                //General
                checkbox_CaptureSoundEffect.Click += (sender, e) =>
                {
                    vSettings.Set("CaptureSoundEffect", checkbox_CaptureSoundEffect.IsChecked);
                };

                checkbox_CaptureDrawBorder.Click += (sender, e) =>
                {
                    vSettings.Set("CaptureDrawBorder", checkbox_CaptureDrawBorder.IsChecked);
                };

                checkbox_CaptureDrawMouseCursor.Click += (sender, e) =>
                {
                    vSettings.Set("CaptureDrawMouseCursor", checkbox_CaptureDrawMouseCursor.IsChecked);
                };

                slider_CaptureMonitorId.ValueChanged += (sender, e) =>
                {
                    textblock_CaptureMonitorId.Text = textblock_CaptureMonitorId.Tag + slider_CaptureMonitorId.Value.ToString();
                    vSettings.Set("CaptureMonitorId", slider_CaptureMonitorId.Value);
                };

                //Saving
                checkbox_SaveWindowTitle.Click += (sender, e) =>
                {
                    vSettings.Set("SaveWindowTitle", checkbox_SaveWindowTitle.IsChecked);
                };

                //Screenshot
                combobox_ScreenshotSaveFormat.SelectionChanged += (sender, e) =>
                {
                    vSettings.Set("ScreenshotSaveFormat", combobox_ScreenshotSaveFormat.SelectedIndex);
                };

                slider_ScreenshotSaveQuality.ValueChanged += (sender, e) =>
                {
                    textblock_ScreenshotSaveQuality.Text = textblock_ScreenshotSaveQuality.Tag + slider_ScreenshotSaveQuality.Value.ToString() + "%";
                    vSettings.Set("ScreenshotSaveQuality", slider_ScreenshotSaveQuality.Value);
                };

                slider_ScreenshotMaxPixelDimension.ValueChanged += (sender, e) =>
                {
                    textblock_ScreenshotMaxPixelDimension.Text = textblock_ScreenshotMaxPixelDimension.Tag + slider_ScreenshotMaxPixelDimension.Value.ToString() + " px";
                    vSettings.Set("ScreenshotMaxPixelDimension", slider_ScreenshotMaxPixelDimension.Value);
                };

                //Recording
                combobox_VideoSaveFormat.SelectionChanged += (sender, e) =>
                {
                    vSettings.Set("VideoSaveFormat", combobox_VideoSaveFormat.SelectedIndex);
                };

                slider_VideoFrameRate.ValueChanged += (sender, e) =>
                {
                    textblock_VideoFrameRate.Text = textblock_VideoFrameRate.Tag + slider_VideoFrameRate.Value.ToString() + " fps";
                    vSettings.Set("VideoFrameRate", slider_VideoFrameRate.Value);
                };

                combobox_VideoRateControl.SelectionChanged += (sender, e) =>
                {
                    vSettings.Set("VideoRateControl", combobox_VideoRateControl.SelectedIndex);
                };

                slider_VideoBitRate.ValueChanged += (sender, e) =>
                {
                    textblock_VideoBitRate.Text = textblock_VideoBitRate.Tag + slider_VideoBitRate.Value.ToString() + " Kbps";
                    vSettings.Set("VideoBitRate", slider_VideoBitRate.Value);
                };

                slider_VideoMaxPixelDimension.ValueChanged += (sender, e) =>
                {
                    textblock_VideoMaxPixelDimension.Text = textblock_VideoMaxPixelDimension.Tag + slider_VideoMaxPixelDimension.Value.ToString() + " px";
                    vSettings.Set("VideoMaxPixelDimension", slider_VideoMaxPixelDimension.Value);
                };

                //Audio
                combobox_AudioSaveFormat.SelectionChanged += (sender, e) =>
                {
                    vSettings.Set("AudioSaveFormat", combobox_AudioSaveFormat.SelectedIndex);
                };

                combobox_AudioChannels.SelectionChanged += (sender, e) =>
                {
                    ComboBoxItemValue saveValue = (ComboBoxItemValue)combobox_AudioChannels.SelectedItem;
                    vSettings.Set("AudioChannels", saveValue.Value);
                };

                slider_AudioBitRate.ValueChanged += (sender, e) =>
                {
                    textblock_AudioBitRate.Text = textblock_AudioBitRate.Tag + slider_AudioBitRate.Value.ToString() + " kbps";
                    vSettings.Set("AudioBitRate", slider_AudioBitRate.Value);
                };

                combobox_AudioBitDepth.SelectionChanged += (sender, e) =>
                {
                    ComboBoxItemValue saveValue = (ComboBoxItemValue)combobox_AudioBitDepth.SelectedItem;
                    vSettings.Set("AudioBitDepth", saveValue.Value);
                };

                combobox_AudioSampleRate.SelectionChanged += (sender, e) =>
                {
                    ComboBoxItemValue saveValue = (ComboBoxItemValue)combobox_AudioSampleRate.SelectedItem;
                    vSettings.Set("AudioSampleRate", saveValue.Value);
                };

                //Overlay
                checkbox_OverlayShowScreenshot.Click += (sender, e) =>
                {
                    vSettings.Set("OverlayShowScreenshot", checkbox_OverlayShowScreenshot.IsChecked);
                };

                checkbox_OverlayShowRecording.Click += (sender, e) =>
                {
                    vSettings.Set("OverlayShowRecording", checkbox_OverlayShowRecording.IsChecked);
                };

                combobox_OverlayPosition.SelectionChanged += (sender, e) =>
                {
                    ComboBoxItemValue saveValue = (ComboBoxItemValue)combobox_OverlayPosition.SelectedItem;
                    vSettings.Set("OverlayPosition", saveValue.Value);
                };

                //Launch on Windows startup
                checkbox_WindowsStartup.Click += (sender, e) =>
                {
                    try
                    {
                        AVSettings.StartupShortcutManage(string.Empty, true);
                    }
                    catch { }
                };
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to save the application settings: " + ex.Message);
            }
        }
    }
}