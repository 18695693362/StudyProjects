using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class BSCEffect : MonoBehaviour
{
	public Shader curShader;
	public float Brightness = 1.0f;
	public float Saturation = 1.0f;
	public float Contrast = 1.0f;
	private Material curMat;

	Material CurMaterial {
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
			Debug.Log ("SystemInfo.supportsImageEffects == false");
			return;
		}
		if (curShader == null) {
			enabled = false;
			Debug.Log ("curShader == null");
			return;
		}
		if (!curShader.isSupported) {
			enabled = false;
			Debug.Log ("curShader.isSupported == false");
			return;
		}
	}

	void OnRenderImage (RenderTexture srcTex, RenderTexture desTex)
	{
		if (curShader != null) {
			CurMaterial.SetFloat ("_BrightnessAmount", Brightness);
			CurMaterial.SetFloat ("_SaturationAmount", Saturation);
			CurMaterial.SetFloat ("_ContrastAmount", Contrast);
			Graphics.Blit (srcTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (srcTex, desTex);
		}
	}
	
	// Update is called once per frame
	void Update ()
	{
		Brightness = Mathf.Clamp (Brightness, 0.0f, 2.0f);
		Saturation = Mathf.Clamp (Saturation, 0.0f, 2.0f);
		Contrast = Mathf.Clamp (Contrast, 0.0f, 3.0f);
	}
}
