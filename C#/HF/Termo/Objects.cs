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

    #region Objects



    public class VisibleElement : Object
    {
        string mName;

        public VisibleElement()
        {
            mName = "";
        }

        public VisibleElement(string n)
        {
            mName = n;
        }
        [System.ComponentModel.DisplayName("Name")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public string Name
        {
            get { return mName; }
            set { mName = value; }
        }

    }

    public class Signal : VisibleElement
    {
        private float mvalue;
        public byte mmsgid;
        public byte mmbyteID;
        //public byte msize;
        public float mscale;
        public float moffset;
        public string mresolution;

        public float GetValue()
        {
            return mvalue;
        }
       
        public string Parse(byte[] msg)
        {
            if (msg[4] == mmsgid)
            {
                int i = 5;
                while (i< msg[0])
                {
                    int len = (msg[i] & 0x0F);
                    if (msg[i]==mmbyteID) 
                    {
                        //found signal ID
                        switch (len)
                        {
                            case 1:
                                mvalue = msg[i+1];
                                break;
                            case 2:
                                int v= msg[i+2];
                                v *= 256;
                                v += msg[i + 1];
                                mvalue = v;
                                break;
                            case 4:
                                long vl= msg[i+4];
                                vl *= 256;
                                vl += msg[i + 3];
                                vl *= 256;
                                vl += msg[i + 2];
                                vl *= 256;
                                vl += msg[i + 1];
                                mvalue = vl;
                                break;
                        }
                        mvalue *= mscale;
                        mvalue += moffset;
                        return GetSigNameAndValue();
                    }
                    i = i +len +1;
                }
            }
            return "";
        }

        public Signal()
        {
            mscale = 1;
            mvalue = 0;
           // msize = 1;
            moffset = 0;
            mmsgid = 0;
            mmbyteID = 0;
            Name = "Signal_";
            mresolution = "";
        }

        public Signal(Signal ly)
        {
            mvalue = ly.mvalue;
            mscale = ly.mscale;
            moffset = ly.moffset;
            mmsgid = ly.mmsgid;
           // msize = ly.msize;
            mmbyteID = ly.mmbyteID;
            Name = ly.Name;
            mresolution = ly.mresolution;
        }

        public string GetSigNameAndValue()
        {
            return Name + ": " + Value + ";";
        }

        [System.ComponentModel.DisplayName("Value")]
        [System.ComponentModel.Category("Info")]
        //[System.ComponentModel.ReadOnly(false)]
        public string Value
        {
            get {
                if (mscale == 1.0)
                {
                    return mvalue.ToString() + " " + mresolution;
                }
                else
                {
                    return mvalue.ToString("F1") + " " + mresolution;
                }
            }
           
        }
        [System.ComponentModel.DisplayName("Scaling")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Scale
        {
            get { return mscale; }
            set { mscale = value; }
        }
        [System.ComponentModel.DisplayName("Offset")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Offest
        {
            get { return moffset; }
            set { moffset = value; }
        }
        [System.ComponentModel.DisplayName("MessageID")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public byte MessageID
        {
            get { return mmsgid; }
            set { mmsgid = value; }
        }
        [System.ComponentModel.DisplayName("SignalID")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public byte SigID
        {
            get { return mmbyteID; }
            set { mmbyteID = value; }
        }
        
        [System.ComponentModel.DisplayName("Resolution")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public string Res
        {
            get { return mresolution; }
            set { mresolution = value; }
        }
    }

    public class Device : VisibleElement
    {
        private Collection<Signal> mSignals;
        private byte mNAD;
        private int mRSSI;
        public long mDevCaps;
        private TreeNode mtn;
        private int mrxflashtime;

        public void SetRSSI(int r)
        {
            mRSSI = r;
        }

        private Collection<NVMBlock> mnvblocks;

        private int GetImageIdndex(Boolean bRx)
        {
            int i;
            if (IsDeviceActuator() == true)
            {
                if (bRx == true)
                {
                    i = 18;
                }
                else
                {
                    i = 17;
                }
            }
            else
            {
                if (bRx == true)
                {
                    i = 13;
                }
                else
                {
                    i = 2;
                }
            }
            return i;
        }

        public bool IsDeviceActuator()
        {
            return ((mDevCaps & (0x8 | 0x10)) != 0);
        }
        public void SetTvNode(TreeNode t)
        {
            mtn = t;
        }
        public bool IsDeviceThermostat()
        {
            return ((mDevCaps & (0x2)) != 0);
        }
        public string Parse(byte[] msg, int rssi)
        {
            if (msg[2] == mNAD)
            {
                string dd="";
                mRSSI = rssi;

                foreach (Signal s in mSignals)
                {
                    dd += s.Parse(msg);
                }
                if (mtn != null)
                {
                    mrxflashtime = 2;
                    mtn.SelectedImageIndex = mtn.ImageIndex = GetImageIdndex(true);
                }
                if (dd != "")
                {
                    return this.Name + "::" + dd;
                }
                return "";
            }
            return "";
        }

        public Device()
        {
            mNAD = 254;
            mSignals = new Collection<Signal>();
           
            mnvblocks = new Collection<NVMBlock>();
            Name = "Device_";
            mtn = null;
            mrxflashtime = 0;
        }

        public void RefreshTxIcon()
        {
            if (0 != mrxflashtime)
            {
                mrxflashtime--;
                if ((0 == mrxflashtime) && (mtn != null))
                {
                    mtn.SelectedImageIndex = mtn.ImageIndex = GetImageIdndex(false);
                }
            }
        }

        public float GetEnergy()
        {
            float e = 0;
            foreach (Signal s in mSignals)
            {
                if ((s.Name.Contains("Energy")) || (s.Name.Contains("Енергия")))
                {
                    e += s.GetValue();
                }
            }
            return e;
        }

        public Device(Device w)
        {
            Name = w.Name;
            mNAD = w.mNAD;
            mSignals = new Collection<Signal>();
            mtn = w.mtn;
            foreach (Signal ly in w.mSignals)
            {
                Signal ln = new Signal(ly);
                mSignals.Add(ln);
            }
            mnvblocks = new Collection<NVMBlock>();
            foreach (NVMBlock b in w.NVM)
            {
                NVMBlock b1 = new NVMBlock(b);
                mnvblocks.Add(b1);
            }
            mrxflashtime = 0;
        }

        [System.ComponentModel.DisplayName("NAD")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]

        public byte NAD
        {
            get { return mNAD; }
            set { mNAD = value; }
        }

         [System.ComponentModel.DisplayName("NvM")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]

        public Collection<NVMBlock> NVM
        {
            get { return mnvblocks; }
            set { mnvblocks = value; }
        }

        [System.ComponentModel.DisplayName("Signals")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public Collection<Signal> Signals
        {
            get { return mSignals; }
            set {mSignals = value;}
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("RSSI[dBm]")]
        public int RSSI
        {
            get
            {
               // double rs = (0.55 * mRSSI) - 118.5;
              //  int pw = (int)rs;
                return mRSSI;
            }
            //set { mRSSI = value; }
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Device Capabilities")]
        public string DevCaps
        {
            get
            {
                string s = "";
                if (0!= (mDevCaps & 1))
                {
                    s += "RTCLOCK,";
                }
                if (0!= (mDevCaps & 2))
                {
                    s += "TERM_REG,";
                }
                if (0!= (mDevCaps & 4))
                {
                    s += "PIR,";
                }
                if (0!= (mDevCaps & 8))
                {
                    s += "RELAY,";
                }
                if (0!= (mDevCaps & 0x10))
                {
                    s += "PWM,";
                }
                if (0!= (mDevCaps & 0x20))
                {
                    s += "SWITCH1,";
                }
                if (0!= (mDevCaps & 0x40))
                {
                    s += "SWITCH2,";
                }

                return s;
            }
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Values")]
        public string Values
        {
            get
            {
                string st="";
                foreach (Signal s in mSignals)
                {
                    st += s.Name + ": " + s.Value + "; ";
                }
                return st;
            }
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Energy")]
        public string Energy
        {
            get
            {
                return GetEnergy().ToString("F1")+" kWh";
            }
        }


    }

    public class Room : VisibleElement
    {
        public Collection<Device> mDevices;

        public string Parse(byte[] msg, int rssi)
        {
            string d1;
            foreach (Device d in mDevices)
            {
                d1 = d.Parse(msg,rssi);
                if (d1 != "")
                {
                    return this.Name+"."+ d1;
                }
            }
            return "";
        }

        public void RefreshTxIcon()
        {
            foreach (Device d in mDevices)
            {
                d.RefreshTxIcon();
            }
        }
        public float GetEnergy()
        {
            float e = 0;
            foreach (Device d in mDevices)
            {

                e += d.GetEnergy();
                
            }
            return e;
        }

        public Room()
        {
            Name = "Room_";
            //mHeight = 2.5f;
            mDevices = new Collection<Device>();
        }

        public Room(Room rm)
        {

            mDevices = new Collection<Device>();
            Name = rm.Name;
            foreach (Device w in rm.mDevices)
            {
                Device wn = new Device(w);
                mDevices.Add(wn);
            }
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Energy")]
        public string Energy
        {
            get
            {
                return GetEnergy().ToString("N1")+" kWh";
            }
        }

    }

    public class House : VisibleElement
    {
        public Collection<Room> mRooms;
        public UInt32 mNetworkID;
        private byte _maxnad;

        public string Parse(byte[] msg, int rssi)
        {
            string d="";
            foreach (Room r in mRooms)
            {
                d = r.Parse(msg,rssi);
                if (d != ""){
                return d;}
            }
            return "";
        }

        public void RefreshTxIcon()
        {
            foreach (Room r in mRooms)
            {
                r.RefreshTxIcon();
            }
        }

        private float GetEnergy()
        {
            float e = 0;
            foreach (Room rm in mRooms)
            {

                e += rm.GetEnergy();

            }
            return e;
        }

        public House()
        {
            Name = "House";
            mNetworkID = 0;
            mRooms = new Collection<Room>();
        }

        public House(House h)
        {
            Name = h.Name;
            mNetworkID = h.mNetworkID;
            mRooms = new Collection<Room>();
            foreach (Room r in h.mRooms)
            {
                Room nr = new Room(r);
                mRooms.Add(nr);
            }
        }

        private void CheckRoom(Room r)
        {
            foreach (Device d in r.mDevices)
            {
                if (_maxnad < d.NAD)
                {
                    _maxnad = d.NAD;
                }
            }
        }

        public byte GetMaxNAD()
        {
            _maxnad = 0;
            foreach (Room r in mRooms)
            {
                CheckRoom(r);
            }
            return _maxnad;
        }

        [System.ComponentModel.DisplayName("Network ID")]
        [System.ComponentModel.Category("Configuration")]
        [System.ComponentModel.ReadOnly(false)]
        public UInt32 PowerLoss
        {
            get
            {
                return mNetworkID;
            }
            set
            {
                mNetworkID = value;
            }
        }

        [System.ComponentModel.Category("Information")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Energy")]
        public string Energy
        {
            get
            {
                return GetEnergy().ToString("N1")+" kWh";
            }
        }

    }

    public class NVMBlock : Object
    {
        private string _name;
        private byte _ID;
        private byte _len;
        private int[] _data;


        public NVMBlock()
        {
            _name = "";
            _len = 0;
            _ID = 0;
            _data = new int[64];
        }

        public byte DataByte(int i)
        {
            if (i < _len)
            {

                return (byte)_data[i];
            }
            else return 0;
        }

        public int[] DataBytes()
        {
            return _data;
        }

        public NVMBlock(string n, byte ID, byte len, byte[] data)
        {
            _name = n;
            _data = new int[len];
            _len = len;
            _ID = ID;
            for (int i = 0; i < _len; i++)
            {
                _data[i] = data[i];
            }
        }

        public NVMBlock(NVMBlock nvb)
        {
            _name = nvb._name;
            _len = nvb._len;
            _ID = nvb._ID;
            _data = new int[nvb._len];
            for (int i = 0; i < _len; i++)
            {
                _data[i] = nvb._data[i];
            }
        }

        public override string ToString()
        {
            string s = "";
            for (int i = 0; i < _len; i++)
            {
                s += _data[i].ToString() + ",";

            }
            return s;
        }

        public Boolean FromString(string s)
        {
            int index = 0;
            while ((s.Length > 0) && (index < _len))
            {
                int i = s.IndexOf(",");
                string sd = s.Substring(0, i);
                _data[index] = byte.Parse(sd);
                index++;
                s = s.Remove(0, i + 1);
            }
            
            return true;
        }

        [System.ComponentModel.DisplayName("Name")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public string Name
        {
            get { return _name; }
            set { _name = value;}
        }

        [System.ComponentModel.DisplayName("ID")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public byte ID
        {
            get { return _ID; }
            set {_ID= value;}
        }
        [System.ComponentModel.DisplayName("Lenght")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public byte Lenght
        {
            get { return _len; }
            set { _len = value; }
        }

        [System.ComponentModel.DisplayName("Data")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public string Data
        {
            get { return ToString(); }
            set { FromString( value); }
        }
    }

    public class NVMMem : Object
    {
        public Collection<NVMBlock> _blocks;

        public NVMMem()
        {
            _blocks = new Collection<NVMBlock>();
        }

        public NVMMem(NVMMem m)
        {
            _blocks = new Collection<NVMBlock>();
            foreach (NVMBlock b in m._blocks)
            {
                _blocks.Add(b);
            }
        }

        public void Add(string n, byte ID, byte len, byte[] data)
        {
            NVMBlock b = new NVMBlock(n, ID, len, data);
            _blocks.Add(b);
        }

        public Collection<string> ToStringArray()
        {
            Collection<string> sc = new Collection<string>();

            for (int i = 0; i < _blocks.Count; i++)
            {
                sc.Add( _blocks[i].ToString());
            }
            return sc;
        }

        public Boolean FromStringArray(Collection<string> sc)
        {
            if (sc.Count != _blocks.Count)
            {
                return false;
            }
            for (int i = 0; i <_blocks.Count ; i++)
            {
                _blocks[i].FromString(sc[i]);
            }
            return true;
        }
    }

    #endregion

}