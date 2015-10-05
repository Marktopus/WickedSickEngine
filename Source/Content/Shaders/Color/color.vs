
cbuffer LightBuffer
{
  float4x4  modelToWorld;
  float4x4  worldToClip;
  float3    lightDir;
  float3    cameraPos;
};

struct VertexInput
{
  float3 position : POSITION;
  float3 normal : NORMAL;
  float4 color : COLOR;
};

struct PixelInputType
{
  float4 position : SV_POSITION;
  float4 normal : NORMAL;
  float4 color : COLOR;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType main(VertexInput input)
{
  PixelInputType output;
  output.position = mul(float4(input.position.xyz, 1), modelToWorld);
  float3 lightDirNorm = normalize(-lightDir);
  float3 view = normalize(cameraPos - output.position.xyz);
  // Calculate the position of the vertex against the world, view, and projection matrices.
  output.position = mul(output.position, worldToClip);

  float4 normalWorldSpace = mul(float4(input.normal, 0), modelToWorld);
  normalWorldSpace = normalize(normalWorldSpace);
  float nDotL = max(dot(lightDirNorm, normalWorldSpace.xyz), 0);
  // Store the input color for the pixel shader to use.
  

  float3 halfVector = (lightDirNorm + view) / 2;

  float nDotH = max(dot(normalWorldSpace.xyz, halfVector), 0);
  float intensity = pow(nDotH, 20);

  float specular = min(intensity * nDotH, 1);


  output.color = input.color * (nDotL + specular * input.color);//input.color;//float4(input.normal, 1);
  output.position.z = 0;
    
  //output.color = float4(1,0,0,1);
  output.normal = normalWorldSpace;
  return output;
}