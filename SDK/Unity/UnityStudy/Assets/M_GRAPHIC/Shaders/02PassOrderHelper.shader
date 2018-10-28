Shader "M_Graphic/02PassOrderHelper"
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

		Pass
		{
            Name "DrawRZP2"
            Blend One One
			CGPROGRAM
            #include "02PassOrderHelper.cginc"
			#pragma vertex vert
			#pragma fragment frag
			ENDCG
		}

        Pass
		{
            Name "DrawRZP2ForwardBase"
            Tags{"LightMode"="ForwardBase"}
            Blend One One
			CGPROGRAM
            #include "02PassOrderHelper.cginc"
			#pragma vertex vert
			#pragma fragment frag
			ENDCG
		}

        Pass
		{
            Name "DrawBZP2ForwardBase"
            Tags{"LightMode"="ForwardBase"}
            Blend One One
			CGPROGRAM
            #include "02PassOrderHelper.cginc"
			#pragma vertex vert
			#pragma fragment frag
			ENDCG
		}

        Pass
		{
            Name "DrawRZP2ForwardAdd"
            Tags{"LightMode"="ForwardAdd"}
            Blend One One
			CGPROGRAM
            #include "02PassOrderHelper.cginc"
			#pragma vertex vert
			#pragma fragment frag
			ENDCG
		}

        Pass
		{
            Name "DrawRZP2Deferred"
            Tags{"LightMode"="Deferred"}
            Blend One One
			CGPROGRAM
            #include "02PassOrderHelper.cginc"
			#pragma vertex vert
			#pragma fragment frag
			ENDCG
		}
	}
}
