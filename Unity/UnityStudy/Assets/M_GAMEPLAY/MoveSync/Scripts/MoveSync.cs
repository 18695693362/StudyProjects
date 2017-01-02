using UnityEngine;
using System.Collections;

public class MoveSync : MonoBehaviour {
    public GameObject clientGObj;
    public GameObject serverGObj;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}

public class MoveInfo
{
    Vector2 velocity;
    Vector2 position;
    Vector2 acceleration;
    Time time;
}

public class Sender
{
}