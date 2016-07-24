Shader "CookbookShader/lesson7/VertexColor"
{
	Properties
	{
		_MainTint("Main Tint",Color) = (1,1,1,1)
	}

	SubShader
	{
		LOD 200

		CGPROGRAM 
		#pragma surface surf Lambert vertex:vert
		#pragma target 3.0

		float4 _MainTint;
		struct Input
		{
			float4 vertColor;
		};

		void vert(inout appdata_full v,out Input o)
		{
			// use pos as color
			//o.vertColor = v.vertex;
			o.vertColor = v.color;
		}

		void surf(Input IN, inout SurfaceOutput o)
		{
			o.Albedo = IN.vertColor.rgb * _MainTint.rgb;
		}
		ENDCG
	}
	FallBack "Diffuse"
}