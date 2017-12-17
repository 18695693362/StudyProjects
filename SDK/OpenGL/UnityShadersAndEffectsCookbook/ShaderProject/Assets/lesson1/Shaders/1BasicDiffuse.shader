﻿Shader "CookbookShader/lesson1/BasicDiffuse" {
	Properties {
		_EmissiveColor("Emissive Color", Color) = (1,1,1,1)
		_AmbientColor("Ambient Color", Color) = (0.5,1,1,1)
		_MyRangeValue("This is a Range", Range(0,10)) = 2.5
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf BasicDiffuse

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		inline float4 LightingBasicDiffuse(SurfaceOutput s, fixed3 lightDir, fixed atten)
		{
			float difLight = max(0, dot(s.Normal, lightDir));

			float4 col;
			col.rgb = s.Albedo * _LightColor0.rgb * (difLight*atten*2);
			col.a = s.Alpha;
			return col;
		}

		float4 _EmissiveColor;
		float4 _AmbientColor;
		float  _MyRangeValue;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			// Albedo comes from a texture tinted by color
			fixed4 c = pow((_EmissiveColor+_AmbientColor),_MyRangeValue);
			o.Albedo = c.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
