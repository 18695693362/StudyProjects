/**
 * Created by guodong on 12/9/15.
 */

var StateBase = cc.Class.extend({
    _name : "INVALID",
    ctor : function (name)
    {
        if(name)
        {
            this._name = name
        }
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