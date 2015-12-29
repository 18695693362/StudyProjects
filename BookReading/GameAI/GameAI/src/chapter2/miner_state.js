/**
 * Created by guodong on 12/9/15.
 */
var MinerGlobalState = StateBase.extend({
    ctor : function () {
        this._super("MinerGlobalState")
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
                entity._state_machine.ChangeToState(QuenchThirst.GetInstance())
            }
            else if(entity.IsSaveCarriedGoldEnoughForDrink())
            {
                entity._state_machine.ChangeToState(VisitBankAndDepositGold.GetInstance())
            }
        }
        else if(entity.IsHungry() || entity.IsFatigue())
        {
            if(entity._state_machine.IsInState(GoHome.GetInstance()))
            {
                // do nothing
            }
            else
            {
                Miner.StateHelper.SavePreState(entity)
                entity._state_machine.ChangeToState(GoHome.GetInstance())
            }
        }
    }
})
MM.MakeSingleton(MinerGlobalState)

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
        entity.ShowDigGold(1)
        entity.AddFatigue()
        entity.ShowTired()

        if(entity.IsFatigue())
        {
            entity._state_machine.ChangeToState(GoHome.GetInstance())
        }
        else if(entity.IsNeedSaveGoldToBank())
        {
            entity._state_machine.ChangeToState(VisitBankAndDepositGold.GetInstance())
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
        var carried_gold = entity._carried_gold
        entity.AddCarriedGoldToBank()
        entity.ShowSaveGoldToBank(carried_gold)

        if(entity.IsThirst())
        {
            entity._state_machine.ChangeToState(QuenchThirst.GetInstance())
        }
        else if(entity.IsComfortable())
        {
            entity._state_machine.ChangeToState(GoHome.GetInstance())
        }
        else
        {
            entity._state_machine.ChangeToState(EnterMineAndDigForNugget.GetInstance())
        }
    }
})
MM.MakeSingleton(VisitBankAndDepositGold)

var GoHome = StateBase.extend({
    ctor : function () {
        this._super("GoHome")
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
    Update : function (entity, delta_time)
    {
        if(entity.IsHungry())
        {
            entity._state_machine.ChangeToState(Home_WaitFood.GetInstance())
        }
        else if(entity.IsFatigue())
        {
            entity._state_machine.ChangeToState(Home_SleepTilRested.GetInstance())
        }
    }
})
MM.MakeSingleton(GoHome)

var Home_SleepTilRested = StateBase.extend({
    ctor : function ()
    {
        this._super("Home_SleepTilRested",GoHome.GetInstance())
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
        MsgDispatcher.GetInstance().DispatchMsg(0,
            EntityHelper.EntityID.kMiner_Bob,
            EntityHelper.EntityID.kElsa,
            EntityHelper.MsgType.kMsg_HiHoneyImAway
        )
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    Update : function (entity,delta_time)
    {
        if(!entity.IsFatigue())
        {
            entity._state_machine.ChangeToState(EnterMineAndDigForNugget.GetInstance())
        }
        else
        {
            entity.MinusFatigue()
            entity.ShowSleep()
        }
    }
})
MM.MakeSingleton(Home_SleepTilRested)

var Home_WaitFood = StateBase.extend({
    ctor : function () {
        this._super("Home_WaitFood",GoHome.GetInstance())
    },
    OnEnter : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this,true)
        MsgDispatcher.GetInstance().DispatchMsg(0,
            EntityHelper.EntityID.kMiner_Bob,
            EntityHelper.EntityID.kElsa,
            EntityHelper.MsgType.kMsg_HiHoneyImHungry
        )
    },
    OnExit : function (entity)
    {
        MM.StateHelper.PrintStateEnterExit(entity,this)
    },
    OnMsg : function (entity, telegram)
    {
        switch (telegram.msg)
        {
            case EntityHelper.MsgType.kMsg_StewReady:
                entity._state_machine.ChangeToState(Home_EatStew.GetInstance())
                return true
        }
        return false
    },
    Update : function (entity,delta_time)
    {
        entity.ShowWaitFood()
    }
})
MM.MakeSingleton(Home_WaitFood)

var Home_EatStew = StateBase.extend({
    ctor : function () {
        this._super("Home_EatStew",GoHome.GetInstance())
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
        entity.ShowEatStew()
        entity._hungry_value = 0
        if(Miner.StateHelper.IsPreStateEmpty(entity))
        {
            entity._state_machine.ChangeToState(EnterMineAndDigForNugget.GetInstance())
        }
        else
        {
            Miner.StateHelper.RevertToPreState(entity)
        }
    }
})
MM.MakeSingleton(Home_EatStew)

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
        if(entity.IsThirst())
        {
            if(entity.IsEnoughForDrink())
            {
                entity.BuyAndDrinkAWhiskey()
                entity.ShowDrink()
                entity._state_machine.ChangeToState(EnterMineAndDigForNugget.GetInstance())
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



