using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

public class MoveInfo:ICloneable
{
    public Vector2 dir = Vector2.zero;
    public Vector2 position = Vector2.zero;
    public int speed = 0;
    // send time unit - second
    public float sendTime;
    
    // receive time unit-ms
    public double receiveTime;

    public void Reset()
    {
        dir = Vector2.zero;
        position = Vector2.zero;
        speed = 0;
    }

    public object Clone()
    {
        return MemberwiseClone();
    }

    public static int ByteSize()
    {
        return sizeof(float) * 4 + sizeof(int);
    }
}

public class NetSimulatorBase
{
    public float delayRate = 0.0f;
    protected System.Random netRandom = new System.Random();
}

public class NetSimulator: NetSimulatorBase
{
    List<MoveInfo> sendStack = new List<MoveInfo>();

    public bool IsNetDataEmpty()
    {
        return sendStack.Count == 0;
    }

    public MoveInfo Receive()
    {
        if (sendStack.Count > 0)
        {
            MoveInfo info = sendStack[0];
            if (netRandom.Next(100)/100.0f > delayRate)
            {
                // not delay
                sendStack.RemoveAt(0);
                return info;
            }
        }
        return null;
    }

    public void Send(MoveInfo moveInfo)
    {
        if (moveInfo != null)
        {
            sendStack.Add(moveInfo);
        }
    }
}

public class SyncData
{
    public int keyframe;
    public List<MoveInfo> infoList = new List<MoveInfo>();
}

public class NetSimulatorEx:NetSimulatorBase
{
    public int keyframe = 5;
    List<SyncData> sendStack = new List<SyncData>();

    public bool IsNetDataEmpty()
    {
        return sendStack.Count == 0;
    }

    public SyncData Receive()
    {
        if (sendStack.Count > 0)
        {
            SyncData syncData = sendStack[0];
            if (netRandom.Next(100)/100.0f > delayRate)
            {
                // not delay
                sendStack.RemoveAt(0);
                return syncData;
            }
        }
        return null;
    }

    public void Send(SyncData syncData)
    {
        if (syncData!= null)
        {
            sendStack.Add(syncData);
        }
    }
}