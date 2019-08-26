using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Serial
{
    public partial class FormMDI : Form
    {
        public FormView fView;
        public FormView fView2;
        public FormIO fCont;
        public FormGauge fGauge;
        
        private byte[] RXQ;
        private byte RXpos;
        private byte RXlen;
        int tmm;
        string strStartLog = "Start Logging ...";
        string strStopLog = "Stop Logging ...";
        string strStopLog2 = "Stop Logging ..";
        string strStopLog1 = "Stop Logging .";
        bool bLogStarted = false;
        StreamWriter writer;
        FormView localForm;
        string csv_separator = ";";
        

        public FormMDI()
        {
            InitializeComponent();
            

            
            fView = new FormView();
            fView.MdiParent = this;
            
            fView.Show();
            fCont = new FormIO();
            fCont.MdiParent = this;
            fCont.Left = fView.Right + 1;
            fCont.Show();

            fGauge = new FormGauge();
            fGauge.MdiParent = this;
           
            fGauge.Show();

                 
            
            comboBox1.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            if (comboBox1.Items.Count > 0)
            {
                comboBox1.SelectedIndex = 0;
            }
            // 
            btnLog.Text = strStartLog;
        }

        private void viewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            fView.WindowState = FormWindowState.Normal;
            
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void controlToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            fCont.WindowState = FormWindowState.Normal;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                try
                {
                    timer1.Stop();
                    serialPort1.Close();                    
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.Open();
                    RXQ = new byte[64];
                    for (int j = 0; j < 64; j++)
                    {
                        RXQ[j] = 0xFF;
                    }
                    RXpos = 0;

                    timer1.Start();
                }
                catch
                {
                }
            }
            else
            {
                timer1.Stop();
                serialPort1.Close();
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] buff = new byte[128];
            byte c;
            int i;
            
            while ((serialPort1.IsOpen) &&(serialPort1.BytesToRead > 0))
            {
                serialPort1.Read(buff, 0, 1);
                RXQ[RXpos] = buff[0];
                RXpos++;
                //check for valid header in buffer
                if (RXQ[0] < 127)
                {
                    RXpos=0;
                }
                else
                {
                    if (RXpos == 1)
                    {
                        if (0x8B == RXQ[0])
                        {
                            RXlen = 20;
                        }
                        else if (0x93 == RXQ[0])
                        {
                            RXlen = 15;
                        }
                        else if (0x8F == RXQ[0])
                        {
                            RXlen = 4;
                        }
                        else
                        {
                            RXpos = 0;//unknown cmd
                        }
                    }
                    else
                    {
                        //check for last byte
                        RXlen--;
                        if (0 == RXlen)
                        {
                            //message received!, check for checksum
                            c = 0;

                            for (i = 0; i < (RXpos - 1); i++)
                            {
                                c ^= RXQ[i];
                            }
                            c &= 0x7F;

                            if (c == RXQ[i])
                            {
                                if (fView != null)
                                {
                                    fView.MsgReceived(RXQ, RXpos, tmm);
                                    fCont.MsgReceived(RXQ, RXpos, tmm);
                                    fGauge.MsgReceived(RXQ, RXpos, tmm);
                                }

                                if (bLogStarted && serialPort1.IsOpen)
                                {
                                    WriteMsgToLog(RXQ, RXpos, tmm);
                                }
                            }
                           
                            //clear RX buffer
                            RXlen = 0;
                            RXpos = 0;
                        }
                    }
                }
                
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

            if (!checkBox1.Checked)
            {

                int coms = System.IO.Ports.SerialPort.GetPortNames().Count();
                if (comboBox1.Items.Count != coms)
                {
                    comboBox1.Items.Clear();
                    comboBox1.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
                    if (comboBox1.Items.Count > 0)
                    {
                        comboBox1.SelectedIndex = 0;
                    }
                }
            }
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            tmm++;
            if (fView != null)
            {
                fView.RepaintGraph();
            }
            DisplayLogging();
            fCont.RefreshOutputs();
            if (label1.Text.Length > 1)
            {
                label1.Text = "";
            }
            else
            {
                label1.Text = "Tx";
            }
        }

        public void Transmit(byte ID, byte[] data, byte len)
        {
            byte[] buff = new byte[40];
            byte c;
            int i;

            

            buff[0] = ID;
           
            for (i = 0; i < len; i++)
            {
                buff[1 + i] = data[i];
            }
            c = 0;
            for (i = 0; i < (len + 1); i++)
            {
                c ^= buff[i];
            }
            c &= 0x7F;
            buff[i] = c;
            len += 2;
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(buff, 0, len);
            }
        }

        private void btnLog_Click(object sender, EventArgs e)
        {

            if(!bLogStarted)
            {
                btnLog.Text = strStopLog;
                string FileName = ("Log.csv");

                string dir = Directory.GetCurrentDirectory();
                writer = new StreamWriter(Path.Combine(dir, FileName));

                

                writer.Write("time");
                writer.Write(csv_separator);
                writer.Write("SOF");
                writer.Write(csv_separator);
                writer.Write("ID");
                writer.Write(csv_separator);
                writer.Write("Length");


                writer.Write("\r\n");
                bLogStarted = true;
            }
            else
            {
                btnLog.Text = strStartLog;
                writer.Write("End");
                writer.Close();
                bLogStarted = false;
            }
        }

        private void WriteMsgToLog(byte[] RXQ, int len, int tmm)
        {


        }

        private void DisplayLogging()
        {
            if (btnLog.Text == strStopLog)
            {
                btnLog.Text = strStopLog1;
            }
            else if (btnLog.Text == strStopLog2)
            {
                btnLog.Text = strStopLog;
            }
            else if (btnLog.Text == strStopLog1)
            {
                btnLog.Text = strStopLog2;
            }
        }

        private void meterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fGauge.WindowState = FormWindowState.Normal;
        }
    }
}
