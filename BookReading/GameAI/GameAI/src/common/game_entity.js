/**
 * Created by guodong on 12/9/15.
 */
var GameEntityMgr = cc.Class.extend({
    _entity_map : {},
    RegisterEntity : function (entity)
    {
        this._entity_map[entity.GetID()] = entity
    },
    GetEntity : function (id)
    {
        return this._entity_map[id]
    },
    UnregisterEntity : function (entity)
    {
        delete this._entity_map[entity.GetID()]
    }
})
MM.MakeSingleton(GameEntityMgr)

var GameEntityBase = cc.Class.extend({
    _id : -1,

    ctor : function (id)
    {
        this._SetID(id)
    },

    OnClear : function () {
        GameEntityMgr.GetInstance().UnregisterEntity(this)
    },

    GetID : function ()
    {
        return this._id
    },

    HandleMsg : function (telegram)
    {
        return false
    },

    _SetID : function (id)
    {
        if(id===undefined)
        {
            id = GameEntityBase._next_valid_id
        }
        cc.assert(id>=GameEntityBase._next_valid_id,"entity id error. id="+id)
        this._id = id
        GameEntityMgr.GetInstance().RegisterEntity(this)

        GameEntityBase._next_valid_id = id+1
    },

    Update : function (dt)
    {
        // do nothing
    },
})
GameEntityBase._next_valid_id = 1