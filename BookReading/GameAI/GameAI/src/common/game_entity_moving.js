
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
    },

    MaxSpeed : function () {
        return this._max_speed
    }
})

var SteeringBehaviors = cc.Class.extend({
    ctor : function (vehicle)
    {
        this._vehicle = vehicle
    },
    Calculate : function ()
    {
        return 0;
    },
    Seek : function (target_pos)
    {
        var desired_velocity = MM.VecMultiNumber(
            MM.VecNormalize(MM.VecMinusVec(target_pos - this._vehicle._position)),
            this._vehicle.MaxSpeed()
        )

        return MM.VecMinusVec(desired_velocity,this._vehicle._velocity);
    },
    Flee : function (target_pos)
    {
        var desired_velocity = MM.VecMultiNumber(
            MM.VecNormalize(MM.VecMinusVec(this._vehicle._position - target_pos)),
            this._vehicle.MaxSpeed()
        )

        return MM.VecMinusVec(desired_velocity - this._vehicle._velocity);
    },
    Arrive : function (target_pos, deceleration)
    {
        var to_target = MM.VecMinusVec(target_pos, this._vehicle._position)
        var dist = MM.VecLen(to_target)

        if(dist > 0)
        {
            var deceleration_tweaker = 0.3
            var speed = dist / (deceleration*deceleration_tweaker)
            speed = Math.min(speed, this._vehicle.MaxSpeed())
            var desired_velocity = MM.VecMultiNumber(to_target,speed/dist)
            return MM.VecMinusVec(desired_velocity - this._vehicle._velocity);
        }
        return MM.VecZero()
    },
    Pursuit : function (evader)
    {
        var to_evader = evader._position - this._vehicle._position
        var relative_heading = MM.VecDotMultiVec(this._vehicle._heading, evader._heading)
    }
})
SteeringBehaviors.Deceleration =
{
    kSlow   : 1,
    kNormal : 2,
    kFast   : 3
}