namespace Csp2dotnetEx
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
			this.button1 = new System.Windows.Forms.Button();
			this.labelMain = new System.Windows.Forms.Label();
			this.labelConnected = new System.Windows.Forms.Label();
			this.labelBarcodes = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(15, 87);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(132, 23);
			this.button1.TabIndex = 0;
			this.button1.Text = "Start";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// labelMain
			// 
			this.labelMain.AutoSize = true;
			this.labelMain.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.labelMain.Location = new System.Drawing.Point(15, 14);
			this.labelMain.Name = "labelMain";
			this.labelMain.Size = new System.Drawing.Size(118, 13);
			this.labelMain.TabIndex = 2;
			this.labelMain.Text = "Read all OPN2001's";
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
			this.Controls.Add(this.button1);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MainForm";
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "csp2Ex.net.test";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label labelMain;
		private System.Windows.Forms.Label labelConnected;
		private System.Windows.Forms.Label labelBarcodes;
    }
}

