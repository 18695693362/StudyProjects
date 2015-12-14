/**
 * Created by guodong on 12/9/15.
 */

var Miner = GameEntityBase.extend({
    _state_machine  : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    _carried_gold   : 0,
    _bank_gold      : 0,
    _thirst_value   : 0,
    _fatigue_value  : 0,

    ctor : function (id) {
        this._super(id)
        this._state_machine = new StateMachine(this)
        this._state_machine._cur_state = GoHomeAndSleepTilRested.GetInstance()
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

    Update : function (dt)
    {
        this._thirst_value += 1

        if(this._state_machine)
        {
            this._state_machine.Update(dt)
        }
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
    }
})
Miner.kFatigueLevel     = 5
Miner.kThirstLevel      = 10
Miner.kMaxCarriedGold   = 5
Miner.kComfortLevel     = 20
Miner.kDrinkOnceCost    = 2