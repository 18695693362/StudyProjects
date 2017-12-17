Shader "CookbookShader/lesson5/Cloth" 
{
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_MainTex("Base Texture", 2D) = "white"{}
		_BumpMap("Bump Map",2D) ="rump"{}
		_BumpDetialMap("Bump detial Map",2D)="rump"{}
		_FresnelColor("Fresnel Color",Color)=(1,1,1,1)
		_FresnelPower("Fresnel Value",Range(0,12)) = 3
		_RimPower("Rim Power",Range(0,12)) = 3
		_SpecIntensity("Specular Intensity",Range(0,1)) = 0.4
		_SpecWidth("Specular Width",Range(0,1)) = 0.2
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		#pragma surface surf Cloth

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		float4 _DiffuseTint;
		sampler2D _MainTex;
		sampler2D _BumpMap;
		sampler2D _BumpDetialMap;
		float4 _FresnelColor;
		float  _FresnelPower;
		float  _RimPower;
		float  _SpecIntensity;
		float  _SpecWidth;

		struct Input {
			float2 uv_MainTex;
			float2 uv_BumpDetialMap;
			float2 uv_BumpMap;
		};
	
		inline fixed4 LightingCloth(SurfaceOutput s, fixed3 lightDir, fixed3 viewDir, fixed atten)
		{
			viewDir = normalize(viewDir);
			lightDir = normalize(lightDir);
			half3 halfVec = normalize(viewDir+lightDir);
			float NDotL = max(0,dot(s.Normal,lightDir));

			float NDotH = max(0,dot(s.Normal,halfVec));
			float spec = pow(NDotH,s.Specular*128.0)*s.Gloss;

			float HDotV = pow(1-max(0,dot(halfVec,viewDir)),_FresnelPower);
			float NDotV = pow(1-max(0,dot(s.Normal,viewDir)),_RimPower);
			float finalSpecMask = HDotV * NDotV;

			fixed4 c;
			c.rgb = (s.Albedo * NDotL * _LightColor0.rgb) + 
				(spec * (finalSpecMask * _FresnelColor) * atten * 2);
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) 
		{
			half4 c = tex2D(_MainTex,IN.uv_MainTex);
			float3 normal_ = UnpackNormal(tex2D(_BumpMap,IN.uv_BumpMap)).rgb;
			float3 detialNormal = UnpackNormal(tex2D(_BumpDetialMap,IN.uv_BumpDetialMap)).rgb;
			fixed3 finalNormal = float3(normal_.x+detialNormal.x,
				normal_.y+detialNormal.y,
				normal_.z+detialNormal.z);
			o.Normal = normalize(finalNormal);
			o.Specular = _SpecWidth;
			o.Gloss = _SpecIntensity;
			o.Albedo = c.rgb*_DiffuseTint;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
