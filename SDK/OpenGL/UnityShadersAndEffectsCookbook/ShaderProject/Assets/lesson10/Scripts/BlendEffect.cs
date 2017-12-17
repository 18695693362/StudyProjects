using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class BlendEffect : MonoBehaviour
{
	public enum BlendType
	{
		Multiply,
		Add,
		Screen,
		Overlay
	}

	public BlendType blendType;
	public Shader curShader;
	public Texture2D blendTex;
	public float blendFactor = 0.5f;
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
			CurMaterial.SetTexture ("_BlendTex", blendTex);
			CurMaterial.SetFloat ("_BlendFactor", blendFactor);
			CurMaterial.SetFloat ("_BlendType", (float)blendType);
			Graphics.Blit (srcTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (srcTex, desTex);
		}
	}

	void Update ()
	{
		blendFactor = Mathf.Clamp (blendFactor, 0.0f, 1.0f);
	}

	void OnDisable ()
	{
		if (curMat) {
			DestroyImmediate (curMat);
			curMat = null;
		}
	}
}
