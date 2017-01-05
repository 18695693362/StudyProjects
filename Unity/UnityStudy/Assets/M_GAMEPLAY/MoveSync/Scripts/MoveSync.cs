using UnityEngine;
using UnityEngine.UI;
using System;
using System.Collections.Generic;

public class MoveSync : MonoBehaviour {
    public GameObject clientGObj;
    public GameObject clientSGObj;
    public GameObject serverGObj;
    public GameObject serverArea;

    public bool isShowGObjInSameArea = false;
    public bool isAutoMove = false;
    public float autoChangeDirInterval = 5.0f;
    float autoChangeTimer = 5.0f;
    System.Random autoDirRandom = new System.Random();

    public int delayTime = 0;
    public int delayDeltaTime = 0;

    public NetSimulator netSimulator = new NetSimulator();
    MoveInfo curMoveInfo = new MoveInfo();
    MoveInfo lastMoveInfo = new MoveInfo();
    MoveInfo svrCurMoveInfo = null;
    int maxX;
    int maxY;

    int moveSpeed = 1;
	// Use this for initialization
	void Start ()
    {
        clientGObj.transform.localPosition = Vector3.zero;
        clientSGObj.transform.localPosition = Vector3.zero;
        serverGObj.transform.localPosition = Vector3.zero;

        maxX = (int)serverArea.GetComponent<RectTransform>().sizeDelta.x;
        maxY = (int)serverArea.GetComponent<RectTransform>().sizeDelta.y;
	}

    bool UpdateGObjPos(Vector2 deltaPos, Transform gObjTrans)
    {
        Vector3 curPos = gObjTrans.localPosition;
        curPos.x += deltaPos.x;
        curPos.y += deltaPos.y;
        if (curPos.x < 0)
        {
            curPos.x = 0;
        }
        if (curPos.x > maxX)
        {
            curPos.x = maxX;
        }
        if (curPos.y < 0)
        {
            curPos.y = 0;
        }
        if (curPos.y > maxY)
        {
            curPos.y = maxY;
        }
        if (curPos != gObjTrans.localPosition)
        {
            gObjTrans.localPosition = curPos;
            return true;
        }
        return false;
    }

    Vector2 originDirVector = new Vector2(0, 1);
    bool UpdateGObjDir(Vector2 dir, Transform gObjTrans)
    {
        Vector3 curEulerAngles = gObjTrans.localEulerAngles;
        curEulerAngles.z = Vector2.Angle(originDirVector, dir);
        gObjTrans.localEulerAngles = curEulerAngles;
        return false;
    }

    bool UpdateSGObjPos(Vector2 deltaPos)
    {
        bool resultClientSGObj = UpdateGObjPos(deltaPos, clientSGObj.transform);
        bool resultServerGObj = UpdateGObjPos(deltaPos, serverGObj.transform);
        Debug.Assert(resultClientSGObj == resultServerGObj);

        return resultClientSGObj;
    }

    bool UpdateSGObjDir(Vector2 dir)
    {
        bool resultClientSGObj = UpdateGObjDir(dir, clientSGObj.transform);
        bool resultServerGObj = UpdateGObjDir(dir, serverGObj.transform);
        Debug.Assert(resultClientSGObj == resultServerGObj);

        return resultServerGObj;
    }
	
	// Update is called once per frame
	void Update ()
    {
        UpdateConfig();

        UpdateCMove();

        UpdateSMove();
	}

    void UpdateConfig()
    {
        netSimulator.delayTime = delayTime;
        netSimulator.delayDeltaTime = delayDeltaTime;
        clientSGObj.SetActive(isShowGObjInSameArea);
        serverArea.SetActive(!isShowGObjInSameArea);
    }

    void UpdateCMove()
    {
        curMoveInfo.Reset();
        if (isAutoMove)
        {
            autoChangeTimer += Time.deltaTime;
            if (autoChangeTimer > autoChangeDirInterval)
            {
                autoChangeTimer -= autoChangeDirInterval;
                int x = autoDirRandom.Next(-1, 2);
                int y = autoDirRandom.Next(-1, 2);
                curMoveInfo.dir.x = x;
                curMoveInfo.dir.y = y;
                //Debug.Log("- dir = "+curMoveInfo.dir.ToString());
            }
            else
            {
                curMoveInfo = lastMoveInfo.Clone() as MoveInfo;
            }
        }
        else
        {
            if (Input.GetKey(KeyCode.A))
            {
                curMoveInfo.dir.x = -1;
            }
            if (Input.GetKey(KeyCode.D))
            {
                curMoveInfo.dir.x = 1;
            }
            if (Input.GetKey(KeyCode.W))
            {
                curMoveInfo.dir.y = 1;
            }
            if (Input.GetKey(KeyCode.S))
            {
                curMoveInfo.dir.y = -1;
            }
        }
        
        if (curMoveInfo.dir != Vector2.zero)
        {
            curMoveInfo.speed = moveSpeed;
            curMoveInfo.dir.Normalize();
        }

        Vector2 deltaPos = curMoveInfo.dir * curMoveInfo.speed;
        UpdateGObjPos(deltaPos, clientGObj.transform);
        UpdateGObjDir(curMoveInfo.dir, clientGObj.transform);

        lastMoveInfo = curMoveInfo.Clone() as MoveInfo;
        netSimulator.Send(curMoveInfo.Clone() as MoveInfo);
    }

    void UpdateSMove()
    {
        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            svrCurMoveInfo = info;
        }
        if (svrCurMoveInfo != null)
        {
            UpdateSGObjPos(svrCurMoveInfo.dir*svrCurMoveInfo.speed);
            UpdateSGObjDir(svrCurMoveInfo.dir);
        }
    }
}

public class MoveInfo:ICloneable
{
    public Vector2 dir = Vector2.zero;
    public Vector2 position = Vector2.zero;
    public int speed = 0;

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
}

public class NetSimulator
{
    System.Random delayTimeRandom = new System.Random();
    List<MoveInfo> sendStack = new List<MoveInfo>();

    public int delayTime = 0;
    public int delayDeltaTime = 0;
    public MoveInfo Receive()
    {
        if (sendStack.Count > 0)
        {
            MoveInfo info = sendStack[0];
            TimeSpan span = new TimeSpan(DateTime.Now.Ticks);
            if (span.TotalMilliseconds >= info.receiveTime)
            {
                Debug.Log("+++++++++++++++++++++++++++++++");
                Debug.Log("curTime = " + span.TotalMilliseconds.ToString());
                Debug.Log("rcvTime = " + info.receiveTime.ToString());
                sendStack.RemoveAt(0);
                return info;
            }
        }
        return null;
    }

    bool isBeginSend = true;
    double preSendTime = 0;
    public void Send(MoveInfo moveInfo)
    {
        if (moveInfo != null)
        {
            int delay = delayTimeRandom.Next(delayTime, delayTime + delayDeltaTime);
            if (isBeginSend)
            {
                isBeginSend = false;
                TimeSpan span = new TimeSpan(DateTime.Now.Ticks);
                moveInfo.receiveTime = span.TotalMilliseconds + delay;
            }
            else
            {
                moveInfo.receiveTime = preSendTime + delay;
            }
            preSendTime = moveInfo.receiveTime;
            sendStack.Add(moveInfo);
        }
    }
}