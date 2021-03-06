/**
 * Created by guodong on 12/9/15.
 */

var Miner = GameEntityBase.extend({
    _state_machine  : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    _carried_gold   : 0,
    _bank_gold      : 0,
    _thirst_value   : 0,
    _hungry_value   : 0,
    _fatigue_value  : 0,

    ctor : function (id) {
        this._super(id)
        this._state_machine = new StateMachine(this)
        this._state_machine.ChangeToState(Home_SleepTilRested.GetInstance())
    },

    GetName : function ()
    {
        return EntityHelper.GetEntityName(this._id)
    },

    HandleMsg : function (telegram)
    {
        this._state_machine.HandleMsg(telegram)
    },

    IsNeedSaveGoldToBank : function ()
    {
        return this._carried_gold>=Miner.kMaxCarriedGold
    },
    AddCarriedGold : function (gold) {
        this._carried_gold += gold
    },
    AddCarriedGoldToBank : function () {
        this._bank_gold += this._carried_gold

        this._carried_gold = 0
    },
    ChangeGoldInBank : function (gold_value)
    {
        var delta = this._bank_gold + gold_value
        if(delta<0)
        {
            return false
        }
        this._bank_gold += gold_value

        return true
    },
    IsComfortable : function () {
        return this._bank_gold>=Miner.kComfortLevel
    },
    IsEnoughForDrink : function () {
        return this._bank_gold>=Miner.kDrinkOnceCost
    },
    IsSaveCarriedGoldEnoughForDrink : function () {
        return (this._bank_gold+this._carried_gold)>=Miner.kDrinkOnceCost
    },

    IsThirst : function () {
        return this._thirst_value>=Miner.kThirstLevel
    },
    AddThirst : function () {
        this._thirst_value += 1
    },
    IsHungry : function () {
        return this._hungry_value>=Miner.kHungryLevel
    },
    AddHungry : function () {
        this._hungry_value += 1
    },

    IsFatigue : function () {
        return this._fatigue_value>=Miner.kFatigueLevel
    },
    AddFatigue : function () {
        this._fatigue_value += 1
    },
    MinusFatigue : function () {
        this._fatigue_value -= 1
    },
    BuyAndDrinkAWhiskey : function ()
    {
        this._thirst_value  =  0
        this._bank_gold     -= Miner.kDrinkOnceCost
    },

    IsInLocation : function (des_location)
    {
        cc.assert(des_location,"des_location is Invalid. des_location="+des_location)
        return this._cur_location==des_location
    },

    Update : function (dt)
    {
        this.AddThirst()
        this.AddHungry()

        this._state_machine.Update(dt)
    },

    // display
    ShowSleep : function ()
    {
        MM.Log(this.GetName()+": Zzzzzz")
    },
    ShowDrink : function ()
    {
        MM.Log(this.GetName()+": I Love Whisky!")
    },
    ShowDigGold : function (count) {
        MM.Log(this.GetName()+": I got "+count+" gold! carried = "+this._carried_gold)
    },
    ShowTired : function () {
        MM.Log(this.GetName()+": I feel tired! fatigue = "+this._fatigue_value)
    },
    ShowSaveGoldToBank : function (carried) {
        MM.Log(this.GetName()+": I save "+carried+" gold to bank! total = "+this._bank_gold)
    },
    ShowWaitFood : function () {
        MM.Log(this.GetName()+": Oh! I'm hungry ....")
    },
    ShowEatStew : function () {
        MM.Log(this.GetName()+": Oh! delicious stew")
        MM.Log(this.GetName()+": I'm full!")
    }
})
Miner.kFatigueLevel     = 5
Miner.kThirstLevel      = 10
Miner.kHungryLevel      = 10
Miner.kMaxCarriedGold   = 5
Miner.kComfortLevel     = 20
Miner.kDrinkOnceCost    = 2

Miner.StateHelper = {
    StateKey : {
        kPreState : "PreState",
    },
    SavePreState : function (entity)
    {
        entity._state_machine._state_data[this.StateKey.kPreState] = entity._state_machine._cur_state
    },
    GetPreState : function (entity)
    {
        return entity._state_machine._state_data[this.StateKey.kPreState]
    },
    IsPreStateEmpty : function (entity)
    {
        return entity._state_machine._state_data[this.StateKey.kPreState]==null
    },
    RevertToPreState : function (entity)
    {
        entity._state_machine.ChangeToState(this.GetPreState(entity))
        entity._state_machine._state_data[this.StateKey.kPreState] = null
    }
}