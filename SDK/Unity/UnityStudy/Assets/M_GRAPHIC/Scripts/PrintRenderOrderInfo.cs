using UnityEngine;
using System.Collections;
using System.Text;

public class PrintRenderOrderInfo : MonoBehaviour {

    public bool isUpdateRenderQueue = false;
    public int renderQueue = 2000;
    void OnEnable()
    {
        PrintOrderInfo(GetRenderer());
    }

    Renderer GetRenderer()
    {
        Renderer renderer = null;
        if (renderer == null)
            renderer = gameObject.GetComponent<MeshRenderer>();
        if (renderer == null)
            renderer = gameObject.GetComponent<MeshRenderer>();
        if (renderer == null)
            renderer = gameObject.GetComponent<SpriteRenderer>();
        return renderer;
    }

    void PrintOrderInfo(Renderer renderer)
    {
        if (renderer != null)
        {
            StringBuilder log = new StringBuilder();
            log.Append("--- Render OrderInfo --- " + name + "\n");
            log.Append(" sortingLayer = " + renderer.sortingLayerName + "\n");
            log.Append(" sortingOrder = " + renderer.sortingOrder + "\n");
            if(renderer.material != null)
            {
                log.Append(" renderQueue = " + renderer.material.renderQueue);
            }
            Debug.Log(log);
        }
    }

    void Update()
    {
        Renderer renderer = GetRenderer();
        if(isUpdateRenderQueue && renderer != null && renderer.material != null)
        {
            if(renderer.material.renderQueue!=renderQueue)
            {
                renderer.material.renderQueue = renderQueue;
            }
        }
    }
}
