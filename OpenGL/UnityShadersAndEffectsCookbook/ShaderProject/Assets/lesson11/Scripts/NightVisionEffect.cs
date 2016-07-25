using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class NightVisionEffect : MonoBehaviour
{
	public Shader curShader;
	public Texture2D VignetteTex;
	public Texture2D ScanLineTex;
	public Texture2D NoiseTex;
	public float NoiseXSpeed = 100f;
	public float NoiseYSpeed = 100f;
	public float ScanLineTileAmount = 4f;
	public Color NightVisionColor = Color.white;
	public float Contrast = 2f;
	public float Brightness = 1f;
	public float RandomValue;
	public float Distortion = 0.2f;
	public float Scale = 0.8f;

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
			}
			if (ScanLineTex != null) {
				CurMaterial.SetTexture ("_ScanLineTex", ScanLineTex);
				CurMaterial.SetFloat ("_ScanLineTileAmount", ScanLineTileAmount);
			}
			if (NoiseTex != null) {
				CurMaterial.SetTexture ("_NoiseTex", NoiseTex);
				CurMaterial.SetFloat ("_NoiseXSpeed", NoiseXSpeed);
				CurMaterial.SetFloat ("_NoiseYSpeed", NoiseYSpeed);
			}
			CurMaterial.SetColor ("_NightVisionColor", NightVisionColor);
			CurMaterial.SetFloat ("_Contrast", Contrast);
			CurMaterial.SetFloat ("_Brightness", Brightness);
			CurMaterial.SetFloat ("_Distortion", Distortion);
			CurMaterial.SetFloat ("_Scale", Scale);
			CurMaterial.SetFloat ("_RandomValue", RandomValue);

			Graphics.Blit (srcTex, desTex, CurMaterial);
		} else {
			Graphics.Blit (srcTex, desTex);
		}
	}

	// Update is called once per frame
	void Update ()
	{
		Brightness = Mathf.Clamp (Brightness, -1f, 1f);
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
