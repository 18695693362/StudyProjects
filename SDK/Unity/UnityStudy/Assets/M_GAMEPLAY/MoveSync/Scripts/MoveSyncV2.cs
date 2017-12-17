using UnityEngine;

public class MoveSyncV2 : BaseMoveSync{
    public bool isEnableStateCheck = true;
    public bool isEnableDeadReckoning = true;
    public float drThreshold = 5.0f;
    protected override void SendMoveInfo(MoveInfo moveInfo)
    {
        bool isNeedSync = false;
        if ( isEnableStateCheck )
        {
            if (!lastMoveInfo.dir.Equals(moveInfo.dir) || lastMoveInfo.speed!=moveInfo.speed)
            {
                isNeedSync = true;
            }
        }

        // Dead Reckoning
        // state check have a higher priority 
        if ( !isNeedSync && isEnableDeadReckoning )
        {
            Vector2 predictedPos = lastSyncedMoveInfo.position;
            predictedPos += (lastSyncedMoveInfo.dir * lastSyncedMoveInfo.speed * (Time.time-lastSyncedMoveInfo.sendTime));
            float offset = Vector2.Distance(predictedPos, moveInfo.position);
            //Debug.Log("offset between real and predicted = " + offset.ToString());
            if (offset > drThreshold)
            {
                isNeedSync = true;
            }
        }

        moveInfo.sendTime = Time.time;
        lastMoveInfo = moveInfo.Clone() as MoveInfo;
        if (isNeedSync)
        {
            lastSyncedMoveInfo = moveInfo.Clone() as MoveInfo;
            netSimulator.Send(moveInfo.Clone() as MoveInfo);
            AddNetflowCounter();
        }
    }
}
