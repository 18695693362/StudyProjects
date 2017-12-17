using UnityEngine;
using System.Collections;

public class S1_StateEvent : MonoBehaviour {
    public bool isDestroyChild = false;
    public bool childActiveValue = false;
    public bool addOrRemoveScriptOfChild = false;
    public bool isPrintOneTimesInUpdate = true;

    void Awake() {
        Debug.Log("Invoke Awake -- " + name);
    }

    int printInUpdateCount = 0;
    void Update()
    {
        if (printInUpdateCount < 1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke Update -- " + name + " " + printInUpdateCount);
            printInUpdateCount++;
        }

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

    int printInLateUpdateCount = 0;
    void LateUpdate()
    {
        if (printInLateUpdateCount < 1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke LateUpdate -- " + name + " " + printInLateUpdateCount);
            printInLateUpdateCount++;
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

    int printInOnWillRenderObject = 0;
    void OnWillRenderObject ( )
    {
        if (printInOnWillRenderObject<1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke OnWillRenderObject -- " + name + " " + printInOnWillRenderObject);
            printInOnWillRenderObject++;
        }
    }

    int printInOnPreRenderCount = 0;
    void OnPreRender()
    {
        if(printInOnPreRenderCount<1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke OnPreRender -- " + name + " " + printInOnPreRenderCount);
            printInOnPreRenderCount++;
        }
    }

    int printInOnRenderImageCount = 0;
    void OnRenderImage(RenderTexture src, RenderTexture dest)
    {
        if(printInOnRenderImageCount<1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke OnRenderImage -- " + name + " " + printInOnRenderImageCount);
            printInOnRenderImageCount++;
        }
    }

    int printInOnPostRenderCount = 0;
    void OnPostRender()
    {
        if(printInOnPostRenderCount<1 || !isPrintOneTimesInUpdate)
        {
            Debug.Log("Invoke OnPostRender -- " + name + " " + printInOnPostRenderCount);
            printInOnPostRenderCount++;
        }
    }
}
