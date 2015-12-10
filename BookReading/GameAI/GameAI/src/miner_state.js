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
        else if(entity.IsThirst())
        {
            entity.ChangeState(QuenchThirst.GetInstance())
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
        if(entity._cur_location != EntityHelper.Location.kBank)
        {
            entity._cur_location = EntityHelper.Location.kBank
        }
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        entity.AddCarriedGoldToBank()

        if(entity.IsComfortable())
        {
            entity.ChangeState(GoHomeAndSleepTilRested.GetInstance())
        }
        else
        {
            entity.ChangeState(EnterMineAndDigForNugget.GetInstance())
        }
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
        if(!entity.IsFatigue())
        {
            entity.ChangeState(EnterMineAndDigForNugget.GetInstance())
        }
        else
        {
            entity.MinusFatigue()
            entity.ShowSleep()
        }
    }
})
MM.MakeSingleton(GoHomeAndSleepTilRested)

var QuenchThirst = StateBase.extend({
    ctor : function ()
    {
        this._super("QuenchThirst")
    },
    IsEnableChangeTo : function (entity)
    {
        return entity.IsEnoughForDrink()
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
        if(entity.IsThirst())
        {
            if(entity.IsEnoughForDrink())
            {
                entity.BuyAndDrinkAWhiskey()
                entity.ShowDrink()
                entity.ChangeState(EnterMineAndDigForNugget.GetInstance())
            }
            else
            {
                MM.StateHelper.PrintError(entity,this,"gold in bank is not enough!")
            }
        }
        else
        {
            MM.StateHelper.PrintError(entity,this,"entity is not thirst!")
        }
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
    PrintError : function (entity, state, error_str)
    {
        MM.Log("ERROR: "+entity.GetName()+" "+state.GetName()+" "+error_str)
    }
}



