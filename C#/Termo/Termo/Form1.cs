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

namespace Termo
{
    public partial class Form1 : Form
    {
        House hs;

        TreeNode CopyNode;
        
        public Form1()
        {
            InitializeComponent();

            hs = new House();
            PopulateTree();
            CopyNode = null;
            
        }

        private void PopulateTree()
        {
            tv.Nodes.Clear();
            TreeNode t = new TreeNode();
            t.Tag = hs;
            t.Text = hs.Name;
            tv.Nodes.Add(t);
            foreach (Room r in hs.mRooms)
            {
                tvAddRoom(r, t);
            }
        }

        private void tvAddRoom(Room rm, TreeNode tr)
        {
            
            TreeNode tn = new TreeNode();
            tn.Tag = rm;
            tn.Text = rm.Name;
            tr.Nodes.Add(tn);
            foreach (Wall w in rm.mWalls)
            {
                tvAddWall(w, tn);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Room rm = new Room();
            hs.mRooms.Add(rm);
            tvAddRoom(rm,tv.SelectedNode); 
        }

        private void tvAddWall(Wall w, TreeNode tn)
        {
            TreeNode tn1 = new TreeNode();
            tn1.Text = w.Name;
            tn1.Tag = w;
            tn.Nodes.Add(tn1);
            foreach (Layer ly in w.mLayers)
            {
                tvAddLayer(ly, tn1);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Wall w = new Wall();
            Room r = tv.SelectedNode.Tag as Room;
            r.mWalls.Add(w);
            tvAddWall(w, tv.SelectedNode);
        }

        private void tvAddLayer(Layer ly, TreeNode tn)
        {         
            TreeNode tn1 = new TreeNode();
            tn1.Text = ly.Name;
            tn1.Tag = ly;
            tn.Nodes.Add(tn1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Layer ly = new Layer();
            Wall w = tv.SelectedNode.Tag as Wall;
            w.mLayers.Add(ly);
            tvAddLayer(ly, tv.SelectedNode);
        }

        private void House_AfterSelect(object sender, TreeViewEventArgs e)
        {
            Prop.SelectedObject = tv.SelectedNode.Tag;
            hs.CalcPowerLoss();
            switch (tv.SelectedNode.Level)
            {
                case 0:
                    button1.Enabled = true;
                    button4.Enabled = false;
                    button2.Enabled = false;
                    button7.Enabled = true;
                    button3.Enabled = false;
                    break;
                case 1:
                    button1.Enabled = false;
                    button4.Enabled = true;//wall
                    button2.Enabled = false;
                    button7.Enabled = true;
                    button3.Enabled = true;
                    break;
                case 2:
                    button1.Enabled = false;
                    button4.Enabled = false;//wall
                    button2.Enabled = true;
                    button7.Enabled = true;
                    button3.Enabled = true;
                    break;
                case 3:
                    button1.Enabled = false;
                    button2.Enabled = false;
                    button4.Enabled = false;//wall
                    button7.Enabled = true;
                    button3.Enabled = true;
                    
                    break;

            }
        }
        
        private void Prop_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            tv.SelectedNode.Text = (tv.SelectedNode.Tag as VisibleElement).Name;
            hs.CalcPowerLoss();
            Prop.Refresh();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            #region store xml
            //saveFileDialog1.FileName = hs.Name + ".xml";

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(House));

                // Create a FileStream to write with.
                Stream writer = new FileStream(saveFileDialog1.FileName, FileMode.Create);

                serializer.Serialize(writer, hs);
                writer.Close();

                //out1.AppendText("XML stored!\n");
                //bChanged = false;
            }
            #endregion
        }

        

        private void button3_Click(object sender, EventArgs e)
        {
            TreeNode t = tv.SelectedNode;
            if (t == null)
            {
                return;
            }
            switch (t.Level)
            {
                case 1://room
                    Room r = t.Tag as Room;
                    hs.mRooms.Remove(r);
                    break;
                case 2://wall
                    Wall w = t.Tag as Wall;
                    Room r1 = t.Parent.Tag as Room;
                    r1.mWalls.Remove(w);
                    break;
                case 3://layer
                    Layer ly = t.Tag as Layer;
                    Wall w1 = t.Parent.Tag as Wall;
                    w1.mLayers.Remove(ly);
                    break;
    
            }
            tv.Nodes.Remove(t);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            #region read xml
            // Create a FileStream .
            
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Stream reader = new FileStream(openFileDialog1.FileName, FileMode.Open);

                //out1.AppendText("Reading XML...");
                try
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(House));
                    hs = serializer.Deserialize(reader) as House;

                    PopulateTree();
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
                saveFileDialog1.FileName = openFileDialog1.FileName;
            }
            #endregion
        }

        private void button7_Click(object sender, EventArgs e)
        {
            CopyNode = tv.SelectedNode;
            button8.Enabled = true;
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
                        hs.mRooms.Add(r);
                        tvAddRoom(r, t);
                        break;
                    case 1://copy wall
                        Wall w = new Wall(CopyNode.Tag as Wall);
                        Room pr = t.Tag as Room;
                        pr.mWalls.Add(w);
                        tvAddWall(w,t);
                        break;
                    case 2://copy layer
                        Layer ly = new Layer(CopyNode.Tag as Layer);
                        Wall pw = t.Tag as Wall;
                        pw.mLayers.Add(ly);
                        tvAddLayer(ly,t);
                        break;

                }
            }
        }

        
    }

    


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

    public class Layer : VisibleElement
    {
        public float mWidth;
        public float mLambda;
        

        public Layer()
        {
            mWidth = 1;
            mLambda = 1;
            Name = "Layer_";
        }
        public Layer(Layer ly)
        {
            mWidth = ly.mWidth;
            mLambda = ly.mLambda;
            Name = ly.Name;
        }
        [System.ComponentModel.DisplayName("Lambda [W/mK]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Lambda
        {
            get { return mLambda; }
            set { mLambda = value; }
        }
        [System.ComponentModel.DisplayName("Width [sm]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Width
        {
            get { return mWidth; }
            set { mWidth = value; }
        }

    }

    public class Wall : VisibleElement
    {
        public Collection<Layer> mLayers;
        public float mRsi;
        public float mRse;
        public float mWidth;
        public float mHeight;

        public float mOutTemp;
        public float mPowerLoss;

        public float CalcPowerLoss(float InTemp)
        {
            float result = 0;

            float R = mRsi + mRse;
            foreach (Layer ly in mLayers)
            {
                float wm = ly.Width;
                wm /= 100.0f;
                float rl = wm / ly.Lambda;
                R += rl;
            }
            result = 1 / R; //for 1m2 and 1 C
            result *= (InTemp - mOutTemp);
            result *= (mHeight * mWidth);
            mPowerLoss = result;
            return result;
        }

        public Wall()
        {
            mRsi = 0.13f;
            mRse = 0.04f;
            mOutTemp = -10;
            mWidth = 3;
            mHeight = 2.5f;
            mPowerLoss = 0;
            mLayers = new Collection<Layer>();
            Name = "Wall_";
        }
        public Wall(Wall w)
        {
            mRsi = w.mRsi;
            mRse = w.mRse;
            Name = w.Name;
            mWidth = w.mWidth;
            mHeight = w.mHeight;
            mOutTemp = w.mOutTemp;
            mLayers = new Collection<Layer>();
            foreach(Layer ly in w.mLayers)
            {
                Layer ln = new Layer(ly);
                mLayers.Add(ln);
            }
        }

        [System.ComponentModel.DisplayName("Rsi [m2K/W]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Rsi
        {
            get { return mRsi; }
            set { mRsi = value; }
        }
        [System.ComponentModel.DisplayName("Rse [m2K/W]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float Rse
        {
            get { return mRse; }
            set { mRse = value; }
        }
        //[System.ComponentModel.Description("Outside Temperature")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        [System.ComponentModel.DisplayName("Outside Temperature [C]")]
        public float OutTemp
        {
            get { return mOutTemp; }
            set { mOutTemp = value; }
        }
        //[System.ComponentModel.Description("Width [m]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        [System.ComponentModel.DisplayName("Width [m]")]
        public float Width
        {
            get { return mWidth; }
            set { mWidth = value; }
        }
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        [System.ComponentModel.DisplayName("Height [m]")]
        public float Height
        {
            get { return mHeight; }
            set { mHeight = value; }
        }
        [System.ComponentModel.Category("Calculation")]
        [System.ComponentModel.ReadOnly(true)]
        [System.ComponentModel.DisplayName("Power Loss [W]")]
        public string PowerLoss
        {
            get {
                int pw = (int)mPowerLoss;
                return pw.ToString(); }
        }
      
        
    }
    public class Room : VisibleElement
    {
        public Collection<Wall> mWalls;
        float mInTemp;
        //float mHeight;
        public float mPowerLoss;
        
        public float CalcPowerLoss()
        {
            mPowerLoss = 0;
            foreach (Wall w in mWalls)
            {
                mPowerLoss += w.CalcPowerLoss(mInTemp);
            }
            return mPowerLoss;
        }

        public Room()
        {
            mInTemp = 20;
            Name = "Room_";
            //mHeight = 2.5f;
            mPowerLoss = 0;
            mWalls = new Collection<Wall>();
        }

        public Room(Room rm)
        {
            mInTemp = rm.mInTemp;
            mWalls = new Collection<Wall>();
            Name = rm.Name;
            //mHeight = rm.mHeight;
            foreach (Wall w in rm.mWalls)
            {
                Wall wn = new Wall(w);
                mWalls.Add(wn);
            }
            CalcPowerLoss();
        }
        [System.ComponentModel.DisplayName("Inside Temperature [C]")]
        [System.ComponentModel.Category("Confguration")]
        [System.ComponentModel.ReadOnly(false)]
        public float InTemp
        {
            get { return mInTemp; }
            set { mInTemp = value;
                    CalcPowerLoss();
            }
        }
        //[System.ComponentModel.DisplayName("Height [m]")]
        //[System.ComponentModel.Category("Confguration")]
        //[System.ComponentModel.ReadOnly(false)]
        //public float Height
        //{
        //    get { return mHeight; }
        //    set { 
        //        mHeight = value;
         //       CalcPowerLoss();
        //    }
        //}

        [System.ComponentModel.DisplayName("Power Loss [W]")]
        [System.ComponentModel.Category("Calculations")]
        [System.ComponentModel.ReadOnly(true)]
        public string PowerLoss
        {
            get
            {
                CalcPowerLoss();
                int pw = (int)mPowerLoss;
                return pw.ToString();
            }
        }
        
    }

    public class House : VisibleElement
    {
        public Collection<Room> mRooms;
        public float mPowerLoss;

        public float CalcPowerLoss()
        {
            mPowerLoss = 0;
            foreach (Room r in mRooms)
            {
                mPowerLoss += r.CalcPowerLoss();
            }
            return mPowerLoss;
        }

        public House()
        {
            Name = "House";
            mPowerLoss = 0;
            mRooms = new Collection<Room>();
        }

        public House(House h)
        {
            Name = h.Name;
            
            mRooms = new Collection<Room>();
            foreach (Room r in h.mRooms)
            {
                Room nr = new Room(r);
                mRooms.Add(nr);
            }
            CalcPowerLoss();
        }

        [System.ComponentModel.DisplayName("Power Loss [W]")]
        [System.ComponentModel.Category("Calculations")]
        [System.ComponentModel.ReadOnly(true)]
        public string PowerLoss
        {
            get 
            {
                int pw = (int)mPowerLoss;
                return pw.ToString();
            }
        }

    }

}
