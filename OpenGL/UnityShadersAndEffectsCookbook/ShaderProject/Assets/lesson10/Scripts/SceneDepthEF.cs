using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class SceneDepthEF : MonoBehaviour
{

	public Shader curShader;
	public float depthPower = 0.1f;
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
		if (curShader == null || !curShader.isSupported) {
			enabled = false;
		}
	}

	void OnRenderImage (RenderTexture sourceTex, RenderTexture desTex)
	{
		if (curShader != null) {
			CurMaterial.SetFloat ("_DepthPower", depthPower);
			Graphics.Blit (sourceTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (sourceTex, desTex);
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		Camera.main.depthTextureMode = DepthTextureMode.Depth;
		depthPower = Mathf.Clamp (depthPower, 0.1f, 5.0f);
	}

	void OnDisable ()
	{
		if (curMat) {
			DestroyImmediate (curMat);
			curMat = null;
		}
	}
}
