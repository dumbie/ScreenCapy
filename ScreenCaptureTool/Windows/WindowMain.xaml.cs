using System;
using System.ComponentModel;
using System.Windows;
using static ArnoldVinkCode.AVSettings;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    public partial class WindowMain : Window
    {
        //Window Initialize
        public WindowMain() { InitializeComponent(); }

        //Window Initialized
        protected override void OnSourceInitialized(EventArgs e)
        {
            try
            {
                //Update first launch setting
                SettingSave(vConfigurationScreenCaptureTool, "AppFirstLaunch", "False");

                //Main menu functions
                lb_Menu.PreviewKeyUp += lb_Menu_KeyPressUp;
                lb_Menu.PreviewMouseUp += lb_Menu_MousePressUp;
            }
            catch { }
        }

        //Window Close Handler
        protected override void OnClosing(CancelEventArgs e)
        {
            try
            {
                e.Cancel = true;
                this.Hide();
            }
            catch { }
        }
    }
}