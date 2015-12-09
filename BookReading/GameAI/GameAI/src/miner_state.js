/**
 * Created by guodong on 12/9/15.
 */

var EnterMineAndDigForNugget = StateBase.extend({
    ctor : function ()
    {
        this._super("EnterMineAndDigForNugget")
    },
    OnEnter : function (entity)
    {
        if(entity._cur_location != EntityHelper.Location.kGoldmine)
        {
            entity._cur_location = EntityHelper.Location.kGoldmine
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        entity.AddCarriedGold(1)
        if(entity.IsNeedSaveGoldToBank())
        {
            entity.ChangeState(VisitBankAndDepositGold.GetInstance())
        }
    }
})
MM.MakeSingleton(EnterMineAndDigForNugget)

var VisitBankAndDepositGold = StateBase.extend({
    ctor : function ()
    {
        this._super("VisitBankAndDepositGold")
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

    }
})
MM.MakeSingleton(VisitBankAndDepositGold)

var GoHomeAndSleepTilRested = StateBase.extend({
    ctor : function ()
    {
        this._super("GoHomeAndSleepTilRested")
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

    }
})
MM.MakeSingleton(GoHomeAndSleepTilRested)

var QuenchThirst = StateBase.extend({
    ctor : function ()
    {
        this._super("QuenchThirst")
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

    }
})
MM.MakeSingleton(QuenchThirst)

MM.StateHelper =
{
    PrintStateEnterExit : function (entity, state, is_enter)
    {
        if(is_enter)
        {
            MM.Log("++++++")
            MM.Log("ENTER: "+entity.GetName()+" "+state.GetName())
        }
        else
        {
            MM.Log("EXIT:  "+entity.GetName()+" "+state.GetName())
            MM.Log("------")
        }
    },
}



