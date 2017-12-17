using UnityEngine;

public class MoveSyncV1 : BaseMoveSync{

    protected override void SendMoveInfo(MoveInfo moveInfo)
    {
        lastMoveInfo = moveInfo.Clone() as MoveInfo;
        lastSyncedMoveInfo = moveInfo.Clone() as MoveInfo;
        netSimulator.Send(moveInfo.Clone() as MoveInfo);
        AddNetflowCounter();
    }
}
