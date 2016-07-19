Shader "CookbookShader/lesson2/AnimatingSprite" {
	Properties {
		_DiffuseTint("Diffuse Tint", Color) = (1,1,1,1)
		_MainTex ("Textrue", 2D) = "white" {}
		_TexWidth("Textrue width", Float) = 0
		_CellAmount("Cell Amount", Float) = 0
		_Speed("Animate Speed", Range(0.01,32)) = 12
	}
	SubShader {
		Tags { "RenderType"="Opaque" }
		LOD 200
		
		CGPROGRAM
		// Physically based Standard lighting model, and enable shadows on all light types
		#pragma surface surf Lambert

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		fixed4 _DiffuseTint;
		sampler2D _MainTex;
		float _TexWidth;
		float _CellAmount;
		float _Speed;

		struct Input {
			float2 uv_MainTex;
		};

		void surf (Input IN, inout SurfaceOutput o) {
			fixed2 spriteUV = IN.uv_MainTex;
			float cellPixelWidth = _TexWidth / _CellAmount;
			float cellUVPercentage = cellPixelWidth / _TexWidth;

			float spriteIndex = fmod(_Time.y * _Speed, _CellAmount);
			spriteIndex = ceil(spriteIndex);
			float xValue = spriteUV.x;
			xValue += spriteIndex;
			xValue *= cellUVPercentage;

			spriteUV = float2(xValue, spriteUV.y);

			half4 c = tex2D(_MainTex, spriteUV) * _DiffuseTint;
			o.Albedo = c.rgb;

			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
