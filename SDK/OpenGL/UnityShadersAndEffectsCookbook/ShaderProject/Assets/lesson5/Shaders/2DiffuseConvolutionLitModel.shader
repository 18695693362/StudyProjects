Shader "CookbookShader/lesson5/DiffuseConvolutionLitModel" {
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_NormalMap("Normal Map", 2D) = "bump"{}
		_AOMap("Ambient Occlusion Map",2D) = "white"{}
		_CubeMap("Diffuse Convolution Cubemap",Cube) = ""{}
		_SpecIntensity("Specular Intensity", Range(0,1)) = 0.5
		_SpecWidth("Specular Width",Range(0,1)) = 0.2
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf DiffuseConvolution

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _AOMap;
		float4 _DiffuseTint;
		sampler2D _NormalMap;
		samplerCUBE _CubeMap;
		fixed _SpecIntensity;
		fixed _SpecWidth;

		struct Input {
			float2 uv_AOMap;
			float worldNormal;
			INTERNAL_DATA
		};
	
		inline fixed4 LightingDiffuseConvolution(SurfaceOutput s, fixed3 lightDir, fixed3 viewDir, fixed atten)
		{
			viewDir = normalize(viewDir);
			lightDir = normalize(lightDir);
			s.Normal = normalize(s.Normal);
			float NDotL = dot(s.Normal,lightDir);
			float3 halfVec = normalize(viewDir+lightDir);
			float spec = pow(dot(s.Normal,halfVec),s.Specular*128.0) * s.Gloss;

			fixed4 c;
			c.rgb = (s.Albedo * atten) + spec;
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D(_AOMap,IN.uv_AOMap);
			float3 normal_ = UnpackNormal(tex2D(_NormalMap,IN.uv_AOMap)).rgb;
			o.Normal = normal_;

			float3 diffuse_ = texCUBE(_CubeMap,WorldNormalVector(IN, o.Normal)).rgb;

			o.Albedo = (c.rgb * diffuse_) * _DiffuseTint;
			o.Specular = _SpecWidth;
			o.Gloss = _SpecIntensity * c.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

