Shader "CookbookShader/lesson2/ProceduralTexture" {
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1)
		_MainTex ("Main Tex", 2D) = "black" {}
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		fixed4 _DiffuseTint;
		sampler2D _MainTex;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex);
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
