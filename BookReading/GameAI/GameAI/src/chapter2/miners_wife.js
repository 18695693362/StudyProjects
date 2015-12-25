/**
 * Created by guodong on 12/15/15.
 */

var MinersWife = GameEntityBase.extend({
    _state_machine  : null,
    _cur_location   : EntityHelper.Location.kInvalid,
    _is_cooking     : false,

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

    HandleMsg : function (telegram)
    {
        this._state_machine.HandleMsg(telegram)
    },

    IsNeedToBathroom : function () {
        return MM.Random()<MinersWife.kGoToBathroomCondition
    },

    SetCooking : function (is_cooking) {
        this._is_cooking = is_cooking
    },

    IsHusbandInHome : function () {
        var husband = GameEntityMgr.GetInstance().GetEntity(EntityHelper.EntityID.kMiner_Bob)
        if(husband)
        {
            return husband.IsInLocation(EntityHelper.Location.kShack)
        }
        return false
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
    },
    ShowWelcomeBack : function () {
        MM.Log(this.GetName()+": Hi honey welcome back!")
    },
    ShowGotoCook : function () {
        MM.Log(this.GetName()+": I'm going to cook!")
    },
    ShowCooking : function () {
        MM.Log(this.GetName()+": Cooking ...")
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