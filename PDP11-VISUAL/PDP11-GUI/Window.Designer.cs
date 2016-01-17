namespace PDP11_GUI
{
    partial class Window
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
            this.Screen = new System.Windows.Forms.PictureBox();
            this.stepButton = new System.Windows.Forms.Button();
            this.runButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.resetButton = new System.Windows.Forms.Button();
            this.programText = new System.Windows.Forms.ListView();
            this.procInfo = new System.Windows.Forms.ListView();
            ((System.ComponentModel.ISupportInitialize)(this.Screen)).BeginInit();
            this.SuspendLayout();
            // 
            // Screen
            // 
            this.Screen.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Screen.Location = new System.Drawing.Point(12, 12);
            this.Screen.Name = "Screen";
            this.Screen.Size = new System.Drawing.Size(640, 480);
            this.Screen.TabIndex = 0;
            this.Screen.TabStop = false;
            // 
            // stepButton
            // 
            this.stepButton.Location = new System.Drawing.Point(12, 701);
            this.stepButton.Name = "stepButton";
            this.stepButton.Size = new System.Drawing.Size(187, 100);
            this.stepButton.TabIndex = 1;
            this.stepButton.Text = "STEP";
            this.stepButton.UseVisualStyleBackColor = true;
            this.stepButton.Click += new System.EventHandler(this.stepButton_Click);
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(12, 518);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(89, 73);
            this.runButton.TabIndex = 2;
            this.runButton.Text = "RUN";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(110, 518);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(91, 73);
            this.stopButton.TabIndex = 3;
            this.stopButton.Text = "STOP";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // resetButton
            // 
            this.resetButton.Location = new System.Drawing.Point(12, 830);
            this.resetButton.Name = "resetButton";
            this.resetButton.Size = new System.Drawing.Size(187, 52);
            this.resetButton.TabIndex = 4;
            this.resetButton.Text = "RESET";
            this.resetButton.UseVisualStyleBackColor = true;
            this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
            // 
            // programText
            // 
            this.programText.Location = new System.Drawing.Point(669, 12);
            this.programText.Name = "programText";
            this.programText.Size = new System.Drawing.Size(620, 480);
            this.programText.TabIndex = 5;
            this.programText.UseCompatibleStateImageBehavior = false;
            // 
            // procInfo
            // 
            this.procInfo.Location = new System.Drawing.Point(215, 518);
            this.procInfo.Name = "procInfo";
            this.procInfo.Size = new System.Drawing.Size(1074, 364);
            this.procInfo.TabIndex = 6;
            this.procInfo.UseCompatibleStateImageBehavior = false;
            // 
            // Window
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1301, 894);
            this.Controls.Add(this.procInfo);
            this.Controls.Add(this.programText);
            this.Controls.Add(this.resetButton);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.stepButton);
            this.Controls.Add(this.Screen);
            this.Name = "Window";
            this.Text = "PDP11-EMULATOR";
            ((System.ComponentModel.ISupportInitialize)(this.Screen)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox Screen;
        private System.Windows.Forms.Button stepButton;
        private System.Windows.Forms.Button runButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Button resetButton;
        private System.Windows.Forms.ListView programText;
        private System.Windows.Forms.ListView procInfo;
    }
}

