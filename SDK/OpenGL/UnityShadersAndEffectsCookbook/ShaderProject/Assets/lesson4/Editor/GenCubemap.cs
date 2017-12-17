using UnityEngine;
using UnityEditor;
using System.Collections;

public class GenCubemap : ScriptableWizard
{
	public Transform renderPos;
	public Cubemap cubemap;

	[MenuItem ("CookBook/L4/Render Cubemap")]
	static void RenderCubemap ()
	{
		ScriptableWizard.DisplayWizard ("Render CubeMap", typeof(GenCubemap), "Render!");
	}

	void OnWizardCreate ()
	{
		GameObject go = new GameObject ("CubeCam", typeof(Camera));
		go.transform.position = renderPos.position;
		go.transform.rotation = Quaternion.identity;

		go.GetComponent<Camera> ().RenderToCubemap (cubemap);

		DestroyImmediate (go);
	}

	void OnWizardUpdate ()
	{
		helpString = "Select transform to render" + "from and cubemap to render into";
		if (renderPos != null && cubemap != null) {
			isValid = true;
		} else {
			isValid = false;
		}
	}
}
