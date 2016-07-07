using System;

namespace TestCSharp
{
	public class TestStruct
	{
		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			Student stu1 = new Student ();
			Console.WriteLine ("stu1.name = {0}", stu1.name);
			Console.WriteLine ("stu1.age = {0}", stu1.age);

			Student stu2;
			stu2.name = "hi";
			stu2.age = 100;
			Console.WriteLine ("stu2.name = {0}", stu2.name);
			Console.WriteLine ("stu2.age = {0}", stu2.age);
			//stu2.PrintGrade ();
		}
	}

	public struct Student
	{
		public string name;
		public int age;
		private int grade;

		public void PrintGrade ()
		{
			Console.WriteLine ("grade = {0}", grade);
		}
	}
}

