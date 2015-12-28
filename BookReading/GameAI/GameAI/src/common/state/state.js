/**
 * Created by guodong on 12/9/15.
 */

var StateBase = cc.Class.extend({
    _name           : "INVALID_state",
    _sub_states     : [],
    _parent_state   : null,
    _cur_sub_state  : null,

    ctor : function (name,parent_state)
    {
        if(name)
        {
            this._name = name
        }
        this._parent_state = parent_state || RootState
        this._sub_states.push(this)
    },
    IsEnableEnter : function (entity)
    {
        return true;
    },
    OnEnter : function (entity) {
        // do nothing
    },
    OnExit : function (entity) {
        // do nothing
    },
    OnMsg : function (entity, telegram)
    {
        if(this._cur_sub_state && this._cur_sub_state.OnMsg(entity,telegram))
        {
            return true
        }
        return false
    },
    Update : function (entity,delta_time)
    {
        // do nothing
    },
    GetName : function ()
    {
        return this._name
    }
})
var RootState = new StateBase("RootState",null)
RootState.OnEnter = function (entity) {
    MM.assert(false,"Error: invoke RootState OnEnter!")
}
RootState.OnExit = function (entity) {
    MM.assert(false,"Error: invoke RootState OnExit!")
}