using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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

        public Window()
        {
            InitializeComponent();
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
