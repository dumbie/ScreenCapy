using System.Windows;
using static ArnoldVinkCode.AVInteropDll;
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
                SetupDefaults(ProcessPriorityClasses.NORMAL_PRIORITY_CLASS, false);
            }
            catch { }
        }
    }
}