using System;

namespace TestCSharp
{
	public class TestDispose:IDisposable
	{
		public static void RunTestDispose (bool isRun)
		{
			if (!isRun)
				return;

			TestDispose temp = new TestDispose ();
			temp.Dispose ();
		}

		string name = "TestDispose - name";
		bool is_disposed = false;

		public TestDispose ()
		{
		}

		protected virtual void Dispose (bool disposing)
		{
			if (!is_disposed) {
				if (disposing) {
					Console.WriteLine ("Not in destructor,Ok to reference other objects");
				}
				Console.WriteLine ("Disposing ... ");
			} else {
				Console.WriteLine ("Disposed ###");
			}
			is_disposed = true;
		}

		public void PrintName ()
		{
			Console.WriteLine (name);
		}

		public void Dispose ()
		{
			Dispose (true);
			GC.SuppressFinalize (this);
		}

		~TestDispose ()
		{
			Dispose (false);
			Console.WriteLine ("In destructor");
		}
	}
}

