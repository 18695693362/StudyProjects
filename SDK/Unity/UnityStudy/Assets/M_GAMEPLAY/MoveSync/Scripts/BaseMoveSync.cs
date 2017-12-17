using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using System;
using System.Collections.Generic;

public class BaseMoveSync : MonoBehaviour {
    protected GameObject clientGObj;
    protected GameObject clientSGObj;
    protected GameObject serverGObj;
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
    public NetSimulatorEx netSimulatorEx = new NetSimulatorEx();
    protected MoveInfo curMoveInfo = new MoveInfo();
    protected MoveInfo lastMoveInfo = new MoveInfo();
    protected MoveInfo lastSyncedMoveInfo = new MoveInfo();
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

    protected bool UpdateGObjPos(Vector2 deltaPos, Transform gObjTrans)
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

    protected bool UpdateGObjDir(Vector2 dir, Transform gObjTrans)
    {
        if (dir.magnitude < 0.01)
        {
            return false;
        }
        Vector3 curEulerAngles = gObjTrans.localEulerAngles;
        curEulerAngles.z = ConvertDirToEulerAngleZ(dir);
        
        gObjTrans.localEulerAngles = curEulerAngles;
        return true;
    }

    Vector2 originDirVector = new Vector2(0, 1);
    public float ConvertDirToEulerAngleZ(Vector2 dir)
    {
        float eulerAngleZ = Vector2.Angle(originDirVector, dir);
        if (dir.x > originDirVector.x)
        {
            eulerAngleZ = -eulerAngleZ;
        }
        return eulerAngleZ;
    }

    public Vector2 ConvertEulerAngleZToDir(float eulerAngleZ)
    {
        Vector2 dir = Quaternion.Euler(0,0,eulerAngleZ) * originDirVector;
        return dir.normalized;
    }

    protected Vector2 GetSGObjPos()
    {
        return serverGObj.transform.localPosition;
    }

    protected Vector2 GetSGObjDir()
    {
        return ConvertEulerAngleZToDir(serverGObj.transform.localEulerAngles.z);
    }

    protected bool UpdateSGObjPosByPos(Vector2 pos)
    {
        clientSGObj.transform.localPosition = pos;
        serverGObj.transform.localPosition = pos;
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

        UpdateCurMoveInfo();

        UpdateCMove();

        UpdateSMove();

        UpdateNetflow();
	}

    void UpdateConfig()
    {
        netSimulator.delayRate = delayRate;
        netSimulatorEx.delayRate = delayRate;
        clientSGObj.SetActive(isShowGObjInSameArea);
        serverArea.SetActive(!isShowGObjInSameArea);
    }

    bool isFirstAutoMove = true;
    void UpdateCurMoveInfo()
    {
        curMoveInfo.Reset();
        if (isAutoMove)
        {
            if (!isStopClient)
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
                    curMoveInfo.speed = moveSpeed;
                    //Debug.Log("- dir = "+curMoveInfo.dir.ToString());
                }
                else
                {
                    curMoveInfo = lastMoveInfo.Clone() as MoveInfo;
                }
            }
            else
            {
                curMoveInfo = lastMoveInfo.Clone() as MoveInfo;
                curMoveInfo.speed = 0;
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

            if (curMoveInfo.dir != Vector2.zero)
            {
                curMoveInfo.speed = moveSpeed;
            }
        }
        
        if (curMoveInfo.dir != Vector2.zero)
        {
            curMoveInfo.dir.Normalize();
        }
        else
        {
            curMoveInfo.dir = lastMoveInfo.dir;
        }
    }

    protected virtual void UpdateCMove()
    {
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
        // do nothing 
    }

    protected virtual void UpdateSMove()
    {
        if ( netSimulator.IsNetDataEmpty() && curMoveInfo.speed == 0 )
        {
            return;
        }

        MoveInfo info = netSimulator.Receive();
        if (info != null)
        {
            AddNetflowCounter();

            UpdateSGObjPosByPos(info.position);
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

    protected void AddNetflowCounter(SyncData syncData)
    {
        if ( syncData != null )
        {
            netflowCounter += sizeof ( int );
            AddNetflowCounter ( syncData.infoList );
        }
    }

    protected void AddNetflowCounter(List<MoveInfo> infoList)
    {
        if ( infoList != null )
        {
            foreach ( var info in infoList )
            {
                if ( info != null )
                    AddNetflowCounter ( );
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
