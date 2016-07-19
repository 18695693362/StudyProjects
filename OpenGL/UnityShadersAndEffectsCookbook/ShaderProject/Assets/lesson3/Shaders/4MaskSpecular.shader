Shader "CookbookShader/lesson3/MyMaskSpec" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_SpecMask("Specular Mask", 2D) = "white"{}
		_SpecColor("Specular Color", Color) = (1,1,1,1)
		_SpecPower("Specular Power", Range(0.1,120)) = 32
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf MyMaskSpec

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		//float4 _SpecColor;
		sampler2D _SpecMask;
		fixed _SpecPower;

		struct Input {
			float2 uv_MainTex;
			float2 uv_SpecMask;
		};

		struct SurfaceCustomOutput
		{
			fixed3 Albedo;
			fixed3 Normal;
			fixed3 Emission;
			fixed3 SpecColor;
			half  	Spec;
			fixed 	Gloss;
			fixed 	Alpha;
		};

		inline fixed4 LightingMyMaskSpec(SurfaceCustomOutput s,fixed3 lightDir,fixed3 viewDir,fixed atten)
		{
			float diffuse_ = dot(s.Normal,lightDir);

			float3 halfVect = normalize(lightDir + viewDir);
			float spec = pow(max(0,dot(halfVect,s.Normal)),_SpecPower) * s.Spec;
			float3 specColor = s.SpecColor*spec*_SpecColor.rgb;

			fixed4 c;
			c.rgb = (s.Albedo * _LightColor0.rgb * diffuse_) + (_LightColor0.rgb * specColor) * atten * 2;
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceCustomOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			float4 specMask = tex2D(_SpecMask,IN.uv_SpecMask) * _SpecColor;

			o.Gloss = 1.0;
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
			o.Spec = specMask.r;
			o.SpecColor = specMask.rgb;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

