using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace PDP11_GUI
{
    public partial class Window : Form
    {

        [DllImport("PDP11-EMULATOR.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern uint pdp11_step();
        [DllImport("PDP11-EMULATOR.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern uint pdp11_init(IntPtr prt);
        [DllImport("PDP11-EMULATOR.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern uint pdp11_debug();
        [DllImport("PDP11-EMULATOR.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern uint pdp11_disasm(UInt16[] ppc);

        // Screen
        static Rectangle screenBorders = new Rectangle(0, 0, 100, 100);
        Bitmap screenImage = new Bitmap(screenBorders.Width, screenBorders.Height, PixelFormat.Format1bppIndexed);
        IntPtr videoMemory = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(byte)) * screenBorders.Width * screenBorders.Height / 8);

        public Window()
        {
            InitializeComponent();
        }

        private void Window_Load(object sender, EventArgs e)
        {
            Screen.Image = screenImage;
        }

        private void stepButton_Click(object sender, EventArgs e)
        {

        }

        private void runButton_Click(object sender, EventArgs e)
        {

        }

        private void stopButton_Click(object sender, EventArgs e)
        {

        }

        private void resetButton_Click(object sender, EventArgs e)
        {

        }

    }
}
