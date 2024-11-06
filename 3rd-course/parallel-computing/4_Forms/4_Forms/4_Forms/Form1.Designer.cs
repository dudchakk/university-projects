namespace _4_Forms
{
    partial class Form1
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
            panel1 = new Panel();
            panel2 = new Panel();
            panel3 = new Panel();
            panel4 = new Panel();
            buttonStart1 = new Button();
            buttonStop1 = new Button();
            buttonStart2 = new Button();
            buttonStart3 = new Button();
            buttonStart4 = new Button();
            buttonStop2 = new Button();
            buttonStop3 = new Button();
            buttonStop4 = new Button();
            SuspendLayout();
            // 
            // panel1
            // 
            panel1.BackColor = SystemColors.ButtonFace;
            panel1.Location = new Point(4, 4);
            panel1.Name = "panel1";
            panel1.Size = new Size(430, 270);
            panel1.TabIndex = 0;
            // 
            // panel2
            // 
            panel2.Location = new Point(538, 4);
            panel2.Name = "panel2";
            panel2.Size = new Size(429, 270);
            panel2.TabIndex = 1;
            // 
            // panel3
            // 
            panel3.Location = new Point(4, 383);
            panel3.Name = "panel3";
            panel3.Size = new Size(430, 286);
            panel3.TabIndex = 2;
            // 
            // panel4
            // 
            panel4.Location = new Point(538, 383);
            panel4.Name = "panel4";
            panel4.Size = new Size(431, 286);
            panel4.TabIndex = 3;
            // 
            // buttonStart1
            // 
            buttonStart1.Location = new Point(42, 301);
            buttonStart1.Name = "buttonStart1";
            buttonStart1.Size = new Size(112, 34);
            buttonStart1.TabIndex = 4;
            buttonStart1.Text = "Start";
            buttonStart1.UseVisualStyleBackColor = true;
            // 
            // buttonStop1
            // 
            buttonStop1.Location = new Point(253, 301);
            buttonStop1.Name = "buttonStop1";
            buttonStop1.Size = new Size(112, 34);
            buttonStop1.TabIndex = 5;
            buttonStop1.Text = "Stop";
            buttonStop1.UseVisualStyleBackColor = true;
            // 
            // buttonStart2
            // 
            buttonStart2.Location = new Point(592, 301);
            buttonStart2.Name = "buttonStart2";
            buttonStart2.Size = new Size(112, 34);
            buttonStart2.TabIndex = 6;
            buttonStart2.Text = "Start";
            buttonStart2.UseVisualStyleBackColor = true;
            // 
            // buttonStart3
            // 
            buttonStart3.Location = new Point(42, 690);
            buttonStart3.Name = "buttonStart3";
            buttonStart3.Size = new Size(112, 34);
            buttonStart3.TabIndex = 7;
            buttonStart3.Text = "Start";
            buttonStart3.UseVisualStyleBackColor = true;
            // 
            // buttonStart4
            // 
            buttonStart4.Location = new Point(592, 690);
            buttonStart4.Name = "buttonStart4";
            buttonStart4.Size = new Size(112, 34);
            buttonStart4.TabIndex = 8;
            buttonStart4.Text = "Start";
            buttonStart4.UseVisualStyleBackColor = true;
            // 
            // buttonStop2
            // 
            buttonStop2.Location = new Point(804, 301);
            buttonStop2.Name = "buttonStop2";
            buttonStop2.Size = new Size(112, 34);
            buttonStop2.TabIndex = 9;
            buttonStop2.Text = "Stop";
            buttonStop2.UseVisualStyleBackColor = true;
            // 
            // buttonStop3
            // 
            buttonStop3.Location = new Point(253, 690);
            buttonStop3.Name = "buttonStop3";
            buttonStop3.Size = new Size(112, 34);
            buttonStop3.TabIndex = 10;
            buttonStop3.Text = "Stop";
            buttonStop3.UseVisualStyleBackColor = true;
            // 
            // buttonStop4
            // 
            buttonStop4.Location = new Point(804, 690);
            buttonStop4.Name = "buttonStop4";
            buttonStop4.Size = new Size(112, 34);
            buttonStop4.TabIndex = 11;
            buttonStop4.Text = "Stop";
            buttonStop4.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(978, 744);
            Controls.Add(buttonStop4);
            Controls.Add(buttonStop3);
            Controls.Add(buttonStop2);
            Controls.Add(buttonStart4);
            Controls.Add(buttonStart3);
            Controls.Add(buttonStart2);
            Controls.Add(buttonStop1);
            Controls.Add(buttonStart1);
            Controls.Add(panel4);
            Controls.Add(panel3);
            Controls.Add(panel2);
            Controls.Add(panel1);
            Name = "Form1";
            Text = "Form1";
            FormClosed += MainForm_FormClosed;
            Load += Form1_Load;
            ResumeLayout(false);
        }

        #endregion

        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Panel panel4;
        private Button buttonStart1;
        private Button buttonStop1;
        private Button buttonStart2;
        private Button buttonStart3;
        private Button buttonStart4;
        private Button buttonStop2;
        private Button buttonStop3;
        private Button buttonStop4;
    }
}
