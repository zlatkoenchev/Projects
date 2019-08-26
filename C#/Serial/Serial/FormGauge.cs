using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Serial
{
    public partial class FormGauge : Form
    {
        int[] Data;
        public FormGauge()
        {
            InitializeComponent();
            Data = new int[10];
            
        }
        public void MsgReceived(byte[] RXQ, int len, int tmm)
        {
            int vv;

            if (RXQ[0] == 0x8b)
            {

                vv = RXQ[1];
                vv <<= 7;
                vv |= RXQ[2];
                Data[0] = vv;

                vv = RXQ[3];
                vv <<= 7;
                vv |= RXQ[4];
                Data[1] = vv;

                vv = RXQ[5];
                vv <<= 7;
                vv |= RXQ[6];
                Data[2] = vv;

                vv = RXQ[7];
                vv <<= 7;
                vv |= RXQ[8];
                Data[3] = vv;

                vv = RXQ[9];
                vv <<= 7;
                vv |= RXQ[10];
                Data[4] = vv;

                vv = RXQ[11];
                vv <<= 7;
                vv |= RXQ[12];
                Data[5] = vv; //A6

                vv = RXQ[13];
                vv <<= 7;
                vv |= RXQ[14];
                vv <<= 7;
                vv |= RXQ[15];
                Data[6] = vv; //FI

                vv = RXQ[16];
                Data[7] = vv; //FI_DC

                vv = RXQ[17];
                vv <<= 7;
                vv |= RXQ[18];
                vv <<= 7;
                vv |= RXQ[19];
                Data[8] = vv; //I
            }
        }

        string AIFormat(int i)
        {
            float fv = Data[i];
            fv /= 100f;
            string s = "A"+(i+1).ToString()+": "+fv.ToString("F2") + "V";
            return s;
        }

        

        private void timer1_Tick(object sender, EventArgs e)
        {
            float fv;
            this.SuspendLayout();
            gA1.Value = Data[0]; lA1.Text = AIFormat(0);
            gA2.Value = Data[1]; lA2.Text = AIFormat(1);
            gA3.Value = Data[2]; lA3.Text = AIFormat(2);
            gA4.Value = Data[3]; lA4.Text = AIFormat(3);
            gA5.Value = Data[4]; lA5.Text = AIFormat(4);
            gA6.Value = Data[5]; lA6.Text = AIFormat(5); ;
            gFreq.Value = Data[6]; lFreq.Text = "FI: " + (Data[6] ).ToString() + "Hz";
            gDC.Value = Data[7]; lDC.Text = "FI_DC: " + (Data[7] ).ToString() + "%";
            if (Data[8] > 10000)
            {
                gCur.Maximum = 2000000;
                fv = Data[8];
                fv /= 1000000f;
                label2.Text = "I: " + fv.ToString("F3") + " A";
                label9.Text = "2";
            }
            else
            {
                gCur.Maximum = 10000;
                fv = Data[8];
                fv /= 1000f;
                label2.Text = "I: " + fv.ToString("F3") + " mA";
                label9.Text = "10";
            }
            gCur.Value = Data[8]; 
            this.ResumeLayout();

        }

        private void FormGauge_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
            }
        }
    }
}
