Shader "CookbookShader/lesson8/OptimizeMobile"
{
	Properties
	{
		_MainTex("Main Texture",2D) = "white"{}
		_NormalTex("Normal Texture",2D) = "bump"{}
		_Diffuse("Diffuse Color",Color) = (1,1,1,1)
		_SpecIntensity("Specular Intentsity",Range(0.01,1)) = 0.5
	}
	SubShader
	{
		Tags{"RenderType"="Opaque"}
		LOD 200

		CGPROGRAM
		#pragma surface surf MobileBlinnPhong exclude_path:prepass nolightmap noforwardadd halfasview

		sampler2D 	_MainTex;
		sampler2D 	_NormalTex;
		fixed4		_Diffuse;
		fixed		_SpecIntensity;

		struct Input
		{
			half2 uv_MainTex;
			//half2 uv_NormalTex;
		};

		inline fixed4 LightingMobileBlinnPhong(SurfaceOutput s,fixed3 lightDir,fixed3 halfDir, fixed atten)
		{
			fixed diff = max(0,dot(s.Normal,lightDir));
			fixed nh = max(0,dot(s.Normal,halfDir));
			fixed spec = pow(nh,s.Specular*128)*s.Gloss;

			fixed4 c; 
			c.rgb = (s.Albedo * _LightColor0.rgb * diff + _LightColor0.rgb * spec) * atten * 2;
			c.a = 0.0;
			return c;
		}

		void surf(Input IN,inout SurfaceOutput o)
		{
			fixed4 c = tex2D(_MainTex,IN.uv_MainTex);
			o.Albedo = c.rgb * _Diffuse.rgb;
			o.Gloss = c.a;
			o.Alpha = 0.0;
			o.Specular = _SpecIntensity;
			o.Normal = UnpackNormal(tex2D(_NormalTex,IN.uv_MainTex));
		}
		ENDCG
	}
	FallBack "Diffuse"
}