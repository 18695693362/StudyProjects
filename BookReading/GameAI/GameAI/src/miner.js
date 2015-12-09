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

    AddCarriedGold : function (gold) {
        this._carried_gold += gold
    },
    AddCarriedGoldToBank : function () {
        this._bank_gold += this._carried_gold

        this._carried_gold = 0
    },
    AddThirst : function () {
        this._thirst_value += 1
    },
    MinusThirst : function () {
        this._thirst_value -= 1
    },
    AddFatigue : function () {
        this._fatigue_value += 1
    },
    MinusFatigue : function () {
        this._fatigue_value -= 1
    }
})