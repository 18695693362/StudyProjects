using System;

namespace TestCSharp
{
	public class TestNestedClass
	{
		public static void RunTest ()
		{
            OuterClass obj = new OuterClass();
		}
	}
	public class OuterClass
	{
		private static int outer_obj_count = 0;
		public OuterClass()
		{
			outer_obj_count++;
            NestedClass.PrintInfo ( );
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
            static protected internal void PrintInfo()
            {
                Console.WriteLine ( "invoke static protected internal function!" );
            }
		}
	}
}

