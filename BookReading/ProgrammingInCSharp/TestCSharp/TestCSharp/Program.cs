using System;

namespace TestCSharp
{
	static class Global
	{
		public static string ClassName = "Global";

		public static void PrintClassName ()
		{
			Console.WriteLine (ClassName);
		}
	}

	class GStaticMember
	{
		public const int const_imember_0 = 10;
		public static int static_imember_0 = 10;
	}

	class MainClass
	{
		#region test region

		//a test region
		//a define is here
		int a = 10;

		#endregion

		enum SomeValues
		{
			Value_0,
			Value_1,
			Value_20 = 20,
			Value_21
		}

		struct UnsafePoint
		{
			public int x, y;
		}

		public static void ChangeStr (string str)
		{
			str = "after changed\n";
		}

		public static void TestUnsafe (bool isRun)
		{
			if (!isRun)
				return;
			
			unsafe {
				UnsafePoint pt = new UnsafePoint ();
				UnsafePoint* pp = &pt;
				pp->x = 123;
				pp->y = 456;
				Console.WriteLine ("{0} {1}", pt.x, pt.y);

				Console.WriteLine ("x&y = {0}", 15 & 3);
			}
		}

		public static void TestStaticMember (bool isRun)
		{
			if (!isRun)
				return;

			// c# dont support local static variable
			//static int local_ivalue_0 = 12; 
			//const static int local_ivlaue_1 = 10;

			const int local_ivlaue_2 = 11;

			GStaticMember member = new GStaticMember ();
			Console.WriteLine ("const_imember_0 = {0}", GStaticMember.const_imember_0);
			//Console.WriteLine ("const_imember_0 = {0}", member.const_imember_0);
		}

        public static void TestFuncArgTransmit(bool isRun)
        {
            if (!isRun)
				return;

            int value1 = 0;
            FuncRefArg(ref value1);
            Console.WriteLine("FuncRefArg value1 = " + value1);

            int value2;
            FuncOutArg(out value2);
            Console.WriteLine("FuncOutArg value2 = " + value2);
        }
        static void FuncRefArg(ref int arg)
        {
            arg = 1111;
        }
        static void FuncOutArg(out int arg)
        {
            arg = 2222;
        }

		public static void RunBookTest (bool isRun)
		{
			if (!isRun)
				return;
			
			Console.WriteLine ("Hello World!");

			int i = 10;
			int j = 10;
			Console.WriteLine ("object.ReferenceEquals(i,j) = {0}", object.ReferenceEquals (i, j));

            int iValue = 10;
            //Boxing int value
            object oValue = iValue;
            Console.WriteLine("Unboxing oValue result = " + (int)oValue);
            //执行到下面的代码会报错，提示非法的类型转换
            //float fValue = (float)oValue;
            //Console.WriteLine("Unboxing oValue result = " + fValue);

			string str1 = "hello";
			string str2 = "hello";
			Console.WriteLine ("object.ReferenceEquals(str1,str2) = {0}", 
				object.ReferenceEquals (str1, str2));

			string temp = "before changed";
			ChangeStr (temp);
			Console.WriteLine (temp);

			TestUnsafe (false);
			TestInheritance.RunTest (false);

			Person person1 = new Person ("God1");
			person1.Print();
			Person person2 = person1.Clone () as Person;
			person2.Name = "God2";
			Console.WriteLine (person1.Name);
			Console.WriteLine (person2.Name);
			//person.PrintClassName();
			//Person.PrintClassName();

			//Global.PrintClassName();

			SomeValues tmp = SomeValues.Value_0;
			Console.WriteLine (tmp.ToString ());
			Console.WriteLine (10.GetType ());

			OuterClass outer_obj = new OuterClass ();
			outer_obj.ToString ();
			OuterClass.NestedClass nested_class = new OuterClass.NestedClass ();
			nested_class.PrintOuterObjCount ();
			nested_class.PrintNestedObjCount ();

			TestStaticMember (false);
            TestFuncArgTransmit(true);
            TestArgPass.RunTest(true);

            TestFraction.RunTest (false);
			TestStruct.RunTest (false);

			TestInterface.RunTest (true);
			TestDispose.RunTestDispose (false);
			TestArray.RunTest (false);

			TestString.RunTest (false);
			TestDelegateEvent.RunTest (false);
			//TestAttribute.RunTest (true);
		}

		public static void RunAlgorithmTest (bool isRun)
		{
			if (!isRun)
				return;
			ListReverse.RunTest (true);
		}

		public static void Main (string[] args)
		{
			RunBookTest (true);
			RunAlgorithmTest (true);
		}
	}

	class Person:ICloneable
	{
		public static string ClassName = "Person";
		private string name = "Unknown";
        private int age;

		public string Name {
			set{ name = value; }
			get{ return name; }
		}
        public int Age
        {
            set { age = value; }
            get { return age; }
        }

		static Person ()
		{
			ClassName = "StaticPerson";
		}

		public Person (string name)
		{
			this.name = name;
		}

		public void Print ()
		{
			Console.WriteLine(this.name);
            Console.WriteLine(this.age);
		}

		public static void PrintClassName ()
		{
			Console.WriteLine (Person.ClassName);
		}

		public object Clone ()
		{
			Person newObj = new Person (name);
			return newObj;
		}
	}
}

class Test
{
	public static void Run ()
	{
		Console.WriteLine ("Test.Run");
	}
}