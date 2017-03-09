using UnityEngine;
using System.Collections;

public class S4_ResourceLoad : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        // 下面的方式会报错
        //var cube = Resources.Load("Cube") as GameObject;

        var cube = Instantiate(Resources.Load("Cube")) as GameObject;
        cube.transform.SetParent ( transform );
	}
}
