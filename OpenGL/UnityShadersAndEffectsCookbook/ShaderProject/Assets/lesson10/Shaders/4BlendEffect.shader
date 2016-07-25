Shader "CookbookShader/lesson9/BlendEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_BlendTex("Blend Texture",2D) = "white"{}
		_BlendFactor("Blend Factor",Range(0,1)) = 1
		[Enum(Multiply, 0, Add, 1, Screen, 2, Overlay 3)]_BlendType("Blend Type",Float) = 0
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
			uniform sampler2D _BlendTex;
			fixed _BlendFactor;
			half  _BlendType;

			fixed OverlayBlendMode(fixed basePixel, fixed blendPixel)
			{
				if(basePixel < 0.5)
				{
					return (2.0 * basePixel * blendPixel);
				}
				else
				{
					return (1.0 - 2.0 * (1.0 - basePixel) * (1.0 - blendPixel));
				}
			}
			
			fixed4 frag (v2f_img i) : COLOR
			{
				fixed4 col = tex2D(_MainTex, i.uv);
				fixed4 blendColor = tex2D(_BlendTex,i.uv);

				half4 blendedColor;
				if(_BlendType == 0)
				{
					blendedColor = col * blendColor;
				}
				else if(_BlendType == 1)
				{
					blendedColor = col + blendColor;
				}
				else if(_BlendType == 2)
				{
					blendedColor = 1.0 - ((1.0 - col) * (1.0 - blendColor));
				}
				else if(_BlendType == 3)
				{
					blendedColor.r = OverlayBlendMode(col.r,blendColor.r);
					blendedColor.g = OverlayBlendMode(col.g,blendColor.g);
					blendedColor.b = OverlayBlendMode(col.b,blendColor.b);
				}
				col = lerp(col, blendedColor, _BlendFactor);
				return col;
			}
			ENDCG
		}
	}
}
