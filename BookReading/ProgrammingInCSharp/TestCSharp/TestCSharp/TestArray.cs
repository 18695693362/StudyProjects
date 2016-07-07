using System;
using System.Collections;
using System.Collections.Generic;

namespace TestCSharp
{
	public class TestArray
	{
		public static void RunArrayTest ()
		{
			Employee[] empArr = {
				new Employee (110),
				new Employee (111),
				new Employee (112)
			};
			//			for (int i = 0; i < empArr.Length; i++) {
			//				empArr [i] = new Employee (i + 10);
			//			}

			foreach (Employee emp in empArr) {
				Console.WriteLine (emp.EmpID);
			}

			int[] intArr = { 11115, 11112, 11113, 11114 };
			Array.Sort (intArr);
			PrintIntArray (intArr);
			PrintIntArray (1111, 1112, 1113);

			int[] lengthArr = { 2, 3, 4 };
			int[] boundArr = { 2, 4, 1 };
			Array multiArr = Array.CreateInstance (typeof(int), lengthArr, boundArr);
			Console.WriteLine ("Bounds:\tLower\tUpper");
			for (int i = 0; i < multiArr.Rank; i++) {
				Console.WriteLine ("{0}:\t{1}\t{2}",
					i,
					multiArr.GetLowerBound (i),
					multiArr.GetUpperBound (i)
				);
			}
			Console.WriteLine (multiArr.ToString ());
			//multiArr [1, 1, 1] = 10;
			multiArr.SetValue (10, 2, 4, 1);
			Console.WriteLine (multiArr.GetValue (2, 4, 1));

			float[] floatArr = { 1.0f, 1.1f, 1.2f };
			PrintArray<float> (floatArr);
			double[] doubleArr = { 2.0, 2.1, 2.2 };
//			doubleArr = (double[])floatArr;
//			PrintArray<double> (doubleArr);
//			Object[] objArr = intArr;
//					
//			PrintArray<Object> (objArr);

			ListBox lstBox = new ListBox ("My", "Name", "is", "God", "!");
			Console.WriteLine (lstBox [1]);
			lstBox [10] = "HelloWorld";
			lstBox ["Na"] = "-name-";
			for (int i = 0; i < lstBox.Count; i++) {
				Console.WriteLine (lstBox [i]);
			}
			foreach (string s in lstBox) {
				//Console.WriteLine (s);
			}
		}

		public static void RunLinkedListTest ()
		{
			LinkedList<int> myLinkList = new LinkedList<int> ();
			Random rand = new Random ();
			for (int i = 0; i < 10; i++) {
				int nextInt = rand.Next (10);
				myLinkList.Add (nextInt);
			}

			Console.WriteLine ("int link list = " + myLinkList);
		}

		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;

			//RunArrayTest ();

			List<Employee> empList = new List<Employee> ();
			Random rand = new Random ();
			for (int i = 0; i < 6; i++) {
				int tempId = rand.Next (10);
				empList.Add (new Employee (i + tempId, i));
			}
			empList.Sort ();
			foreach (Employee emp in empList) {
				Console.WriteLine (emp.ToString ());
			}
			Employee.EmployeeComparer comparer = Employee.GetComparer ();
			comparer.CompType = Employee.EmployeeComparer.ComparerType.YearOfSvr;
			empList.Sort (comparer);
			foreach (Employee emp in empList) {
				Console.WriteLine (emp.ToString ());
			}
			Console.WriteLine (empList.Capacity);
		}

		public static void PrintIntArray (params int[] intArr)
		{
			foreach (int value in intArr) {
				Console.WriteLine (value);
			}
		}

		public static void PrintArray<Type> (params Type[] arr)
		{
			foreach (Type value in arr) {
				Console.WriteLine (value);
			}
		}
	}

	public class Employee:IComparable<Employee>
	{
		private int empID;
		private int yearsOfSvr = 1;

		public int EmpID {
			get{ return empID; }
			set{ empID = value; }
		}

		public int YearsOfSvr {
			get{ return yearsOfSvr; }
			set{ yearsOfSvr = value; }
		}

		public Employee (int empID)
		{
			this.empID = empID;
		}

		public Employee (int empID, int yearsOfSvr)
		{
			this.empID = empID;
			this.yearsOfSvr = yearsOfSvr;
		}

		public static EmployeeComparer GetComparer ()
		{
			return new EmployeeComparer ();
		}

		public int CompareTo (Employee rhs)
		{
			return this.empID.CompareTo (rhs.EmpID);
		}

		public int CompareTo (Employee rhs, EmployeeComparer.ComparerType cmpType)
		{
			switch (cmpType) {
			case EmployeeComparer.ComparerType.EmpID:
				return this.empID.CompareTo (rhs.EmpID);
			case EmployeeComparer.ComparerType.YearOfSvr:
				return this.yearsOfSvr.CompareTo (rhs.yearsOfSvr);
			}
			return 0;
		}

		public override string ToString ()
		{
			return string.Format ("EmpID={0}, SvrYears={1}", empID, yearsOfSvr);
		}

		public class EmployeeComparer:IComparer<Employee>
		{
			public enum ComparerType
			{
				EmpID,
				YearOfSvr
			}

			private ComparerType compType;

			public ComparerType CompType {
				get{ return compType; }
				set{ compType = value; }
			}

			public bool Equals (Employee lhs, Employee rhs)
			{
				return lhs.CompareTo (rhs) == 0;
			}

			public int GetHashCode (Employee e)
			{
				return e.GetHashCode ();
			}

			public int Compare (Employee lhs, Employee rhs)
			{
				return lhs.CompareTo (rhs, compType);
			}
		}
	}

	public class ListBox:IEnumerable<string>
	{
		public ListBox (params string[] init_strs)
		{
			strings = new string[256];
			foreach (string str in init_strs) {
				strings [count++] = str;
			}
		}

		public IEnumerator<string> GetEnumerator ()
		{
			foreach (string s in strings) {
				yield return s;
			}
		}

		IEnumerator IEnumerable.GetEnumerator ()
		{
			return GetEnumerator ();
		}

		public void Add (string item)
		{
			if (count >= strings.Length) {
				//
			} else {
				strings [count++] = item;
			}
		}

		public string this [int index] {
			get {
				if (index >= count) {
					return "";
				} else {
					return strings [index];
				}
			}
			set {
				if (index >= strings.Length) {
					//
				} else {
					if (index >= count) {
						count = index + 1;
					}
					strings [index] = value;
				}
			}
		}

		public string this [string index] {
			get {
				int idx = findString (index);
				if (idx != -1) {
					return strings [idx];
				} else {
					return "";
				}
			}
			set {
				int idx = findString (index);
				if (idx != -1) {
					strings [idx] = value;
				} else {
					//
				}
			}
		}

		private int findString (string str)
		{
			for (int i = 0; i < count; i++) {
				if (strings [i].StartsWith (str)) {
					return i;
				}
			}
			return -1;
		}

		public int Count {
			get {
				return count;
			}
			//private set;
		}

		private string[] strings;
		private int count;
	}

	public class Node<T>:IComparable<Node<T>> where T : IComparable<T>
	{
		private T data;
		private Node<T> prev;
		private Node<T> next;

		public Node (T data)
		{
			this.data = data;
		}

		public T Data{ get { return data; } }

		public Node<T> Next { get { return next; } }

		public int CompareTo (Node<T> rhs)
		{
			return data.CompareTo (rhs.Data);
		}

		public bool Equals (Node<T> rhs)
		{
			return data.Equals (rhs.Data);
		}

		public Node<T> Add (Node<T> newNode)
		{
			if (this.CompareTo (newNode) > 0) {
				newNode.next = this;
				if (this.prev != null) {
					this.prev.next = newNode;
					newNode.prev = this.prev;
				}
				this.prev = newNode;

				return newNode;
			} else {
				if (this.next != null) {
					this.next.Add (newNode);
				} else {
					this.next = newNode;
					newNode.prev = this;
				}
				return this;
			}
		}

		public override string ToString ()
		{
			string output = data.ToString ();
			if (next != null) {
				output += ", "	+ next.ToString ();
			}
			return output;
		}
	}

	public class LinkedList<T> where T : IComparable<T>
	{
		private Node<T> headNode = null;

		public T this [int index] {
			get {
				int count = 0;
				Node<T> node = headNode;
				while (node != null && count <= index) {
					if (count == index) {
						return node.Data;
					} else {
						count++;
						node = node.Next;
					}
				}
				throw new ArgumentOutOfRangeException ();
			}
		}

		public void Add (T data)
		{
			if (headNode == null) {
				headNode = new Node<T> (data);
			} else {
				headNode.Add (new Node<T> (data));
			}
		}

		public override string ToString ()
		{
			if (headNode == null) {
				return string.Empty;
			} else {
				return this.headNode.ToString ();
			}
		}
	}
}

