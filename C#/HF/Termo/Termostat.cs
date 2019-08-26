using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Collections.ObjectModel;

namespace HFHome
{
    public partial class Termostat : UserControl
    {
        public Termostat()
        {
            InitializeComponent();
        }

        private const int xo = 15;
        private const int yo = 7;
        private const int px = 7;
        private const int py = 2;
        private const int mint = 160;
        private const int maxt = 240;

        private int[] _cdata;
        
        private Color cl_off;
        private Color cl_on;
        private Color cl_frame;
        private bool _movtemp;
        private int _capturerange;
        private int _moverange;
        private bool _movtime;
        private Collection<NVMBlock> nvc;

        private void checkdata()
        {
            for (int i = 0; i < 7; i++)
            {
                if ((_cdata[i] > 95) || (_cdata[i + 7] < 160) || (_cdata[i + 7] > 240))
                {
                    //set def
                    _cdata[0] = 0;
                    _cdata[1] = 24;
                    _cdata[2] = 32;
                    _cdata[3] = 48;
                    _cdata[4] = 60;
                    _cdata[5] = 70;
                    _cdata[6] = 80;

                    _cdata[7] = 200;
                    _cdata[8] = 200;
                    _cdata[9] = 200;
                    _cdata[10] = 200;
                    _cdata[11] = 200;
                    _cdata[12] = 200;
                    _cdata[13] = 200;
                    return;
                }
            }
        }

        public Termostat(SplitterPanel sp, Collection<NVMBlock> nv)
        {
            InitializeComponent();
            this.Parent = sp;
            this.Left = 0;
            this.Width = sp.Width;
            this.Top = 0;
            this.Height = sp.Height;
            this.Anchor = (AnchorStyles.Bottom | AnchorStyles.Right | AnchorStyles.Top | AnchorStyles.Left);
            nvc = nv;

            DayOfWeek dw = System.DateTime.Now.DayOfWeek;
            if ((dw == DayOfWeek.Sunday) || (dw == DayOfWeek.Saturday))
            {
                rbWeekend.Checked = true;
                rbWeekend_CheckedChanged(null, null);
            }
            else
            {
                rbDaily.Checked = true;
                rbDaily_CheckedChanged(null, null);
            }
           
            cl_on = Color.Red;
            cl_off = Color.White;
            cl_frame = System.Drawing.SystemColors.Info;//Color.LightGray;

            drawTable();

            cbpresense.Checked = ((nvc[2].DataByte(0) & 1) != 0);
            cbpresenceframe.Enabled = cbpresense.Checked;
            gbpresence.Enabled = cbpresense.Checked;
            cbpresenceframe.Checked = ((nvc[2].DataByte(0) & 2) != 0);

            udNopresencetemp.Value = nvc[1].DataByte(4)/10;
            udPresenceday.Value = (nvc[2].DataByte(5) + nvc[2].DataByte(6) * 256);
            udpresencenight.Value = (nvc[2].DataByte(7) + nvc[2].DataByte(8) * 256);
            wNAD1.Value = nvc[5].DataByte(0);
            wNAD2.Value = nvc[5].DataByte(1);

        }

        private void drawlinkline(Graphics g , int time, int temp1, int temp2)
        {
            Color c = cl_on;

            int x = TimeToX(time);
            
            int y1 = TempToY(temp1);
            int y2 = TempToY(temp2);
            int y = y1;
           // int dy = 1;
           // if (y1 > y2) { dy = -1; }

            Pen p = new Pen(c);
            p.Width = 3;

            g.DrawLine(p, x, y1, x, y2);

          //  while (y != y2)
          //  {
           //     b.SetPixel(x, y, c);
          //      b.SetPixel(x+1, y, c);
          //      b.SetPixel(x-1, y, c);
          //      y += dy;
          //  }

        }

        private void drawTempZone(Graphics g, int starttime, int enddtime, int temp)
        {
            Color c = cl_on;

            int x1 = TimeToX(starttime);
            int x2 = TimeToX(enddtime);
            
            int y = TempToY(temp);
            

            Pen p = new Pen(c);
            p.Width = 3;

            g.DrawLine(p, x1, y, x2, y);
              
      }

        private int TempToY(int temp)
        {
            if (temp < mint) { temp = mint; }
            if (temp > maxt) { temp = maxt; }
            int y = pictureBox1.Height -yo - ((temp - mint) * py);
            return y;
        }

        private int YtoTemp(int y)
        {
            y = (pictureBox1.Height - y) - yo ;
            return (y / py)+mint;
        }

        private int XToTime(int x)
        {
            if (x > xo)
            {
                x = x - xo;
            }
            else
            {
                x = 0;
            }
            return x / px;
        }

        private int TimeToX(int time)
        {
            return ( xo+(time * px));
        }

        private void drawTable()
        {
            int maxx = pictureBox1.Width;
            int maxy = pictureBox1.Height;

                      
            Bitmap bm = new Bitmap(maxx, maxy);
           

            Graphics g = Graphics.FromImage(bm);
            g.Clear(cl_frame);
            
            
            int t;
            int y;
            int x;
            int mx = pictureBox1.Width - 2;
            for ( t = mint; t <= maxt; t += 10)
            {
                y = TempToY(t);
                for ( x = 0; x < mx; x += 3)
                {
                    bm.SetPixel(x, y, Color.Black);
                }
            }

            int my = pictureBox1.Height - 2;
            for ( t = 0; t <= 96; t += 4)
            {
                x = TimeToX(t);
                for ( y = 2; y < my; y += 3)
                {
                    bm.SetPixel(x, y, Color.Black);
                }
            }
            

            for (int i = 0; i < 6; i++)
            {
                drawTempZone(g, _cdata[i], _cdata[i+1], _cdata[7+i]);
                drawlinkline(g, _cdata[i+1], _cdata[7+i], _cdata[8+i]);
            }
            drawTempZone(g, _cdata[6], 96, _cdata[13]);
            
            //draw cuurent temp log
            if (nvc.Count > 6)
            {
                Pen p = new Pen(Color.Blue);
                for ( t = 0; t <= 90; t += 4)
                {
                    int y1 = nvc[6].DataByte(t / 4);// ;
                    int y2 = nvc[6].DataByte((t + 4) / 4);

                    if ((y1 != 255) && (y2 != 255))
                    {
                        y1 = TempToY(y1*2);
                        y2 = TempToY(y2*2);

                        int x1 = TimeToX(t);
                        int x2 = TimeToX(t + 4);
                        g.DrawLine(p, x1, y1, x2, y2);
                    }
                    
                }
            }

            pictureBox1.Image = bm;
        }

        private void pictureBox1_MouseMove_1(object sender, MouseEventArgs e)
        {
            int t = XToTime(e.X);
            int tp = YtoTemp( e.Y);
            //Find time ArraySegment
            int i ;
            for ( i = 6; i >= 0; i--)
            {
                if (t > _cdata[i])
                {
                    break;
                }
            }

            if (Math.Abs(_cdata[i + 7] - tp) < 4)
            {
                pictureBox1.Cursor = Cursors.SizeNS;
                _capturerange = i + 7;
            }
            else if ((i < 6) && (Math.Abs(t - _cdata[i + 1]) < 2) && (t>0))
            {
                pictureBox1.Cursor = Cursors.SizeWE;
                _capturerange = i + 1;
            }
            else
            {
                pictureBox1.Cursor = Cursors.Arrow;
            }

            if (_movtemp == true)
            {
                //temp move
                if (tp > maxt) { tp = maxt; }
                if (tp < mint) { tp = mint; }
                _cdata[_moverange] = tp;
                drawTable();
            } else if (_movtime == true) {
                if (t < 0) { t = 4; }
                if (t > 94) { t = 94; }

                if ((t > _cdata[_moverange - 1]) && (t < _cdata[_moverange + 1]))
                {
                    _cdata[_moverange] = t;
                    drawTable();
                }
            }

            label22.Top = e.Y + pictureBox1.Top - 8;
            float f = tp;
            f = f / 10;
            label22.Text = f.ToString("F1") + "*C";
            label22.Visible = true;

            label23.Left = e.X + pictureBox1.Left - 15;

            int h = t / 4;
            int m = (t % 4) * 15;

            label23.Text = h.ToString() + ":"+m.ToString("D2")+" h";
            label23.Visible = true;
        }

        private void pictureBox1_MouseDown_1(object sender, MouseEventArgs e)
        {
            if (pictureBox1.Cursor == Cursors.SizeNS)
            {
                _movtemp = true;
                _moverange = _capturerange;
            }
            else if (pictureBox1.Cursor == Cursors.SizeWE) 
            {
                _movtime = true;
                _moverange = _capturerange;
            }
            
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            _movtime = _movtemp = false;
            pictureBox1.Cursor = Cursors.Arrow;
        }

        private void rbDaily_CheckedChanged(object sender, EventArgs e)
        {
            rbWeekend.Checked = !rbDaily.Checked;
            _cdata = nvc[3].DataBytes();
            checkdata();
            drawTable();
        }

        private void rbWeekend_CheckedChanged(object sender, EventArgs e)
        {
            rbDaily.Checked = !rbWeekend.Checked;
            _cdata = nvc[4].DataBytes();
            checkdata();
            drawTable();
        }

        private void udNopresencetemp_ValueChanged(object sender, EventArgs e)
        {
             nvc[1].DataBytes()[4] = ((int)udNopresencetemp.Value*10);
       }

        private void udPresenceday_ValueChanged(object sender, EventArgs e)
        {
            int t = (int)udPresenceday.Value;
           
            nvc[2].DataBytes()[5] = (int)t % 256;
            nvc[2].DataBytes()[6] = (int)t / 256;
        }

        private void udpresencenight_ValueChanged(object sender, EventArgs e)
        {
            int t = (int)udpresencenight.Value;
            
            nvc[2].DataBytes()[7] = (int)t % 256;
            nvc[2].DataBytes()[8] = (int)t / 256;
        }

        private void cbpresense_CheckedChanged(object sender, EventArgs e)
        {
            if (cbpresense.Checked) { nvc[2].DataBytes()[0] |= 1; }
            else { nvc[2].DataBytes()[0] &= 0xFE; };

            cbpresenceframe.Enabled = cbpresense.Checked;
            gbpresence.Enabled = cbpresense.Checked;
        }

        private void cbpresenceframe_CheckedChanged(object sender, EventArgs e)
        {
            if (cbpresenceframe.Checked) { nvc[2].DataBytes()[0] |= 2; }
            else { nvc[2].DataBytes()[0] &= 0xFD; };
        }

        private void pictureBox1_MouseEnter(object sender, EventArgs e)
        {
            
        }

        private void pictureBox1_MouseLeave(object sender, EventArgs e)
        {
            label22.Visible = false;
            label23.Visible = false;
        }

        private void wNAD1_ValueChanged(object sender, EventArgs e)
        {
            nvc[5].DataBytes()[0]= (byte) wNAD1.Value; 
        }

        private void wNAD2_ValueChanged(object sender, EventArgs e)
        {
            nvc[5].DataBytes()[1] = (byte)wNAD2.Value;
        }

  
    }
}
