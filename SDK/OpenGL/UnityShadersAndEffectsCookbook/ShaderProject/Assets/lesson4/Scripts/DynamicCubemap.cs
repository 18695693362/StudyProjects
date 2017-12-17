using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class DynamicCubemap : MonoBehaviour
{
	public Cubemap cubeMap1;
	public Cubemap cubeMap2;
	public Transform transform1;
	public Transform transform2;

	private Cubemap curCubemap;
	private Material curMat;
	private Vector3 moveStep = new Vector3 (0.03f, 0.0f, 0.0f);
	//private float moveStep = 0.3f;

	void OnDrawGizmos ()
	{
		Gizmos.color = Color.red;

		if (transform1) {
			Gizmos.DrawWireSphere (transform1.position, 0.5f);
		}
		Gizmos.color = Color.green;
		if (transform2) {
			Gizmos.DrawWireSphere (transform2.position, 0.5f);
		}
	}

	public Cubemap GetCubemap ()
	{
		float dist1 = Vector3.Distance (transform.position, transform1.position);
		float dist2 = Vector3.Distance (transform.position, transform2.position);
		if (dist1 < dist2) {
			return cubeMap1;
		} else {
			return cubeMap2;
		}
	}

	void Update ()
	{
		//curMat = GetComponent<MeshRenderer> ().material;
		curMat = GetComponent<Renderer> ().sharedMaterial;
		if (curMat) {
			Cubemap temp = GetCubemap ();
			if (temp != curCubemap) {
				curCubemap = temp;
				curMat.SetTexture ("_Cubemap", curCubemap);
			}
		}
			
		//transform.position.x += moveStep;
		transform.position += moveStep;
		if (transform.position.x > transform2.position.x) {
			moveStep = -moveStep;
		}
		if (transform.position.x < transform1.position.x) {
			moveStep = -moveStep;
		}
	}
}
