using UnityEngine;
using System.Collections.Generic;

public static class GGameObject
{
    #region DontDestroyOnLoad
    static List<GameObject> _notDestroyedGObjs = new List<GameObject>();
    static public List<GameObject> NotDestroyedGObjs
    {
        get
        {
            return _notDestroyedGObjs;
        }
    }

    public static void DontDestroyOnLoad(GameObject gObj)
    {
        UnityEngine.Object.DontDestroyOnLoad(gObj);
        if (!_notDestroyedGObjs.Contains(gObj))
        {
            _notDestroyedGObjs.Add(gObj);
        }
        else
        {
            Debug.LogWarning("_notDestroyedGObjs is exist gObj. name=" + gObj.name);
        }
    }

    public static GameObject GetNotDestroyedGObjByName(string name)
    {
        for (int i = _notDestroyedGObjs.Count - 1; i > -1; i--)
        {
            var gObj = _notDestroyedGObjs[i];
            if (gObj != null && gObj.name == name)
            {
                return gObj;
            }
        }
        return null;
    }

    public static void DestroyNotDestroyedGObj(GameObject gObj, bool isImmediateDestroy = true)
    {
        for (int i = _notDestroyedGObjs.Count - 1; i > -1; i--)
        {
            var tmpGObj = _notDestroyedGObjs[i];
            if (gObj != tmpGObj)
            {
                if (isImmediateDestroy)
                {
                    UnityEngine.Object.DestroyImmediate(gObj);
                }
                else
                {
                    UnityEngine.Object.Destroy(gObj);
                }
                _notDestroyedGObjs.RemoveAt(i);
                return;
            }
        }
    }

    public static void DestoryNotDestroyedGObjByName(string name, bool isImmediateDestroy = true, bool isAll = true)
    {
        for (int i = _notDestroyedGObjs.Count - 1; i > -1; i--)
        {
            var gObj = _notDestroyedGObjs[i];
            if (gObj != null && gObj.name == name)
            {
                if (isImmediateDestroy)
                {
                    UnityEngine.Object.DestroyImmediate(gObj);
                }
                else
                {
                    UnityEngine.Object.Destroy(gObj);
                }
                _notDestroyedGObjs.RemoveAt(i);
            }
        }
    }

    public static void DestroyAllNotDestroyedGObj(bool isImmediateDestroy = true)
    {
        for (int i = _notDestroyedGObjs.Count - 1; i > -1; i--)
        {
            var gObj = _notDestroyedGObjs[i];
            if (gObj != null)
            {
                if (isImmediateDestroy)
                {
                    UnityEngine.Object.DestroyImmediate(gObj);
                }
                else
                {
                    UnityEngine.Object.Destroy(gObj);
                }
            }
        }
        _notDestroyedGObjs.Clear();
    }

    public static void ForeachNotDestoryedGObj(System.Func<GameObject, bool> cb)
    {
        foreach (var gObj in _notDestroyedGObjs)
        {
            if (cb != null)
            {
                if (!cb(gObj))
                {
                    break;
                }
            }
        }
    }
    #endregion

    #region Find
    static Transform ObjToTransform(Object gObjOrComp)
    {
        Transform trans = null;
        if(gObjOrComp is Component)
        {
            trans = (gObjOrComp as Component).transform;
        }
        else if(gObjOrComp is GameObject)
        {
            trans = (gObjOrComp as GameObject).transform;
        }
        else
        {
            Debug.LogError("gObjOrComp type error! gObjOrComp = " + gObjOrComp);
        }
        return trans;
    }

    static object GObjToGObjOrComp(GameObject gObj, object compTypeOrName)
    {
        object retGObjOrComp = null;
        if (gObj != null)
        {
            if (compTypeOrName != null)
            {
                if (compTypeOrName.GetType() == typeof(string))
                {
                    retGObjOrComp = gObj.GetComponent((string)compTypeOrName);
                }
                else
                {
                    retGObjOrComp = gObj.GetComponent((System.Type)compTypeOrName);
                }
            }
            else
            {
                retGObjOrComp = gObj;
            }
        }
        return retGObjOrComp;
    }

    public static GameObject FindParent(Object gObjOrComp, string targetName, bool isExceptSelf=false)
    {
        Transform trans = ObjToTransform(gObjOrComp);
        if (gObjOrComp == null)
        {
            return null;
        }

        if(!isExceptSelf)
        {
            if(trans.name == targetName)
            {
                return trans.gameObject;
            }
        }
        return FindParent(trans.parent, targetName);
        
    }

    public static object FindParent(Object gObjOrComp, string parentName, object compTypeOrName, bool isExceptSelf=false)
    {
        var gObj = FindParent(gObjOrComp, parentName, isExceptSelf);
        return GObjToGObjOrComp(gObj, compTypeOrName);
    }

    public static GameObject Find(Object gObjOrComp, string targetName, bool isExceptSelf=false)
    {
        Transform trans = ObjToTransform(gObjOrComp);
        if (gObjOrComp == null)
        {
            return null;
        }

        if(!isExceptSelf)
        {
            if(trans.name == targetName)
            {
                return trans.gameObject;
            }
        }
        foreach(Transform t in trans)
        {
            GameObject result = Find(t, targetName);
            if(result!=null)
            {
                return result;
            }
        }
        return null;
    }

    public static object Find(Object gObjOrComp, string childName, object compTypeOrName, bool isExceptSelf=false)
    {
        var gObj = Find(gObjOrComp, childName, isExceptSelf);
        return GObjToGObjOrComp(gObj, compTypeOrName);
    }
    
    public static Component GetComponentInParent(Object gObjOrComp, object compTypeOrName, bool isExceptSelf=false)
    {
        Transform trans = ObjToTransform(gObjOrComp);
        if (gObjOrComp == null || compTypeOrName==null)
        {
            return null;
        }
        
        if (!isExceptSelf)
        {
            Component comp = (Component)GObjToGObjOrComp(trans.gameObject, compTypeOrName);
            if(comp!=null)
            {
                return comp;
            }
        }
        return GetComponentInParent(trans.parent, compTypeOrName);
    }
    public static Component GetComponentInChildren(Object gObjOrComp, object compTypeOrName, bool isExceptSelf=false)
    {
        Transform trans = ObjToTransform(gObjOrComp);
        if (gObjOrComp == null)
        {
            return null;
        }

        if(!isExceptSelf)
        {
            Component comp = (Component)GObjToGObjOrComp(trans.gameObject, compTypeOrName);
            if(comp!=null)
            {
                return comp;
            }
        }
        foreach(Transform t in trans)
        {
            Component comp = GetComponentInChildren(t, compTypeOrName);
            if(comp!=null)
            {
                return comp;
            }
        }
        return null;
    }
    #endregion

    #region Transform
    public static void RemoveAllChild(Transform trans, bool isImmediate = false)
    {
        if (trans != null)
        {
            for (int i = trans.childCount - 1; i >= 0; i--)
            {
                if (isImmediate)
                {
                    GameObject.DestroyImmediate(trans.GetChild(i).gameObject);
                }
                else
                {
                    GameObject.Destroy(trans.GetChild(i).gameObject);
                }
            }
        }
    }
    #endregion
}
