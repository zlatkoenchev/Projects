using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Globalization;

namespace font
{
    public partial class Form1 : Form
    {
        Bitmap bm;
        int xs, ys, p;
        byte[] data;
        
        public Form1()
        {
            InitializeComponent();
            xs = 12; ys = 24; p = 10;
            data = new byte[(xs*ys/8)];
            for (int i = 0; i < (xs * ys/8); i++)
                data[i] = 0;
            draw();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string s = textBox1.Text;
           
              //  data[i] = 0;
            NumberStyles styles;
            styles = NumberStyles.HexNumber;
            CultureInfo provider;
            provider = CultureInfo.InvariantCulture;
            int db = 0;
            while (s.Length > 3)
            {
                int i = s.IndexOf(',');
                if (i != -1)
                {
                    string v = s.Substring(0, i);
                    int val;
                    v = v.Trim();
                    v = v.Remove(0, 2);
                    if (true == Int32.TryParse(v, styles, provider, out val))
                    {
                        data[db] = (byte)val; db++;
                    }
                    s = s.Remove(0, i + 1);
                }
                else
                {
                    s="";
                }
            }
           draw();
        }


        private Color GetDataColor(int x, int y)
        {
            int r = y / 8;
            byte d = data[r * xs + x];
            int bity = y - (r * 8);

            int bit = d & (1 << bity);
            if (0 != bit)
            {
                return Color.Black;
            }
            return Color.White;
        }

        private void drawpoint(Bitmap b, int x, int y, Color c)
        {
            int xx = x * p;
            int yy = y * p;
            for (int i = 1; i < p; i++)
            {
                for (int j = 1; j < p; j++)
                {
                    b.SetPixel(xx + i, yy + j, c);
                }
            }
        }

        private void draw()
        {

            int maxx = xs * p + 1;
            int maxy = ys * p + 1;

            bm = new Bitmap(maxx, maxy);
            int i,j;
            //clear
            for (i = 0; i < maxx; i++)
            {
                for (j = 0; j < maxy; j++)
                {
                    
                    bm.SetPixel(i, j, Color.White);
                }
            }
            
            //vert lines
            for (i = 0; i < maxx; i = i + p)
            {
                for (j = 0; j < maxy; j++)
                {
                    bm.SetPixel(i, j, Color.Gray);
                }
            }

            //hor lines
            for (j = 0; j < maxy; j = j + p)
            {
                for (i = 0; i < maxx; i++)
                {
                
                    bm.SetPixel(i, j, Color.Gray);
                }
            }

            for (i = 0; i < xs; i++)
            {
                for (j = 0; j < ys; j++)
                {
                    drawpoint(bm, i, j, GetDataColor(i, j));
                }
            }
            pictureBox1.Image = bm;
        }

        

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            int x = e.X/p;
            int y = e.Y/p;
            int col = x;
            int row = y/8;
            int bity = y - (row * 8);
            data[(row * xs) + col] = (byte)(data[(row * xs) + col] ^ (1 << bity));
            draw();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            string s = "";
            for (int i = 0; i < (xs * ys / 8); i++)
            {
                s += "0x" + data[i].ToString("X")+",";

            }
            textBox1.Text = s;
        }

    }
}
