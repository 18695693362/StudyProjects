Shader "CookbookShader/lesson4/FresnelReflect" 
{
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_Cubemap("Cube map",Cube) = ""{}
		_ReflectAmount("Reflection Amount",Range(0.01,1)) = 0.5
		_RimPower("Fresnel Falloff",Range(0.1,3)) = 2
		_SpecColor("Specular Color",Color) = (1,1,1,1)
		_SpecPower("Specular Power",Range(0,1)) = 0.5
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf BlinnPhong

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		samplerCUBE _Cubemap;
		fixed _ReflectAmount;
		half  _RimPower;
		//float4 _SpecColor;
		fixed  _SpecPower;

		struct Input {
			float2 uv_MainTex;
			float3 worldRefl;
			float3 viewDir;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			float rim = 1.0 - saturate(dot(o.Normal,normalize(IN.viewDir)));
			rim = pow(rim,_RimPower);

			o.Albedo = color_.rgb * _DiffuseTint.rgb;
			o.Emission = (texCUBE(_Cubemap,IN.worldRefl).rgb * _ReflectAmount)*rim;
			o.Specular = _SpecPower;
			o.Gloss = 1.0;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
