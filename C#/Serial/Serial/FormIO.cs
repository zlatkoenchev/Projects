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
    public partial class FormIO : Form
    {

        string sadc;
        string seep;
        public FormIO()
        {
            InitializeComponent();
            
            FOmode.SelectedIndex = 0;
            PulseRelN.SelectedIndex = 6;
            CalID.SelectedIndex = 0;
            sadc = "";
            seep = "";
        }

        public void MsgReceived(byte[] RXQ, int len, int tmm)
        {
            int vv;
            string s = "";
            if (RXQ[0] == 0x93)
            {
                vv = RXQ[1] << 7;
                vv |= RXQ[2];
                s += "A1:" + vv.ToString() + "\r\n";
                vv = RXQ[3] << 7;
                vv |= RXQ[4];
                s += "A2:" + vv.ToString() + "\r\n";
                vv = RXQ[5] << 7;
                vv |= RXQ[6];
                s += "A3:" + vv.ToString() + "\r\n";
                vv = RXQ[7] << 7;
                vv |= RXQ[8];
                s += "A4:" + vv.ToString() + "\r\n";
                vv = RXQ[9] << 7;
                vv |= RXQ[10];
                s += "A5:" + vv.ToString() + "\r\n";
                vv = RXQ[11] << 7;
                vv |= RXQ[12];
                s += "A6:" + vv.ToString() + "\r\n";
                vv = RXQ[13] << 7;
                vv |= RXQ[14];
                s += "A7:" + vv.ToString() + "\r\n";

                sadc = s;
                
            }
            else if (RXQ[0] == 0x8f)
            {
                vv = RXQ[2] << 7;
                vv |= RXQ[3];
                seep = vv.ToString();
            }
        }

        
        public void RefreshOutputs()
        {
            byte[] Txd = new byte[32];

            byte Rel = 0;
            int AA;

            if (tabControl1.SelectedIndex == 0)
            {
                if (cbr1.Checked) { Rel |= 0x01; }
                if (cbr2.Checked) { Rel |= 0x02; }
                if (cbr3.Checked) { Rel |= 0x04; }
                if (cbr4.Checked) { Rel |= 0x08; }
                if (cbr5.Checked) { Rel |= 0x010; }
                if (cbr6.Checked) { Rel |= 0x020; }
                if (cbSSR.Checked) { Rel |= 0x040; }
                Txd[0] = Rel;

                
                AA = tbUbat.Value;
                
                Txd[1] = (byte)((AA >> 7) & 0x7F);
                Txd[2] = (byte)((AA) & 0x7F);
                AA = tbAO.Value;
                Txd[3] = (byte)((AA >> 7) & 0x7F);
                Txd[4] = (byte)((AA) & 0x7F);

                AA = 0;
                if (cb2A.Checked) { AA |= 0x20; }
                if (cb10mA.Checked) { AA |= 0x10; }
                if (0 == FOmode.SelectedIndex)
                {
                    if (cbFO.Checked) { AA |= 1; }
                }
                else
                {
                    AA |= 2;
                }
                if (cbFilter.Checked) { AA |= 0x40; }
                Txd[5] = (byte)AA;

                AA = Freq.Value;
                Txd[6] = (byte)((AA >> 7) & 0x7F);
                Txd[7] = (byte)((AA) & 0x7F);
                Txd[8] = (byte)Dcyc.Value;
                ((this.MdiParent) as FormMDI).Transmit(0x8A, Txd, 9);
            }
            else
            {
                ((this.MdiParent) as FormMDI).Transmit(0x92, Txd, 0);
            }
            

             
          
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
            }
        }    

       

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            float f = tbUbat.Value;
            f /= 100;
            textBox1.Text = f.ToString("F1")  +"V" ;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            float f = tbAO.Value ;
            f /= 100;
            textBox2.Text = f.ToString("F1") + "V";
        }



        private void button1_Click(object sender, EventArgs e)
        {
            byte[] Txd = new byte[4];

           
            int AA;
            Txd[0] = (byte)(CalID.SelectedIndex*2);

            if (int.TryParse(calib.Text, out AA))
            {
                Txd[1] = (byte)((AA >> 7) & 0x7F);
                Txd[2] = (byte)((AA) & 0x7F);

                ((this.MdiParent) as FormMDI).Transmit(0x8C, Txd, 3);
            }
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            textBox3.Text = Freq.Value + "Hz";
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            textBox4.Text = Dcyc.Value + "%";
        }

        private void FOmode_SelectedIndexChanged(object sender, EventArgs e)
        {
            Freq.Visible = (FOmode.SelectedIndex != 0);
            Dcyc.Visible = Freq.Visible;
            label3.Visible = Freq.Visible;
            label4.Visible = Freq.Visible;
            textBox3.Visible = Freq.Visible;
            textBox4.Visible = Freq.Visible;

            cbFO.Visible = !Freq.Visible; ;

        }

        private void SSRmode_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] Txd = new byte[4];

           
            int AA;
            
            Txd[0] = (byte)PulseRelN.SelectedIndex ;
            
            AA = PulseLen.Value;

            Txd[1] = (byte)((AA >> 7) & 0x7F);
            Txd[2] = (byte)((AA) & 0x7F);

            ((this.MdiParent) as FormMDI).Transmit(0x90, Txd, 3);
            
        }

        private void PulseLen_Scroll(object sender, EventArgs e)
        {
            textBox5.Text = PulseLen.Value.ToString() + "ms";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
            RawADC.Text = sadc;
            textBox6.Text = seep;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] Txd = new byte[4];


            
            Txd[0] = (byte)(CalID.SelectedIndex * 2);
          
            ((this.MdiParent) as FormMDI).Transmit(0x8E, Txd, 1);
            
        }

       

        

        

        

        

       
    }
}


