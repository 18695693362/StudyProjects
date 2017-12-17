Shader "CookbookShader/lesson4/SimpleCubemap" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_Cubemap("Cube map",Cube) = ""{}
		_ReflectAmount("Reflection Amount",Range(0.01,1)) = 0.5
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		samplerCUBE _Cubemap;
		fixed _ReflectAmount;

		struct Input {
			float2 uv_MainTex;
			//float3 worldReflect;
			float3 worldRefl;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			o.Emission = texCUBE(_Cubemap,IN.worldRefl).rgb * _ReflectAmount;
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

