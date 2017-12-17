Shader "CookbookShader/lesson6/GUITransparency" 
{
	Properties {
		_GUITint("GUI Tint", Color) = (1,1,1,1)
		_GUITex("GUI Texture", 2D) = "white"{}
		_FadeValue("Fade Value", Range(0,1)) = 1
	}
	SubShader {
		Tags { "Queue" = "Transparent" "RenderType" = "Transparency" "IgnoreProjector" = "True" }
		ZWrite Off
		Cull Back
		LOD 200
		
		CGPROGRAM
		#pragma surface surf UnlitGUI alpha novertexlights

		// Use shader model 3.0 target, to get nicer looking lighting
		#pragma target 3.0

		fixed4 		_GUITint;
		sampler2D 	_GUITex;
		fixed		_FadeValue;

		struct Input {
			float2 uv_GUITex;
		};

		inline fixed4 LightingUnlitGUI(SurfaceOutput s,fixed lightDir, fixed viewDir, fixed atten)
		{
			fixed4 c;
			c.rgb = s.Albedo;
			c.a = s.Alpha;
			return c;
		}

		void surf (Input IN, inout SurfaceOutput o) {
			half4 texColor = tex2D(_GUITex,IN.uv_GUITex);
			o.Albedo = _GUITint.rgb*texColor.rgb;
			o.Alpha = _GUITint.a*texColor.a*_FadeValue;
		}
		ENDCG
	}
	FallBack "Diffuse"
}