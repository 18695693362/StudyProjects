using UnityEngine;

// 每帧都进行同步的 帧同步
public class MoveSyncV4 : BaseMoveSync{
    // 在帧同步算法中 客户端不直接使用本地的输入数据，而是统一采用服务器发送的数据
    protected override void UpdateCMove()
    {
        if (!isStopClient)
        {
            SendMoveInfo(curMoveInfo);
        }
    }
    protected override void SendMoveInfo(MoveInfo moveInfo)
    {
        bool isNeedSync = false;
        if (!lastMoveInfo.dir.Equals(moveInfo.dir) || lastMoveInfo.speed!=moveInfo.speed)
        {
            isNeedSync = true;
        }

        if(isNeedSync)
        {
            lastMoveInfo = moveInfo.Clone() as MoveInfo;
            netSimulator.Send(moveInfo.Clone() as MoveInfo);
            AddNetflowCounter();
        }
    }
    protected override void UpdateSMove()
    {
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();
            svrPreMoveInfo = info;
        }
        else
        {
            if (svrPreMoveInfo != null)
            {
                info = svrPreMoveInfo;
            }    
        }

        if (info != null)
        {
            Vector2 deltaPos = info.dir * info.speed;
            UpdateGObjPos(deltaPos, clientGObj.transform);
            UpdateGObjDir(info.dir, clientGObj.transform);
            UpdateSGObjPosByDeltaPos(deltaPos);
            UpdateSGObjDir(info.dir);
        }
    }
}
