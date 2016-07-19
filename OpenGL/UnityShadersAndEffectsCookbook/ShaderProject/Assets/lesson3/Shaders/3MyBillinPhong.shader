Shader "CookbookShader/lesson3/MyBillinPhong" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_SpecColor("Specular Color", Color) = (1,1,1,1)
		_SpecPower("Specular Power", Range(0.1,120)) = 32
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf MyBillinPhong

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		//float4 _SpecColor;
		fixed _SpecPower;

		struct Input {
			float2 uv_MainTex;
		};

		inline fixed4 LightingMyBillinPhong(SurfaceOutput s,fixed3 lightDir,fixed3 viewDir,fixed atten)
		{
			float diffuse_ = dot(s.Normal,lightDir);

			float3 halfVect = normalize(lightDir + viewDir);
			float spec = pow(max(0,dot(halfVect,s.Normal)),_SpecPower);
			float4 specColor = _SpecColor*spec;

			fixed4 c;
			c.rgb = (s.Albedo * _LightColor0.rgb * diffuse_) + (_LightColor0.rgb * specColor) * atten * 2;
			c.a = 1.0;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex) * _DiffuseTint;
			o.Specular = _SpecPower;
			o.Gloss = 1.0;
			o.Albedo = color_.rgb;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

