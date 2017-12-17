Shader "CookbookShader/lesson5/VehiclePaint" 
{
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_MainTex("Base Texture", 2D) = "white"{}
		_SpecColor("Specular Color", Color) = (1,1,1,1)
		_SpecPower("Specular Power", Range(0.01,30)) = 3
		_ReflectCube("Reflect Cubemap",Cube) = ""{}
		_BRDFTex("BRDF Texture",2D) = "white"{}
		_DiffusePower("Diffuse Power",Range(0.01,10)) = 0.5
		_FalloffPower("Falloff Power",Range(0.01,30)) = 3
		_ReflectAmount("Reflect Amount",Range(0.01, 1.0)) = 0.5
		_ReflectPower("Reflect Power",Range(0.01,3.0)) = 2.0
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
//		#pragma surface surf CarPaint
		#pragma surface surf_vehicle VehiclePaint

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float3 _DiffuseTint;
		//float3 _SpecColor;
		float _SpecPower;
		samplerCUBE _ReflectCube;
		sampler2D 	_BRDFTex;
		float _DiffusePower;
		float _FalloffPower;
		float _ReflectAmount;
		float _ReflectPower;

		struct Input {
			float2 uv_MainTex;
			float3 worldRefl;
			float3 viewDir;
		};
	
		inline fixed4 LightingVehiclePaint(SurfaceOutput s, fixed3 lightDir, fixed3 viewDir, fixed atten)
		{
			half3 halfVec = normalize(viewDir + lightDir);
			fixed diff = max(0,dot(s.Normal,lightDir));

			float ahdn = 1-dot(halfVec,normalize(s.Normal));
			ahdn = pow(clamp(ahdn,0.0,1.0),_DiffusePower);
			half4 brdf = tex2D(_BRDFTex,float2(diff,1-ahdn));
			//half4 brdf = tex2D(_BRDFTex,float2(diff,diff));

			float spec = max(0,dot(halfVec,s.Normal));
			spec = pow(spec,s.Specular*_SpecPower) * s.Gloss;

			fixed4 c;
			c.rgb = (s.Albedo * _LightColor0.rgb * brdf.rgb + _LightColor0.rgb*_SpecColor.rgb*spec)*atten*2;
			c.a = s.Alpha + _LightColor0.a * _SpecColor.a * spec * atten;
			return c;
		}

		void surf_vehicle (Input IN, inout SurfaceOutput o) {
			half4 c = tex2D(_MainTex,IN.uv_MainTex);
			fixed falloff = saturate(1-dot(normalize(IN.viewDir),o.Normal));
			falloff = pow(falloff,_FalloffPower);

			o.Albedo = c.rgb * _DiffuseTint;
			o.Emission = pow((texCUBE(_ReflectCube,IN.worldRefl).rgb*falloff),_ReflectPower) * _ReflectAmount;
			o.Specular = c.r;
			o.Gloss = 1.0;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}