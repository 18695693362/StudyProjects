using System;

namespace TestCSharp
{
	public class TestInterface
	{
		static public void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			GDoc doc = new GDoc ();
			doc.Read ();
			doc.Write (null);
			Console.WriteLine ("doc status is {0}", doc.Status);

			GNote note = new GNote ();

			IStorable[] iStorArr = new IStorable[2];
			iStorArr [0] = doc as IStorable;
			iStorArr [1] = note as IStorable;
			for (int i = 0; i < 2; i++) {
				if (iStorArr [i] != null) {
					iStorArr [i].Read ();
				}
			}

			GMyClass myClass = new GMyClass ();
			Console.WriteLine ("my class P = {0}", myClass.P);
		}
	}

	public interface IStorable
	{
		void Read ();

		void Write (Object obj);

		void Talk ();

		int Status {
			get;
			set;
		}
	}

	public interface ITalk
	{
		void Talk ();
	}

	public class GDoc : IStorable,ITalk
	{
		public virtual void Read ()
		{
			Console.WriteLine ("GDoc read ...");
		}

		virtual public void Write (Object obj)
		{
			Console.WriteLine ("GDoc write ...");
		}

		public void Talk ()
		{
		}

		void ITalk.Talk ()
		{
		}

		private int status;

		public int Status {
			get;
			set;
		}
	}

	public class GNote : GDoc
	{
		public override void Read ()
		{
			Console.WriteLine ("GNote read ...");
		}

		public override void Write (Object obj)
		{
			Console.WriteLine ("GNote write ...");
		}
	}

	public interface IGBase
	{
		int P {
			get;
			set;
		}
	}

	public interface IGDerived:IGBase
	{
		new int P {
			get;
			set;
		}
	}

	public class GMyClass:IGDerived
	{
		int IGBase_P;

		int IGBase.P {
			get {
				return IGBase_P;
			}
			set { 
				IGBase_P = value;
			}
		}

		int p = 10;

		public int P {
			get {
				return p;
			}
			set { 
				p = value;
			}
		}
	}
}

