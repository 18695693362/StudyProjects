using System;
using System.Text;
using System.Collections.Generic;

namespace TestCSharp
{
	public class ListReverse
	{
		public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;

			GList<int> tempList = new GList<int> ();
			for (int i = 0; i < 10; i++) {
				GListNode<int> tempNode = new GListNode<int> (i + 10);
				tempList.AddLast (tempNode);
			}

			GList<int>.Reverse (tempList);

			Console.WriteLine ("tempList = {0}", String.Join (", ", tempList));
		}

		class GListNode<T>
		{
			private T value_;

			public T Value {
				set { value_ = value; }
				get{ return value_; }
			}

			private GListNode<T> next_ = null;

			public GListNode<T> Next {
				set{ next_ = value; }
				get{ return next_; }
			}

			public GListNode (T val)
			{
				value_ = val;
			}
		}

		class GList<T>:IEnumerable<T>
		{
			private GListNode<T> first = null;
			private GListNode<T> last = null;

			public GListNode<T> First {
				get{ return first; }
			}

			public GListNode<T> Last {
				get{ return last; }
			}

			public GList ()
			{
			}

			public IEnumerator<T> GetEnumerator ()
			{
				bool isUseType1 = false;
				if (isUseType1) {
					for (GListNode<T> iter = first; iter != null; iter = iter.Next) {
						yield return iter.Value;
					}
				} else {
					GListNode<T> iter = first;
					while (iter != null) {
						yield return iter.Value;
						iter = iter.Next;
					}
				}
			}

			System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator ()
			{  
				return GetEnumerator ();  
			}

			public void AddFirst (T val)
			{
				GListNode<T> node = new GListNode<T> (val);
				AddFirst (node);
			}

			public void AddFirst (GListNode<T> node)
			{
				if (first != null) {
					node.Next = first;
					first = node;
				} else {
					first = node;
					last = node;
				}
			}

			public void AddLast (T val)
			{
				GListNode<T> node = new GListNode<T> (val);
				AddLast (node);
			}

			public void AddLast (GListNode<T> node)
			{
				if (last != null) {
					last.Next = node;
					last = node;
				} else {
					first = node;
					last = node;
				}
			}

			public static GList<T> Reverse (GList<T> list)
			{
				GListNode<T> pre = null;
				GListNode<T> iter = list.first;
				GListNode<T> temp = null;
				//注意：先赋值last
				list.last = list.first; 
				while (iter != null) {
					temp = iter.Next;
					iter.Next = pre;
					pre = iter;
					iter = temp;
				}
				//注意：反转完成后赋值first
				list.first = pre;
				return list;
			}
		}
	}
}

