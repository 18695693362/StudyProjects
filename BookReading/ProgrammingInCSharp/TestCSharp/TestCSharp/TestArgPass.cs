using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCSharp
{

    public class TestArgPass
    {
        public static void RunTest (bool isRun)
		{
			if (!isRun)
				return;
            CArgType tmp = new CArgType();
            tmp._i_member = 200;
            CArgType.ChangeObjV0(tmp);
            Console.WriteLine("tmp._i_member = " + tmp._i_member);
            CArgType.ChangeObjV1(ref tmp);
            Console.WriteLine("tmp._i_member = " + tmp._i_member);
            CArgType.ChangeObjV2(out tmp);
            Console.WriteLine("tmp._i_member = " + tmp._i_member);
            int tmpV = 200;
            CArgType.ChangeValueV0(tmpV);
            Console.WriteLine("tmpV = " + tmpV);
            CArgType.ChangeValueV1(ref tmpV);
            Console.WriteLine("tmpV = " + tmpV);
            CArgType.ChangeValueV2(out tmpV);
            Console.WriteLine("tmpV = " + tmpV);
		}
    }
    public class CArgType
    {
        public int _i_member = 10;
        public static void ChangeObjV0(CArgType arg)
        {
            arg._i_member += 1;
        }
        public static void ChangeObjV1(ref CArgType arg)
        {
            arg._i_member += 1;
        }
        public static void ChangeObjV2(out CArgType arg)
        {
            arg = new CArgType();
            arg._i_member += 1;
        }
        public static void ChangeValueV0(int arg)
        {
            arg += 10;
        }
        public static void ChangeValueV1(ref int arg)
        {
            arg += 10;
        }
        public static void ChangeValueV2(out int arg)
        {
            arg = 100;
            arg += 10;
        }
    }
}
