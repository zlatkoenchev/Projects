﻿namespace Serial
{
    partial class FormGauge
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
            this.gA1 = new System.Windows.Forms.ProgressBar();
            this.lA1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.gCur = new System.Windows.Forms.ProgressBar();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lA2 = new System.Windows.Forms.Label();
            this.gA2 = new System.Windows.Forms.ProgressBar();
            this.lA3 = new System.Windows.Forms.Label();
            this.gA3 = new System.Windows.Forms.ProgressBar();
            this.lA4 = new System.Windows.Forms.Label();
            this.gA4 = new System.Windows.Forms.ProgressBar();
            this.lA5 = new System.Windows.Forms.Label();
            this.gA5 = new System.Windows.Forms.ProgressBar();
            this.lA6 = new System.Windows.Forms.Label();
            this.gA6 = new System.Windows.Forms.ProgressBar();
            this.lFreq = new System.Windows.Forms.Label();
            this.gFreq = new System.Windows.Forms.ProgressBar();
            this.lDC = new System.Windows.Forms.Label();
            this.gDC = new System.Windows.Forms.ProgressBar();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // gA1
            // 
            this.gA1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA1.Location = new System.Drawing.Point(21, 25);
            this.gA1.Maximum = 2800;
            this.gA1.Name = "gA1";
            this.gA1.Size = new System.Drawing.Size(140, 13);
            this.gA1.Step = 1;
            this.gA1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA1.TabIndex = 0;
            // 
            // lA1
            // 
            this.lA1.AutoSize = true;
            this.lA1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA1.ForeColor = System.Drawing.Color.Black;
            this.lA1.Location = new System.Drawing.Point(18, 9);
            this.lA1.Name = "lA1";
            this.lA1.Size = new System.Drawing.Size(22, 13);
            this.lA1.TabIndex = 1;
            this.lA1.Text = "A1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(11, 336);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Current";
            // 
            // gCur
            // 
            this.gCur.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gCur.Location = new System.Drawing.Point(21, 352);
            this.gCur.Maximum = 2000000;
            this.gCur.Name = "gCur";
            this.gCur.Size = new System.Drawing.Size(140, 13);
            this.gCur.Step = 1;
            this.gCur.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gCur.TabIndex = 2;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 200;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lA2
            // 
            this.lA2.AutoSize = true;
            this.lA2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA2.ForeColor = System.Drawing.Color.Black;
            this.lA2.Location = new System.Drawing.Point(18, 46);
            this.lA2.Name = "lA2";
            this.lA2.Size = new System.Drawing.Size(22, 13);
            this.lA2.TabIndex = 5;
            this.lA2.Text = "A2";
            // 
            // gA2
            // 
            this.gA2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA2.Location = new System.Drawing.Point(21, 62);
            this.gA2.Maximum = 2800;
            this.gA2.Name = "gA2";
            this.gA2.Size = new System.Drawing.Size(140, 13);
            this.gA2.Step = 1;
            this.gA2.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA2.TabIndex = 4;
            // 
            // lA3
            // 
            this.lA3.AutoSize = true;
            this.lA3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA3.ForeColor = System.Drawing.Color.Black;
            this.lA3.Location = new System.Drawing.Point(18, 85);
            this.lA3.Name = "lA3";
            this.lA3.Size = new System.Drawing.Size(22, 13);
            this.lA3.TabIndex = 7;
            this.lA3.Text = "A3";
            // 
            // gA3
            // 
            this.gA3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA3.Location = new System.Drawing.Point(21, 101);
            this.gA3.Maximum = 2800;
            this.gA3.Name = "gA3";
            this.gA3.Size = new System.Drawing.Size(140, 13);
            this.gA3.Step = 1;
            this.gA3.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA3.TabIndex = 6;
            // 
            // lA4
            // 
            this.lA4.AutoSize = true;
            this.lA4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA4.ForeColor = System.Drawing.Color.Black;
            this.lA4.Location = new System.Drawing.Point(18, 124);
            this.lA4.Name = "lA4";
            this.lA4.Size = new System.Drawing.Size(22, 13);
            this.lA4.TabIndex = 9;
            this.lA4.Text = "A4";
            // 
            // gA4
            // 
            this.gA4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA4.Location = new System.Drawing.Point(21, 140);
            this.gA4.Maximum = 2800;
            this.gA4.Name = "gA4";
            this.gA4.Size = new System.Drawing.Size(140, 13);
            this.gA4.Step = 1;
            this.gA4.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA4.TabIndex = 8;
            // 
            // lA5
            // 
            this.lA5.AutoSize = true;
            this.lA5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA5.ForeColor = System.Drawing.Color.Black;
            this.lA5.Location = new System.Drawing.Point(18, 166);
            this.lA5.Name = "lA5";
            this.lA5.Size = new System.Drawing.Size(22, 13);
            this.lA5.TabIndex = 11;
            this.lA5.Text = "A5";
            // 
            // gA5
            // 
            this.gA5.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA5.Location = new System.Drawing.Point(21, 182);
            this.gA5.Maximum = 2800;
            this.gA5.Name = "gA5";
            this.gA5.Size = new System.Drawing.Size(140, 13);
            this.gA5.Step = 1;
            this.gA5.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA5.TabIndex = 10;
            // 
            // lA6
            // 
            this.lA6.AutoSize = true;
            this.lA6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lA6.ForeColor = System.Drawing.Color.Black;
            this.lA6.Location = new System.Drawing.Point(18, 208);
            this.lA6.Name = "lA6";
            this.lA6.Size = new System.Drawing.Size(22, 13);
            this.lA6.TabIndex = 13;
            this.lA6.Text = "A6";
            // 
            // gA6
            // 
            this.gA6.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gA6.Location = new System.Drawing.Point(21, 224);
            this.gA6.Maximum = 2800;
            this.gA6.Name = "gA6";
            this.gA6.Size = new System.Drawing.Size(140, 13);
            this.gA6.Step = 1;
            this.gA6.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gA6.TabIndex = 12;
            // 
            // lFreq
            // 
            this.lFreq.AutoSize = true;
            this.lFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lFreq.ForeColor = System.Drawing.Color.Black;
            this.lFreq.Location = new System.Drawing.Point(12, 251);
            this.lFreq.Name = "lFreq";
            this.lFreq.Size = new System.Drawing.Size(66, 13);
            this.lFreq.TabIndex = 15;
            this.lFreq.Text = "Frequency";
            // 
            // gFreq
            // 
            this.gFreq.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gFreq.Location = new System.Drawing.Point(21, 267);
            this.gFreq.Maximum = 60000;
            this.gFreq.Name = "gFreq";
            this.gFreq.Size = new System.Drawing.Size(140, 13);
            this.gFreq.Step = 1;
            this.gFreq.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gFreq.TabIndex = 14;
            // 
            // lDC
            // 
            this.lDC.AutoSize = true;
            this.lDC.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lDC.ForeColor = System.Drawing.Color.Black;
            this.lDC.Location = new System.Drawing.Point(11, 297);
            this.lDC.Name = "lDC";
            this.lDC.Size = new System.Drawing.Size(68, 13);
            this.lDC.TabIndex = 17;
            this.lDC.Text = "Duty Cycle";
            // 
            // gDC
            // 
            this.gDC.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gDC.Location = new System.Drawing.Point(21, 313);
            this.gDC.Name = "gDC";
            this.gDC.Size = new System.Drawing.Size(140, 13);
            this.gDC.Step = 1;
            this.gDC.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.gDC.TabIndex = 16;
            // 
            // label9
            // 
            this.label9.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label9.ForeColor = System.Drawing.Color.Black;
            this.label9.Location = new System.Drawing.Point(167, 352);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(21, 13);
            this.label9.TabIndex = 19;
            this.label9.Text = "10";
            this.label9.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label10
            // 
            this.label10.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label10.ForeColor = System.Drawing.Color.Black;
            this.label10.Location = new System.Drawing.Point(165, 25);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(21, 13);
            this.label10.TabIndex = 18;
            this.label10.Text = "28";
            this.label10.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.ForeColor = System.Drawing.Color.Black;
            this.label4.Location = new System.Drawing.Point(165, 62);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(21, 13);
            this.label4.TabIndex = 27;
            this.label4.Text = "28";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label5
            // 
            this.label5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.ForeColor = System.Drawing.Color.Black;
            this.label5.Location = new System.Drawing.Point(167, 101);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(21, 13);
            this.label5.TabIndex = 28;
            this.label5.Text = "28";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label6
            // 
            this.label6.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.ForeColor = System.Drawing.Color.Black;
            this.label6.Location = new System.Drawing.Point(167, 140);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(21, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "28";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label7.ForeColor = System.Drawing.Color.Black;
            this.label7.Location = new System.Drawing.Point(165, 182);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(21, 13);
            this.label7.TabIndex = 30;
            this.label7.Text = "28";
            this.label7.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label8
            // 
            this.label8.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.ForeColor = System.Drawing.Color.Black;
            this.label8.Location = new System.Drawing.Point(165, 224);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(21, 13);
            this.label8.TabIndex = 31;
            this.label8.Text = "28";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.ForeColor = System.Drawing.Color.Black;
            this.label3.Location = new System.Drawing.Point(165, 267);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(28, 13);
            this.label3.TabIndex = 32;
            this.label3.Text = "60k";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(165, 313);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 33;
            this.label1.Text = "100";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label11.ForeColor = System.Drawing.Color.Black;
            this.label11.Location = new System.Drawing.Point(3, 25);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(14, 13);
            this.label11.TabIndex = 34;
            this.label11.Text = "0";
            this.label11.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label12.ForeColor = System.Drawing.Color.Black;
            this.label12.Location = new System.Drawing.Point(3, 62);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(14, 13);
            this.label12.TabIndex = 35;
            this.label12.Text = "0";
            this.label12.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label13.ForeColor = System.Drawing.Color.Black;
            this.label13.Location = new System.Drawing.Point(3, 101);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(14, 13);
            this.label13.TabIndex = 36;
            this.label13.Text = "0";
            this.label13.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label14.ForeColor = System.Drawing.Color.Black;
            this.label14.Location = new System.Drawing.Point(3, 140);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(14, 13);
            this.label14.TabIndex = 37;
            this.label14.Text = "0";
            this.label14.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label15.ForeColor = System.Drawing.Color.Black;
            this.label15.Location = new System.Drawing.Point(3, 182);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(14, 13);
            this.label15.TabIndex = 38;
            this.label15.Text = "0";
            this.label15.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label16.ForeColor = System.Drawing.Color.Black;
            this.label16.Location = new System.Drawing.Point(3, 224);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(14, 13);
            this.label16.TabIndex = 39;
            this.label16.Text = "0";
            this.label16.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label17.ForeColor = System.Drawing.Color.Black;
            this.label17.Location = new System.Drawing.Point(3, 267);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(14, 13);
            this.label17.TabIndex = 40;
            this.label17.Text = "0";
            this.label17.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label18.ForeColor = System.Drawing.Color.Black;
            this.label18.Location = new System.Drawing.Point(3, 313);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(14, 13);
            this.label18.TabIndex = 41;
            this.label18.Text = "0";
            this.label18.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label19.ForeColor = System.Drawing.Color.Black;
            this.label19.Location = new System.Drawing.Point(3, 352);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(14, 13);
            this.label19.TabIndex = 42;
            this.label19.Text = "0";
            this.label19.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // FormGauge
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(192, 379);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.lDC);
            this.Controls.Add(this.gDC);
            this.Controls.Add(this.lFreq);
            this.Controls.Add(this.gFreq);
            this.Controls.Add(this.lA6);
            this.Controls.Add(this.gA6);
            this.Controls.Add(this.lA5);
            this.Controls.Add(this.gA5);
            this.Controls.Add(this.lA4);
            this.Controls.Add(this.gA4);
            this.Controls.Add(this.lA3);
            this.Controls.Add(this.gA3);
            this.Controls.Add(this.lA2);
            this.Controls.Add(this.gA2);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.gCur);
            this.Controls.Add(this.lA1);
            this.Controls.Add(this.gA1);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(200, 406);
            this.MinimumSize = new System.Drawing.Size(200, 406);
            this.Name = "FormGauge";
            this.ShowInTaskbar = false;
            this.Text = "Meter";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormGauge_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar gA1;
        private System.Windows.Forms.Label lA1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar gCur;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lA2;
        private System.Windows.Forms.ProgressBar gA2;
        private System.Windows.Forms.Label lA3;
        private System.Windows.Forms.ProgressBar gA3;
        private System.Windows.Forms.Label lA4;
        private System.Windows.Forms.ProgressBar gA4;
        private System.Windows.Forms.Label lA5;
        private System.Windows.Forms.ProgressBar gA5;
        private System.Windows.Forms.Label lA6;
        private System.Windows.Forms.ProgressBar gA6;
        private System.Windows.Forms.Label lFreq;
        private System.Windows.Forms.ProgressBar gFreq;
        private System.Windows.Forms.Label lDC;
        private System.Windows.Forms.ProgressBar gDC;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
    }
}