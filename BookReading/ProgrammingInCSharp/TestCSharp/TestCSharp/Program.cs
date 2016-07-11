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

			TestFraction.RunTest (false);
			TestStruct.RunTest (false);

			TestInterface.RunTest (true);
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