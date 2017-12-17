Shader "CookbookShader/lesson4/NormalMapReflect" 
{
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_Cubemap("Cube map",Cube) = ""{}
		_ReflectAmount("Reflection Amount",Range(0.01,1)) = 0.5
		_NormalMap("Normal Map",2D) = "bump"{}
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
		sampler2D _NormalMap;
		fixed _ReflectAmount;

		struct Input {
			float2 uv_MainTex;
			float2 uv_NormalMap;
			float3 worldRefl;
			INTERNAL_DATA
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			float3 normal_ = UnpackNormal(tex2D(_NormalMap,IN.uv_NormalMap)).rgb;
			o.Normal = normal_;
			float3 reflection = texCUBE(_Cubemap,WorldReflectionVector(IN,o.Normal)).rgb;

			o.Emission = reflection * _ReflectAmount;
			o.Albedo = color_.rgb * _DiffuseTint;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}