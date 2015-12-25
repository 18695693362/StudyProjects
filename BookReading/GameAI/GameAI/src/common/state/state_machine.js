/**
 * Created by guodong on 12/14/15.
 */

var StateMachine = cc.Class.extend({
    _owner          : null,
    _cur_state      : null,
    _pre_state      : null,
    _global_state   : null,

    ctor : function (owner) {
        this._owner = owner
    },
    Update : function (dt) {
        if(this._global_state)
        {
            this._global_state.Update(this._owner,dt)
        }
        if(this._cur_state)
        {
            this._cur_state.Update(this._owner,dt)
        }
    },
    ChangeToState : function (new_state,is_global)
    {
        var old_state = is_global ? this._global_state : this._cur_state
        cc.assert(new_state&&old_state!=new_state, "state name is " + new_state?new_state.GetName():"NONE")
        if(old_state)
        {
            old_state.OnExit(this._owner)
            old_state.OnAfterExit(this._owner)
        }

        if(is_global)
        {
            this._global_state = new_state
        }
        else
        {
            this._pre_state = old_state
            this._cur_state = new_state
        }

        new_state.OnBeforeEnter(this._owner)
        new_state.OnEnter(this._owner)
    },
    RevertToPreState : function () {
        var pre_state = this._pre_state
        cc.assert(pre_state, "pre state is null!")
        this._pre_state = null
        this.ChangeToState(pre_state)
    },
    IsInState : function (state_class) {
        cc.assert(state_class, "state_class is none!")
        cc.assert(this._cur_state, "cur_state is none!")

        return state_class.GetInstance() == this._cur_state
    },
    HandleMsg : function (telegram) {
        if(this._cur_state && this._cur_state.OnMsg(this._owner,telegram))
        {
            return true
        }
        if(this._global_state && this._global_state.OnMsg(this._owner,telegram))
        {
            return true
        }
        return false
    }
})