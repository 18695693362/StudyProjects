using UnityEngine;
using System.Collections.Generic;

// 关键帧进行同步的帧同步
public class MoveSyncV5 : BaseMoveSync{
    List<MoveInfo> sendInfoList = new List<MoveInfo>();
    List<SyncData> recievedDatumList = new List<SyncData>();
    int syncInterval = 5;
    int svrKeyframe = 0;
    int sendCurFrame = 0;
    int recieveCurFrame = 0;
    protected override void UpdateCMove()
    {
        SendMoveInfo(curMoveInfo);
    }
    protected override void SendMoveInfo(MoveInfo moveInfo)
    {
        if ( sendCurFrame <= svrKeyframe + syncInterval )
        {
            if ( isStopClient )
            {
                sendInfoList.Add ( null );
            }
            else
            {
                bool isNeedSync = false;
                if ( !lastMoveInfo.dir.Equals ( moveInfo.dir ) || lastMoveInfo.speed != moveInfo.speed )
                {
                    isNeedSync = true;
                }

                if ( isNeedSync )
                {
                    lastMoveInfo = moveInfo.Clone ( ) as MoveInfo;
                    sendInfoList.Add ( lastMoveInfo );
                }
                else
                {
                    sendInfoList.Add ( null );
                }
            }


            // 在关键帧进行同步
            if ( sendCurFrame == svrKeyframe + syncInterval)
            {
                List<MoveInfo> tmpInfoList = new List<MoveInfo>(sendInfoList.ToArray());
                SyncData syncData = new SyncData();
                syncData.keyframe = svrKeyframe + syncInterval;
                syncData.infoList = tmpInfoList;
                netSimulatorEx.Send ( syncData );
                AddNetflowCounter ( syncData );
                sendInfoList.Clear ( );
            }

            sendCurFrame += 1;
        }
        else
        {
            // block game wait for other players
        }
    }
    protected override void UpdateSMove()
    {
        SyncData syncData = netSimulatorEx.Receive();
        if (syncData!= null)
        {
            // update svrKeyframe
            svrKeyframe = syncData.keyframe;

            AddNetflowCounter(syncData);
            recievedDatumList.Add ( syncData );
        }

        if ( recievedDatumList.Count > 0 )
        {
            SyncData tmp = recievedDatumList[0];
            int idx = recieveCurFrame - (tmp.keyframe - syncInterval);
            if ( idx < tmp.infoList.Count )
            {
                MoveInfo info = tmp.infoList[idx];
                if ( info != null )
                {
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
                    UpdateGObjPos ( deltaPos, clientGObj.transform );
                    UpdateGObjDir ( info.dir, clientGObj.transform );
                    UpdateSGObjPosByDeltaPos ( deltaPos );
                    UpdateSGObjDir ( info.dir );
                }


                if ( idx == tmp.infoList.Count - 1 )
                {
                    recievedDatumList.Remove ( tmp );
                }
                recieveCurFrame += 1;
            }
        }
        else
        {
            // block game wait server data
        }
    }
}
