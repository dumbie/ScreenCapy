using ArnoldVinkCode;
using System.Threading.Tasks;
using static ScreenCapture.AppVariables;

namespace ScreenCapture
{
    public partial class SocketServer
    {
        //Enable the socket server
        public static async Task EnableSocketServer()
        {
            try
            {
                int socketServerPort = vSettings.Load("ServerPort", typeof(int));
                vArnoldVinkSockets = new ArnoldVinkSockets("127.0.0.1", socketServerPort, false, true);
                vArnoldVinkSockets.vSocketTimeout = 250;
                vArnoldVinkSockets.EventBytesReceived += ReceivedSocketHandler;
                await vArnoldVinkSockets.SocketServerEnable();
            }
            catch { }
        }
    }
}