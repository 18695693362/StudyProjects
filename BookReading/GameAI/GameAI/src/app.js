
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function ()
    {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        var mainscene = ccs.load(res.MainScene_json);
        this.addChild(mainscene.node);

        this._btn_test = ccui.helper.seekWidgetByName(mainscene.node,"Button_1")
        this._btn_test.addTouchEventListener(this.OnPressedTest,this)

        cc.log("test start ----- ")

        return true;
    },

    OnPressedTest : function (sender,type)
    {
        if(type == ccui.Widget.TOUCH_ENDED)
        {
            cc.log("pressed test")
            this.TestMineState(true)
        }
    },

    TestMineState : function (test) {
        if(test)
        {
            if(!this._test_mine_state_start)
            {
                if(!this._tmp_miner)
                {
                    this._tmp_miner = new Miner(EntityHelper.EntityID.kMiner_Bob)
                    this._tmp_miner.ChangeState(GoHomeAndSleepTilRested.GetInstance())
                }

                cc.director.getScheduler().schedule(this._tmp_miner.Update,this._tmp_miner,1,999,0,false)
                this._test_mine_state_start = true
            }
            else
            {
                cc.director.getScheduler().unschedule(this._tmp_miner.Update,this._tmp_miner)
                this._test_mine_state_start = false
            }
        }
    },
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

