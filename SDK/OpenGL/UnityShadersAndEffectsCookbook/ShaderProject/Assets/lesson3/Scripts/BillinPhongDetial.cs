using UnityEngine;
using System.Collections;
using UnityEditor;

public class BillinPhongDetial : MonoBehaviour
{
	public Vector2 lightPos = new Vector2 (-1, 1);
	public Vector2 eyePos = new Vector2 (1, 1);

	public Color testColor;
	private Vector3 realLightPos = new Vector3 ();
	private Vector3 realEyePos = new Vector3 ();
	private Vector3 objPos = new Vector3 ();
	private Vector3 reflectPos = new Vector3 ();
	private Vector3 halfVecPos = new Vector3 ();

	private float HDotN;
	private float RDotE;

	void OnEnable ()
	{
		lightPos = new Vector2 (-1, 1);
		eyePos = new Vector2 (1, 1);
	}

	void OnDrawGizmos ()
	{
		realLightPos.x = lightPos.x;
		realLightPos.y = lightPos.y;
		realEyePos.x = eyePos.x;
		realEyePos.y = eyePos.y;

		float lengthScale = 1.0f;

		// draw floor
		Gizmos.color = Color.white;
		Vector3 floor = new Vector3 (-1f, 0f, 0f);
		lengthScale = 3f;
		Gizmos.DrawLine (floor * lengthScale, -floor * lengthScale);
		Handles.Label (floor * lengthScale, "Floor");

		// draw normal
		Gizmos.color = Color.green;
		Vector3 normal = new Vector3 (0f, 2f, 0f);
		lengthScale = 2f;
		Gizmos.DrawLine (objPos * lengthScale, normal * lengthScale);
		Handles.Label (normal * lengthScale, " Normal");

		// draw light
		Gizmos.color = Color.yellow;
		Gizmos.DrawLine (objPos, realLightPos.normalized * lengthScale);
		Handles.Label (realLightPos.normalized * lengthScale, " Light");

		// draw reflect
		Gizmos.color = new Color (210f / 255f, 210f / 255f, 40f / 255f);
		reflectPos.x = -realLightPos.x;
		reflectPos.y = realLightPos.y;
		Gizmos.DrawLine (objPos, reflectPos.normalized * lengthScale);
		Handles.Label (reflectPos.normalized * lengthScale, " Reflect");

		// draw eye
		Gizmos.color = Color.blue;
		lengthScale = 1.5f;
		Gizmos.DrawLine (objPos, realEyePos.normalized * lengthScale);
		Handles.Label (realEyePos.normalized * lengthScale, " Eye");

		// draw halfVec
		Gizmos.color = Color.cyan;
		halfVecPos = realEyePos.normalized + realLightPos.normalized;
		lengthScale = 1.2f;
		Gizmos.DrawLine (objPos, halfVecPos.normalized * lengthScale);
		Handles.Label (halfVecPos.normalized * lengthScale, " HalfVec");

		// draw HDotN
		Gizmos.color = Color.magenta;
		float HDotN = Vector3.Dot (halfVecPos.normalized, normal.normalized);
		float hNAngle = Vector3.Angle (halfVecPos, normal);
		Vector3 hDotNPosBegin = new Vector3 (-3f, 1.6f, 0f);
		Vector3 hDotNPosEnd = new Vector3 (-3f, 1.6f, 0f);
		float HDotNScale = 1.0f;
		hDotNPosEnd.y += HDotN * HDotNScale;
		Gizmos.DrawLine (hDotNPosBegin, hDotNPosEnd);
		Handles.Label (hDotNPosBegin, "\n HalfVec");
		Vector3 hNAnglePos = new Vector3 (-3.5f, 1.2f, 0f);
		Handles.Label (hNAnglePos, "hNAngle: " + hNAngle.ToString ());

		// draw RDotE
		Gizmos.color = Color.red;
		float RDotE = Vector3.Dot (reflectPos.normalized, eyePos.normalized);
		float rEAngle = Vector3.Angle (reflectPos, eyePos);
		Vector3 rDotEPosBegin = new Vector3 (-3.5f, 1.6f, 0f);
		Vector3 rDotEPosEnd = new Vector3 (-3.5f, 1.6f, 0f);
		float RDotEScale = 1.0f;
		rDotEPosEnd.y += RDotE * RDotEScale;
		Gizmos.DrawLine (rDotEPosBegin, rDotEPosEnd);
		Handles.Label (rDotEPosBegin, "\nRDotE");
		Vector3 rEAnglePos = new Vector3 (-3.5f, 1.0f, 0f);
		Handles.Label (rEAnglePos, "rEAngle: " + rEAngle.ToString ());

		// draw deltaAngle
		Vector3 deltaAnglePos = new Vector3 (-3.5f, 0.8f, 0f);
		Handles.Label (deltaAnglePos, "deltaAngle: " + (rEAngle - hNAngle).ToString ());
	}
}
