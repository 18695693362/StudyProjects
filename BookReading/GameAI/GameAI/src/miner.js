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

    ctor : function () {

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
        this._bank_gold     -= 2
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

        this._cur_state.Update()
    },
})
Miner.kFatigueLevel     = 5
Miner.kThirstLevel      = 5
Miner.kMaxCarriedGold   = 5