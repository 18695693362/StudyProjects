Shader "CookbookShader/lesson6/Transparency" 
{
	Properties {
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_TransVal("Transparency Value",Range(0,1)) = 0.5
		[Toggle] _EnableTrans ("Enalbe Trans  ?", Float) = 0
		[Enum(Red, 0, Green, 1, Blue, 2)] _OpaqueColor ("OpaqueColor", Float) = 0
	}
	SubShader {
		Tags { "Queue" = "Transparent" }
//		Tags {"Queue"="Transparent" "RenderType"="Transparent" "IgnoreProjector"="True"}
		ZWrite Off

		LOD 200
		
		CGPROGRAM
		#pragma surface surf Lambert alpha:fade
		//#pragma surface surf Lambert alpha
		//#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		fixed _TransVal;
		fixed _EnableTrans;
		float _OpaqueColor;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D(_MainTex,IN.uv_MainTex);
			o.Albedo = c.rgb;
			if(_EnableTrans > 0)
			{
				if(_OpaqueColor == 0)
				{
					o.Alpha = c.r * _TransVal;
				}
				else if(_OpaqueColor == 1)
				{
					o.Alpha = c.g * _TransVal;
				}
				else if(_OpaqueColor == 2)
				{
					o.Alpha = c.b * _TransVal;
				}
			}
			else
			{
				o.Alpha = 1.0;
			}
		}
		ENDCG
	}
	FallBack "Diffuse"
}
