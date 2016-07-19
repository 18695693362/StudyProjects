using UnityEngine;
using System.Collections;

public class ProceduralTexture : MonoBehaviour
{
	public enum ProceduralTexType: int
	{
		Parabola,
		Rings,
		DotProductOfPixelDir,
		AngleOfPixelDir
	}

	public ProceduralTexType procTexType;

	public int widthHeight = 100;
	public Texture2D generaledTex;

	private Material curMaterial;
	private Vector2 centerPosition;

	// Use this for initialization
	void Start ()
	{
		if (!curMaterial) {
			curMaterial = transform.GetComponent<MeshRenderer> ().material;
			if (!curMaterial) {
				Debug.LogWarning ("Cannot found a material on " + transform.name);
			}
		}

		if (curMaterial) {
			centerPosition = new Vector2 (0.5f, 0.5f);
			switch (procTexType) {
			case ProceduralTexType.Parabola:
				generaledTex = GenerateParabola ();
				break;
			case ProceduralTexType.Rings:
				generaledTex = GenerateRings ();
				break;
			case ProceduralTexType.DotProductOfPixelDir:
				generaledTex = GenerateDotProductOfPixelDir ();
				break;
			case ProceduralTexType.AngleOfPixelDir:
				generaledTex = GenerateAngleOfPixelDir ();
				break;
			}
			curMaterial.SetTexture ("_MainTex", generaledTex);
		}
	}

	private Texture2D GenerateParabola ()
	{
		Texture2D tempTex = new Texture2D (widthHeight, widthHeight);
		Vector2 centerPixelPos = centerPosition * widthHeight;

		Vector2 curPosition = new Vector2 ();
		float pixelDistance = 0;
		Color pixelColor = new Color ();
		pixelColor.a = 1.0f;
		for (int x = 0; x < widthHeight; x++) {
			for (int y = 0; y < widthHeight; y++) {
				curPosition.x = x;
				curPosition.y = y;
				pixelDistance = Vector2.Distance (curPosition, centerPixelPos) / widthHeight * 0.5f;
				pixelDistance = Mathf.Abs (1 - Mathf.Clamp (pixelDistance, 0f, 1f));

				pixelColor.r = pixelDistance;
				pixelColor.g = pixelDistance;
				pixelColor.b = pixelDistance;

				tempTex.SetPixel (x, y, pixelColor);
			}
		}
		tempTex.Apply ();
		return tempTex;
	}

	private Texture2D GenerateRings ()
	{
		Texture2D tempTex = new Texture2D (widthHeight, widthHeight);
		Vector2 centerPixelPos = centerPosition * widthHeight;

		Vector2 curPosition = new Vector2 ();
		float pixelDistance = 0;
		Color pixelColor = new Color ();
		pixelColor.a = 1.0f;
		for (int x = 0; x < widthHeight; x++) {
			for (int y = 0; y < widthHeight; y++) {
				curPosition.x = x;
				curPosition.y = y;
				pixelDistance = Vector2.Distance (curPosition, centerPixelPos) / widthHeight * 0.5f;
				pixelDistance = Mathf.Abs (1 - Mathf.Clamp (pixelDistance, 0f, 1f));
				pixelDistance = (Mathf.Sin (pixelDistance * 60.0f) * pixelDistance);

				pixelColor.r = pixelDistance;
				pixelColor.g = pixelDistance;
				pixelColor.b = pixelDistance;

				tempTex.SetPixel (x, y, pixelColor);
			}
		}
		tempTex.Apply ();
		return tempTex;
	}

	private Texture2D GenerateDotProductOfPixelDir ()
	{
		Texture2D tempTex = new Texture2D (widthHeight, widthHeight);
		Vector2 centerPixelPos = centerPosition * widthHeight;

		Vector2 curPosition = new Vector2 ();
		Vector2 pixelDir = new Vector2 ();
		Color pixelColor = new Color ();
		pixelColor.a = 1.0f;
		for (int x = 0; x < widthHeight; x++) {
			for (int y = 0; y < widthHeight; y++) {
				curPosition.x = x;
				curPosition.y = y;

				pixelDir = centerPixelPos - curPosition;
				pixelDir.Normalize ();

				float rightDir = Vector2.Dot (pixelDir, Vector3.right);
				float upDir = Vector2.Dot (pixelDir, Vector3.up);
				float forward = Vector2.Dot (pixelDir, Vector3.forward);
				pixelColor.r = rightDir;
				pixelColor.g = forward;
				pixelColor.b = upDir;

				tempTex.SetPixel (x, y, pixelColor);
			}
		}
		tempTex.Apply ();
		return tempTex;
	}

	private Texture2D GenerateAngleOfPixelDir ()
	{
		Texture2D tempTex = new Texture2D (widthHeight, widthHeight);
		Vector2 centerPixelPos = centerPosition * widthHeight;

		Vector2 curPosition = new Vector2 ();
		Vector2 pixelDir = new Vector2 ();
		Color pixelColor = new Color ();
		pixelColor.a = 1.0f;
		for (int x = 0; x < widthHeight; x++) {
			for (int y = 0; y < widthHeight; y++) {
				curPosition.x = x;
				curPosition.y = y;

				pixelDir = centerPixelPos - curPosition;
				pixelDir.Normalize ();

				float rightDir = Vector2.Angle (pixelDir, Vector3.right) / 360;
				float upDir = Vector2.Angle (pixelDir, Vector3.up) / 360;
				float forward = Vector2.Angle (pixelDir, Vector3.forward) / 360;
				pixelColor.r = rightDir;
				pixelColor.g = forward;
				pixelColor.b = upDir;

				tempTex.SetPixel (x, y, pixelColor);
			}
		}
		tempTex.Apply ();
		return tempTex;
	}
}

