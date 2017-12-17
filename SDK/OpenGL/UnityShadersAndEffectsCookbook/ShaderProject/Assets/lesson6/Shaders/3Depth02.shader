Shader "CookbookShader/lesson6/Depth02" 
{
	Properties {
		_MainTint("Main Tint", Color) = (1,1,1,1)
	}
	SubShader {
		Tags { "Queue" = "Geometry" }

		LOD 200
		
		CGPROGRAM
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		fixed4 _MainTint;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			o.Albedo = _MainTint.rgb;
			o.Alpha = _MainTint.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
