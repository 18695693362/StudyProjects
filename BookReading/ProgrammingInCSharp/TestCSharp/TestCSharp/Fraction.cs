using System;

namespace TestCSharp
{
	public class TestFraction
	{
		static public void RunTest (bool isRun)
		{
			if (!isRun)
				return;
			Fraction f1 = new Fraction (1, 2);
			Console.WriteLine ("f1 : {0}", f1.ToString ());
			Fraction f2 = new Fraction (2, 4);
			Console.WriteLine ("f2 : {0}", f2.ToString ());
			Fraction f3 = f1 + f2;
			Console.WriteLine ("f3 = f1 + f2 : {0}", f3.ToString ());
			Fraction f4 = f3 + 5;
			Console.WriteLine ("f4 = f3 + 5 : {0}", f4.ToString ());
			if (f1 == f2) {
				Console.WriteLine ("f1:{0} == f2:{1}", f1.ToString (), f2.ToString ());
			}

			Console.WriteLine (f4.Denominator);
			//f4.Denominator = 100;
			Console.WriteLine (f4.Denominator);
		}
	}

	public class Fraction
	{
		private int numerator;

		public int Numerator {
			get {
				return numerator;
			}
			set {
				numerator = value;
			}
		}

		private int denominator;

		public int Denominator {
			get {
				return denominator;
			}
			protected set {
				denominator = value;
			}
		}

		public Fraction (int numerator, int denominator)
		{
			this.Numerator = numerator;
			this.denominator = denominator;
		}

		public Fraction (int value)
		{
			this.numerator = value;
			this.denominator = 1;
		}

		public static implicit operator Fraction (int theInt)
		{
			return new Fraction (theInt);
		}

		public static explicit operator int (Fraction fraction)
		{
			return fraction.numerator / fraction.denominator;
		}

		public static bool operator== (Fraction lhs, Fraction rhs)
		{
			if (lhs.denominator == rhs.denominator &&
			    lhs.numerator == rhs.numerator) {
				return true;
			}
			return lhs.numerator / lhs.denominator == rhs.numerator / rhs.denominator;
		}

		public static bool operator!= (Fraction lhs, Fraction rhs)
		{
			return !(lhs == rhs);
		}

		public override bool Equals (object o)
		{
			if ((o is Fraction)) {
				return false;
			}
			return this == (Fraction)o;
		}

		public override int GetHashCode ()
		{
			return base.GetHashCode ();
		}

		public static Fraction operator+ (Fraction lhs, Fraction rhs)
		{
			if (lhs.denominator == rhs.denominator) {
				return new Fraction (lhs.numerator + rhs.numerator, lhs.denominator);	
			} else {
				int newDenominator = lhs.denominator * rhs.denominator;
				return new Fraction (lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator,
					newDenominator);
			}
		}

		public override string ToString ()
		{
			string s = numerator.ToString () + "/" + denominator.ToString ();
			return s;
		}
	}
}

