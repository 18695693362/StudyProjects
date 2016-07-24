Shader "CookbookShader/lesson7/VertexAnim"
{
	Properties
	{
		_MainTex("Main Texture",2D) = "white"{}
		_MainTint("Main Tint",Color) = (1,1,1,1)
		_TintAmount("Tint Amount",Range(0,1)) = 0.5
		_ColorA("Color A",Color) = (1,1,1,1)
		_ColorB("Color B",Color) = (1,1,1,1)
		_Speed("Wave Speed",Range(0.1,80)) = 5
		_Frequency("Wave Frequency",Range(0,5)) = 2
		_Amplitude("Wave Amplitude",Range(-1,1)) = 1
	}

	SubShader
	{
		LOD 200

		CGPROGRAM 
		#pragma surface surf Lambert vertex:vert
		#pragma target 3.0

		sampler2D 	_MainTex;
		fixed4 		_MainTint;
		fixed		_TintAmount;
		fixed4 		_ColorA;
		fixed4 		_ColorB;
		float 		_Speed;
		half		_Frequency;
		fixed		_Amplitude;

		struct Input
		{
			float2 uv_MainTex;
			float3 vertColor;
		};

		void vert(inout appdata_full v,out Input o)
		{
			UNITY_INITIALIZE_OUTPUT(Input,o); 
			float time = _Time.x * _Speed;
			float waveValueA = sin(time + v.vertex.x * _Frequency) * _Amplitude;
			v.vertex.xyz = float3(v.vertex.x,v.vertex.y+waveValueA,v.vertex.z);
			v.normal = normalize(float3(v.normal.x+waveValueA,v.normal.y,v.normal.z));
			o.vertColor = float3(waveValueA,waveValueA,waveValueA);
		}

		void surf(Input IN, inout SurfaceOutput o)
		{
			half4 c = tex2D(_MainTex,IN.uv_MainTex);
			float3 color_ = lerp(_ColorA,_ColorB,IN.vertColor).rgb;

			o.Albedo = c.rgb * (color_*_TintAmount);
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}