using System;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Collections;
using System.Collections.ObjectModel;

namespace HFHome
{
    public partial class Actuator : UserControl
    {
        private const int px = 8;
        private int[] _data;
        private int _cpx;
        private Color cl_off;
        private Color cl_on;
        private Color cl_frame;
        private Collection<NVMBlock> nvc;
        
        public Actuator()
        {
            InitializeComponent();
        }

//0 NVM_BLOCK(NVM_NWDATA, NWDATA_LEN, &RAM_NWID[0], &ROM_NWID[0]  ,  NWDATA_ADDR)
//1 NVM_BLOCK(NVM_TIMEPROG, TIMEPROG_LEN, &RAM_TIMEPROGRAM[0], &ROM_TIMEPROGRAM[0] , TIMEPROG_ADDR)
//2 NVM_BLOCK(NVM_ACTMODE, ACTMODE_LEN, (__ram uint8 *)&RAM_ACTMODE, (__rom uint8 *)&ROM_ACTMODE, ACTMODE_ADDR)
//3 NVM_BLOCK(NVM_PIRDATA, PIRDATA_LEN, (__ram uint8 *) &RAM_PIRDATA, (__rom uint8 *) & ROM_PIRDATA, PIRDATA_ADDR)
//NVM_BLOCK(NVM_THERMO, THERMO_LEN, (__ram uint8 *) & RAM_THERMO, (__rom uint8 *) & ROM_THERMO, THERMO_ADDR)
//NVM_BLOCK(NVM_RUNTIME, RUNTIME_LEN, (__ram uint8 *) & RAM_RUNTIME, (__rom uint8 *) & ROM_RUNTIME, RUNTIME_ADDR)
//NVM_BLOCK(NVM_LOADPOWER, LOADPOWER_LEN, (__ram uint8 *) & RAM_LOADPOWER, (__rom uint8 *) & ROM_LOADPOWER, LOADPOWER_ADDR)


        private void DetermineDOW()
        {
            if ((rbWeekend.Checked == true) && (nvc.Count > 8))
            {    
                  _data = nvc[8].DataBytes();
             }
             else
             {
                 _data = nvc[1].DataBytes();
            }
        }

        public Actuator(SplitterPanel sp, Collection<NVMBlock> nv)
        {
            InitializeComponent();
            this.Parent = sp;
            this.Left = 0;
            this.Width = sp.Width;
            this.Top = 0;
            this.Height = sp.Height;
            this.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right | AnchorStyles.Top | AnchorStyles.Left);
            nvc = nv;
            //_data = nv[1].DataBytes();
            _cpx = 96;
           
            cl_on = Color.Red;
            cl_off = System.Drawing.SystemColors.Info;
            cl_frame = Color.Gray;//Color.LightGray;

            
            checkBox1.Checked = ((nvc[2].DataByte(0) & 1) != 0);
            checkBox2.Checked = ((nvc[2].DataByte(0) & 2) != 0);
            checkBox3.Checked = ((nvc[2].DataByte(0) & 4) != 0);

            nNAD1.Value = nvc[3].DataByte(1);
            nNAD2.Value = nvc[3].DataByte(2);
            nNAD3.Value = nvc[3].DataByte(3);
            nNAD4.Value = nvc[3].DataByte(4);


            checkBox1_CheckedChanged(null, null);
            checkBox2_CheckedChanged(null, null);
            cbpresenceframe.Enabled = checkBox2.Checked;

            cbpresenceframe.Checked = (nvc[3].DataByte(0) & 0x02) != 0;
            udPresenceday.Value = (nvc[3].DataByte(5) + nvc[3].DataByte(6) * 256);
            udpresencenight.Value = (nvc[3].DataByte(7) + nvc[3].DataByte(8) * 256);
            udCmdTimoeut.Value = (nvc[2].DataByte(4) + nvc[2].DataByte(5) * 256); 
            
            cbActType.SelectedIndex = nvc[2].DataByte(1);


          
            DayOfWeek dw = System.DateTime.Now.DayOfWeek;
            if ((dw == DayOfWeek.Sunday) || (dw == DayOfWeek.Saturday))
            {
                rbWeekend.Checked = true;
             //   rbWeekend_CheckedChanged(null, null);
            }
            else
            {
                rbDaily.Checked = true;       
               // rbDaily_CheckedChanged(null, null);
            }

            //     drawTable();
       
        }
   
        private void drawTimeZone(Bitmap b, int n, int bstate)
        {
            Color c = cl_on;
            if (bstate == 0) { c = cl_off; }
            int xoffs = n * px;
            int ym = b.Height ;
            int x;
            int x2 = xoffs + px;
            int x1 = xoffs +1;

            for (int y = 0; y < ym; y++)
            {
                for( x = x1; x < x2; x++)
                {
                    b.SetPixel(x, y, c);
                }
                b.SetPixel(x, y, Color.Gray);
            }
        }

        private void drawTable()
        {
            int maxx = pictureBox1.Width;
            int maxy = pictureBox1.Height;

            DetermineDOW();

            Bitmap bm = new Bitmap(maxx, maxy);

            Graphics g = Graphics.FromImage(bm);
            g.Clear(cl_off);

            int i;
               
            for (i = 0; i < 96; i++)
            {
                drawTimeZone(bm,i,(_data[i/8] & (1<<(i%8))));
            }
            pictureBox1.Image = bm;
        }     

        private void ToggleRange(int t)
        {
            if (t < 96)
            {
                int by = t / 8;
                int bi = t % 8;
                _data[by] = (byte)(_data[by] ^ (1 << bi));
               
            }
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            int t = e.X / px;
            int tm = t * 15;
            int hr = tm / 60;
            int mn = tm - (hr * 60);
            label3.Visible = true;
            label3.Text = hr.ToString("d2") + ":" + mn.ToString("d2") + "ч";
            label3.Left = pictureBox1.Left + e.X;
            
            if ((_cpx <96) && (t != _cpx))
            {
                ToggleRange(t);
                drawTable();
                _cpx = t;
            }
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            int t = e.X / px;
            if (t < 96)
            {
                ToggleRange(t);
                drawTable();
                _cpx = t;
            }
        }

        private void pictureBox1_MouseLeave(object sender, EventArgs e)
        {
            _cpx = 96;
            label3.Visible = false;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            _cpx = 96;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            pictureBox1.Enabled = checkBox1.Checked;
            label1.Enabled = checkBox1.Checked;
            label5.Enabled = checkBox1.Checked;
            label2.Enabled = checkBox1.Checked;
            label3.Enabled = checkBox1.Checked;

            if (checkBox1.Checked) { nvc[2].DataBytes()[0] |= 1;} else {nvc[2].DataBytes()[0] &= 0xFE;}
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked) 
            { 
                nvc[2].DataBytes()[0] |= 2;
                nvc[3].DataBytes()[0] |= 1;//PIR mode
                
            } else { nvc[2].DataBytes()[0] &= 0xFD; }
            cbpresenceframe.Enabled = checkBox2.Checked;
            nNAD1.Enabled = nNAD2.Enabled = nNAD3.Enabled = nNAD4.Enabled = checkBox2.Checked;

            udPresenceday.Enabled = udpresencenight.Enabled = label20.Enabled = label21.Enabled = checkBox2.Checked;
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked) 
            { 
                nvc[2].DataBytes()[0] |= 4;
                
                
            } else 
            { 
                nvc[2].DataBytes()[0] &= 0xFB; 
            }//actuator mode
            label6.Enabled = checkBox3.Checked;
            udCmdTimoeut.Enabled = checkBox3.Checked;
          

        }

        private void cbpresenceframe_CheckedChanged(object sender, EventArgs e)
        {
            if (cbpresenceframe.Checked) { nvc[3].DataBytes()[0] |= 2; }
            else
            {
                nvc[3].DataBytes()[0] &= 0xFD; 
            }
        }

        private void udPresenceday_ValueChanged(object sender, EventArgs e)
        {
            int t = (int)udPresenceday.Value;

            nvc[3].DataBytes()[5] = (int)t % 256;
            nvc[3].DataBytes()[6] = (int)t / 256;
        }

        private void udpresencenight_ValueChanged(object sender, EventArgs e)
        {
            int t = (int)udpresencenight.Value;

            nvc[3].DataBytes()[7] = (int)t % 256;
            nvc[3].DataBytes()[8] = (int)t / 256;
        }

        private void cbActType_SelectedIndexChanged(object sender, EventArgs e)
        {
             nvc[2].DataBytes()[1]= cbActType.SelectedIndex;
        }

        private void udCmdTimoeut_ValueChanged(object sender, EventArgs e)
        {
            nvc[2].DataBytes()[4] = (((int)udCmdTimoeut.Value) & 0xFF);
            nvc[2].DataBytes()[5] = (((int)udCmdTimoeut.Value / 256) & 0xFF);
        }

        private void nNAD1_ValueChanged_1(object sender, EventArgs e)
        {
            nvc[3].DataBytes()[1] = (int)nNAD1.Value;
        }

        private void nNAD2_ValueChanged(object sender, EventArgs e)
        {
            nvc[3].DataBytes()[2] = (int)nNAD2.Value;
        }

        private void nNAD3_ValueChanged(object sender, EventArgs e)
        {
            nvc[3].DataBytes()[3] = (int)nNAD3.Value;
        }

        private void nNAD4_ValueChanged(object sender, EventArgs e)
        {
            nvc[3].DataBytes()[4] = (int)nNAD4.Value;
        }

        private void rbDaily_CheckedChanged(object sender, EventArgs e)
        {
            rbWeekend.Checked = !rbDaily.Checked;
            drawTable();
        }

        private void rbWeekend_CheckedChanged(object sender, EventArgs e)
        {
            rbDaily.Checked = !rbWeekend.Checked;
            drawTable();
        }

     
    }
}
