Shader "CookbookShader/lesson9/UseInternalFunc"
{
	Properties {
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_Desaturate("Desaturate Value",Range(0,1)) = 0.5
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		#pragma surface surf Lambert

		#pragma target 3.0

		sampler2D _MainTex;
		fixed _Desaturate;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D (_MainTex, IN.uv_MainTex);
			c.rgb = lerp(c.rgb,Luminance(c.rgb),_Desaturate);
			o.Albedo = c.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
