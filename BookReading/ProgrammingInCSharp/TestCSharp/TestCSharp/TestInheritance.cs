using System;

namespace TestCSharp
{
	public class TestInheritance
	{
		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			Control[] controlArr = new Control[3];
			controlArr [0] = new Button (1);
			controlArr [1] = new LabelButton (2, "label_btn");
			controlArr [2] = new ImgButton (3, "img_btn");

			for (int i = 0; i < 3; i++) {
				controlArr [i].DrawWindow ();
			}

			ImgButton imgBtn = new ImgButton (4, "img_btn");
			imgBtn.DrawWindow ();

			ImgButton[] imgBtnArr = { new ImgButton (10, "10"), new ImgButton (11, "11") };
			PrintControl (imgBtnArr);
			Control[] tmpCtrlArr = imgBtnArr;
			PrintControl (tmpCtrlArr);
			ImgButton[] tmpImgBtnArr = (ImgButton[])tmpCtrlArr;
			PrintControl (tmpImgBtnArr);
		}

		public static void PrintControl (Control[] controlArr)
		{
			foreach (Control ctr in controlArr) {
				Console.WriteLine ("controlId = {0}", ctr.Id);
			}
		}
	}

	abstract public class Control
	{
		private int id = 0;

		public int Id {	
			get { 
				return id;			
			}
			set {
				id = value;
			}
		}

		abstract public void DrawWindow ();
	}

	public class Button: Control
	{
		public Button (int id)
		{
			this.Id = id;
		}

		public override void DrawWindow ()
		{
			Console.WriteLine ("Button DrawWindow");
		}
	}

	public class LabelButton:Button
	{
		private string label;

		public LabelButton (int id, string label)
			: base (id)
		{
			this.label = label;
		}

		public override	void DrawWindow ()
		{
			Console.WriteLine ("LabelButton DrawWindow");
		}
	}

	public class ImgButton: Button
	{
		private string img;

		public ImgButton (int id, string img)
			: base (id)
		{
			this.img = img;
		}

		public new void DrawWindow ()
		{
			Console.WriteLine ("ImgButton DrawWindow");
		}
	}
}

