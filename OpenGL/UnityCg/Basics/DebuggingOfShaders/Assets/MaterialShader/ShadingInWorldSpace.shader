Shader "Cg ShadingInWorldSpace" {
	SubShader {
		Pass {
			CGPROGRAM
			
			#pragma vertex vert
			#pragma fragment frag
			
			struct vertexInput {
				float4 vertex : POSITION;
			};
			
			struct vertexOutput {
				float4 pos : SV_POSITION;
				float4 position_in_world_space : TEXCOORD0;
			};
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput output;
				
				output.pos = mul(UNITY_MATRIX_MVP, input.vertex);
				output.position_in_world_space = mul(_Object2World, input.vertex);
				return output;
			}
			
			float4 frag(vertexOutput input) : COLOR
			{
				float dist = distance(input.position_in_world_space,float4(0.0,0.0,0.0,1.0));
				if(dist < 5.0)
				{
					return float4(0.0,0.5,0.0,0.8);
				}
				else
				{
					return float4(0.3,0.3,0.8,1.0);
				}
			}
			
			ENDCG
		}
	}
}
