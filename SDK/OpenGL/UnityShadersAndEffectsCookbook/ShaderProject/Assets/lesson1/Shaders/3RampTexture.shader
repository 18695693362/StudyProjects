Shader "CookbookShader/lesson1/RampTexture" {
	Properties {
		_EmissiveColor("Emissive Color", Color) = (1,1,1,1)
		_AmbientColor("Ambient Color", Color) = (0.5,1,1,1)
		_MyRangeValue("This is a Range", Range(0,10)) = 2.5
		_RampTex("Ramp Texture", 2D) = "white" {}
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf RampTexture

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		float4 _EmissiveColor;
		float4 _AmbientColor;
		float  _MyRangeValue;
		sampler2D _RampTex;

		struct Input {
			float2 uv_MainTex;
		};

		inline float4 LightingRampTexture(SurfaceOutput s, fixed3 lightDir, fixed atten)
		{
			float diffuse_ = max(0, dot(s.Normal, lightDir));
			float halfLambert = diffuse_ * 0.5 + 0.5;
			float3 ramp = tex2D(_RampTex, float2(halfLambert,halfLambert)).rgb;

			float4 col;
			col.rgb = s.Albedo * _LightColor0.rgb * ramp;
			col.a = s.Alpha;
			return col;
		}

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
