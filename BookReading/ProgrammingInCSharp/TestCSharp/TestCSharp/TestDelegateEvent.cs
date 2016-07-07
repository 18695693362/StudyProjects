using System;
using System.Collections;
using System.Collections.Generic;

namespace TestCSharp
{
	public class TestDelegateEvent
	{
		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			
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
}

