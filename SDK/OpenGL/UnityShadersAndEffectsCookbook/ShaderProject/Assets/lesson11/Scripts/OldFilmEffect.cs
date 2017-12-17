using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class OldFilmEffect : MonoBehaviour
{
	public Shader curShader;
	public Texture2D VignetteTex;
	public Texture2D ScratchesTex;
	public Texture2D DustTex;
	public Color SepiaColor = Color.white;
	public float EffectAmount = 0.5f;
	public float VignetteAmount = 0.5f;
	public float ScratchesXSpeed = 10f;
	public float ScratchesYSpeed = 10f;
	public float DustXSpeed = 10f;
	public float DustYSpeed = 10f;
	public float RandomValue;

	private Material curMat;

	Material CurMaterial {
		get {
			if (curMat == null) {
				curMat = new Material (curShader);
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
			if (VignetteTex != null) {
				CurMaterial.SetTexture ("_VignetteTex", VignetteTex);
				CurMaterial.SetFloat ("_VignetteAmount", VignetteAmount);
			}
			if (ScratchesTex != null) {
				CurMaterial.SetTexture ("_ScratchesTex", ScratchesTex);
				CurMaterial.SetFloat ("_ScratchesXSpeed", ScratchesXSpeed);
				CurMaterial.SetFloat ("_ScratchesYSpeed", ScratchesYSpeed);
			}
			if (DustTex != null) {
				CurMaterial.SetTexture ("_DustTex", DustTex);
				CurMaterial.SetFloat ("_DustXSpeed", DustXSpeed);
				CurMaterial.SetFloat ("_DustYSpeed", DustYSpeed);
			}

			CurMaterial.SetColor ("_SepiaColor", SepiaColor);
			CurMaterial.SetFloat ("_EffectAmount", EffectAmount);
			CurMaterial.SetFloat ("_RandomValue", RandomValue);

			Graphics.Blit (srcTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (srcTex, desTex);
		}
	}

	// Update is called once per frame
	void Update ()
	{
		EffectAmount = Mathf.Clamp01 (EffectAmount);
		VignetteAmount = Mathf.Clamp01 (VignetteAmount);
		RandomValue = Random.Range (0.0f, 1.0f);
	}

	void OnDisable ()
	{
		if (curMat) {
			DestroyImmediate (curMat);
			curMat = null;
		}
	}
}
