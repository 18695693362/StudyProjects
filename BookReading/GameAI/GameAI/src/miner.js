/**
 * Created by guodong on 12/9/15.
 */

var Miner = GameEntityBase.extend({
    _cur_state      : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    _carried_gold   : 0,
    _bank_gold      : 0,
    _thirst_value   : 0,
    _fatigue_value  : 0,

    ctor : function (id) {
        this._super(id)
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

    ChangeState : function (new_state)
    {
        var old_state = this._cur_state
        cc.assert(new_state&&this._cur_state!=new_state,new_state?new_state.GetName():"NONE")
        if(old_state)
        {
            old_state.OnExit()
        }

        this._cur_state = new_state

        new_state.OnEnter()
    },

    Update : function ()
    {
        this._super()
        this._thirst_value += 1

        if(this._cur_state)
        {
            this._cur_state.Update()
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
    }
})
Miner.kFatigueLevel     = 5
Miner.kThirstLevel      = 5
Miner.kMaxCarriedGold   = 5
Miner.kComfortLevel     = 20
Miner.kDrinkOnceCost    = 2