Shader "CookbookShader/lesson5/LitSphere" {
	Properties {
		_MainTex ("Main Tex", 2D) = "white" {}
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1) 
		_NormalMap("Normal Map", 2D) = "bump"{}
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Unlit vertex:vert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float4 _DiffuseTint;
		sampler2D _NormalMap;

		struct Input {
			float2 uv_MainTex;
			float2 uv_NormalMap;
			float3 tan1;
			float3 tan2;
		};

		void vert(inout appdata_full v, out Input o)
		{
			UNITY_INITIALIZE_OUTPUT(Input,o);
			TANGENT_SPACE_ROTATION;
			o.tan1 = mul(rotation,UNITY_MATRIX_IT_MV[0].xyz);
			o.tan2 = mul(rotation,UNITY_MATRIX_IT_MV[1].xyz);
		}

		inline fixed4 LightingUnlit(SurfaceOutput s, fixed3 lightDir, fixed atten)
		{
			fixed4 c = fixed4(1,1,1,1);
			c.rgb = c * s.Albedo;
			c.a = s.Alpha;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) {
			float3 normal_ = UnpackNormal(tex2D(_NormalMap,IN.uv_NormalMap));
			o.Normal = normal_;

			float2 litSphereUV;
			litSphereUV.x = dot(IN.tan1,o.Normal);
			litSphereUV.y = dot(IN.tan2,o.Normal);

			float4 color_ = tex2D(_MainTex,litSphereUV*0.5+0.5) * _DiffuseTint;
			o.Albedo = color_.rgb * _DiffuseTint;
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}

