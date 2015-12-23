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
        SingletonClass.ClearInstance = function () {
            if(SingletonClass.__singleon)
            {
                if(SingletonClass.OnClear)
                {
                    SingletonClass.OnClear.call(SingletonClass.__singleon)
                    SingletonClass.__singleon = null
                }
            }
        }
    }
}

MM.Log = function (log_str)
{
    cc.log(log_str)
}
MM.assert = function ()
{
    cc.assert.apply(cc.assert,arguments)
}
MM.GetObjStr = function (obj)
{
    return JSON.stringify(obj,null,4)
}
MM.PrintObj = function (obj)
{
    var obj_str = MM.GetObjStr(obj)
    MM.Log(obj_str)
}

MM.Random = function () {
    return Math.random()
}

/**
 * 返回[begin, end)范围内的一个整数
 */
MM.RandomRange = function (begin, end)
{
    var range = end-begin
    MM.assert(range>=0,"Error: end="+end+"begin="+begin)
    if(range==0)
    {
        return begin
    }
    return Math.floor(begin+Math.random()*range)
}
/**
 * 返回[begin, end)范围内的count个不重复的整数
 */
MM.RandomArray = function (begin, end, count) {
    var random_arr  = []
    var unchoosed_num_map = {}
    for(var i=0; i<count; i++)
    {
        var random_num = MM.RandomRange(begin,end-i)
        var real_random_num = unchoosed_num_map[random_num] || random_num
        unchoosed_num_map[random_num] = unchoosed_num_map[end-i-1] || end-i-1
        random_arr.push(real_random_num)
    }
    return random_arr
}

MM.FrameByFrameTask = cc.Class.extend({
    /**
     * _step_cb(task_cur_count, task_total_num)
     * _finish_cb(task_cur_count, task_total_num)
     */
    _step_cb    : null,
    _finish_cb  : null,
    _task_num   : 0,
    _task_count : 0,
    _is_started : false,
    _frame_rate : 30,

    StartTask : function (task_arr,delay,step_cb,finish_cb)
    {
        cc.assert(task_arr,"Error: task_arr is none!")

        //Tips:确保Task只开启一次
        cc.assert(!this._is_started,"Error: task is started!")
        this._is_started = true

        this._task_num   = task_arr.length
        this._task_arr   = this._task_arr.concat(task_arr)
        this._step_cb    = step_cb
        this._finish_cb  = finish_cb

        delay = delay || 0
        cc.director.getScheduler().schedule(this._Update,this,0,cc.REPEAT_FOREVER,delay,false)
    },
    CancelTask : function () {
        cc.director.getScheduler().unschedule(this._Update,this)
    },
    _Update : function () {
        var begin = Date.now()
        while(this._task_arr.length>0)
        {
            this._task_count++
            this._task_arr[0](this._task_count,this._task_num)
            if(this._step_cb)
            {
                this._step_cb()
            }
            this._task_arr.shift()
            if( (Date.now()-begin) >= 1000/this._frame_rate )
            {
                break;
            }
        }
        if( this._task_count == this._task_num )
        {
            if(this._finish_cb)
            {
                this._finish_cb(this._task_count,this._task_num)
                cc.director.getScheduler().unschedule(this._Update,this)
            }
        }
    }
})
