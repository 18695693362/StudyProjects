using System;
using System.Reflection;

namespace TestCSharp
{
	public class TestAttribute
	{
		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			

//			RunGetMetaData ();
//			RunGetType ();
//			RunReflectType ();
			RunDelayBinding ();
		}

		public static void RunGetMetaData ()
		{
			MyMath temp = new MyMath ();
			Console.WriteLine ("DoFunc1 result = {0}", temp.DoFunc1 (3.0));

			System.Reflection.MemberInfo info = typeof(MyMath);
			object[] attri_arr = info.GetCustomAttributes (typeof(BugFixAttribute), false);
			foreach (object attri in attri_arr) {
				BugFixAttribute pAttri = (BugFixAttribute)attri;
				Console.WriteLine ("\nBugID:      {0}", pAttri.BugID);
				Console.WriteLine ("Programmer: {0}", pAttri.Programmer);
				Console.WriteLine ("Date:       {0}", pAttri.Date);
				Console.WriteLine ("Comment:    {0}", pAttri.Comment);
			}
		}

		public static void RunGetType ()
		{
			Assembly a = Assembly.Load ("mscorlib");
			Type[] types = a.GetTypes ();
			foreach (Type t in types) {
				Console.WriteLine ("Type is {0}", t);
			}
			Console.WriteLine ("{0} types found", types.Length);
		}

		public static void RunReflectType ()
		{
			Type theType = Type.GetType ("System.Reflection.Assembly");
			Console.WriteLine ("\nSingle Type is {0}\n", theType);

			MemberInfo[] memberInfoArr = theType.GetMembers ();
			foreach (MemberInfo info in memberInfoArr) {
				Console.WriteLine ("{0} is a {1}", info, info.MemberType);
			}
			Console.WriteLine ("{0} members found\n", memberInfoArr.Length);

			MethodInfo[] methodInfoArr = theType.GetMethods ();
			foreach (MethodInfo info in methodInfoArr) {
				Console.WriteLine ("{0} is a {1}", info, info.MemberType);
			}
			Console.WriteLine ("{0} methods found\n", methodInfoArr.Length);

			MemberInfo[] someMemberInfoArr = theType.FindMembers (MemberTypes.Method,
				                                 BindingFlags.Public |
				                                 BindingFlags.Static |
				                                 BindingFlags.NonPublic |
				                                 BindingFlags.Instance,
				                                 Type.FilterName, "Get*");
			foreach (MethodInfo info in someMemberInfoArr) {
				Console.WriteLine ("{0} is a {1}", info, info.MemberType);
			}
			Console.WriteLine ("FindMembers: {0} methods found\n", methodInfoArr.Length);
		}

		public static void RunDelayBinding ()
		{
			Type theMathType = Type.GetType ("System.Math");
			Type[] paramTypes = new Type[1];
			paramTypes [0] = Type.GetType ("System.Double");
			MethodInfo info = theMathType.GetMethod ("Cos", paramTypes);
			Object[] parameters = new Object[1];
			parameters [0] = 60 * (Math.PI / 180);
			Object returnVal = info.Invoke (theMathType, parameters);
			Console.WriteLine ("The cosine of a 60 degree angle {0}", returnVal);
		}
	}

	[AttributeUsage (AttributeTargets.Class |
	AttributeTargets.Constructor |
	AttributeTargets.Delegate |
	AttributeTargets.Field |
	AttributeTargets.Method |
	AttributeTargets.Property,
		AllowMultiple = true)]
	public class BugFixAttribute : System.Attribute
	{
		public BugFixAttribute (int bugID, string programmer, string date)
		{
			this.bugID = bugID;
			this.programmer = programmer;
			this.date = date;
		}

		private string comment;

		public string Comment {
			get{ return comment; }
			set{ comment = value; }
		}

		private int bugID;

		public int BugID{ get { return bugID; } }

		private string programmer;

		public string Programmer{ get { return programmer; } }

		private string date;

		public string Date{ get { return date; } }
	}

	[BugFix (101, "GuoDong", "2016-07-09")]
	[BugFix (102, "GuoDong", "2016-07-10", Comment = "comment 1")]
	public class MyMath
	{
		public double DoFunc1 (double param)
		{
			return param + this.DoFunc2 (param);
		}

		public double DoFunc2 (double param)
		{
			return param / 3;
		}
	}
}

