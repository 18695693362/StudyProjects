/**
 * Created by guodong on 12/9/15.
 */

var StateBase = cc.Class.extend({
    _name           : "INVALID_state",

    ctor : function (name)
    {
        if(name)
        {
            this._name = name
        }
    },
    OnChangeToFailed : function (entity,from_state)
    {
        // do nothing
    },
    OnEnter : function (entity) {
        // do nothing
    },
    OnExit : function (entity) {
        // do nothing
    },
    Update : function (entity,delta_time) {
        // do nothing
    },
    GetName : function ()
    {
        return this._name
    }
})