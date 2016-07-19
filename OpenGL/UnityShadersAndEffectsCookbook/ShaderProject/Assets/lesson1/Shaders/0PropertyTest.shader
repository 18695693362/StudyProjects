Shader "CookbookShader/PropertyTest" {
	Properties {
		_EmissiveColor("Emissive Color", Color) = (1,1,1,1)
		_AmbientColor("Ambient Color", Color) = (0.5,1,1,1)
		_MyRangeValue("This is a Range", Range(0,10)) = 2.5

		_MyFloatValue("This is a Float", Float) = 1.5
		_MyColorValue("This is a ColorAmbient Color", Color) = (0.5,1,1,1)
		_MyVectorValue("This is a Vector", Vector) = (1,2,3,4)
		_My2DValue("This is a Texture 2D", 2D) = "white" {}
		_MyRectValue("This is a Texture Rect", Rect) = "white" {}
		_MyCubeValue("This is a Texture Cube", Cube) = "white" {}
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Standard fullforwardshadows

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		float4 _EmissiveColor;
		float4 _AmbientColor;
		float  _MyRangeValue;

		struct Input {
			float2 uv_MainTex;
		};

		half _Glossiness;
		half _Metallic;
		fixed4 _Color;

		void surf (Input IN, inout SurfaceOutputStandard o) {
			// Albedo comes from a texture tinted by color
			fixed4 c = pow((_EmissiveColor+_AmbientColor),_MyRangeValue);
			o.Albedo = c.rgb;
			// Metallic and smoothness come from slider variables
			o.Metallic = _Metallic;
			o.Smoothness = _Glossiness;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
