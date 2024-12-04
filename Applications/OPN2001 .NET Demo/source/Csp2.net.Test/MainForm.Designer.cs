namespace Csp2dotnet
{
    partial class MainForm
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
			this.buttonStart = new System.Windows.Forms.Button();
			this.labelMain = new System.Windows.Forms.Label();
			this.labelConnected = new System.Windows.Forms.Label();
			this.labelBarcodes = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// buttonStart
			// 
			this.buttonStart.Location = new System.Drawing.Point(15, 87);
			this.buttonStart.Name = "buttonStart";
			this.buttonStart.Size = new System.Drawing.Size(132, 23);
			this.buttonStart.TabIndex = 0;
			this.buttonStart.Text = "Start";
			this.buttonStart.UseVisualStyleBackColor = true;
			this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
			// 
			// labelMain
			// 
			this.labelMain.AutoSize = true;
			this.labelMain.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelMain.Location = new System.Drawing.Point(15, 14);
			this.labelMain.Name = "labelMain";
			this.labelMain.Size = new System.Drawing.Size(121, 13);
			this.labelMain.TabIndex = 2;
			this.labelMain.Text = "Read all OPN2001\'s";
			// 
			// labelConnected
			// 
			this.labelConnected.AutoSize = true;
			this.labelConnected.Location = new System.Drawing.Point(15, 40);
			this.labelConnected.Name = "labelConnected";
			this.labelConnected.Size = new System.Drawing.Size(68, 13);
			this.labelConnected.TabIndex = 3;
			this.labelConnected.Text = "Connected: -";
			// 
			// labelBarcodes
			// 
			this.labelBarcodes.AutoSize = true;
			this.labelBarcodes.Location = new System.Drawing.Point(15, 62);
			this.labelBarcodes.Name = "labelBarcodes";
			this.labelBarcodes.Size = new System.Drawing.Size(61, 13);
			this.labelBarcodes.TabIndex = 4;
			this.labelBarcodes.Text = "Barcodes: -";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(159, 121);
			this.Controls.Add(this.labelBarcodes);
			this.Controls.Add(this.labelConnected);
			this.Controls.Add(this.labelMain);
			this.Controls.Add(this.buttonStart);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MainForm";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "csp2.net.test";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Label labelMain;
		private System.Windows.Forms.Label labelConnected;
		private System.Windows.Forms.Label labelBarcodes;
    }
}

