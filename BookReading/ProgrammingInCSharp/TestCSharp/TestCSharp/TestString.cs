using System;
using System.Text;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace TestCSharp
{
	public class TestString
	{
		public TestString ()
		{
		}

		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;

			string line = "My name is God!";
			char[] lineCharArr = line.ToCharArray ();
			lineCharArr [0] = 'm';
			line = new string (lineCharArr);
			Console.WriteLine (line);

			StringBuilder mutableStr = new StringBuilder ("My name is God!");
			mutableStr [0] = 'm';
			Console.WriteLine (mutableStr);
		}
	}

}

