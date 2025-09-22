using ArnoldVinkCode;
using ArnoldVinkStyles;
using ScreenCaptureImport;
using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace ScreenCapture
{
    public class AppExit
    {
        //Application close prompt
        public static void Exit_Prompt()
        {
            try
            {
                List<string> messageAnswers = new List<string>();
                messageAnswers.Add("Exit application");
                messageAnswers.Add("Cancel");

                string messageResult = AVMessageBox.Popup(null, "Do you really want to exit Screen Capture Tool?", "You will no longer be able to take screenshots using the set shortcuts.", messageAnswers);
                if (messageResult == "Exit application")
                {
                    Exit();
                }
            }
            catch { }
        }

        //Close application
        public static void Exit()
        {
            try
            {
                //Check exit status
                if (AppVariables.vApplicationExiting)
                {
                    Debug.WriteLine("Application is already exiting.");
                    return;
                }
                else
                {
                    Debug.WriteLine("Exiting application.");
                    AppVariables.vApplicationExiting = true;
                }

                //Stop active video capture
                try
                {
                    CaptureResult captureResult = CaptureScreen.StopCaptureVideoToFile();
                    Debug.WriteLine("Capture stop result: " + captureResult.Status + " / " + captureResult.ResultCode + " / " + captureResult.Message);
                }
                catch { }

                //Reset screen capture resources
                try
                {
                    CaptureResult captureResult = CaptureImport.CaptureReset();
                    Debug.WriteLine("Capture reset result: " + captureResult.Status + " / " + captureResult.ResultCode + " / " + captureResult.Message);
                }
                catch { }

                //Stop keyboard hotkeys
                AVInputOutputHotkeyHook.Stop();

                //Hide the visible tray icons
                AVDispatcherInvoke.DispatcherInvoke(delegate
                {
                    AppTrayMenuTool.TrayNotifyIcon.Visible = false;
                    AppTrayMenuCapture.TrayNotifyIcon.Visible = false;
                });

                //Close the application
                Environment.Exit(0);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Failed to exit application: " + ex.Message);
            }
        }
    }
}