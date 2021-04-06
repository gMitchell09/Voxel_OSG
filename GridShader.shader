Shader "Unlit/GridShader"
{
   Properties
   {
      _MainColor("Main Color", Color) = (0.5, 1.0, 1.0)
      _SecondaryColor("Secondary Color", Color) = (0.0, 0.0, 0.0)

      [Header(Grid)]
	  _GridSize("Major Grid Spacing", Range(1, 1000)) = 100
      _Thickness("Lines Thickness", Range(0.01, 10)) = 0.3
      _GridSizeSecondary("Minor Grid Spacing", Range(1, 1000)) = 10.0
      _SecondaryThickness("Lines Thickness (minor grid)", Range(0.01, 10)) = 0.1

	  _BlurFactor("Line Blur Factor", Range(0.1, 32)) = 2.0
	  _SecondaryBlurFactor("Line Blur Factor (minor grid)", Range(0.1, 32)) = 2.0
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
         float _BlurFactor;
         float _SecondaryBlurFactor;

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

		 float3 max3(float3 vec) {
			return max(max(vec.x, vec.y), vec.z);
		 }

         fixed4 frag (v2f i) : SV_Target
         {
            fixed4 mainCol = _MainColor;
            fixed4 secCol = _SecondaryColor;
			mainCol.a = 0.0f;
			secCol.a = 0.0f;

			float c1, c2, c3, c4;
			c1 = max3(smoothstep(
						(_GridSize - _Thickness/_BlurFactor) * float3(1.0f, 1.0f, 1.0f),
						(_GridSize + _Thickness/_BlurFactor) * float3(1.0f, 1.0f, 1.0f),
						abs(i.worldSpacePos.xxz % float3(_GridSize, _GridSize, _GridSize))));

			c2 = max3(smoothstep(
						(_GridSize - _Thickness/_BlurFactor) * float3(1.0f, 1.0f, 1.0f),
						(_GridSize + _Thickness/_BlurFactor) * float3(1.0f, 1.0f, 1.0f),
						float3(_GridSize, _GridSize, _GridSize) - abs(i.worldSpacePos.xxz % float3(_GridSize, _GridSize, _GridSize))));

			c3 = max3(smoothstep(
						(_GridSizeSecondary - _SecondaryThickness/_SecondaryBlurFactor) * float3(1.0f, 1.0f, 1.0f),
						(_GridSizeSecondary + _SecondaryThickness/_SecondaryBlurFactor) * float3(1.0f, 1.0f, 1.0f),
						abs(i.worldSpacePos.xxz % float3(_GridSizeSecondary, _GridSizeSecondary, _GridSizeSecondary))));

			c4 = max3(smoothstep(
						(_GridSizeSecondary - _SecondaryThickness/_SecondaryBlurFactor) * float3(1.0f, 1.0f, 1.0f),
						(_GridSizeSecondary + _SecondaryThickness/_SecondaryBlurFactor) * float3(1.0f, 1.0f, 1.0f),
						float3(_GridSizeSecondary, _GridSizeSecondary, _GridSizeSecondary) - abs(i.worldSpacePos.xxz % float3(_GridSizeSecondary, _GridSizeSecondary, _GridSizeSecondary))));

			mainCol.a = max(c1, c2);
			secCol.a = max(c3, c4);
			if (mainCol.a > secCol.a) return mainCol;
			else if (secCol.a > mainCol.a) return secCol;

			return mainCol;
         }

         ENDCG
      }
   }
}
