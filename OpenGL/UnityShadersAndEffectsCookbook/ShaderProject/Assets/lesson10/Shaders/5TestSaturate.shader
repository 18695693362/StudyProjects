Shader "CookbookShader/lesson10/TestSaturate"
{
	Properties
	{
		_MainColor("Main Color", Color) = (1,1,1,1)
		_SaturationAmount("Saturation Amount",Range(0.0,1)) = 1.0
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

		CGPROGRAM
		#pragma surface surf Lambert
		#pragma target 3.0

		fixed4 _MainColor;
		fixed _SaturationAmount;

		struct Input
		{
			half2 uv_MainTex;
		};

		void surf(Input IN, inout SurfaceOutput o)
		{
			fixed3 LuminanceCoeff = float3(0.2125,0.7154,0.0721);
			fixed  intensityf = dot(_MainColor.rgb,LuminanceCoeff);
			fixed3 grayColor = float3(intensityf,intensityf,intensityf);

			o.Albedo = lerp(grayColor, _MainColor.rgb, _SaturationAmount);
			o.Alpha = _MainColor.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
