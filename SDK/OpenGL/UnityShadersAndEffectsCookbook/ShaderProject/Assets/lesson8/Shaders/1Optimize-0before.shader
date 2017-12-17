Shader "CookbookShader/lesson8/OptimizeBefore"
{
	Properties
	{
		_MainTex("Main Texture",2D) = "white"{}
		_NormalTex("Normal Texture",2D) = "ramp"{}
	}
	SubShader
	{
		Tags{"RenderType"="Opaque"}
		LOD 200

		CGPROGRAM
		#pragma surface surf SimpleLambert

		sampler2D _MainTex;
		sampler2D _NormalTex;

		struct Input
		{
			float2 uv_MainTex;
			float2 uv_NormalTex;
		};

		inline float4 LightingSimpleLambert(SurfaceOutput s,float3 lightDir,float3 viewDir, float atten)
		{
			float diff = max(0,dot(s.Normal,lightDir));

			float4 c; 
			c.rgb = s.Albedo * _LightColor0.rgb * (diff * atten * 2);
			c.a = s.Alpha;
			return c;
		}

		void surf(Input IN,inout SurfaceOutput o)
		{
			float4 c = tex2D(_MainTex,IN.uv_MainTex);
			o.Albedo = c.rgb;
			o.Alpha = c.a;
			o.Normal = UnpackNormal(tex2D(_NormalTex,IN.uv_NormalTex));
		}
		ENDCG
	}
	FallBack "Diffuse"
}