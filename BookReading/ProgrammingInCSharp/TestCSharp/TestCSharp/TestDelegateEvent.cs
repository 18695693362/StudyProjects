using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

namespace TestCSharp
{
	public class TestDelegateEvent
	{
		public static void RunDelegateTest ()
		{
			DelegateTest.Student stu1 = new DelegateTest.Student ("Stu1");
			Pair<DelegateTest.Student> pairStu = new Pair<DelegateTest.Student> (stu1,
				                                     new DelegateTest.Student ("Stu2"));
			Pair<DelegateTest.Student>.WhichIsFirst stDele1 = new Pair<DelegateTest.Student>.WhichIsFirst (
				                                                  DelegateTest.Student.WhichStudentComesFirst
			                                                  );
			//			Pair<DelegateTest.Student>.WhichIsFirst stDele2 = new Pair<DelegateTest.Student>.WhichIsFirst (
			//				                                                  stu1.WhichStudentComesFirst
			//			                                                  );
			pairStu.ReverseSort (DelegateTest.Student.WhichStudentComesFirst);
			Console.WriteLine ("pairStu ------------------ 1");
			Console.WriteLine (pairStu);
			pairStu.Sort (stDele1);
			Console.WriteLine ("pairStu ------------------ 2");
			Console.WriteLine (pairStu);
			pairStu.ReverseSort (DelegateTest.Student.OrderStudents);
			Console.WriteLine ("pairStu ------------------ 3");
			Console.WriteLine (pairStu);

			DelegateTest.Dog dog1 = new DelegateTest.Dog ("Dog1");
			Pair<DelegateTest.Dog> pairDog = new Pair<DelegateTest.Dog> (dog1,
				                                 new DelegateTest.Dog ("Dog2"));
			pairDog.ReverseSort (DelegateTest.Dog.OrderDogs);
			Console.WriteLine ("pairDog ------------------ 1");
			Console.WriteLine (pairDog);
		}

		public static void RunMultiDelegate ()
		{
			MultiDelegate.MyClassWithDelegate.StringDelegate writer, logger, transmiter;
			writer = new MultiDelegate.MyClassWithDelegate.StringDelegate (
				MultiDelegate.MyImplClass.WriteStr);
			logger = new MultiDelegate.MyClassWithDelegate.StringDelegate (
				MultiDelegate.MyImplClass.LogStr);
			transmiter = new MultiDelegate.MyClassWithDelegate.StringDelegate (
				MultiDelegate.MyImplClass.TransmitStr);

			writer ("str pass to writer");
			logger ("str pass to logger");

			MultiDelegate.MyClassWithDelegate.StringDelegate multiDelegate = writer + transmiter;
			multiDelegate ("str pass to writer+transmiter");
			multiDelegate += logger; 
			multiDelegate ("str pass to writer+transmiter+loger");
			multiDelegate -= transmiter; 
			multiDelegate ("str pass to writer+transmiter+loger-transmiter");
			multiDelegate += logger; 
			multiDelegate ("str pass to writer+loger+loger");
		}

		static void RunEventTest ()
		{
			Clock clock = new Clock ();

			DisplayClock showClock = new DisplayClock ();
			showClock.Subsribe (clock);
			LogCurrentTime logger = new LogCurrentTime ();
			logger.Subsribe (clock);

			clock.Run ();
		}

		static void RunDelegateReturnInt ()
		{
			ClassWithReturnIntDelegate tmpClass = new ClassWithReturnIntDelegate ();
			ClassWithReturnIntDelegate.FirstSubscriber fst = new ClassWithReturnIntDelegate.FirstSubscriber ();
			fst.Subscribe (tmpClass);
			ClassWithReturnIntDelegate.SecondSubscriber scd = new ClassWithReturnIntDelegate.SecondSubscriber ();
			scd.Subscribe (tmpClass);
			int result = tmpClass.returnIntDelegate ();
			Console.WriteLine ("result = {0}", result);
			result = tmpClass.returnIntDelegate ();
			Console.WriteLine ("result = {0}", result);
			result = tmpClass.returnIntDelegate ();
			Console.WriteLine ("result = {0}", result);

			tmpClass.Run ();
		}

		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			
			//RunMultiDelegate ();
			//RunEventTest ();
			RunDelegateReturnInt ();
		}
	}

	public class Pair<T>
	{
		private T first;
		private T second;

		T First{ set { first = value; } get { return first; } }

		T Second{ set { second = value; } get { return second; } }

		public delegate Comparison WhichIsFirst (T obj1, T obj2);

		WhichIsFirst compDelegate;

		public WhichIsFirst Comparer {
			set { compDelegate = value; }
		}

		public enum Comparison
		{
			theFirstComesFromFirst,
			theSecondComesFromFirst
		}

		public Pair (T first, T second)
		{
			this.first = first;
			this.second = second;
		}

		public override string ToString ()
		{
			return string.Format ("[Pair: {0} {1}]", first, second);
		}

		public void Sort (WhichIsFirst theDelegatedFunc)
		{
			if (theDelegatedFunc (first, second) == Comparison.theSecondComesFromFirst) {
				T temp = first;
				first = second;
				second = temp;
			}
		}

		public void ReverseSort (WhichIsFirst theDelegatedFunc)
		{
			if (theDelegatedFunc (first, second) == Comparison.theFirstComesFromFirst) {
				T temp = first;
				first = second;
				second = temp;
			}			
		}
	}

	namespace DelegateTest
	{
		class Student
		{
			public Student (string name)
			{
				this.name = name;
			}

			public static readonly Pair<Student>.WhichIsFirst OrderStudents = 
				new Pair<Student>.WhichIsFirst (Student.WhichStudentComesFirst);

			private string name;

			public string Name{ set { name = value; } get { return name; } }

			public override string ToString ()
			{
				return string.Format ("[Student: Name={0}]", Name);
			}

			public static Pair<Student>.Comparison WhichStudentComesFirst (Student lhs, Student rhs)
			{
				if (String.Compare (lhs.name, rhs.name) < 0) {
					return	Pair<Student>.Comparison.theFirstComesFromFirst;
				} else {
					return Pair<Student>.Comparison.theSecondComesFromFirst;
				}
			}
		}

		class Dog
		{
			public Dog (string name)
			{
				this.name = name;
			}

			private static Pair<Dog>.WhichIsFirst orderDogs = null;

			public static Pair<Dog>.WhichIsFirst OrderDogs {
				get {
					if (Dog.orderDogs == null) {
						Dog.orderDogs = new Pair<Dog>.WhichIsFirst (Dog.WhichDogComesFirst);
					}
					return Dog.orderDogs;
				}
			}


			private string name;

			public string Name{ set { name = value; } get { return name; } }

			public override string ToString ()
			{
				return string.Format ("[Dog: Name={0}]", Name);
			}

			public static Pair<Dog>.Comparison WhichDogComesFirst (Dog lhs, Dog rhs)
			{
				if (String.Compare (lhs.name, rhs.name) < 0) {
					return	Pair<Dog>.Comparison.theFirstComesFromFirst;
				} else {
					return Pair<Dog>.Comparison.theSecondComesFromFirst;
				}
			}
		}
	}

	namespace MultiDelegate
	{
		public class MyClassWithDelegate
		{
			public delegate void StringDelegate (string s);
		}

		public class MyImplClass
		{
			public static void WriteStr (string s)
			{
				Console.WriteLine ("// Write String     -- {0}", s);
			}

			public static void LogStr (string s)
			{
				Console.WriteLine ("// Log String       -- {0}", s);
			}

			public static void TransmitStr (string s)
			{
				Console.WriteLine ("// Transimit String -- {0}", s);
			}
		}
	}

	public class TimeInfoEventArgs : EventArgs
	{
		public readonly int hour;
		public readonly int minute;
		public readonly int seconds;

		public TimeInfoEventArgs (int hour, int minute, int seconds)
		{
			this.hour = hour;
			this.minute = minute;
			this.seconds = seconds;
		}
	}

	public class Clock
	{
		private int hour;
		private int minute;
		private int seconds;

		public delegate void SecondChangeHandler (object clock, TimeInfoEventArgs args);

		public event SecondChangeHandler OnSecondChanged;

		public void Run ()
		{
			while (true) {
				Thread.Sleep (10);
				System.DateTime dt = System.DateTime.Now;
				if (dt.Second != seconds) {
					TimeInfoEventArgs eventArgs = new TimeInfoEventArgs (dt.Hour,
						                              dt.Minute, dt.Second);
					if (OnSecondChanged != null) {
						OnSecondChanged (this, eventArgs);
					}
				}
				this.hour = dt.Hour;
				this.minute = dt.Minute;
				this.seconds = dt.Second;
			}
		}

	}

	public class DisplayClock
	{
		public void Subsribe (Clock clock)
		{
			clock.OnSecondChanged += new Clock.SecondChangeHandler (TimeHasChanged);
			clock.OnSecondChanged += delegate (object obj, TimeInfoEventArgs args) {
				Console.WriteLine ("current time h{0}-m{1}-s{2}", args.hour, args.minute, args.seconds);	
			};
		}

		public void TimeHasChanged (object clock, TimeInfoEventArgs args)
		{
			Console.WriteLine ("current time {0}:{1}:{2}", args.hour, args.minute, args.seconds);
		}
	}

	public class LogCurrentTime
	{
		public void Subsribe (Clock clock)
		{
			clock.OnSecondChanged += new Clock.SecondChangeHandler (WriteLogEntity);
			//clock.OnSecondChanged = new Clock.SecondChangeHandler (WriteLogEntity);
		}

		public void WriteLogEntity (object clock, TimeInfoEventArgs args)
		{
			Console.WriteLine ("logging to console {0}:{1}:{2}", args.hour, args.minute, args.seconds);
		}
	}

	public class ClassWithReturnIntDelegate
	{
		public delegate int DelegateReturnInt ();

		public DelegateReturnInt returnIntDelegate;

		public void Run ()
		{
			while (true) {
				Thread.Sleep (1000);

				foreach (DelegateReturnInt subDelegate in returnIntDelegate.GetInvocationList()) {
					int result = subDelegate ();
					Console.WriteLine ("result = {0}", result);
				}
				Console.WriteLine ();
			}
		}

		public class FirstSubscriber
		{
			private int myCounter = 0;

			public void Subscribe (ClassWithReturnIntDelegate theClass)
			{
				theClass.returnIntDelegate += delegate {
					Thread.Sleep (1000);
					return ++myCounter;
				};
			}
		}

		public class SecondSubscriber
		{
			private int myCounter = 0;

			public void Subscribe (ClassWithReturnIntDelegate theClass)
			{
				theClass.returnIntDelegate += delegate {
					return myCounter += 2;
				};
			}
		}
	}
}

