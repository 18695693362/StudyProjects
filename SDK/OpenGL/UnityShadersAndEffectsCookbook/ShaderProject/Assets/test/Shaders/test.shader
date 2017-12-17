Shader "Test/test1"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma surface surf BlinnPhong

			struct Input {
				float4 color : COLOR;
			};

			void surf(Input IN, inout SurfaceOutput o) {
				o.Albedo = float3(0, 1, 0);
			}
			ENDCG
		}
	}
}
