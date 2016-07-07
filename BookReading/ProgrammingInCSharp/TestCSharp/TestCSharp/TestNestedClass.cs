using System;

namespace TestCSharp
{
	public class TestNestedClass
	{
		public static void RunTest ()
		{
			
		}
	}
	public class OuterClass
	{
		private static int outer_obj_count = 0;
		public OuterClass()
		{
			outer_obj_count++;
		}
		public class NestedClass
		{
			private static int nested_obj_count = 0;
			public void PrintOuterObjCount()
			{
				Console.WriteLine(outer_obj_count);
			}
			public void PrintNestedObjCount()
			{
				Console.WriteLine(nested_obj_count);
			}
		}
	}
}

