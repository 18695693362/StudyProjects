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

public class NetSimulator
{
    public float delayRate = 0.0f;
    System.Random netRandom = new System.Random();
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