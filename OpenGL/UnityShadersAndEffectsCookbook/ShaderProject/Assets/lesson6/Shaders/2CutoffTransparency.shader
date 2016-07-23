Shader "CookbookShader/lesson6/CutoffTransparency" 
{
	Properties {
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_Cutoff("Cutoff Value",Range(0,1)) = 0.5
//		[Toggle] _EnableTrans ("Enalbe Trans  ?", Float) = 0
//		[Enum(Red, 0, Green, 1, Blue, 2)] _OpaqueColor ("OpaqueColor", Float) = 0
	}
	SubShader {
		Tags { "Queue" = "Transparent" }

		LOD 200
		
		CGPROGRAM
		#pragma surface surf Lambert alphatest:_Cutoff

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
//		fixed _Cutoff;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D(_MainTex,IN.uv_MainTex);
			o.Albedo = c.rgb;
			o.Alpha = c.r;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
