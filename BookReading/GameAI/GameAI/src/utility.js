/**
 * Created by guodong on 12/9/15.
 */
var MM = MM || {}

MM.MakeSingleton = function (SingletonClass)
{
    cc.assert(SingletonClass,"singleton class is null!")
    if(!SingletonClass.GetInstance)
    {
        SingletonClass.GetInstance = function ()
        {
            if(!SingletonClass.__singleon)
            {
                SingletonClass.__singleon = new SingletonClass()
            }
            return SingletonClass.__singleon
        }
    }
}

MM.Log = function (log_str)
{
    cc.log(log_str)
}
