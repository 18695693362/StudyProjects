Shader "CookbookShader/lesson2/PhotoshopLevel" {
	Properties {
		_MainTex ("Main Tex", 2D) = "black" {}
		_inBlack("Input Black", Range(0,255)) = 0
		_inGamma("Input Gamma", Range(0,2)) = 1.61
		_inWhite("Input White", Range(0,255)) = 255

		_outWhite("Output White",Range(0,255)) = 255
		_outBlack("Output Black",Range(0,255)) = 0 
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		sampler2D _MainTex;
		float _inBlack;
		float _inGamma;
		float _inWhite;
		float _outWhite;
		float _outBlack;

		float GetPixelLevel(float pixelColor)
		{
			float resultColor = pixelColor*255;
			resultColor = max(0, resultColor-_inBlack);
			resultColor = saturate(pow(resultColor/(_inWhite-_inBlack),_inGamma));
			resultColor = (resultColor * (_outWhite - _outBlack)+_outBlack) / 255.0;
			return resultColor;
		}

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 color_ = tex2D(_MainTex,IN.uv_MainTex);
			float outRPixel = GetPixelLevel(color_.r);
			float outGPixel = GetPixelLevel(color_.g);
			float outBPixel = GetPixelLevel(color_.b);

			o.Albedo = float3(outRPixel,outGPixel,outBPixel);
			o.Alpha = color_.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
