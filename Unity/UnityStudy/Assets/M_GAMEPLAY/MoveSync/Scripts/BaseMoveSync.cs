using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;

public class BaseMoveSync : MonoBehaviour {
    GameObject clientGObj;
    GameObject clientSGObj;
    GameObject serverGObj;
    GameObject serverArea;
    Text netflowTxt;

    public bool isShowGObjInSameArea = false;
    public bool isStopClient = false;
    public bool isAutoMove = false;
    public float autoChangeDirInterval = 4.0f;
    float autoChangeTimer = 5.0f;
    System.Random autoDirRandom = new System.Random();

    public float delayRate = 0.3f;

    public NetSimulator netSimulator = new NetSimulator();
    protected MoveInfo curMoveInfo = new MoveInfo();
    protected MoveInfo lastMoveInfo = new MoveInfo();
    protected MoveInfo svrPreMoveInfo = null;
    int maxX;
    int maxY;

    int moveSpeed = 1;
	// Use this for initialization
	void Start ()
    {
        clientGObj = transform.Find("BG_Client/ClientObj").gameObject;
        clientSGObj = transform.Find("BG_Client/CServerObj").gameObject;
        serverGObj = transform.Find("BG_Server/ServerObj").gameObject;
        serverArea = transform.Find("BG_Server").gameObject;
        netflowTxt = transform.Find("NetworkFlow").GetComponent<Text>();

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
        if (dir.x > originDirVector.x)
        {
            curEulerAngles.z = -curEulerAngles.z;
        }
        gObjTrans.localEulerAngles = curEulerAngles;
        return false;
    }

    protected bool UpdateSGObjPosByMoveInfo(MoveInfo moveInfo)
    {
        Vector3 newPos = moveInfo.position;
        clientSGObj.transform.localPosition = newPos;
        serverGObj.transform.localPosition = newPos;
        return true;
    }

    protected bool UpdateSGObjPosByDeltaPos(Vector2 deltaPos)
    {
        bool resultClientSGObj = UpdateGObjPos(deltaPos, clientSGObj.transform);
        bool resultServerGObj = UpdateGObjPos(deltaPos, serverGObj.transform);
        Debug.Assert(resultClientSGObj == resultServerGObj);

        return resultClientSGObj;
    }

    protected bool UpdateSGObjDir(Vector2 dir)
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

        UpdateNetflow();
	}

    void UpdateConfig()
    {
        netSimulator.delayRate = delayRate;
        clientSGObj.SetActive(isShowGObjInSameArea);
        serverArea.SetActive(!isShowGObjInSameArea);
    }

    bool isFirstAutoMove = true;
    void UpdateCMove()
    {
        curMoveInfo.Reset();
        if (isAutoMove)
        {
            autoChangeTimer += Time.deltaTime;
            if (autoChangeTimer > autoChangeDirInterval)
            {
                autoChangeTimer -= autoChangeDirInterval;
                int x = 0;
                int y = 0;
                if (isFirstAutoMove)
                {
                    isFirstAutoMove = false;
                    x = 1;
                    y = 1;
                }
                else
                {
                    x = autoDirRandom.Next(-1, 2);
                    y = autoDirRandom.Next(-1, 2);   
                }
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
        else
        {
            curMoveInfo.dir = lastMoveInfo.dir;
        }

        if (!isStopClient)
        {
            Vector2 deltaPos = curMoveInfo.dir * curMoveInfo.speed;
            UpdateGObjPos(deltaPos, clientGObj.transform);
            curMoveInfo.position.x = clientGObj.transform.localPosition.x;
            curMoveInfo.position.y = clientGObj.transform.localPosition.y;
            UpdateGObjDir(curMoveInfo.dir, clientGObj.transform);

            SendMoveInfo(curMoveInfo);
        }
    }

    protected virtual void SendMoveInfo(MoveInfo moveInfo)
    {
        lastMoveInfo = moveInfo.Clone() as MoveInfo;
        netSimulator.Send(moveInfo.Clone() as MoveInfo);
        AddNetflowCounter();
    }

    protected virtual void UpdateSMove()
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

    protected void AddNetflowCounter()
    {
        netflowCounter += MoveInfo.ByteSize();
    }

    float netflowTimer = 0;
    float netflowInterval = 1.0f;
    int netflowCounter = 0;
    void UpdateNetflow()
    {
        netflowTimer += Time.deltaTime;
        if (netflowTimer>=netflowInterval)
        {
            netflowTxt.text = "NetworkFlow: " + netflowCounter.ToString() + " Byte/s";

            netflowTimer -= netflowInterval;
            netflowCounter = 0;
        }
    }
}
