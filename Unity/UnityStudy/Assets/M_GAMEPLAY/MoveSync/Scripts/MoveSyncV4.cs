using UnityEngine;

public class MoveSyncV4 : BaseMoveSync{
    protected override void UpdateSMove()
    {
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();

            UpdateSGObjPosByMoveInfo(info);
            UpdateSGObjDir(info.dir);

            svrPreMoveInfo = info;
        }
        else
        {
            if (svrPreMoveInfo != null)
            {
                UpdateSGObjPosByDeltaPos(svrPreMoveInfo.dir*svrPreMoveInfo.speed);
                UpdateSGObjDir(svrPreMoveInfo.dir);
            }    
        }
    }
}
