namespace HFHome
{
    partial class Actuator
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbpresenceframe = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.udpresencenight = new System.Windows.Forms.NumericUpDown();
            this.label21 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.udPresenceday = new System.Windows.Forms.NumericUpDown();
            this.cbActType = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.udCmdTimoeut = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.nNAD1 = new System.Windows.Forms.NumericUpDown();
            this.nNAD2 = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.nNAD3 = new System.Windows.Forms.NumericUpDown();
            this.nNAD4 = new System.Windows.Forms.NumericUpDown();
            this.rbDaily = new System.Windows.Forms.RadioButton();
            this.rbWeekend = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udpresencenight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udPresenceday)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCmdTimoeut)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD4)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.Info;
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pictureBox1.ErrorImage = null;
            this.pictureBox1.InitialImage = null;
            this.pictureBox1.Location = new System.Drawing.Point(15, 108);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(771, 32);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.pictureBox1.MouseLeave += new System.EventHandler(this.pictureBox1_MouseLeave);
            this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.SystemColors.ControlText;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.ForeColor = System.Drawing.SystemColors.Control;
            this.label3.Location = new System.Drawing.Point(379, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 16);
            this.label3.TabIndex = 7;
            this.label3.Text = "12:00";
            this.label3.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(15, 143);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 16);
            this.label1.TabIndex = 8;
            this.label1.Text = "0ч";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(379, 143);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 16);
            this.label5.TabIndex = 9;
            this.label5.Text = "12ч";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(783, 143);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 16);
            this.label2.TabIndex = 10;
            this.label2.Text = "24ч";
            // 
            // cbpresenceframe
            // 
            this.cbpresenceframe.AutoSize = true;
            this.cbpresenceframe.Enabled = false;
            this.cbpresenceframe.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.cbpresenceframe.Location = new System.Drawing.Point(260, 183);
            this.cbpresenceframe.Name = "cbpresenceframe";
            this.cbpresenceframe.Size = new System.Drawing.Size(270, 20);
            this.cbpresenceframe.TabIndex = 33;
            this.cbpresenceframe.Text = "Изпращай съобщение за присъствие";
            this.cbpresenceframe.UseVisualStyleBackColor = true;
            this.cbpresenceframe.CheckedChanged += new System.EventHandler(this.cbpresenceframe_CheckedChanged);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBox1.Location = new System.Drawing.Point(15, 64);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(164, 20);
            this.checkBox1.TabIndex = 34;
            this.checkBox1.Text = "Включване по време";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBox2.Location = new System.Drawing.Point(15, 183);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(201, 20);
            this.checkBox2.TabIndex = 35;
            this.checkBox2.Text = "Включване по присъствие";
            this.checkBox2.UseVisualStyleBackColor = true;
            this.checkBox2.CheckedChanged += new System.EventHandler(this.checkBox2_CheckedChanged);
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.checkBox3.Location = new System.Drawing.Point(15, 255);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(179, 20);
            this.checkBox3.TabIndex = 36;
            this.checkBox3.Text = "Включване по команда";
            this.checkBox3.UseVisualStyleBackColor = true;
            this.checkBox3.CheckedChanged += new System.EventHandler(this.checkBox3_CheckedChanged);
            // 
            // udpresencenight
            // 
            this.udpresencenight.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.udpresencenight.Location = new System.Drawing.Point(480, 216);
            this.udpresencenight.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.udpresencenight.Name = "udpresencenight";
            this.udpresencenight.Size = new System.Drawing.Size(66, 22);
            this.udpresencenight.TabIndex = 40;
            this.udpresencenight.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.udpresencenight.ValueChanged += new System.EventHandler(this.udpresencenight_ValueChanged);
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label21.Location = new System.Drawing.Point(322, 218);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(153, 16);
            this.label21.TabIndex = 39;
            this.label21.Text = "Вечер изкл. след [сек]";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label20.Location = new System.Drawing.Point(15, 218);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(180, 16);
            this.label20.TabIndex = 38;
            this.label20.Text = "През деня изкл. след [сек]";
            // 
            // udPresenceday
            // 
            this.udPresenceday.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.udPresenceday.Location = new System.Drawing.Point(201, 216);
            this.udPresenceday.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.udPresenceday.Name = "udPresenceday";
            this.udPresenceday.Size = new System.Drawing.Size(65, 22);
            this.udPresenceday.TabIndex = 37;
            this.udPresenceday.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.udPresenceday.ValueChanged += new System.EventHandler(this.udPresenceday_ValueChanged);
            // 
            // cbActType
            // 
            this.cbActType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbActType.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.cbActType.FormattingEnabled = true;
            this.cbActType.Items.AddRange(new object[] {
            "----",
            "BISTABLE",
            "RELAY",
            "AC-PWM",
            "PHOTOMOS"});
            this.cbActType.Location = new System.Drawing.Point(130, 21);
            this.cbActType.Name = "cbActType";
            this.cbActType.Size = new System.Drawing.Size(121, 24);
            this.cbActType.TabIndex = 41;
            this.cbActType.SelectedIndexChanged += new System.EventHandler(this.cbActType_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(12, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(96, 16);
            this.label4.TabIndex = 42;
            this.label4.Text = "Тип на ключа";
            // 
            // udCmdTimoeut
            // 
            this.udCmdTimoeut.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.udCmdTimoeut.Location = new System.Drawing.Point(521, 254);
            this.udCmdTimoeut.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.udCmdTimoeut.Name = "udCmdTimoeut";
            this.udCmdTimoeut.Size = new System.Drawing.Size(65, 22);
            this.udCmdTimoeut.TabIndex = 43;
            this.udCmdTimoeut.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.udCmdTimoeut.ValueChanged += new System.EventHandler(this.udCmdTimoeut_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(276, 256);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(239, 16);
            this.label6.TabIndex = 44;
            this.label6.Text = "Стоп при липса на команда за [сек]";
            // 
            // nNAD1
            // 
            this.nNAD1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.nNAD1.Location = new System.Drawing.Point(631, 216);
            this.nNAD1.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nNAD1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nNAD1.Name = "nNAD1";
            this.nNAD1.Size = new System.Drawing.Size(42, 22);
            this.nNAD1.TabIndex = 45;
            this.nNAD1.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nNAD1.ValueChanged += new System.EventHandler(this.nNAD1_ValueChanged_1);
            // 
            // nNAD2
            // 
            this.nNAD2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.nNAD2.Location = new System.Drawing.Point(679, 216);
            this.nNAD2.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nNAD2.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nNAD2.Name = "nNAD2";
            this.nNAD2.Size = new System.Drawing.Size(42, 22);
            this.nNAD2.TabIndex = 46;
            this.nNAD2.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nNAD2.ValueChanged += new System.EventHandler(this.nNAD2_ValueChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label7.Location = new System.Drawing.Point(581, 218);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 16);
            this.label7.TabIndex = 47;
            this.label7.Text = "NADs";
            // 
            // nNAD3
            // 
            this.nNAD3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.nNAD3.Location = new System.Drawing.Point(727, 216);
            this.nNAD3.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nNAD3.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nNAD3.Name = "nNAD3";
            this.nNAD3.Size = new System.Drawing.Size(42, 22);
            this.nNAD3.TabIndex = 48;
            this.nNAD3.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nNAD3.ValueChanged += new System.EventHandler(this.nNAD3_ValueChanged);
            // 
            // nNAD4
            // 
            this.nNAD4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.nNAD4.Location = new System.Drawing.Point(775, 216);
            this.nNAD4.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nNAD4.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nNAD4.Name = "nNAD4";
            this.nNAD4.Size = new System.Drawing.Size(42, 22);
            this.nNAD4.TabIndex = 49;
            this.nNAD4.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nNAD4.ValueChanged += new System.EventHandler(this.nNAD4_ValueChanged);
            // 
            // rbDaily
            // 
            this.rbDaily.AutoSize = true;
            this.rbDaily.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.rbDaily.Location = new System.Drawing.Point(786, 20);
            this.rbDaily.Name = "rbDaily";
            this.rbDaily.Size = new System.Drawing.Size(81, 20);
            this.rbDaily.TabIndex = 51;
            this.rbDaily.Text = "Пон-Пет";
            this.rbDaily.UseVisualStyleBackColor = true;
            this.rbDaily.CheckedChanged += new System.EventHandler(this.rbDaily_CheckedChanged);
            // 
            // rbWeekend
            // 
            this.rbWeekend.AutoSize = true;
            this.rbWeekend.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.rbWeekend.Location = new System.Drawing.Point(786, 43);
            this.rbWeekend.Name = "rbWeekend";
            this.rbWeekend.Size = new System.Drawing.Size(82, 20);
            this.rbWeekend.TabIndex = 50;
            this.rbWeekend.Text = "Съб-Нед";
            this.rbWeekend.UseVisualStyleBackColor = true;
            this.rbWeekend.CheckedChanged += new System.EventHandler(this.rbWeekend_CheckedChanged);
            // 
            // Actuator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbDaily);
            this.Controls.Add(this.rbWeekend);
            this.Controls.Add(this.nNAD4);
            this.Controls.Add(this.nNAD3);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.nNAD2);
            this.Controls.Add(this.nNAD1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.udCmdTimoeut);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.cbActType);
            this.Controls.Add(this.udpresencenight);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.udPresenceday);
            this.Controls.Add(this.checkBox3);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.cbpresenceframe);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.pictureBox1);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.Name = "Actuator";
            this.Size = new System.Drawing.Size(936, 308);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udpresencenight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udPresenceday)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCmdTimoeut)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nNAD4)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox cbpresenceframe;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.NumericUpDown udpresencenight;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.NumericUpDown udPresenceday;
        private System.Windows.Forms.ComboBox cbActType;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown udCmdTimoeut;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown nNAD1;
        private System.Windows.Forms.NumericUpDown nNAD2;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown nNAD3;
        private System.Windows.Forms.NumericUpDown nNAD4;
        private System.Windows.Forms.RadioButton rbDaily;
        private System.Windows.Forms.RadioButton rbWeekend;


    }
}
