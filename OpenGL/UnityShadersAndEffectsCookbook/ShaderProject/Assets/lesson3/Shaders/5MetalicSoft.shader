Shader "CookbookShader/lesson3/MetalicSoft" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_RoughnessTex("Roughness Tex", 2D) = "white"{}
		_Roughness("Roughness", Range(0,1)) = 0.5
		_SpecColor("Specular Color", Color) = (1,1,1,1)
		_SpecPower("Specular Power", Range(0.1,120)) = 32
		_FresnelValue("Fresnel Value",Range(0,1)) = 0.01
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf MetalicSoft

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		sampler2D _RoughnessTex;
		fixed _Roughness;
		half  _SpecPower;
		fixed _FresnelValue;

		struct Input {
			float2 uv_MainTex;
			float2 uv_RoughnessTex;
		};

		inline fixed4 LightingMetalicSoft(SurfaceOutput s,fixed3 lightDir,fixed3 viewDir,fixed atten)
		{
			float diffuse_ = dot(s.Normal,lightDir);

			float3 halfVect = normalize(lightDir + viewDir);
			float NDotL = saturate(dot(s.Normal,normalize(lightDir)));
			float NDotH_raw = dot(s.Normal,halfVect);
			float NDotH = saturate(NDotH_raw);
			float NDotV = saturate(dot(s.Normal,normalize(viewDir)));
			float VDotH = saturate(dot(halfVect,normalize(viewDir)));

			float geoEnum = 2.0 * NDotH;
			float G1 = geoEnum*NDotV/NDotH;
			float G2 = geoEnum*NDotL/NDotH;
			float G = min(1.0,min(G1,G2));

			float roughness = tex2D(_RoughnessTex,float2(NDotH_raw*0.5+0.5,_Roughness)).r;
			float fresnel = pow(1.0-VDotH,5.0);
			fresnel *= (1.0-_FresnelValue);
			fresnel += _FresnelValue;

			float spec = fresnel*G*roughness*roughness*_SpecPower;
			float3 specColor = spec*_SpecColor.rgb;

			fixed4 c;
			c.rgb = (s.Albedo * _LightColor0.rgb * diffuse_) + (_LightColor0.rgb * specColor) * atten * 2;
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;

			o.Gloss = 1.0;
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

