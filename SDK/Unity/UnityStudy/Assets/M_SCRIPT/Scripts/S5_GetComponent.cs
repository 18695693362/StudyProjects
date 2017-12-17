using UnityEngine;
using System.Collections;

public class S5_GetComponent : MonoBehaviour
{
	// Use this for initialization
	void Start ()
    {
        var obj = new GameObject();

        // 下面两种效果是一样的
        foreach ( var t in gameObject.GetComponents ( typeof ( Component ) ) )
        //foreach ( var t in this.GetComponents<Component> ( ) )
        {
            Debug.Log ( t.ToString ( ) );
        }

        var widget = GetComponent<UIWidget>();
        if ( widget != null )
        {
            Debug.Log ( "从UIImage上获取UIWidget成功 --- " + widget.ToString ( ) );
        }
        else
        {
            Debug.Log ( "从UIImage上获取UIWidget失败 " );
        }

        if (obj.transform != null)
        {
            Debug.Log ( "new出来的GameObject 会 自动附带Transform" );
        }
        else
        {
            Debug.Log ( "new出来的GameObject 不会 自动附带Transform" );
        }
	}
}
