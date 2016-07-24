Shader "CookbookShader/lesson9/GrayScreenEF"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_LuminosityAmount("GrayScale Amount",Range(0.0,1)) = 1.0
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
			#pragma fragmentoption ARB_precision_hint_fastest
			#include "UnityCG.cginc"

			uniform sampler2D _MainTex;
			fixed _LuminosityAmount;

			fixed4 frag (v2f_img i) : Color
			{
				fixed4 col = tex2D(_MainTex, i.uv);

				float luminosity = 0.299 * col.r + 0.587 * col.g + 0.114 * col.b;
				fixed4 finalColor = lerp(col,luminosity,_LuminosityAmount);
				return finalColor;
			}
			ENDCG
		}
	}
}
