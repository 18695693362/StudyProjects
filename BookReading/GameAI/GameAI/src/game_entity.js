/**
 * Created by guodong on 12/9/15.
 */


var GameEntityBase = cc.Class.extend({
    _id : -1,

    ctor : function (id)
    {
        this.SetID(id)
    },

    GetID : function ()
    {
        return this._id
    },

    SetID : function (id)
    {
        cc.assert(id>=GameEntityBase._next_valid_id,"entity id error. id="+id)
        this.SetID(id)

        GameEntityBase._next_valid_id = id+1
    },

    Update : function ()
    {
        // do nothing
    },
})
GameEntityBase._next_valid_id = 0