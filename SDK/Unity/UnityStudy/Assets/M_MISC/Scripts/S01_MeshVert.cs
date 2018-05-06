using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S01_MeshVert : MonoBehaviour
{
    void Update()
    {
        Mesh mesh = GetComponent<MeshFilter>().mesh;
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
}