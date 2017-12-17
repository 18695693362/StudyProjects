Shader "CookbookShader/lesson2/NormalMapping" {
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1)
		_NormalTex ("Normal Tex", 2D) = "bump" {}
		_NormalIntensity("Normal Map Intensity",Range(0,2)) = 1
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
		sampler2D _NormalTex;
		float _NormalIntensity;

		struct Input {
			float2 uv_NormalTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float3 normalVec = UnpackNormal(tex2D(_NormalTex,IN.uv_NormalTex));
			normalVec = float3(normalVec.x*_NormalIntensity,normalVec.y*_NormalIntensity,normalVec.z);
			o.Normal = normalVec.rgb;
			o.Albedo = _DiffuseTint.rgb;
			o.Alpha = _DiffuseTint.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
