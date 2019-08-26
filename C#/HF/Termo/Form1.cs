using System;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;


namespace HFHome
{
    enum TActionList { HouseSelected, RoomSelected, DeviceSelected, SignalSelected, ConnectedCom};

    public partial class Form1 : Form
    {
        House _housecfg;
        String _housecfg_old;

        SerialProtocol spf;
        MyBackgroundWorker _bw;
        Scanner _scanner;
        NVMreader _nvmReader;
        NVMwriter _nvmWriter;
        Actuator _tprofile;
        Termostat _tempprofile;

        TreeNode CopyNode;

        private void Action(TActionList a)
        {
            if (tv.SelectedNode != null)
            {
                this.Text = tv.SelectedNode.Text;
            } 
            switch (a)
            {
                case TActionList.DeviceSelected:
                    {
                        bAddRoom.Enabled = false;
                        bAddDevice.Enabled = false;
                        bAddSignal.Enabled = true;
                        bCopy.Enabled = true;
                        bDelete.Enabled = true;
                        writeNVMToolStripMenuItem.Enabled = (spf !=null);
                        readNVMToolStripMenuItem.Enabled = (spf != null);
                        flashToolStripMenuItem.Enabled = (spf != null);
                        MIReset.Enabled = (spf != null);
                        button18.Enabled = (spf != null);

                        bWriteNVM.Enabled = breadNVM.Enabled = (spf != null);

                        Device d = tv.SelectedNode.Tag as Device;

                        splitContainer1.Panel2.Controls.Clear();
                        if ((d.IsDeviceActuator()) && (d.NVM.Count > 6) && (d.NVM[1].Lenght == 12))
                        {
                            _tprofile = new Actuator(splitContainer1.Panel2, d.NVM);
                            _tprofile.Show();
                        }
                        else if ((d.IsDeviceThermostat()) && (d.NVM.Count > 3) && (d.NVM[3].Lenght == 14))
                        {
                            _tempprofile = new Termostat(splitContainer1.Panel2, d.NVM);
                            _tempprofile.Show();
                        }
                       
                    }
                    break;
                case TActionList.HouseSelected:
                    {
                        bAddRoom.Enabled = true;
                        bAddDevice.Enabled = false;
                        bAddSignal.Enabled = false;
                        bCopy.Enabled = true;
                        bDelete.Enabled = false;
                        writeNVMToolStripMenuItem.Enabled = false;
                        readNVMToolStripMenuItem.Enabled = false;
                        MIReset.Enabled = false;
                        flashToolStripMenuItem.Enabled = false;
                        bWriteNVM.Enabled = breadNVM.Enabled = false;
                        
                        button18.Enabled = false;
                    }
                    break;
                case TActionList.RoomSelected:
                    {
                        bAddRoom.Enabled = false;
                        bAddDevice.Enabled = true;
                        bAddSignal.Enabled = false;
                        bCopy.Enabled = true;
                        bDelete.Enabled = true;
                        writeNVMToolStripMenuItem.Enabled = false;
                        readNVMToolStripMenuItem.Enabled = false;
                        MIReset.Enabled = false;
                        flashToolStripMenuItem.Enabled = false;
                        bWriteNVM.Enabled = breadNVM.Enabled = false;
                        

                        button18.Enabled = false;
                    }
                    break;
                case TActionList.SignalSelected:
                    {
                        bAddRoom.Enabled = false;
                        bAddSignal.Enabled = false;
                        bAddDevice.Enabled = false;
                        bCopy.Enabled = true;
                        bDelete.Enabled = true;
                        writeNVMToolStripMenuItem.Enabled = false;
                        readNVMToolStripMenuItem.Enabled = false;
                        MIReset.Enabled = false;
                        flashToolStripMenuItem.Enabled = false;
                        bWriteNVM.Enabled = breadNVM.Enabled = false;
                        button18.Enabled = false;
                    }
                    break;
                case TActionList.ConnectedCom:
                    {
                        
                       
                        bScan.Enabled = true;
                       
                        bSetTime.Enabled = true;
                        button15.Enabled = true;
                        button16.Enabled = true;
                        button1.Enabled = true;
                        button18.Enabled = true;
                        
                    }
                    break;
            }
        }

        long _FlashStartTime;
        
        public Form1()
        {
            InitializeComponent();
            _housecfg = null;
            _housecfg_old = "";
         
            CopyNode = null;



            comboBox1.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            if (comboBox1.Items.Count > 0)
            {
                comboBox1.SelectedIndex = 0;
            }
           
        }

        private void PopulateTree()
        {
            tv.Nodes.Clear();
            TreeNode t = new TreeNode();
            t.Tag = _housecfg;
            t.Text = _housecfg.Name;
            t.ImageIndex = 0;
            t.SelectedImageIndex = 0;
            tv.Nodes.Add(t);
            foreach (Room r in _housecfg.mRooms)
            {
                tvAddRoom(r, t);
            }
            t.Expand();
        }

        private void tvClrCheckboxesRec(TreeNode t)
        {
            t.Checked = false;
            foreach (TreeNode t1 in t.Nodes)
            {
                tvClrCheckboxesRec(t1);
            }
        }

        private TreeNode tvGetRecDevicebyNAD(TreeNode t, byte nad)
        {
            if (t.Tag is Device)
            {
                if ((t.Tag as Device).NAD == nad)
                {
                    return t;
                }
            }
            
            foreach (TreeNode t1 in t.Nodes)
            {
                if (t1.Tag is Device)
                {
                    if ((t1.Tag as Device).NAD == nad)
                    {
                        return t1;
                    }
                }
                if (t1.Nodes.Count > 0)
                {
                    TreeNode t2 = tvGetRecDevicebyNAD(t1, nad);
                    if (t2 != null)
                    {
                        return t2;
                    }
                }
            }
            return null;
        }

        private TreeNode tvGetDevicebyNAD(byte nad)
        {
            return tvGetRecDevicebyNAD(tv.Nodes[0], nad);
        }

        private TreeNode tvGetFirstRoom()
        {

            if (tv.Nodes[0].Nodes.Count == 0)
            {
                Room r = new Room();
                _housecfg.mRooms.Add(r);
                tvAddRoom(r, tv.Nodes[0]);
            }
            return tv.Nodes[0].Nodes[0];
        }

        private void tvAddSignal(Signal s, TreeNode tr)
        {
            TreeNode tn = new TreeNode();
            tn.Tag = s;
            tn.Text = s.Name;
            tn.ImageIndex = 3;
            tn.SelectedImageIndex = tn.ImageIndex;
            tr.Nodes.Add(tn);
        }

        private void tvAddDevice(Device d, TreeNode tr)
        {
            TreeNode tn = new TreeNode();
            tn.Tag = d;
            tn.Text = d.Name;
            if (d.IsDeviceThermostat()){
                tn.ImageIndex = 2;
            } else {
                tn.ImageIndex = 17;
            }
            
            d.SetTvNode(tn);
            tn.SelectedImageIndex = tn.ImageIndex;
            tr.Nodes.Add(tn);
          //  tn.Collapse(); 
        }

        private void tvAddRoom(Room rm, TreeNode tr)
        {
            TreeNode tn = new TreeNode();
            tn.Tag = rm;
            tn.Text = rm.Name;
            tn.ImageIndex = 1;
            tn.SelectedImageIndex = tn.ImageIndex;
            tr.Nodes.Add(tn);
            foreach (Device d in rm.mDevices)
            {
                tvAddDevice(d, tn);
            }
            tn.Expand();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Room rm = new Room();
            _housecfg.mRooms.Add(rm);
            tvAddRoom(rm,tv.SelectedNode); 
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Device w = new Device();

            Room r = tv.SelectedNode.Tag as Room;
            r.mDevices.Add(w);
            tvAddDevice(w, tv.SelectedNode);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Signal s = new Signal();
            Device w = tv.SelectedNode.Tag as Device;
            w.Signals.Add(s);
            tvAddSignal(s, tv.SelectedNode);
        }

        private void House_AfterSelect(object sender, TreeViewEventArgs e)
        {
            Prop.SelectedObject = tv.SelectedNode.Tag;
           
            switch (tv.SelectedNode.Level)
            {
                case 0://house
                    Action(TActionList.HouseSelected);
                    break;
                case 1://room
                    Action(TActionList.RoomSelected);
                    break;
                case 2://device
                    Action(TActionList.DeviceSelected);
                    break;
                case 3://signal
                    Action(TActionList.SignalSelected);
                    
                    break;

            }
        }
        
        private void Prop_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            tv.SelectedNode.Text = (tv.SelectedNode.Tag as VisibleElement).Name;
           
            Prop.Refresh();
        }

        private void SaveCFG()
        {
            #region store xml

                //backup
                //           
                XmlSerializer serializer = new XmlSerializer(typeof(House));

                // Create a FileStream to write with.
                //Stream writer = new FileStream(GetHouseCfgFname(), FileMode.Create);
                MemoryStream ms = new MemoryStream();

                serializer.Serialize(ms, _housecfg);

                string newcfg = Stream2String(ms);

                if (_housecfg_old != newcfg)
                {
                    System.IO.File.Copy(GetHouseCfgFname(), GetHouseCfgBakFname(), true);

                    Stream fs = new FileStream(GetHouseCfgFname(), FileMode.Create);
                    ms.Position = 0;
                    fs.Write(ms.ToArray(), 0,(int) ms.Length);
                    fs.Close();
                 }

                    
                
                ms.Close();

                //out1.AppendText("XML stored!\n");
                //bChanged = false;
            
            #endregion
        }

        private string Stream2String(Stream st)
        {
            string s = "";
            st.Position = 0;
            StreamReader sr = new StreamReader(st);

            s = sr.ReadToEnd();
            return s;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Confirm Delete","Question",MessageBoxButtons.YesNo,MessageBoxIcon.Warning) != System.Windows.Forms.DialogResult.Yes){
                return;
            }

            TreeNode t = tv.SelectedNode;
            if (t == null)
            {
                return;
            }
            switch (t.Level)
            {
                case 1://room
                    Room r = t.Tag as Room;
                    _housecfg.mRooms.Remove(r);
                    break;
                case 2://device
                    Device w = t.Tag as Device;
                    Room r1 = t.Parent.Tag as Room;
                    r1.mDevices.Remove(w);
                    break;
                case 3://signal
                    Signal ly = t.Tag as Signal;
                    Device w1 = t.Parent.Tag as Device;
                    w1.Signals.Remove(ly);
                    break;
    
            }
            tv.Nodes.Remove(t);
        }

        private string GetHouseCfgFname()
        {
            return Application.StartupPath + "\\house.xml";
        }

        private string GetHouseCfgBakFname()
        {
            return Application.StartupPath + "\\house_bak.xml";
        }

        private void LoadCfg()
        {
            #region read xml
           

            if (File.Exists(GetHouseCfgFname()))
            {
                Stream reader = new FileStream(GetHouseCfgFname(), FileMode.Open);

                _housecfg_old = Stream2String(reader);
                reader.Position = 0;
                //out1.AppendText("Reading XML...");
                try
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(House));
                    _housecfg = serializer.Deserialize(reader) as House;

                    //out1.AppendText("OK\n");
                }
                catch
                {
                    //out1.AppendText("Error!\n");
                    MessageBox.Show("Error in loading of XML configuration file!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                }
                finally
                {
                    reader.Close();
                }
            }
            else{
                _housecfg = new House();
               
            }
             PopulateTree();
            #endregion
        }
       
        private void button7_Click(object sender, EventArgs e)
        {
            CopyNode = tv.SelectedNode;
            bPaste.Enabled = true;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            TreeNode t = tv.SelectedNode;
            int lt = t.Level;
            if (CopyNode.Level  == (lt+1))
            {
                switch (t.Level)
                {
                    case 0://copy room
                        Room r = new Room(CopyNode.Tag as Room);
                        r.Name = "Copy of " + r.Name;
                        _housecfg.mRooms.Add(r);
                        tvAddRoom(r, t);
                        break;
                    case 1://copy device
                        Device d = new Device(CopyNode.Tag as Device);
                        Room pr = t.Tag as Room;
                        pr.mDevices.Add(d);
                        tvAddDevice(d, t);
                        break;
                    case 2://copy signal
                        Signal s = new Signal(CopyNode.Tag as Signal);
                        Device dv = t.Tag as Device;
                        dv.Signals.Add(s);
                        tvAddSignal(s, t);
                        break;

                }
            }
        }
       
       //delegate void CrosThreadLog(string text);  
        delegate void CrosThreadLog(byte[] msg, int rssi);

        private string GetMsgName(byte id)
        {
            string s ;
            switch (id)
            {
                case 1:
                    s = "Global_Time";
                    break;
                case 2:
                    s = "Air_Sensor";
                    break;
                case 3:
                    s = "Switch_Ctl";
                    break;
                case 4:
                    s = "Actuator";
                    break;
                case 5:
                    s = "PIR_Sensor";
                    break;
                case 6:
                    s = "Status_Info";
                    break;
                case 7:
                    s = "Energy_Info";
                    break;
                case 8:
                    s = "Energy_Clear";
                    break;
                case 0xf0:
                    s = "Get_Seed";
                    break;
                case 0xf1:
                    s = "Send_Key";
                    break;
                case 0xf2:
                    s = "Erase_Flash";
                    break;
                case 0xf3:
                    s = "Write_Data";
                    break;
                case 0xf4:
                    s = "Validate";
                    break;
                case 0xf5:
                    s = "ECU_Reset";
                    break;
                case 0xf6:
                    s = "Read_Data";
                    break;
                case 0xf7:
                    s = "Mode";
                    break;
                   case 0xf8:
                    s = "Invalidate";
                    break;
                case 0xf9:
                    s = "Com_Control";
                    break;
                case 0xff:
                    s = "Neg_Resp";
                    break;
                default:
                    s = "Unknown";
                    break;
            }

            while (s.Length < 13)
            {
                s += " ";
            }
            return s;
        }

        private void DoLog(byte[] msg, int rssi)
        {

            if (this.lvLog.InvokeRequired)
            {
                CrosThreadLog cc = new CrosThreadLog(DoLog);
                this.Invoke(cc, new object[] { msg, rssi });
            }
            else
            {
                if (lvLog.Lines.Count() > 1000)
                {
                    lvLog.Text ="";//remove first one
                }

                string s = "";
                DateTime t = DateTime.Now;
                  string ss = "";
                s = t.Hour.ToString("D2") + ":" + t.Minute.ToString("D2") + ":" + t.Second.ToString("D2") + ":" + t.Millisecond.ToString("D3");
                if (rssi == 256)
                {
                    s += "  Tx       ";
                }
                else
                {
                    s += "  Rx  " + rssi.ToString("D2") +"  ";
                    ss =_housecfg.Parse(msg,rssi);
                }

                //len
                s += msg[0].ToString("X2"); s += "  ";
                s += msg[1].ToString("X2"); s += "  ";
                if (ss != "")
                {
                    s += ss;
                   
                }
                else
                {
                    s += msg[2].ToString("X2"); s += "  ";
                    s += msg[3].ToString("X2"); s += "  ";

                    //name
                    s += GetMsgName(msg[4]);

                    //data

                    int l = msg[0] - 3;
                    for (int i = 0; i < l; i++)
                    {
                        s += msg[i + 4].ToString("X2") + " ";
                    }
                   
                }
                s += "\r\n";
                
                lvLog.AppendText(s) ;//lvLog.AppendText("\n");
                Prop.Refresh();
                
            }
            
            
        }

        private void sport_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] buff = new byte[2];
           
            while ((sport.IsOpen) && (sport.BytesToRead > 0))
            {
                sport.Read(buff, 0, 1);//read one byte
                if (spf != null)
                {
                    spf.SerialProtocolRxData(buff[0]);
                }
            }
        }
       
        private void button9_Click(object sender, EventArgs e)
        {
            opendia.Filter = "Hex files|*.hex";
            if (opendia.ShowDialog() == DialogResult.OK)
            {
                spf.FlashApplication(opendia.FileName, 255, GetCNAD());
               
                timer1.Enabled = true;
                _FlashStartTime = 0;
            }
            
            toolStripStatusLabel1.Text = "Flashing...";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (spf != null)
            {
                _FlashStartTime += timer1.Interval;
                if ((spf.GetMode() == SerialProtocol.TCOMMode.Flash) && ((_FlashStartTime % 500) ==0))
                {
                    long speed = spf.GetFlashedSizeInBytes() * 1000 / _FlashStartTime;
                    toolStripStatusLabel3.Text = speed.ToString() + " B/s";
                    toolStripStatusLabel4.Text = spf.GetlocalRSSI().ToString() + " dBm  " + spf.GetremoteRSSI() + " dBm  ";
                    
                    toolStripProgressBar1.Value = (int)spf.GetProgress();
                    toolStripStatusLabel2.Text = spf.GetStateName();
                    toolStripStatusLabel5.Text = spf.GetRetryNumber().ToString()+" Retries";
                }
                spf.SerialTick(timer1.Interval);
               
                if (spf.IsCMDFinshedOK())
                {
                    timer1.Enabled = false;
                    toolStripProgressBar1.Value = (int)spf.GetProgress();
                    toolStripStatusLabel2.Text = spf.GetStateName();
                    toolStripStatusLabel5.Text = spf.GetRetryNumber().ToString() + " Retries";
                }
                else if (spf.IsCMDFinshedNOK())
                {
                    timer1.Enabled = false;
                    toolStripStatusLabel1.Text = spf.GetError();
                    toolStripStatusLabel2.Text = spf.GetStateName();
                    toolStripStatusLabel5.Text = spf.GetRetryNumber().ToString() + " Retries";
                }
            }
        }

        private UInt32 GetNWID()
        {
            return _housecfg.mNetworkID;
        }

        private byte GetCNAD()
        {
            byte res = 0;
            if (tv.SelectedNode.Tag is Device)
            {
                res = (tv.SelectedNode.Tag as Device).NAD; 
            }
            return res;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (spf != null)
            {
                _bw = new Scanner(spf, 20);
                timer2.Start();
                tvClrCheckboxesRec(tv.Nodes[0]);
            }
        }

        private void FillDevces(Scanner sc)
        {
            TreeNode tns = tv.SelectedNode;
            tv.SelectedNode = null;
            for (byte i = 0; i < 255; i++)
            {
                long dc = sc.GetDevCaps(i);
                if (dc != 0)
                {
                    Device d ;
                    TreeNode tn = tvGetDevicebyNAD(i);
                    if (tn == null)
                    {
                        tn = tvGetFirstRoom();
                        d = new Device();
                        d.NAD = i;
                        d.Name = "Device " + i.ToString();
                        (tn.Tag as Room).mDevices.Add(d);
                        tvAddDevice(d, tn);
                    }
                    else
                    {
                        d = tn.Tag as Device;
                    }
                    d.SetRSSI(sc.GetDevRSSI(i));
                    d.mDevCaps = sc.GetDevCaps(i);
                    tn.Checked = true;
                }
            }
            tv.SelectedNode = tns;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

            if (_bw != null)
            {
                _bw.Tick(timer2.Interval);
                toolStripProgressBar1.Value = _bw.Progress();
                if (_bw.IsFinshed())
                {
                    timer2.Stop();
                    if (_bw is Scanner)
                    {
                        FillDevces(_bw as Scanner);
                        toolStripStatusLabel5.Text = (_bw as Scanner).GetNumDevFound().ToString() + " Found";
                    }
                    else if (_bw is NVMreader)
                    {
                        if (tv.SelectedNode.Tag is Device)
                        {
                            Device d = tv.SelectedNode.Tag as Device;
                            d.NVM = (_bw as NVMreader)._mem;
                            Action(TActionList.DeviceSelected);
                        }
                    } 
                    _bw = null;
                }
            }

        }

        private void button13_Click(object sender, EventArgs e)
        {
            lvLog.Text= "";
        }

        private void button14_Click(object sender, EventArgs e)
        {
            spf.SetTime(255,0);
        }

        private void button15_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[10];

            data[0] = (byte)RelayValue.Value;//tx power reg
         
            byte cnad = GetCNAD();

            //len,nad,nad,res,cmd,wdbid,data...
            spf.WDBID(5, data, 1, 255, cnad,true,true);
            // timer1.Interval = 20;
            timer1.Enabled = true;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[10];

            data[0] = 0x0;//tx power reg

            byte cnad = GetCNAD();

            //len,nad,nad,res,cmd,wdbid,data...
            spf.WDBID(5, data, 1, 255, cnad,true,true);
            // timer1.Interval = 20;
            timer1.Enabled = true;
        }

        private void button18_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[10];

            data[0] = 0x7;

            byte cnad = GetCNAD();
           // spf.RDBID(2, data, 1, 255, cnad);
            //len,nad,nad,res,cmd,wdbid,data...
            spf.RDBID(5, data, 1, 255, cnad);
            // timer1.Interval = 20;
            timer1.Enabled = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadCfg();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (sport.IsOpen)
            {
                sport.Close();
            }
            SaveCFG();
        }

        private void readNVMToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (spf != null)
            {
                if (tv.SelectedNode.Tag is Device)
                {
                    Device d = tv.SelectedNode.Tag as Device;
                    _bw = new NVMreader(spf, d.NAD);
                    timer2.Start();
                }
            
            }

#if false
            #region store xml2
            //saveFileDialog1.FileName = hs.Name + ".xml";

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(NVMMem));

                // Create a FileStream to write with.
                Stream writer = new FileStream(saveFileDialog1.FileName, FileMode.Create);

                NVMMem mm = new NVMMem();
                byte[] bd = new byte[5];
                bd[0] = 1;
                bd[1] = 4;
                bd[2] = 254;
                bd[3] = 255;
                mm.Add("b1", 1, 4, bd);
                mm.Add("b2", 2, 2, bd);

                serializer.Serialize(writer, mm);
                writer.Close();

                //out1.AppendText("XML stored!\n");
                //bChanged = false;
            }
            #endregion
#endif
        }

        private void button10_Click_1(object sender, EventArgs e)
        {
            if (comboBox1.Text == "") return;

            try
            {
                if (sport.IsOpen)
                {
                    sport.Close();
                }
                sport.PortName = comboBox1.Text;
                sport.Open();
                toolStripStatusLabel1.Text = "Connected";

                Action(TActionList.ConnectedCom);

                spf = new SerialProtocol(sport, DoLog, GetNWID());
                //Form2 f2 = new Form2();
                //f2.Show();
            }
            catch
            {
            }
        }
 
        private void writeNVMToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (spf != null)
            {
                if (tv.SelectedNode.Tag is Device)
                {
                    Device d = tv.SelectedNode.Tag as Device;
                    _bw = new NVMwriter(spf, d.NAD, d.NVM);
                    timer2.Start();
                }
            }
        }

        private void MIReset_Click(object sender, EventArgs e)
        {
             if (tv.SelectedNode.Tag is Device)
                {
                    Device d = tv.SelectedNode.Tag as Device;
                    spf.ECUReset(255, d.NAD);
                    timer1.Start();
                }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            spf.ClrEnergy(255, 0);
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            if (_housecfg != null)
            {
                _housecfg.RefreshTxIcon();
            }
        }

     
    }

   

}
