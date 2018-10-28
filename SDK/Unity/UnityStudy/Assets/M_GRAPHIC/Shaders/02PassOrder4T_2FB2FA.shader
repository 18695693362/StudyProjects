Shader "M_Graphic/02PassOrder4T_2FB2FA"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
        _rValue ("RValue", float) = 0.2
        _bValue ("BValue", float) = 0.2
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2ForwardBase"
        UsePass "M_Graphic/02PassOrderHelper/DrawBZP2ForwardBase"
        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2ForwardAdd"
        UsePass "M_Graphic/02PassOrderHelper/DrawRZP2ForwardAdd"
	}
}
