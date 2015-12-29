/**
 * Created by guodong on 12/15/15.
 */

var WifesGlobalState = StateBase.extend({
    ctor : function () {
        this._super("WifesGlobalState")
    },
    OnEnter : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        if(!entity._state_machine.IsInState(VisitBathroom.GetInstance()) && entity.IsNeedToBathroom())
        {
            entity._state_machine.ChangeToState(VisitBathroom.GetInstance())
        }
    },
    OnMsg : function (entity, telegram)
    {
        if(telegram.msg == EntityHelper.MsgType.kMsg_HiHoneyImHome)
        {
            entity.ShowWelcomeBack()
        }
        else if(telegram.msg == EntityHelper.MsgType.kMsg_HiHoneyImHungry)
        {
            entity.ShowGotoCook()
            entity._state_machine.ChangeToState(CookStew.GetInstance())
            return true
        }
        else if(telegram.msg==EntityHelper.MsgType.kMsg_StewReady)
        {
            if(entity.IsHusbandInHome())
            {
                MsgDispatcher.GetInstance().DispatchMsg(0,
                    entity.GetID(),
                    EntityHelper.EntityID.kMiner_Bob,
                    EntityHelper.MsgType.kMsg_StewReady
                )
            }
            entity.SetCooking(false)
            return true
        }
        else if(telegram.msg==EntityHelper.MsgType.kMsg_HiHoneyImAway)
        {
            entity.SetCooking(false)
            return true
        }
        return false
    }
})
MM.MakeSingleton(WifesGlobalState)

var VisitBathroom = StateBase.extend({
    ctor : function () {
        this._super("VisitBathroom")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kBathroom)
        {
            entity._cur_location = EntityHelper.Location.kBathroom
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

var CookStew = StateBase.extend({
    ctor : function () {
        this._super("CookStew")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kShack)
        {
            entity._cur_location = EntityHelper.Location.kShack
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)

        if(!entity._is_cooking)
        {
            entity.SetCooking(true)
            MsgDispatcher.GetInstance().DispatchMsg(1.5,
                entity.GetID(),
                entity.GetID(),
                EntityHelper.MsgType.kMsg_StewReady
            )
        }
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        if(entity._is_cooking)
        {
            entity.ShowCooking()
        }
        else
        {
            entity._state_machine.ChangeToState(DoHouseWork.GetInstance())
        }
    }
})
MM.MakeSingleton(CookStew)