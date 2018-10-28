Shader "M_Graphic/02PassOrder3T"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
        _rValue ("RValue", float) = 0.2
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2"
        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2"
        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2"
	}
}
