Shader "CookbookShader/lesson9/UseCgInclude"
{
	Properties {
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_MyColor ("My Color", Color) = (1,1,1,1)
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		#include "MyCgInclude.cginc"
		#pragma surface surf HalfLambert

		#pragma target 3.0

		sampler2D _MainTex;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D (_MainTex, IN.uv_MainTex);
			o.Albedo = c.rgb * _MyColor.rgb;
			//o.Alpha = c.a * _MyColor.a;
			o.Alpha = c.a * _MyColor.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
