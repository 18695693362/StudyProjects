using UnityEngine;
using System.Text;
using System.Collections;

public class DisplayRenderQueue : MonoBehaviour
{
	private Material tempMat;
	private bool isLoged = false;

	void Update ()
	{
		if (isLoged) {
			return;
		}

		isLoged = true;
		tempMat = transform.GetComponent<MeshRenderer> ().material;
		if (tempMat != null) {
			StringBuilder info = new StringBuilder ();
			info.Append ("RenderQueue = ");
			info.Append (tempMat.renderQueue.ToString ());
			info.Append (" ");

			// gameObject.name == transform.name
			//info.Append (gameObject.name);

			info.Append (transform.name);
			Debug.Log (info);
		}
	}
}
