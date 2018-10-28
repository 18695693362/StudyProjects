using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S03_ChangeSharedMesh : MonoBehaviour {

    public GameObject cubePrefab;
    private Mesh originMesh;
    private Mesh gObj1Mesh;
    private Mesh gObj2Mesh;
    private Mesh mesh;

	// Use this for initialization
	void Start ()
    {
        var gObj1 = Instantiate<GameObject>(cubePrefab, transform);
        var gObj2 = Instantiate<GameObject>(cubePrefab, transform);
        gObj2.transform.localPosition += new Vector3(2, 0, 0);

        originMesh = gObj1.GetComponent<MeshFilter>().mesh;
        gObj1Mesh = gObj1.GetComponent<MeshFilter>().sharedMesh;
        gObj2Mesh = gObj2.GetComponent<MeshFilter>().sharedMesh;
        Debug.Log("gObj1Mesh==gObj2Mesh is " + (gObj1Mesh == gObj2Mesh));

        gObj1Mesh = gObj1.GetComponent<MeshFilter>().mesh;
        mesh = gObj1Mesh;

        GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
    }
	
	void Update ()
    {
        if (mesh == null) return;
        Vector3[] vertices = mesh.vertices;
        Vector3[] normals = mesh.normals;
        int i = 0;
        while (i < vertices.Length)
        {
            vertices[i] += normals[i] * Mathf.Sin(Time.time) * 0.1f;
            i++;
        }
        mesh.vertices = vertices;
	}

    private void OnDestroy()
    {
        if (mesh == null) return;
        mesh = originMesh;
    }
}
