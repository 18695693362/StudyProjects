using UnityEngine;
using System.Collections;

public class S1_StateEvent : MonoBehaviour {
    public bool isDestroyChild = false;
    public bool childActiveValue = false;
    public bool addOrRemoveScriptOfChild = false;

    void Awake() {
        Debug.Log("Invoke Awake -- " + name);
    }

    void Update()
    {
        if(transform.childCount>0)
        {
            var child = transform.GetChild(0).gameObject;
            if(child.activeSelf != childActiveValue)
            {
                child.SetActive(childActiveValue);
            }
        }

        if(transform.childCount>0)
        {
            var child = transform.GetChild(0).gameObject;
            var comp = child.GetComponent<S1_StateEvent>();
            if(addOrRemoveScriptOfChild)
            {
                if(comp == null)
                {
                    child.AddComponent<S1_StateEvent>();
                }
            }
            else
            {
                if(comp != null)
                {
                    Destroy(comp);
                }
            }
        }

        if (isDestroyChild)
        {
            if(transform.childCount>0)
            {
                GameObject.Destroy(transform.GetChild(0).gameObject);
            }
        }
    }

	// Use this for initialization
	void Start () {
        Debug.Log("Invoke Start -- " + name);
	}

    void OnEnable()
    {
        Debug.Log("Invoke OnEnable -- " + name);
    }

    void OnDisable()
    {
        Debug.Log("Invoke OnDisable -- " + name);
    }

    void OnDestroy()
    {
        Debug.Log("Invoke OnDestroy -- " + name);
    }
}
