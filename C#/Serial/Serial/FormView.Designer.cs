namespace Serial
{
    partial class FormView
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("A1 [mV]");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("A2 [mV]");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("A3 [mV]");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("A4 [mV]");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("A5 [mV]");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("A6 [mV]");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Frequency[Hz]");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Duty cyle [%]");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Current    [uA]");
            this.label4 = new System.Windows.Forms.Label();
            this.TimeRangeEdit = new System.Windows.Forms.DomainUpDown();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.Msgs = new System.Windows.Forms.TreeView();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.cbPause = new System.Windows.Forms.CheckBox();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(355, 518);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Time Range";
            // 
            // TimeRangeEdit
            // 
            this.TimeRangeEdit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.TimeRangeEdit.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TimeRangeEdit.Items.Add("300");
            this.TimeRangeEdit.Items.Add("100");
            this.TimeRangeEdit.Items.Add("30");
            this.TimeRangeEdit.Items.Add("10");
            this.TimeRangeEdit.Location = new System.Drawing.Point(426, 514);
            this.TimeRangeEdit.Name = "TimeRangeEdit";
            this.TimeRangeEdit.ReadOnly = true;
            this.TimeRangeEdit.Size = new System.Drawing.Size(48, 18);
            this.TimeRangeEdit.TabIndex = 5;
            this.TimeRangeEdit.Text = "100";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(2, 3);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.Msgs);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.pictureBox1);
            this.splitContainer1.Size = new System.Drawing.Size(472, 509);
            this.splitContainer1.SplitterDistance = 93;
            this.splitContainer1.TabIndex = 2;
            // 
            // Msgs
            // 
            this.Msgs.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Msgs.CheckBoxes = true;
            this.Msgs.Location = new System.Drawing.Point(3, 0);
            this.Msgs.Name = "Msgs";
            treeNode1.Checked = true;
            treeNode1.Name = "Node1";
            treeNode1.Tag = "1";
            treeNode1.Text = "A1 [mV]";
            treeNode2.Checked = true;
            treeNode2.Name = "Node2";
            treeNode2.Tag = "1";
            treeNode2.Text = "A2 [mV]";
            treeNode3.Checked = true;
            treeNode3.Name = "Node3";
            treeNode3.Tag = "1";
            treeNode3.Text = "A3 [mV]";
            treeNode4.Checked = true;
            treeNode4.Name = "Node4";
            treeNode4.Tag = "1";
            treeNode4.Text = "A4 [mV]";
            treeNode5.Checked = true;
            treeNode5.Name = "Node5";
            treeNode5.Tag = "1";
            treeNode5.Text = "A5 [mV]";
            treeNode6.Checked = true;
            treeNode6.Name = "Node6";
            treeNode6.Tag = "1";
            treeNode6.Text = "A6 [mV]";
            treeNode7.Checked = true;
            treeNode7.Name = "Node7";
            treeNode7.Tag = "1";
            treeNode7.Text = "Frequency[Hz]";
            treeNode8.Checked = true;
            treeNode8.Name = "Node1";
            treeNode8.Text = "Duty cyle [%]";
            treeNode9.Checked = true;
            treeNode9.Name = "Node1";
            treeNode9.Tag = "1";
            treeNode9.Text = "Current    [uA]";
            this.Msgs.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3,
            treeNode4,
            treeNode5,
            treeNode6,
            treeNode7,
            treeNode8,
            treeNode9});
            this.Msgs.Size = new System.Drawing.Size(87, 509);
            this.Msgs.TabIndex = 0;
            this.Msgs.AfterCheck += new System.Windows.Forms.TreeViewEventHandler(this.Msgs_AfterCheck);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox1.BackColor = System.Drawing.SystemColors.MenuText;
            this.pictureBox1.Location = new System.Drawing.Point(3, 3);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(375, 506);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(271, 517);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(78, 17);
            this.checkBox1.TabIndex = 8;
            this.checkBox1.Text = "Auto Scale";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // cbPause
            // 
            this.cbPause.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cbPause.AutoSize = true;
            this.cbPause.Location = new System.Drawing.Point(185, 518);
            this.cbPause.Name = "cbPause";
            this.cbPause.Size = new System.Drawing.Size(56, 17);
            this.cbPause.TabIndex = 9;
            this.cbPause.Text = "Pause";
            this.cbPause.UseVisualStyleBackColor = true;
            // 
            // FormView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(477, 535);
            this.Controls.Add(this.cbPause);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.TimeRangeEdit);
            this.Name = "FormView";
            this.Text = "View";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DomainUpDown TimeRangeEdit;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.PictureBox pictureBox1;
        public System.Windows.Forms.TreeView Msgs;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.CheckBox cbPause;
    }
}

