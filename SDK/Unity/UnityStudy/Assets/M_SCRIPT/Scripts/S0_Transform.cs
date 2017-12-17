using UnityEngine;
using System.Collections;

public class S0_Transform : MonoBehaviour
{
	public enum TransformType
	{
		kMove,
		kRotate,
		kRotateAround
	}

	public TransformType transformType = TransformType.kMove;
	public Space spaceType = Space.Self;
	public Vector3 rotateAroundPoint = Vector3.zero;
	public float speed = 1.0f;

	// Vector3.right   = Vector3(1, 0, 0).
	// Vector3.up      = Vector3(0, 1, 0).
	// Vector3.forward = Vector3(0, 0, 1).

	void Start ()
	{
		Vector3 temp = Vector3.right;
		temp.x = 10;
		Debug.Log (temp.ToString ());
		Debug.Log (Vector3.right.ToString ());
	}

	// Update is called once per frame
	void Update ()
	{
		if (transformType == TransformType.kMove) {
			// Translate interface
			//public void Translate(Vector3 translation, Space relativeTo = Space.Self);
			//public void Translate(Vector3 translation, Transform relativeTo);
			//public void Translate(float x, float y, float z, Transform relativeTo);

			transform.Translate (Vector3.forward * Time.deltaTime, spaceType);
		} else if (transformType == TransformType.kRotate) {
			// Rotate interface 自转
			//public void Rotate(Vector3 eulerAngles, Space relativeTo = Space.Self);
			//public void Rotate(Vector3 axis, float angle, Space relativeTo = Space.Self);

			transform.Rotate (Vector3.right * Time.deltaTime * speed, spaceType);	
		} else if (transformType == TransformType.kRotateAround) {
			// RotateAround interface 公转
			// public void RotateAround(Vector3 point, Vector3 axis, float angle);

			transform.RotateAround (rotateAroundPoint, Vector3.up, 20 * Time.deltaTime);
		}
	}

	void OnValidate ()
	{
	}
}
