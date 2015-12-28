
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
            //this.TestRandomRange(true)
            //this.TestQWE(true)
        }
    },

    TestMineState : function (test) {
        if(!test)return

        if(!this._test_mine_state_start)
        {
            if(!this._tmp_miner)
            {
                this._tmp_miner = new Miner(EntityHelper.EntityID.kMiner_Bob)
            }
            if(!this._tmp_miner_wife)
            {
                this._tmp_miner_wife = new MinersWife(EntityHelper.EntityID.kElsa)
            }

            cc.director.getScheduler().schedule(this._tmp_miner.Update,this._tmp_miner,1,999,0,false)
            cc.director.getScheduler().schedule(this._tmp_miner_wife.Update,this._tmp_miner_wife,1,999,0,false)
            this._test_mine_state_start = true
        }
        else
        {
            cc.director.getScheduler().unschedule(this._tmp_miner.Update,this._tmp_miner)
            cc.director.getScheduler().unschedule(this._tmp_miner_wife.Update,this._tmp_miner_wife)
            this._test_mine_state_start = false
        }
    },

    TestRandomRange : function (test) {
        if(!test)return

        for(var i=0; i<20; i++)
        {
            //MM.Log(MM.RandomRange(0,10))
            MM.PrintObj(MM.RandomArray(10,15,4))
        }
    },

    TestQWE : function (test) {
        if(!test)return
        qwe.dbgMode(true);
        var log = MM.Log

        var StateA = qwe.state('StateA');
        StateA.trace  = function(text) {
            var state = this.hsm.state;
            log(state.name +': ' + text + '\n');
        };
        StateA.moveTo = function(e, state){
            log('executing Action "moveTo" ' + state.name +'\n');
            this.hsm.tran(state);
        };

        var StateB = qwe.state('StateB', StateA);
        var StateC = qwe.state('StateC', StateB, false);
        var StateD = qwe.state('StateD', StateC);
        var StateE = qwe.state('StateE', StateC);
        var StateF = qwe.state('StateF', StateB);
        var StateG = qwe.state('StateG', StateF, false);
        var StateH = qwe.state('StateH', StateF);
        var StateX = qwe.state('StateX', StateB);
        var StateY = qwe.state('StateY', StateA);
        var StateZ = qwe.state('StateZ');
// A Whole new state machine
        StateZ.trace  = function(text) {
            var state = this.hsm.state;
            log(state.name +': ' + text + '\n')
        };
        StateZ.moveTo = function(e, state){ this.hsm.tran(state); };


        function MyObject(){
            // Put here any state you want
        }

        var obj = new MyObject();
        qwe.init(obj, StateZ, function(srcState, currState){
            this.hsm.trace('Previous state was: ' + srcState.name);
            this.hsm.trace('Current state is: ' + currState.name);
        });

///////////////////////////////////////////////////////////////////////////////////////
// From here just the scene setup
///////////////////////////////////////////////////////////////////////////////////////

        var all_states = []
        all_states.push(StateA)
        all_states.push(StateB)
        all_states.push(StateC)
        all_states.push(StateD)
        all_states.push(StateE)
        all_states.push(StateF)
        all_states.push(StateG)
        all_states.push(StateH)
        all_states.push(StateX)
        all_states.push(StateY)
        all_states.push(StateZ)

        obj.hsm.send('moveTo', StateD);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

