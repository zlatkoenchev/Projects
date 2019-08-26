using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Serial
{
   
    
    public partial class FormView : Form
    {

       
        Graph myGraph;
        
        

       // delegate void SetTextCallback( );

        // This method is passed in to the SetTextCallBack delegate 
        // to set the Text property of textBox1. 
        public void MsgReceived(byte[] RXQ, int len, int tmm)
        {
            int vv;
            if (RXQ[0] == 0x8b)
            {
                //TreeNode tn = Msgs.Nodes[0];
                //int child = tn.Nodes.Count;
                
                Point pt = new Point(0,0);
                pt.X = tmm;
                vv = RXQ[1];
                vv <<= 7;
                vv |= RXQ[2];
                pt.Y = vv*10;
                //Msgs.Nodes[0].Text = "A1=" + vv.ToString() + "mV";
                myGraph.AddNewData(0, pt);

                vv = RXQ[3];
                vv <<= 7;
                vv |= RXQ[4];
                pt.Y = vv * 10;
                myGraph.AddNewData(1, pt);

                vv = RXQ[5];
                vv <<= 7;
                vv |= RXQ[6];
                pt.Y = vv * 10;
                myGraph.AddNewData(2, pt);

                vv = RXQ[7];
                vv <<= 7;
                vv |= RXQ[8];
                pt.Y = vv * 10;
                myGraph.AddNewData(3, pt);

                vv = RXQ[9];
                vv <<= 7;
                vv |= RXQ[10];
                pt.Y = vv * 10;
                myGraph.AddNewData(4, pt);

                vv = RXQ[11];
                vv <<= 7;
                vv |= RXQ[12];
                pt.Y = vv * 10;
                myGraph.AddNewData(5, pt); //A6

                vv = RXQ[13];
                vv <<= 7;
                vv |= RXQ[14];
                vv <<= 7;
                vv |= RXQ[15];
                pt.Y = vv;
                myGraph.AddNewData(6, pt); //FI

                vv = RXQ[16];
                pt.Y = vv;
                myGraph.AddNewData(7, pt); //FI_DC

                vv = RXQ[17];
                vv <<= 7;
                vv |= RXQ[18];
                vv <<= 7;
                vv |= RXQ[19];
                pt.Y = vv;///1000;
                myGraph.AddNewData(8, pt); //I
            } 
        }

        public FormView()
        {
            InitializeComponent();
          
           
            int child = Msgs.Nodes.Count;
            myGraph = new Graph(child, 10000);
            for (int i = 0; i < child; i++)
            {
                myGraph.Channels[i].Name = Msgs.Nodes[i].Text;
                myGraph.Channels[i].Visible = Msgs.Nodes[i].Checked;
            }

           
            TimeRangeEdit.SelectedIndex = 1;
            
        }

 
        public void RepaintGraph()
        {

            if (cbPause.Checked == true)
            {
                return;
            }

            int tm = int.Parse(TimeRangeEdit.Text);

            myGraph.Xrange = tm * 1000 / 100;
            myGraph.XLabelStep = myGraph.Xrange / 10;
            myGraph.XResolution = (float)0.1;
            myGraph.SetImageSize(pictureBox1.Size.Width, pictureBox1.Size.Height);
            myGraph.Draw();
            pictureBox1.Image = myGraph.bmp;
        }


        public Point GetLastData(string data_name)
        {
            return myGraph.GetLastData(data_name);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
            }
            
        }


        private void Msgs_AfterCheck(object sender, TreeViewEventArgs e)
        {
            int child = Msgs.Nodes.Count;
            
            for (int i = 0; i < child; i++)
            {
                myGraph.Channels[i].Visible = Msgs.Nodes[i].Checked;
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (null != myGraph) { myGraph.Dispose(); }
        }

        

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            myGraph.UpdateMinMax = checkBox1.Checked;
        }

       
       


       
       

       

              

        
    }

    struct gPoint 
    {
        public UInt16 ChID;
        public Point Data;
    }

    public class gChannel: Object
    {
        public int cMin;
        public int cMax;
        public int cVisibleMin;
        public int cVisibleMax;
        public Pen cPen;
        public Point LastData;
        private Point LastDrawnData;
        public String Name;
        public Boolean Visible;
        public int VisibleIndex;

        public gChannel(Color col,string n)
            : base()
        {
            LastData.X = 0;
            LastData.Y = 32767;
            LastDrawnData = LastData;
            cMin = 32767;
            cVisibleMin = 32768;
            cVisibleMax = -32766; 
            cMax = -32766;
            cPen = new Pen(col);
            Name = n;
            Visible = true;
        }
        public void SetData(Point NewP)
        {
            if (LastData.Y != NewP.Y)
            {
                if (cMin >= NewP.Y) { cMin = NewP.Y; }
                if (cMax <= NewP.Y) { cMax = NewP.Y; }
            }
            LastData = NewP;
            LastDrawnData = NewP;
        }

        public void StartDraw(bool bUseVisibleMinMax)
        {
            if (true == bUseVisibleMinMax) //use previous range
            {
                cMin = cVisibleMin;
                cMax = cVisibleMax;
                if (LastData.Y > cMax)
                {
                    cMax = LastData.Y;
                }
                if (LastData.Y < cMin)
                {
                    cMin = LastData.Y;
                }
            }
            cVisibleMin = 32768;
            cVisibleMax = -32766; 
        }

        public void SetLastDrawnData(Point NewP)
        {
            LastDrawnData = NewP;
            if (cVisibleMax <= NewP.Y)
            {
                cVisibleMax = NewP.Y;
            }
            if (cVisibleMin >= NewP.Y)
            {
                cVisibleMin = NewP.Y;
            }
        }

        public Point GetLastDrawnData()
        {
            return LastDrawnData;
        }

        public int DataSpan()
        {
            int d = cMax - cMin;
            if (0 == d)
            {
                d = 1;
            }
            return d;
        }
    }

    public class Graph : Object
    {
        public Collection<gChannel> Channels;
        private gPoint[] gData;
        public Bitmap bmp;
        private Graphics gr;
        public float XResolution; //resolution of x 
        private int NumPoints; //in buffer
        private int PointPos;
        private int MaxPoints;
        public int Xrange;   //size of x of each graph
        private float Yrange;   //size of y of each graph
        private float Xscale;
        private int SizeX;
        private int SizeY;
        private Font drawFont;
        private SolidBrush drawBrush;
        private Pen drawPen;
        private int LastX;
        private int LeftX;
        private int RightX;
        public Color BackgroundColor;
        public Color GridColor;
        private Byte GIntens;
        public String FontName;
        public int FontSize;
        public int LeftGraphMargin;
        private int YGraphMargin;
        public int XLabelStep;
        public string Xunit;
        public bool UpdateMinMax;
          
        private int NumChannels()
        {
            return Channels.Count;
        }

        private Color GetColor(int i)
        {
            Color c;
            switch (i % 5)
            {
                case 1:
                    c = Color.Red;
                    break;
                case 2:
                    c = Color.Blue;
                    break;
                case 3:
                    c = Color.GreenYellow;
                    break;
                case 4:
                    c = Color.Orange;
                    break;
                default:
                    c = Color.White;
                    break;
            }
            return c;
        }

        public Graph(int numCh, int max_points):base()
        {
            MaxPoints = max_points;
            Channels = new Collection<gChannel>();
            gData = new gPoint[MaxPoints];
            for (int i = 0; i < numCh; i++)
            {
                gChannel cd = new gChannel(GetColor(i),"Ch_"+i.ToString());
                Channels.Add(cd);
            }
            NumPoints = 0;
            PointPos = 0;
            
            Xrange = 100;
            BackgroundColor = Color.Black;
            GridColor = Color.FromArgb(0,255,0);
            GIntens = 20;
            FontName = "Arial";
            FontSize = 8;
            LeftGraphMargin = 20;
            YGraphMargin = 4;
            XLabelStep = 20;
            XResolution = 0.2f;
            Xunit = "s";
            UpdateMinMax = false;
        }

        private Color GetColorWithIntensity(Color col, Byte intens)
        {
            
            if (intens > 100) { intens = 100; }
            int r = (col.R * intens)/100;
            int g = (col.G * intens)/100;
            int b = (col.B * intens)/100;
            
            col = Color.FromArgb(r,g,b);
            return col;
        }

        public byte GridIntensity
        {
            get { return GIntens; }
            set
            {
                if (value > 100)
                {
                    GIntens = 100;
                }
                else
                {
                    GIntens = value;
                }
            }
        }

        public void Dispose()
        {
            if (null != bmp) { bmp.Dispose(); };
            if (null != drawBrush) { drawBrush.Dispose(); }
            if (null != drawFont) { drawFont.Dispose(); }
            if (null != drawPen) { drawPen.Dispose(); }
        }

        //set new image size
        public void SetImageSize(int x, int y)
        {
            try
            {
                Dispose();

                SizeX = x;
                SizeY = y;
                bmp = new Bitmap(SizeX, SizeY);
                gr = Graphics.FromImage(bmp);
                drawPen = new Pen(GridColor);
                drawPen.Color = GridColor;
                drawFont = new System.Drawing.Font(FontName, FontSize);
                drawBrush = new System.Drawing.SolidBrush(BackgroundColor);
                
            }
            catch
            {
            }
        }      

        //adds new data to channels
        public void AddNewData(int channel, Point newdata)
        {
            if (channel < NumChannels())
            {
                if (LastX < newdata.X)
                {
                    LastX = newdata.X;
                }
                gData[PointPos].Data = newdata;
                gData[PointPos].ChID = (UInt16)channel;
                NumPoints++;
                //keep num of data in buffer
                if (NumPoints >= MaxPoints)
                {
                    NumPoints = MaxPoints;
                }
                //keep ring position
                PointPos++;
                if (PointPos >= MaxPoints)
                {
                    PointPos = 0;
                }
                Channels[channel].SetData(newdata);
            }
        }

        public void Draw()
        {
            float CX = Xrange + 5;
            float CY = 0;//Top right point

            bool bUpdateRange = UpdateMinMax;
            
            //clear BMP
            drawBrush.Color = BackgroundColor;
            gr.FillRectangle(drawBrush, 0, 0, SizeX, SizeY);
            
            #region count visible channels
            int numVisCh = 0;
            for (int i = 0; i < NumChannels(); i++)
            {
                if (Channels[i].Visible)
                {
                    Channels[i].VisibleIndex = numVisCh;
                    numVisCh++;
                    Channels[i].StartDraw(bUpdateRange);
                }
                else
                {
                    Channels[i].VisibleIndex = -1;
                }
                
            }
            if (0 == numVisCh)
            {
                return;
            }
            Yrange = (SizeY - 10) / numVisCh;
            #endregion
          
            #region determine dispalyed X range values
            
            if (LastX <= Xrange)
            {
                LeftX = 0;
                RightX = Xrange;
            }
            else
            {
                LeftX = LastX - Xrange;
                RightX = LastX;
            }


            Xscale = (SizeX - LeftGraphMargin);
            Xscale /= Xrange;
            #endregion

            #region DrawVertLines
            int xt = LeftX;

            drawPen.Color = GetColorWithIntensity(GridColor, GIntens);
            drawBrush.Color = GridColor;
            while (xt <= RightX)
            {
                if (0 == (xt % XLabelStep))
                {
                    //draw
                    float x1 = LeftGraphMargin + ((xt - LeftX) * Xscale);
                    xt += XLabelStep;

                    gr.DrawLine(drawPen, x1, SizeY , x1, 0);
                    float xl = xt * XResolution;
                    //outptu time
                    string s = xl.ToString("f1") ;
                    s += Xunit;
                    gr.DrawString(s, drawFont, drawBrush, x1 , SizeY - drawFont.GetHeight());
                    
                }
                else
                {
                    xt++;
                }
            }
            #endregion

            #region EvalData
            int startPos = GetPrevPos(PointPos);
            int PointsRem = NumPoints;
            Boolean bStop = (gData[startPos].Data.X < LeftX);
            if (0 == NumPoints) { bStop = true; }
            while (bStop == false)
            {
                Point cp = gData[startPos].Data;
                int ch = gData[startPos].ChID;

                if (Channels[ch].Visible)
                {
                    DrawChannel(ch, cp);
                }

                startPos = GetPrevPos(startPos);
                if (PointsRem != 0)
                {
                    PointsRem--;
                    
                }
                if (PointsRem != 0)
                {
                    if (gData[startPos].Data.X < LeftX)
                    {
                        bStop = true;
                    }
                }
                else
                {
                    bStop = true;
                }
            } 
            #endregion

            #region DrawGrid
            CY = 0;
            string str;
            drawPen.Color = GetColorWithIntensity(GridColor, GIntens);
            for (int i = 0; i < NumChannels(); i++)
            {
                if (Channels[i].Visible)
                {
                    int miny = Channels[i].cMin;
                    int maxy = Channels[i].cMax;
                    drawBrush.Color = Channels[i].cPen.Color;
                    str=Channels[i].Name + "["+Channels[i].LastData.Y.ToString()+"]";
                    gr.DrawString(str, drawFont, drawBrush, 1, CY);
                    gr.DrawString(maxy.ToString(), drawFont, drawBrush, 1, CY + drawFont.GetHeight());
              
                    CY += Yrange;
                    
                    gr.DrawString(miny.ToString(), drawFont, drawBrush, 1, CY - drawFont.GetHeight());
                    

                    if ((miny < 0) && (maxy>0))
                    {
                        float Yscale = (Yrange) / Channels[i].DataSpan();
                        float yy = CY + (miny * Yscale);

                        gr.DrawLine(drawPen, 0, yy, SizeX, yy);
                        gr.DrawString("0", drawFont, drawBrush, 1, yy - drawFont.GetHeight());
                    }
                    else
                    {
                        gr.DrawLine(drawPen, 0, CY, SizeX, CY);
                    }
                    
                }
            } 
            #endregion

        }

        private int GetPrevPos(int i)
        {
            if (i == 0)
            {
                return (MaxPoints-1);
            }
            else
            {
                return i - 1;
            }
        }

        private void DrawChannel(int i, Point p)
        {
            if (!p.Equals(Channels[i].GetLastDrawnData()))
            {
                float Yscale = (Yrange - YGraphMargin) / Channels[i].DataSpan();
                float x2 = LeftGraphMargin + ((Channels[i].GetLastDrawnData().X - LeftX) * Xscale);
                float x1 = LeftGraphMargin + ((p.X - LeftX) * Xscale);
                int miny = Channels[i].cMin;
                float Ybase = ((Channels[i].VisibleIndex + 1) * Yrange) - (YGraphMargin/2);
                float y1 = Ybase - ((p.Y - miny) * Yscale);
                float y2 = Ybase - ((Channels[i].GetLastDrawnData().Y - miny) * Yscale);

                gr.DrawLine(Channels[i].cPen, x1, y1, x2, y2);
                Channels[i].SetLastDrawnData(p);
            }
        }

        public Point GetLastData(string cname)
        {
            Point p = new Point(0,0);

            for (int c = 0; c < Channels.Count; c++)
            {
                if (Channels[c].Name == cname)
                {
                    p = Channels[c].LastData;
                    break;
                }
            }
            return p;
        }
    }

 
}
