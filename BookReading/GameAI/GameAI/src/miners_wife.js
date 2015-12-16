/**
 * Created by guodong on 12/15/15.
 */

var MinersWife = GameEntityBase.extend({
    _state_machine  : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    ctor : function (id) {
        this._super(id)
        this._state_machine = new StateMachine(this)
    },

    Update : function (dt) {
        this._state_machine.Update(dt)
    },
})