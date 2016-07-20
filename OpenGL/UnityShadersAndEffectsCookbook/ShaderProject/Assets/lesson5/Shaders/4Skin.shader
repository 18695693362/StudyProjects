Shader "CookbookShader/lesson5/Skin" 
{
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_MainTex("Base Texture", 2D) = "white"{}
		_BumpMap("Bump Map",2D) ="rump"{}
		_CurvatureScale("Curverture Scale",Range(0.001, 0.09)) = 0.01
		_CurvatureAmount("Curverture Amount",Range(0, 1)) = 0.5
		_BumpBias("Normal Map Blur",Range(0,5)) = 2.0
		_BRDF("BRDF Map",2D) = "white"{}
		_FresnelValue("Fresnel Value",Range(0.01,0.3)) = 0.05
		_RimPower("Rim Power",Range(0,5)) = 2
		_RimColor("Rim Color",Color) = (1,1,1,1)
		_SpecIntensity("Specular Intensity",Range(0,1)) = 0.4
		_SpecWidth("Specular Width",Range(0,1)) = 0.2
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		#pragma surface surf Skin

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		float4 _DiffuseTint;
		sampler2D _MainTex;
		sampler2D _BumpMap;
		sampler2D _BRDF;
		float _CurvatureScale;
		float _CurvatureAmount;
		float _BumpBias;
		float _FresnelValue;
		float _RimPower;
		float4 _RimColor;
		float _SpecIntensity;
		float _SpecWidth;

		struct Input {
			float2 uv_MainTex;
			float3 worldPos;
			float3 worldNormal;
			INTERNAL_DATA
		};

		struct SurfaceOutputSkin
		{
			fixed3 Albedo;
			fixed3 Normal;
			fixed3 Emission;
			fixed3 Specular;
			fixed Gloss;
			fixed Alpha;
			float Curvature;
			fixed3 BlurredNormal;
		};
	
		inline fixed4 LightingSkin(SurfaceOutputSkin s, fixed3 lightDir, fixed3 viewDir, fixed atten)
		{
			viewDir = normalize(viewDir);
			lightDir = normalize(lightDir);
			s.Normal = normalize(s.Normal);
			float NDotL = dot(s.Normal,lightDir);
			float3 halfVec = normalize(viewDir+lightDir);

			float3 brdf = tex2D(_BRDF,float2((NDotL*0.5+0.5)*atten,s.Curvature)).rgb;
			float fresnel = saturate(pow(1-dot(viewDir,halfVec),5.0));
			fresnel += _FresnelValue * (1-fresnel);
			float rim = saturate(pow(1-dot(viewDir,s.BlurredNormal),_RimPower))*fresnel;

			float specBase = max(0,dot(s.Normal,halfVec));
			float spec = pow(specBase,s.Specular*128.0) * s.Gloss;

			fixed4 c;
			c.rgb = (s.Albedo*brdf*_LightColor0.rgb*atten) + (spec +(rim*_RimColor));
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceOutputSkin o) {
			half4 c = tex2D(_MainTex, IN.uv_MainTex);
			fixed3 normal_ = UnpackNormal(tex2D(_BumpMap,IN.uv_MainTex));
			float3 blurredNormal = UnpackNormal(tex2Dbias(_BumpMap,float4(IN.uv_MainTex,0.0,_BumpBias)));

			float curvature = length(fwidth(WorldNormalVector(IN,blurredNormal))) /
			 length(fwidth(IN.worldPos)) * _CurvatureScale;

			 o.Normal = normal_;
			 o.BlurredNormal = blurredNormal;
			 o.Albedo = c.rgb * _DiffuseTint;
			 o.Curvature = curvature;
			 o.Specular = _SpecWidth;
			 o.Gloss = _SpecIntensity;
			 o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
