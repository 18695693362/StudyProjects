using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S0_TransformTest : MonoBehaviour
{
    public Quaternion localRot;
    public Vector3 localRotToLocalEuler;
    public Vector3 localEuler;
    public Transform testNode1;
    public Transform testNode2;

    // Use this for initialization
    void Start ()
    {
        Vector3 pos = new Vector3(10, 5, 20);
        testNode1 = (Transform)GGameObject.Find(transform, "GObj1", typeof(Transform), true);
        testNode1.localPosition = pos;
        testNode2 = (Transform)GGameObject.Find(transform, "GObj2", typeof(Transform), true);
        testNode2.localPosition = pos;

        Vector3 newPos1 = Matrix4x4.TRS(new Vector3(5, 10, -5), Quaternion.Euler(45, 45, 45), Vector3.one).MultiplyPoint(pos);
        Vector3 newPos2 = (Matrix4x4.Translate(new Vector3(5, 10, -5)) * Matrix4x4.Rotate(Quaternion.Euler(45, 45, 45))).MultiplyPoint(pos);
        Debug.Log("newPos1==newPos2 " + (newPos1 == newPos2));

        Vector3 newPos3 = Quaternion.Euler(0, 0, 30) * pos;
        Debug.Log("newPos3 = " + newPos3);

        testNode1.localRotation = Quaternion.Euler(15, 10, 40);
        testNode2.rotation = transform.rotation * Quaternion.Euler(15, 10, 40);
        Debug.Log("1 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True

        testNode1.rotation = transform.rotation * Quaternion.Euler(25, 20, 50);
        testNode2.localRotation = Quaternion.Inverse(transform.rotation) * testNode1.rotation;
        Debug.Log("2 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True

        testNode1.localRotation *= Quaternion.Euler(15, 10, 40);
        testNode2.rotation *= Quaternion.Euler(15, 10, 40);
        Debug.Log("3 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True

        Debug.Log("localEulerAngles = " + testNode1.localEulerAngles);
        Debug.Log("eulerAngles = " + testNode1.eulerAngles);
        testNode1.localRotation *= Quaternion.Euler(0, 0, 10);
        testNode2.rotation *= Quaternion.Euler(0, 0, 10);
        Debug.Log("4 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True
        Debug.Log("z+10 localEulerAngles = " + testNode1.localEulerAngles);
        Debug.Log("z+10 eulerAngles = " + testNode1.eulerAngles);
        testNode1.localRotation *= Quaternion.Euler(5, 0, 0);
        testNode2.rotation *= Quaternion.Euler(5, 0, 0);
        Debug.Log("6 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True
        Debug.Log("x+5 localEulerAngles = " + testNode1.localEulerAngles);
        Debug.Log("x+5 eulerAngles = " + testNode1.eulerAngles);
        testNode1.localRotation *= Quaternion.Euler(0, 6, 0);
        testNode2.rotation *= Quaternion.Euler(0, 6, 0);
        Debug.Log("7 testNode1.rotation == testNode2.rotation " + (testNode1.rotation == testNode2.rotation)); // print True
        Debug.Log("y+6 localEulerAngles = " + testNode1.localEulerAngles);
        Debug.Log("y+6 eulerAngles = " + testNode1.eulerAngles);
    }
}
