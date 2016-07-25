Shader "CookbookShader/lesson10/BSCEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_BrightnessAmount("Brightness Amount",Range(0.0,1)) = 1.0
		_SaturationAmount("Saturation Amount",Range(0.0,1)) = 1.0
		_ContrastAmount("Constrast Amount",Range(0.0,1)) = 1.0
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma vertex vert_img
			#pragma fragment frag
			#include "UnityCG.cginc"

			sampler2D _MainTex;
			fixed _BrightnessAmount;
			fixed _SaturationAmount;
			fixed _ContrastAmount;

			float3 ContrastSaturationBrightness(float3 color, float brt, float sat, float con)
			{
				float AvgLumR = 0.5;
				float AvgLumG = 0.5;
				float AvgLumB = 0.5;

				float3 LuminanceCoeff = float3(0.2125,0.7154,0.0721);

				// opt Brightness
				float3 brtColor = color * brt;

				// opt Saturation
				float intensityf = dot(brtColor,LuminanceCoeff);
				float3 intensity = float3(intensityf,intensityf,intensityf);
				float3 satColor = lerp(intensity, brtColor, sat);

				// opt Contrast
				float3 AvgLumin = float3(AvgLumR,AvgLumG,AvgLumB);
				float3 conColor = lerp(AvgLumin, satColor, con);

				return conColor;
			}

			fixed4 frag (v2f_img i) : COLOR
			{
				fixed4 col = tex2D(_MainTex, i.uv);
				col.rgb = ContrastSaturationBrightness(col.rgb,
						_BrightnessAmount,
						_SaturationAmount,
						_ContrastAmount);

				return col;
			}
			ENDCG
		}
	}
}
