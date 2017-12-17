Shader "CookbookShader/lesson3/AnisotropicSpec" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_SpecColor("Specular Color", Color) = (1,1,1,1)
		_SpecPower("Specular Power", Range(0,1)) = 0.5
		_Spec("Specular", Range(0,1)) = 0.5
		_AnisoDir("Anisotropic Dir", 2D) = ""{}
		_AnisoOffset("Anisotropic Offset",Range(-1,1)) = -0.2
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Anisotropic

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		sampler2D _AnisoDir;
		fixed _AnisoOffset;
		half  _SpecPower;
		fixed _Spec;

		struct Input {
			float2 uv_MainTex;
			float2 uv_AnisoDir;
		};

		struct SurfaceAnisoOutput
		{
			fixed3 Albedo;
			fixed3 Normal;
			fixed3 Emission;
			fixed3 SpecColor;
			float3 AnisoDir;
			fixed  	Specular;
			fixed 	Gloss;
			fixed 	Alpha;
		};

		inline fixed4 LightingAnisotropic(SurfaceAnisoOutput s,fixed3 lightDir,fixed3 viewDir,fixed atten)
		{
			float diffuse_ = dot(s.Normal,lightDir);

			float3 halfVect = normalize(lightDir + viewDir);
			float NDotL = saturate(dot(s.Normal,normalize(lightDir)));
			fixed HDotA = dot(normalize(s.Normal+s.AnisoDir),halfVect);

			//float aniso = max(0,sin(radians((HDotA+_AnisoOffset)*180)));
			float aniso = max(0,sin((HDotA+_AnisoOffset)*3.141));

			//float spec = saturate(aniso) * s.Specular;
			float spec = saturate(pow(aniso,s.Gloss*128)) * s.Specular;
			float3 specColor = spec*_SpecColor.rgb;

			fixed4 c;
			c.rgb = (s.Albedo * _LightColor0.rgb * diffuse_) + (_LightColor0.rgb * specColor) * atten * 2;
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceAnisoOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			float3 anisoTex = UnpackNormal(tex2D(_AnisoDir,IN.uv_AnisoDir));

			o.Gloss = _SpecPower;
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
			o.Specular = _Spec;
			o.AnisoDir = anisoTex;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

