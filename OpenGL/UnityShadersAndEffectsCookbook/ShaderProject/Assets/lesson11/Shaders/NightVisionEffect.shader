Shader "CookbookShader/lesson11/NightVisionEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_VignetteTex("Vignette Tex",2D) = "white" {}
		_ScanLineTex("Scan Line Tex",2D) = "white" {}
		_NoiseTex("Nosie Tex",2D) = "white" {}
		_NoiseXSpeed("Noise X Speed",Float) = 100
		_NoiseYSpeed("Noise Y Speed",Float) = 100
		_ScanLineTileAmount("Scan Line Tile Amount",Float) = 4.0
		_NightVisionColor("NightVisionColor",Color) = (1,1,1,1)
		_Contrast("Constrast",Range(0,4)) = 2
		_Brightness("Brightness",Range(0,2)) = 1
		_RandomValue("Random Value",Range(0,1)) = 1
		_Distortion("Distortion",Float) = 0.2
		_Scale("Scale (Zoom)",Float) = 0.8
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
			uniform sampler2D _VignetteTex;
			uniform sampler2D _ScanLineTex;
			uniform sampler2D _NoiseTex;
			half _NoiseXSpeed;
			half _NoiseYSpeed;
			half _ScanLineTileAmount;
			fixed4 	_NightVisionColor;
			half 	_Contrast;
			fixed 	_Brightness;
			fixed 	_RandomValue;
			half	_Distortion;
			half 	_Scale;

			float2 BarrelDistortion(float2 coord)
			{
				float2 h = coord.xy - float2(0.5,0.5);
				float r2 = h.x * h.x + h.y * h.y;
				float f = 1.0 + r2 * (_Distortion * sqrt(r2));
				return f * _Scale * h + 0.5;
			}
			
			fixed4 frag (v2f_img i) : Color
			{
				half2 distortedUV = BarrelDistortion(i.uv);
				fixed4 color_ = tex2D(_MainTex, distortedUV);
				fixed4 vignetteColor = tex2D(_VignetteTex, i.uv);

				half2 scanLineUV = half2(i.uv.x*_ScanLineTileAmount, i.uv.y * _ScanLineTileAmount);
				fixed4 scanLineColor = tex2D(_ScanLineTex, scanLineUV);

				half2 noiseUV = half2(i.uv.x+(_RandomValue*_NoiseXSpeed*_SinTime.z),
					i.uv.y+(_RandomValue*_NoiseYSpeed*_SinTime.z));
				fixed4 noiseColor = tex2D(_NoiseTex,noiseUV);

				fixed luminosity = dot(color_.rgb, fixed3(0.299,0.587,0.114));
				luminosity += _Brightness;

				fixed4 finalColor = luminosity * 2.0 + _NightVisionColor;
				finalColor = pow(finalColor, _Contrast);
				finalColor *= vignetteColor * scanLineColor * noiseColor;

				return finalColor;
			}
			ENDCG
		}
	}
}
