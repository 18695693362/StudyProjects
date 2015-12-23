/**
 * Created by guodong on 12/15/15.
 */

var MinersWife = GameEntityBase.extend({
    _state_machine  : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    ctor : function (id) {
        this._super(id)
        this._state_machine = new StateMachine(this)
        this._state_machine.ChangeToState(WifesGlobalState.GetInstance(),true)
        this._state_machine.ChangeToState(DoHouseWork.GetInstance())
    },

    GetName : function ()
    {
        return EntityHelper.GetEntityName(this._id)
    },

    IsNeedToBathroom : function () {
        return MM.Random()<MinersWife.kGoToBathroomCondition
    },

    Update : function (dt) {
        this._state_machine.Update(dt)
    },

    // display
    ShowGoToBathroom : function () {
        MM.Log(this.GetName()+": I need go to bathroom!")
    },
    ShowDoHouseWork : function (house_work_type) {
        if(house_work_type==MinersWife.HouseWorkType.kMopFloor)
        {
            this.ShowMopFloor()
        }
        else if(house_work_type==MinersWife.HouseWorkType.kWashDishes)
        {
            this.ShowWashDishes()
        }
        else if(house_work_type==MinersWife.HouseWorkType.kMakeBed)
        {
            this.ShowMakeBed()
        }
    },
    ShowMopFloor : function () {
        MM.Log(this.GetName()+": Moppin floor!")
    },
    ShowWashDishes : function () {
        MM.Log(this.GetName()+": Washin dishes!")
    },
    ShowMakeBed : function () {
        MM.Log(this.GetName()+": Makin bed!")
    }
})
MinersWife.kGoToBathroomCondition = 0.1
MinersWife.HouseWorkType = {
    kMopFloor   : 1,
    kWashDishes : 2,
    kMakeBed    : 3,

    GetNeedOptHouseWorkType : function () {
        return MM.RandomRange(1,4)
    }
}