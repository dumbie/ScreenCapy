using System.Windows;
using static ArnoldVinkCode.AVProcess;
using static ArnoldVinkCode.AVStartup;

namespace ScreenCapture
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            try
            {
                //Setup application defaults
                SetupDefaults(ProcessPriorityClasses.Normal, false);
            }
            catch { }
        }
    }
}