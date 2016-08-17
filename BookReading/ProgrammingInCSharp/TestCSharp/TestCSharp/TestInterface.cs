﻿using System;

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

			int iValue = 10;
			Console.WriteLine ("iValue is object = {0}", iValue is object);
			Console.WriteLine ("iValue as object = {0}", iValue as object);
			Console.WriteLine ("iValue is int    = {0}", iValue is int);

			//Console.WriteLine ("iValue as int    = {0}", iValue as int);

			RunStructTest (false);
			RunEventInterface (true);
		}

		static public void RunStructTest (bool isRun)
		{
			if (!isRun)
				return;
			
			GStudentA stu1 = new GStudentA ("God1");
			IChangeName iCN = stu1;
			iCN.Name = "God2";
			Console.WriteLine ("stu1 name = {0}", stu1.Name);
			Console.WriteLine ("iCN  name = {0}", iCN.Name);

			GStudentB stu2 = new GStudentB ("Dog1"); // GStudentB is a sealed class
			IChangeName iCN2 = stu2;
			iCN2.Name = "Dog2";
			Console.WriteLine ("stu2 name = {0}", stu2.Name);
			Console.WriteLine ("iCN2 name = {0}", iCN2.Name);
		}

		static public void RunEventInterface (bool isRun)
		{
			if (!isRun)
				return;

			Shape shape = new Shape ();
			Subscriber1 sub = new Subscriber1 (shape);
			Subscriber2 sub2 = new Subscriber2 (shape);
			shape.Draw ();

			// Keep the console window open in debug mode.
			System.Console.WriteLine ("Press any key to exit.");
			System.Console.ReadKey ();
			/* Output:
    			Sub1 receives the IDrawingObject event.
    			Drawing a shape.
    			Sub2 receives the IShape event.
			*/
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

	public interface IChangeName
	{
		string Name {
			set;
			get;
		}
	}

	public struct GStudentA:IChangeName
	{
		private string name;

		public string Name {
			set{ name = value; }
			get{ return name; }
		}

		public GStudentA (string name)
		{
			this.name = name;
		}
	}

	public sealed class GStudentB:IChangeName
	{
		private string name;

		public string Name {
			set{ name = value; }
			get{ return name; }
		}

		public GStudentB (string name)
		{
			this.name = name;
		}
	}

	public interface IDrawingObject
	{
		// Raise this event before drawing
		// the object.
		event EventHandler OnDraw;
	}

	public interface IShape
	{
		// Raise this event after drawing
		// the shape.
		event EventHandler OnDraw;
	}


	// Base class event publisher inherits two
	// interfaces, each with an OnDraw event
	public class Shape : IDrawingObject, IShape
	{
		// Create an event for each interface event
		event EventHandler PreDrawEvent;
		event EventHandler PostDrawEvent;

		object objectLock = new Object ();

		// Explicit interface implementation required.
		// Associate IDrawingObject's event with
		// PreDrawEvent
		event EventHandler IDrawingObject.OnDraw {
			add {
				lock (objectLock) {
					PreDrawEvent += value;
				}
			}
			remove {
				lock (objectLock) {
					PreDrawEvent -= value;
				}
			}
		}
		// Explicit interface implementation required.
		// Associate IShape's event with
		// PostDrawEvent
		event EventHandler IShape.OnDraw {
			add {
				lock (objectLock) {
					PostDrawEvent += value;
				}
			}
			remove {
				lock (objectLock) {
					PostDrawEvent -= value;
				}
			}


		}

		// For the sake of simplicity this one method
		// implements both interfaces.
		public void Draw ()
		{
			// Raise IDrawingObject's event before the object is drawn.
			EventHandler handler = PreDrawEvent;
			if (handler != null) {
				handler (this, new EventArgs ());
			}
			Console.WriteLine ("Drawing a shape.");

			// RaiseIShape's event after the object is drawn.
			handler = PostDrawEvent;
			if (handler != null) {
				handler (this, new EventArgs ());
			}
		}
	}

	public class Subscriber1
	{
		// References the shape object as an IDrawingObject
		public Subscriber1 (Shape shape)
		{
			IDrawingObject d = (IDrawingObject)shape;
			d.OnDraw += new EventHandler (d_OnDraw);
		}

		void d_OnDraw (object sender, EventArgs e)
		{
			Console.WriteLine ("Sub1 receives the IDrawingObject event.");
		}
	}
	// References the shape object as an IShape
	public class Subscriber2
	{
		public Subscriber2 (Shape shape)
		{
			IShape d = (IShape)shape;
			d.OnDraw += new EventHandler (d_OnDraw);
		}

		void d_OnDraw (object sender, EventArgs e)
		{
			Console.WriteLine ("Sub2 receives the IShape event.");
		}
	}
}


