/**
 * Created by guodong on 12/9/15.
 */

var StateBase = cc.Class.extend({
    _name           : "INVALID_state",
    _sub_states     : [],
    _parent_state   : null,
    _cur_sub_state  : null,

    ctor : function (name,sub_states)
    {
        if(name)
        {
            this._name = name
        }
        if(sub_states)
        {
            for(var i=0; i<sub_states.length; i++)
            {
                this.AddSubState(sub_states[i])
            }
        }
    },
    AddSubState : function (sub_state)
    {
        if(sub_state)
        {
            sub_state._parent_state = this
            this._sub_states.push(sub_state)
            return true
        }
        return false
    },
    RemoveSubState : function (sub_state)
    {
        if(sub_state)
        {
            for(var i=0; i<this._sub_states.length; i++)
            {
                if(sub_state==this._sub_states[i])
                {
                    sub_state._parent_state = null
                    this._sub_states.splice(i,1)
                    if(this._cur_sub_state==sub_state)
                    {
                        this._cur_sub_state = null
                    }
                    return true
                }
            }
        }
        return false
    },
    IsEnableEnter : function (entity)
    {
        return true;
    },
    OnBeforeEnter : function (entity)
    {
        // do nothing
    },
    OnEnter : function (entity) {
        for(var i=0; i<this._sub_states.length; i++)
        {
            if(this._sub_states[i].IsEnableEnter(entity))
            {
                this._cur_sub_state = this._sub_states[i]
                this._cur_sub_state.OnBeforeEnter(entity)
                this._cur_sub_state.OnEnter(entity)
                return
            }
        }
    },
    OnExit : function (entity) {
        if(this._cur_sub_state)
        {
            this._cur_sub_state.OnExit(entity)
            this._cur_sub_state.OnAfterExit(entity)
            this._cur_sub_state = null
        }
    },
    OnAfterExit : function (entity)
    {
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
        if(this._cur_sub_state)
        {
            this._cur_sub_state.Update(entity,delta_time)
        }
    },
    GetName : function ()
    {
        return this._name
    }
})