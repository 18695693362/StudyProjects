
var MovingEntity = GameEntityBase.extend({
    ctor : function (id)
    {
        this._super(id)
        this._position      = cc.p(0,0)
        this._velocity      = cc.p(0,0)
        this._heading       = cc.p(0,0)
        this._side          = cc.p(0,0)
        this._mass          = 0
        this._max_speed     = 0
        this._max_force     = 0
        this._max_turnrate  = 0
    }
})

var Vehicle = MovingEntity.extend({
    ctor : function (id)
    {
        this._super(id)
        this._world     = null
        this._steering  = null
    },
    
    Update : function (dt)
    {
        var steering_force  = this._steering.Calculate()
        var acceleration    = MM.VecMultiNumber(steering_force,this._mass)
        this._velocity = MM.VecPlusVec(this._velocity,MM.VecMultiNumber(acceleration,dt))

        MM.VecTruncate(this._velocity,this._max_speed)

        this._position = MM.VecPlusVec(this._position,MM.VecMultiNumber(this._velocity,dt))
        if(MM.VecLenSquare(this._velocity) > 0.00000001)
        {
            this._heading = MM.VecNormalize(this._velocity)
            this._side    = MM.VectPerp(this._heading)
        }
    }
})

var SteeringForce = cc.Class.extend({
    Calculate : function ()
    {
        return 0;
    }
})