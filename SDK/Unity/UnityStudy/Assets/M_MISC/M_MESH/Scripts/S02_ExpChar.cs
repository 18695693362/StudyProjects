using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class S02_ExpChar : MonoBehaviour
{
    Transform Bone_zuijiao_l;
    Transform Bone_zuijiao_r;
    Transform Bone_zuibaroot;
    public Vector3 deltaPosL = Vector3.zero;
    public Vector3 deltaPosR = Vector3.zero;
    public Vector3 deltaRotL = Vector3.zero;
    public Vector3 deltaRotR = Vector3.zero;
    public Vector3 deltaScaleL = Vector3.zero;
    public Vector3 deltaScaleR = Vector3.zero;
    public bool isUpdate = false;
    public SkinnedMeshRenderer headSMR;
    Dictionary<Transform, KeyValuePair<int, Matrix4x4>> originBindposeDict = new Dictionary<Transform, KeyValuePair<int, Matrix4x4>>();

    void Awake()
    {
        transform.localEulerAngles = new Vector3(0, 110, 0);
        var tmpMesh = Instantiate(headSMR.sharedMesh);
        headSMR.sharedMesh = tmpMesh;
        for(var i=0; i<headSMR.bones.Length; i++)
        {
            originBindposeDict.Add(headSMR.bones[i], new KeyValuePair<int, Matrix4x4>(i,headSMR.sharedMesh.bindposes[i]));
            if(headSMR.bones[i].name == "Bone_zuijiao_l")
            {
                Bone_zuijiao_l = headSMR.bones[i];
            }
            else if(headSMR.bones[i].name == "Bone_zuijiao_r")
            {
                Bone_zuijiao_r = headSMR.bones[i];
            }
            else if(headSMR.bones[i].name == "Bone_zuibaroot")
            {
                Bone_zuibaroot = headSMR.bones[i];
            }
            if(headSMR.sharedMesh.bindposes[i] != headSMR.bones[i].worldToLocalMatrix*transform.localToWorldMatrix)
            {
                Debug.Log("not equal!");
            }
        }
    }

    Vector3 _preDeltaPosL = Vector3.zero;
    Vector3 _preDeltaPosR = Vector3.zero;
	void Update()
    {
        if(isUpdate)
        {
            ChangeBone(Bone_zuijiao_l, deltaPosL, deltaRotL);
            ChangeBone(Bone_zuijiao_r, deltaPosR, deltaRotR);
            ChangeBone(Bone_zuibaroot, deltaPosL, deltaRotL);
        }
        isUpdate = false;
	}

    void ChangeBone(Transform boneTrans, Vector3 deltaPos, Vector3 deltaRot)
    {
        var bpArr = headSMR.sharedMesh.bindposes;
        KeyValuePair<int, Matrix4x4> bpInfo;
        if(originBindposeDict.TryGetValue(boneTrans, out bpInfo))
        {
            //Matrix4x4.TRS(boneTrans.localPosition, boneTrans.localRotation, boneTrans.localScale)
            //bpArr[bpInfo.Key] = boneTrans.parent.worldToLocalMatrix * boneTrans.localToWorldMatrix * bpInfo.Value;
            //bpArr[bpInfo.Key] = Matrix4x4.TRS(deltaPos, Quaternion.Euler(deltaRot), boneTrans.localScale) * bpInfo.Value;
            var posDelta = Matrix4x4.Translate(boneTrans.worldToLocalMatrix.MultiplyPoint(boneTrans.parent.TransformPoint(deltaPos)) 
                - boneTrans.worldToLocalMatrix.MultiplyPoint(boneTrans.parent.TransformPoint(Vector3.zero)));
            var rotScaleDelta = Matrix4x4.TRS(Vector3.zero, Quaternion.Euler(deltaRot), boneTrans.localScale);
            //bpArr[bpInfo.Key] = posDelta * bpInfo.Value;
            bpArr[bpInfo.Key] = posDelta * rotScaleDelta * bpInfo.Value;
            headSMR.sharedMesh.bindposes = bpArr;
        }
        else
        {
            Debug.LogWarning("not exist bone");
        }
    }
}
