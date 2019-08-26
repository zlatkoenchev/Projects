namespace HFHome
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.tv = new System.Windows.Forms.TreeView();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MIReset = new System.Windows.Forms.ToolStripMenuItem();
            this.readNVMToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.writeNVMToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.flashToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.bAddRoom = new System.Windows.Forms.Button();
            this.bAddSignal = new System.Windows.Forms.Button();
            this.bDelete = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.breadNVM = new System.Windows.Forms.Button();
            this.bWriteNVM = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.Prop = new System.Windows.Forms.PropertyGrid();
            this.bConnect = new System.Windows.Forms.Button();
            this.bScan = new System.Windows.Forms.Button();
            this.bPaste = new System.Windows.Forms.Button();
            this.bCopy = new System.Windows.Forms.Button();
            this.bAddDevice = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.button16 = new System.Windows.Forms.Button();
            this.button15 = new System.Windows.Forms.Button();
            this.RelayValue = new System.Windows.Forms.NumericUpDown();
            this.bSetTime = new System.Windows.Forms.Button();
            this.button18 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lvLog = new System.Windows.Forms.TextBox();
            this.button13 = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.opendia = new System.Windows.Forms.OpenFileDialog();
            this.sport = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel5 = new System.Windows.Forms.ToolStripStatusLabel();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.contextMenuStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RelayValue)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tv
            // 
            this.tv.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tv.BackColor = System.Drawing.SystemColors.Info;
            this.tv.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tv.ContextMenuStrip = this.contextMenuStrip1;
            this.tv.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tv.ForeColor = System.Drawing.SystemColors.ControlText;
            this.tv.HideSelection = false;
            this.tv.HotTracking = true;
            this.tv.ImageKey = "cigd.png";
            this.tv.ImageList = this.imageList1;
            this.tv.Location = new System.Drawing.Point(0, 0);
            this.tv.Name = "tv";
            this.tv.SelectedImageIndex = 0;
            this.tv.ShowRootLines = false;
            this.tv.Size = new System.Drawing.Size(178, 495);
            this.tv.TabIndex = 0;
            this.tv.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.House_AfterSelect);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MIReset,
            this.readNVMToolStripMenuItem,
            this.writeNVMToolStripMenuItem,
            this.flashToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(141, 92);
            // 
            // MIReset
            // 
            this.MIReset.Enabled = false;
            this.MIReset.Name = "MIReset";
            this.MIReset.Size = new System.Drawing.Size(140, 22);
            this.MIReset.Text = "Reset Device";
            this.MIReset.Click += new System.EventHandler(this.MIReset_Click);
            // 
            // readNVMToolStripMenuItem
            // 
            this.readNVMToolStripMenuItem.Enabled = false;
            this.readNVMToolStripMenuItem.Name = "readNVMToolStripMenuItem";
            this.readNVMToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.readNVMToolStripMenuItem.Text = "Read NVM";
            this.readNVMToolStripMenuItem.Click += new System.EventHandler(this.readNVMToolStripMenuItem_Click);
            // 
            // writeNVMToolStripMenuItem
            // 
            this.writeNVMToolStripMenuItem.Enabled = false;
            this.writeNVMToolStripMenuItem.Name = "writeNVMToolStripMenuItem";
            this.writeNVMToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.writeNVMToolStripMenuItem.Text = "Write NVM";
            this.writeNVMToolStripMenuItem.Click += new System.EventHandler(this.writeNVMToolStripMenuItem_Click);
            // 
            // flashToolStripMenuItem
            // 
            this.flashToolStripMenuItem.Enabled = false;
            this.flashToolStripMenuItem.Name = "flashToolStripMenuItem";
            this.flashToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.flashToolStripMenuItem.Text = "Flash";
            this.flashToolStripMenuItem.Click += new System.EventHandler(this.button9_Click);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.White;
            this.imageList1.Images.SetKeyName(0, "untitled.png");
            this.imageList1.Images.SetKeyName(1, "room2.png");
            this.imageList1.Images.SetKeyName(2, "imagesMZW9XZDP.png");
            this.imageList1.Images.SetKeyName(3, "519790-100_Pressure_Reading-512.png");
            this.imageList1.Images.SetKeyName(4, "81PJiLyKw1L__SL1500_.jpg");
            this.imageList1.Images.SetKeyName(5, "paste-icon-17_jpg.png");
            this.imageList1.Images.SetKeyName(6, "delete_button__366592.png");
            this.imageList1.Images.SetKeyName(7, "imagesH7T4NBFD.png");
            this.imageList1.Images.SetKeyName(8, "copy.png");
            this.imageList1.Images.SetKeyName(9, "67422-200.png");
            this.imageList1.Images.SetKeyName(10, "cigd.png");
            this.imageList1.Images.SetKeyName(11, "untitled.png");
            this.imageList1.Images.SetKeyName(12, "untitled2.png");
            this.imageList1.Images.SetKeyName(13, "Untitled - Copy.png");
            this.imageList1.Images.SetKeyName(14, "167130.png");
            this.imageList1.Images.SetKeyName(15, "SoftwareIcons-21-512.png");
            this.imageList1.Images.SetKeyName(16, "read-icon-14_jpg.png");
            this.imageList1.Images.SetKeyName(17, "__actuator_due__1339441.png");
            this.imageList1.Images.SetKeyName(18, "Untitled.png");
            // 
            // bAddRoom
            // 
            this.bAddRoom.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAddRoom.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bAddRoom.Enabled = false;
            this.bAddRoom.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bAddRoom.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bAddRoom.ImageIndex = 1;
            this.bAddRoom.ImageList = this.imageList1;
            this.bAddRoom.Location = new System.Drawing.Point(850, 4);
            this.bAddRoom.Name = "bAddRoom";
            this.bAddRoom.Size = new System.Drawing.Size(75, 38);
            this.bAddRoom.TabIndex = 1;
            this.bAddRoom.UseVisualStyleBackColor = false;
            this.bAddRoom.Click += new System.EventHandler(this.button1_Click);
            // 
            // bAddSignal
            // 
            this.bAddSignal.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAddSignal.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bAddSignal.Enabled = false;
            this.bAddSignal.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bAddSignal.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bAddSignal.ImageIndex = 3;
            this.bAddSignal.ImageList = this.imageList1;
            this.bAddSignal.Location = new System.Drawing.Point(850, 84);
            this.bAddSignal.Name = "bAddSignal";
            this.bAddSignal.Size = new System.Drawing.Size(75, 38);
            this.bAddSignal.TabIndex = 2;
            this.bAddSignal.UseVisualStyleBackColor = false;
            this.bAddSignal.Visible = false;
            this.bAddSignal.Click += new System.EventHandler(this.button2_Click);
            // 
            // bDelete
            // 
            this.bDelete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bDelete.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bDelete.Enabled = false;
            this.bDelete.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bDelete.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bDelete.ImageIndex = 6;
            this.bDelete.ImageList = this.imageList1;
            this.bDelete.Location = new System.Drawing.Point(850, 124);
            this.bDelete.Name = "bDelete";
            this.bDelete.Size = new System.Drawing.Size(75, 38);
            this.bDelete.TabIndex = 3;
            this.bDelete.UseVisualStyleBackColor = false;
            this.bDelete.Click += new System.EventHandler(this.button3_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.tabControl1.Location = new System.Drawing.Point(3, 5);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(941, 527);
            this.tabControl1.TabIndex = 4;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.SystemColors.Control;
            this.tabPage1.Controls.Add(this.breadNVM);
            this.tabPage1.Controls.Add(this.bWriteNVM);
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.splitContainer2);
            this.tabPage1.Controls.Add(this.bConnect);
            this.tabPage1.Controls.Add(this.bScan);
            this.tabPage1.Controls.Add(this.bPaste);
            this.tabPage1.Controls.Add(this.bCopy);
            this.tabPage1.Controls.Add(this.bAddDevice);
            this.tabPage1.Controls.Add(this.bAddRoom);
            this.tabPage1.Controls.Add(this.bAddSignal);
            this.tabPage1.Controls.Add(this.bDelete);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(933, 501);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "House";
            // 
            // breadNVM
            // 
            this.breadNVM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.breadNVM.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.breadNVM.Enabled = false;
            this.breadNVM.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.breadNVM.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.breadNVM.ImageIndex = 16;
            this.breadNVM.ImageList = this.imageList1;
            this.breadNVM.Location = new System.Drawing.Point(850, 402);
            this.breadNVM.Name = "breadNVM";
            this.breadNVM.Size = new System.Drawing.Size(75, 38);
            this.breadNVM.TabIndex = 18;
            this.breadNVM.UseVisualStyleBackColor = false;
            this.breadNVM.Click += new System.EventHandler(this.readNVMToolStripMenuItem_Click);
            // 
            // bWriteNVM
            // 
            this.bWriteNVM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bWriteNVM.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bWriteNVM.Enabled = false;
            this.bWriteNVM.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bWriteNVM.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bWriteNVM.ImageIndex = 14;
            this.bWriteNVM.ImageList = this.imageList1;
            this.bWriteNVM.Location = new System.Drawing.Point(850, 358);
            this.bWriteNVM.Name = "bWriteNVM";
            this.bWriteNVM.Size = new System.Drawing.Size(75, 38);
            this.bWriteNVM.TabIndex = 17;
            this.bWriteNVM.UseVisualStyleBackColor = false;
            this.bWriteNVM.Click += new System.EventHandler(this.writeNVMToolStripMenuItem_Click);
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button1.Enabled = false;
            this.button1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.ImageIndex = 12;
            this.button1.ImageList = this.imageList1;
            this.button1.Location = new System.Drawing.Point(850, 454);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 38);
            this.button1.TabIndex = 16;
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // splitContainer2
            // 
            this.splitContainer2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.tv);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer1);
            this.splitContainer2.Size = new System.Drawing.Size(844, 498);
            this.splitContainer2.SplitterDistance = 181;
            this.splitContainer2.TabIndex = 15;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.Prop);
            this.splitContainer1.Size = new System.Drawing.Size(656, 492);
            this.splitContainer1.SplitterDistance = 175;
            this.splitContainer1.TabIndex = 13;
            // 
            // Prop
            // 
            this.Prop.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Prop.BackColor = System.Drawing.SystemColors.Control;
            this.Prop.CategoryForeColor = System.Drawing.Color.Black;
            this.Prop.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Prop.HelpBackColor = System.Drawing.Color.Black;
            this.Prop.HelpForeColor = System.Drawing.Color.White;
            this.Prop.HelpVisible = false;
            this.Prop.LineColor = System.Drawing.Color.White;
            this.Prop.Location = new System.Drawing.Point(3, 3);
            this.Prop.Name = "Prop";
            this.Prop.Size = new System.Drawing.Size(650, 169);
            this.Prop.TabIndex = 4;
            this.Prop.ViewBackColor = System.Drawing.SystemColors.Info;
            this.Prop.ViewForeColor = System.Drawing.SystemColors.ControlText;
            this.Prop.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.Prop_PropertyValueChanged);
            // 
            // bConnect
            // 
            this.bConnect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bConnect.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bConnect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bConnect.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bConnect.ImageIndex = 9;
            this.bConnect.ImageList = this.imageList1;
            this.bConnect.Location = new System.Drawing.Point(850, 259);
            this.bConnect.Name = "bConnect";
            this.bConnect.Size = new System.Drawing.Size(75, 38);
            this.bConnect.TabIndex = 11;
            this.bConnect.UseVisualStyleBackColor = false;
            this.bConnect.Click += new System.EventHandler(this.button10_Click_1);
            // 
            // bScan
            // 
            this.bScan.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bScan.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bScan.Enabled = false;
            this.bScan.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bScan.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bScan.ImageIndex = 10;
            this.bScan.ImageList = this.imageList1;
            this.bScan.Location = new System.Drawing.Point(850, 301);
            this.bScan.Name = "bScan";
            this.bScan.Size = new System.Drawing.Size(75, 38);
            this.bScan.TabIndex = 10;
            this.bScan.UseVisualStyleBackColor = false;
            this.bScan.Click += new System.EventHandler(this.button12_Click);
            // 
            // bPaste
            // 
            this.bPaste.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bPaste.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bPaste.Enabled = false;
            this.bPaste.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bPaste.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bPaste.ImageIndex = 5;
            this.bPaste.ImageList = this.imageList1;
            this.bPaste.Location = new System.Drawing.Point(850, 204);
            this.bPaste.Name = "bPaste";
            this.bPaste.Size = new System.Drawing.Size(75, 38);
            this.bPaste.TabIndex = 9;
            this.bPaste.UseVisualStyleBackColor = false;
            this.bPaste.Click += new System.EventHandler(this.button8_Click);
            // 
            // bCopy
            // 
            this.bCopy.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bCopy.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bCopy.Enabled = false;
            this.bCopy.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bCopy.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bCopy.ImageIndex = 8;
            this.bCopy.ImageList = this.imageList1;
            this.bCopy.Location = new System.Drawing.Point(850, 164);
            this.bCopy.Name = "bCopy";
            this.bCopy.Size = new System.Drawing.Size(75, 38);
            this.bCopy.TabIndex = 8;
            this.bCopy.UseVisualStyleBackColor = false;
            this.bCopy.Click += new System.EventHandler(this.button7_Click);
            // 
            // bAddDevice
            // 
            this.bAddDevice.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAddDevice.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bAddDevice.Enabled = false;
            this.bAddDevice.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bAddDevice.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bAddDevice.ImageIndex = 2;
            this.bAddDevice.ImageList = this.imageList1;
            this.bAddDevice.Location = new System.Drawing.Point(850, 44);
            this.bAddDevice.Name = "bAddDevice";
            this.bAddDevice.Size = new System.Drawing.Size(75, 38);
            this.bAddDevice.TabIndex = 5;
            this.bAddDevice.UseVisualStyleBackColor = false;
            this.bAddDevice.Click += new System.EventHandler(this.button4_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.SystemColors.Control;
            this.tabPage2.Controls.Add(this.checkBox1);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Controls.Add(this.comboBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(933, 501);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Connection";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(17, 63);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(88, 17);
            this.checkBox1.TabIndex = 4;
            this.checkBox1.Text = "AutoConnect";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM Port";
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(85, 9);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.SystemColors.Control;
            this.tabPage3.Controls.Add(this.button16);
            this.tabPage3.Controls.Add(this.button15);
            this.tabPage3.Controls.Add(this.RelayValue);
            this.tabPage3.Controls.Add(this.bSetTime);
            this.tabPage3.Controls.Add(this.button18);
            this.tabPage3.Controls.Add(this.label2);
            this.tabPage3.Controls.Add(this.lvLog);
            this.tabPage3.Controls.Add(this.button13);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(933, 501);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Log";
            // 
            // button16
            // 
            this.button16.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button16.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button16.Enabled = false;
            this.button16.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.button16.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button16.Location = new System.Drawing.Point(850, 195);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(75, 23);
            this.button16.TabIndex = 28;
            this.button16.Text = "Rel OFF";
            this.button16.UseVisualStyleBackColor = false;
            this.button16.Click += new System.EventHandler(this.button16_Click);
            // 
            // button15
            // 
            this.button15.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button15.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button15.Enabled = false;
            this.button15.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.button15.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button15.Location = new System.Drawing.Point(850, 166);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(75, 23);
            this.button15.TabIndex = 27;
            this.button15.Text = "Rel ON";
            this.button15.UseVisualStyleBackColor = false;
            this.button15.Click += new System.EventHandler(this.button15_Click);
            // 
            // RelayValue
            // 
            this.RelayValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.RelayValue.Location = new System.Drawing.Point(850, 140);
            this.RelayValue.Name = "RelayValue";
            this.RelayValue.Size = new System.Drawing.Size(75, 20);
            this.RelayValue.TabIndex = 26;
            this.RelayValue.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            // 
            // bSetTime
            // 
            this.bSetTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bSetTime.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.bSetTime.Enabled = false;
            this.bSetTime.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.bSetTime.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bSetTime.Location = new System.Drawing.Point(850, 93);
            this.bSetTime.Name = "bSetTime";
            this.bSetTime.Size = new System.Drawing.Size(75, 23);
            this.bSetTime.TabIndex = 25;
            this.bSetTime.Text = "Set Time";
            this.bSetTime.UseVisualStyleBackColor = false;
            this.bSetTime.Click += new System.EventHandler(this.button14_Click);
            // 
            // button18
            // 
            this.button18.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button18.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button18.Enabled = false;
            this.button18.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.button18.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button18.Location = new System.Drawing.Point(850, 64);
            this.button18.Name = "button18";
            this.button18.Size = new System.Drawing.Size(75, 23);
            this.button18.TabIndex = 24;
            this.button18.Text = "Read Stat";
            this.button18.UseVisualStyleBackColor = false;
            this.button18.Click += new System.EventHandler(this.button18_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Consolas", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(6, 8);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(488, 18);
            this.label2.TabIndex = 3;
            this.label2.Text = "Time          Dir  RSSI Len Da  Sa Rsv  Name         Id Data";
            // 
            // lvLog
            // 
            this.lvLog.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lvLog.BackColor = System.Drawing.SystemColors.Info;
            this.lvLog.Font = new System.Drawing.Font("Consolas", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lvLog.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lvLog.Location = new System.Drawing.Point(9, 30);
            this.lvLog.Multiline = true;
            this.lvLog.Name = "lvLog";
            this.lvLog.ReadOnly = true;
            this.lvLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.lvLog.Size = new System.Drawing.Size(835, 465);
            this.lvLog.TabIndex = 2;
            this.lvLog.WordWrap = false;
            // 
            // button13
            // 
            this.button13.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button13.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.button13.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Red;
            this.button13.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button13.Location = new System.Drawing.Point(850, 6);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(75, 23);
            this.button13.TabIndex = 1;
            this.button13.Text = "Clear";
            this.button13.UseVisualStyleBackColor = false;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // opendia
            // 
            this.opendia.FileName = "house.xml";
            // 
            // sport
            // 
            this.sport.BaudRate = 115200;
            this.sport.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.sport_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(88, 17);
            this.toolStripStatusLabel1.Text = "Not Connected";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.AutoSize = false;
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(100, 17);
            this.toolStripStatusLabel2.Text = "Progress";
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.toolStripProgressBar1.ForeColor = System.Drawing.Color.Olive;
            this.toolStripProgressBar1.MarqueeAnimationSpeed = 1000;
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 16);
            this.toolStripProgressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(33, 17);
            this.toolStripStatusLabel3.Text = "0 B/s";
            // 
            // statusStrip1
            // 
            this.statusStrip1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel2,
            this.toolStripProgressBar1,
            this.toolStripStatusLabel3,
            this.toolStripStatusLabel4,
            this.toolStripStatusLabel5});
            this.statusStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.statusStrip1.Location = new System.Drawing.Point(0, 535);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(944, 22);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel4
            // 
            this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
            this.toolStripStatusLabel4.Size = new System.Drawing.Size(41, 17);
            this.toolStripStatusLabel4.Text = "0 dbm";
            // 
            // toolStripStatusLabel5
            // 
            this.toolStripStatusLabel5.Name = "toolStripStatusLabel5";
            this.toolStripStatusLabel5.Size = new System.Drawing.Size(51, 17);
            this.toolStripStatusLabel5.Text = "0 Retries";
            // 
            // timer2
            // 
            this.timer2.Interval = 20;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // timer3
            // 
            this.timer3.Enabled = true;
            this.timer3.Interval = 1000;
            this.timer3.Tick += new System.EventHandler(this.timer3_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(944, 557);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tabControl1);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Name = "Form1";
            this.Text = "HouseCon";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.contextMenuStrip1.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RelayValue)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView tv;
        private System.Windows.Forms.Button bAddRoom;
        private System.Windows.Forms.Button bAddSignal;
        private System.Windows.Forms.Button bDelete;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button bAddDevice;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.OpenFileDialog opendia;
        private System.Windows.Forms.Button bPaste;
        private System.Windows.Forms.Button bCopy;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.IO.Ports.SerialPort sport;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel4;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem MIReset;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel5;
        private System.Windows.Forms.Button bScan;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.TextBox lvLog;
        private System.Windows.Forms.ToolStripMenuItem readNVMToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem writeNVMToolStripMenuItem;
        private System.Windows.Forms.Button bConnect;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem flashToolStripMenuItem;
        private System.Windows.Forms.Button button18;
        private System.Windows.Forms.Button bSetTime;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.NumericUpDown RelayValue;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Button breadNVM;
        private System.Windows.Forms.Button bWriteNVM;
        public System.Windows.Forms.PropertyGrid Prop;
    }
}

