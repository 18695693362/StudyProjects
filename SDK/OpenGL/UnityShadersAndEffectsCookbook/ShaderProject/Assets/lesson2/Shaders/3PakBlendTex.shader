Shader "CookbookShader/lesson2/PakBlendTex" {
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1)
		_ColorA("Terrian Color A", Color) = (1,1,1,1)
		_ColorB("Terrian Color B", Color) = (1,1,1,1)
		_RTex("Red Channel Tex",2D) = ""{}
		_GTex("Green Channel Tex",2D) = ""{}
		_BTex("Blue Channel Tex",2D) = ""{}
		_ATex("Alpha Channel Tex",2D) = ""{}
		_BlendTex("Blend Texture",2D) = ""{}
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 4.0

		float4 _DiffuseTint;
		float4 _ColorA;
		float4 _ColorB;
		sampler2D _RTex;
		sampler2D _GTex;
		sampler2D _BTex;
		sampler2D _ATex;
		sampler2D _BlendTex;

		struct Input {
			float2 uv_RTex;
			float2 uv_GTex;
			float2 uv_BTex;
			float2 uv_ATex;
			float2 uv_BlendTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			float4 blendData = tex2D(_BlendTex, IN.uv_BlendTex);
			float4 rTexData = tex2D(_RTex, IN.uv_RTex);
			float4 gTexData = tex2D(_GTex, IN.uv_GTex);
			float4 bTexData = tex2D(_BTex, IN.uv_BTex);
			float4 aTexData = tex2D(_ATex, IN.uv_ATex);

			float4 finalColor;
			finalColor = lerp(rTexData, gTexData, blendData.g);
			finalColor = lerp(finalColor, bTexData, blendData.b);
			finalColor = lerp(finalColor, aTexData, blendData.a);
			finalColor.a = 1.0;

			float4 terrianLayers = lerp(_ColorA,_ColorB,blendData.r);
			finalColor *= terrianLayers;
			finalColor = saturate(finalColor);

			o.Albedo = finalColor.rgb * _DiffuseTint.rgb;
			o.Alpha = finalColor.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
