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

	// 类内部有抽象方法时，必须将类声明为抽象类
	//public class Control
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

		// 可以将函数指定为virtual 提供默认实现
		//		public virtual void DrawWindow ()
		//		{
		//		}

		// error 抽象方法不能有实现
		//		abstract public void DrawWindow ()
		//		{
		//		}

		// 可以将函数指定为abstract 如果子类没有实现abstract方法则子类也需要标记为抽象类
		abstract public void DrawWindow ();
	}

	abstract public class ConrolX : Control
	{
		// 不需要重新声明抽象方法，否则会隐藏Control中的声明
		//abstract public void DrawWindow ();
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

