using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class GrayScreenEF : MonoBehaviour
{

	public Shader curShader;
	public float grayScaleAmount = 1.0f;
	private Material curMat;

	public Material CurMaterial {
		get {
			if (curMat == null) {
				curMat = new Material (curShader);
				curMat.hideFlags = HideFlags.HideAndDontSave;
			}
			return curMat;
		}
	}

	// Use this for initialization
	void Start ()
	{
		if (!SystemInfo.supportsImageEffects) {
			enabled = false;
			return;
		}
		if (!curShader && !curShader.isSupported) {
			enabled = false;
		}
	}

	void OnRenderImage (RenderTexture sourceTex, RenderTexture desTex)
	{
		if (curShader != null) {
			CurMaterial.SetFloat ("_LuminosityAmount", grayScaleAmount);
			Graphics.Blit (sourceTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (sourceTex, desTex);
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		grayScaleAmount = Mathf.Clamp (grayScaleAmount, 0.0f, 1.0f);
	}

	void OnDisable ()
	{
		if (curMat) {
			DestroyImmediate (curMat);
			curMat = null;
		}
	}
}
