/**
 * Created by guodong on 12/14/15.
 */

var StateMachine = cc.Class.extend({
    _owner          : null,
    _cur_state      : null,
    _pre_state      : null,
    _global_state   : null,
    _state_data     : {},

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
    _GetCommonParent : function (sub_state_one,sub_state_two)
    {
        MM.assert(sub_state_one,"Error: sub_state_one is null")
        MM.assert(sub_state_two,"Error: sub_state_two is null")
        MM.assert(sub_state_one!=sub_state_two,"Error: same state")

        var _parent_map = {}
        _parent_map[sub_state_one.GetName()] = {state:sub_state_one,count:1}
        _parent_map[sub_state_two.GetName()] = {state:sub_state_two,count:1}
        while(sub_state_one._parent_state)
        {
            sub_state_one = sub_state_one._parent_state
            if(_parent_map[sub_state_one.GetName()])
            {
                _parent_map[sub_state_one.GetName()].count += 1
            }
            else
            {
                _parent_map[sub_state_one.GetName()] = {}
                _parent_map[sub_state_one.GetName()].state  = sub_state_one
                _parent_map[sub_state_one.GetName()].count  = 1
            }
        }
        while(sub_state_two._parent_state)
        {
            sub_state_two = sub_state_two._parent_state
            if(_parent_map[sub_state_two.GetName()])
            {
                _parent_map[sub_state_two.GetName()].count += 1
            }
            else
            {
                _parent_map[sub_state_two.GetName()] = {}
                _parent_map[sub_state_two.GetName()].state  = sub_state_two
                _parent_map[sub_state_two.GetName()].count  = 1
            }
        }
        for(var key in _parent_map)
        {
            if(_parent_map[key].count==2)
            {
                return _parent_map[key].state
            }
        }
        MM.assert(false,"Error: find common parent failed!")
    },
    ChangeToState : function (new_state,is_global)
    {
        var old_state = is_global ? this._global_state : this._cur_state
        cc.assert(new_state&&old_state!=new_state, "state name is " + new_state?new_state.GetName():"NONE")
        var old_exit_states  = []
        var new_enter_states = []
        var tmp_state        = null
        var common_parent    = null
        if(old_state)
        {
            common_parent = this._GetCommonParent(old_state,new_state)
            tmp_state = old_state
            while(tmp_state!=common_parent)
            {
                old_exit_states.push(tmp_state)
                tmp_state = tmp_state._parent_state
            }
        }
        else
        {
            common_parent = RootState
        }
        tmp_state = new_state
        while(tmp_state!=common_parent)
        {
            new_enter_states.splice(0,0,tmp_state)
            tmp_state = tmp_state._parent_state
        }

        // do exit
        for(var i=0; i<old_exit_states.length; i++)
        {
            old_exit_states[i].OnExit(this._owner)
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
        // do enter
        for(var i=0; i<new_enter_states.length; i++)
        {
            new_enter_states[i].OnEnter(this._owner)
        }
    },
    RevertToPreState : function () {
        var pre_state = this._pre_state
        cc.assert(pre_state, "pre state is null!")
        this._pre_state = null
        this.ChangeToState(pre_state)
    },
    IsInState : function (des_state) {
        cc.assert(des_state, "des_state is none!")
        cc.assert(this._cur_state, "cur_state is none!")

        var check_state = this._cur_state
        while(check_state)
        {
            if(check_state==des_state)
            {
                return true
            }
            check_state = check_state._parent_state
        }
        return  false
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