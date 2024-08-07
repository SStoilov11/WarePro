namespace WarePro_ControlApplication
{
    partial class ControlApplication
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            lbLogs = new ListBox();
            lbShelves = new Label();
            cbShelves = new ComboBox();
            btnGoToLocation = new Button();
            btnGoToRestLocation = new Button();
            label1 = new Label();
            tbCurrentSpeed = new TextBox();
            textBox1 = new TextBox();
            label2 = new Label();
            tbTestMessage = new TextBox();
            btnSendTestMsg = new Button();
            SuspendLayout();
            // 
            // lbLogs
            // 
            lbLogs.FormattingEnabled = true;
            lbLogs.ItemHeight = 25;
            lbLogs.Location = new Point(6, 9);
            lbLogs.Name = "lbLogs";
            lbLogs.Size = new Size(212, 429);
            lbLogs.TabIndex = 0;
            // 
            // lbShelves
            // 
            lbShelves.AutoSize = true;
            lbShelves.Location = new Point(224, 23);
            lbShelves.Name = "lbShelves";
            lbShelves.Size = new Size(118, 25);
            lbShelves.TabIndex = 1;
            lbShelves.Text = "Select a shelf:";
            // 
            // cbShelves
            // 
            cbShelves.FormattingEnabled = true;
            cbShelves.Location = new Point(348, 20);
            cbShelves.Name = "cbShelves";
            cbShelves.Size = new Size(83, 33);
            cbShelves.TabIndex = 2;
            // 
            // btnGoToLocation
            // 
            btnGoToLocation.Location = new Point(224, 59);
            btnGoToLocation.Name = "btnGoToLocation";
            btnGoToLocation.Size = new Size(207, 42);
            btnGoToLocation.TabIndex = 3;
            btnGoToLocation.Text = "Go to selected location";
            btnGoToLocation.UseVisualStyleBackColor = true;
            btnGoToLocation.Click += btnGoToLocation_Click;
            // 
            // btnGoToRestLocation
            // 
            btnGoToRestLocation.Location = new Point(224, 107);
            btnGoToRestLocation.Name = "btnGoToRestLocation";
            btnGoToRestLocation.Size = new Size(207, 42);
            btnGoToRestLocation.TabIndex = 4;
            btnGoToRestLocation.Text = "Go to rest position";
            btnGoToRestLocation.UseVisualStyleBackColor = true;
            btnGoToRestLocation.Click += btnGoToRestLocation_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(224, 318);
            label1.Name = "label1";
            label1.Size = new Size(129, 25);
            label1.TabIndex = 5;
            label1.Text = "Current Speed:";
            // 
            // tbCurrentSpeed
            // 
            tbCurrentSpeed.Location = new Point(376, 312);
            tbCurrentSpeed.Name = "tbCurrentSpeed";
            tbCurrentSpeed.ReadOnly = true;
            tbCurrentSpeed.Size = new Size(150, 31);
            tbCurrentSpeed.TabIndex = 6;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(376, 349);
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.Size = new Size(150, 31);
            textBox1.TabIndex = 8;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(224, 352);
            label2.Name = "label2";
            label2.Size = new Size(146, 25);
            label2.TabIndex = 7;
            label2.Text = "Current Location:";
            // 
            // tbTestMessage
            // 
            tbTestMessage.Location = new Point(526, 59);
            tbTestMessage.Name = "tbTestMessage";
            tbTestMessage.Size = new Size(235, 31);
            tbTestMessage.TabIndex = 9;
            // 
            // btnSendTestMsg
            // 
            btnSendTestMsg.Location = new Point(526, 96);
            btnSendTestMsg.Name = "btnSendTestMsg";
            btnSendTestMsg.Size = new Size(235, 38);
            btnSendTestMsg.TabIndex = 10;
            btnSendTestMsg.Text = "Send Message";
            btnSendTestMsg.UseVisualStyleBackColor = true;
            btnSendTestMsg.Click += btnSendTestMsg_Click;
            // 
            // ControlApplication
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(btnSendTestMsg);
            Controls.Add(tbTestMessage);
            Controls.Add(textBox1);
            Controls.Add(label2);
            Controls.Add(tbCurrentSpeed);
            Controls.Add(label1);
            Controls.Add(btnGoToRestLocation);
            Controls.Add(btnGoToLocation);
            Controls.Add(cbShelves);
            Controls.Add(lbShelves);
            Controls.Add(lbLogs);
            Name = "ControlApplication";
            Text = "Form1";
            Load += ControlApplication_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ListBox lbLogs;
        private Label lbShelves;
        private ComboBox cbShelves;
        private Button btnGoToLocation;
        private Button btnGoToRestLocation;
        private Label label1;
        private TextBox tbCurrentSpeed;
        private TextBox textBox1;
        private Label label2;
        private TextBox tbTestMessage;
        private Button btnSendTestMsg;
    }
}
