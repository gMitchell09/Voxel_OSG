Shader "Unlit/GridShader"
{
   Properties
   {
      _MainColor("Main Color", Color) = (0.5, 1.0, 1.0)
      _SecondaryColor("Secondary Color", Color) = (0.0, 0.0, 0.0)

      [Header(Grid)]
	  _GridSize("Major Grid Spacing", Range(0.0001, 100000)) = 100
      _Thickness("Lines Thickness", Range(0.0001, 10)) = 0.3
      _GridSizeSecondary("Minor Grid Spacing", Range(0.0001, 100)) = 10.0
      _SecondaryThickness("Lines Thickness (secondary)", Range(0.0001, 10)) = 0.1
   }
   SubShader
   {
      Tags { "Queue" = "Transparent" "RenderType" = "Transparent" }
      LOD 100

      ZWrite On // We need to write in depth to avoid tearing issues
      Blend SrcAlpha OneMinusSrcAlpha
	  Cull Off

      Pass
      {
         CGPROGRAM
         #pragma vertex vert
         #pragma fragment frag
         #pragma multi_compile _ UNITY_SINGLE_PASS_STEREO STEREO_INSTANCING_ON STEREO_MULTIVIEW_ON
         #include "UnityCG.cginc"

         struct appdata
         {
            float4 vertex : POSITION;
            float2 uv : TEXCOORD0;
            float2 uv1 : TEXCOORD1;
            UNITY_VERTEX_INPUT_INSTANCE_ID
         };

         struct v2f
         {
            float2 uv : TEXCOORD0;
			float4 worldSpacePos : TEXCOORD1;
            float4 vertex : SV_POSITION;
            UNITY_VERTEX_OUTPUT_STEREO
         };

		 float _GridSize;
         float _Thickness;
		 float _GridSizeSecondary;
         float _SecondaryThickness;

         fixed4 _MainColor;
         fixed4 _SecondaryColor;

         v2f vert (appdata v)
         {
            v2f o;
            UNITY_SETUP_INSTANCE_ID(v);
            UNITY_INITIALIZE_VERTEX_OUTPUT_STEREO(o);
            o.vertex = UnityObjectToClipPos(v.vertex);

            // Remap UVs from [0:1] to [-0.5:0.5] to make scaling effect start from the center 
            o.uv = v.uv - 0.5f;
            // Scale the whole thing if necessary
            //o.uv *= _GraduationScale;

			o.worldSpacePos = mul(unity_ObjectToWorld, v.vertex);
            return o;
         }

         // Remap value from a range to another
         float remap(float value, float from1, float to1, float from2, float to2) {
            return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
         }

         fixed4 frag (v2f i) : SV_Target
         {
            fixed4 col = _MainColor;

			if (
				any(
					float3(1.0f, 1.0f, 1.0f) <=
						step(
							abs(i.worldSpacePos.xyz % float3(_GridSize, _GridSize, _GridSize)),
							float3(1.0f, 1.0f, 1.0f) * (_Thickness - (_Thickness/2.0f))))) {
					col.a = 1.0f;
			} else if (
				any(
					float3(1.0f, 1.0f, 1.0f) <=
						step(
							abs(i.worldSpacePos.xyz % float3(_GridSizeSecondary, _GridSizeSecondary, _GridSizeSecondary)),
							float3(1.0f, 1.0f, 1.0f) * (_SecondaryThickness - (_SecondaryThickness/2.0f))))) {
					col = _SecondaryColor;
			} else {
				col.a = 0.0f;
			}

			return col;
         }

         ENDCG
      }
   }
}
