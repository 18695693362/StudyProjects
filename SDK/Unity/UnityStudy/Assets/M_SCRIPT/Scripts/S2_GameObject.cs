using UnityEngine;
using System.Collections;

public class S2_GameObject : MonoBehaviour
{
    public bool isTestGameObjectFind = false;
    public bool isTestObjectDestroy = false;
    public bool isDoDestroyInOnEnable = false;
    public bool isDoDestroyInStart = false;
    public bool isDoDestroyInUpdate = false;
    public bool isDoDestroyInLateUpdate = false;
    public bool isDoDestroyInPostRender = false;

    ~S2_GameObject()
    {
        if(isTestObjectDestroy)
            Debug.Log("-- Finalize S2_GameObject");
    }

	// Use this for initialization
	void Start ()
    {
        // 1 测试GameObject.Find方法
        if (isTestGameObjectFind)
        {
            GameObjectFind("go1");
            GameObjectFind("go2-1");
            GameObjectFind("go3.1");
            GameObjectFind("go3.2");

            GameObject goNotDestoryRoot = new GameObject("NotDestory_root");
            GameObject goChild1 = new GameObject("go4");
            goChild1.transform.parent = goNotDestoryRoot.transform;
            GameObjectFind("go4");
        }

        if (isTestObjectDestroy && isDoDestroyInStart)
        {
            Debug.Log("Start Before Invoke Destroy");
            Destroy(this);
            Debug.Log("Start After Invoke Destroy");
        }
	}
	
    void GameObjectFind(string name)
    {
        GameObject go = GameObject.Find(name);
        if (go!=null)
        {
            Debug.Log("GameObject.Find name = " + name + " parent = " + go.transform.parent.name);
        }
        else
        {
            Debug.Log("GameObject.Find name = " + name + " FAILED!");
        }
    }

    void Update()
    {
        if (isTestObjectDestroy)
            Debug.Log("-- Update name = " + name);

        if(isTestObjectDestroy && isDoDestroyInUpdate)
        {
            Debug.Log("Update Before Invoke Destroy");
            Destroy(this);
            Debug.Log("Update After Invoke Destroy");
        }
    }
    void LateUpdate()
    {
        if (isTestObjectDestroy)
            Debug.Log("-- LateUpdate name = " + name);

        if(isTestObjectDestroy&&isDoDestroyInLateUpdate)
        {
            Debug.Log("LateUpdate Before Invoke Destroy");
            Destroy(this);
            Debug.Log("LateUpdate After Invoke Destroy");
        }
    }
    void OnPreRender()
    {
        if(isTestObjectDestroy)
            Debug.Log("-- OnPreRender name = " + name);
    }
    void OnPostRender()
    {
        if(isTestObjectDestroy)
            Debug.Log("-- OnPostRender name = " + name);

        if(isTestObjectDestroy&&isDoDestroyInPostRender)
        {
            Debug.Log("OnPostRender Before Invoke Destroy");
            Destroy(this);
            Debug.Log("OnPostRender After Invoke Destroy");
        }
    }
    void OnEnable()
    {
        if (isTestObjectDestroy)
            Debug.Log("-- OnEnable name = " + name);

        if(isTestObjectDestroy && isDoDestroyInOnEnable)
        {
            Debug.Log("OnEnable Before Invoke Destroy");
            Destroy(this);
            Debug.Log("OnEnable After Invoke Destroy");
        }
    }
    void OnDisable()
    {
        if (isTestObjectDestroy)
            Debug.Log("-- OnDisable name = " + name);
    }
    void OnDestroy()
    {
        if (isTestObjectDestroy)
            Debug.Log("-- OnDestroy name = " + name);
    }
}
