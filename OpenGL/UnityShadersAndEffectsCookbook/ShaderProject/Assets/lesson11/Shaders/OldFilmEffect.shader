Shader "CookbookShader/lesson11/OldFilmEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_VignetteTex("Vignette Texture", 2D) = "white" {}
		_ScratchesTex("Scratches Texture", 2D) = "white" {}
		_DustTex("Dust Texture", 2D) = "white" {}
		_SepiaColor("Sepia Color", Color) = (1,1,1,1)
		_EffectAmount("Effect Amount",Range(0,1)) = 0.5
		_VignetteAmount("Vignette Amount",Range(0,1)) = 0.5
		_ScratchesXSpeed("Scratches X Speed",Float) = 10
		_ScratchesYSpeed("Scratches Y Speed",Float) = 10
		_DustXSpeed("Dust X Speed",Float) = 10
		_DustYSpeed("Dust Y Speed",Float) = 10
		_RandomValue("Random Value",Float) = 1.0
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

			sampler2D _MainTex;
			sampler2D _VignetteTex;
			sampler2D _ScratchesTex;
			sampler2D _DustTex;
			fixed4 _SepiaColor;
			fixed _EffectAmount;
			fixed _VignetteAmount;
			half  _ScratchesXSpeed;
			half  _ScratchesYSpeed;
			half  _DustXSpeed;
			half  _DustYSpeed;
			half  _RandomValue;
			
			fixed4 frag (v2f_img i) : Color
			{
				half2  mainUV = half2(i.uv.x, i.uv.y+(_RandomValue*_SinTime.z*0.005));
				fixed4 col = tex2D(_MainTex, mainUV);
				fixed4 vignetteColor = tex2D(_VignetteTex,i.uv);

				half2 scratchesUV = half2(i.uv.x + (_RandomValue*_SinTime.z*_ScratchesXSpeed),
					i.uv.y + (_Time.x * _ScratchesYSpeed));

				fixed4 scratchesColor = tex2D(_ScratchesTex,scratchesUV);

				half2 dustUV = half2(i.uv.x + (_RandomValue*_SinTime.z*_DustXSpeed),
					i.uv.y + (_RandomValue*_SinTime.z*_DustYSpeed));
				fixed4 dustColor = tex2D(_DustTex,dustUV);

				fixed lum = dot(fixed3(0.299,0.587,0.114),col.rgb);
				fixed4 finalColor = lum + lerp(_SepiaColor,_SepiaColor+fixed4(0.1,0.1,0.1,1),_RandomValue);

				fixed3 constWhiteColor = fixed3(1,1,1);
				finalColor = lerp(finalColor,finalColor*vignetteColor,_VignetteAmount);
				finalColor.rgb *= lerp(scratchesColor.rgb,constWhiteColor,_RandomValue);
				finalColor.rgb *= lerp(dustColor.rgb,constWhiteColor,_RandomValue*_SinTime.z);
				finalColor = lerp(col,finalColor,_EffectAmount);
				return finalColor;
			}
			ENDCG
		}
	}
}
