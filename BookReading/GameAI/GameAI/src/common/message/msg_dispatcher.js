/**
 * Created by guodong on 12/23/15.
 */

var MsgDispatcher = cc.Class.extend({
    _msg_arr : [],

    ctor : function (clock)
    {
        this._clock = clock
        this._clock.RegisterUpdate(this.DispatchDelayedMsg)
    },
    OnClear : function () {
        this._clock.UnregisterUpdate(this.DispatchDelayedMsg)
    },

    _Discharge : function (receiver, telegram) {
        if(!receiver.HandleMsg(telegram))
        {
            MM.Log("Warnning: msg not handle!")
        }
    },

    DispatchMsg : function (delay,sender,receiver,msg,extra_info)
    {
        var pReceiver = GameEntityMgr.GetInstance().GetEntity(receiver)
        if(!pReceiver)
        {
            return
        }
        var telegram = new Telegram(sender,receiver,msg,extra_info,0)
        if(delay>0)
        {
            telegram.dispatch_time = this._clock.GetCurTime()+delay
            this._msg_arr.push(telegram)
        }
        else
        {
            this._Discharge(receiver,telegram)
        }
    },

    DispatchDelayedMsg : function ()
    {
        this._msg_arr.sort(function (one, two) {
            return one.dispatch_time-two.dispatch_time
        })

        var cur_time = this._clock.GetCurTime()
        while(this._msg_arr.length>0 && this._msg_arr[0].dispatch_time<cur_time && this._msg_arr[0].dispatch_time>0)
        {
            var pReceiver = GameEntityMgr.GetInstance().GetEntity(this._msg_arr[0].receiver)
            this._Discharge(pReceiver,this._msg_arr[0])
            this._msg_arr.shift()
        }
    }
})

var Telegram = cc.Class.extend({
    ctor : function (sender,receiver,msg,extra_info,dispatch_time)
    {
        this.sender         = sender
        this.receiver       = receiver
        this.msg            = msg
        this.extra_info     = extra_info
        this.dispatch_time  = dispatch_time
    }
})