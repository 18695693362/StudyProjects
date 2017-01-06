using UnityEngine;

public class MoveSyncV2 : BaseMoveSync{
    protected override void SendMoveInfo(MoveInfo moveInfo)
    {
        if (lastMoveInfo.dir.Equals(moveInfo.dir) && lastMoveInfo.speed==moveInfo.speed)
        {
            return;
        }

        lastMoveInfo = moveInfo.Clone() as MoveInfo;
        netSimulator.Send(moveInfo.Clone() as MoveInfo);
        AddNetflowCounter();
    }
}
