/**
 * Created by guodong on 12/15/15.
 */

var WifesGlobalState = StateBase.extend({
    ctor : function () {
        this._super("WifesGlobalState")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kShack)
        {
            entity._cur_location = EntityHelper.Location.kShack
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        if(entity.IsNeedToBathroom())
        {
            entity._state_machine.ChangeToState(VisitBathroom.GetInstance())
        }
    }
})
MM.MakeSingleton(WifesGlobalState)

var VisitBathroom = StateBase.extend({
    ctor : function () {
        this._super("VisitBathroom")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kShack)
        {
            entity._cur_location = EntityHelper.Location.kShack
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        entity.ShowGoToBathroom()
        entity._state_machine.RevertToPreState()
    }
})
MM.MakeSingleton(VisitBathroom)

var DoHouseWork = StateBase.extend({
    ctor : function () {
        this._super("DoHouseWork")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kShack)
        {
            entity._cur_location = EntityHelper.Location.kShack
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        entity.ShowDoHouseWork(MinersWife.HouseWorkType.GetNeedOptHouseWorkType())
    }
})
MM.MakeSingleton(DoHouseWork)