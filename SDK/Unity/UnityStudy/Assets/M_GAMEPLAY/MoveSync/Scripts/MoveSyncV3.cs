using UnityEngine;

public class MoveSyncV3 : MoveSyncV2{
    public enum LerpType
    {
        kNone,
        kLinear,
        kCubeSpline,
        kWeightedAverage
    }
    public LerpType lerpType = LerpType.kLinear;

    enum SmoothState
    {
        kSmoothing,
        kUnSmoothing
    }
    SmoothState curSmoothState = SmoothState.kUnSmoothing;
    float smoothThreshold = 10.0f;
    float smoothTime = 0.0f;
    float smoothTimer = 0.0f;
    Vector2 smoothTargetPos = Vector2.zero;
    Vector2 smoothDir = Vector2.zero;
    float smoothLength = 0.0f;

    int slowdownFactor = 10;
    protected override void UpdateSMove()
    {
        if ( netSimulator.IsNetDataEmpty() && curMoveInfo.speed == 0 && curSmoothState == SmoothState.kUnSmoothing)
        {
            return;
        }

        switch (lerpType)
        {
            case LerpType.kLinear:
                LinearLerp();
                break;
            case LerpType.kCubeSpline:
                CubeSplineLerp();
                break;
            case LerpType.kWeightedAverage:
                WeightAverageLerp();
                break;
            default:
                curSmoothState = SmoothState.kUnSmoothing;
                NoneLerp();
                break;
        }
    }
    protected void NoneLerp()
    {
        base.UpdateSMove();
    }
    protected void LinearLerp()
    {
        Vector2 curPos = GetSGObjPos();
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();

            smoothTime = smoothTimer = Time.time - info.sendTime;
            smoothTargetPos = info.position + smoothTime * info.dir * info.speed;
            smoothLength = (smoothTargetPos - curPos).magnitude;
            smoothDir = (smoothTargetPos - curPos).normalized;

            if ( smoothLength > smoothThreshold )
            {
                curSmoothState = SmoothState.kSmoothing;
            }
            else
            {
                curSmoothState = SmoothState.kUnSmoothing;

                UpdateSGObjPosByPos(info.position);
                UpdateSGObjDir(info.dir);
            }
            svrPreMoveInfo = info;
        }
        if (curSmoothState == SmoothState.kSmoothing)
        {
            if (smoothTimer>0)
            {
                UpdateSGObjPosByDeltaPos(smoothDir * Time.deltaTime / smoothTime * smoothLength);
                UpdateSGObjDir(smoothDir);

                smoothTimer -= Time.deltaTime;
            }
            else
            {
                UpdateSGObjPosByPos(smoothTargetPos);
                UpdateSGObjDir(svrPreMoveInfo.dir);
                curSmoothState = SmoothState.kUnSmoothing;
            }
        }
        else {
            if (svrPreMoveInfo != null)
            {
                UpdateSGObjPosByDeltaPos(svrPreMoveInfo.dir*svrPreMoveInfo.speed);
                UpdateSGObjDir(svrPreMoveInfo.dir);
            }    
        }
    }

    float argA = 0.0f;
    float argB = 0.0f;
    float argC = 0.0f;
    float argD = 0.0f;
    float argE = 0.0f;
    float argF = 0.0f;
    float argG = 0.0f;
    float argH = 0.0f;
    Vector3 pos0 = Vector3.zero;
    Vector3 pos1 = Vector3.zero;
    Vector3 pos2 = Vector3.zero;
    Vector3 pos3 = Vector3.zero;
    protected void CubeSplineLerp()
    {
        Vector2 curPos = GetSGObjPos();
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();

            smoothTime = smoothTimer = Time.time - info.sendTime;
            smoothTargetPos = info.position + smoothTime * info.dir * info.speed;
            smoothLength = (smoothTargetPos - curPos).magnitude;
            //smoothDir = (smoothTargetPos - curPos).normalized;

            MoveInfo sCurMoveInfo = svrPreMoveInfo;
            if (sCurMoveInfo == null)
                sCurMoveInfo = info;
            
            pos0 = curPos;
            pos1 = curPos + sCurMoveInfo.dir * sCurMoveInfo.speed * 0.1f;
            pos2 = smoothTargetPos - info.dir * info.speed * 0.1f;
            pos3 = smoothTargetPos;
            argA = pos3.x - 3 * pos2.x + 3 * pos1.x - pos0.x;
            argE = pos3.y - 3 * pos2.y + 3 * pos1.y - pos0.y;
            argB = 3*pos2.x - 6*pos1.x + 3*pos0.x;
            argF = 3*pos2.y - 6*pos1.y + 3*pos0.y;
            argC = 3*pos1.x - 3*pos0.x;
            argG = 3*pos1.y - 3*pos0.y;
            argD = pos0.x;
            argH = pos0.y;
            if ( smoothLength > smoothThreshold )
            {
                curSmoothState = SmoothState.kSmoothing;
            }
            else
            {
                curSmoothState = SmoothState.kUnSmoothing;
            }
            svrPreMoveInfo = info;
        }
        if (curSmoothState == SmoothState.kSmoothing)
        {
            if (smoothTimer>0)
            {
                float deltaT = smoothTime / 5;
                float deltaTSquare = deltaT * deltaT;
                float deltaTCube = deltaTSquare * deltaT;
                Vector2 newPos = Vector3.zero;
                newPos.x = argA * deltaTCube + argB * deltaTSquare + argC * deltaT + argD;
                newPos.y = argE * deltaTCube + argF * deltaTSquare + argG * deltaT + argH;
                UpdateSGObjPosByPos(newPos);
                UpdateSGObjDir((newPos-curPos).normalized);

                smoothTimer -= deltaT;
            }
            else
            {
                UpdateSGObjPosByPos(smoothTargetPos);
                UpdateSGObjDir(svrPreMoveInfo.dir);

                curSmoothState = SmoothState.kUnSmoothing;
            }
        }
        else {
            if (svrPreMoveInfo != null)
            {
                UpdateSGObjPosByDeltaPos(svrPreMoveInfo.dir*svrPreMoveInfo.speed);
                UpdateSGObjDir(svrPreMoveInfo.dir);
            }    
        }
    }

    protected void WeightAverageLerp()
    {
        Vector2 curPos = GetSGObjPos();
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();

            smoothTime = smoothTimer = Time.time - info.sendTime;
            smoothTargetPos = info.position + smoothTime * info.dir * info.speed;
            //smoothLength = (smoothTargetPos - curPos).magnitude;
            //smoothDir = (smoothTargetPos - curPos).normalized;
            if ( smoothLength > smoothThreshold )
            {
                curSmoothState = SmoothState.kSmoothing;
            }
            else
            {
                curSmoothState = SmoothState.kUnSmoothing;

                UpdateSGObjPosByPos(info.position);
                UpdateSGObjDir(info.dir);
            }
            svrPreMoveInfo = info;
        }
        if (curSmoothState == SmoothState.kSmoothing)
        {
            // 加权平均插值 不需要记录deltaTime 通过离目标距离判断是否结束平滑 平滑时间通过slowdownFactor来调节
            if( (smoothTargetPos - curPos).magnitude > 2 )
            {
                Vector2 newPos = curPos + (smoothTargetPos - curPos) / slowdownFactor;
                Vector2 newDir = newPos - curPos;
                UpdateSGObjPosByPos(newPos);
                UpdateSGObjDir(newDir);
            }
            else
            {
                UpdateSGObjPosByPos(smoothTargetPos);
                UpdateSGObjDir(svrPreMoveInfo.dir);
                curSmoothState = SmoothState.kUnSmoothing;
            }
        }
        else {
            if (svrPreMoveInfo != null)
            {
                UpdateSGObjPosByDeltaPos(svrPreMoveInfo.dir*svrPreMoveInfo.speed);
                UpdateSGObjDir(svrPreMoveInfo.dir);
            }    
        }
    }
}
