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

		public static void Main (string[] args)
		{

			Console.WriteLine ("Hello World!");

			TestInheritance.RunTest (false);
		
			Person person1 = new Person ("God1");
			//person.Print();
			Person person2 = person1.Clone () as Person;
			person2.Name = "God2";
			Console.WriteLine (person1.Name);
			Console.WriteLine (person2.Name);
			//person.PrintClassName();
			//Person.PrintClassName();

			//Global.PrintClassName();

			SomeValues
			tmp = SomeValues.Value_0;
			Console.WriteLine (tmp.ToString ());
			Console.WriteLine (10.GetType ());

			OuterClass outer_obj = new OuterClass ();
			outer_obj.ToString ();
			OuterClass.NestedClass nested_class = new OuterClass.NestedClass ();
			nested_class.PrintOuterObjCount ();
			nested_class.PrintNestedObjCount ();

			TestStaticMember (true);

			TestFraction.RunTest (false);
			TestStruct.RunTest (false);

			TestInterface.RunTest (false);
			TestArray.RunTest (false);

			TestString.RunTest (false);
			TestDelegateEvent.RunTest (false);
			//TestAttribute.RunTest (true);
		}
	}

	class Person:ICloneable
	{
		public static string ClassName = "Person";
		private string name = "Unknown";

		public string Name {
			set{ name = value; }
			get{ return name; }
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
			Console.WriteLine (this.name);
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